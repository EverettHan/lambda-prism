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

float u_Max
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01;
> = 1.f;

float u_Min
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01;
> = 0.f;

float u_SeuilMin
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01;
> = 0.5f;

float u_SeuilMax
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01;
> = 0.5f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
									  
float4 Effect_Color_Seuil_WithMax_PS(pixelInput IN) : COLOR 
{
	float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(Auto_EyeMap, screenCoord);  
	
	float l = max(col.x, max(col.y, col.z));
	if (l<=u_SeuilMin)      l = u_Min;
	else if (l>=u_SeuilMax) l = u_Max;
	else                    l = lerp(u_Min, u_Max, (float)(l-u_SeuilMin)/(float)(u_SeuilMax-u_SeuilMin));
	
	return float4(l, l, l, 1.f);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_Seuil_WithMax_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_Seuil_WithMax_PS();
    }
}
