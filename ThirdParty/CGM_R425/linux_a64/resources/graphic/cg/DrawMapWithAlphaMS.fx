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

float Auto_NbAASamples
<
>;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 DrawMapWithAlphaPS(pixelInput IN) : COLOR 
{
  int2 screenCoord = IN.ScreenPosition; 
  float4 result = texRECT(Auto_InputMap_0, screenCoord.xy); 
  float sumW = 0;

  for(unsigned int curSample = 0 ; curSample < Auto_NbAASamples ; ++curSample)
    sumW += result.w * tex2DMSfetch(Auto_NormalMap, screenCoord.xy, curSample).w*ratio;
  
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
    FragmentProgram = compile glslf DrawMapWithAlphaPS();
  }
}
