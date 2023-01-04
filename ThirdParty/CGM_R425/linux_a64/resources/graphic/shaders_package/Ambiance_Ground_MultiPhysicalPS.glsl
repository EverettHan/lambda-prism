//-------------------------------------------------------------------------------------------

void ComputeCommonValues()
{
  //-----------------
  // uv
  vec2 groundUV = vGroundUV.xy*cb_Ground.u_GroundScaling.x;

  vec2 uv[2];
  uv[0] =  TransformUV(groundUV, cb_Ground_Physical.u_Matrix1_UVTransfo);
  uv[1] =  TransformUV(groundUV, cb_Ground_Physical.u_Matrix2_UVTransfo);

  //-----------------
  // ratio
  float ratio  = vTexture(s_MaterialMap, TransformUV(groundUV, cb_Ground_Physical.u_MainMatrix_UVTransfo)).r;

  //-----------------
  // fadding
  float distance = vLength(vGroundUV);
  g_RadialFading = ComputeFading(distance, cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);

  
  //-----------------
  // normal
  vec3 normal[2];
  
  vec3 groundWorldNormal = vNormalize(vGroundWorldNormal);
  
#if defined(NORMAL_MAP1) || defined (NORMAL_MAP2)
  vec3 groundWorldTangent = vNormalize(vGroundWorldTangent);
  vec3 groundWorldBiNormal = vNormalize(vGroundWorldBiNormal);
#endif

#ifdef NORMAL_MAP1
  normal[0] = ApplyBumpToNormal(uv[0], s_NormalMap1, cb_Ground_Physical.u_BumpScale1*g_RadialFading, groundWorldNormal, groundWorldTangent, groundWorldBiNormal);
#else
  normal[0] = groundWorldNormal;
#endif

#ifdef NORMAL_MAP2
  normal[1] = ApplyBumpToNormal(uv[1], s_NormalMap2, cb_Ground_Physical.u_BumpScale2*g_RadialFading, groundWorldNormal, groundWorldTangent, groundWorldBiNormal);
#else
  normal[1] = groundWorldNormal;
#endif

  g_WorldNormal = vMix(normal[0], normal[1], ratio);

  
  //-----------------
  // roughness
  float roughness[2];

#ifdef ROUGHNESS_MAP1
  roughness[0] = 1.0-vClamp(vTexture(s_RoughnessMap1, uv[0]).x, 0.01, 1.0);
#else
  roughness[0] = cb_Ground_Physical.u_Roughness1;
#endif

#ifdef ROUGHNESS_MAP2
  roughness[1] = 1.0-vClamp(vTexture(s_RoughnessMap2, uv[1]).x, 0.01, 1.0);
#else
  roughness[1] = cb_Ground_Physical.u_Roughness2;
#endif

  g_Roughness = vMix(roughness[0], roughness[1], ratio);
  
  
  //-----------------
  // fresnel
  g_FresnelCoef =   vMix(cb_Ground_Physical.u_FresnelCoef1, cb_Ground_Physical.u_FresnelCoef2, ratio);
  
  
  //-----------------
  // mirror
#if defined (GROUND_MIRRORING)
#if defined(NORMAL_MAP1) || defined (NORMAL_MAP2)
  g_MirrorDeviation = ComputeMirrorDeviationFromNormal(g_WorldNormal);
#endif
#endif
  

  //-----------------
  // Albedo
  vec3 col[2];

#ifdef BASECOLOR_MAP1
  col[0] = vTexture(s_BaseColorMap1, uv[0]).xyz;
#else 
  col[0] = vec3(1);
#endif

#ifdef BASECOLOR_MAP2
  col[1] = vTexture(s_BaseColorMap2, uv[1]).xyz;
#else
  col[1] = vec3(1);
#endif

  g_AlbedoColor = vMix(col[0], col[1], ratio);
}



