vec3 gv3_Normal;

void ComputeCommonValues()
{
  vec2 v2PC = vGetPointCoord();
  vec3 n;
  n.xy = v2PC * 2.0 - 1.0;
  n.z = dot(n.xy, n.xy);
  if( n.z > 1.0 )
    discard;
  n.z = sqrt(1.0 - n.z);
  gv3_Normal = normalize(n);
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
  return gv3_Normal;
}

// from pdsfx v0 version; commented instead of removed, just to keep the inner comment
//void ProcessFinalColor(inout vec3 finalColor)
//{
//  // Could enable this if not using lighting
//  //finalColor = finalColor * gv3_Normal.z;
//}
