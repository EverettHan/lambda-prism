
void ComputeVaryingValues()
{
  float fAlpha = 1.0 - vGetAttribTexCoord2().x;
  vec4 v4Col = vGetAttribColor(); // This fails unless color-per-vertex is passed (not texture per vertex).
  v4Col.a = fAlpha;

  float fTime = -1.0;
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
