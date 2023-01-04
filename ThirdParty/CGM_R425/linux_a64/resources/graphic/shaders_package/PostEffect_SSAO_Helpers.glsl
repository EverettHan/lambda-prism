//  Projette un point sur l'ecran
//  En sortie on un point dont les coordonees pour x et y sont entre [0, 1]
vec2 ProjectPtOnScreen(const vec4 iPt)
{
  vec4 pt = cb_PostEffectAuto.u_ProjectionMatrix * iPt;
  vec2 ptScreen = pt.xy/pt.w;
  ptScreen = vFma(ptScreen, vec2(0.5), vec2(0.5));
  
  return ptScreen;
}

vec2 ProjectPtOnScreen(const vec3 iPt)
{
  return ProjectPtOnScreen(vec4(iPt, 1.0));
}

// Calcul le rayon en unite model a utiliser pour le 
// iScreenPt:       point ecran x entre [0,1], y entre [0,1]
// oPt:             point de l'espace View
// oRadius:         rayon de la sphere d'influence du SSAO dans l'espace View (unite model)
// oScreenRadius:   rayon de la sphere d'influence du SSAO dans l'espace ecran [0,1]
bool ComputePointAndRadiusInViewSpace(const vec2 iScreenPt, out vec3 oPt, out float oRadius, out float oScreenRadius)
{
  if (ComputePointInViewSpace(iScreenPt, oPt)==false) 
    return false;
  
  oScreenRadius = 0;
#ifdef DYNAMIC_RADIUS
  oRadius = cb_PostEffectAuto.u_SceneRadius * cb_PostEffect_SSAO.u_Radius;
#else
  oRadius = cb_PostEffect_SSAO.u_Radius;
#endif

  if (oRadius==0.0)
    return false;

#if defined(ADAPTATIVE_RADIUS) || defined(HBAO_MODE)
  // proj: Near / (right - left)
  // otho: 1 / (right - left)
  float radiusToScreen = 0.5 * cb_PostEffectAuto.u_ProjectionMatrix[0][0]; 
#ifdef PROJECTION_CONIC
  radiusToScreen /= (-oPt.z);
#endif
  oScreenRadius = radiusToScreen * oRadius;
#endif
  
#ifdef ADAPTATIVE_RADIUS
  float screenRadiusMin = vMax(cb_PostEffect_SSAO.u_RadiusPixelMin*cb_PostEffect_SSAO.u_PixelSize.x, cb_PostEffect_SSAO.u_RadiusMin);
  float screenRadiusMax = vMin(cb_PostEffect_SSAO.u_RadiusPixelMax*cb_PostEffect_SSAO.u_PixelSize.x, cb_PostEffect_SSAO.u_RadiusMax);

  oScreenRadius = vMin(screenRadiusMax, vMax(oScreenRadius, screenRadiusMin));
  oRadius       = oScreenRadius / radiusToScreen;
#endif

  return true;
}
