
void ComputeVaryingValues()
{
  float fAlpha = 1.0 - vGetAttribTexCoord2().x;
#if 0 //ndef GLES2Platform
  vec4 v4Col = vGetAttribColor();
  vec4 v4ColBack = vGetAttribColor();
  v4Col.a = fAlpha;
  v4ColBack.a = fAlpha;
#else
  vec4 v4Col = vec4(1.0,1.0,1.0,fAlpha); // NRE
  vec4 v4ColBack = vec4(1.0,1.0,1.0,fAlpha); // NRE
#endif

  // Save texture coordinate for the result value
  float fDim = cb_cbSMAResultsData.ResultsDim;
  if( 0.0 != fDim )
  {
    vec2 v2TexCoord = vGetAttribTexCoord0().xy;
    float fResX = v2TexCoord.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
    if( 4.0 > fDim )
      v2TexCoord.x = clamp(fResX, 0.0, 1.0);
    else
        v2TexCoord.x = fract(fResX);
    if( 1.0 == fDim || 5.0 == fDim )
      v4Col *= vTexture(ContourMap1D, vec2(v2TexCoord.x,0.0) );
    else //if( 2.0 == fDim || 6.0 == fDim )
    {
        v2TexCoord.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(v2TexCoord.y, 0.0, 1.0);
      v4Col *= vTexture(ContourMap2D, v2TexCoord);
    }

    if( 0.0 == cb_cbSMAResultsData.FrontBack )
      v4ColBack = v4Col;
    else
    {
      v2TexCoord = vGetAttribTexCoord1().xy;
      fResX = v2TexCoord.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
      if( 4.0 > fDim )
        v2TexCoord.x = clamp(fResX, 0.0, 1.0);
      else
        v2TexCoord.x = fract(fResX);
      if( 1.0 == fDim || 5.0 == fDim )
        v4ColBack *= vTexture(ContourMap1D, vec2(v2TexCoord.x,0.0));
      else //if( 2.0 == fDim || 6.0 == fDim )
      {
        v2TexCoord.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(v2TexCoord.y, 0.0, 1.0);
        v4ColBack *= vTexture(ContourMap2D, v2TexCoord);
      }
    }
  }

  v4_color = v4Col;
  v4_colorBack = v4ColBack;
}
