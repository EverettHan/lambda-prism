vec4 gv4_color;

void ComputeCommonValues()
{
  vec2 v2_texVal = v2_tex;
  if( ! vIsFrontFacing() )
    v2_texVal = v2_texBack;
  v2_texVal.x = clamp(v2_texVal.x, 0.0, 1.0);

  gv4_color = vec4(1.0);
  if( 1.0 == cb_cbSMAResultsData.ResultsDim || 5.0 == cb_cbSMAResultsData.ResultsDim )
    gv4_color = vTexture(ContourMap1D, vec2(v2_texVal.x,0.0) );
  else if( 2.0 == cb_cbSMAResultsData.ResultsDim || 6.0 == cb_cbSMAResultsData.ResultsDim )
    gv4_color = vTexture(ContourMap2D, v2_texVal);
  gv4_color.a *= f_alpha;
}

vec3 ComputeAlbedo()
{
  return gv4_color.rgb;
}

float ComputeOpacity()
{
  return gv4_color.a;
}

vec3 ComputeSpecularReflectance()
{
  return 0.04 * gv4_color.rgb;
}

//void ProcessFinalColor(inout vec3 finalColor)
//{
//#if 0
//  vec2 fCutFlags = vec2(0.0, 1.0); // Contour
//  if( cb_cbSMACutData.CutType > 0.0 )
//  {
//    if( f_clip < 0.0 )
//      fCutFlags = cb_cbSMACutData.CutFlags.rg;
//    else
//      fCutFlags = cb_cbSMACutData.CutFlags.ba;
//  }
//  if( fCutFlags.x == 0.0 && fCutFlags.y == 0.0 )
//    discard;
//#endif
//}
