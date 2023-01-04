//#define CONFIG_1
//#define CONFIG_2
#define CONFIG_3

vec3 gasComputeAlbedo()
{
#ifdef VertexColor
  return vColor.rgb;
#else
  #ifdef GlobalGASColor
    return vGetGlobalGASColor().rgb;
  #else
    return cb_cbVolMaterial.u_DiffuseColor.rgb;
  #endif
#endif
}

float gasComputeOpacity()
{
  #ifdef GlobalGASColor
    return vGetGlobalGASColor().w;
  #else
    return cb_cbVolMaterial.u_AmbientColor.w;
  #endif
}

vec3 gasComputeSpecularReflectance()
{
  #ifdef CONFIG_1
    return vec3(0.1);
  #endif
  #ifdef CONFIG_2
    return vec3(0.1);
  #endif
  #ifdef CONFIG_3
    return vec3(0.05) * cb_cbVolMaterial.u_SpecularColor.rgb;
  #endif
}

vec3 gasComputeViewNormal()
{ 
  vec3 vNormal;

  #ifdef NoNormal
    vec3 U = dFdx(vGetViewPosition());                     
    vec3 V = dFdy(vGetViewPosition());                 
    vec3 N = normalize(cross(U,V));
    vNormal = N;
    //vNormal = vNormalize(vec3(1,1,1));
  #else
    vNormal = vGetViewNormal();
  #endif

  vec3 bumpNorm;

  #ifdef CONFIG_3
    bumpNorm = texture(NoiseVolumeTextureMap, noiseCoords*0.5).xxx*0.04;
  #else
    bumpNorm = (texture(NoiseVolumeTextureMap, noiseCoords*0.13f).xxx + texture(NoiseVolumeTextureMap, noiseCoords*0.06f).xxx)*0.12f;
  #endif

  bumpNorm = (vGetViewMatrix() * vec4(bumpNorm, 0.0)).xyz;

  vNormal += bumpNorm;
  vNormal = normalize(vNormal);

  return vNormal;
}

float gasComputeRoughness()
{
  #ifdef CONFIG_1
    return 0.5;
  #endif

  #ifdef CONFIG_2
    return 0.45;
  #endif

  #ifdef CONFIG_3
    return 0.3;
  #endif
}

#ifndef PDSFX1_FS_Albedo_GASLook0
vec3 ComputeAlbedo()
{
  return gasComputeAlbedo();
}
#endif

#ifndef PDSFX1_FS_Opacity_GASLook0
float ComputeOpacity()
{
  return gasComputeOpacity();
}
#endif

#ifndef PDSFX1_FS_F0_GASLook0
vec3 ComputeSpecularReflectance()
{
  return gasComputeSpecularReflectance();
}
#endif

#ifndef PDSFX1_FS_Roughness_GASLook0
float ComputeRoughness()
{
  return gasComputeRoughness();
}
#endif

#ifndef PDSFX1_FS_Normal_GASLook0
vec3 ComputeViewNormal()
{
  return gasComputeViewNormal();
}
#endif

