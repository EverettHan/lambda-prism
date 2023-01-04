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

float       u_BlurSize
<
    float uimin = 0.f;
    float uimax = 0.2f;
    float uistep=0.001f;
> = 0.04f;

float4      Auto_Size
<
>;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

#define NUM_BLUR 12
#define INV_NUM_BLUR 0.08333334
float2 filterBlurData[NUM_BLUR]=
{
  {-0.326212f,  -0.405805f},
  {-0.840144f,  -0.07358f },
  {-0.695914f,  0.457137f },
  {-0.203345f,  0.620716f },
  {0.96234f,    -0.194983f},
  {0.473434f,   -0.480026f},
  {0.519456f,   0.767022f },
  {0.185461f,   -0.893124f},
  {0.507431f,   0.064425f },
  {0.89642f,    0.412458f },
  {-0.32194f,   -0.932615f},
  {0.791559f,   -0.597705f}
};					
								  
float4 Effect_Blur_Poisson_PS(pixelInput IN,
                              uniform samplerRECT iInputTexture,
                              uniform float     iBlurSize
                              ) : COLOR 
{
  float4 result = float4(0,0,0,1); 
	float2 screenCoord = IN.texCoord.xy;

  for(int i=0; i<NUM_BLUR; i++)
  {
    float2 coord = screenCoord.xy + iBlurSize * filterBlurData[i] * Auto_Size.x;
    result += texRECT(iInputTexture,	coord); 
  }

  result.xyz *= INV_NUM_BLUR;
  result.w = 1;

  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Blur_Poisson_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 Effect_Blur_Poisson_PS(Auto_EyeMap, u_BlurSize);
  }
}

technique Effect_Blur_Poisson_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf Effect_Blur_Poisson_PS(Auto_EyeMap, u_BlurSize);
  }
}

technique Effect_Blur_Poisson_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 Effect_Blur_Poisson_PS(Auto_EyeMap, u_BlurSize);
  }
}

technique Effect_Blur_Poisson_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 Effect_Blur_Poisson_PS(Auto_EyeMap, u_BlurSize);
  }
}


