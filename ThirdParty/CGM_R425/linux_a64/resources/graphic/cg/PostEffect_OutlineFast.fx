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

samplerRECT Auto_ZMap_WithTransparency
<
>;

samplerRECT Auto_NormalMap_WithTransparency
<
>;

float4 Auto_Size
<
>;


float u_NormalStrength
<	
	float UIMin = 0.0f;
	float UIMax = 100.0f;
	float UIStep = 0.1f;
> = 1.f;

float u_NormalStrength2
<	
	float UIMin = 0.0f;
	float UIMax = 100.0f;
	float UIStep = 0.1f;
> = 1.f;

float u_NormalMin
<	
	float UIMin = 0.0f;
	float UIMax = 1.0f;
	float UIStep = 0.01f;
> = 0.5f;

float u_NormalMax
<	
	float UIMin = 0.0f;
	float UIMax = 1.0f;
	float UIStep = 0.01f;
> = 1.0f;

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------
						  
float4 Effect_DOFX_PS(pixelInput IN) : COLOR 
{
  float2 screenCoord  = IN.texCoord.xy; 
  float4 col = texRECT(Auto_EyeMap, screenCoord); 
  float4 n = texRECT(Auto_NormalMap_WithTransparency, screenCoord); 
  n.xyz = 2*(n.xyz-0.5);
  float4 n1 = texRECT(Auto_NormalMap_WithTransparency, screenCoord+float2(1,0));   
  n1.xyz = 2*(n1.xyz-0.5);
  float4 n2 = texRECT(Auto_NormalMap_WithTransparency, screenCoord+float2(0,1)); 
  n2.xyz = 2*(n2.xyz-0.5);
  float4 n3 = texRECT(Auto_NormalMap_WithTransparency, screenCoord+float2(1,1)); 
  n3.xyz = 2*(n3.xyz-0.5);
 
  
  float ratio = (1.f-clamp(n.x*n1.x+n.y*n1.y+n.z*n1.z, 0, 1))*n1.w;
  float ratio2 = (1.f-clamp(n.x*n2.x+n.y*n2.y+n.z*n2.z, 0, 1))*n2.w;;
  float ratio3 = (1.f-clamp(n.x*n3.x+n.y*n3.y+n.z*n3.z, 0, 1))*n3.w;;
  if (ratio2 > ratio) ratio = ratio2;
  if (ratio3 > ratio) ratio = ratio3;

  ratio = u_NormalStrength2*(clamp(ratio*u_NormalStrength, u_NormalMin, u_NormalMax)-u_NormalMin);
    		
  return float4(0, 0, 0, ratio);
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------

technique Effect_DOFX_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 Effect_DOFX_PS();
    }
}

technique Effect_DOFX_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf Effect_DOFX_PS();
    }
}

technique Effect_DOFX_NV30
{
    pass p0 
    {		
        FragmentProgram = compile fp30 Effect_DOFX_PS();
    }
}

technique Effect_DOFX_ARB
{
    pass p0 
    {		
        FragmentProgram = compile arbfp1 Effect_DOFX_PS();
    }
}


