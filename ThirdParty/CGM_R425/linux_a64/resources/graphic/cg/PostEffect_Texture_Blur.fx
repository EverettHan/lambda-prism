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

float4      Auto_Size
<
>;

float4      Auto_Position
<
>;

sampler2D   s_BlurMap
<
	string File = "Noise256_01.dds";
>;

float       u_Scale
<
	float UIMin		= 1.f;
	float UIMax		= 100.f;
	float UIStep	= 0.1f;
> = 1.f;

float       u_Strength
<
	float UIMin		= 0;
	float UIMax		= 0.2f;
	float UIStep	= 0.001f;
> = 0.01f;

float       u_Quality
<
	float UIMin		= 1.f;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = 5.f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Texture_BlurX_PS(pixelInput IN,
                            uniform samplerRECT iInputTexture,
                            uniform float4		iSize,
                            uniform float4		iPos,
                            uniform sampler2D	iTexture,
                            uniform float     iScale,
                            uniform float     iStrength,
                            uniform float     iQuality
                            ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
    
  float4 bgCol = tex2D  (iTexture, ((screenCoord.xy+iPos.xy)*iSize.zw)*iScale);
			
  float ratio = dot(bgCol.xyz, float3(0.3,0.6,0.1));
  ratio *= iStrength*iSize.x/iQuality;
  
  int numStep = (int) iQuality;	
  float4 col = float4(0,0,0,1.f);
  for (int i=-numStep; i<=numStep; i++)
  {
    col += texRECT(iInputTexture,	screenCoord.xy+float2(i*ratio, 0));   
  }
    
  col *= (1.f/(numStep*2+1));
	
  col.w = 1;
	
  return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Texture_BlurX_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_Texture_BlurX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                  s_BlurMap, u_Scale, u_Strength, u_Quality);
  }
}

technique Effect_Texture_BlurX_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Texture_BlurX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                  s_BlurMap, u_Scale, u_Strength, u_Quality);
  }
}

technique Effect_Texture_BlurX_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_Texture_BlurX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                  s_BlurMap, u_Scale, u_Strength, u_Quality);
  }
}

technique Effect_Texture_BlurX_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_Texture_BlurX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                    s_BlurMap, u_Scale, u_Strength, u_Quality);
  }
}


