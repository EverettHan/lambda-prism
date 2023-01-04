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

float u_Brightness
<
	float UIMin		= -1;
	float UIMax		= 1;
	float UIStep	= 0.01f;
> = float(0.f);

float u_Contrast
<
	float UIMin		= 0;
	float UIMax		= 2;
	float UIStep	= 0.01f;
> = float(1.f);


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Color_BrightnessContrast_PS(pixelInput IN,
                                          uniform samplerRECT iInputTexture,
                                          uniform float iB,
                                          uniform float iC
                                          ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture,  screenCoord.xy);
	
	col = (col-0.5f)*iC+0.5f+iB;
	
	return float4(col.xyz, 1.f);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_BrightnessContrast_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Brightness, u_Contrast);
  }
}

technique Effect_Color_BrightnessContrast_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Brightness, u_Contrast);
  }
}

technique Effect_Color_BrightnessContrast_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Brightness, u_Contrast);
  }
}

technique Effect_Color_BrightnessContrast_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Brightness, u_Contrast);
  }
}


