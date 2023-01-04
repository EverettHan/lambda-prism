float _vPrivComputeClipResult(in vec4 iViewPlaneEq, in vec4 iViewPosition)
{
#ifdef UsePassThroughTransition
  return vDot(_vPrivGetViewInverseTransposeTransition() * iViewPlaneEq, iViewPosition);
#else
  return vDot(iViewPlaneEq, iViewPosition);
#endif
}

#ifdef Clipping
vec4 _vPrivGetViewClipPlaneEq(in uint iIndex)
{
  vec4 clipPlaneEq = _sbCbClipping.clipPlanes[iIndex];
#ifdef ClippingPlaneShift
  clipPlaneEq.w += 0.005; // should be 0.005 * toleranceScale
#endif // ClippingPlaneShift
#ifdef UsePassThroughTransition
  return _vPrivGetViewInverseTransposeTransition() * clipPlaneEq;
#else
  return clipPlaneEq;
#endif
}
#endif

#if defined(VertexStage) || defined(GeometryStage)

// Compute the clipping values between a point and the clipping planes in world space
void _vComputePlaneClipping(in vec4 iWorldPosition, inout vec4 oResult4, inout vec2 oResult2)
{
  // Default init
  oResult4 = vec4(0.0);
  oResult2 = vec2(0.0);

#ifdef Clipping
  vec4 clipPlaneShift = vec4(0.0);
#ifdef ClippingPlaneShift
  clipPlaneShift.w += 0.005; // should be 0.005 * toleranceScale
#endif // ClippingPlaneShift

  if (kClipPlanesCount>0)
  {
    oResult4.x = _vPrivComputeClipResult(_sbCbClipping.clipPlanes[0] + clipPlaneShift, iWorldPosition);
  }
  if (kClipPlanesCount>1)
  {
    oResult4.y = _vPrivComputeClipResult(_sbCbClipping.clipPlanes[1] + clipPlaneShift, iWorldPosition);
  }
  if (kClipPlanesCount>2)
  {
    oResult4.z = _vPrivComputeClipResult(_sbCbClipping.clipPlanes[2] + clipPlaneShift, iWorldPosition);
  }
  if (kClipPlanesCount>3)
  {
    oResult4.w = _vPrivComputeClipResult(_sbCbClipping.clipPlanes[3] + clipPlaneShift, iWorldPosition);
  }
  if (kClipPlanesCount>4)
  {
    oResult2.x = _vPrivComputeClipResult(_sbCbClipping.clipPlanes[4] + clipPlaneShift, iWorldPosition);
  }
  if (kClipPlanesCount>5)
  {
    oResult2.y = _vPrivComputeClipResult(_sbCbClipping.clipPlanes[5] + clipPlaneShift, iWorldPosition);
  }
#endif
}

#endif

#ifdef FragmentStage

// Return the sum of the plane clipping result computed in the vertex shader
// The fragment should be discarded if the returned value is negative
float _vResolvePlaneClipping(in vec4 iResult4, in vec2 iResult2)
{
  float sum = 0.0;

#ifdef Clipping
  sum += vMin(iResult4.x, 0.0);
  sum += vMin(iResult4.y, 0.0);
  sum += vMin(iResult4.z, 0.0);
  sum += vMin(iResult4.w, 0.0);
  sum += vMin(iResult2.x, 0.0);
  sum += vMin(iResult2.y, 0.0);
#endif

  return sum;
}

#ifndef GLESPlatform
#ifdef ManualZTest  
bool vGetZTestResult()//implemented in the file pdsfxCommons.glsl
{
  #ifndef IS_MSAA
    vec2 texCoord = (gl_FragCoord.xy - 0.5) / _sbCbCamera.ScreenSize.xy;
    float depth = texture(pdsfxZMap, texCoord).x;  
  #else //We are in MSAA
    ivec2 texCoord = ivec2(gl_FragCoord.xy);
    float depth = texelFetch(pdsfxZMap, texCoord, gl_SampleID).x;  
  #endif
  
  return (gl_FragCoord.z < depth);  
}
#endif

#if defined(ColorMapAccess) || defined(ZMapAccess) || defined(MirrorMapAccess)

//I making this trick because I don't always want to have gl_SampleID in my shader as this call is dangerous...

#ifdef IS_MSAA
  #define _TMP_SAMPLER_TYPE sampler2DMS
#else //!IS_MSAA
  #define _TMP_SAMPLER_TYPE sampler2D
#endif//IS_MSAA


vec4 _vGetSamplerAccess(vec2 iSamplingPos, _TMP_SAMPLER_TYPE iSampler)
{
  vec4 outputResult;
  
  #ifndef IS_MSAA
    outputResult = texture(iSampler , iSamplingPos);
  #else //We are in MSAA
    ivec2 size = vTextureSize(iSampler);
    outputResult = texelFetch(iSampler , ivec2(iSamplingPos.xy * size), gl_SampleID);
  #endif //IS_MSAA
  
  return outputResult;
}

#undef _TMP_SAMPLER_TYPE

#endif //defined(ColorMapAccess) || defined(ZMapAccess)


#ifdef ColorMapAccess

vec4 vGetColorRefractionMap(vec2 iSamplingPos)
{
  #ifndef IS_MSAA
    return _vGetSamplerAccess(iSamplingPos, pdsfxColorMap);
  #else //We are in MSAA
  return _vGetSamplerAccess(iSamplingPos, pdsfxColorMap);
#endif //IS_MSAA
  
}

#endif //ColorMapAccess


#ifdef ZMapAccess

float vGetZMap(vec2 iSamplingPos)
{
  return _vGetSamplerAccess(iSamplingPos, pdsfxZMap).x;
}

#endif //ZMapAccess

#ifdef MirrorMapAccess

vec4 vGetMirrorMap(vec2 iSamplingPos)
{
  return texture(mirrorMapTex, iSamplingPos);
}

#endif

#endif
#endif

#if defined(ZMapAccess) || defined(ManualZTest) 

#ifndef GLESPlatform
#define kFloatULPShift 5u

bool vGetClipSpaceDepthTest(in vec4 iPosition)
{
  vec3 texPosition = (iPosition.xyz / iPosition.w) * 0.5 + vec3(0.5); // range 0-1 
   
  uint depthInUint = vFloatBitsToUint(texPosition.z);
  depthInUint -= kFloatULPShift;
  float depthOffseted = vUintBitsToFloat(depthInUint);
 
  float depthFromZMap;

#ifndef IS_MSAA
  depthFromZMap = vTexture(pdsfxZMap, texPosition.xy).x;
#else //We are in MSAA
  ivec2 size = vTextureSize(pdsfxZMap);
  depthFromZMap = vTexelFetch(pdsfxZMap, ivec2(texPosition.xy * size), 0).x;
  for (int i = 1;i < IS_MSAA; ++i)
	depthFromZMap = vMax(depthFromZMap, vTexelFetch(pdsfxZMap, ivec2(texPosition.xy * size), i).x);
#endif

  return (depthFromZMap < depthOffseted);
}

#else

bool vGetClipSpaceDepthTest(in vec4 iPosition)
{
  return false;
}

#endif

bool vGetViewDepthTest(in vec3 iViewPosition)
{
  return vGetClipSpaceDepthTest(vGetProjectionMatrix() * vec4(iViewPosition, 1.0));
}

#endif

// Access to forbidden world matrix is required for some physical material functions
// Those accesses can be allowed because they don't imply world position.
vec3 vApplyWorldRotationOnVector(in vec3 iObjectVector)
{
  mat4 worldInvTransp = _vPrivGetWorldInverseTransposeMatrix(); // Private access
  return (worldInvTransp * vec4(iObjectVector, 0.0)).xyz;
}

void vApplyWorldRotationOnVector(in  vec3 iV1, in  vec3 iV2, in  vec3 iV3, 
                                 out vec3 oV1, out vec3 oV2, out vec3 oV3)
{
  mat3 worldInvTransp = mat3(_vPrivGetWorldInverseTransposeMatrix()); // Private access

  mat3 vectors = mat3(iV1, iV2, iV3);

  mat3 result = worldInvTransp * vectors;

  oV1 = result[0];
  oV2 = result[1];
  oV3 = result[2];
}


vec3 vComputeWorldScaling()
{
  mat3 mat = vTranspose(mat3(_vPrivGetWorldMatrix())); // Private access
  return 1.0/vec3(vLength(mat[0]),vLength(mat[1]),vLength(mat[2]));
}

mat3 vGet3x3WorldMatrix()
{
  return mat3(_vPrivGetWorldMatrix());
}

mat3 vGet3x3WorldInvTranspMatrix()
{
  return mat3(_vPrivGetWorldInverseTransposeMatrix());
}

vec4 _internal_vGetGASColor()
{
  return cb_cbVolMaterial.u_DiffuseColor;
}

#ifdef PDSFXInstancing
  vec4 vGetInstanceData(in int iIndex)
  {
    return vTexelFetch(PDSFXInstanceBuffer, iIndex);
  }
#endif
