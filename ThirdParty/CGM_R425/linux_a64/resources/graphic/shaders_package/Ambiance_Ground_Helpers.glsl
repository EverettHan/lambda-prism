float ComputeFading(const float iDistance, const float iMin, const float iMax)
{
  float fading = vClamp(iDistance, iMin, iMax);
  fading = (fading-iMin)/(iMax-iMin);
  fading = 1.0-fading;

#if defined(RADIUS_FADING_CUBIC) || defined (RADIUS_FADING_BICUBIC)
  fading *= fading;
#if defined(RADIUS_FADING_BICUBIC)
  fading *= fading;
#endif
#endif

  return fading;
}

vec2 ComputeMirrorDeviationFromNormal(const vec3 iWorldNormal)
{
  vec4 n1 = vGetViewMatrix() * vec4(iWorldNormal, 0.0);
  n1 = vNormalize(n1);
#ifdef UsePassThroughTransition
  vec4 n2 = _vPrivGetViewTransition() * cb_Ground_Matrix.u_GroundMatrix * vec4(0.0, 0.0, 1.0, 0.0);
#else
  vec4 n2 = cb_Ground_Matrix.u_GroundMatrix * vec4(0.0, 0.0, 1.0, 0.0);
#endif
  n2 = vNormalize(n2);

  vec2 deviation = (n1.xy - n2.xy)*0.2;
  return deviation;
}

vec2 TransformUV(const vec2 iUV, const mat4 iMatrix)
{
  vec4 uv = iMatrix*vec4(iUV, 0.0, 1.0);
  return uv.xy;
}

#if !defined(GLES2Platform) || !defined(VertexStage)

vec3 ApplyBumpToNormal(const vec2 iUV, const sampler2D iNormalMap, const float iBumpFactor, const vec3 iNormal, const vec3 iTangent, const vec3 iBiNormal)
{
  vec3 normal = vTexture(iNormalMap, iUV).xyz;  
  normal = 2.0*normal - 1.0;

  normal *= vec3(iBumpFactor, iBumpFactor, 1.0);
  normal = vNormalize(normal);

  normal = normal.x*iTangent + normal.y*iBiNormal + normal.z*iNormal;  

  return normal;
}

#endif
