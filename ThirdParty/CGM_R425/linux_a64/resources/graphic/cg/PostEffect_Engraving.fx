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

float4 Auto_Position
<
>;

float u_LineSizeInPixel
<	
  float UIMin		= 1.f;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = float(11.f);

float u_EdgeStrength
<
	float UIMin		= 0;
	float UIMax		= 2.f;
	float UIStep	= 0.01f;
> = float(1.f);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
									  
float4 Effect_Gravure_PS(pixelInput IN,
                    uniform samplerRECT iInputTexture,
                    uniform float4		  iPos,
                    uniform float       iLineSizeInPixel,
                    uniform float       iEdgeStrength
                    ) : COLOR 
{
  const float4 LUMINANCE=float4(0.3f, 0.6f, 0.1f, 0);
  
	int lineSize=(int)iLineSizeInPixel;		
	float invLineSize=1.f/iLineSizeInPixel;		
	
	float2 screenCoord = IN.texCoord.xy;
   
  // Line Effect
    
  float2 ptLocal = float2(0, ((int)(screenCoord.y+iPos.w))%lineSize);
  float2 pt = screenCoord - ptLocal;
    
	float4 col = float4(1.f,1.f,1.f,1.f);  
    
  float luminance = 0;
	for (int j=0; j<lineSize; j++)
	{
		float4 tmpCol = texRECT(iInputTexture, pt.xy+float2(0,j));   
		luminance += dot(tmpCol, LUMINANCE);
	}
  luminance *= invLineSize;
  luminance = 1 - luminance;
  luminance *= lineSize;
	
	float lMax = luminance + 1.f;
	float lMin = luminance - 1.f;
				
	float r = smoothstep(lMin, lMax, ptLocal.y*0.6f+1.5f);
  col = float4(r,r,r,1.f);
    
  // Edge Effect  
    
	float4 pixCol = texRECT(iInputTexture,  screenCoord.xy);
	
  float4 colOutline = float4(0,0,0,0);
  colOutline += texRECT(iInputTexture,  screenCoord.xy+float2( 1,-1));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2( 0,-1));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2(-1,-1));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2( 1, 0));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2(-1, 0));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2( 1, 1));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2( 0, 1));
	colOutline += texRECT(iInputTexture,  screenCoord.xy+float2(-1, 1));
	colOutline -= 8*pixCol;
		
  luminance = dot(colOutline, LUMINANCE);
  colOutline = float4(luminance, luminance, luminance, 1.f);
		
	col= saturate(1.f-colOutline*iEdgeStrength)*col;
	col.w = 1.f;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Gravure_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_Gravure_PS(Auto_EyeMap, Auto_Position, 
                                                         u_LineSizeInPixel, u_EdgeStrength);
    }
}

technique Effect_Gravure_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Gravure_PS(Auto_EyeMap, Auto_Position, 
                                                         u_LineSizeInPixel, u_EdgeStrength);
    }
}

technique Effect_Gravure_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_Gravure_PS(Auto_EyeMap, Auto_Position, 
                                                         u_LineSizeInPixel, u_EdgeStrength);
    }
}

technique Effect_Gravure_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_Gravure_PS(Auto_EyeMap, Auto_Position, 
                                                         u_LineSizeInPixel, u_EdgeStrength);
    }
}


