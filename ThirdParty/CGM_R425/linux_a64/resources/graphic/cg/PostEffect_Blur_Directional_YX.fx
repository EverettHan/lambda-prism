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

float u_Size
<
	float UIMin		= 0;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = 4.f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Color_BlurGaussian_PS (pixelInput IN) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
  
  float4 col  = float4(0,0,0,0);
  
  for (int i=-u_Size; i<=u_Size; i++)
  {
    col += texRECT(Auto_EyeMap, screenCoord+float2(0,i));
  }
  
  col *= 1.f/(u_Size*2+1);
  col.w = 1.f;
	
  return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_BlurGaussian_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Color_BlurGaussian_PS();
  }
}
