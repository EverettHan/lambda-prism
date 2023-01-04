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

sampler2DMS Auto_ZMap
<
>;

float4 Auto_Size
<
>;

float4 Auto_Focus
<
>;

float Auto_NbAASamples
<
>;


float u_BlurQuality
<	
	float UIMin		= 0;
	float UIMax		= 100.f;
	float UIStep	= 1.f;
> = 5.f;

float u_BlurSize
<
	float UIMin		= 0;
	float UIMax		= 0.1f;
	float UIStep	= 0.001f;
> = 0.01f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float GetBlurRadius(int2 iPt, unsigned int iSample)
{
  float focus = (Auto_Focus.y + 1.f) * 0.5f;
  float z = tex2DMSfetch(Auto_ZMap, iPt, iSample).x;
  
  float radius = abs(z-focus)/(1.f-focus);
  
  return radius;
}
							  
float4 Effect_DOFX_PS(pixelInput IN) : COLOR 
{
  float2 screenCoord  = IN.texCoord.xy; 

  float4 sumColor = float4(0.,0.,0.,0.);

  for(unsigned int curSample = 0 ; curSample < Auto_NbAASamples ; ++curSample)
  {
    float2 screenCoordToModif = screenCoord;

    float4 col       = float4(0,0,0,1.f);
    float blurRadius = GetBlurRadius(int2(screenCoordToModif.xy), curSample)*(u_BlurSize*Auto_Size.x);  

    screenCoordToModif.x -= blurRadius;  

    float deltaRadius = blurRadius/u_BlurQuality;

    float num = 0;

    for (int i=-u_BlurQuality; i<=u_BlurQuality; i++)
    {
      float ratio = GetBlurRadius(int2(screenCoordToModif.xy), curSample)*(1.f+u_BlurQuality-abs((float)i))+0.01;  

      col += texRECT(Auto_EyeMap, screenCoordToModif)*ratio; 
      num += ratio;

      screenCoordToModif.x += deltaRadius;
    }  

    col *= 1.f/(float) num;
    col.w = 1;

    sumColor += col;
  }
		
	return sumColor / Auto_NbAASamples;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_DOFX_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_DOFX_PS();
    }
}
