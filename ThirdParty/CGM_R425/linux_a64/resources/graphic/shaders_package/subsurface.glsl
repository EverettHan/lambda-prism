#ifdef SO_EVISUPBR_SUBSURFACE

  #define MINR (2.0)
  #define MAXR (16.0)

  #define MINC (1.0/MAXR)
  #define MAXC (1.0/MINR)

  #define MIND 0.5
  #define MAXD 16.0

  #ifdef ShadowMap

    #define TRANS_PERFMODE 2

    #if TRANS_PERFMODE == 0
      #define TRANS_SAMPLE 64
      #define TRANS_POISSON_DISK  getPoissonSample64
    #elif TRANS_PERFMODE == 1
      #define TRANS_SAMPLE 32
      #define TRANS_POISSON_DISK  getPoissonSample32
    #else
      #define TRANS_SAMPLE 25
      #define TRANS_POISSON_DISK  getPoissonSample25
    #endif

    int  GetShadowID(int iLightID);
    vec4 SampleShadowMapTex2(in vec4 coord);
    vec4 GetShadowMapCoord(int iShadowID);
    float ZClipToEye(float z, int iLayer);
    vec2 getPoissonSample25(in int ind);
    vec2 getPoissonSample32(in int ind);
    vec2 getPoissonSample64(in int ind);

    float getDepthValue(in int iShadowID, in vec2 coord)
    {
      return SampleShadowMapTex2(vec4(coord, iShadowID, 0.0)).x;
    }

    vec3 translucencyValue(in float s)
    {
      vec2 coord = vec2(vToTexCoord(s, MIND, MAXD), 0.5);
      return texture2D(translucency_sss_map, coord).rgb;
    }

    vec3 multiSampleTranslucency(in int iLightID)
    {
      int shadowID = GetShadowID(iLightID);

      vec3 depthMapCoord = GetShadowMapCoord(shadowID).xyz;
      float depth2 = getDepthValue(shadowID, depthMapCoord.xy);

      vec2 currentCoord;
      float currentDepth = ZClipToEye(2.0 * depthMapCoord.z - 1.0, shadowID);

      mat3 mat = transpose(mat3(_vPrivGetWorldMatrix()));
      vec3 worldScaling = 1.0 / vec3(length(mat[0]), length(mat[1]), length(mat[2]));

      vec3 res = vec3(0.0);

      for (int i = 0; i < TRANS_SAMPLE; i++)
      {
        vec2 offset =  (1.5/float(ShadowMapResolution)) * TRANS_POISSON_DISK(i);
        currentCoord.xy = clamp(depthMapCoord.xy + offset, vec2(0.0), vec2(1.0));
        float depth = 2.0 * getDepthValue(shadowID, currentCoord.xy) - 1.0;
        float s = max( currentDepth - ZClipToEye(depth, shadowID), 0.0);
        res += translucencyValue(worldScaling[0] * s);
      }

      return res / float(TRANS_SAMPLE);
    }

    vec3 translucencyBRDF(in vec3 N, in vec3 L, in int iLightIndex, in vec3 V, in vec3 diffuseColor,  in vec3 sr0Color, in vec3 sr90Color)
    {
      //return multiSampleTranslucency(iLightIndex);

      vec3 Lt = L - 2.0 * dot(L,N) * N;
      float mcdirNoL = clamp(dot(N, Lt)+0.3, 0.0, 1.0);
      vec3 attenuation = multiSampleTranslucency(iLightIndex);
      vec3 Ht = normalize(Lt+V);
      vec3 fTrans = fresnel_schlick(sr0Color, sr90Color, clamp(dot(Ht,V), 0.0, 1.0));

      return mcdirNoL * attenuation * diffuseColor * (vec3(1.0) - fTrans) * INV_PI;
    }

  #else //ShadowMap

    vec3 translucencyBRDF(in vec3 N, in vec3 L, in int iLightIndex, in vec3 V, in vec3 diffuseColor,  in vec3 sr0Color, in vec3 sr90Color)
    {
      return vec3(0.0);
    }

  #endif

  vec3 getScattering(in float NoL, in float c)
  {
    float cNoL = vAffine(NoL, 0.51, 0.99);
    float cC = vToTexCoord(0.5, MINC, MAXC);
    vec2 coord = vec2(cC, 1.0-cNoL);
    return vTexture(sss_map, coord).rgb;
  }

  vec3 SssLUTSampling(in float c)
  {
    float cC = vToTexCoord(ceil(c), MINC, MAXC);
    vec2 coord = vec2(0.5, cC);
    return vTexture(sssIBL_map, coord).rgb;
  }

#endif //SO_EVISUPBR_SUBSURFACE
