float IntersectPlane(const vec3 iRayOrigin, const vec3 iRayDir, 
                     const vec3 iPlaneOrig, const vec3 iPlaneNormal)
{
  float t = vDot(iPlaneNormal, iPlaneOrig-iRayOrigin);

  // FBJ: on devrait garder ce test, pour supprimer tout ce qui est dans la matiere
  //      mais cela introduit un reg avec  les background avec dome en mode ortho
  //      car dans ce cas la, le near plane est mal calculé
  //      Vu que dans ce cas, on bidouille une pojection perspective a partie d'une proj ortho, ce n'est pas etonnant
  //      Il faudrait revoir ce code, mais en attendant pour supprimer la reg, je commente cette ligne
  //if (t>0.0) return 0.0;

  float cosNormalDir = vDot(iPlaneNormal, iRayDir);
  if (cosNormalDir==0.0) return 0.0;

  t = t/cosNormalDir;

  return t;
}

float IntersectSphere(const vec3 iRayOrigin, const vec3 iRayDir, 
                      const vec3 iSphereCenter, const float iSphereRadius)
{
  float t = 0.0;

  vec3 l = iRayOrigin-iSphereCenter;
  float l2 = vDot(l, l);

  float r2 = iSphereRadius*iSphereRadius;

  // on est a l'interieur de la sphere
  if (l2<r2) return -1.0;

  float dot = vDot(iRayDir, l);
  float delta = dot*dot-l2+r2;

  if (delta<0.0) return -1.0;

  t = - dot - vSqrt(delta);

  return t;
}

float IntersectSphereFar(const vec3  iRayOrig, const vec3  iRayDir, 
                         const vec3  iSphereCenter, const float iSphereRadius)
{
  vec3 dist   = iRayOrig - iSphereCenter;
  
  float B     = 2.0*vDot(iRayDir, dist);
  float C     = vDot(dist, dist) - iSphereRadius*iSphereRadius;

  float disc  = B*B - 4.0*C;
  if (disc < 0.0) return -1.0;

  float t = (-B + vSqrt(disc)) / 2.0;

  return t;
}

vec3 GetWorldCameraRay(const vec2 iTexCoord, const vec4 iBufferToViewNearPlane, const float iNearPlane, const mat4 iViewInverseMatrix, const vec2 iPixelSize)
{
  vec3 viewDir;
#if !defined(GLESPlatform) && (GLSLVersion >= 400)
  vec2 texCoord = iTexCoord.xy + (vGetSamplePosition()-vec2(0.5))*iPixelSize;
#else
  vec2 texCoord = iTexCoord.xy;
#endif

  viewDir.xy = vFma(texCoord.xy, iBufferToViewNearPlane.zw, iBufferToViewNearPlane.xy);
  viewDir.z = -iNearPlane;
  viewDir = (iViewInverseMatrix * vec4(viewDir, 0.0)).xyz;

  return viewDir;
}

