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

sampler2D   s_Texture
<
	string File = "Noise256_01.dds";
>;

float       u_Scale
<
	float UIMin		= 1.f;
	float UIMax		= 100.f;
	float UIStep	= 0.1f;
> = 1.f;

float       u_Strenght
<
	float UIMin		= 0;
	float UIMax		= 0.2f;
	float UIStep	= 0.001f;
> = 0.01f;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Texture_Displacement_PS(pixelInput IN,
                            uniform samplerRECT iInputTexture,
                            uniform float4		iSize,
                            uniform float4		iPos,
                            uniform sampler2D	iTexture,
                            uniform float     iScale,
                            uniform float     iStrength
                            ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
    
	float4 bgCol = tex2D  (iTexture, ((screenCoord.xy+iPos.xy)*iSize.zw)*iScale);
	
  float ratio = iStrength*iSize.x;
		
	screenCoord += (bgCol.xy-float2(0.5,0.5))*ratio;
	float4 col   = texRECT(iInputTexture,	screenCoord.xy);    
	
	col.w = 1;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Texture_Displacement_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_Texture_Displacement_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                  s_Texture, u_Scale, u_Strenght);
  }
}

technique Effect_Texture_Displacement_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Texture_Displacement_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                  s_Texture, u_Scale, u_Strenght);
  }
}

technique Effect_Texture_Displacement_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_Texture_Displacement_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                  s_Texture, u_Scale, u_Strenght);
  }
}

technique Effect_Texture_Displacement_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_Texture_Displacement_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                    s_Texture, u_Scale, u_Strenght);
  }
}


