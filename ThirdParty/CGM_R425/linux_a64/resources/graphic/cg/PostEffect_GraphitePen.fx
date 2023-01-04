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

sampler2D s_PenTexture
<
>;

float4 Auto_Size
<
>;

float u_Scale
<
  float UIMin		= 0;
	float UIMax		= 100.f;
	float UIStep	= 0.1f;
> = 1.f;

float u_SMini
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.1f;

float u_S0
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.25f;

float u_S1
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.5f;

float u_S2
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.75f;

float u_S3
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 1.f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
						  
float4 Effect_GraphitePen_PS(pixelInput IN) : COLOR 
{
	float4 col          = texRECT(Auto_EyeMap, IN.texCoord.xy);  
	float luminance     = dot(col.xyz, float3(0.3f, 0.6f, 0.1f));

	float2 screenCoord  = IN.texCoord.xy*Auto_Size.zw*u_Scale;
	float2 screenCoord2 = float2(screenCoord.y, screenCoord.x);
	float2 screenCoord3 = float2(screenCoord.x*0.707f-screenCoord.y*0.707f, screenCoord.x*0.707f+screenCoord.y*0.707f);
		
	float visbility = 1.f;
	if (luminance<u_S0) visbility *= saturate((luminance+u_SMini)/u_S0);
	if (luminance<u_S1) visbility *= saturate(tex2D(s_PenTexture, screenCoord).x  + saturate((luminance-u_S0)/(u_S1-u_S0)));
	if (luminance<u_S2) visbility *= saturate(tex2D(s_PenTexture, screenCoord2).x + saturate((luminance-u_S1)/(u_S2-u_S1)));
	if (luminance<u_S3) visbility *= saturate(tex2D(s_PenTexture, screenCoord3).x + saturate((luminance-u_S2)/(u_S3-u_S2)));
	
	col.xyz = luminance;
  col.xyz = lerp(col.xyz, float3(1.f), visbility);
  col.w = 1.f;
  
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_ColoredPen_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_GraphitePen_PS();
    }
}




