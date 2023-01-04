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

samplerRECT Auto_NormalMap_WithTransparency
<
>;

float u_V0
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.f;

float u_V1
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.010f;
> = 0.5f;

float u_V2
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.010f;
> = 0.5f;

float u_V3
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.010f;
> = 0.5f;



float u_S0
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.001f;
> = 0.25f;

float u_S1Min
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.001f;
> = 0.26f;

float u_S1Max
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.001f;
> = 0.5f;

float u_S2Min
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.001f;
> = 0.51f;

float u_S2Max
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.001f;
> = 0.51f;

float u_S3
<
  float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.001f;
> = 0.51f;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
									  
#include "Effect_Color_Services.hfx"

float4 Effect_Color_Toon_PS(pixelInput IN) : COLOR 
{
	float4 colInit  = texRECT(Auto_EyeMap,     IN.texCoord.xy);  
	float  ratio    = texRECT(Auto_NormalMap_WithTransparency,  IN.texCoord.xy).w;  
	if (ratio!=1.f) discard;
	
	float4 colHSL = ConvertToHSL(colInit);
	
	float4 col = colInit;
	col = ConvertToRGB(float4(colHSL.xy, 1.f, colHSL.w));
	
	if (colHSL.z<u_S0)          col.xyz *= u_V0;
	else if (colHSL.z<u_S1Min)  col.xyz *= lerp(u_V0, u_V1, (colHSL.z-u_S0)/(u_S1Min-u_S0));
	else if (colHSL.z<u_S1Max)  col.xyz *= u_V1;
	else if (colHSL.z<u_S2Min)  col.xyz *= lerp(u_V1, u_V2, (colHSL.z-u_S1Max)/(u_S2Min-u_S1Max));
	else if (colHSL.z<u_S2Max)  col.xyz *= u_V2;
	else if (colHSL.z<u_S3)     col.xyz *= lerp(u_V2, u_V3, (colHSL.z-u_S2Max)/(u_S3-u_S2Max));
	else                        col.xyz *= u_V3;
		
	col.w = ratio;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_Toon_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_Toon_PS();
    }
}
