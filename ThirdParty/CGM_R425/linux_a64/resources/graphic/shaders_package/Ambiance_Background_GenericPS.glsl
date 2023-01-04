/*
Shader Options:
  - BACKGROUND_TYPE:            Background's type
      1 : Uniform
      2 : Gradient
      3 : Gradient with Horizon
      4 : CubeMap
      5 : LatLong

  - BACKGROUND_GEOMETRY:        Define a finite geometry for the background
      1 : Sphere

  - BACKGROUND_GEOMETRY_AUTO:   When a geometry is defined, its position, radius are based on 3D scene BE

  - BACKGROUND_GEOMETRY_GROUND: Define a geometry for ground (a plane which cut the background geometry)

  - BACKGROUND_GROUND:          Define a gradient for infinite ground
  
  - FORCE_NOALPHA:              Force alpha to be set to 1 (opaque)
*/

vec2 MapNormalToTextureCoordinate(in vec3 iNormal)
{
  float u = (vAtan(iNormal.x, iNormal.y) + PI) * 0.5*INV_PI; // 1/(2*PI)
  float v = vAsin(iNormal.z) * INV_PI + 0.5;  
  
  return vec2(u,v);
}

void main()
{ 
  vec3 n = vNormalize(vRay);
      
#if defined(OFFSET_ACTIVATION) 
  n.z += cb_Background.u_Offset;
#endif

  bool geometry = false;

#if defined(BACKGROUND_GEOMETRY) && !defined(FILTER_BACKGROUND_GEOMETRY)

  vec3  groundPosition = cb_BackgroundAuto.u_GroundPosition2;
#ifdef UsePassThroughTransition
  groundPosition -= vGetEyeWorldPosOffset();
#endif
  vec3  groundNormal   = cb_BackgroundAuto.u_GroundNormal;

#ifdef BACKGROUND_GEOMETRY_AUTO
  // Auto
  vec3  sphereCenter = groundPosition + groundNormal * cb_Background.u_SceneHeight * cb_BackgroundAuto.u_GroundRadius;
  float sphereRadius = cb_BackgroundAuto.u_GroundRadius * cb_Background.u_GroundScale;
#else
  // Manual
  vec3  sphereCenter = vDomePosition;
  float sphereRadius = cb_Background.u_Size;
#endif
 
  if (sphereRadius > 0.0)
  {
#ifdef PROJECTION_CONIC
    vec3  rayDir      = n;
    vec3  rayOrig     = vec3(0,0,0);
#else
    // TODO: ameliorer ce mode en precalculant correctement un vViewDir dans le VS ou une semantic
    vec3  rayDir = vec3(0.0,0.0,-1.0);
    vec4  tmp = vGetViewInverseMatrix() * vec4(rayDir, 0.0);
    rayDir = tmp.xyz;

    vec3  rayOrig  = vRay;
#endif

    float t =  IntersectSphereFar(rayOrig, rayDir, sphereCenter, sphereRadius);
    
    if (t>0.0)
    {
      geometry = true;

#ifdef BACKGROUND_GEOMETRY_GROUND
      if (vDot(groundNormal, rayDir)<-1e-10)
      {
        float planeT  = IntersectPlane(rayOrig, rayDir, groundPosition, groundNormal);
  
#ifdef PROJECTION_CONIC
        t = (planeT>0.0) ? vMin(planeT,t) : t;
#else   
        t = vMin(planeT,t);
#endif
      }
#endif

      vec3 hitPos = rayOrig + t*rayDir;

#ifdef BACKGROUND_GEOMETRY_AUTO
      vec3  projectionCenter = sphereCenter - vDot(sphereCenter - groundPosition, groundNormal) * groundNormal;
      projectionCenter += groundNormal * cb_BackgroundAuto.u_GroundRadius * cb_Background.u_ShootHeight;
#else
      vec3 projectionCenter = sphereCenter + cb_Background.u_ShootPositionOffset;
#endif

      vec3 sn = (hitPos - projectionCenter);
      n = vNormalize(sn);
    }
  }
#endif
    
#ifdef BACKGROUND_MATRIX
  n = (cb_Background.u_Matrix * vec4(n, 0)).xyz;
#endif

  vec4 color = vec4(0, 0, 0, 1.0);
  
#if BACKGROUND_TYPE==1
  // Uniform
  color = cb_Background.u_Color;

#elif BACKGROUND_TYPE==2
  // Gradient
  float ratio = vFma(n.z, 0.5, 0.5);
  color = ratio * cb_Background.u_ColorTop + (1.0 - ratio) * cb_Background.u_Color;

  
#elif BACKGROUND_TYPE==3
  // Gradient with Horizon
  float ratio = vClamp(n.z, cb_Background.u_HorizonHeight, 1.0);
  ratio = (ratio - cb_Background.u_HorizonHeight) / (1.0 - cb_Background.u_HorizonHeight);
  color = ratio * cb_Background.u_ColorTop + (1.0 - ratio) * cb_Background.u_Color;

#elif BACKGROUND_TYPE==4
  // CubeMap
  color = vTextureCubeMapLod(s_SkyMap, n, 0.0);
  //color = vTexture(s_SkyMap, n);
    
#elif BACKGROUND_TYPE==5
  // LatLong
  vec2 coords = MapNormalToTextureCoordinate(n);
  // On utilise textureLod et non pas texture car sinon on a des artefact a la frange
  color = vTextureLod(s_SkyMap, coords, 0.0); 
  //color = vTexture(s_SkyMap, coords);
  
#endif

#ifdef BACKGROUND_GROUND
  // l'offset sere a créer un AA fictif au niveau de l'horizon
  float offset = geometry ? 0.005f : 0.001f;
  if (n.z < (cb_Background.u_HorizonHeight+offset))
  {
    if (n.z < cb_Background.u_HorizonHeight)
    {
      float ratioGround = vClamp(n.z, -1.0, cb_Background.u_HorizonHeight);
      ratioGround = (ratioGround + 1.0) / (cb_Background.u_HorizonHeight + 1.0);

      color = ratioGround * cb_Background.u_ColorGroundTop + (1.0 - ratioGround) * cb_Background.u_ColorGround;
    }
    else
    {
      float alpha = (n.z - cb_Background.u_HorizonHeight) / offset;
      alpha = alpha *alpha;
      color = alpha * color + (1.0 - alpha)*cb_Background.u_ColorGroundTop;
    }
  }
#endif

  color.xyz *= cb_Background.u_Intensity;
  
#ifdef FORCE_NOALPHA
  color.w = 1.0;
#endif

  FRAGCOLOR = color;
}
