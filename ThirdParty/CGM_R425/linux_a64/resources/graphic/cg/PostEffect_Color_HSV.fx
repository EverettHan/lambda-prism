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

float u_Saturation
<
	float UIMin		= 0;
	float UIMax		= 4.f;
	float UIStep	= 0.01f;
> = float(1.f);

float u_Value
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = float(0.5f);

float u_Hue
<
	float UIMin		= 0;
	float UIMax		= 360;
	float UIStep	= 1.f;
> = float(0.f);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
				
#include "Effect_Color_Services.hfx"

float4 Effect_Color_HSV_PS(pixelInput IN,
                    uniform samplerRECT iInputTexture,
                    uniform float       iSaturation,
                    uniform float       iValue,
                    uniform float       iHue
                    ) : COLOR 
{
	float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture, screenCoord);  
	
  col = ConvertToHSL(col);

	col.x = fmod(col.x+iHue,360.f);
	col.y = saturate(col.y*iSaturation);
	col.z = (2-4*col.z)*(iValue*iValue)+(4*col.z-1)*iValue;
	
	col = ConvertToRGB(col);

	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_HSV_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_HSV_PS(Auto_EyeMap, u_Saturation, u_Value, u_Hue);
    }
}
