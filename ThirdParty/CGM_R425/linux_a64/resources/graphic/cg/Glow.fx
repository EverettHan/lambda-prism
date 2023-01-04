//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
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

float effectSize
<
    float uimin = 0;
    float uimax = 100;
> = 4;

float effectStrenght
<
    float uimin = 0;
    float uimax = 4;
> = 1;

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

float4 SmoothPS(pixelInput IN,
                uniform float       iEffectSize,
                uniform float       iEffectStrenght,
                uniform samplerRECT iSmoothTexture
                ) : COLOR 
{
    float4 result = float4(0,0,0,0); 
    float4 screenCoord = IN.ScreenPosition;
    
    float2 coord =  screenCoord.xy;
	
    result.w = texRECT(iSmoothTexture, coord).w;
   
    for(int i=0; i<NUM_BLUR; i++)
    {
        coord = screenCoord.xy + iEffectSize * FILTERBLURDATA[i].xy;
        result.xyz += (texRECT(iSmoothTexture, coord)).xyzw; 
    }
    result.xyz *= INV_NUM_BLUR*iEffectStrenght;
     
    return result;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique SmoothTexture_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 SmoothPS(effectSize, effectStrenght, Auto_EyeMap);
    }
}

technique SmoothTexture_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf SmoothPS(effectSize, effectStrenght, Auto_EyeMap);
    }
}

technique SmoothTexture_NV30
{
    pass p0 
    {		

        FragmentProgram = compile fp30 SmoothPS(effectSize, effectStrenght, Auto_EyeMap);
    }
}

technique SmoothTexture_ARB
{
    pass p0 
    {		

        FragmentProgram = compile arbfp1 SmoothPS(effectSize, effectStrenght, Auto_EyeMap);
    }
}


