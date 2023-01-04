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

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 DrawMapWithAlphaPS(pixelInput IN) : COLOR 
{
  float4 screenCoord = IN.ScreenPosition; 
  float4 result = texRECT(Auto_InputMap_0, screenCoord.xy); 
  result.w *= texRECT(Auto_NormalMap, screenCoord.xy).w*ratio;
  
  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique DrawMapWithAlpha_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 DrawMapWithAlphaPS();
  }
}

technique DrawMapWithAlpha_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf DrawMapWithAlphaPS();
  }
}

technique DrawMapWithAlpha_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 DrawMapWithAlphaPS();
  }
}

technique DrawMapWithAlpha_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 DrawMapWithAlphaPS();
  }
}


