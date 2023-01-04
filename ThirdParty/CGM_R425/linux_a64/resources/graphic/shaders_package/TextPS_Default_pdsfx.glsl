// Text value for alpha
float g_TextAlpha = 0.0;

void ComputeCommonValues()
{ 
  float alpha = vTexture(atlasTexture, vTexCoord.xy).r;

#ifdef HighlightAdvanced
  g_TextAlpha = alpha;
#else
  g_TextAlpha = cb_cbVolMaterial.u_DiffuseColor.a * alpha; 
#endif
}

bool ComputeDiscard()
{
  // Discard non-character pixels on the atlas background
  return (g_TextAlpha < 0.1);
}

vec3 ComputeViewNormal()
{
  vec3 normal;

#ifdef NoViewProj
  // Make the normal compatible with highlight in ortho mode
  normal = vec3(0.0, 0.0, -1.0);
#else
  normal = vGetViewNormal();
#endif

  return normal;
}

vec3 ComputeAlbedo()
{
  return cb_cbVolMaterial.u_DiffuseColor.rgb;
}

vec3 ComputeSpecularReflectance()
{
  return vec3(0.0);
}

float ComputeOpacity()
{
  return g_TextAlpha;
}
