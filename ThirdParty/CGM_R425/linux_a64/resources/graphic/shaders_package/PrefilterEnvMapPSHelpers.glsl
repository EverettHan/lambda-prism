#ifdef SO_CONVOLUTION_USE_GEOMETRY_STAGE
  #define TEXCOORD gTexCoord
#else
  #define TEXCOORD vTexCoord
#endif

vec3 Tangent2World(in vec3 iTS, in vec3 iNormal)
{
  vec3 res;

  vec3 up = abs(iNormal.z) < 0.9999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 tX = normalize(cross(up, iNormal));
  vec3 tY = normalize(cross(iNormal, tX));
  
  res.x = tX.x*iTS.x + tY.x*iTS.y + iNormal.x*iTS.z;
  res.y = tX.y*iTS.x + tY.y*iTS.y + iNormal.y*iTS.z;
  res.z = tX.z*iTS.x + tY.z*iTS.y + iNormal.z*iTS.z;

  return res;
}
