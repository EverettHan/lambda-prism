//-------------------------------------------------------------------------------------------

void ComputeCommonValues()
{
  //-----------------
  // uv
  vec2 groundUV = vGroundUV*cb_Ground.u_GroundScaling.x;

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
  
  vec3 groundWorldTangent = vNormalize(vGroundWorldTangent);
  vec3 groundWorldBiNormal = vNormalize(vGroundWorldBiNormal);

  normal[0] = ApplyBumpToNormal(uv[0], s_NormalMap, cb_Ground_Physical.u_BumpScale*g_RadialFading, groundWorldNormal, groundWorldTangent, groundWorldBiNormal);
  normal[1] = ApplyBumpToNormal(uv[1], s_NormalMap, cb_Ground_Physical.u_BumpScale*g_RadialFading, groundWorldNormal, groundWorldTangent, groundWorldBiNormal);
  g_WorldNormal = vMix(normal[0], normal[1], ratio);

  
  //-----------------
  // roughness
  float roughness[2];
  roughness[0] = 1.0-vClamp(vTexture(s_RoughnessMap, uv[0]).x, 0.01, 1.0);
  roughness[1] = 1.0-vClamp(vTexture(s_RoughnessMap, uv[1]).x, 0.01, 1.0);
  g_Roughness = vMix(roughness[0], roughness[1], ratio);
  

  //-----------------
  // fresnel
  g_FresnelCoef =  cb_Ground_Physical.u_FresnelCoef;
  

  //-----------------
  // mirror
#if defined (GROUND_MIRRORING)
  g_MirrorDeviation = ComputeMirrorDeviationFromNormal(g_WorldNormal);
#endif
  

  //-----------------
  // Albedo
  g_AlbedoColor = vMix(vTexture(s_BaseColorMap, uv[0]).xyz, vTexture(s_BaseColorMap, uv[1]).xyz, ratio);
}


