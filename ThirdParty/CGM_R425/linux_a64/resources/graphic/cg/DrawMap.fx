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

float mapRatio
<
>  = float(1);

samplerRECT Auto_InputMap_0
<
> = sampler_state
{
  magFilter = Linear;
  minFilter = Linear;
};

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 DrawMapPS(pixelInput IN) : COLOR 
{
  float4 screenCoord = IN.ScreenPosition; 
  
  float4 result = texRECT(Auto_InputMap_0, screenCoord.xy*mapRatio);
  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique DrawMap_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 DrawMapPS();
  }
}

technique DrawMap_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf DrawMapPS();
  }
}

technique DrawMap_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 DrawMapPS();
  }
}

technique DrawMap_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 DrawMapPS();
  }
}


