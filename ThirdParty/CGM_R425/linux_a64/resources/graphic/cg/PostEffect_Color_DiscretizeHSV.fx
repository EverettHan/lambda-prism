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

float u_Saturation
<
	float UIMin		= 0;
	float UIMax		= 4.f;
	float UIStep	= 0.01f;
> = float(1.f);

float u_Value
<
	float UIMin		= 0;
	float UIMax		= 1.f;
	float UIStep	= 0.01f;
> = float(0.5f);

float u_Hue
<
	float UIMin		= 0;
	float UIMax		= 360;
	float UIStep	= 1.f;
> = float(0.f);

float u_NumSaturation
<
	float UIMin		= 0;
	float UIMax		= 255;
	float UIStep	= 1;
> = float(255);

float u_NumValue
<
	float UIMin		= 0;
	float UIMax		= 255;
	float UIStep	= 1;
> = float(14);

float u_NumHue
<
	float UIMin		= 0;
	float UIMax		= 255;
	float UIStep	= 1;
> = float(255);

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------		
									  
float4 Effect_Color_DiscretizeLuminance_PS(pixelInput IN,
                    uniform samplerRECT iInputTexture,
                    uniform float       iSaturation,
                    uniform float       iValue,
                    uniform float       iTeinte,
                    uniform float       iNumSaturation,
                    uniform float       iNumValue,
                    uniform float       iNumTone
                    ) : COLOR 
{
	float2 screenCoord = IN.texCoord.xy;
	float4 col = texRECT(iInputTexture, screenCoord);  
	
	float colMax= max(max(col.x, col.y), col.z);
	float colMin= min(min(col.x, col.y), col.z);
	
	float v = colMax;
	
	float s = 0;
	if (colMax!=0) s = 1.f-colMin/colMax;
	
	float t = 0;
	float delta = colMax-colMin;
	if (delta)
	{
	  if (colMax==col.x)
	  {
	    t = 60.f*(col.y-col.z)/delta+360.f;
	  }
	  else if (colMax==col.y)
	  {
	    t = 60.f*(col.z-col.x)/delta+120.f;
	  }
	  else if (colMax==col.z)
	  {
	    t = 60.f*(col.x-col.y)/delta+240.f;
	  }
	}
	t = fmod(t,360.f);
	
	s = saturate(s*iSaturation);
	v = (2-4*v)*(iValue*iValue)+(4*v-1)*iValue;
	t = fmod(t+iTeinte,360.f);
	
	// discretisation
	v = (int)(v*iNumValue);
	v *= 1.f/iNumValue;
	
	t = (int)(t*iNumTone/360.f);
	t *= 360.f/iNumTone;
	
	s = (int)(s*iNumSaturation);
	s *= 1.f/iNumSaturation;
	
	
	int ti = ((int)t/60) % 6;
	
	float f = t/60-ti;
	float l = v*(1-s);
	float m = v*(1-f*s);
	float n = v*(1-(1-f)*s);
	
	switch (ti)
	{
	  case 0:
	    col = float4(v,n,l,1.f);
	    break;
	    
	  case 1:
	    col = float4(m,v,l,1.f);
	    break;
	    
	  case 2:
	    col = float4(l,v,n,1.f);
	    break;
	    
	  case 3:
	    col = float4(l,m,v,1.f);
	    break;
	    
	  case 4:
	    col = float4(n,l,v,1.f);
	    break;
	    
	  case 5:
	    col = float4(v,l,m,1.f);
	    break;
	}
	
	return col;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_Color_DiscretizeLuminance_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_Color_DiscretizeLuminance_PS(Auto_EyeMap, u_Saturation, u_Value, u_Hue, u_NumSaturation, u_NumValue, u_NumHue);
    }
}

technique Effect_Color_DiscretizeLuminance_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_Color_DiscretizeLuminance_PS(Auto_EyeMap, u_Saturation, u_Value, u_Hue, u_NumSaturation, u_NumValue, u_NumHue);
    }
}

technique Effect_Color_DiscretizeLuminance_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_Color_DiscretizeLuminance_PS(Auto_EyeMap, u_Saturation, u_Value, u_Hue, u_NumSaturation, u_NumValue, u_NumHue);
    }
}

technique Effect_Color_DiscretizeLuminance_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_Color_DiscretizeLuminance_PS(Auto_EyeMap, u_Saturation, u_Value, u_Hue, u_NumSaturation, u_NumValue, u_NumHue);
    }
}


