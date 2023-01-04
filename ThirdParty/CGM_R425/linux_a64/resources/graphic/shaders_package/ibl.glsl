#ifdef Lighting
#ifdef ImageBasedLighting
#if defined(FragmentStage) || defined(RayHitStage)
#ifdef PDSFX_ENABLE_IBL_MIRROR_MAP

//Special case for Globe's Ocean
vec3 ComputeIBL(in LightingData iData, in BRDFParameters iParameters, out vec3 specContrib, out vec3 diffuseContrib)
{
// TODO: implement for EVisuPBR !!!
  vec2 envBRDF = vTextureLod(LookUpTexture2D, vec2(vMax(0.0, vDot(iData.Nworld, iData.Vworld)), 0.0), 0.0).xy;
  vec3 f0 = iParameters.f0 * envBRDF.x + envBRDF.y;
  vec3 specularColor = vGetMirrorMap(iParameters.iblMirrorMapCoords.xy).xyz;

  #ifdef PDSFX_ENABLE_IBL_CONTROL
    specularColor *= iParameters.specularIBLFactor;
  #endif
  
  vec3 custom_radiance = vec3(0.0);

  #ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
    BRDFLayerParameters params;
    params.fresnel = f0;
    params.irradiance = vec3(0.0); //not sure if this is useful in this case
    params.lightType = LIGHT_TYPE_IBL;
    params.lightID = iData.lightID;
    custom_radiance += ComputeCustomBRDFLayer(params);
  #endif

  specContrib = specularColor * f0 + custom_radiance;

  return specContrib;
}

#else // PDSFX_ENABLE_IBL_MIRROR_MAP 
vec3 ComputeIBL(in LightingData iData, in BRDFParameters iParameters, out vec3 specContrib, out vec3 diffuseContrib)
{
// TODO: implement for EVisuPBR !!!
  //When prefiltering, we ignore the last 2 levels so that roughness maps from [0, 1] to [0, 7] for cube maps >= 512x512
  //Anything less than 512 will use less that 8 mip levels
#if !defined(GLESPlatform) && (GLSLVersion >= 430)
  float numMipMaps = vMin(8.0, textureQueryLevels(SpecularIBL)-2.0)-1.0;
#else // !GLES2Platform
  float numMipMaps = 5.5;
#endif // !GLES2Platform
  
  vec3 contribution;
  contribution = computeBaseIBL(iData, iParameters, numMipMaps, specContrib, diffuseContrib);

#ifdef Coating  
  vec3 coatingContrib = computeCoatingIBL(iData, iParameters, numMipMaps);
  contribution += coatingContrib;
  specContrib += coatingContrib;
#endif // Coating

#ifdef Flakes
  vec3 metalFlakes = computeMetallicFlakesIBL(iData, iParameters,numMipMaps) + computeMetalIBL(iData, iParameters, numMipMaps);
  vec3 pearlFlakes = computePearlFlakesIBL(iData, iParameters,numMipMaps) +  computePearlIBL(iData, iParameters, numMipMaps);
  contribution += metalFlakes + pearlFlakes;
#endif // Flakes

  return contribution;
}

#endif //PDSFX_ENABLE_IBL_MIRROR_MAP 
#endif //FragmentStage
#endif //ImageBasedLighting
#endif //Lighting
