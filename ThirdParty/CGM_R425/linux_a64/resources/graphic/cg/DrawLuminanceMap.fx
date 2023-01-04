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

float4 color
<
> = float4(0,0,0,1);

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

float4 DrawLuminanceMapPS(pixelInput IN) : COLOR 
{
  float4 result = color; 
  float4 screenCoord = IN.ScreenPosition; 
  
  float occ = texRECT(Auto_InputMap_0, screenCoord.xy*mapRatio).x;
  result.w = color.w*(1.f-occ);
  
  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique DrawLuminanceMap_NV40
{
  pass p0 
  {		
    FragmentProgram = compile fp40 DrawLuminanceMapPS();
  }
}

technique DrawLuminanceMap_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf DrawLuminanceMapPS();
  }
}

technique DrawLuminanceMap_NV30
{
  pass p0 
  {		
    FragmentProgram = compile fp30 DrawLuminanceMapPS();
  }
}

technique DrawLuminanceMap_ARB
{
  pass p0 
  {		
    FragmentProgram = compile arbfp1 DrawLuminanceMapPS();
  }
}


