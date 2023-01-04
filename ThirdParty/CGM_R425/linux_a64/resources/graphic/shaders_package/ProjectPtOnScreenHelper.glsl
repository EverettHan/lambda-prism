
// Piece of code copied from ./VisualizationEngines/VisualizationEnginesOGLResources.m/src/resources/graphic/shaders_package/PostEffect_SSAO_Helpers.glsl
//  Projette un point sur l'ecran
//  En sortie on un point dont les coordonees pour x et y sont entre [0, 1]
vec2 ProjectPtOnScreen(const vec4 iPt)
{
  vec4 pt = cb_PostEffectAuto.u_ProjectionMatrix * iPt;
  vec2 ptScreen = pt.xy/pt.w;
  ptScreen = ptScreen*0.5+0.5;
  
  return ptScreen;
}

vec2 ProjectPtOnScreen(const vec3 iPt)
{
  return ProjectPtOnScreen(vec4(iPt, 1.0));
}
