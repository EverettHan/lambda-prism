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

samplerRECT Auto_AlphaColorMap
<
>;

samplerRECT Auto_AlphaDepthMap
<
>;

samplerRECT Auto_AlphaZMap
<
>;

samplerRECT Auto_AlphaZMapScene
<
>;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------


float4 WeightedAverageFinalPS(pixelInput IN,
                uniform samplerRECT iAlphaColorTexture,
                uniform samplerRECT iAlphaDepthTexture,
                uniform samplerRECT iZTex,
                uniform samplerRECT iZTexScene
                ) : COLOR
{   

  float4 coord =  IN.ScreenPosition;	

  float4 sumColor =  texRECT(iAlphaColorTexture, coord.xy);
  float  n        =  texRECT(iAlphaDepthTexture, coord.xy).r;

  if(n <= 0.1)
    discard;

  if(texRECT(iZTexScene, coord.xy).r < texRECT(iZTex, coord.xy).r)
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

technique SmoothTexture_NV40
{
    pass p0 
    {
        FragmentProgram = compile fp40 WeightedAverageFinalPS(Auto_AlphaColorMap, Auto_AlphaDepthMap, Auto_AlphaZMap, Auto_AlphaZMapScene);
    }
}

technique SmoothTexture_GLSL
{
    pass p0 
    {	
        FragmentProgram = compile glslf WeightedAverageFinalPS(Auto_AlphaColorMap, Auto_AlphaDepthMap, Auto_AlphaZMap, Auto_AlphaZMapScene);
    }
}

technique SmoothTexture_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 WeightedAverageFinalPS(Auto_AlphaColorMap, Auto_AlphaDepthMap, Auto_AlphaZMap, Auto_AlphaZMapScene);
    }
}

technique SmoothTexture_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 WeightedAverageFinalPS(Auto_AlphaColorMap, Auto_AlphaDepthMap, Auto_AlphaZMap, Auto_AlphaZMapScene);
    }
}