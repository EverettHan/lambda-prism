vec2 gv2_tex;
vec3 gv3_normal;

void ComputeCommonValues()
{
  gv3_normal = vec3( 0.0, 1.0, 0.0 );
}

vec3 ComputeObjectPosition()
{
#ifdef PDSFXInstancing //This macro will be defined if the instancing buffer is set
  int nPos = vGetInstanceID() * 3;
  vec4 v4Rot = vGetInstanceData(nPos  ); // x, y, z, biDirectional (tensor)
  vec4 v4Pos = vGetInstanceData(nPos+1); // x, y, z, scale
  vec4 v4Dat = vGetInstanceData(nPos+2); // tex.x, 3D, sin(rot), cos(rot)
  gv2_tex = vec2(v4Dat.x, 0.0);

  // Build the rotation matrix
  vec3 v3Sq = vec3(v4Rot.x * v4Rot.x, v4Rot.y * v4Rot.y, v4Rot.z * v4Rot.z);
  float xy = v4Rot.x * v4Rot.y;
  float xz = v4Rot.x * v4Rot.z;
  float yz = v4Rot.y * v4Rot.z;
  float fCos = v4Dat.w;
  v4Rot.xyz = v4Rot.xyz * v4Dat.z;
  mat3 m = mat3( v3Sq.x + (v3Sq.y + v3Sq.z) * fCos, xy - xy*fCos + v4Rot.z, xz - xz*fCos - v4Rot.y,
           xy - xy*fCos - v4Rot.z, v3Sq.y + (v3Sq.x + v3Sq.z) * fCos, yz - yz*fCos + v4Rot.x,
           xz - xz*fCos + v4Rot.y, yz - yz*fCos - v4Rot.x, v3Sq.z + (v3Sq.x + v3Sq.y) * fCos );
  if( 0.0 < v4Dat.y ) // If 3D
    gv3_normal = normalize( m * vGetNormal() );
//  m *= v4Pos.a;
  mat3 ms = mat3( v4Pos.a, 0.0, 0.0, 0.0, v4Pos.a, 0.0, 0.0, 0.0, v4Pos.a );
  m *= ms;

  vec3 v3Pos = vGetAttribPosition();
  // For negative tensor values, this will invert the unit arrowhead
  if( v4Rot.w > 0.0 && v4Dat.x < 0.0 && (v3Pos.x != 0.0 || v3Pos.y != 0.0) )
    v3Pos.z = v3Pos.z < 0.0 ? -1.0 : 1.0;
  v3Pos = m * v3Pos;

  return v3Pos + v4Pos.xyz;
#else
  return vec3(0.0);
#endif

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
    float fResX = gv2_tex.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
    if( 4.0 > fDim )
      gv2_tex.x = clamp(fResX, 0.0, 1.0);
    else
      gv2_tex.x = fract(fResX);
    if( 1.0 == fDim || 5.0 == fDim )
    {
      gv2_tex.y = 0.0;
      v4Col.rgb *= vTexture(ContourMap1D, gv2_tex).rgb;
    }
    else //if( 2.0 == cb_cbSMAResultsData.ResultsDim )
    {
      gv2_tex.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(gv2_tex.y,0.0,1.0);
      v4Col.rgb *= vTexture(ContourMap2D, gv2_tex).rgb;
    }
  }

  v4_color = v4Col;// * 0.9;
  
  // the varying output will be the normal in view space
  v3_normal = (vGetWorldViewInvTranspMatrix() * vec4(gv3_normal, 0.0)).xyz;
}
