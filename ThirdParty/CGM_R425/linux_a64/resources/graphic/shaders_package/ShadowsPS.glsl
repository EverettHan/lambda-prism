#ifdef ShadowMap

//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                        VARYINGS
//----------------------------------------------------------------------------------------------------------------------------------------------

#if defined(MultiShadow)
in vec4 shadowMapCoord;
#endif


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                       Service for Textures to manage array
//----------------------------------------------------------------------------------------------------------------------------------------------

float SampleShadowTexture(sampler2DShadow iTexture, vec4 iPos)
{
  return vTexture(iTexture, iPos.xyz);
}

float SampleShadowTexture(sampler2DArrayShadow iTexture, vec4 iPos)
{
  return vTexture(iTexture, vec4(iPos.xy, iPos.w, iPos.z));
}

vec4 SampleShadowTexture(sampler2D iTexture, vec4 iPos)
{
  return vTexture(iTexture, iPos.xy);
}

vec4 SampleShadowTexture(sampler2DArray iTexture, vec4 iPos)
{
  return vTexture(iTexture, iPos.xyz);
}

vec4 SampleCubemapTex(samplerCube iCubeMapTex, vec3 ilightDir, int iLightLayer)
{
  return vTexture(iCubeMapTex, vNormalize(ilightDir));
}

vec4 SampleCubemapTex(samplerCubeArray iCubeMapTex, vec3 ilightDir, int iLightLayer)
{
  return vTexture(iCubeMapTex, vec4(vNormalize(ilightDir), iLightLayer));
}


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                       Bias (PCF, PCSS)
//----------------------------------------------------------------------------------------------------------------------------------------------

#ifdef SHADOWS_USE_GPU_BIAS
float ApplyBiasedZ(float z0, vec2 dz_duv, vec2 offset)
{
  return vClamp(z0 + dot(dz_duv, offset) - 0.005, 0.0, 1.0);
}
#elif defined(SHADOWS_USE_FIXED_BIAS)
float ApplyBiasedZ(float z0, vec2 dz_duv, vec2 offset)
{
  return vClamp(z0 - 0.005, 0.0, 1.0);
}
#else //No bias
float ApplyBiasedZ(float z0, vec2 dz_duv, vec2 offset)
{
  return z0;
}
#endif


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                       Service for Ligths
//----------------------------------------------------------------------------------------------------------------------------------------------

float GetLightNear(int iShadowID)
{
#ifndef MultiShadow
  return _sbcbShadow.LightNearFarDirRadius.x;
#else
  return g_shadowBuffer[iShadowID].LightNearFarDirRadius.x;
#endif
}

float GetLightFar(int iShadowID)
{
#ifndef MultiShadow
  return _sbcbShadow.LightNearFarDirRadius.y;
#else
  return g_shadowBuffer[iShadowID].LightNearFarDirRadius.y;
#endif
}

vec3 GetLightDir(vec3 iViewPt, vec3 iLightPos)
{
  vec3 lightDir = iViewPt - iLightPos;
  return vec3(vGetViewInverseMatrix()  * vec4(lightDir, 0.0));
}

vec3 GetLightDir(vec3 iLightPos)
{
  return GetLightDir(vGetViewPosition(), iLightPos);
}

vec2 GetLightDirRadius(int iShadowID)
{
#ifndef MultiShadow
  return vec2(_sbcbShadow.LightNearFarDirRadius.z);
#else
  return vec2(g_shadowBuffer[iShadowID].LightNearFarDirRadius.z);
#endif
}

float ZClipToEye(float z, int iShadowID)
{
  float lightNear = GetLightNear(iShadowID);
  float lightFar = GetLightFar(iShadowID);

  return ZClipToEye(lightNear, lightFar, z);
}


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                        Shadow map coord
//----------------------------------------------------------------------------------------------------------------------------------------------

vec4 _GetShadowMapCoord(vec3 iViewPos, int iShadowID)
{
  mat4 offsetMatrix = mat4(0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0);

  vec4 coord = vec4(iViewPos, 1);

  mat4 projMatrix;
#if defined(MultiShadow) || defined(CascadedShadow)
  mat4 passageMatrix = _sbcbMultiShadow.PassageMatrix;
  projMatrix = g_shadowBuffer[iShadowID].ObjectViewToLightProjMatrix * passageMatrix;
#else 
  projMatrix = _sbcbShadow.ObjectViewToLightProjMatrix;
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

  return resCoord;
}

vec4 GetShadowMapCoord(vec3 iViewPos, int iShadowID)
{
  return _GetShadowMapCoord(iViewPos, iShadowID);
}

vec4 GetShadowMapCoord(int iShadowID)
{
  return GetShadowMapCoord(vGetViewPosition(), iShadowID);
}

//find face index using lightdir
int GetShadowFaceID(vec3 iViewPos, vec3 iLightPos)
{
  vec3 lightDir = iViewPos - iLightPos;

  lightDir = vec3(vGetViewInverseMatrix()  * vec4(lightDir, 0.0));

  int faceIndex;
  if (vAbs(lightDir.x) >= vAbs(lightDir.y) && vAbs(lightDir.x) >= vAbs(lightDir.z))
  {
    faceIndex = (lightDir.x > 0.0) ? 0 : 1;
  }
  else if (vAbs(lightDir.y) >= vAbs(lightDir.x) && vAbs(lightDir.y) >= vAbs(lightDir.z))
  {
    faceIndex = (lightDir.y > 0.0) ? 2 : 3;
  }
  else
  {
    faceIndex = (lightDir.z > 0.0) ? 4 : 5;
  }

  return faceIndex;
}

vec4 GetPointLightShadowCoord(vec3 iViewPos, int iShadowID, vec3 iLightPos)
{
  return _GetShadowMapCoord(iViewPos, iShadowID + GetShadowFaceID(iViewPos, iLightPos));
}

vec4 GetPointLightShadowCoord(int iShadowID, vec3 iLightPos)
{
  return GetPointLightShadowCoord(vGetViewPosition(), iShadowID, iLightPos);
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                        Cascade
//----------------------------------------------------------------------------------------------------------------------------------------------

#ifdef CascadedShadow

int GetCascade(vec3 iViewPos)
{
  int cascade = 0;

  float depth = -iViewPos.z;

  vec4 cascadedPlane1 = _sbcbCascadedShadow.cascadePlanes[0];
  vec4 cascadedPlane2 = _sbcbCascadedShadow.cascadePlanes[1];

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

int GetCascade()
{
  return GetCascade(vGetViewPosition());
}

float FadeLastCascade(int iCascadeID)
{
#if LastCascadeFadingFactor > 0
  if (NB_CASCADES - 1 == iCascadeID)
  {
    vec4 cascadedPlane1 = _sbcbCascadedShadow.cascadePlanes[0];
    vec4 cascadedPlane2 = _sbcbCascadedShadow.cascadePlanes[1];

    float depth = -vGetViewPosition().z;

    float nearPlane = 0;
    float farPlane = cascadedPlane1.x;

#if NB_CASCADES == 2
    nearPlane = cascadedPlane1.x;
    farPlane = cascadedPlane1.y;
#elif NB_CASCADES == 3
    nearPlane = cascadedPlane1.y;
    farPlane = cascadedPlane1.z;
#elif NB_CASCADES == 4
    nearPlane = cascadedPlane1.z;
    farPlane = cascadedPlane1.w;
#elif NB_CASCADES == 5
    nearPlane = cascadedPlane1.w;
    farPlane = cascadedPlane2.x;
#elif NB_CASCADES == 6
    nearPlane = cascadedPlane2.x;
    farPlane = cascadedPlane2.y;
#elif NB_CASCADES == 7
    nearPlane = cascadedPlane2.y;
    farPlane = cascadedPlane2.z;
#elif NB_CASCADES == 8
    nearPlane = cascadedPlane2.z;
    farPlane = cascadedPlane2.w;
#endif

    const float factor = float(LastCascadeFadingFactor) / 100.0;

    const float nearFarDistance = farPlane - nearPlane;

    const float startFadingZ = nearPlane + factor * nearFarDistance;
    const float startFadingZFarDistance = farPlane - startFadingZ;


    //The return is equivalent to the commented code below
    return vStep(startFadingZ, depth) * (depth - startFadingZ) / startFadingZFarDistance;
  }
#endif

  return 0.0;
}

vec3 DebugCascade(float iFragDepth)
{
  vec3 debugColor = vec3(1, 0, 0);

  int curCascade = GetCascade();

  if (curCascade == 1)
    debugColor = vec3(0, 1, 0);

  if (curCascade == 2)
    debugColor = vec3(0, 0, 1);

  if (curCascade == 3)
    debugColor = vec3(1, 1, 0);

  if (curCascade == 4)
    debugColor = vec3(1, 0, 1);

  if (curCascade == 5)
    debugColor = vec3(0, 1, 1);

  if (curCascade == 6)
    debugColor = vec3(1, 0.39, 0); //Orange

  if (curCascade == 7)
    debugColor = vec3(0.34, 0.16, 0); //Marron


  return debugColor;
}

#endif // CascadedShadow


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                        Services (used outside)
//----------------------------------------------------------------------------------------------------------------------------------------------

int GetShadowID(int iLightID)
{
#ifdef CascadedShadow
  int shadowID = iLightID;

  if (iLightID == CascadedShadowLightID)
    shadowID += GetCascade();
  else if (iLightID > CascadedShadowLightID)
    shadowID += (NB_CASCADES - 1);

  return shadowID;
#else
  return iLightID;
#endif
}

vec4 SampleShadowMapTex2(in vec4 coord)
{
#if defined(NonPointShadow) || defined(MultiNonPointShadows)
#if defined(PCF) && defined(SO_EVISUPBR_SUBSURFACE) || defined(ESM) || defined(PCSS)
  return SampleShadowTexture(shadowMapTex2, coord);
#else
  return vec4(0.0);
#endif
#else
  return vec4(0.0);
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                        PCF
//----------------------------------------------------------------------------------------------------------------------------------------------

float ComputePCFSample(bool iForPlane, vec4 iShadowMapCoord, vec2 iDz_duv, vec2 iOffset, vec2 iScale)
{
  vec2 offset = iOffset * iScale;

  vec4 shadowMapCoordProj;
  shadowMapCoordProj.xy = iShadowMapCoord.xy;
  shadowMapCoordProj.z = ApplyBiasedZ(iShadowMapCoord.z, iDz_duv, offset);
  shadowMapCoordProj.w = iShadowMapCoord.w;

  shadowMapCoordProj.xy += offset;

  if (iForPlane == true && iShadowMapCoord.z >= 1)
  {
    shadowMapCoordProj.z = 0.9; //DRef
  }

#if defined(NonPointShadow) || defined(MultiNonPointShadows)
  return SampleShadowTexture(shadowMapTex, shadowMapCoordProj);
#endif

  return 0;
}

// Derivatives of light-space depth with respect to texture2D coordinates
vec2 DepthGradient(vec2 uv, float z)
{
  vec2 dz_duv = vec2(0.0, 0.0);

  vec3 duvdist_dx = dFdx(vec3(uv, z));
  vec3 duvdist_dy = dFdy(vec3(uv, z));

  dz_duv.x = duvdist_dy.y * duvdist_dx.z;
  dz_duv.x -= duvdist_dx.y * duvdist_dy.z;

  dz_duv.y = duvdist_dx.x * duvdist_dy.z;
  dz_duv.y -= duvdist_dy.x * duvdist_dx.z;

  float det = (duvdist_dx.x * duvdist_dy.y) - (duvdist_dx.y * duvdist_dy.x);
  dz_duv /= det;

  return dz_duv;
}

//Define for PCF in case of PCSS
#if defined (PCSS_Filter_Poisson25)
#define NBShadowPCFSample 25
#define Poisson_PCF_Disk g_Poisson25
#elif defined (PCSS_Filter_Poisson32)
#define NBShadowPCFSample 32
#define Poisson_PCF_Disk g_Poisson32
#elif defined (PCSS_Filter_Poisson64)
#define NBShadowPCFSample 64
#define Poisson_PCF_Disk g_Poisson64
#elif defined (PCSS_Filter_Poisson100)
#define NBShadowPCFSample 100
#define Poisson_PCF_Disk g_Poisson100
#elif defined (PCSS_Filter_Poisson128)
#define NBShadowPCFSample 128
#define Poisson_PCF_Disk g_Poisson128
#endif //PCSS_Blocker


#ifndef Poisson_PCF_Disk
#define Poisson_PCF_Disk g_Poisson32
#endif

float PoissonPCF(bool iForPlane, vec2 iPoissonMultiplier, vec2 dz_duv, int iShadowID, const int iNbShadowSample)
{
  const int nbShadowSample = iNbShadowSample;

  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);
  curShadowMapCoord.w = iShadowID;

  float visibility = 0.;

  for (int i = 0; i < nbShadowSample; ++i)
  {
    visibility += ComputePCFSample(iForPlane, curShadowMapCoord, dz_duv, Poisson_PCF_Disk[i], iPoissonMultiplier);
  }

  return visibility / float(nbShadowSample);
}

float SimplePCF(bool iForPlane, vec2 dz_duv, int iShadowID, const int iNbShadowSample)
{
  float minV = 0.;
  float maxV = 0.;

  const int nbShadowSample = iNbShadowSample;

  if (nbShadowSample == 4)
  {
    minV = -0.5; maxV = 0.5;
  }
  else if (nbShadowSample == 9)
  {
    minV = -1.;
    maxV = 1.;
  }
  else if (nbShadowSample == 16)
  {
    minV = -1.5;
    maxV = 1.5;
  }
  else if (nbShadowSample == 25)
  {
    minV = -2.;
    maxV = 2.;
  }
  else if (nbShadowSample == 36)
  {
    minV = -2.5;
    maxV = 2.5;
  }
  else if (nbShadowSample == 49)
  {
    minV = -3.;
    maxV = 3.;
  }
  else if (nbShadowSample == 64)
  {
    minV = -3.5;
    maxV = 3.5;
  }
  else if (nbShadowSample == 81)
  {
    minV = -4.;
    maxV = 4.;
  }
  else if (nbShadowSample == 100)
  {
    minV = -4.5;
    maxV = 4.5;
  }
  else if (nbShadowSample == 121)
  {
    minV = -5.;
    maxV = 5.;
  }
  else if (nbShadowSample == 144)
  {
    minV = -5.5;
    maxV = 5.5;
  }

  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);
  curShadowMapCoord.w = iShadowID;

  float visibility = 0.;

  float i = 0.0;
  float j = 0.0;

  float pcfStep = 1. / float(ShadowMapResolution);
  vec2 offsetScale = vec2(pcfStep);

  for (i = minV; i <= maxV; i += 1.0)
  {
    for (j = minV; j <= maxV; j += 1.0)
    {
      visibility += ComputePCFSample(iForPlane, curShadowMapCoord, dz_duv, vec2(i, j), offsetScale);
    }
  }

  return visibility / float(nbShadowSample);
}

float OptimizedPCF(bool iForPlane, vec2 dz_duv, int iShadowID, const int iNbShadowSample)
{

  float minV = 0.;
  float maxV = 0.;

  const int nbShadowSample = iNbShadowSample;

  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);

  float i = 0.0;
  float j = 0.0;

  const float shadowMapSizeInv = 1. / float(ShadowMapResolution);

  vec2 uv = curShadowMapCoord.xy * ShadowMapResolution;

  vec2 base_uv;
  base_uv.x = floor(uv.x + 0.5);
  base_uv.y = floor(uv.y + 0.5);

  float s = (uv.x + 0.5 - base_uv.x);
  float t = (uv.y + 0.5 - base_uv.y);

  base_uv -= vec2(0.5, 0.5);
  base_uv *= shadowMapSizeInv;

  float sum = 0;

  vec4 shadowFetchPos = vec4(base_uv, curShadowMapCoord.z, iShadowID);
  vec2 offsetScale = vec2(shadowMapSizeInv);

#if NBShadowPCFSample <= 4 //Filter size is 2

  return ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(0, 0), offsetScale);

#elif NBShadowPCFSample <= 9  //Filter size is 3

  float uw0 = (3.0 - 2.0 * s);
  float uw1 = (1.0 + 2.0 * s);

  float u0 = (2.0 - s) / uw0 - 1.0;
  float u1 = s / uw1 + 1.0;

  float vw0 = (3.0 - 2.0 * t);
  float vw1 = (1.0 + 2.0 * t);

  float v0 = (2.0 - t) / vw0 - 1.0;
  float v1 = t / vw1 + 1.0;

  sum += uw0 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v0), offsetScale);
  sum += uw1 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v0), offsetScale);
  sum += uw0 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v1), offsetScale);
  sum += uw1 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v1), offsetScale);
  return sum * 1.0f / 16.0;

#elif NBShadowPCFSample <= 25 //Filter size is 5

  float uw0 = (4 - 3 * s);
  float uw1 = 7;
  float uw2 = (1 + 3 * s);

  float u0 = (3 - 2 * s) / uw0 - 2;
  float u1 = (3 + s) / uw1;
  float u2 = s / uw2 + 2;

  float vw0 = (4 - 3 * t);
  float vw1 = 7;
  float vw2 = (1 + 3 * t);

  float v0 = (3 - 2 * t) / vw0 - 2;
  float v1 = (3 + t) / vw1;
  float v2 = t / vw2 + 2;
   
  sum += uw0 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v0), offsetScale );
  sum += uw1 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v0), offsetScale );
  sum += uw2 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v0), offsetScale );
  sum += uw0 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v1), offsetScale );
  sum += uw1 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v1), offsetScale );
  sum += uw2 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v1), offsetScale );
  sum += uw0 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v2), offsetScale );
  sum += uw1 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v2), offsetScale );
  sum += uw2 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v2), offsetScale );

  return sum * 1.0f / 144;


#else  //Filter size is 7
  float uw0 = (5 * s - 6);
  float uw1 = (11 * s - 28);
  float uw2 = -(11 * s + 17);
  float uw3 = -(5 * s + 1);

  float u0 = (4 * s - 5) / uw0 - 3;
  float u1 = (4 * s - 16) / uw1 - 1;
  float u2 = -(7 * s + 5) / uw2 + 1;
  float u3 = -s / uw3 + 3;

  float vw0 = (5 * t - 6);
  float vw1 = (11 * t - 28);
  float vw2 = -(11 * t + 17);
  float vw3 = -(5 * t + 1);

  float v0 = (4 * t - 5) / vw0 - 3;
  float v1 = (4 * t - 16) / vw1 - 1;
  float v2 = -(7 * t + 5) / vw2 + 1;
  float v3 = -t / vw3 + 3;
   
  sum += uw0 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v0), offsetScale);
  sum += uw1 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v0), offsetScale);
  sum += uw2 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v0), offsetScale);
  sum += uw3 * vw0 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u3, v0), offsetScale);
  sum += uw0 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v1), offsetScale);
  sum += uw1 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v1), offsetScale);
  sum += uw2 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v1), offsetScale);
  sum += uw3 * vw1 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u3, v1), offsetScale);
  sum += uw0 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v2), offsetScale);
  sum += uw1 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v2), offsetScale);
  sum += uw2 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v2), offsetScale);
  sum += uw3 * vw2 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u3, v2), offsetScale);
  sum += uw0 * vw3 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u0, v3), offsetScale);
  sum += uw1 * vw3 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u1, v3), offsetScale);
  sum += uw2 * vw3 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u2, v3), offsetScale);
  sum += uw3 * vw3 * ComputePCFSample(iForPlane, shadowFetchPos, dz_duv, vec2(u3, v3), offsetScale);
  
  return sum * 1.0f / 2704;
#endif 
}

float SimplePCF(bool iForPlane, int iShadowID)
{
  vec4 uvz = GetShadowMapCoord(iShadowID);
  vec2 dzduv = DepthGradient(uvz.xy, uvz.z);

  return SimplePCF(iForPlane, dzduv, iShadowID, NBShadowPCFSample);
}

float PoissonPCF(bool iForPlane, int iShadowID)
{
  vec4 uvz = GetShadowMapCoord(iShadowID);
  vec2 dzduv = DepthGradient(uvz.xy, uvz.z);

  return PoissonPCF(iForPlane, vec2(2. / ShadowMapResolution), dzduv, iShadowID, NBShadowPCFSample);
}

float OptimizedPCF(bool iForPlane, int iShadowID)
{
  vec4 uvz = GetShadowMapCoord(iShadowID);
  vec2 dzduv = DepthGradient(uvz.xy, uvz.z);

  return OptimizedPCF(iForPlane, dzduv, iShadowID, NBShadowPCFSample);
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                        PCF (point light)
//----------------------------------------------------------------------------------------------------------------------------------------------

float SimplePCFPointLight(bool iForPlane, int iShadowID, const int iNbShadowSample, int iLightLayer, vec3 iLightPos)
{
  float offsetValue = 0.;

  const int nbShadowSample = iNbShadowSample;

  if (nbShadowSample == 4)
  {
    offsetValue = 0.2;
  }
  else if (nbShadowSample == 9)
  {
    offsetValue = 0.5;
  }
  else if (nbShadowSample == 36)
  {
    offsetValue = 1.3;
  }
  else if (nbShadowSample == 144)
  {
    offsetValue = 2.9;
  }

  vec4 curShadowMapCoord = GetPointLightShadowCoord(iShadowID, iLightPos);

  float visibility = 0.;

  float i = 0.0;
  float j = 0.0;

  vec3 lightDir = GetLightDir(iLightPos);
  float invShadowMapRes = 1. / float(ShadowMapResolution);

  for (i = -offsetValue; i <= offsetValue; i += 0.5)
  {
    for (j = -offsetValue; j <= offsetValue; j += 0.5)
    {
      vec3 offset = vec3(i, j, 0);
      float sampledDistance = 0.;
      float currentDistance = curShadowMapCoord.z;

      if (iForPlane == true && curShadowMapCoord.z >= 1.0)
        currentDistance = 0.9; //DRef

#if defined(PointLightShadows) || defined(MultiPointLightShadows)
      sampledDistance = SampleCubemapTex(ShadowCubeMapTex, (lightDir + offset), iLightLayer).r;
#endif

      visibility += (currentDistance > sampledDistance) ? 0.0 : 1.0;
    }
  }

  return visibility / float(nbShadowSample);
}


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                          ESM
//----------------------------------------------------------------------------------------------------------------------------------------------
#ifdef ESM

#define V_POW3_DOUBLE(x) x * x * x 

float SimpleESM(bool iForPlane, int iShadowID)
{
  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);

  float visibility = 0.;

#if defined(NonPointShadow) || defined(MultiNonPointShadows)
#ifndef CascadedShadow
  vec4 expFromLight = SampleShadowTexture(shadowMapESMTex, vec4(curShadowMapCoord.xy, iShadowID, 0));
#else
  vec4 expFromLight = textureLod(shadowMapESMTex, vec3(curShadowMapCoord.xy, iShadowID), 0);
#endif

  float offsetZ = curShadowMapCoord.z - 0.001;

  double a = exp(-80.0 * offsetZ);
  a = V_POW3_DOUBLE(a);

  double bDouble = expFromLight.x;
  double b = V_POW3_DOUBLE(bDouble);

  visibility = float(a * b);

  float invShadowMapRes = 1. / float(ShadowMapResolution);

#ifdef ESM_THRESHOLD

  vec4 samplerPos = curShadowMapCoord;
  float myMax = 0;

#ifndef ESM_PRECOMPUTEDMAP
  const int detectionKernel = 4;

  for (int i = -detectionKernel; i <= detectionKernel; ++i)
  {
    for (int j = -detectionKernel; j <= detectionKernel; ++j)
    {
      vec4 samplingPos = vec4(samplerPos.xy + vec2(i * invShadowMapRes, j * invShadowMapRes), iShadowID, 0);

      myMax = max(myMax, SampleShadowTexture(shadowMapTex2, samplingPos).x);
    }
  }
#else
  myMax = SampleShadowTexture(shadowMapMaxZTex, samplerPos).x;
#endif //ESM_PRECOMPUTEDMAP

  if (curShadowMapCoord.z + 0.03 < myMax)
  {
    visibility = SimplePCF(false, iShadowID);
  }

#endif //ESM_THRESHOLD
#endif

  return clamp(visibility, 0, 1);
}

#endif //ESM

//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                          ESM (point light)
//----------------------------------------------------------------------------------------------------------------------------------------------

#ifdef ESM

float SimpleESMPointLight(bool iForPlane, int iShadowID, int iLightLayer, vec3 iLightPos)
{
  vec4 curShadowMapCoord = GetPointLightShadowCoord(iShadowID, iLightPos);
  vec3 lightDir = GetLightDir(iLightPos);
  float visibility = 0.;

#if defined(PointLightShadows) || defined(MultiPointLightShadows)
  vec4 expFromLight = SampleCubemapTex(ShadowCubeMapESMTex, lightDir, iLightLayer);

  float offsetZ = curShadowMapCoord.z - 0.001;

  double a = exp(-80.0 * offsetZ);
  a = V_POW3_DOUBLE(a);

  double bDouble = expFromLight.x;
  double b = V_POW3_DOUBLE(bDouble);

  visibility = float(a * b);

#ifdef ESM_THRESHOLD

  float myMax = 0;
  const float detectionKernel = 1.3;

  for (float i = -detectionKernel; i <= detectionKernel; i += 0.5)
    for (float j = -detectionKernel; j <= detectionKernel; j += 0.5)
    {
      vec3 offset = vec3(i, j, 0);
      float sampledDistance = 0;
#if defined(PointLightShadows) || defined(MultiPointLightShadows)
      sampledDistance = SampleCubemapTex(ShadowCubeMapTex, (lightDir + offset), iLightLayer).r;
#endif
      myMax = max(myMax, sampledDistance);
    }

  if (curShadowMapCoord.z + 0.03 < myMax)
  {
    //discard; //uncomment this to see the threshold (debug feature)

    visibility = SimplePCFPointLight(iForPlane, iShadowID, 9, iLightLayer, iLightPos); // NBShadowPCFSample 9
  }

#endif //ESM_THRESHOLD
#endif

  return clamp(visibility, 0, 1);
}
#endif //ESM


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                          PCSS
//----------------------------------------------------------------------------------------------------------------------------------------------
#ifdef PCSS

////// PCSS Defines ////////

//Define for search blocker parts
#if defined (PCSS_Blocker_Poisson25)
#define PCSS_Blocker_Poisson_NbSample 25
#define PCSS_Blocker_Poisson_Disk g_Poisson25
#elif defined (PCSS_Blocker_Poisson32)
#define PCSS_Blocker_Poisson_NbSample 32
#define PCSS_Blocker_Poisson_Disk g_Poisson32
#elif defined (PCSS_Blocker_Poisson64)
#define PCSS_Blocker_Poisson_NbSample 64
#define PCSS_Blocker_Poisson_Disk g_Poisson64
#elif defined (PCSS_Blocker_Poisson100)
#define PCSS_Blocker_Poisson_NbSample 100
#define PCSS_Blocker_Poisson_Disk g_Poisson100
#elif defined (PCSS_Blocker_Poisson128)
#define PCSS_Blocker_Poisson_NbSample 128
#define PCSS_Blocker_Poisson_Disk g_Poisson128
#else
ERROR: No Poisson blocker is defined !;
#endif //PCSS_Blocker


vec2 searchRegionRadiusUV(float zWorld, int iShadowID)
{
  float lightNear = GetLightNear(iShadowID);

  vec2  lightRadiusUV = GetLightDirRadius(iShadowID);

  return lightRadiusUV * (zWorld - lightNear) / zWorld;
}

// Using similar triangles between the area light, the blocking plane and the surface point
vec2 penumbraRadiusUV(float zReceiver, float zBlocker, int iShadowID)
{
  vec2  lightRadiusUV = GetLightDirRadius(iShadowID);

  return lightRadiusUV * (zReceiver - zBlocker) / zBlocker;
}

// Project UV size to the near plane of the light
vec2 projectToLightUV(vec2 sizeUV, float zWorld, int iShadowID)
{
  float lightNear = GetLightNear(iShadowID);

  return sizeUV * lightNear / zWorld;
}

void findBlocker(out float accumBlockerDepth,
  out int   numBlockers,
  vec2 uv,
  float z0,
  vec2 dz_duv,
  vec2 searchRegionRadiusUV,
  int iShadowID
)
{
  accumBlockerDepth = 0.0;
  numBlockers = 0;

  for (int i = 0; i < PCSS_Blocker_Poisson_NbSample; ++i)
  {
    vec2 offset = PCSS_Blocker_Poisson_Disk[i] * searchRegionRadiusUV;

    vec4 samplingPos;

    samplingPos.xy = uv + offset;
    samplingPos.z = iShadowID;

    float shadowMapDepth = 0.0;
#if defined(NonPointShadow) || defined(MultiNonPointShadows)
    shadowMapDepth = SampleShadowTexture(shadowMapTex2, samplingPos).x;
#endif
    float z = ApplyBiasedZ(z0, dz_duv, offset);
    if (shadowMapDepth < z)
    {
      accumBlockerDepth += shadowMapDepth;
      numBlockers++;
    }
  }
}

float SimplePCSS(bool iForPlane, int iShadowID)
{
  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);

  vec2 uv = curShadowMapCoord.xy;
  float z = curShadowMapCoord.z;

  vec2 dz_duv = DepthGradient(uv, z);
  float zEye = ZClipToEye(z, iShadowID);

  // ------------------------
  // STEP 1: blocker search
  // ------------------------
  float accumBlockerDepth;
  int numBlockers;
  vec2 searchRegionRadiusUV = searchRegionRadiusUV(zEye, iShadowID);

  findBlocker(accumBlockerDepth, numBlockers, uv, z, dz_duv, searchRegionRadiusUV, iShadowID);

#ifdef PCSS_DEBUG_OCCLUDER
  return vClamp(1 - numBlockers / 10.0f, 0, 1);
#endif

  // Early out if not in the penumbra
  if (numBlockers == 0)
    return 1.0;

  // ------------------------
  // STEP 2: penumbra size
  // ------------------------
  float avgBlockerDepth = accumBlockerDepth / numBlockers;
  float avgBlockerDepthWorld = ZClipToEye(avgBlockerDepth, iShadowID);
  vec2 penumbraRadius = penumbraRadiusUV(zEye, avgBlockerDepthWorld, iShadowID);
  vec2 filterRadius = projectToLightUV(penumbraRadius, zEye, iShadowID);

  // ------------------------
  // STEP 3: filtering
  // ------------------------

  return PoissonPCF(iForPlane, filterRadius, dz_duv, iShadowID, NBShadowPCFSample);
}

#endif //PCSS



//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                          Main methods to Compute Shadow visiblity
//----------------------------------------------------------------------------------------------------------------------------------------------

float _ComputeShadowsAlgo(bool iForPlane, int iShadowID)
{
  float visibility = 0.;
  int   cascadeID = 0;
  int   shadowID = iShadowID;

#ifdef CascadedShadow
  if (iShadowID == CascadedShadowLightID)
  {
    cascadeID = GetCascade();
    shadowID += cascadeID;
  }
#endif

#ifdef PCF

  //--------------------
  // PCF
  //--------------------

#ifdef PoissonSampling
  visibility = PoissonPCF(iForPlane, shadowID);
#elif defined OptimizedSampling
  visibility = OptimizedPCF(iForPlane, shadowID);
#else //basic PCF
  visibility = SimplePCF(iForPlane, shadowID);
#endif

  visibility *= 1.3;

#elif defined(ESM) 

  //--------------------
  // ESM
  //--------------------

  visibility = SimpleESM(iForPlane, shadowID);

#elif defined(PCSS)

  //--------------------
  // PCSS
  //--------------------

  visibility = SimplePCSS(iForPlane, shadowID);
  visibility *= 1.3;

#endif

#ifdef CascadedShadow
  if (iShadowID == CascadedShadowLightID)
  {
    visibility += FadeLastCascade(cascadeID);
  }
#endif

  visibility = vClamp(visibility, 0., 1.);

  return visibility;
}

float ComputeShadows(int iShadowID)
{
  return _ComputeShadowsAlgo(false, iShadowID);
}

float _ComputePointLightShadowsAlgo(bool iForPlane, int iShadowID, int iLightLayer, vec3 iLightPos)
{
  float visibility = 0.;

#ifdef ESM
  //--------------------
  // ESM
  //--------------------

  visibility = SimpleESMPointLight(iForPlane, iShadowID, iLightLayer, iLightPos);
#else

  //--------------------
  // PCF
  // NB: PCSS isn't taken into account
  //--------------------

  visibility = SimplePCFPointLight(iForPlane, iShadowID, NBShadowPCFSample, iLightLayer, iLightPos);
  visibility *= 1.3;
#endif

  visibility = vClamp(visibility, 0., 1.);
  return visibility;
}

float ComputePointLightShadows(int iShadowID, int iLightLayer, vec3 iLightPos)
{
  return _ComputePointLightShadowsAlgo(false, iShadowID, iLightLayer, iLightPos);
}


//----------------------------------------------------------------------------------------------------------------------------------------------
//                                                          Transparent Shadows
//----------------------------------------------------------------------------------------------------------------------------------------------


vec4 TransparentShadowCubeFilter(bool iForPlane, int iShadowID, const int iNbShadowSample, int iLightLayer, vec3 iLightPos)
{
#if defined(TransparentShadow) && (defined(PointLightShadows) || defined(MultiPointLightShadows))

  float offsetValue = 0.;

  int nbShadowSample = iNbShadowSample;

  if (nbShadowSample == 4)
  {
    offsetValue = 0.2;
  }
  else if (nbShadowSample == 9)
  {
    offsetValue = 0.5;
  }
  else if (nbShadowSample == 36)
  {
    offsetValue = 1.3;
  }
  else if (nbShadowSample == 144)
  {
    offsetValue = 2.9;
  }

  vec4 curShadowMapCoord = GetPointLightShadowCoord(iShadowID, iLightPos);

  vec4 outputColor = vec4(0.);

  float i = 0.0;
  float j = 0.0;

  vec3 lightDir = GetLightDir(iLightPos);
  float invShadowMapRes = 1. / float(ShadowMapResolution);

  for (i = -offsetValue; i <= offsetValue; i += 0.5)
  {
    for (j = -offsetValue; j <= offsetValue; j += 0.5)
    {
      vec3 offset = vec3(i, j, 0);
      vec4 sampleFrag = vec4(0.);

#if defined(PointLightShadows) || defined(MultiPointLightShadows)
      sampleFrag = SampleCubemapTex(transparentShadowCubeMapTex, (lightDir + offset), iLightLayer);
#endif

      outputColor += sampleFrag;
    }
  }
  return outputColor / float(nbShadowSample);
#endif //TransparentShadow
  return vec4(1.0);
}

vec4 GetTransparentShadowMapPointLight(vec3 iLightPos, int iShadowID, int iLightLayer)
{
#if defined(TransparentShadow) && (defined(PointLightShadows) || defined(MultiPointLightShadows))
  vec3 lightDir = GetLightDir(iLightPos);
#ifdef PCF
  return TransparentShadowCubeFilter(false, iShadowID, NBShadowPCFSample, iLightLayer, iLightPos);
#else
  return TransparentShadowCubeFilter(false, iShadowID, 9, iLightLayer, iLightPos);  // fix no of samples for other than PCF
#endif
#endif //TransparentShadow
  return vec4(1.0);
}

vec4 SimpleTransparentShadow(bool iForPlane, int iShadowID)
{
  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);

  vec4 shadowColor = vec4(1.);

#if defined(TransparentShadow) && (defined(NonPointShadow) || defined(MultiNonPointShadows))
#ifndef CascadedShadow
  shadowColor = SampleShadowTexture(transparentShadowMapTex, vec4(curShadowMapCoord.xy, iShadowID, 0));
#else
  shadowColor = textureLod(transparentShadowMapTex, vec3(curShadowMapCoord.xy, iShadowID), 0);
#endif
#endif //TransparentShadow
  return shadowColor;
}

vec4 PCFTransparentShadow(bool iForPlane, int iShadowID, const int iNbShadowSample)
{
  float minV = 0.;
  float maxV = 0.;

  int nbShadowSample = iNbShadowSample;

  if (nbShadowSample == 4)
  {
    minV = -0.5; maxV = 0.5;
  }
  else if (nbShadowSample == 9)
  {
    minV = -1.;
    maxV = 1.;
  }
  else if (nbShadowSample == 16)
  {
    minV = -1.5;
    maxV = 1.5;
  }
  else if (nbShadowSample == 25)
  {
    minV = -2.;
    maxV = 2.;
  }
  else if (nbShadowSample == 36)
  {
    minV = -2.5;
    maxV = 2.5;
  }
  else if (nbShadowSample == 49)
  {
    minV = -3.;
    maxV = 3.;
  }
  else if (nbShadowSample == 64)
  {
    minV = -3.5;
    maxV = 3.5;
  }
  else if (nbShadowSample == 81)
  {
    minV = -4.;
    maxV = 4.;
  }
  else if (nbShadowSample == 100)
  {
    minV = -4.5;
    maxV = 4.5;
  }
  else if (nbShadowSample == 121)
  {
    minV = -5.;
    maxV = 5.;
  }
  else if (nbShadowSample == 144)
  {
    minV = -5.5;
    maxV = 5.5;
  }

  vec4 curShadowMapCoord = GetShadowMapCoord(iShadowID);

  float i = 0.0;
  float j = 0.0;

  float pcfStep = 1. / float(ShadowMapResolution);
  vec4 shadowColor = vec4(0.);
  for (i = minV; i <= maxV; i += 1.0)
  {
    for (j = minV; j <= maxV; j += 1.0)
    {
      vec4 shadowMapCoordProj = curShadowMapCoord;

      vec2 offset = vec2(i, j) * pcfStep;

      shadowMapCoordProj.xy += offset;

#if defined(TransparentShadow) && (defined(NonPointShadow) || defined(MultiNonPointShadows))
#ifndef CascadedShadow
      shadowColor += SampleShadowTexture(transparentShadowMapTex, vec4(shadowMapCoordProj.xy, iShadowID, 0));
#else
      shadowColor += textureLod(transparentShadowMapTex, vec3(shadowMapCoordProj.xy, iShadowID), 0);
#endif
#endif //TransparentShadow

    }
  }
  return shadowColor / float(nbShadowSample);
}

vec4 GetTransparentShadowMap(int iShadowID)
{
  int shadowID = iShadowID;
#if defined(TransparentShadow) && (defined(NonPointShadow) || defined(MultiNonPointShadows))
#ifdef CascadedShadow
  if (iShadowID == CascadedShadowLightID)
  {
    shadowID += GetCascade();
  }
#endif 

#ifdef PCF
  return PCFTransparentShadow(false, shadowID, NBShadowPCFSample);
#else  
  return SimpleTransparentShadow(false, shadowID);
#endif 

#endif //TransparentShadow 

  return vec4(1.);
}

#endif //ShadowMap
