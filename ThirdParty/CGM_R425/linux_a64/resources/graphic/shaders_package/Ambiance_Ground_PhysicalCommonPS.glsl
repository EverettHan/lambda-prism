//-------------------------------------------------------------------------------------------
// Mirror
#if defined (GROUND_MIRRORING)
#ifndef GLES2Platform
in vec2 vMirrorTexCoord;
#else
varying vec2 vMirrorTexCoord;
#endif
#endif


//-------------------------------------------------------------------------------------------
// Methode non surchargee

vec3 ComputeEmissive()
{
  return vec3(0.0); 
}

vec3 ComputeSpecularColor()
{
  return vec3(1.0, 1.0, 1.0);
}

void PerformClipping()
{
  if(cb_Ground.u_GroundColor.a == 0.f)
    discard;
}

//-------------------------------------------------------------------------------------------
// Code commun

float g_RadialFading = 1.0;
vec3  g_WorldNormal   = vec3(0.0,0.0,1.0);
float g_Roughness     = 1.0;
vec3  g_FresnelCoef   = vec3(0,0,0);
#ifdef GROUND_MIRRORING
vec2  g_MirrorDeviation = vec2(0,0);
#endif
vec3  g_AlbedoColor   = vec3(0,0,0);

float ComputeAlpha()
{  
  float alpha = cb_Ground.u_GroundColor.w;
  
  alpha *= g_RadialFading; 
  
  return alpha;
}

vec3 ComputeWorldNormal()
{ 
  return g_WorldNormal;
}

vec3 ComputeAlbedo()
{
  return g_AlbedoColor*cb_Ground.u_GroundColor.xyz;
}

void ProcessBRDFParameters(inout BRDFParameters oParameters)
{ 
  oParameters.roughness = g_Roughness;
  oParameters.f0        = g_FresnelCoef;
}

void ProcessFinalColor(inout vec3 finalColor)
{
  //---------------------
  // Shadow  
  
#if defined(GROUND_SHADOW) 
  finalColor = ApplyGroundShadow(finalColor);
#endif 


  //---------------------
  // Mirroring

#if defined (GROUND_MIRRORING)
  ivec2 tsize = vTextureSize(mirrorMapTex, 0);
  
  vec2 texCoord = vec2(gl_FragCoord.x/tsize.x, gl_FragCoord.y/tsize.y);
  texCoord += vMirrorTexCoord;
  texCoord += g_MirrorDeviation;

  vec3 mirrorColor = vTexture(mirrorMapTex, texCoord.xy).xyz;

  finalColor = vMix(finalColor, mirrorColor, cb_Ground.u_MirrorCoef*(1.0-vClamp(g_Roughness*1.4,0.0,1.0)));
#endif
}
