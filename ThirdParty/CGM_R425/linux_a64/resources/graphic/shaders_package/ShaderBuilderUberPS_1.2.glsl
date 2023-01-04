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

  #ifdef SO_MRT_LOCATION_FRAGWORLDPOS
    layout(location = SO_MRT_LOCATION_FRAGWORLDPOS) out uvec4 fragWorldPos;
  #endif

  #ifdef SO_MRT_LOCATION_GBUFFERADDITIONALDATA
    layout(location = SO_MRT_LOCATION_GBUFFERADDITIONALDATA) out float fragGBufferAdditionalData;
  #endif

  #ifdef SO_MRT_LOCATION_FRAGMOTIONVECTOR
    layout(location = SO_MRT_LOCATION_FRAGMOTIONVECTOR) out vec2 fragMotionVector;
  #endif

  #ifdef SO_MRT_LOCATION_GPUPICKINGMAP
    layout(location = SO_MRT_LOCATION_GPUPICKINGMAP) out uint gpuPickingMap;
  #endif

  #ifdef SO_MRT_LOCATION_MATERIALINFO1
    layout(location = SO_MRT_LOCATION_MATERIALINFO1) out uvec4 materialInfo1;
  #endif

  #ifdef SO_MRT_LOCATION_MATERIALINFO2
    layout(location = SO_MRT_LOCATION_MATERIALINFO2) out uvec4 materialInfo2;
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

//buffer ProfilingData
//{
//  int myData;
//};

#endif

#ifdef SparseTexturePrepass

#endif //SparseTexturePrepass

#ifdef SparseTextureRenderPass
#endif //SparseTextureRenderPass

#ifdef OutputMaterialEval
  #ifndef LogDepth
    layout(early_fragment_tests) in;
  #endif
#endif // OutputWorldPos

void main()
{
#ifdef PROFILING_STATS
  atomicAdd(myData, 1);
#endif

  float depth = gl_FragCoord.z;

  vec3 _worldNormal = vNormalize(_SBWorldN);

#ifdef SparseTexturePrepass

  ivec3	sparseTexelCoord = ivec3(-1, -1, -1);
  float	requiredMipmapLevel = 0.0;

  ComputeSparseTextureData(requiredMipmapLevel, sparseTexelCoord);

  fragColor = vec4(requiredMipmapLevel +1., sparseTexelCoord);

  return;
#endif //SparseTexturePrepass

//#ifdef SparseTextureRenderPass
//
//  ivec2	windowSize = textureSize(sparseLODMap, 0).xy; //this texture is only used to fetch the rendertarget size (at the beginning the texture was here to test is the first pass worked properly)
//  ivec2	fragCoord = ivec2(gl_FragCoord.xy - vec2(0.5,0.5));
//  uint	ssboIndex = (fragCoord.y * windowSize.x) + fragCoord.x;
//
//  vec4	col = vec4(0);
//
//  CanPerformClassicSampling(false);
//  ProvideSparseTextureAvailableMipmapLevels(sparseAvailableMipmapLevel[ssboIndex]);
//  ProcessFinalColor(col);
//
//  fragColor = col;
//  return;
//#endif //SparseTextureRenderPass

#ifdef DecalLighting
    //We are rendering a decal, this will compute a few attributes such as position, normal & tex coords
    //This will also handle multiple layers of transparency
    //See Decals.glsl
  vec3 decalViewPos;
    ComputeDecals(decalViewPos, depth);
#endif

/******************************* World Normal *************************************/

  vec3 _view = vNormalize(_vPrivGetViewEyePos() - vGetViewPosition());

  //In otho we use the forward vector as the view vector.
  {
    mat4 viewMat = vGetViewMatrix();
    vec3 lookAt = vec3(viewMat * vec4(normalize(vec3(viewMat[0].z, viewMat[1].z, viewMat[2].z)), 0.0));
    float fact = vStep(0.0, vGetProjMatrix()[2].w);
    _view = mix(_view, lookAt, fact);
  }

  _SBModifiedWorldN = vNormalize(vGetOrientedNormal(_worldNormal, _view));

/******************************* Tangents and Bi-normals  *************************************/
#ifdef TangentSpaceGeneration

  _SBModifiedViewN = (vGetViewMatrix() * vec4(_SBModifiedWorldN, 0.)).xyz;

  _SBComputeTangentSpace(_SBViewPos, _SBuv, _SBModifiedViewN, _SBViewTangent, _SBViewBinormal);

  _SBtangent = (vGetViewInverseMatrix() * vec4(_SBViewTangent, 0.)).xyz;
  _SBbinormal = (vGetViewInverseMatrix() * vec4(_SBViewBinormal, 0.)).xyz;

#else

  _SBModifiedViewN = (vGetViewMatrix() * vec4(_SBModifiedWorldN, 0.)).xyz;

#ifdef UseTangentSpace
  // Optim - Already in view space
  _SBViewTangent = _SBWorldT;
  _SBViewBinormal = _SBWorldB;

  _SBtangent = (vGetViewInverseMatrix() * vec4(_SBViewTangent, 0.)).xyz;
  _SBbinormal = (vGetViewInverseMatrix() * vec4(_SBViewBinormal, 0.)).xyz;
#endif

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

#ifdef SphereClipping
  PerformSphereClippingDiscard();
#endif

#ifdef CurveClipping
  PerformCurveClippingDiscard();
#endif

#ifdef Sectioning
  PerformSectioningDiscard();
#endif

#if defined(ClippingVol) && !defined(ClipVolDebug)
  PerformClippingVolumeDiscard();
#endif

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

    #if defined(OIT) 
    // we must do a manual Z test with LogDepth + OIT or LogDepth + AntiZFight
      if(depth > texelFetch(pdsfxZMap, ivec2(gl_FragCoord.xy), gl_SampleID).x)
        discard;
    #endif

      gl_FragDepth  = depth;


  #endif

   
  // This code will cause issue with AntiZFight/ZPrepass
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

#if (defined(FragmentDepthOffsetForLines) || defined(FragmentDepthOffsetForSurface)) && !defined(LogDepth)
    gl_FragDepth = depth + GetPolygonOffset(depth);
#endif

#ifdef _PDSFX1_FS_CommonValues
  ComputeCommonValues();
#endif

#ifdef _PDSFX1_FS_Discard
  if (ComputeDiscard())
    discard;
#endif

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

#ifdef VoxelMapGeneration
  ComputeVoxelMap();
#endif

#ifdef _PDSFX1_FS_Opacity
  float opacity = ComputeOpacity();
#else
  float opacity = 1.0;
#endif

#if defined(ESM) && defined(GENERATE_SHADOWMAP)

  //We made an small alpha test for the ESM
  #ifdef AlphaTest
    _PerformAlphaTest(opacity);
  #endif //AlphaTest

  #ifdef _PDSFX

    #ifndef GLES2Platform
       fragColor = vec4(exp(80.0 * depth),0,0,0);
    #else
       gl_FragColor = vec4(exp(80.0 * depth),0,0,0);
    #endif

  #else
     gl_FragColor = vec4(exp(80.0 * depth),0,0,0);
  #endif //_PDSFX

   return;

#endif //ESM && GENERATE_SHADOW

#ifdef ZOnly

  //We made an small alpha test for the Z Only
  #ifdef AlphaTest
    _PerformAlphaTest(opacity);
  #endif //AlphaTest

  return;
#endif //ZOnly

  vec3 finalColor = vec3(0, 0, 0);
#ifdef _PDSFX1_FS_Albedo
  #if defined(ClippingVol) && defined(ClipVolDebug) && (kClipVolMethod != ClipVolMethod_FullscreenMap)
    vec3 albedo = PerformClippingVolumeDiscard();
  #else
  vec3 albedo = ComputeAlbedo();
  #endif
#else
  vec3 albedo = vec3(0.0);
#endif
  float alpha = 1.0;


#ifdef OutputWorldPos
  fragWorldPos.xyz = floatBitsToUint(vGetWorldPos());
  fragWorldPos.w = compress_unit_vec(_SBModifiedWorldN);
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
  #if defined(OutputWorldPosOnly) && !defined(OutputMaterialEval)
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

  /******************************** PerVertex Lighting ***************************************/

  #ifdef DecalLighting
    vec3 worldSurfaceNormal = _decalNormal; // this is the world space normal without normal mapping

    #if defined normalMapEnabled || defined coatingNormalMapEnabled || defined EVisuPBR_normal_textured
      vec3 worldU = vNormalize(vec3(_vPrivGetWorldMatrix() * vec4(vGetTangent(), 0.0)));
      vec3 worldV = vNormalize(vec3(_vPrivGetWorldMatrix() * vec4(vGetBinormal(), 0.0)));
    #endif

    #ifdef Coating
      #if defined coatingNormalMapEnabled
        vec3 localDecalCoatingNormal = ComputeWorldCoatingN();
        vec3 myCoatingWorldNormal = vComputeDecalNormal(worldU, worldV, localDecalCoatingNormal, worldSurfaceNormal);
      #else
        vec3 myCoatingWorldNormal = worldSurfaceNormal;
      #endif
    #endif

    #if defined(normalMapEnabled) || defined(EVisuPBR_normal_textured)
      #ifdef _PDSFX1_FS_Normal
        vec3 localDecalNormal = ComputeViewNormal(); //This is the tangent space normal map coming from the decal material
      #else
        vec3 localDecalNormal = vec3(vGetViewInvMatrix() * vec4(viewNormal, 0.0));
      #endif

      vec3 myWorldNormal = vComputeDecalNormal(worldU, worldV, localDecalNormal, worldSurfaceNormal);
      vec3 viewNormal = vec3(vGetViewMatrix() * vec4(myWorldNormal, 0.0));
    #else
      vec3 viewNormal = vec3(vGetViewMatrix() * vec4(worldSurfaceNormal, 0.0));
      vec3 myWorldNormal = worldSurfaceNormal;
    #endif

    vec3 viewPos = decalViewPos;
  #else
    #ifdef _PDSFX1_FS_Normal
      vec3 viewNormal = ComputeViewNormal();
    #else
      vec3 viewNormal = vGetViewNormal();
    #endif

    vec3 myWorldNormal = vec3(vGetViewInvMatrix() * vec4(viewNormal, 0.0));

    #ifdef Coating
      vec3 myCoatingWorldNormal = ComputeWorldCoatingN();
    #endif

    #ifdef _PDSFX1_FS_Position
      vec3 viewPos = ComputeViewPosition();
    #else
      vec3 viewPos = _SBViewPos;
    #endif
  #endif

  data = ComputeStdLightingData(viewPos, vNormalize(viewNormal), _view);

  data.Vworld = (vGetViewInverseMatrix() * vec4(_view, 0.)).xyz;
#ifdef ImageBasedLighting
  data.VworldTransformed = ComputeTransformation(data.Vworld);
#endif
  data.Nworld = vNormalize(myWorldNormal);

  // BRDF
#if defined(EVisuPBR) || defined(XRiteCarPaint2)
#else
  brdf.albedo = albedo;
#ifndef _PDSFX1_FS_F0
  brdf.f0 = vec3(0.04);
#else
  brdf.f0 = ComputeSpecularReflectance();
#endif
  brdf.f90 = vec3(1.0);
#ifndef _PDSFX1_FS_Roughness
  brdf.roughness = 1.0;
#else
  brdf.roughness = ComputeRoughness();
#endif
#ifndef _PDSFX1_FS_Transparency
  brdf.transparency = 0.0;
#else
  brdf.transparency = ComputeTransparency();
#endif
#endif // EVisuPBR || XRiteCarPaint2

#ifdef _PDSFX1_FS_AdvancedBRDFUser
  ProcessBRDFParameters(brdf);
#endif

#if defined(XRiteCarPaint2)
  // do nothing
#else
  // If DSPBR without specular_AA or any other material (except XRiteCPA2 accounted above)
  #if (defined(EVisuPBR) && !defined(SO_EVISUPBR_SPECULAR_AA)) || !defined(EVisuPBR)
    #ifndef V_DISABLE_GLOSSINESS_SMOOTHING
      ComputeGlossinessSmoothing(data, brdf); //See glossiness.glsl
    #endif
    ComputeGlossinessClamping(brdf); //See glossiness.glsl
  #endif
#endif // XRiteCarPaint2

#ifdef OutputMaterialEval
{
  MaterialEval res;
  /*
  vec4  baseColor;
  float perceptualRoughness;
  float metallic;
  vec3  shadingNormal;
  vec3  shadingTangentU;
  vec3  shadingTangentV;
  vec3  emissive;
  */
  
  res.perceptualRoughness = brdf.roughness*brdf.roughness;

  #ifdef EVisuPBR
    res.baseColor = vec4(brdf.albedo, 1.0);
    res.metallic = brdf.metallic;
  #else
    if(all(equal(brdf.f0, vec3(0.0))))
      brdf.f0 = vec3(0.04);

    // Convert metallic value from specular glossiness inputs
    float maxSpecular = max(max(brdf.f0.r, brdf.f0.g), brdf.f0.b);
    res.metallic = solveMetallic(brdf.albedo.rgb, brdf.f0, maxSpecular);
    vec3 baseColorDiffusePart = brdf.albedo.rgb * ((1.0 - maxSpecular) / (1 - c_MinReflectance) / max(1 - res.metallic, kEpsilon));
    vec3 baseColorSpecularPart = brdf.f0 - (vec3(c_MinReflectance) * (1 - res.metallic) * (1 / max(res.metallic, kEpsilon)));
    res.baseColor = vec4(mix(baseColorDiffusePart, baseColorSpecularPart, res.metallic * res.metallic), 1.0);
  #endif
  res.shadingNormal = _SBModifiedWorldN;
  res.shadingTangentU = vGetTangent();
  res.shadingTangentV = vGetBinormal();
  #if !defined(PDSFX1) || defined(_PDSFX1_FS_Emissive)
    res.emissive = ComputeEmissive();
  #else
    res.emissive = vec3(0.0);
  #endif

  uvec4 v1, v2;
  encodeMaterialEval(res, v1, v2);
  
  materialInfo1 = v1;
  materialInfo2 = v2;
  return;
}
#endif

#if defined(EVisuPBR) || defined(XRiteCarPaint2)
  data.T = (vGetViewMatrix() * vec4(vGetTangent(),0)).xyz;
  data.B = (vGetViewMatrix() * vec4(vGetBinormal(),0)).xyz;
#endif

#ifdef PhysicalMaterial
  #if defined(AnisotropicDistribution)
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
  vec3 fresnel = vec3(0.0);
  vec4 compositingColor = DoFragmentLightingCompositing(data, brdf, fragIBLRefl.xyz,fresnel);
  finalColor = compositingColor.rgb;
  alpha = compositingColor.a;

#ifdef OutputF0RoughMap
#ifdef DiscardF0RoughPixel
  fragF0Rough = vec4(0.0, 0.0, 0.0, 1.0); // roughness = 1.0 disables SSR
#else
  #ifdef EVisuPBR
    vec3 F_0 = brdf.specular * brdf.specularTint * pow((1.0 - brdf.ior) / (1.0 + brdf.ior), 2.0);
    vec3 rho_sr0 = (1.0 - brdf.metallic) * F_0 * brdf.specular * brdf.specularTint + brdf.metallic * brdf.albedo;

    fragF0Rough.rgb = rho_sr0;
    fragF0Rough.a = brdf.roughness;
  #else
    #ifdef XRiteCarPaint2
    #else
      fragF0Rough.rgb = brdf.f0;
      fragF0Rough.a = brdf.roughness;
    #endif
  #endif
#endif
#endif

/************************************************************** Lighting Disabled *********************************************************/
#else
  finalColor = albedo;
    
	#if defined(GENERATE_TRANSPARENTSHADOW)
		BRDFParameters brdf;
		#ifdef EVisuPBR
		#else
			#ifndef _PDSFX1_FS_Transparency
			  brdf.transparency = 0.0;
			#else
			  brdf.transparency = ComputeTransparency();
			#endif
		#endif

		#ifdef _PDSFX1_FS_AdvancedBRDFUser
		  ProcessBRDFParameters(brdf);
		#endif
		alpha = 1-brdf.transparency;

		// OIT color ++
		#if defined(TRANSPARENTSHADOW_OITCOLOR) && defined(EVisuPBR)
			if(brdf.thinWalled != 1.0 && (brdf.attenuationColor.r!=0.f || brdf.attenuationColor.g!=0.f || brdf.attenuationColor.b==0.f))
			{
				// To get more closure output as RayTracing
				finalColor.r = finalColor.r * brdf.attenuationColor.r *brdf.attenuationDistance;
				finalColor.g = finalColor.g * brdf.attenuationColor.g *brdf.attenuationDistance;
				finalColor.b = finalColor.b * brdf.attenuationColor.b *brdf.attenuationDistance;
				finalColor /= 5.f;
				alpha = 0.9;
			}
		#endif // TRANSPARENTSHADOW_OITCOLOR --
		// setting offset to have good shadow when alpha near 0
		if(alpha>=0.f && alpha<=0.1f)
		{
			alpha = 0.1f;
		}
		if(finalColor.r==1.0 && finalColor.g==1.0 && finalColor.b==1.0)
		{
			finalColor *= (1-alpha); //Reason : with current blending formula complete white will not have premultiplied alpha, so the shadow map will be 1,1,1 and multiply light with 1,1,1 does not generate shadows
		}
	#endif //GENERATE_TRANSPARENTSHADOW
#endif

#if defined (GPUSectionProfile) && defined (ComputeSectionProfileInGS_AdditionalPass)
  finalColor = cb_GPUSectionProfile.u_GPUSectionProfileColor;
#endif

#ifdef HighlightAdvanced
  finalColor = vGetMaterialAmbientColor().rgb;
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
  alpha = vClamp(alpha, 0.0, opacity);
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

  #ifdef _PDSFX1_FS_Normal
  vec3 norm = ComputeViewNormal();
  #else
  vec3 norm = vGetViewNormal();
  #endif

  #ifdef NoViewProj
  norm = vNormalize((vGetViewInvMatrix() * vec4(norm, 0.0)).xyz);
  #endif

  alpha = vDot(norm, vec3(0.0, 0.0, 1.0));

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

  #ifdef LogDepth
    if(depth > texelFetch(pdsfxZMap, ivec2(gl_FragCoord.xy), gl_SampleID).x)
      discard;
  #endif

  const uint numLayers = 5;
  uint minDepth = imageLoad(DecalTransparZMap, ivec3(gl_FragCoord.xy, numLayers-1)).x;

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

      if(oldDepth == 0xFFFFFFFFu || oldDepth == myDepth)
        break;

      myDepth = max(oldDepth, myDepth);
    #endif

    #if defined(DecalTranspar2)
      uint depthInList = imageLoad(DecalTransparZMap, fragPosList).x;

      if(myDepth == depthInList)
      {
        g_DecalTransparData[numLayers * ind + i].first = floatBitsToUint(finalColorWithAlpha);
        g_DecalTransparData[numLayers * ind + i].second = floatBitsToUint(vec4(data.N.xy, _vPrivGetLegacyUVs().xy));
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

#ifdef _PDSFX1_FS_FinalColor
  ProcessFinalColor(finalColorWithAlpha);
#endif

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

#ifdef OutputMotionVectorMap
	fragMotionVector = vGetMotionVector();
#endif
}

#ifdef _PDSFX
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

