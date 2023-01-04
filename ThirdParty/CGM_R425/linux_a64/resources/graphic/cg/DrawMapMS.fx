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

sampler2DMS Auto_InputMap_0
<
>;

float Auto_NbSamples
<
> = 1;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 DrawMapMSPS(pixelInput IN) : COLOR 
{
  float4 screenCoord = IN.ScreenPosition; 
  
  float4 sumColor = (0.,0.,0.,0.);
  
  for(int i = 0 ; i < Auto_NbSamples ; ++i)
  {
    sumColor += tex2DMSfetch(Auto_InputMap_0, screenCoord.xy, i);
  }
  
  sumColor /= Auto_NbSamples;
  return sumColor;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------



technique DrawMapMS_GLSL
{
  pass p0 
  {		
    FragmentProgram = compile glslf DrawMapMSPS();
  }
}


