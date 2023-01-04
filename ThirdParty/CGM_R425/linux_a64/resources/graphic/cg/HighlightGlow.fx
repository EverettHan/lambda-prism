//
// Advanced Highlight Shader (FBJ)
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

float4 haloColor
<
> = float4(0,1,0,1);

float haloSize
<
> = 3;

samplerRECT Auto_EyeMap
<
>;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

#define NUM_BLUR 12
#define INV_NUM_BLUR 0.0833333333333333
float2 FILTERBLURDATA[NUM_BLUR]=
{
    {-0.326212f, -0.405805f},
    {-0.840144f, -0.07358f},
    {-0.695914f, 0.457137f},
    {-0.203345f, 0.620716f},
    {0.96234f,   -0.194983f},
    {0.473434f,  -0.480026f},
    {0.519456f, 0.767022f},
    {0.185461f, -0.893124f},
    {0.507431f, 0.064425f},
    {0.530992f,  0.412458f},
    {-0.32194f, -0.871945f},
    {-0.791559f, 0.597705f}
};

float4 HighlightGlowPS(pixelInput IN,
                uniform float       iHaloSize,
                uniform float4      iHaloColor,
                uniform samplerRECT iInputTexture
                ) : COLOR 
{
  float4 result = float4(1,0,0,1); 
    
  float4 screenCoord = IN.ScreenPosition;                  
  result = (texRECT(iInputTexture, screenCoord.xy));
   
	if (result.x != 0)
	{
		result.x = 0;
		for(int i=0; i<NUM_BLUR; i++)
		{
			float2 coord = screenCoord.xy + iHaloSize * FILTERBLURDATA[i];
			result.x += (texRECT(iInputTexture, coord).x);
		}

		result.x *= (INV_NUM_BLUR);
	}
	
  return result;
}

#define NUM_BLURLOW 6
#define INV_NUM_BLURLOW 0.166666666666667
float2 FILTERBLURDATALOW[NUM_BLURLOW]=
{
    {-0.326212f, -0.405805f},
    {-0.840144f, -0.07358f},
    {-0.695914f, 0.457137f},
    {-0.203345f, 0.620716f},
    {0.96234f,   -0.194983f},
    {0.473434f,  -0.480026f}
};

float4 HighlightGlowLowPS(pixelInput IN,
                uniform float       iHaloSize,
                uniform float4      iHaloColor,
                uniform samplerRECT iInputTexture
                ) : COLOR 
{
  float4 result = float4(1,0,0,1); 
    
  float4 screenCoord = IN.ScreenPosition;                  
  result = (texRECT(iInputTexture, screenCoord.xy));
   
	if (result.x != 0)
	{
		result.x = 0;
		for(int i=0; i<NUM_BLURLOW; i++)
		{
			float2 coord = screenCoord.xy + iHaloSize * FILTERBLURDATALOW[i];
			result.x += (texRECT(iInputTexture, coord).x);
		}

		result.x *= (INV_NUM_BLURLOW);
	}
	
  return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique SmoothTexture_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 HighlightGlowPS(haloSize, haloColor, Auto_EyeMap);
    }
}

technique SmoothTexture_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf HighlightGlowPS(haloSize, haloColor, Auto_EyeMap);
    }
}

technique SmoothTexture_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 HighlightGlowPS(haloSize, haloColor, Auto_EyeMap);
    }
}

technique SmoothTexture_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 HighlightGlowLowPS(haloSize, haloColor, Auto_EyeMap);
    }
}


