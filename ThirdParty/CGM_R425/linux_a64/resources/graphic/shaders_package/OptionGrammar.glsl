/******************************************************************************************************************************/
/**********************************SMALL GRAMMAR WHICH MANGES SOME GENERIC OPTIONS ********************************************/

#if defined(ClosestHitStage) || defined(AnyHitStage)
  #define RayHitStage
  #define V_IN
  #define V_OUT
#else
  #define V_IN in
  #define V_OUT out
#endif

#ifdef OutputNormalMap
  #ifndef SO_MRT_LOCATION_FRAGNORMAL
    #undef OutputNormalMap
  #endif
#endif

// handle alternate definition here, because shaders are often mixed up
#if defined(LogDepth) && !defined(LOG_DEPTH)
# define LOG_DEPTH
#elif defined(LOG_DEPTH) && !defined(LogDepth)
# define LogDepth
#endif

#if (!defined(FragmentStage) || defined(GENERATE_SHADOWMAP) || defined(GLES2Platform))

#ifdef FragmentDepthOffsetForLines
#undef FragmentDepthOffsetForLines
#endif

#ifdef FragmentDepthOffsetForSurface
#undef FragmentDepthOffsetForSurface
#endif

#ifdef FragmentDepthOffsetForLogZ
#undef FragmentDepthOffsetForLogZ
#endif

#endif

#if defined(FragmentDepthOffsetForLines) && (!defined(UseFragmentDepthOffset))
#undef FragmentDepthOffsetForLines
#endif

#if defined(NoNormalAndLighting)
#define NoNormal 1
#ifdef Lighting
# undef Lighting
#endif
#endif

#define GLSLVersion __VERSION__

/************************************************************* GLSL type ***********************************************************************/
#if defined(GLES2Platform) || defined(GLES3Platform)
#define GLESPlatform
#endif

#ifdef GLESPlatform
#ifdef SO_EVISUPBR_SUBSURFACE
#undef SO_EVISUPBR_SUBSURFACE
#endif
#endif //GLESPlatform

/************************************************************* GLES2 **************************************************************************/
#if defined(GLES2Platform)

#ifdef AnisotropicDistribution
#undef AnisotropicDistribution
#endif

#ifdef normalMapEnabled
#undef normalMapEnabled
#endif

#ifdef Fabrics
#undef Fabrics
#endif

#ifdef coatingNormalMapEnabled
#undef coatingNormalMapEnabled
#endif
#ifdef Flakes
#undef Flakes
#endif

#ifndef V_DISABLE_GLOSSINESS_SMOOTHING
#define V_DISABLE_GLOSSINESS_SMOOTHING
#endif

#if defined(MappingOperator) 
#undef MappingOperator
#define MappingOperator 0 //Mapping operator are only cpu on ios
#endif

#endif

/************************************* PHYSICAL MAT : Mapping operaotr might become generic **************************************/
#if defined(MappingOperator) 
#if (MappingOperator > 0) 
#define GPUMappingOperator
#endif
#endif

#if !defined GPUMappingOperator && defined heightMapEnabled
#undef heightMapEnabled
#endif

///////// Remove fabrics type if fabrics not defined
#ifndef Fabrics
  #ifdef UseVelvet
    #undef UseVelvet
  #endif
  #ifdef UseSilkVelvet
    #undef UseSilkVelvet
  #endif
  #ifdef UseSatin
    #undef UseSatin
  #endif
#endif

/////// Disable flakes and coating if in fabrics mode or SSS mode
#if defined(Fabrics) || defined(SSS)
  #ifdef Flakes
    #undef Flakes
  #endif // Flakes
  #ifdef Coating
    #undef Coating
    #ifdef coatingNormalMapEnabled
      #undef coatingNormalMapEnabled
    #endif
  #endif // Coating
#endif // defined(Fabrics) ||defined(SSS)

///////////// COATING
#if defined(ProceduralCoating) && !defined(Coating)
	#undef ProceduralCoating
#endif

#if defined(ProceduralCoating) && defined(coatingNormalMapEnabled)
	#undef coatingNormalMapEnabled
#endif

#if defined(FLAKES_PERFORMANCE_MODE)
  #if FLAKES_PERFORMANCE_MODE == 0 //Low
    #if defined(Flakes) 
      #undef Flakes
    #endif
  #elif FLAKES_PERFORMANCE_MODE == 1 //Medium
    #ifndef INTERNAL_FLAKES_PERFORMANCE_MODE
      #define INTERNAL_FLAKES_PERFORMANCE_MODE 2
    #endif
  #elif FLAKES_PERFORMANCE_MODE == 2 //High
    #ifndef INTERNAL_FLAKES_PERFORMANCE_MODE
      #define INTERNAL_FLAKES_PERFORMANCE_MODE 1
    #endif
  #else //FLAKES_PERFORMANCE_MODE == 3 //Ultra
    #ifndef INTERNAL_FLAKES_PERFORMANCE_MODE
      #define INTERNAL_FLAKES_PERFORMANCE_MODE 0
    #endif
  #endif
#endif

/////////////// NOISE
#if defined(Flakes) || defined(ProceduralCoating)
	#define Noise
#endif

///////////

#ifdef PDSFX0
#define _PDSFX 0
#endif
#ifdef PDSFX1
#define _PDSFX 1
#endif

#if defined(AnisotropicDistribution) || defined(normalMapEnabled) || defined(heightMapEnabled)\
    || defined(Flakes) || defined(coatingNormalMapEnabled) || defined(EVisuPBR) || defined(XRiteCarPaint2)
#ifndef NeedTangentSpace
#define NeedTangentSpace 
#endif
#endif

#if defined(normalMapEnabled) || defined(Flakes) || defined(coatingNormalMapEnabled)
#ifndef V_DISABLE_GLOSSINESS_SMOOTHING
#define V_DISABLE_GLOSSINESS_SMOOTHING //Disable glossiness smoothing when normal map is applied (too ugly)
#endif
#endif
 
#ifdef NeedTangentSpace
  #ifndef GPUMappingOperator
    #if (defined(NeedTangent) && defined(NeedBinormal)) || (defined(_PDSFX1_VS_Tangent) && defined(_PDSFX1_VS_Binormal))
      #define UseTangentSpace
    #else //No attribs : generate tangent space
      #ifndef TangentSpaceGeneration
        #define TangentSpaceGeneration
      #endif
    #endif
  #endif
#endif

#ifdef NoInterObjShadows
#undef ShadowMap
#endif

#ifdef NoInterObjReflections
#ifndef DiscardF0RoughPixel
#define DiscardF0RoughPixel 1
#endif
#endif

#ifdef IBLLocal
#ifndef ImageBasedLighting
#define ImageBasedLighting 1
#endif
#endif

#ifdef IBLDefaultCorrection
#ifdef IBLLocal
#undef IBLDefaultCorrection
#else
#ifndef IBLParallaxCorrection
#define IBLParallaxCorrection IBLDefaultCorrection
#else
#undef IBLDefaultCorrection
#endif
#endif
#endif

#if !defined _PDSFX_NOLIGHTING && defined(StdLighting) && !defined(NoNormalAndLighting)
#if defined(TiledLighting) || defined(ImageBasedLighting) || defined(StdLighting)
#ifndef Lighting
#define Lighting 1
#if !defined(ImageBasedLighting)
#define LegacyGlobalIllumination
#endif
#endif
#endif
#endif

#ifdef StdLighting
#if defined(FragmentStage) || defined(RayHitStage)
#define LightingStage
#endif
#endif

#if !defined(NoNormal) && ( defined(Lighting) || defined(NeedTangentSpace) || defined(ShadowMap) || defined(WeightedAverage) || defined(OutputNormalMap) || defined(Mirroring) || defined(HighlightAdvanced) || defined(_PDSFX))
#ifndef UseNormal
#define UseNormal 1
#endif
#endif

// Normal compression
#if defined(UseNormal) && (UseNormal)
  #if defined(NormalCompressBit0)
    #undef NormalCompressBit0
    #define NormalCompressBit0 1
  #else
    #define NormalCompressBit0 0
  #endif

  #if defined(NormalCompressBit1)
    #undef NormalCompressBit1
    #define NormalCompressBit1 1
  #else
    #define NormalCompressBit1 0
  #endif

  #if (NormalCompressBit0) || (NormalCompressBit1)
    #define V_NCOMPRESS_ENABLED 1

    #if (NormalCompressBit0) && !(NormalCompressBit1)
      #define V_NCOMPRESS_OCT16 1
    #elif !(NormalCompressBit0) && (NormalCompressBit1)
      #define V_NCOMPRESS_OCT24 1
    #elif (NormalCompressBit0) && (NormalCompressBit1)
      #define V_NCOMPRESS_OCT32 1
    #endif

  #else
    #define V_NCOMPRESS_ENABLED 0
  #endif

#endif

/*
#ifndef HasDecal //Disable UV map if no decal is applied
  #ifdef OutputUVMap
    #undef OutputUVMap
  #endif
#endif
*/

//#define NeedUVs 1
#if defined(NeedTangentSpace) || defined(PmUseDiffuseTexture) || defined(PmUseSpecularTexture)\
    || defined(UseTexture) || defined(_PDSFX) || defined(OutputUVMap) || defined(EVisuPBR)
#ifndef NeedUVs
#define NeedUVs 1
#endif
#endif

#if defined (TiledLighting) || defined(ManualZTest)
#ifndef NeedProjPos
#define NeedProjPos 1
#endif
#endif

#if defined(LogDepth) || defined(Fog) || defined(LowLight)
#ifndef NeedViewPos
#define NeedViewPos 1
#endif
#endif


//decal + no alpha : no lighting is enabled
#if defined(UseTexture) && defined(VolMaterial_TextureFunction) 
#if (VolMaterial_TextureFunction == 4)
#ifdef Lighting
#undef Lighting
#endif
#endif
#endif

#if defined(GENERATE_TRANSPARENTSHADOW) 
#ifdef Lighting
#undef Lighting
#endif
#endif


#if defined DecalLighting
  #ifndef NeedProjPos
    #define NeedProjPos
  #endif
  #ifndef ZMapAccess
    #define ZMapAccess
  #endif
  #ifdef UseNormal
    #undef UseNormal
  #endif
    #endif

//Enable mirror map access if mirror map IBL is enabled
#ifdef PDSFX_ENABLE_IBL_MIRROR_MAP
  #ifndef MirrorMapAccess
    #define MirrorMapAccess
  #endif
#endif

#if (GLSLVersion < 400)
#define NoPerSampleShading
#endif

#ifdef NoClipping
#undef Clipping
#undef kClipPlanesCount
#undef Sectioning
#undef SectioningAllowed
#undef ClippingVol
#undef ClippingVolAllowed
#endif

/************************************************************* ERRORS **************************************************************************/

//Check for NJ3
//#if defined(MultiShadow) && !defined(ShadowMap)
//ERROR : Shadow map must be define if multi shadow is enabled;
//#endif

