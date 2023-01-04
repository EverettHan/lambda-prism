//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

//--------------------------------
// Tweakables
//--------------------------------

sampler2DMS Auto_NormalMap_WithTransparency
<
>;

//--------------------------------
// Structure
//--------------------------------

struct pixelInput
{
    float4 HPosition    : POSITION;
    float3 texCoord		  : TEXCOORD0;
};


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
						  
float4 DumpNormalMap(pixelInput IN) : COLOR 
{
  int2 screenCoord  = IN.texCoord.xy; 
  return tex2DMSfetch(Auto_NormalMap_WithTransparency, screenCoord, 0); 
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------


technique Effect_DOFX_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf DumpNormalMap();
    }
}





