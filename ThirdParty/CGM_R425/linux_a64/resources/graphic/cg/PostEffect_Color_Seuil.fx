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

float u_ValueMax
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01;
> = 1.f;

float u_ValueMin
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
									  
float4 Effect_Color_Seuil_PS(pixelInput IN) : COLOR 
{
	float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(Auto_EyeMap, screenCoord);  
	
	float l = dot (col.xyz, float3(0.3f, 0.6f, 0.1f));
	if (l<=u_SeuilMin)      l = u_ValueMin;
	else if (l>=u_SeuilMax) l = u_ValueMax;
	else                    l = lerp(u_ValueMin, u_ValueMax, (float)(l-u_SeuilMin)/(float)(u_SeuilMax-u_SeuilMin));
	
	return float4(l, l, l, 1.f);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_Seuil_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_Seuil_PS();
    }
}
