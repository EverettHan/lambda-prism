//===============================================================================================================
//////////////////////////////////////
// Shader Builder Pixel Shader Code //
//////////////////////////////////////

#ifdef _PDSFX
  layout(location = 0) out vec4 fragColor;
  
  #ifdef SO_MRT_LOCATION_FRAGDEPTHWA
    layout(location = SO_MRT_LOCATION_FRAGDEPTHWA) out vec4 fragDepthWA;
  #endif
  
  #ifdef SO_MRT_LOCATION_FRAGNORMAL
    layout(location = SO_MRT_LOCATION_FRAGNORMAL) out vec4 fragNormal;
  #endif
  
  #ifdef SO_MRT_LOCATION_FRAGIBLREFL
    layout(location = SO_MRT_LOCATION_FRAGIBLREFL) out vec4 fragIBLRefl;
  #endif
  
  #ifdef SO_MRT_LOCATION_FRAGF0ROUGH
    layout(location = SO_MRT_LOCATION_FRAGF0ROUGH) out vec4 fragF0Rough;
  #endif
  
  #ifdef SO_MRT_LOCATION_FRAGUV
    layout(location = SO_MRT_LOCATION_FRAGUV) out vec2 fragUV;
  #endif
  
  #ifdef SO_MRT_LOCATION_FRAGMOTIONVECTOR
    layout(location = SO_MRT_LOCATION_FRAGMOTIONVECTOR) out vec2 fragMotionVector;
  #endif
  
  #ifdef SO_MRT_LOCATION_GPUPICKINGMAP
    layout(location = SO_MRT_LOCATION_GPUPICKINGMAP) out uint gpuPickingMap;
  #endif
  
  #ifdef SO_MRT_LOCATION_FRAGWORLDPOS
    layout(location = SO_MRT_LOCATION_FRAGWORLDPOS) out vec4 fragWorldPos;
  #endif
  
  #ifdef SO_MRT_LOCATION_GBUFFERADDITIONALDATA
    layout(location = SO_MRT_LOCATION_GBUFFERADDITIONALDATA) out float fragGBufferAdditionalData;
  #endif
#endif // _PDSFX


#ifndef HasDecal //Disable UV map if no decal is applied
  #ifdef OutputUVMap
    #undef OutputUVMap
  #endif
#endif

#ifdef DecalLighting
  #ifdef OutputWorldPos
    #undef OutputWorldPos
  #endif
#endif

#if defined(WriteDepth) && (GLSLVersion >= 420)

//#ifndef IS_MSAA
//uniform coherent layout(r32ui) uimage2D transparDepth;
//#else //We are in MSAA
//uniform coherent layout(r32ui) uimage2DMS transparDepth;
//#endif //IS_MSAA

#endif //WriteDepth



#if defined(Clipping) && defined(Capping) && defined(CappingFromPassSystem) && !defined(GLESPlatform) && (GLSLVersion >= 400)
#define CappingEnabled
#endif

void _PerformAlphaTest(float iAlphaValue)
{
#ifdef AlphaTest
  
  #ifndef IS_MSAA

    if(iAlphaValue < 0.5)
      discard;

  #endif

#endif //AlphaTest
}

#ifdef PROFILING_STATS

buffer ProfilingData
{
    int myData;
};

#endif


#ifdef LogDepth
float ComputeLogDepth(float projPos)
{
  float NearPlane = vGetNearFarLogFactor().x;
  //float LogZFactor = 1 / vLog(FarPlane / NearPlane);
  float LogZFactor = vGetNearFarLogFactor().z;
  return vLog(projPos / NearPlane) * LogZFactor;
}
#endif


void main()
{

#ifdef PROFILING_STATS
  atomicAdd(myData, 1);
#endif

  float depth = gl_FragCoord.z;

  vec3 _worldNormal = vNormalize(_SBWorldN);

#ifdef DecalLighting
    //We are rendering a decal, this will compute a few attributes such as position, normal & tex coords
    //This will also handle multiple layers of transparency
    //See Decals.glsl
    vec3 decalViewPos;
    ComputeDecals(decalViewPos, depth);
#endif


/******************************* World Normal *************************************/
  vec3 _view = vNormalize(vGetViewEyePos() - vGetViewPos());

  //In otho we use the forward vector as the view vector.
  {
    mat4 viewMat = vGetViewMatrix();
    vec3 lookAt = vec3(viewMat * vec4(normalize(vec3(viewMat[0].z, viewMat[1].z, viewMat[2].z)), 0.0));
    float fact = vStep(0.0, vGetProjMatrix()[2].w);
    _view = mix(_view, lookAt, fact);
  }

  _SBModifiedWorldN = vNormalize(vGetOrientedNormal(_worldNormal, _view));

/******************************* Special Depth Processing *************************************/

#if defined LogDepth || defined WriteDepth
  #ifdef LogDepth

    //Apply logZ only In perspective mode, 
    //this is accounted for during pass creation itself
    float projPos = -vGetViewPosPostTransform().z;
    depth = ComputeLogDepth(projPos);
    
    #if defined(FragmentDepthOffsetForSurface)
      depth += GetPolygonOffset(depth);
    #elif defined(FragmentDepthOffsetForLines)
      depth += GetPolygonOffset(projPos);
    #endif
      
    gl_FragDepth  = depth;

  #endif
    
  #if defined(WriteDepth) && (GLSLVersion >= 420)
    //Convert the float to uint values.
    uint depthInUint = vFloatBitsToUint(depth);  
    uint oldValue;
    #ifndef IS_MSAA
      oldValue = vImageAtomicMin(transparDepth, ivec2(gl_FragCoord.xy), depthInUint);
    #else //We are in MSAA
      oldValue = vImageAtomicMin(transparDepth, ivec2(gl_FragCoord.xy), gl_SampleID, depthInUint);
    #endif //IS_MSAA

    #ifdef TestDepth
    float oldFloat = vUintBitsToFloat(oldValue);

    if(oldFloat < depth)
      discard;
    #endif

  #endif //WriteDepth

#endif //defined LogDepth || defined WriteDept
    
#if (defined(FragmentDepthOffsetForLines) || defined(FragmentDepthOffsetForSurface)) && !(defined(LogDepth))
    gl_FragDepth = depth + GetPolygonOffset(depth);
#endif

#ifdef TangentSpaceGeneration  

    vec3 viewNormalModified = (vGetViewMatrix() * vec4(_SBModifiedWorldN, 0.)).xyz;

  _SBComputeTangentSpace(_SBViewPos, _SBuv, viewNormalModified, _SBtangent, _SBbinormal);  

   _SBtangent = (vGetViewInverseMatrix() * vec4(_SBtangent, 0.)).xyz;
  _SBbinormal = (vGetViewInverseMatrix() * vec4(_SBbinormal, 0.)).xyz;

#endif



/******************************* Clipping Planes *************************************/
#if defined Clipping
  float _SBkeep = 0.0;
  _SBkeep += _vResolvePlaneClipping(_SBSignedDistance4, _SBSignedDistance2);

#ifdef GroundClipping
  _SBkeep += vMin(_SBSignedDistanceGround, 0.0);
#endif
  
#ifndef CappingEnabled // Capping needs extra processing
  if (_SBkeep < 0.0)
  {
    discard;
  }
#endif

#elif defined GroundClipping
  float keep = float(1+int(vSignf(_SBSignedDistanceGround)));

  if (keep == 0.0)
    discard;
#endif

#ifdef CurveClipping
  PerformCurveClippingDiscard();
#endif

#ifdef Sectioning
  PerformSectioningDiscard();
#endif

#ifdef ClippingVol
  PerformClippingVolumeDiscard();
#endif

  ComputeCommonValues();

  PerformClipping();

#ifdef CappingEnabled
  // Capping
  UpdateCapping();

  // Discard the clipped fragment
  if(_SBkeep < 0.0)
  {
    discard;
  }

#endif

#if defined(GENERATE_SHADOWMAP)

  //We linearize the Z if we have a perspective projection (means w != 1)
  if(vAbs(gl_FragCoord.w-1.0) > 0.001)
  {
    float n = _sbCbCamera.NearFarLogFactor.x;
    float f = _sbCbCamera.NearFarLogFactor.y;
    float z = depth;

    depth = ZClipRemmapedInLinear(n, f, z);
  }

#ifndef GLES2Platform
  gl_FragDepth = depth;
#endif

#endif //GENERATE_SHADOWMAP

#if defined(ESM) && defined(GENERATE_SHADOWMAP)

  //We made an small alpha test for the ESM
  #ifdef AlphaTest
    _PerformAlphaTest(ComputeAlpha());
  #endif //AlphaTest

  #ifdef PDSFX0

    #ifndef GLES2Platform
       fragColor = vec4(exp(80.0 * depth),0,0,0);
    #else
       gl_FragColor = vec4(exp(80.0 * depth),0,0,0);
    #endif

  #else
     gl_FragColor = vec4(exp(80.0 * depth),0,0,0);
  #endif //PDSFX0

   return;

#endif //ESM && GENERATE_SHADOW
  
#ifdef ZOnly
   
  //We made an small alpha test for the Z Only
  #ifdef AlphaTest
    _PerformAlphaTest(ComputeAlpha());
  #endif //AlphaTest

  return;
#endif //ZOnly
  
  vec3 finalColor = vec3(0, 0, 0);
  vec3 albedo = ComputeAlbedo();
  float alpha = 1.0;

/************************************************************** Lighting Enabled *********************************************************/

#ifdef OutputWorldPos
  fragWorldPos.xyz = vGetWorldPos();
  fragWorldPos.w = uintBitsToFloat(compress_unit_vec(_SBModifiedWorldN));
  #ifndef UseLegacyRayOriginOffset
  {
    vec4 localPosVec4 = vec4(vGetWorldPos(), 1.0) * _vPrivGetWorldInverseTransposeMatrix(); // <=> worldInverse * worldPos
    vec3 localPos = localPosVec4.xyz / localPosVec4.w;
    vec3 localNormal = normalize((vec4(_SBModifiedWorldN, 0.0) * _vPrivGetWorldInverseTransposeMatrix()).xyz); //  <=> worldInverse * worldNormal; actually,
    // we would want worldInverseTransposeInverse * worldNormal but it looks like worldNormal is, in current code, by mistake, computed as world * localNormal instead
    // of worldInverseTranspose * localNormal
    float localOffset = distance(localPos, offset_ray_origin(localPos, localNormal));
    float worldScaleAlongNormal = 1.0;
    float worldScaleInvAlongNormal = length((vec4(_SBModifiedWorldN, 0.0) * _vPrivGetWorldInverseTransposeMatrix()).xyz);
    if(worldScaleInvAlongNormal != 0.0)
      worldScaleAlongNormal = 1.0 / worldScaleInvAlongNormal;
    fragGBufferAdditionalData.x = worldScaleAlongNormal * localOffset;
  }
  #endif // ifndef UseLegacyRayOriginOffset
  #ifdef OutputWorldPosOnly
    return;
  #endif
#endif

#ifdef Lighting //useful only if we use lighting
  
  LightingData data;
  BRDFParameters brdf;

#ifndef OutputIBLReflMap
  vec4 fragIBLRefl;
#endif
  fragIBLRefl.a = 1.0;


  /******************************** Standard Lighting ***************************************/
  #ifdef DecalLighting
    vec3 worldSurfaceNormal = _decalNormal;

    #if defined normalMapEnabled || defined coatingNormalMapEnabled
      vec3 worldU = vNormalize(vec3(vGetWorldMatrix() * vec4(vGetTangent(), 0.0)));
      vec3 worldV = vNormalize(vec3(vGetWorldMatrix() * vec4(vGetBinormal(), 0.0)));
    #endif
    
    #ifdef Coating
      #if defined coatingNormalMapEnabled
        vec3 localDecalCoatingNormal = ComputeWorldCoatingN();
        vec3 myCoatingWorldNormal = vComputeDecalNormal(worldU, worldV, localDecalCoatingNormal, worldSurfaceNormal);
      #else
        vec3 myCoatingWorldNormal = worldSurfaceNormal;
      #endif
    #endif

    #ifdef normalMapEnabled
      vec3 localDecalNormal = ComputeWorldNormal();
      vec3 myWorldNormal = vComputeDecalNormal(worldU, worldV, localDecalNormal, worldSurfaceNormal);
    #else
      vec3 myWorldNormal = worldSurfaceNormal;
    #endif

    vec3 viewNormal = vec3(vGetViewMatrix() * vec4(myWorldNormal, 0.0));
    vec3 viewPos = decalViewPos;
  #else
    vec3 myWorldNormal = ComputeWorldNormal();

    #ifdef Coating
      vec3 myCoatingWorldNormal = ComputeWorldCoatingN();
    #endif

    vec3 viewNormal = vec3(vGetViewMatrix() * vec4(myWorldNormal, 0.0));
    vec3 viewPos = _SBViewPos;
  #endif
  
  data = ComputeStdLightingData(viewPos, vNormalize(viewNormal), _view);

  data.Vworld = (vGetViewInverseMatrix() * vec4(_view, 0.)).xyz;
#ifdef ImageBasedLighting
  data.VworldTransformed = ComputeTransformation(data.Vworld);
#endif
  data.Nworld = vNormalize(myWorldNormal);

  // BRDF
  vec3 specularColor = ComputeSpecularColor();
  brdf.albedo = albedo;
  brdf.f0 = vec3(0.04) * specularColor;
  brdf.f90 = vec3(1.0);
  brdf.roughness = 1.0;
  brdf.transparency = 0.0;

  ProcessBRDFParameters(brdf);

#ifndef V_DISABLE_GLOSSINESS_SMOOTHING
  ComputeGlossinessSmoothing(data, brdf); //See glossiness.glsl
#endif

  ComputeGlossinessClamping(brdf); //See glossiness.glsl

#ifdef PhysicalMaterial
  #ifdef AnisotropicDistribution
    data.T = (vGetViewMatrix() * vec4(vGetTangent(),0)).xyz;
    data.B = (vGetViewMatrix() * vec4(vGetBinormal(),0)).xyz;
  #endif
  #ifdef Coating
    data.coatingNWorld = myCoatingWorldNormal;
    data.coatingN = vNormalize((vGetViewMatrix() * vec4(data.coatingNWorld, 0)).xyz);
  #endif
  #ifdef Flakes
    data.pearlFlakesNWorld = ComputeWorldPearlFlakesN();
    data.pearlFlakesN = vNormalize((vGetViewMatrix() * vec4(data.pearlFlakesNWorld, 0)).xyz);
    data.metalFlakesNWorld = ComputeWorldMetalFlakesN();
    data.metalFlakesN = vNormalize((vGetViewMatrix() * vec4(data.metalFlakesNWorld, 0)).xyz);
  #endif
#endif

  // Compute all lighting contributions
  vec3 fresnel = vec3(1.0);
  vec4 compositingColor = DoFragmentLightingCompositing(data, brdf, fragIBLRefl.xyz,fresnel);
  finalColor = compositingColor.rgb;
  alpha = compositingColor.a;

#ifdef OutputF0RoughMap
#ifdef DiscardF0RoughPixel
  fragF0Rough = vec4(0.0);
#else
  fragF0Rough.rgb = brdf.f0;
  fragF0Rough.a = brdf.roughness;
#endif
#endif

/************************************************************** Lighting Disabled *********************************************************/
#else
    finalColor = albedo;
#endif
    
#ifdef HighlightAdvanced
  finalColor = vGetMaterialAmbientColor().rgb;
#else
#ifdef PDSFX0
  ProcessFinalColor(finalColor);
#endif
#endif

#ifdef DebugCascadedShadow
  finalColor = DebugCascade(gl_FragCoord.z);
#endif

#if defined(Fog) || defined(LowLight)
  //NJ3/NC5 : previous code did not work in ortho.
  //NJ3/NC5 : previous code did not work in ortho.
  float linearZ = vStep(0.0, vGetProjMatrix()[2].w);
  linearZ = gl_FragCoord.z * gl_FragCoord.w *linearZ + (1.0 - linearZ) * ((-vGetViewPosPostTransform().z-vGetNearFarLogFactor().x) / (vGetNearFarLogFactor().y-vGetNearFarLogFactor().x));
  finalColor = vMix(finalColor, cb_Fog.fogColor.xyz, vClamp(linearZ, 0.0, 1.0));
#endif
  
#ifndef HighlightAdvanced
#ifdef LowLight
  // Lowlight computation
  finalColor = DoLowlighting(finalColor);
#endif
#ifdef GhostLook
  finalColor = vec3(1.); // ghost color is white
#endif
#endif

  // Clamp the alpha value
  alpha = vClamp(alpha, 0.0, ComputeAlpha());
  _PerformAlphaTest(alpha);

#if !defined(HighlightAdvanced) && defined (GhostLook)
  alpha = 0.1; // ghost alpha is very transparent
#endif

#ifdef OutputIBLReflMap
  fragIBLRefl.a = alpha;
#endif

// Highlight computation
#ifdef HighlightAdvanced
  
#ifdef ForceHLOpacity
  #if HighlightAdvanced == 3
  alpha = 0.95;
  #else
  alpha = 0.0;
  #endif
#else

#ifdef Lighting
  vec3   norm = ComputeWorldNormal();
  #ifndef NoViewProj
  norm = vNormalize((vGetViewInverseTransposeMatrix() * vec4(norm, 0.0)).xyz);
  #endif

  alpha = vDot(norm, vec3(0, 0, 1));

  #if HighlightAdvanced == 2 || HighlightAdvanced == 3
  alpha = 1.0 - alpha;
  #endif

  alpha = vClamp(alpha * 0.9, 0.0, 0.9);
#else
    
  #if HighlightAdvanced == 2 || HighlightAdvanced == 3
  alpha = 0.95; // value to specify an object without lighting in the post effect
  #else
  alpha = 0.9;
  #endif

#endif

#endif
#endif

#if defined(AdvancedHLFirstPolite)
  alpha = vClamp(AdvancedHLFirstPolite / 255., 0.01, 0.99);
#endif


  vec4 finalColorWithAlpha = vec4(finalColor, alpha);

#if defined(Lighting)
#if defined(DecalTranspar)
  const uint numLayers = 5;
  const uint minDepth = imageLoad(DecalTransparZMap, ivec3(gl_FragCoord.xy, numLayers-1)).x;

  #ifndef DecalLighting
    uint myDepth = _CompactDepthStencil(depth, cb_cbVolMaterial.u_DecalID);
  #else
    uint myDepth = _CompactDepthStencil(depth, 0x0u);
  #endif

  uint oldDepth;
  uint i;

  #if defined(DecalTranspar2)
    uvec4 depthInList;
    uvec4 fragColorInList;
    uint oldInd;
  #endif

  ivec3 fragPosList = ivec3(gl_FragCoord.xy, 0);
  uint ind = uint(gl_FragCoord.y) * uint(imageSize(DecalTransparZMap).x) + uint(gl_FragCoord.x);
  
  if(myDepth < minDepth)
  {
    for (i=0; i<numLayers; ++i)
    {
      fragPosList.z = int(i);

    #if defined(DecalTranspar1)
      oldDepth = imageAtomicMin(DecalTransparZMap, fragPosList, myDepth);

    #if defined(OutputGPUPicking)
      if(i == 0 && vFloatBitsToUint(PushConstants.x) != 0 && (oldDepth == 0xFFFFFFFFu || myDepth < oldDepth))
        imageStore(GPUPickingDecalMap, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
    #endif
      if(oldDepth == 0xFFFFFFFFu)
        break;
        
      myDepth = max(oldDepth, myDepth);
    #endif

    #if defined(DecalTranspar2)
      uint depthInList = imageLoad(DecalTransparZMap, fragPosList).x;
      
      if(myDepth == depthInList)
      {
        g_DecalTransparData[numLayers * ind + i].first = floatBitsToUint(finalColorWithAlpha);
        g_DecalTransparData[numLayers * ind + i].second = floatBitsToUint(vec4(data.N.xy, vGetUvs().xy));
        g_DecalTransparData[numLayers * ind + i].third = uvec4(cb_cbVolMaterial.u_DecalID, floatBitsToUint(depth), 0, 0);
        break;
      }
    #endif
    }

  #ifdef DecalTranspar2
    discard;
  #endif
  }

#if defined(DecalTranspar1)
  discard;
#endif
#endif
#endif //#if defined Lighting

#ifdef OIT

#ifdef OIT_SORT_COLOR_AND_FRESNEL
  float frontFace = 1.0;
  if(vIsFrontFacing())
	frontFace = 0.5;

	#ifdef EVisuPBR

  StoreColor( gl_FragCoord.z, finalColorWithAlpha, vec4(fresnel,frontFace), vec4(brdf.attenuationColor*(1.0-brdf.thinWalled), brdf.attenuationDistance) );
  #else
  StoreColor( gl_FragCoord.z, finalColorWithAlpha, vec4(vec3(1.0-finalColorWithAlpha.a),frontFace ), vec4(0.0) );
  #endif
  #else
  StoreColor( gl_FragCoord.z, finalColorWithAlpha);
  #endif
#ifdef OIT_TAIL_WA
  OutputMRT(finalColorWithAlpha);
#else
  discard;
#endif

#else
  OutputMRT(finalColorWithAlpha);
#endif  //OIT
   
#ifdef OutputNormalMap
#if !defined(Lighting)
  vec4 normalView = _sbCbCamera.ViewMatrix * vec4(_SBModifiedWorldN, 0);
#else
  vec4 normalView = vec4(data.N, 0);
#endif  
  fragNormal = normalView * 0.5 + vec4(0.5);
#ifdef OutputNormalMap_WithAlpha
  fragNormal.w = finalColorWithAlpha.w;
#else
  fragNormal.w = 1.0;
#endif
#endif

#if defined(OutputUVMap)
#ifdef HasDecal
  fragUV = _vPrivGetLegacyUVs().xy;
#else
  fragUV = vGetUvs().xy;
#endif
#endif

#if defined(OutputGPUPicking) && !defined(DecalLighting)
  #ifdef SO_MRT_LOCATION_GPUPICKINGMAP
    gpuPickingMap = GetGPUPickingID();
  #endif
#elif OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif

#if defined WeightedAverage || defined OIT_TAIL_WA
  fragDepthWA = vec4(1.);
#endif //WeightedAverage
}

#ifdef PDSFX0
void OutputMRT(vec4 finalColor)
{
#ifdef DebugHybrid
  if(DebugHybrid == 1)
  {
    finalColor = (finalColor + 0.2) * vec4(1.0, 0.0, 0.0,1.0);
  }
  else if(DebugHybrid == 2)
  {
    finalColor = (finalColor + 0.2) * vec4(0.0, 0.0, 1.0,1.0);
  }
#endif

#ifndef GLES2Platform
  // Added this to avoid NaN propagation in frame buffer (breaks down tone mapping)
  bvec4 foundNan = isnan(finalColor);

  float anyNanFound = float(any(foundNan));
  finalColor = mix(finalColor, vec4(0.0, 0.0, 0.0, 1.0), anyNanFound);
  fragColor = finalColor;
#else
  gl_FragColor = finalColor;
#endif
}
#endif
