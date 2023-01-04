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

samplerRECT Auto_AmbientOcclusionMap = sampler_state
{
    minFilter = Linear;
    magFilter = Linear;
};

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------


float4 DownSampling2PS(pixelInput IN, uniform samplerRECT iBackBuffer) : COLOR 
{   
    float2 tc =  IN.ScreenPosition.xy * 2.0;	
    
    float4 color;
    
    float4 tap0 = f4texRECT(iBackBuffer, tc);
    float4 tap1 = f4texRECT(iBackBuffer, tc +  float2(  0.4,  0.9 ));
    float4 tap2 = f4texRECT(iBackBuffer, tc +  float2( -0.4, -0.9 ));
    float4 tap3 = f4texRECT(iBackBuffer, tc +  float2( -0.9,  0.4 ));
    float4 tap4 = f4texRECT(iBackBuffer, tc +  float2(  0.9, -0.4 ));
    color = 0.2 * ( tap0 + tap1 + tap2 + tap3 + tap4 );

    float4 tap11 = f4texRECT(iBackBuffer, tc +  float2(  0.9,  1.9 ));
    float4 tap21 = f4texRECT(iBackBuffer, tc +  float2( -0.9, -1.9 ));
    float4 tap31 = f4texRECT(iBackBuffer, tc +  float2( -1.9,  0.9 ));
    float4 tap41 = f4texRECT(iBackBuffer, tc +  float2(  1.9, -0.9 ));
    float4 color2 = 0.2 * ( tap0 + tap11 + tap21 + tap31 + tap41 );

    float mask = saturate(color2.w * 1);

    color = lerp(color2, color, mask);
    color.w = mask;

    return color;
}

float4 DownSamplingPS(pixelInput IN,
                uniform samplerRECT iBackBuffer
                ) : COLOR 
{   
    float4 coord =  IN.ScreenPosition * 2.0;	
    
    float4 coordTL = texRECT(iBackBuffer, coord.xy);
    float4 coordTR = texRECT(iBackBuffer, float2(coord.x + 1, coord.y));
    float4 coordBR = texRECT(iBackBuffer, float2(coord.x + 1, coord.y + 1));
    float4 coordBL = texRECT(iBackBuffer, float2(coord.x, coord.y + 1));
    
    float4 color = coordTL + coordTR + coordBR + coordBL;
    color *= 1./4.;
    return color;
}



//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique SmoothTexture_NV40
{
    pass p0 
    {
        FragmentProgram = compile fp40 DownSampling2PS(Auto_AmbientOcclusionMap);
    }
}

technique SmoothTexture_GLSL
{
    pass p0 
    {	
        FragmentProgram = compile glslf DownSampling2PS(Auto_AmbientOcclusionMap);
    }
}

technique SmoothTexture_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 DownSampling2PS(Auto_AmbientOcclusionMap);
    }
}

technique SmoothTexture_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 DownSampling2PS(Auto_AmbientOcclusionMap);
    }
}