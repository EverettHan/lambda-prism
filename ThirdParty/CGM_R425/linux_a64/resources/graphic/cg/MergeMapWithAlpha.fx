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

samplerRECT Auto_NormalMap
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

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 MergeMapWithAlphaPS(pixelInput IN) : COLOR 
{
  float4 screenCoord = IN.ScreenPosition; 
  
  float4 result1 = texRECT(Auto_InputMap_0, screenCoord.xy); 
  float4 result2 = texRECT(Auto_InputMap_1, screenCoord.xy); 
  float4 result  = lerp(result2, result1, ratio);
  
  result.w *= texRECT(Auto_NormalMap, screenCoord.xy).w;
  
  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique DrawMapWithAlpha_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 MergeMapWithAlphaPS();
  }
}

technique DrawMapWithAlpha_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf MergeMapWithAlphaPS();
  }
}

technique DrawMapWithAlpha_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 MergeMapWithAlphaPS();
  }
}

technique DrawMapWithAlpha_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 MergeMapWithAlphaPS();
  }
}


