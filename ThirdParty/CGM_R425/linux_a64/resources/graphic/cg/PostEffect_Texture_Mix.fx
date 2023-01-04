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

float4 Auto_Size
<
>;

float4 Auto_Position
<
>;

sampler2D s_BackgroundTexture
<
	string File = "Noise256_01.dds";
>;

float     u_Alpha
<  
  float UIMin		= 0.f;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = float(1.f);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_TextureMix_PS(pixelInput IN,
                            uniform samplerRECT iInputTexture,
                            uniform float4		iSize,
                            uniform float4		iPos,
                            uniform sampler2D	iBgTexture,
                            uniform float     iAlpha
                            ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
    
	float4 col   = texRECT(iInputTexture,	screenCoord.xy);    
	float4 bgCol = tex2D  (iBgTexture,	   (screenCoord.xy+iPos.xy)*iSize.zw);
	
	col = lerp(col, (2-4*bgCol)*(col*col)+(4*bgCol-1)*col, iAlpha);
	col.w = 1;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_TextureMix_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_TextureMix_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                        s_BackgroundTexture, u_Alpha);
  }
}

technique Effect_TextureMix_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_TextureMix_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                        s_BackgroundTexture, u_Alpha);
  }
}

technique Effect_TextureMix_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_TextureMix_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                        s_BackgroundTexture, u_Alpha);
  }
}

technique Effect_TextureMix_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_TextureMix_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                        s_BackgroundTexture, u_Alpha);
  }
}


