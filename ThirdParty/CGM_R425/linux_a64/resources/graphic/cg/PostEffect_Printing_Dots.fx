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

float u_DotSizeInPixel
<	
  float UIMin		= 1.f;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = float(11.f);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
		
								  
float4 Effect_Dot_PS(pixelInput IN,
                     uniform samplerRECT iInputTexture,
                     uniform float4		iPos,
                     uniform float     iDotSizeInPixel
                     ) : COLOR 
{
  const float4 LUMINANCE=float4(0.3f, 0.6f, 0.1f, 0);
  
	int dotSize=(int)iDotSizeInPixel;	
  
	float radius = (float)dotSize*1.44f*0.5f;
	
  float2 screenCoord = IN.texCoord.xy;
  float2 pt = float2(
			screenCoord.x-((int)(screenCoord.x+iPos.z))%dotSize, 
			screenCoord.y-((int)(screenCoord.y+iPos.w))%dotSize);
    
        
  float luminance = 0;
  for (int i=0; i<dotSize; i++)
  {
		for (int j=0; j<dotSize; j++)
		{
			float4 tmpCol = texRECT(iInputTexture, pt.xy+float2(i,j));   
			luminance += dot(LUMINANCE, tmpCol);
		}
  }   
  luminance *= (1.f/(float)(dotSize*dotSize));
  luminance = 1 - luminance;
  luminance *= radius;
    
  float4 col = float4(1.f,1.f,1.f,1.f);

	pt = screenCoord.xy - pt.xy - float2(dotSize*0.5f, dotSize*0.5f);
    
	float lMax = luminance + 1.f;
	float lMin = luminance - 1.f;
	if (lMin<0) lMin = 0;
        
	float value = pt.x*pt.x+pt.y*pt.y;
	value = smoothstep(lMin*lMin, lMax*lMax, value+1);
	
	col = float4(value, value, value, 1.f);
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Dot_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_Dot_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}

technique Effect_Dot_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Dot_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}

technique Effect_Dot_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_Dot_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}

technique Effect_Dot_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_Dot_PS(Auto_EyeMap, Auto_Position, u_DotSizeInPixel);
    }
}


