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

float u_Size
<
	float UIMin		= 0;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = 4.f;

float u_Delta
<
	float UIMin		= -1.f;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = 0.f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

#define KERNEL_SIZE     12
float2  KERNEL[KERNEL_SIZE]=
{
    {-0.326212f, -0.405805f},
    {-0.840144f, -0.07358f},
    {-0.695914f, 0.457137f},
    {-0.203345f, 0.620716f},
    {0.96234f,   -0.194983f},
    {0.473434f,  -0.480026f},
    {0.519456f, 0.767022f},
    {0.185461f, -0.893124f},
    {0.507431f, 0.064425f},
    {0.530992f,  0.412458f},
    {-0.32194f, -0.871945f},
    {-0.791559f, 0.597705f}
};
						  
float4 Effect_Dilatation_PS (pixelInput IN) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
  
  float4 colInit  = texRECT(Auto_EyeMap, screenCoord);
  float4 deltaCol = float4(0,0,0,0);
			
  for (int i=0; i<KERNEL_SIZE; i++)
  {
    float4 col = (1.f+u_Delta) * texRECT(Auto_EyeMap, screenCoord + u_Size*KERNEL[i].xy) - colInit;
    if (col.x < deltaCol.x) deltaCol.x = col.x;
    if (col.y < deltaCol.y) deltaCol.y = col.y;
    if (col.z < deltaCol.z) deltaCol.z = col.z;
  }
	
  float4 resCol = colInit + deltaCol;
  resCol.w = 1.f;
  
  return resCol;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Dilatation_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Dilatation_PS();
  }
}
