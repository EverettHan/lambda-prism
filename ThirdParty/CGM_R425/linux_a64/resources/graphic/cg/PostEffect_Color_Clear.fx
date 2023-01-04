//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

#include "Effect_General.hfx"

//--------------------------------
// Tweakables
//--------------------------------

float4 u_ClearColor
<
> = float4(0,0,0,0);


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
									  
float4 Effect_Color_Clear_PS(pixelInput IN) : COLOR 
{
	return u_ClearColor;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_Clear_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Color_Clear_PS();
  }
}



