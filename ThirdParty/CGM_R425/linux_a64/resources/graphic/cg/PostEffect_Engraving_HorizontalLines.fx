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

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
									  
float4 Effect_Line_PS(pixelInput IN,
                      uniform samplerRECT iInputTexture,
                      uniform float4		  iPos,
                      uniform float       iLineSizeInPixel
                      ) : COLOR 
{
  const float4 LUMINANCE=float4(0.3f, 0.6f, 0.1f, 0);
  
	int lineSize=(int)iLineSizeInPixel;		
	
  float2 screenCoord = IN.texCoord.xy;
    
  float2 ptLocal = float2(0, ((int)(screenCoord.y+iPos.w))%lineSize);
  float2 pt = screenCoord - ptLocal;
    
	float4 col = float4(1.f,1.f,1.f,1.f);  
    
  float luminance = 0;
	for (int j=0; j<lineSize; j++)
	{
		float4 tmpCol = texRECT(iInputTexture, pt.xy+float2(0,j));   
		luminance += dot(LUMINANCE, tmpCol);
	}
  luminance *= (1.f/(float)(lineSize));
  luminance = 1 - luminance;
  luminance *= lineSize;
	
	float lMax = luminance + 1.f;
	float lMin = luminance - 1.f;
				
	float r = smoothstep(lMin, lMax, ptLocal.y*0.8f+2.f);
  col = float4(r,r,r,1.f);
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Line_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_Line_PS(Auto_EyeMap, Auto_Position, u_LineSizeInPixel);
    }
}

technique Effect_Line_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Line_PS(Auto_EyeMap, Auto_Position, u_LineSizeInPixel);
    }
}

technique Effect_Line_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_Line_PS(Auto_EyeMap, Auto_Position, u_LineSizeInPixel);
    }
}

technique Effect_Line_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_Line_PS(Auto_EyeMap, Auto_Position, u_LineSizeInPixel);
    }
}


