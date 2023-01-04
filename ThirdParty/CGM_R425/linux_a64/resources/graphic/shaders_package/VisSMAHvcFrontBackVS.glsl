
void ComputeVaryingValues()
{
  vec2 v2TexCoord = vec2(0.0);
  vec2 v2TexCoordBack = vec2(0.0);

    // Save texture coordinate for the result value
  float fDim = cb_cbSMAResultsData.ResultsDim;
  if( 0.0 != fDim )
  {
        v2TexCoord = vGetAttribTexCoord0().xy;
    v2TexCoord.x = v2TexCoord.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
    if( 4.0 <= fDim )
        v2TexCoord.x = fract(v2TexCoord.x);
    v2TexCoord.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(v2TexCoord.y, 0.0, 1.0);

    v2TexCoordBack = v2TexCoord;
    if( 0.0 < cb_cbSMAResultsData.FrontBack )
    {
      v2TexCoordBack = vGetAttribTexCoord1().xy;
      v2TexCoordBack.x = v2TexCoordBack.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
      if( 4.0 <= fDim )
        v2TexCoordBack.x = fract(v2TexCoordBack.x);
      v2TexCoordBack.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(v2TexCoordBack.y, 0.0, 1.0);
    }
  }

  v2_tex     = v2TexCoord;
  v2_texBack = v2TexCoordBack;
  f_alpha    = 1.0 - vGetAttribTexCoord2().x;
#if 0
  vec3 v3Pos = vGetAttribPosition();
  f_clip = cb_cbSMACutData.CutNormal.x * v3Pos.x + cb_cbSMACutData.CutNormal.y * v3Pos.y + cb_cbSMACutData.CutNormal.z * v3Pos.z - cb_cbSMACutData.CutParam;
#endif
}
