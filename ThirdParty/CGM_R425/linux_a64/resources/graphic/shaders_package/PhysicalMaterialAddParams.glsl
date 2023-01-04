#ifdef Flakes

// metallic flakes BRDF
  float _metallicFlakesGlossiness;
  vec3 _metallicFlakesFresnel;
  vec3 _metallicFlakesNormal;
  float _metalGlossiness;
  vec3 _metalFresnel;
  

  // pearl flakes BRDF
  float _pearlFlakesGlossiness;
  vec3 _pearlFlakesFresnel;
  vec3 _pearlFlakesNormal;
  float _pearlGlossiness;
  vec3 _pearlFresnel;
  
#endif // Flakes

#ifdef Coating

  vec3 _coatingNormal;
  vec4 _coatingFresnelCoefficient;
  float _coatingGlossiness;

#ifndef coatingFresnelCoefficientAsTexture
vec4 pmGetCoatingFresnelCoefficient()
{
    return vec4(PMat.coatingFresnelCoefficient,0.);
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
vec4 pmGetCoatingFresnelCoefficient()
{
    vec2 uvs = _GetParameterUvs(mat3(PMat.coatingFresnelCoefficientUvTransform));
    return vTexture(V_GET_PM_TEXTURE(coatingFresnelCoefficient), uvs);
}
#endif // coatingFresnelCoefficientAsTexture

float pmGetCoatingGlossiness()
{
  return PMat.coatingGlossiness;
}

#ifndef coatingNormalMapEnabled
  vec4 pmGetCoatingNormalMap()
  {
    return vec4(0.0);
  }
#else
  vec4 pmGetCoatingNormalMap()
  {
      vec2 uvs = _GetParameterUvs(mat3(PMat.coatingNormalMapUvTransform));
      return vTexture(V_GET_PM_TEXTURE(coatingNormalMap), uvs);
  }
#endif // coatingNormalMapEnabled

#endif // Coating


float _occlusionMap;
#ifndef occlusionMapEnabled
vec4 pmGetOcclusionMap()
{
  return vec4(0.0);
}
#else
vec4 pmGetOcclusionMap()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.occlusionMapUvTransform));
  return vTexture(V_GET_PM_TEXTURE(occlusionMap), uvs);
}
#endif // occlusionMapEnabled

#ifdef Fabrics

#if defined(UseSatin) || defined(UseSilkVelvet)
  #define SpecularF0  vec3(0.284)
  #define SpecularF90  vec3(0.102)
#endif

#if defined(UseVelvet) 
  #define SpecularF0  vec3(0.051)
  #define SpecularF90  vec3(0.048)
#endif

#endif // Fabrics
