//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

//--------------------------------
// Structure
//--------------------------------

struct vertexOutput
{
    float3 texCoord		  : TEXCOORD0;
};


//--------------------------------
// Tweakables
//--------------------------------

samplerRECT Auto_InputMap_0
<
>;

samplerRECT Auto_InputMap_1
<
>;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4x4 leftMatrix = {	0.299f, 0.587, 0.114, 0.0f,   
						0.0f, 0.0f, 0.0f, 0.0f, 
						0.0f, 0.0f, 0.0f, 0.0f, 
						0.0f, 0.0f, 0.0f, 1.0f
						}; 

float4x4 rightMatrix = {0.0f, 0.0, 0.0, 0.0f,   
						0.299f, 0.587f, 0.114f, 0.0f, 
						0.299f, 0.587f, 0.114f, 0.0f,  
						0.0f, 0.0f, 0.0f, 1.0f
						};
								  
float4 StereoMergePS(vertexOutput IN,
                uniform samplerRECT iLeftTexture,
                uniform samplerRECT iRightTexture
                ) : COLOR 
{
  float4 result = float4(0,0,0,1); 

  float2 screenCoord = IN.texCoord.xy;
    
	float4 leftColor  = texRECT(iLeftTexture,  screenCoord.xy);
	float4 rightColor = texRECT(iRightTexture, screenCoord.xy);
	
	result = mul(leftMatrix, leftColor) + mul(rightMatrix, rightColor); 
	result.w = 1.f;

  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique StereoMerge_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 StereoMergePS(Auto_InputMap_0, Auto_InputMap_1);
    }
}

technique StereoMerge_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf StereoMergePS(Auto_InputMap_0, Auto_InputMap_1);
    }
}

technique StereoMerge_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 StereoMergePS(Auto_InputMap_0, Auto_InputMap_1);
    }
}

technique StereoMerge_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 StereoMergePS(Auto_InputMap_0, Auto_InputMap_1);
    }
}

