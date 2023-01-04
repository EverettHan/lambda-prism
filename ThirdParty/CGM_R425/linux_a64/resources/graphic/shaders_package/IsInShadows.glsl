//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                          IsInShadow (for Globe)
//----------------------------------------------------------------------------------------------------------------------------------------------

#if defined(ShadowMap) && defined(Lighting)

bool _IsInShadow(vec3 iViewPos, int iShadowID)
{
#if defined(MultiNonPointShadows) || defined(NonPointShadow)
  if (iShadowID < 0) return false;

  int shadowID = iShadowID;
#ifdef CascadedShadow
  if (iShadowID == CascadedShadowLightID)
  {
    shadowID += GetCascade(iViewPos);
  }
#endif

  vec4  resCoord = GetShadowMapCoord(iViewPos, shadowID);

  // To filter points behind light source
  if (resCoord.w < 0) return false;

  resCoord.w = shadowID;
    
#if defined(ESM) || defined(PCSS)
  float shadowDepth = SampleShadowTexture(shadowMapTex2, vec4(resCoord.xy, shadowID, 0)).x;
  if (shadowDepth < resCoord.z) return true;
#else
  float res = SampleShadowTexture(shadowMapTex, resCoord);
  if (res < 1) return true;
#endif

#endif

  return false;
}

bool vIsInShadowPointLight(vec3 iViewPt, int iLightID)
{
#if defined(PointLightShadows) || defined(MultiPointLightShadows)
  int shadowID = _sbLightsSB2.PointShadowLayer[iLightID];
  if (shadowID < 0) return false;

  vec3 lightPos     = _sbLightsSB2.PointPosition[iLightID];
  vec4 resCoord     = GetPointLightShadowCoord(iViewPt, shadowID, lightPos);
  vec3 lightDir     = GetLightDir(iViewPt, lightPos);
  float shadowDepth = SampleCubemapTex(ShadowCubeMapTex, lightDir, iLightID).x;

  if (shadowDepth < resCoord.z)
    return true;
#endif

  return false;
}

bool vIsInShadowSpotLight(vec3 iViewPt, int iLightID)
{
  return _IsInShadow(iViewPt, _sbLightsSB2.SpotShadowLayer[iLightID]);
}

bool vIsInShadowDirLight(vec3 iViewPt, int iLightID)
{
  return _IsInShadow(iViewPt, _sbLightsSB2.DirShadowLayer[iLightID]);
}

int vIsInShadow(vec3 iViewPt)
{
  int isInShadow = 0;

  int shadowID = 0;

  int lightID = 0;
#ifdef NumberOfPointLights
  for (lightID = 0; lightID < vMin(NumberOfPointLights, _V_MAX_LIGHTS); ++lightID)
  {
    if (vIsInShadowPointLight(iViewPt, lightID))
    {
      isInShadow++;
    }
  }
#endif

#ifdef NumberOfSpotLights
  for (lightID = 0; lightID < vMin(NumberOfSpotLights, _V_MAX_LIGHTS); ++lightID)
  {
    if (vIsInShadowSpotLight(iViewPt, lightID))
    {
      isInShadow++;
    }
  }
#endif
  
#ifdef NumberOfDirLights
  for (lightID = 0; lightID < vMin(NumberOfDirLights, _V_MAX_LIGHTS); ++lightID)
  {
    if (vIsInShadowDirLight(iViewPt, lightID))
    {
      isInShadow++;
    }
  }
#endif

  return isInShadow;
}
#else
bool vIsInShadowPointLight(vec3 iViewPt, int iLightID)
{
  return false;
}

bool vIsInShadowSpotLight(vec3 iViewPt, int iLightID)
{
  return false;
}

bool vIsInShadowDirLight(vec3 iViewPt, int iLightID)
{
  return false;
}

int  vIsInShadow(vec3 iPt)
{
  return 0;
}
#endif 


