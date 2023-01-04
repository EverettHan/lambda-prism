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
								  
float4 Effect_EdgeDetection_Laplacian2_PS(pixelInput IN,
                                 uniform samplerRECT iInputTexture,
                                 uniform float iEdgeStength
                                 ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
  
	float4 pixCol = texRECT(iInputTexture,  screenCoord.xy);
	
  float4 col = float4(0,0,0,0);
  col += texRECT(iInputTexture,  screenCoord.xy+float2( 1,-1));
	col += texRECT(iInputTexture,  screenCoord.xy+float2( 0,-1));
	col += texRECT(iInputTexture,  screenCoord.xy+float2(-1,-1));
	col += texRECT(iInputTexture,  screenCoord.xy+float2( 1, 0));
	col += texRECT(iInputTexture,  screenCoord.xy+float2(-1, 0));
	col += texRECT(iInputTexture,  screenCoord.xy+float2( 1, 1));
	col += texRECT(iInputTexture,  screenCoord.xy+float2( 0, 1));
	col += texRECT(iInputTexture,  screenCoord.xy+float2(-1, 1));
	col -= 8*pixCol;
	
	col = saturate(1.f-col*iEdgeStength)*pixCol;
	
	col.w = 1.f;
		
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_EdgeDetection_Laplacian2_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_EdgeDetection_Laplacian2_PS(Auto_EyeMap, u_EdgeStrength);
    }
}

technique Effect_EdgeDetection_Laplacian2_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_EdgeDetection_Laplacian2_PS(Auto_EyeMap, u_EdgeStrength);
    }
}

technique Effect_EdgeDetection_Laplacian2_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_EdgeDetection_Laplacian2_PS(Auto_EyeMap, u_EdgeStrength);
    }
}

technique Effect_EdgeDetection_Laplacian2_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_EdgeDetection_Laplacian2_PS(Auto_EyeMap, u_EdgeStrength);
    }
}


