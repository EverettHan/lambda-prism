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

float4 outlineColor
<
> = float4(0,1,0,1);

float4 haloColor
<
> = float4(0,0,1,1);

float haloIntensity
<
> = 1;

float haloSize
<
> = 3;

float4 scanEffectColor
<
> = float4(0,0,1,1);

float scanEffectIntensity
<
> = 1;

samplerRECT Auto_EyeMap
<
>;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float4 ScanEffectAndOutline(
				        float4		  iColor,
				        float4		  iScreenCoord,
                float4      iOutlineColor,
                float       iScanEffectIntensity,
                float4      iScanEffectColor,
                samplerRECT iInputTexture)
{
	float4 result = iColor;
	float red = 0;
	float4 screenCoord = iScreenCoord;
	
	screenCoord.y -= 1;
	red += (texRECT(iInputTexture, screenCoord.xy)).x;
	screenCoord.y += 2;
	red += (texRECT(iInputTexture, screenCoord.xy)).x;
	screenCoord.y -= 1;
	screenCoord.x -= 1;
	red += (texRECT(iInputTexture, screenCoord.xy)).x;
	screenCoord.x += 2;
	red += (texRECT(iInputTexture, screenCoord.xy)).x;
		
	// outline interne
	if (red!=0)
	{
		result = iOutlineColor;
	}
	// effect scan
	else
	{
		red = (1-result.y);
		red *= red;
		
		result = float4(
		          iScanEffectColor.xyz, 
		          (0.6f*red+0.2f)*iScanEffectIntensity);
	}
	
	return result;
}

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

float4 AdvancedHighlightPS(pixelInput IN,
                uniform float4      iOutlineColor,
                uniform float       iHaloSize,
                uniform float       iHaloIntensity,
                uniform float4      iHaloColor,
                uniform float       iScanEffectIntensity,
                uniform float4      iScanEffectColor,
                uniform samplerRECT iInputTexture
                ) : COLOR 
{
  float4 result = float4(0,0,0,0); 
    
  float4 screenCoord = IN.ScreenPosition;                  
  result += (texRECT(iInputTexture, screenCoord.xy));
 
    
  // cas du halo
	if (result.x != 0)
	{
    result   = iHaloColor;
    
		result.w = 0;
		for(int i=0; i<NUM_BLUR; i++)
		{
			float2 coord = screenCoord.xy + iHaloSize * FILTERBLURDATA[i];
			result.w += (texRECT(iInputTexture, coord)).x;
		}
		result.w = (1-result.w*INV_NUM_BLUR)*iHaloIntensity;
	}
	// object en higlight
	else
	{
		result = ScanEffectAndOutline(result, screenCoord, 
									  iOutlineColor, 
									  iScanEffectIntensity, iScanEffectColor,
									  iInputTexture);
	}
	
    return result;
}

// dans le cas ARB, on fait un smoothing moins precis, car sinon le
// shader genere depasse le nombre d'instruction supportees
// par certaines cartes

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


float4 AdvancedHighlightLowPS(pixelInput IN,
                uniform float4      iOutlineColor,
                uniform float       iHaloSize,
                uniform float       iHaloIntensity,
                uniform float4      iHaloColor,
                uniform float       iScanEffectIntensity,
                uniform float4      iScanEffectColor,
                uniform samplerRECT iInputTexture
                ) : COLOR 
{
  float4 result = float4(0,0,0,0); 
    
  float4 screenCoord = IN.ScreenPosition;                  
  result += (texRECT(iInputTexture, screenCoord.xy));
    
  // cas du halo
  if (result.x != 0)
	{
    result   = iHaloColor;
    
		result.w = 0;
		for(int i=0; i<NUM_BLURLOW; i++)
		{
			float2 coord = screenCoord.xy + iHaloSize * FILTERBLURDATALOW[i];
			result.w += (texRECT(iInputTexture, coord)).x;
		}
		result.w = (1-result.w*INV_NUM_BLURLOW)*iHaloIntensity;
	}
	// object en higlight
	else
	{
		result = ScanEffectAndOutline(result, screenCoord, 
									  iOutlineColor, 
									  iScanEffectIntensity, iScanEffectColor,
									  iInputTexture);
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
        FragmentProgram = compile fp40 AdvancedHighlightPS(outlineColor, 
														   haloSize, haloIntensity, haloColor,
														   scanEffectIntensity, scanEffectColor,
														   Auto_EyeMap);
    }
}

technique SmoothTexture_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf AdvancedHighlightPS(outlineColor, 
														   haloSize, haloIntensity, haloColor,
														   scanEffectIntensity, scanEffectColor,
														   Auto_EyeMap);
    }
}

technique SmoothTexture_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 AdvancedHighlightPS(outlineColor, 
														   haloSize, haloIntensity, haloColor,
														   scanEffectIntensity, scanEffectColor,
														   Auto_EyeMap);
    }
}

technique SmoothTexture_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 AdvancedHighlightLowPS(outlineColor, 
														   haloSize, haloIntensity, haloColor,
														   scanEffectIntensity, scanEffectColor,
														   Auto_EyeMap);
    }
}


