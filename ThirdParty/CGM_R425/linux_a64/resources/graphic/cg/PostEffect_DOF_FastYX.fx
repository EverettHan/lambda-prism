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

samplerRECT Auto_ZMap
<
>;

float4 Auto_Size
<
>;

float4 Auto_Focus
<
>;

float u_BlurQuality
<	
	float UIMin		= 0;
	float UIMax		= 100.f;
	float UIStep	= 1.f;
> = 5.f;

float u_BlurSize
<
	float UIMin		= 0;
	float UIMax		= 0.1f;
	float UIStep	= 0.001f;
> = 0.01f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------

float GetBlurRadius(float2 iPt)
{
  float focus = (Auto_Focus.y+1.f)*0.5f;
  float z = texRECT(Auto_ZMap, iPt).x;
  
  float radius = abs(z-focus)/(1.f-focus);
  
  return radius;
}
							  
float4 Effect_DOFY_PS(pixelInput IN) : COLOR 
{
  float2 screenCoord  = IN.texCoord.xy; 
  float4 col = float4(0,0,0,1.f);

  float blurRadius = GetBlurRadius(screenCoord.xy)*(u_BlurSize*Auto_Size.x);  
    
  screenCoord.y -= blurRadius;  
  
  float deltaRadius = blurRadius/u_BlurQuality;
  
  float num = 0;
  
  for (int i=-u_BlurQuality; i<=u_BlurQuality; i++)
  {
    float ratio = GetBlurRadius(screenCoord.xy)*(1.f+u_BlurQuality-abs((float)i))+0.01;  
     
    col += texRECT(Auto_EyeMap, screenCoord)*ratio; 
    num += ratio;
      
    screenCoord.y += deltaRadius;
  }  
  
  col *= 1.f/(float) num;
	col.w = 1;
		
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_DOFY_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_DOFY_PS();
    }
}

technique Effect_DOFY_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_DOFY_PS();
    }
}

technique Effect_DOFY_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_DOFY_PS();
    }
}

technique Effect_DOFY_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_DOFY_PS();
    }
}


