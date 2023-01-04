
/** Tell if the projection matrix is a perspective or an ortho projection
*  @param iProjectionMatrix The projection matrix.
*  @return true if it's a perspective else false.
*/
bool IsPerspective(mat4 iProjectionMatrix) 
{
	return (iProjectionMatrix[2].w < 0.0);
}

/** 
*  @param iFragCoord is gl_FragCoord
*  @return true if it's a perspective else false.
*/
bool IsPerspective(vec4 iFragCoord)
{
  return vAbs(iFragCoord.w-1.0) > 0.001; // w != 1 --> Perspective 
}



/** Project a Z value in clip space (usually comming from the Zbuffer) to the Eye space (also called view)
*  @param  iNearPlane The near plane
*  @param  iFarPlane  The far plane
*  @param  iZClipSpace The Z value in clip space (usually the Zmap value)
*  @return the Eye space Z value
*/
float ZClipToEye(float iNearPlane, float iFarPlane, float iZClipSpace) 
{
	return (2.0 * iNearPlane * iFarPlane) / (iFarPlane + iNearPlane - iZClipSpace * (iFarPlane - iNearPlane));
}


/** Take the Z value in clip space (usually comming from the Zbuffer) and
*  remap it to a linear [0..1] range (near plane to far plane)
*  @param  iNearPlane The near plane
*  @param  iFarPlane  The far plane
*  @param  iZClipSpace The Z value in clip space (usually the Zmap value)
*  @return depth buffer Z-value remapped to a linear [0..1] range (near plane to far plane)
*/
float ZClipRemmapedInLinear(float iNearPlane, float iFarPlane, float iZClipSpace) 
{
	return iNearPlane * (iZClipSpace + 1.0) / (iFarPlane + iNearPlane - iZClipSpace * (iFarPlane - iNearPlane));
}

#if defined(FragmentStage)

/** Take a texture coordinate in normalized space and a texture size and
*   return the mipmap level that would be used if the texture was sampled
*  @param  iTextureCoordinate The texture coordinates in normalized space
*  @param  iTextureSize  The size of the texture
*  @return The mipmap level that have to be used to sample the texture associated to the input parameters
*/
float ComputeTextureMipmapLevel(in vec2 iTextureCoordinate, in ivec2 iTextureSize)
{
	vec2	textureWindowCoordinate = iTextureCoordinate * vec2(iTextureSize.xy);
	vec2	dXTextureWindowCoordinate = dFdx(textureWindowCoordinate);	
	vec2	dYTextureWindowCoordinate = dFdy(textureWindowCoordinate);
	
	float	deltaMaxSqr = vMax(vDot(dXTextureWindowCoordinate, dXTextureWindowCoordinate), vDot(dYTextureWindowCoordinate, dYTextureWindowCoordinate));
	float	mipmapBaseLevel = 0.5 * log2(deltaMaxSqr);
	
	return vMax(0.0, mipmapBaseLevel);
}

#endif

// XK7 GPU_SKINNING ++
#if defined(VertexStage)

#if defined(BoneInformation)
//uniform samplerBuffer BoneTransformationBuffer;

mat4 vGetMatrix(int index, in samplerBuffer iBuffer)
{
  vec4 col1 = vTexelFetch(iBuffer, (index * 3) + 0);
  vec4 col2 = vTexelFetch(iBuffer, (index * 3) + 1);
  vec4 col3 = vTexelFetch(iBuffer, (index * 3) + 2);

  mat4 mat = mat4(vec4(col1.xyz, 0.0),
    vec4(col1.w, col2.x, col2.y, 0.0),
    vec4(col2.z, col2.w, col3.x, 0.0),
    vec4(col3.yzw, 1));
  return mat;
}

vec3 vGetWeightedVertex(vec3 vertexPos,ivec4 boneIndices,vec4  boneWeights)
{
  int offset = gl_InstanceID * cb_cbVolMaterial.u_NumBones;

  mat4 finalBoneTransform  = vGetMatrix(boneIndices.x + offset, BoneTransformationBuffer) * boneWeights.x;
  finalBoneTransform      += vGetMatrix(boneIndices.y + offset, BoneTransformationBuffer) * boneWeights.y;
  finalBoneTransform      += vGetMatrix(boneIndices.z + offset, BoneTransformationBuffer) * boneWeights.z;
  finalBoneTransform      += vGetMatrix(boneIndices.w + offset, BoneTransformationBuffer) * boneWeights.w;

  vec4 transfomedPos = finalBoneTransform * vec4(vertexPos, 1.0);
  return transfomedPos.xyz;
}

#if defined(BoneInstanceInformation)
//uniform samplerBuffer BonePositionBuffer;
vec3 vGetInstancedVertex(vec3 vertexPos)
{
  mat4 finalBoneTransform = vGetMatrix(gl_InstanceID,BonePositionBuffer);
  vec4 transfomedPos = finalBoneTransform * vec4(vertexPos, 1.0);
  return transfomedPos.xyz;
}
#endif //BoneInstanceInformation

#endif // BoneInformation

#endif// VertexStage
// XK7 GPU_SKINNING --

