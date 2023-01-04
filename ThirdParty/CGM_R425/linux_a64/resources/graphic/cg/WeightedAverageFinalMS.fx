//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

//--------------------------------
// Structure
//--------------------------------

struct pixelInput
{
    float4 ScreenPosition : TEXCOORD0;
};
    

//--------------------------------
// Tweakables
//--------------------------------

sampler2DMS Auto_AlphaColorMap
<
>;

sampler2DMS Auto_AlphaDepthMap
<
>;

float NbSamples
<
> = 1;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------


float4 WeightedAverageFinalPS(pixelInput IN,
                uniform sampler2DMS iAlphaColorTexture,
                uniform sampler2DMS iAlphaDepthTexture,
                uniform float       iNbSamples
                ) : COLOR 
{
  int2 coord =  IN.ScreenPosition.xy;	

  float4 sumColor = (0.,0.,0.,0.);
  float  n        = 0.;

  for(int i = 0 ; i < iNbSamples ; ++i)
  {
    sumColor += tex2DMSfetch(iAlphaColorTexture, coord.xy, i);
    n        += tex2DMSfetch(iAlphaDepthTexture, coord.xy, i).r;
  }

  sumColor /= iNbSamples;
  n        /= iNbSamples;

  if(n <= 0.1)
    discard;

  float3 avgColor = sumColor.rgb / sumColor.a;
  float  avgAlpha = sumColor.a   / n;

  avgAlpha = clamp(avgAlpha,0,0.999);

  float tmp = pow(1.0 - avgAlpha, n);

  return float4(avgColor, 1-tmp);
}



//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique SmoothTexture_GLSL
{
    pass p0 
    {
        FragmentProgram = compile glslf WeightedAverageFinalPS(Auto_AlphaColorMap, Auto_AlphaDepthMap, NbSamples);
    }
}


/*
technique SmoothTexture_GLSL
{
    pass p0 
    {	
        FragmentProgram = compile glslf WeightedAverageFinalPS(Auto_AlphaColorMap, Auto_AlphaDepthMap, Auto_AlphaZMap, Auto_AlphaZMapScene);
    }
}
*/