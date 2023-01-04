

void ComputeVaryingValues()
{
  float fAlpha = 1.0 - vGetAttribTexCoord2().x;
  vec4 v4Col = vec4(1.0, 1.0, 1.0, fAlpha); // NRE

  // Save texture coordinate for the result value
  float fDim = cb_cbSMAResultsData.ResultsDim;
  if( 0.0 != fDim ) // && (v4Col.r==v4Col.g && v4Col.g==v4Col.b) ) // Ignore texture if base color is not shade of gray
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
  }

  float fTime=-1.0;
  if( 0.0 <= cb_cbSMATravelTime.TravelTimePos )
    fTime = vGetAttribTexCoord1().x;

  float fClip = 0.0;
  switch( int(cb_cbSMATravelTime.TravelTimeClip.z) )
  {
  case 1: fClip = vGetAttribPosition().x; break;
  case 2: fClip = vGetAttribPosition().y; break;
  case 3: fClip = vGetAttribPosition().z; break;
  case 4: fClip = vGetAttribTexCoord1().x; break;
  }

  v4_color = v4Col;
  f_travelTime = fTime;
  f_clip = fClip;
}
