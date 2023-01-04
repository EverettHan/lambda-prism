#ifdef ShadowMap

#ifdef MultiShadow
  struct ShadowData_t
  {
    mat4 ViewToLightProjMatrix;
    vec4 LightNearFarDirRadius;
  };

  layout(std430) readonly buffer ShadowBuffer
  {
    ShadowData_t g_shadowBuffer[];
  };
#endif
  
float GetLightNear(int iShadowID)
{
#ifndef MultiShadow
  return cb_Shadow_Auto.LightNearFarDirRadius.x;
#else
  return g_shadowBuffer[iShadowID].LightNearFarDirRadius.x;
#endif
}

float GetLightFar(int iShadowID)
{
#ifndef MultiShadow
  return cb_Shadow_Auto.LightNearFarDirRadius.y;
#else
  return g_shadowBuffer[iShadowID].LightNearFarDirRadius.y;
#endif
}

float SampleDepthTexture(sampler2D iTexture, vec3 iCoord)
{
  return vTexture(iTexture, iCoord.xy).x;
}

float SampleDepthTexture(sampler2DArray iTexture, vec3 iCoord)
{
  return vTexture(iTexture, iCoord).x;
}

#ifdef CascadedShadow
int GetCascade(vec3 iViewPos)
{
  int cascade = 0;

  float depth = -iViewPos.z;

  vec4 cascadedPlane1 = cb_Shadow_Auto.CascadePlanes[0];
  vec4 cascadedPlane2 = cb_Shadow_Auto.CascadePlanes[1];

#if NB_CASCADES > 7
  if (depth > cascadedPlane2.z)
    cascade = 7;
  else
#endif

#if NB_CASCADES > 6
    if (depth > cascadedPlane2.y)
      cascade = 6;
    else
#endif


#if NB_CASCADES > 5
      if (depth > cascadedPlane2.x)
        cascade = 5;
      else
#endif

#if NB_CASCADES > 4
        if (depth > cascadedPlane1.w)
          cascade = 4;
        else
#endif

#if NB_CASCADES > 3
          if (depth > cascadedPlane1.z)
            cascade = 3;
          else
#endif

#if NB_CASCADES > 2
            if (depth > cascadedPlane1.y)
              cascade = 2;
            else
#endif

              if (depth > cascadedPlane1.x)
                cascade = 1;

  return cascade;
}
#endif 


bool IsInShadow(vec3 iViewPos, int iShadowID)
{
  mat4 offsetMatrix = mat4(0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);

  mat4 projMatrix;
  vec4 coord = vec4(iViewPos, 1.0);

#ifdef MultiShadow  
  projMatrix = g_shadowBuffer[iShadowID].ViewToLightProjMatrix;
#else 
  projMatrix = cb_Shadow_Auto.ObjectViewToLightProjMatrix;
#endif 

#ifdef UsePassThroughTransition
  vec4 resCoord = offsetMatrix * projMatrix * _vPrivGetViewInverseTransition() * coord;
#else
  vec4 resCoord = offsetMatrix * projMatrix * coord;
#endif

  resCoord.xyz /= resCoord.w;

  //Clamp is made for globe
  resCoord.z = vClamp(resCoord.z, 0, 1);

  //We linearize the Z if we have a perspective projection
  if (IsPerspective(resCoord))
  {
    float n = GetLightNear(iShadowID);
    float f = GetLightFar(iShadowID);
    float z = resCoord.z;

    resCoord.z = ZClipRemmapedInLinear(n, f, z);
  }

  float shadowDepth = SampleDepthTexture(s_ShadowMap, vec3(resCoord.xy, iShadowID)).x;

  if (shadowDepth < resCoord.z)
    return true;

  return false;
}

bool IsInShadows(vec3 iPt)
{
  int shadowID = 0;
#ifdef MultiNonPointShadows
  for (int lightID = 0; lightID < MultiNonPointShadows; lightID++)
  {
#else
  int lightID = 0;
#endif

#ifdef CascadedShadow
  if (lightID == CascadedShadowLightID)
  {
    shadowID += GetCascade(iPt);
  }
#endif

  if (IsInShadow(iPt, shadowID))
    return true;

#ifdef MultiNonPointShadows
#ifdef CascadedShadow
  if (lightID == CascadedShadowLightID)
  {
    shadowID = lightID + NB_CASCADES;
  }
  else
#endif
  {
    shadowID++;
  }
  }
#endif

return false;
}
#else
#define IsInShadows(iPt) (false)
#endif


