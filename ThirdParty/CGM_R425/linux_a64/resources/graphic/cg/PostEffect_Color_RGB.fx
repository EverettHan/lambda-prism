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

float u_Red
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = float(0.5f);

float u_Green
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = float(0.5f);

float u_Blue
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = float(0.5f);


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
									  
float4 Effect_Color_RGB_PS(pixelInput IN,
                    uniform samplerRECT iInputTexture,
                    uniform float iRed, 
                    uniform float iGreen, 
                    uniform float iBlue
                    ) : COLOR 
{
	float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture, screenCoord);  
	
	float4 ratio = float4(iRed, iGreen, iBlue, 1.f);
	col = (2-4*col)*(ratio*ratio)+(4*col-1)*ratio;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_RGB_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_Color_RGB_PS(Auto_EyeMap, u_Red, u_Green, u_Blue);
    }
}

technique Effect_Color_RGB_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_RGB_PS(Auto_EyeMap, u_Red, u_Green, u_Blue);
    }
}

technique Effect_Color_RGB_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_Color_RGB_PS(Auto_EyeMap, u_Red, u_Green, u_Blue);
    }
}

technique Effect_Color_RGB_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_Color_RGB_PS(Auto_EyeMap, u_Red, u_Green, u_Blue);
    }
}


