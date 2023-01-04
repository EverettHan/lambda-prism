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

float u_Gamma
<
	float UIMin		= 0;
	float UIMax		= 4.f;
	float UIStep	= 0.01f;
> = float(1.f);


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Color_BrightnessContrast_PS(pixelInput IN,
                                          uniform samplerRECT iInputTexture,
                                          uniform float iGama
                                          ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture,  screenCoord.xy);
	
	col.xyz = pow(col.xyz, 1.f/iGama);
	
	return float4(col.xyz, 1.f);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_BrightnessContrast_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Gamma);
  }
}

technique Effect_Color_BrightnessContrast_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Gamma);
  }
}

technique Effect_Color_BrightnessContrast_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Gamma);
  }
}

technique Effect_Color_BrightnessContrast_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_Color_BrightnessContrast_PS(Auto_EyeMap, u_Gamma);
  }
}


