layout(location = 0) out vec4 fragColor;

//#ifdef IS_MSAA
//  uniform coherent layout(rgba32ui) uimage2DMS cellIndices;
//#else
//  uniform coherent layout(rgba32ui) uimage2D cellIndices;
//#endif

//layout(std430) buffer hashMapBuffer
//{
//  HashRecordContrib hashMap[];
//};

void resetPixelsToUpdate() { hashMap[cb_PostEffect_RT_AO.u_HashTableSize].contribWeight = 0; }

void getCellContrib(uint cellId, inout float ao, inout uint weight)
{
  if (cellId != HASH_CELL_NOT_FOUND)
  {
    uvec2 contrib = getContribWeight(hashMap[cellId].contribWeight);

    if (contrib.y > 0)
    {
      ao = contrib.x / float(contrib.y);
      weight = contrib.y;
      return;
    }
  }
  weight = 0;
  ao = 0.f;
}

float getHashAO(ivec2 index
#ifdef IS_MSAA
  , in int iMSAASample
#endif
)
{
  float ao = 1.0;
  const uint threshold = 200;
  const float inverseTreshold = 1.0 / float(threshold);

  vec4 cellAo = vec4(0);
  uvec4 wAo = uvec4(0);

  #ifdef IS_MSAA
    uvec4 cellIds = imageLoad(cellIndices, index, iMSAASample);
  #else
    uvec4 cellIds = imageLoad(cellIndices, index);
  #endif

  getCellContrib(cellIds.x, cellAo.x, wAo.x);

  uvec4 outCellIds = uvec4(cellIds.x, uvec3(HASH_CELL_NOT_FOUND));


  vec4 weights = vec4(0.0);

  uint combinedW = wAo.x;
  weights.x = max(0.f, min(1.f, wAo.x*inverseTreshold));

  if (combinedW < threshold)
  {
    outCellIds.y = cellIds.y;
    getCellContrib(cellIds.y, cellAo.y, wAo.y);
    weights.y = max(0.f, min(1.f - weights.x, wAo.y*inverseTreshold));
    combinedW += wAo.y;
    if (combinedW < threshold)
    {
      outCellIds.z = cellIds.z;
      getCellContrib(cellIds.z, cellAo.z, wAo.z);
      weights.z = max(0.f, min(1.f - weights.x - weights.y, wAo.z*inverseTreshold));
      combinedW += wAo.z;
      if (combinedW < threshold)
      {
        outCellIds.w = cellIds.w;
        getCellContrib(cellIds.w, cellAo.w, wAo.w);
        weights.w = max(0.f, min(1.f - weights.x - weights.y - weights.z, wAo.w*inverseTreshold));
      }
    }
  }

  float w = 0;
  if (wAo.x != 0) w += weights.x;
  if (wAo.y != 0) w += weights.y;
  if (wAo.z != 0) w += weights.z;
  if (wAo.w != 0) w += weights.w;

  if (w > 0.f)
    ao = (cellAo.x*weights.x + cellAo.y*weights.y + cellAo.z*weights.z + cellAo.w*weights.w) / w;

  #ifdef IS_MSAA
    imageStore(cellIndices, index, iMSAASample, outCellIds);
  #else
    imageStore(cellIndices, index, outCellIds);
  #endif
  return ao;

}

void main(void)
{
  ivec2 pixel = ivec2(gl_FragCoord.xy);

  if (pixel == ivec2(0, 0))
    resetPixelsToUpdate();

  float ao = 0.0;

  #ifdef IS_MSAA
    //for (int i = 0; i < IS_MSAA; ++i)
      ao += getHashAO(pixel, gl_SampleID);

    //ao *= 1.0 / IS_MSAA;
  #else
    ao = getHashAO(pixel);
  #endif


  ao = pow(clamp(ao, 0, 1), cb_PostEffect_RT_AO.u_AoPower);
  fragColor = vec4(ao);
  
  //uint cellid = imageLoad(cellIndices, ivec2(gl_FragCoord.xy), 0).x;
  //fragColor = vec4(cellIndexToColor(cellid), 1.0);

}
