
#ifndef NUM_SSAO_SMOOTH_SAMPLE
#define NUM_SSAO_SMOOTH_SAMPLE 7
#endif

struct SmoothAOData
{
  float globalOcc;
  float globalRatio;
#ifndef BLUR_MODE_EXP2
  float ratio;
#endif

#ifdef BLUR_DETECTION_FROM_Z
  float zStrength;
#ifdef AO_OPTIM_MIX_AO_AND_ZMAP
  float mainDeltaZ;
#else
  float zRef;
#endif
#endif

#ifdef BLUR_DETECTION_FROM_NORMAL
  vec3  normalRef;
#endif
};

vec2 ComputeCoord(const int iIndex)
{
#ifdef SMOOTH_AO_Y
  vec2 index = vec2(0, iIndex);
#else
  vec2 index = vec2(iIndex, 0);
#endif

  return vFma(index, cb_PostEffect_SSAO.u_PixelSize.xy, vTexCoord);
}

void SmoothAO(const vec2 iCoord, const float iOcc, const float iIndex, inout SmoothAOData ioData)
{
  float ratio = 1.0;
#ifndef BLUR_MODE_EXP2
  ratio = ioData.ratio;
#endif

#ifdef BLUR_DETECTION_FROM_Z

#ifdef AO_OPTIM_MIX_AO_AND_ZMAP
  float mainDeltaZ = ioData.mainDeltaZ;
#else
  float z = GetZ(iCoord);
  z = -ConvertZBufferToZView(z);
  float mainDeltaZ = z - ioData.zRef;
#endif

  float deltaDepth = vAbs(mainDeltaZ)*ioData.zStrength;

#endif

#ifdef BLUR_MODE_EXP2

  const float BlurSigma = float(NUM_SSAO_SMOOTH_SAMPLE) * 0.5;
  const float BlurFalloff = 1.0 / (2.0*BlurSigma*BlurSigma);

  ratio = iIndex*iIndex*BlurFalloff;

#ifdef BLUR_DETECTION_FROM_Z
  ratio += deltaDepth*deltaDepth*cb_PostEffect_SSAO.u_EdgeDetectionZRatio;
#endif

  ratio = vExp2(-ratio);

#else

#ifdef BLUR_DETECTION_FROM_Z
  deltaDepth = 1.0 / (1.0 + deltaDepth);
  deltaDepth = vMix(1.0, deltaDepth, cb_PostEffect_SSAO.u_EdgeDetectionZRatio);
  ratio *= deltaDepth;
#endif

#endif

  //----------------------------------------
  // Edge Detection from Normal

#ifdef BLUR_DETECTION_FROM_NORMAL
  vec3 n = GetNormal(iCoord).xyz;
  ratio *= vMix(1.0, vClamp(vDot(n, ioData.normalRef), 0.0, 1.0), cb_PostEffect_SSAO.u_EdgeDetectionNormalRatio);
#endif


  //--------------------------------------
  // Global ratio/occ

  ioData.globalOcc = vFma(ratio, iOcc, ioData.globalOcc);
  ioData.globalRatio += ratio;

#ifndef BLUR_MODE_EXP2
  ioData.ratio = ratio;
#endif
}

void SmoothAO_Positive(const int iIndex, inout SmoothAOData ioData)
{
  //--------------------------------------
  // Retrieve AO and deltaZ

  vec2 coord = ComputeCoord(iIndex);
  vec2 occ = GetEffectTexture(s_AoMap, coord).xy;

  //--------------------------------------
  // Smmooth AO

  SmoothAO(coord, occ.x, iIndex, ioData);

  //--------------------------------------
  // Optim DeltaZ

#ifdef AO_OPTIM_MIX_AO_AND_ZMAP
  ioData.mainDeltaZ += occ.y;
#endif
}


void SmoothAO_Negative(const int iIndex, inout SmoothAOData ioData)
{
  //--------------------------------------
  // Retrieve AO and deltaZ

  vec2 coord = ComputeCoord(iIndex);
  vec2 occ = GetEffectTexture(s_AoMap, coord).xy;

  //--------------------------------------
  // Optim DeltaZ

#ifdef AO_OPTIM_MIX_AO_AND_ZMAP
  ioData.mainDeltaZ += occ.y;
#endif

  //--------------------------------------
  // Smmoth AO

  SmoothAO(coord, occ.x, iIndex, ioData);
}


void main()
{ 
  float globalOcc = 0.0;

  vec3  pt;
  float radius        = 0.0;
  float screenRadius  = 0.0;
  if (ComputePointAndRadiusInViewSpace(vTexCoord.xy, pt, radius, screenRadius)==true) 
  {
    vec2 occ = GetEffectTexture(s_AoMap, vTexCoord).xy;

    SmoothAOData smoothAOData;
    smoothAOData.globalOcc    = occ.x;
    smoothAOData.globalRatio  = 1.0;

#ifdef BLUR_DETECTION_FROM_Z
#ifdef AO_OPTIM_MIX_AO_AND_ZMAP
    smoothAOData.mainDeltaZ = occ.y;
#else
    smoothAOData.zRef        = pt.z;
#endif
    smoothAOData.zStrength  = cb_PostEffect_SSAO.u_EdgeDetectionZStrength/radius;
#endif

#ifdef BLUR_DETECTION_FROM_NORMAL
    smoothAOData.normalRef = GetNormal(vTexCoord.xy).xyz;
#endif
    
#ifndef BLUR_MODE_EXP2
    smoothAOData.ratio = 1.0;
#endif     
                    
    int i = 0;
    for (i=1; i<=NUM_SSAO_SMOOTH_SAMPLE; i++)
    {
      SmoothAO_Positive(i, smoothAOData);
    }

#ifndef BLUR_MODE_EXP2
    smoothAOData.ratio = 1.0;
#endif

#ifdef AO_OPTIM_MIX_AO_AND_ZMAP
    smoothAOData.mainDeltaZ   = 0.0;
#endif

    for (i=1; i<=NUM_SSAO_SMOOTH_SAMPLE; i++)
    {
      SmoothAO_Negative(-i, smoothAOData);
    }

    globalOcc  = smoothAOData.globalOcc /smoothAOData.globalRatio;
  }
  
#ifdef AO_WRITE_DELTAZ
  float z2 = GetZ(vTexCoord + vec2(0.0, cb_PostEffect_SSAO.u_PixelSize.y));
  z2 = -ConvertZBufferToZView(z2);

  FRAGCOLOR = vec4(globalOcc, z2-pt.z, 0.0, 0.0);
#else
  FRAGCOLOR = vec4(globalOcc, globalOcc, globalOcc, 0.0);
#endif
}




