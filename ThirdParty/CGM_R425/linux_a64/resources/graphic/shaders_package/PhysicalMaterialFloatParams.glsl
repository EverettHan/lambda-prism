#ifndef GeometryStage

/********************************************    FLOAT PARAM   *************************************************************/
float _glossiness;
#ifndef glossinessAsTexture
float pmGetGlossiness()
{
  return PMat.glossiness;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetGlossiness()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.glossinessUvTransform));
  return vTexture(V_GET_PM_TEXTURE(glossiness), uvs).x;
}
#endif // glossinessAsTexture

/********************************************/
float _edgeColorBias;
#ifndef edgeColorBiasAsTexture
float pmGetEdgeColorBias()
{
  return PMat.edgeColorBias;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetEdgeColorBias()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.edgeColorBiasUvTransform));
  return vTexture(V_GET_PM_TEXTURE(edgeColorBias), uvs).x;
}
#endif // edgeColorBiasAsTexture

/********************************************/
float _displacement;
#ifndef displacementAsTexture
float pmGetDisplacement()
{
  return PMat.displacement;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetDisplacement()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.displacementUvTransform));
  return vTexture(V_GET_PM_TEXTURE(displacement), uvs).x;
}
#endif //displacementAsTexture


/********************************************/
float _anisotropy;
#ifndef anisotropyAsTexture
float pmGetAnisotropy()
{
  return PMat.anisotropy;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetAnisotropy()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.anisotropyUvTransform));
  return vTexture(V_GET_PM_TEXTURE(anisotropy), uvs).x;
}
#endif // anisotropyAsTexture

/********************************************/
float _anisotropyAngle;
#ifndef anisotropyAngleAsTexture
float pmGetAnisotropyAngle()
{
  return PMat.anisotropyAngle;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetAnisotropyAngle()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.anisotropyAngleUvTransform));
  return vTexture(V_GET_PM_TEXTURE(anisotropyAngle), uvs).x;
}
#endif // anisotropyAngleAsTexture

/********************************************/
float _bumpScale;
#ifndef bumpScaleAsTexture
float pmGetBumpScale()
{
  return PMat.bumpScale;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetBumpScale()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.bumpScaleUvTransform));
  return vTexture(V_GET_PM_TEXTURE(bumpScale), uvs).x;
}
#endif // bumpScaleAsTexture

/********************************************/
float _transparency;
#ifndef transparencyAsTexture
float pmGetTransparency()
{
  return PMat.transparency;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
float pmGetTransparency()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.transparencyUvTransform));
  return vTexture(V_GET_PM_TEXTURE(transparency), uvs).x;
}
#endif // transparencyAsTexture

/********************************************/

float _opacity;
#ifndef opacityAsTexture
float pmGetOpacity()
{
  return PMat.opacity;
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture

float pmGetOpacity()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.opacityUvTransform));
  return vTexture(V_GET_PM_TEXTURE(opacity), uvs).x;
}
#endif // opacityAsTexture


#endif
