//
// Draw Blend Shadow Map (FBJ)
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

float ratio
<
> = float(1.f);

sampler2DMS Auto_NormalMap
<
> = sampler_state
{
  magFilter = Linear;
  minFilter = Linear;
};

samplerRECT Auto_InputMap_0
<
>;

samplerRECT Auto_InputMap_1
<
>;

float Auto_NbAASamples
<
>;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 MergeMapWithAlphaPS(pixelInput IN) : COLOR 
{
  int2 screenCoord = IN.ScreenPosition; 
  
  float4 result1 = texRECT(Auto_InputMap_0, screenCoord.xy); 
  float4 result2 = texRECT(Auto_InputMap_1, screenCoord.xy); 
  float4 result  = lerp(result2, result1, ratio);
  float sumW = 0;

  for(unsigned int curSample = 0 ; curSample < Auto_NbAASamples ; ++curSample)
  {
    sumW += result.w * tex2DMSfetch(Auto_NormalMap, screenCoord.xy, curSample).w;
  }

  result.w = sumW / Auto_NbAASamples;

  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique DrawMapWithAlpha_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf MergeMapWithAlphaPS();
  }
}
