//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

#include "Effect_General.hfx"

//--------------------------------
// Tweakables
//--------------------------------

samplerRECT Auto_EyeMap
<
>;

float4 Auto_Position
<
>;

float u_DotSizeInPixel
<	
  float UIMin		= 1.f;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = float(11.f);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
			
			
float4 ComputeColor(float2				      iScreenCoord,
	                  float2				      iScreenDelta,
	                  uniform samplerRECT iInputTexture,
	                  const int			      iSizePic)
{
	float radius = (float)iSizePic*1.44f*0.5f;
	    
  float2 pt = float2(
			iScreenCoord.x-((int)(iScreenCoord.x-iScreenDelta.x))%iSizePic, 
			iScreenCoord.y-((int)(iScreenCoord.y-iScreenDelta.y))%iSizePic);
        
  float4 tmpCol = float4(0,0,0,0);
  float luminance = 0;
  for (int i=0; i<iSizePic; i++)
  {
		for (int j=0; j<iSizePic; j++)
		{
			tmpCol += texRECT(iInputTexture, pt.xy+float2(i,j));   
		}
  }   
  tmpCol *= (1.f/(iSizePic*iSizePic));
  tmpCol = 1 - tmpCol;
  tmpCol *= radius;   
    	
	pt = iScreenCoord.xy - pt.xy - float2(iSizePic*0.5f, iSizePic*0.5f);
	float value = pt.x*pt.x+pt.y*pt.y;
	
	float4 col = float4(0,0,0,0);
	
	float4 colMin = tmpCol-1.f;
	if (colMin.x<0) colMin.x = 0;
	if (colMin.y<0) colMin.y = 0;
	if (colMin.z<0) colMin.z = 0;
	
	float4 colMax = tmpCol+1.f;
	
	colMin = colMin*colMin;
	colMax = colMax*colMax;
	
	col.x = smoothstep(colMin.x, colMax.x, value+1.f);
	col.y = smoothstep(colMin.y, colMax.y, value+1.f);
	col.z = smoothstep(colMin.z, colMax.z, value+1.f);
		
  return col;
}			
								  
float4 Effect_DotRGB_PS(pixelInput          IN,
                    uniform samplerRECT iInputTexture,
                    uniform float4		  iPos,
                    uniform float       iDotSizeInPixel
                    ) : COLOR 
{
	int    dotSize     =(int)iDotSizeInPixel;	
	float4 col         = float4(0,0,0,1.f);
  float2 screenCoord = IN.texCoord.xy;
  
  col.x = ComputeColor(screenCoord, iPos.zw+float2(0, dotSize*0.25f),					      iInputTexture, dotSize).x;
  col.y = ComputeColor(screenCoord, iPos.zw+float2(-dotSize*0.25f, -dotSize*0.25f),	iInputTexture, dotSize).y;
  col.z = ComputeColor(screenCoord, iPos.zw+float2(dotSize*0.25f,  -dotSize*0.25f),	iInputTexture, dotSize).z;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_DotRGB_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_DotRGB_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}

technique Effect_DotRGB_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_DotRGB_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}

technique Effect_DotRGB_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_DotRGB_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}

technique Effect_DotRGB_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_DotRGB_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}


