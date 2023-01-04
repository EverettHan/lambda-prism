vec3 ComputeNormal()
{
  return vWorldNormal.xyz;
}

vec4 ComputeLighting(vec3 iWorldNormal)
{   
  vec4  mirrorCol   = vec4(0.0);
  float mirrorCoef  = 0.0;
  
#if defined (GROUND_MIRRORING) && defined (MIRROR_CATCHER)
  mirrorCol  = GetGroundMirrorColor();
  mirrorCoef = cb_Ground.u_MirrorCoef*mirrorCol.w;
#endif

  vec4  shadowCol = vec4(0.0);
  float shadowCoef = 0.0;
#if defined (GROUND_SHADOW) && defined (SHADOW_CATCHER)   
  shadowCol  = GetGroundShadow();
  shadowCoef = shadowCol.w;
#endif
  
#if defined(SO_HRTAO)
  shadowCoef = 1.0 - ((1.0 - shadowCoef) * GetGroundRTAORatio());
#endif
  vec4 col = vec4(0.0);

  col.w = 1.0 - (1.0 - shadowCoef)*(1.0 - mirrorCoef);
  col.xyz = shadowCol.xyz;

  if (col.w > 0.0)
  {
    col.xyz = (mirrorCol.xyz * (1.0 - shadowCoef) * mirrorCoef /*+ shadowCoef * shadowCol.xyz*/) / col.w;
  }

  col.w *= cb_Ground.u_GroundColor.w;
  
#ifdef OutputIBLReflMap
  FRAGREFLECT = vec4(vec3(1.0), cb_Ground.u_MirrorCoef);
#endif

  return col;
}
