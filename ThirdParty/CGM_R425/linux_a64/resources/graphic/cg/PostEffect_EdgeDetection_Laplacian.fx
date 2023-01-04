//
// FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM FRAGMENT PROGRAM
//

#include "Effect_General.hfx"

//--------------------------------
// Tweakables
//--------------------------------

samplerRECT Auto_EyeMap
<
>;

float u_EdgeStrength
<
	float UIMin		= 0;
	float UIMax		= 2.f;
	float UIStep	= 0.01f;
> = float(1.f);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_EdgeDetection_Laplacian_PS(pixelInput IN,
                                         uniform samplerRECT iInputTexture,
                                         uniform float iEdgeStrength
                                         ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
  
	float4 pixCol = texRECT(iInputTexture,  screenCoord.xy);
	
  float4 col = texRECT(iInputTexture,  screenCoord.xy+float2(1,0));
	col += texRECT(iInputTexture,  screenCoord.xy+float2(-1,0));
	col += texRECT(iInputTexture,  screenCoord.xy+float2(0,1));
	col += texRECT(iInputTexture,  screenCoord.xy+float2(0,1));
	col -= 4*pixCol;
	
	col = saturate(1.f-col*iEdgeStrength)*pixCol;
	
	col.w = 1.f;
		
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_EdgeDetection_Laplacian_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40    Effect_EdgeDetection_Laplacian_PS(Auto_EyeMap, u_EdgeStrength);
    }
}

technique Effect_EdgeDetection_Laplacian_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf   Effect_EdgeDetection_Laplacian_PS(Auto_EyeMap, u_EdgeStrength);
    }
}

technique Effect_EdgeDetection_Laplacian_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30    Effect_EdgeDetection_Laplacian_PS(Auto_EyeMap, u_EdgeStrength);
    }
}

technique Effect_EdgeDetection_Laplacian_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_EdgeDetection_Laplacian_PS(Auto_EyeMap, u_EdgeStrength);
    }
}


