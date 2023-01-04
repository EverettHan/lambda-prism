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

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Color_Desaturate_PS(pixelInput IN,
                                  uniform samplerRECT iInputTexture
                                  ) : COLOR 
{
  const float4 LUMINANCE=float4(0.3f, 0.6f, 0.1f, 0);
  
  float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture,  screenCoord.xy);
	
	float luminance = dot(LUMINANCE, col);
  col = float4(luminance, luminance, luminance, 1.f);
    	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_Desaturate_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_Color_Desaturate_PS(Auto_EyeMap);
    }
}

technique Effect_Color_Desaturate_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_Desaturate_PS(Auto_EyeMap);
    }
}

technique Effect_Color_Desaturate_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_Color_Desaturate_PS(Auto_EyeMap);
    }
}

technique Effect_Color_Desaturate_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_Color_Desaturate_PS(Auto_EyeMap);
    }
}


