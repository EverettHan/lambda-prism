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

float u_Delta
<
	float UIMin		= -1.f;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

#define kernelSize 4
float2  kernel[kernelSize]=
{
  float2( 0,-1),
  float2( 0, 1),
  float2(-1, 0),
  float2( 1, 0)
};
								  
float4 Effect_Erosion_PS (pixelInput IN) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
  
  float4 colInit  = texRECT(Auto_EyeMap, screenCoord);
  float4 deltaCol = float4(0,0,0,0);
			
  for (int i=0; i<kernelSize; i++)
  {
    float4 col = (1.f+u_Delta) * texRECT(Auto_EyeMap, screenCoord + kernel[i].xy ) - colInit;
    if (col.x > deltaCol.x) deltaCol.x = col.x;
    if (col.y > deltaCol.y) deltaCol.y = col.y;
    if (col.z > deltaCol.z) deltaCol.z = col.z;
  }
	
	float4 resCol = colInit + deltaCol;
  resCol.w = 1.f;
  
  return resCol;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Erosion_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Erosion_PS();
  }
}
