void _ProcessVertexOperation(const bool iOutputLocalPosition)
{
#ifdef _PDSFX1_VS_CommonValues
  ComputeCommonValues();
#endif

#ifdef ZTestAnnotation
  bool result = ProcessAnchorPosition();
  if (result)
  {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    return;
  }
#endif

  TangentSpace localTS, worldTS;

  // Local position and normal
#ifdef _PDSFX1_VS_Position
  localTS.Pos = ComputeObjectPosition();
#else
  localTS.Pos = vGetAttribPosition();
#endif
#ifdef _PDSFX1_VS_Normal
  localTS.N = ComputeObjectNormal();
#else
  localTS.N = vGetAttribNormal();
#endif

  // Local tangent and binormal
#ifdef UseTangentSpace

#ifdef _PDSFX1_VS_Tangent
  localTS.T = ComputeObjectTangent();
#else
  localTS.T = vGetAttribTangent();
#endif
#ifdef _PDSFX1_VS_Binormal
  localTS.B = ComputeObjectBinormal();
#else
  localTS.B = vGetAttribBinormal();
#endif

#if !defined(GPUMappingOperator) && defined(TextureMatrix)
  vec2 uVec = vGetTextureMatrix()[0].xy;
  vec2 vVec = vGetTextureMatrix()[1].xy;

  vec3 tempT = normalize(vVec.x * localTS.B + vVec.y * localTS.T);
  localTS.B  = normalize(uVec.x * localTS.B + uVec.y * localTS.T);
  localTS.T  = tempT;
#endif

#endif

// XK7 GPU_SKINNING ++  
#ifdef BoneInformation 
  ivec4 boneIndices = vGetBoneID();
  vec4  boneWeights = vGetBoneWeight(); 
  localTS.Pos = vGetWeightedVertex(localTS.Pos,boneIndices,boneWeights);

#ifdef BoneInstanceInformation
  localTS.Pos = vGetInstancedVertex(localTS.Pos);
#endif //BoneInstanceInformation
#endif // BoneInformation
// XK7 GPU_SKINNING --

  // World-view position and world TBN
#ifdef DoNotUseWorldViewMatrix
  worldTS.Pos = localTS.Pos;
#else
  worldTS.Pos = (vGetWorldViewMatrix() * vec4(localTS.Pos, 1.)).xyz;
#endif
  // World-view TBN
  worldTS.N = vNormalize((vGetWorldViewMatrix() * vec4(localTS.N, 0.)).xyz);
#ifdef UseTangentSpace
  worldTS.T = vNormalize((vGetWorldViewMatrix() * vec4(localTS.T, 0.)).xyz);
  worldTS.B = vCross(worldTS.N, worldTS.T);
#endif

#ifdef _PDSFX1_VS_TangentSpace
  ProcessViewTangentSpace(worldTS);
#endif

  // Convert back view normal to world (avoid some fragment shader algo issues)
  worldTS.N = vNormalize((vGetViewInvMatrix() * vec4(worldTS.N, 0.)).xyz);

  vec4 worldPos = vec4(worldTS.Pos, 1);
  vec4 finalPosition = vGetProjMatrix() * worldPos;

#ifdef _PDSFX1_VS_ClipSpacePos
  ProcessClipSpacePosition(finalPosition);
#endif

#ifndef RayHitStage

  //If we have tessellation stages, we don't use transformed position
  if(iOutputLocalPosition == false)
  {
  #ifdef DecalLighting
    finalPosition.z = 0.0;
  #endif
    gl_Position = finalPosition;
  }
  else
  {
    gl_Position = vec4(localTS.Pos, 1.);
  }

#endif

#ifdef NeedProjPos
  vSetProjPos(finalPosition);
#endif

#ifdef NeedViewPos
  vSetViewPosPostTransform(vGetProjInverseMatrix() * finalPosition);
#endif //NeedViewPos
  
#ifdef NeedUVs
#if defined(_PDSFX1_VS_TexCoord0)
  vec2 tc0 = ComputeObjectTexCoord0().xy;
#else
  vec2 tc0 = vGetAttribTexCoord0().xy;
#endif

#if !defined(GPUMappingOperator) && defined(TextureMatrix)
  vSetUV( (vGetTextureMatrix() * vec4(tc0, 0.0, 1.0)).xy );
#else
  vSetUV( tc0 );
#endif
#endif

  // Legacy UVs access is not allowed in PDSFX
#ifdef HasDecal
#if !defined(GPUMappingOperator) && defined(TextureMatrix)
  _vPrivSetLegacyUVs( (vGetTextureMatrix() * vec4(_SBLegacyUV, 0.0, 1.0)).xy );
#else
  _vPrivSetLegacyUVs( _SBLegacyUV );
#endif
#endif

#ifdef _PDSFX
#ifdef _PDSFX1_VS_TexCoord1
  _vPrivSetSTPQ1(ComputeObjectTexCoord1());
#else
  _vPrivSetSTPQ1(vGetAttribTexCoord1());
#endif
#ifdef _PDSFX1_VS_TexCoord2
  _vPrivSetSTPQ2(ComputeObjectTexCoord2());
#else
  _vPrivSetSTPQ2(vGetAttribTexCoord2());
#endif
#endif

  vSetViewPos(worldTS.Pos);
  vSetWorldN(worldTS.N);

#ifdef LightMap
  _vPrivSetLightMapUVs(_SBLightMapCoord.xy);
#endif

#ifndef VIEW_SPACE_ONLY
  vSetWorldPos( (_vPrivGetWorldMatrix() * vec4(localTS.Pos, 1.)).xyz );
#endif

#ifdef UseTangentSpace
  vSetTangentBiNorm(worldTS.T, worldTS.B);
#endif

#ifdef _PDSFX1_VS_PointSize
  gl_PointSize = ComputePointSize();
#endif

#ifdef _PDSFX1_VS_Varyings
  ComputeVaryingValues();
#endif

#if defined(TiledLighting) //|| defined(LogDepth) NJ3 : I remove the defined because it's not longer used
  ProjPos = gl_Position;
#endif

#ifdef Clipping
  vec4 signedDistance4;
  vec2 signedDistance2;
  
  // Set the default clipping position
  vec3 clippingPosition = vec4(worldTS.Pos, 1).xyz;

  #ifdef _PDSFX1_VS_ClippingPosition
    clippingPosition = ComputeClippingViewPosition();
  #endif

  _vComputePlaneClipping(vec4(clippingPosition, 1.0), signedDistance4, signedDistance2);

  vSetClippingDistance(signedDistance4, signedDistance2);
#endif

#ifdef GroundClipping
#if GroundClipping==1
  vSetGroundClipping(_vPrivComputeClipResult(_sbCbGroundClipping.groundClipPlane,    vec4(worldTS.Pos, 1.)));
#else
  vSetGroundClipping(_vPrivComputeClipResult(_sbCbGroundClipping.groundClipPlaneInv, vec4(worldTS.Pos, 1.)));
#endif
#endif

#ifdef OutputMotionVectorMap
  vSetClipPos(vGetUnjitteredProjMatrix() * vec4(worldTS.Pos, 1.0));
  vSetPrevClipPos(vGetUnjitteredProjMatrix() * (vGetViewDeltaMatrix() * vec4(worldTS.Pos, 1.0)));
#endif

}
