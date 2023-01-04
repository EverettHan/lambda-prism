
float ComputePointSize()
{
  return cb_cbSMAPointData.PointSpriteSize;
  // NRE gl_PointSize = vGetPointSize();
}

void ComputeVaryingValues()
{
#if 0 // ndef GLES2Platform
  vec4 v4Col = vGetAttribColor(); // gl_FrontColor; // vGetColor();
#else
  vec4 v4Col = vec4(1.0,1.0,1.0,1.0); // NRE
#endif

  float fDim = cb_cbSMAResultsData.ResultsDim;
  if( 0.0 != fDim )
  {
    // Get texture coordinate for the result value
    vec2 v2TexCoord = vGetAttribTexCoord2().xy;
    float fResX = v2TexCoord.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
    if( 4.0 > fDim )
      v2TexCoord.x = clamp(fResX, 0.0, 1.0);
    else
      v2TexCoord.x = fract(fResX);
    if( 1.0 == fDim || 5.0 == fDim )
    {
      v2TexCoord.y = 0.0;
      v4Col.rgb *= vTexture(ContourMap1D, v2TexCoord).rgb;
    }
    else //if( 2.0 == cb_cbSMAResultsData.ResultsDim )
    {
      v2TexCoord.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(v2TexCoord.y,0.0,1.0);
      v4Col.rgb *= vTexture(ContourMap2D, v2TexCoord).rgb;
    }
  }

  v4_color = v4Col * 0.9;

  v4_WorldViewPosition = vGetWorldViewMatrix() * vec4(vGetAttribPosition(), 1.0);

  // Convert the point sprite size from pixels to world-view space
  vec4 v4ProjectedPosition = vGetProjMatrix() * v4_WorldViewPosition;
  f_Size = cb_cbSMAPointData.PointSpriteSize / ((vGetProjMatrix()[0][0] / v4ProjectedPosition.w) * vGetViewportSize().x);
}
