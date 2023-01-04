void _ProcessVertexOperation(const bool iOutputLocalPosition)
{   
  ComputeCommonValues();

  TangentSpace localTS, worldTS;
  localTS.Pos = GetLocalPosition();
  localTS.N   = vGetNormal();
#ifdef UseTangentSpace
  /*localTS.T   = TANGENT;
  localTS.B   = vCross(_SBNormal, _SBTangent);*/

#if !defined(GPUMappingOperator) && defined(TextureMatrix)

  vec2 uVec = vGetTextureMatrix()[0].xy;
  vec2 vVec = vGetTextureMatrix()[1].xy;

  vec3 tempT = normalize(vVec.x * _SBBinormal + vVec.y * _SBTangent);
  localTS.B  = normalize(uVec.x * _SBBinormal + uVec.y * _SBTangent);
  localTS.T = tempT;
#else

  localTS.T   = _SBTangent;
  localTS.B   =  _SBBinormal;
#endif  
#endif

  worldTS.Pos = (vGetWorldViewMatrix() * vec4(localTS.Pos, 1.)).xyz;
  worldTS.N   = vNormalize((vGetWorldMatrix() * vec4(localTS.N, 0.)).xyz);
#ifdef UseTangentSpace
  worldTS.T   = vNormalize((vGetWorldMatrix() * vec4(localTS.T, 0.)).xyz);
  worldTS.B   = vCross(worldTS.N, worldTS.T);
#endif

  //Enabled for now but will be disable soon !
  ProcessTangentSpaceCustom(worldTS);
  
  // Set the default clipping position
  _SBClippingViewPosition = vec4(worldTS.Pos, 1).xyz;


  vec4 worldPos = vec4(worldTS.Pos, 1);
  vec4 finalPosition = vGetProjMatrix() * worldPos;
 
  TransformFinalPosition(finalPosition);


  //If we have tessellation stages, we don't use transformed position
  if(iOutputLocalPosition == false)
    gl_Position = finalPosition;
  else
    gl_Position = vec4(localTS.Pos, 1.);



#ifdef NeedProjPos
  vSetProjPos(finalPosition);
#endif

#ifdef NeedViewPos
  vSetViewPosPostTransform(vGetProjInverseMatrix() * finalPosition);
#endif //NeedViewPos
  
#ifdef NeedUVs
#if !defined(GPUMappingOperator) && defined(TextureMatrix)
  vSetUV( (vGetTextureMatrix() * vec4(vGetTexCoord0().xy, 0.0, 1.0)).xy );
#else
  vSetUV( vGetTexCoord0().xy );
#endif
#endif
  
#ifdef HasDecal
#if !defined(GPUMappingOperator) && defined(TextureMatrix)
  _vPrivSetLegacyUVs( (vGetTextureMatrix() * vec4(_SBLegacyUV, 0.0, 1.0)).xy );
#else
  _vPrivSetLegacyUVs( _SBLegacyUV );
#endif
#endif

  vSetViewPos(worldTS.Pos);
  vSetWorldN(worldTS.N);

#ifdef LightMap
  _vPrivSetLightMapUVs(_SBLightMapCoord.xy);
#endif

#ifndef VIEW_SPACE_ONLY
  vSetWorldPos( (_sbCbNode.WorldMatrix * vec4(localTS.Pos, 1.)).xyz );
#endif

#ifdef UseTangentSpace
  vSetTangentBiNorm(worldTS.T, worldTS.B);
#endif
  
  ProcessVertexCustom();

#if defined(TiledLighting) //|| defined(LogDepth) NJ3 : I remove the defined because it's not longer used
  ProjPos = gl_Position;
#endif

#ifdef Clipping
  vec4 signedDistance4;
  vec2 signedDistance2;
  
  _vComputePlaneClipping(vec4(_SBClippingViewPosition, 1.), signedDistance4, signedDistance2);

  vSetClippingDistance(signedDistance4, signedDistance2);
#endif

#ifdef GroundClipping
#if GroundClipping==1
  vSetGroundClipping(_vPrivComputeClipResult(_sbCbGroundClipping.groundClipPlane,    vec4(worldTS.Pos, 1.)) );
#else
  vSetGroundClipping(_vPrivComputeClipResult(_sbCbGroundClipping.groundClipPlaneInv, vec4(worldTS.Pos, 1.)));
#endif
#endif
}
