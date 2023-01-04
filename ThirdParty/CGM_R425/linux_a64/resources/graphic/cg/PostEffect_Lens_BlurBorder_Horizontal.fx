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

float4 Auto_Size
<
>;

float4 Auto_Position
<
>;

float u_Quality
<	
	float UIMin		= 0;
	float UIMax		= 20.f;
	float UIStep	= 1.f;
> = 5.f;


float u_Size
<
	float UIMin		= 0;
	float UIMax		= 0.2f;
	float UIStep	= 0.001f;
> = 0.1f;


//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
								  
float4 Effect_Lens_BlurBorderX_PS(pixelInput IN,
                                  uniform samplerRECT iInputTexture,
                                  uniform float4		iSize,
                                  uniform float4		iPos,
                                  uniform float		  iStepNum,
                                  uniform float		  iStepSize
                                  ) : COLOR 
{
  float2 screenCoord = IN.texCoord.xy;
    
  float2 pt = (screenCoord.xy+iPos.xy)*iSize.zw-0.5f;
  float ratio = dot(pt, pt);
  ratio *= ratio;
  ratio *= iStepSize*iSize.x/iStepNum;
    			
	int numStep = (int) iStepNum;	
  float4 col = float4(0,0,0,1.f);
  for (int i=-numStep; i<=numStep; i++)
  {
	  col += texRECT(iInputTexture,	screenCoord.xy+float2(i*ratio, 0));   
  }
    
  col *= (1.f/(numStep*2+1));
	col.w = 1;
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Lens_BlurBorderX__NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40    Effect_Lens_BlurBorderX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                     u_Quality, u_Size);
    }
}

technique Effect_Lens_BlurBorderX__GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf   Effect_Lens_BlurBorderX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                     u_Quality, u_Size);
    }
}

technique Effect_Lens_BlurBorderX__NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30    Effect_Lens_BlurBorderX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                     u_Quality, u_Size);
    }
}

technique Effect_Lens_BlurBorderX__ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1  Effect_Lens_BlurBorderX_PS(Auto_EyeMap, Auto_Size, Auto_Position, 
                                                                     u_Quality, u_Size);
    }
}


