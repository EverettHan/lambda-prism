
vec3 ComputeObjectPosition()
{
  return vGetAttribPosition();
}

void ComputeVaryingValues()
{
  vec2 v2TexCoord = vec2(0.0);

  // Save texture coordinate for the result value
  float fDim = cb_cbSMAMpaFrontBackTranslucent.HasTexture;
  if( 0.0 != fDim )
    v2TexCoord = vGetAttribTexCoord0().xy;

  v2_Tex = v2TexCoord;
}
