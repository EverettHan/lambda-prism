//-------------------------------------------------------------------------------------------

void ComputeCommonValues()
{

  //-----------------
  // uv
  vec2 groundUV = vGroundUV.xy*cb_Ground.u_GroundScaling.x;

  vec2 uv =  TransformUV(groundUV, cb_Ground_Physical.u_Matrix_UVTransfo); 
  

  //-----------------
  // fadding
  float distance = vLength(vGroundUV.xy);
  g_RadialFading = ComputeFading(distance, cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);
  

  //-----------------
  // normal
  vec3 groundWorldNormal = vNormalize(vGroundWorldNormal);

#ifdef NORMAL_MAP 
  vec3 groundWorldTangent  = vNormalize(vGroundWorldTangent);
  vec3 groundWorldBiNormal = vNormalize(vGroundWorldBiNormal);

  g_WorldNormal = ApplyBumpToNormal(uv, s_NormalMap, cb_Ground_Physical.u_BumpScale*g_RadialFading, groundWorldNormal, groundWorldTangent, groundWorldBiNormal);
#else
  g_WorldNormal = groundWorldNormal;
#endif

  
  //-----------------
  // roughness
  g_Roughness = cb_Ground_Physical.u_Roughness;
#ifdef ROUGHNESS_MAP
  g_Roughness = 1.0-vClamp(vTexture(s_RoughnessMap, uv).x, 0.01, 1.0);
#endif
  

  //-----------------
  // fresnel
  g_FresnelCoef =  cb_Ground_Physical.u_FresnelCoef;
  

  //-----------------
  // mirror 
#if defined(NORMAL_MAP) && defined (GROUND_MIRRORING)
  g_MirrorDeviation = ComputeMirrorDeviationFromNormal(g_WorldNormal);
#endif
  

  //-----------------
  // Albedo
#ifdef BASECOLOR_MAP
 g_AlbedoColor = vTexture(s_BaseColorMap, uv).xyz;
#else 
 g_AlbedoColor = vec3(1);
#endif
}



