bool ComputeDiscard()
{
  vec2 n = vGetPointCoord() * 2.0 - 1.0;

  if(cb_cbSMAPointData.PointSymbol == 1.0 )    //CROSS
  {
    if( (abs(n.x - n.y) >= cb_cbSMAPointData.PointLineWidth)  &&  (abs(n.x + n.y) >= cb_cbSMAPointData.PointLineWidth) )
      return true;
  }
  else if(cb_cbSMAPointData.PointSymbol == 2.0)  //PLUS    
  {
    if( (abs(n.x) >= cb_cbSMAPointData.PointLineWidth)  &&  (abs(n.y) >= cb_cbSMAPointData.PointLineWidth) )
      return true;
  }
  else if(cb_cbSMAPointData.PointSymbol == 3.0)  //CONCENTRIC
  {
    if( abs(dot(n, n) - 0.7) >= 0.35 )
      return true;
  }
  else if(cb_cbSMAPointData.PointSymbol == 4.0)  //COINCIDENT
  {
    float fMag = dot(n, n);
    if( (abs(fMag - 0.75) >= cb_cbSMAPointData.PointLineWidth)  &&  (abs(fMag - 0.2) >= 0.10))
      return true;
  }
  else if(cb_cbSMAPointData.PointSymbol == 7.0)  //STAR
  {
    if( (abs(n.x - n.y) >= cb_cbSMAPointData.PointLineWidth) &&
        (abs(n.x + n.y) >= cb_cbSMAPointData.PointLineWidth) &&
        (abs(n.x) >= 0.18) && (abs(n.y) >= 0.18) )
      return true;
  }
  else if(cb_cbSMAPointData.PointSymbol == 10.0)  //FULLCIRCLE
  {
    if( dot(n, n) > 0.65 )
      return true; 
  }
  else if(cb_cbSMAPointData.PointSymbol == 11.0)  //FULLSQUARE
  {
    if( abs(n.x) > 0.7 || abs(n.y) > 0.7 )
      return true;
  }
  else if(cb_cbSMAPointData.PointSymbol == 12.0)  //FULLCIRCLE2
  {
    if( dot(n, n) > 1.0 )
      return true;
  }
#if 0 // For everything else, just output the entire square
  //FULLSQUARE2, DOT and SMALLDOT. Dot size changed in SMAHvcNodesVS
  else if( cb_cbSMAPointData.PointSymbol == 13.0 || cb_cbSMAPointData.PointSymbol == 15.0  ||  cb_cbSMAPointData.PointSymbol == 14.0 )
  {
    if( abs(n.x) >= 1.0 || abs(n.y) >= 1.0 )
      return true;
  }
  // else just output the full square
#endif
  return false;
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

vec3 ComputeViewNormal()
{
  //return vGetWorldN();
  //return vec3(0.0, 1.0, 0.0);

  // in pdsfx v0, the name of the function was ComputeWorldNormal(), and it was returning vec3(0.0, 1.0, 0.0);
  // In theory, to get the corresponding value in view space, we should multiply the inverse transpose view matrix by vec4(0.0, 1.0, 0.0, 0.0)
  // But does it make sense to have a world-space constant direction for normals, to display camera-facing points?
  // And is the normal used anyway? VisSMAHvcPtSym.xml has <LIGHTING>false</LIGHTING>...
  // So during migration to pdsfx v1, I return view-space constant direction facing the camera, instead
  return vec3(0.0, 0.0, 1.0);
}
