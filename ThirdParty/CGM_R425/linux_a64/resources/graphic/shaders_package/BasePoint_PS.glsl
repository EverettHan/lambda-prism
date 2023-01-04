
// Texel value
vec4 texelValue;

void ComputeCommonValues()
{
#ifdef MarkerTexture
  vec2 texCoord = vec2(vGetPointCoord().x, 1.0 - vGetPointCoord().y);
  texelValue = vTexture(markerTexture, texCoord, 0.);
#endif
}

vec3 ComputeAlbedo()
{
#ifdef VertexColor
  return vColor.xyz;
#else
  return cb_cbVolMaterial.u_DiffuseColor.rgb;
#endif // VertexColor
}

float ComputeOpacity()
{
  return cb_cbVolMaterial.u_DiffuseColor.a;
}

bool ComputeDiscard()
{  
#ifdef MarkerTexture
  return (texelValue.a < 0.5);
#else
  return false;
#endif
}

#ifdef CUSTOM_COVERAGE
void PerformCustomCoverage()
{
}
#endif


vec3 ComputeViewNormal()
{
  vec3 normal;

#ifdef NoNormal
  // Make the normal compatible with highlight in ortho mode
  normal = vec3(0.0, 0.0, 1.0);
#else
  normal = vGetViewNormal();
#endif

  return normal;
}
