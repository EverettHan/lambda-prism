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

float u_NumValue
<
	float UIMin		= 0;
	float UIMax		= 255;
	float UIStep	= 1;
> = float(14);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Color_Discretize_PS(pixelInput IN,
                uniform samplerRECT iInputTexture,
                uniform float iNumValue
                ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture,  screenCoord.xy);
	
	col.x = (int)(col.x*iNumValue);
	col.y = (int)(col.y*iNumValue);
	col.z = (int)(col.z*iNumValue);
	
	col *= 1.f/iNumValue;
	
	col.w = 1.f;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_Discretize_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_Color_Discretize_PS(Auto_EyeMap, u_NumValue);
  }
}

technique Effect_Color_Discretize_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Color_Discretize_PS(Auto_EyeMap, u_NumValue);
  }
}

technique Effect_Color_Discretize_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_Color_Discretize_PS(Auto_EyeMap, u_NumValue);
  }
}

technique Effect_Color_Discretize_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_Color_Discretize_PS(Auto_EyeMap, u_NumValue);
  }
}


