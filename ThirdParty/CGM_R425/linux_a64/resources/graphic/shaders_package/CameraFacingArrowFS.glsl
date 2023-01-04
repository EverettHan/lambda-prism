


#ifdef TextureFontText

// Text value for alpha
float g_TextAlpha = 0.0;

#endif // ifdef TextureFontText

void ComputeCommonValues()
{ 

  basicComputeCommonValues();

#ifdef TextureFontText

  float alpha = vTexture(atlasTexture, vGetTexCoord0().xy).r;

#ifdef HighlightAdvanced
  g_TextAlpha = alpha;
#else
  g_TextAlpha = cb_cbVolMaterial.u_DiffuseColor.a * alpha; 
#endif

#endif // ifdef TextureFontText

}

bool ComputeDiscard()
{
#ifdef TextureFontText

  // Discard non-character pixels on the atlas background
  return (g_TextAlpha < 0.1);

#endif // ifdef TextureFontText
  return false;
  return basicComputeDiscard();
}

vec3 ComputeViewNormal()
{

#ifdef TextureFontText

  vec3 normal;

#ifdef NoViewProj
  // Make the normal compatible with highlight in ortho mode
  normal = vec3(0.0, 0.0, -1.0);
#else
  normal = vGetViewNormal();
#endif

  return normal;

#endif // ifdef TextureFontText

  return basicComputeViewNormal();
}

vec3 ComputeAlbedo()
{
#ifdef TextureFontText

  return cb_cbVolMaterial.u_DiffuseColor.rgb;

#endif // ifdef TextureFontText

  return basicComputeAlbedo();

}

vec3 ComputeSpecularReflectance()
{
#ifdef TextureFontText

  return vec3(0.0);

#endif // ifdef TextureFontText

  return basicComputeSpecularReflectance();
}

float ComputeOpacity()
{
#ifdef TextureFontText

  return g_TextAlpha;

#endif // ifdef TextureFontText

  return basicComputeOpacity();

}



