float gf_Shift = 0.0;
float gf_MaxClip = 0.0;

void ComputeCommonValues()
{
  gf_Shift = fract( cb_cbSMATravelTime.TravelTimePos / cb_cbSMATravelTime.TravelTimeParam.x ) * cb_cbSMATravelTime.TravelTimeParam.x;
  // If gap is smaller than dash, need to reverse shift or it looks like stream is traveling backwards
  if( (cb_cbSMATravelTime.TravelTimeParam.x - cb_cbSMATravelTime.TravelTimeParam.y) > cb_cbSMATravelTime.TravelTimeParam.y )
    gf_Shift = -gf_Shift;

  if( 4.0 == cb_cbSMATravelTime.TravelTimeClip.z && cb_cbSMATravelTime.TravelTimeClip.y < 0.0 )
    gf_MaxClip = 3.402823466e+38; // FLT_MAX
  else
    gf_MaxClip = cb_cbSMATravelTime.TravelTimeClip.y;
}

vec3 ComputeAlbedo()
{
  return v4_color.rgb;
}

float ComputeOpacity()
{
  return v4_color.a;
}

vec3 ComputeSpecularReflectance()
{
  return 0.04 * v4_color.rgb;
}

bool ComputeDiscard()
{
  float fKeep = 1.0;
  if( 1.0 > cb_cbSMATravelTime.TravelTimeClip.z || 4.0 < cb_cbSMATravelTime.TravelTimeClip.z ||
      (f_clip >= cb_cbSMATravelTime.TravelTimeClip.x && f_clip <= gf_MaxClip) )
  {
    if( 0.0 <= cb_cbSMATravelTime.TravelTimePos )
    {
      if( cb_cbSMATravelTime.StreamAnimStyle == 1.0 || cb_cbSMATravelTime.StreamAnimStyle == 2.0 )
      {
        if( f_travelTime > cb_cbSMATravelTime.TravelTimePos )
          fKeep = 0.0;
      }
      if( cb_cbSMATravelTime.StreamAnimStyle == 0.0 || (cb_cbSMATravelTime.StreamAnimStyle == 2.0 && fKeep > 0.0) )
      {
        float fPos = fract( (f_travelTime-gf_Shift+cb_cbSMATravelTime.TravelTimeParam.x) / cb_cbSMATravelTime.TravelTimeParam.x ) * cb_cbSMATravelTime.TravelTimeParam.x;
        if( fPos < cb_cbSMATravelTime.TravelTimeParam.y )
          fKeep = 0.0;
      }
    }
  }
  else
    fKeep = 0.0;
  return (fKeep < 0.5);
}
