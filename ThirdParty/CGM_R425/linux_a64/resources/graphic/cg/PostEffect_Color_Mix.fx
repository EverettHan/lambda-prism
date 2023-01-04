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

float4 u_Color
<
> = float4(0.68f, 0.54f, 0.39f, 1.f);


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_ColorMix_PS(pixelInput IN,
                          uniform samplerRECT iInputTexture,
                          uniform float4 iCol
                          ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture,  screenCoord.xy);
 
	col = lerp(col, (2-4*iCol)*(col*col)+(4*iCol-1)*col, iCol.w);
	col.w = 1.f;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_ColorMix_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_ColorMix_PS(Auto_EyeMap, u_Color);
    }
}

technique Effect_ColorMix_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_ColorMix_PS(Auto_EyeMap, u_Color);
    }
}

technique Effect_ColorMix_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_ColorMix_PS(Auto_EyeMap, u_Color);
    }
}

technique Effect_ColorMix_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_ColorMix_PS(Auto_EyeMap, u_Color);
    }
}


