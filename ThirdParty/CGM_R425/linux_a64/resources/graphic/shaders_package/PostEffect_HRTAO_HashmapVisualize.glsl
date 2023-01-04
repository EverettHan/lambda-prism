/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

 // Final compositing for deferred shading with AO result, plus some debug output

//#version 450
//#extension GL_ARB_separate_shader_objects : enable
//#extension GL_EXT_nonuniform_qualifier : enable
//#extension GL_GOOGLE_include_directive : enable


//#include "common_spatial_hash.h"
//#include "hashmap_visualize_data.h"

const uvec2 digits[10] =
{
  uvec2(706880028, 471999018),
  uvec2(136845320, 1040713736),
  uvec2(67248668, 1042288648),
  uvec2(201466396, 471990786),
  uvec2(302646786, 33701666),
  uvec2(1008738366, 471990786),
  uvec2(1008734220, 471999010),
  uvec2(67371582, 269486088),
  uvec2(471999004, 471999010),
  uvec2(572662300, 402915870)
};

bool getPixel(uvec2 coord, uint number)
{
  uint part;
  uint yOffset;
  coord.y = 8 - coord.y;
  if (coord.y > 3)
  {
    part = digits[number].y;
    yOffset = 4;
  }
  else
  {
    part = digits[number].x;
    yOffset = 0;
  }
  return ((part >> (8*(coord.y-yOffset) + (8-coord.x))) & 0x1) ==1;
}

layout(location = 0) out vec4 outColor;

//layout(location = 0) in vec2 uv;

//#include "../bindings/hashmap_visualize_bindings.h"

// Hash map keys, each containing a checksum and the last time the cell was used
//layout(binding = eHashmapKeys) buffer hashMapBufferKey { HashRecordKey hashMapKeys[]; };
//layout(binding = eHistogram) buffer visualizeBuffer { HashMapVisualizeData visualizeData; };
//#include "hash_key_access.h"

vec3 fillRateToHeat(float fill)
{
  if (fill > 0.75)
    return vec3(1,0,0);
  if(fill > 0.5)
    return vec3(1, 1, 0);
  if(fill > 0.25)
    return vec3(0, 1, 0);
  return vec3(0,0,1);
}

vec3 getHeatMapColor(float value)
{
  const int NUM_COLORS = 4;
  vec3 color[NUM_COLORS] = { {0,0,1}, {0,1,0}, {1,1,0}, {1,0,0} };
    // A static array of 4 colors:  (blue,   green,  yellow,  red) using {r,g,b} for each.
  
  int idx1;        // |-- Our desired color will be between these two indexes in "color".
  int idx2;        // |
  float fractBetween = 0;  // Fraction between "idx1" and "idx2" where our value is.
  
  if(value <= 0)      {  idx1 = idx2 = 0;            }    // accounts for an input <=0
  else if(value >= 1)  {  idx1 = idx2 = NUM_COLORS-1; }    // accounts for an input >=0
  else
  {
    value = value * (NUM_COLORS-1);        // Will multiply value by 3.
    idx1  = int(floor(value));                  // Our desired color will be after this index.
    idx2  = idx1+1;                        // ... and before this index (inclusive).
    fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).
  }
    
  vec3 res;
  res.r   = (color[idx2].r - color[idx1].r)*fractBetween + color[idx1].r;
  res.g = (color[idx2].g - color[idx1].g)*fractBetween + color[idx1].g;
  res.b = (color[idx2].b - color[idx1].b)*fractBetween + color[idx1].b;
  return res;
}


void main() {

  uint pixelsInViz = resX*resY/4;
  if (cb_PostEffect_HRTAO.hashVisualizeMode == 0)
  {
    
    uint records = cb_PostEffect_HRTAO.hashTableSize;

    uint recordCount = max(100, (records+pixelsInViz-1)/pixelsInViz);

    ivec2 coord = ivec2(gl_FragCoord.xy);
    uint pixelId = coord.x + coord.y*resX;
    uint counter = 0;
    uint actualRecordCount=0;
    for(actualRecordCount=0; actualRecordCount < recordCount; actualRecordCount++)
    {
      uint index = actualRecordCount+recordCount*pixelId;
      if (index >= cb_PostEffect_HRTAO.hashTableSize)
        break;
      uint key = hashMapKeys[index];
      if (key !=0 && framesSinceLastAccess(cb_PostEffect_HRTAO_Auto.frameIdx, index) < (cb_PostEffect_HRTAO.cellLifespan+1)) // +1 as the frame ID has already been incremented
        counter++;
      //if (key.secondaryKey !=0 && framesSinceLastAccess(frameIdx, key) >= 10)
       // hashMapKeys[i+recordCount*pixelId].secondaryKey = 0;


    }
    if (actualRecordCount==0)
      discard;
    uint histogramCell = (10*counter)/actualRecordCount;
    if (histogramCell == 10)
      histogramCell = 9;
    atomicAdd(visualizeData.histogram[histogramCell], 1);

    float fillRate = float(counter)/float(actualRecordCount);
    //fillRate = log(1+(exp(2)-1)*fillRate);
    outColor = vec4(fillRateToHeat(fillRate),0.5);
    return;
  }    

  if (cb_PostEffect_HRTAO.hashVisualizeMode == 1)
  {
    outColor = vec4(1,0,0,1);

    uint columnExtent = resX/(8*10);

    uvec2 coord = uvec2(gl_FragCoord.xy) - uvec2((7*resX)/8, resY/4);
    coord.y = (resY/4) - coord.y;
    uint column = coord.x / columnExtent;

    bool isInColumn = true;

    if (coord.x%columnExtent < 3)
    {
      isInColumn = false;
      //outColor = vec4(1,1,1,0.1);
      //return;
    }

    // Offset by half a column to have the numbers inbetween the columns
    uvec2 pixelInColumn = uvec2((coord.x-columnExtent/2) %columnExtent, coord.y);

    if (column ==0 && (coord.x>(columnExtent/2)) && pixelInColumn.x > 3 && pixelInColumn.x < 11 && pixelInColumn.y < 9)
    {
      bool isDigit = getPixel(uvec2(pixelInColumn.x-3, pixelInColumn.y), column+1);
      if (isDigit)
      {
        outColor = vec4(1,0,0,1);
        return;
      }
    }

    if (column > 0 && column < 9 && pixelInColumn.x > 3 && pixelInColumn.x < 11 && pixelInColumn.y < 9)
    {
      bool isDigit = getPixel(uvec2(pixelInColumn.x-3, pixelInColumn.y), column+1);

      if (isDigit)
      {
        outColor = vec4(1,0,0,1);
        return;
      }
    }

    if (column>0  && pixelInColumn.x > 11 && pixelInColumn.x < 19 && pixelInColumn.y < 9)
    {
      bool isDigit = getPixel(uvec2(pixelInColumn.x-11, pixelInColumn.y), 0);
      if (isDigit)
      {
        outColor = vec4(1,0,0,1);
        return;
      }
    }


    uint recordCountPerPixel = max(64, (cb_PostEffect_HRTAO.hashTableSize+pixelsInViz-1)/pixelsInViz);
    uint actualPixelsInViz = 1+cb_PostEffect_HRTAO.hashTableSize/recordCountPerPixel;
    float colValue = float(visualizeData.histogram[column]) / float(actualPixelsInViz);


    if (isInColumn && colValue > float(coord.y)/float(resY/4))

      outColor = vec4(fillRateToHeat(float(column)/10.0),0.8);
    else
      outColor = vec4(1,1,1,(coord.x == 0)?1.0:0.1);
      //outColor = vec4(1,1,1,1);
    //outColor = vec4(vec2(gl_FragCoord.xy - vec2((7*resX)/8, resY/4))/vec2(resX/8, resY/4), 0, 1);

  }
    if (cb_PostEffect_HRTAO.hashVisualizeMode == 2)
  {
    //outColor = vec4(1,0,1,1);
    uvec2 coord = uvec2(gl_FragCoord.xy) - uvec2((7*resX)/8, 2*resY/4);

    //coord.y = (resY/4) - coord.y;
    uint lineExtent = resY/(8*10);

    float xCoord = coord.x / float(resX/8);

    uint success = visualizeData.allocations - visualizeData.collisions - visualizeData.fails;
    float successRatio = float(success)/float(visualizeData.allocations);
    float collisionRatio = float(visualizeData.collisions)/float(visualizeData.allocations);
    float failRatio = float(visualizeData.fails)/float(visualizeData.allocations);

    float ratio = visualizeData.collisions / float(visualizeData.allocations);

    float hopsToSucceed = visualizeData.hopsToSucceed / float(visualizeData.collisions);

    if (coord.y < 4 || coord.y > (3*lineExtent+8))
    {
      discard;
    }
    if (coord.y > lineExtent && coord.y < 2*lineExtent)
    {
      if (coord.y < lineExtent+4)
        discard;
      if (xCoord < hopsToSucceed/100.0)
      {
        outColor = vec4(1,1,0,0.8);
        return;
      }
      else
        discard;
    }

    if (coord.y > 2*lineExtent && coord.y < 3*lineExtent)
    {
      if (coord.y < 2*lineExtent+8)
        discard;
      if (xCoord < float(visualizeData.maxHopsToSucceed)/100.0)
      {
        uint step = uint(xCoord*10)%2;
        float alpha = step==0?0.8:0.5;

        if (xCoord < 32.0/100.0)
        {
          outColor = vec4(0,0,1,alpha);
          return;
        }
        if (xCoord < 64.0/100.0)
        {
          outColor = vec4(0,1,0,alpha);
          return;
        }
        if (xCoord < 96.0/100.0)
        {
          outColor = vec4(1,1,0,alpha);
          return;
        }
        outColor = vec4(1,0,0,alpha);
        return;
      }
      else
        discard;
    }

    if (coord.y < lineExtent)
    {
      if (xCoord < successRatio )
      {
        outColor = vec4(0,1,0,0.8);
        return;
      }
      if (xCoord < (successRatio+collisionRatio) )
      {
        outColor = vec4(1,1,0,0.8);
      }
      else
      {
        outColor = vec4(1,0,0,0.8);
      }
      return;

    }
    discard;

  }

}
