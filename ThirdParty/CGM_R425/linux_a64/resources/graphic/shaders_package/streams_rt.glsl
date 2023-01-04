/*
** Some conditional defines
**
** V_ATTRIB_POSITION_TYPE : type for the position attribute
** V_ATTRIB_TEXCOORD0_TYPE : type for the texcoord0 attribute
** V_ATTRIB_UNIT_VECTOR_TYPE : type for unit vectors (normal, tangent, binormal)
** V_DECODE_UNIT_VECTOR_IF_NEEDED : wrapper around the unit vector decompression function
** V_CONVERT_TO_LINEAR_IF_NEEDED : wrapper around the gamma to linear function
*/

#ifdef PositionAsVec2
  #define V_ATTRIB_POSITION_TYPE vec2
#else
  #define V_ATTRIB_POSITION_TYPE vec3
#endif

#ifdef TexCoordAsVec2
  #define V_ATTRIB_TEXCOORD0_TYPE vec2
#else
  #define V_ATTRIB_TEXCOORD0_TYPE vec3
#endif

//#if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
//  #define V_ATTRIB_UNIT_VECTOR_TYPE uint
//  #define V_DECODE_UNIT_VECTOR_IF_NEEDED NCompress_Uncompress
//#else
  #define V_ATTRIB_UNIT_VECTOR_TYPE vec3
  #define V_DECODE_UNIT_VECTOR_IF_NEEDED 
//#endif

#ifdef VertexColorSRGB
  #define V_CONVERT_TO_LINEAR_IF_NEEDED _SBsRGBToLinear
#else
  #define V_CONVERT_TO_LINEAR_IF_NEEDED
#endif

/*
** Vertex attrib declarations
**
** _SBPosition                       -> vGetAttribPosition
** _SBNormal                         -> vGetAttribNormal
** _SBTexCoord0                      -> vGetAttribTexCoord0
** _SBTexCoord1                      -> vGetAttribTexCoord1
** _SBTexCoord2                      -> vGetAttribTexCoord2
** _SBLegacyUV                       -> ??
** _SBLightMapCoord                  -> ??
** _SBColor                          -> vGetAttribColor
** _SBTangent                        -> vGetAttribTangent
** _SBBinormal                       -> vGetAttribBinormal
** _SBBoneID                         -> vGetAttribBoneID
** _SBBoneWeight                     -> vGetAttribBoneWeight
** _SBAnchorPosition                 -> vGetAttribAnchorPosition
** _SBFixedSizeOriginAndLengthInMM   -> vGetAttribFixedSizeOriginAndLengthInMM
** _SBArrowXAxisAndXValue            -> vGetAttribArrowXAxisAndXValue
** _SBArrowOriginAndYValue           -> vGetAttribArrowOriginAndYValue
** _SBArrowTextScreenAndTextureCoord -> vGetAttribArrowTextScreenAndTextureCoord
** _SBAttribUInt2                    -> vGetAttribUInt2
** _SBDRAWID                         -> ??
*/

// Vertex position
V_IN V_ATTRIB_POSITION_TYPE _SBPosition;

// Vertex normal
#ifdef UseNormal
  V_IN V_ATTRIB_UNIT_VECTOR_TYPE _SBNormal;
#else
  const V_ATTRIB_UNIT_VECTOR_TYPE _SBNormal = V_ATTRIB_UNIT_VECTOR_TYPE(0);
#endif

// Tex Coords 0
#ifdef NeedUVs
  V_IN V_ATTRIB_TEXCOORD0_TYPE _SBTexCoord0;
#else
  const V_ATTRIB_TEXCOORD0_TYPE _SBTexCoord0 = V_ATTRIB_TEXCOORD0_TYPE(0);
#endif

// Tex Coords 1
#ifdef NeedTexCoord1
  V_IN vec4 _SBTexCoord1;
#else
  const vec4 _SBTexCoord1 = vec4(0);
#endif

// Tex Coords 2
#ifdef NeedTexCoord2
  V_IN vec4 _SBTexCoord2;
#else
  const vec4 _SBTexCoord2 = vec4(0);
#endif

// Legacy UVs
#ifdef HasDecal
  V_IN vec2 _SBLegacyUV;
#endif

// Lightmap 
#ifdef LightMap
  V_IN vec2 _SBLightMapCoord;
#endif

// Per vertex colors
#ifdef VertexColor
  V_IN vec4 _SBColor;
#endif

// Tangents
#ifdef NeedTangent
  V_IN V_ATTRIB_UNIT_VECTOR_TYPE _SBTangent;
#else
  const V_ATTRIB_UNIT_VECTOR_TYPE _SBTangent = V_ATTRIB_UNIT_VECTOR_TYPE(0);
#endif

// Binormals
#ifdef NeedBinormal
  V_IN V_ATTRIB_UNIT_VECTOR_TYPE _SBBinormal;
#else
  const V_ATTRIB_UNIT_VECTOR_TYPE _SBBinormal = V_ATTRIB_UNIT_VECTOR_TYPE(0);
#endif

//Other vertex attribs
#ifdef BoneInformation
  V_IN ivec4 _SBBoneID;
  V_IN vec4 _SBBoneWeight;
#endif

#ifdef ZTestAnnotation
  V_IN vec3 _SBAnchorPosition;
#endif

#ifdef FixedSize
  V_IN vec4 _SBFixedSizeOriginAndLengthInMM;
#endif

#ifdef CameraFacingArrow
  V_IN vec4 _SBArrowXAxisAndXValue;
  V_IN vec4 _SBArrowOriginAndYValue;
#endif

#ifdef CameraFacingArrowText
  V_IN vec4 _SBArrowTextScreenAndTextureCoord;
#endif

#ifdef UseAttribUInt
  V_IN uvec2 _SBAttribUInt2;
#endif

#ifdef Instancing
  V_IN int _SBDRAWID;
#endif

/*
** API
*/

V_ATTRIB_POSITION_TYPE vGetAttribPosition() { return _SBPosition; }
vec3 vGetAttribNormal() { return V_DECODE_UNIT_VECTOR_IF_NEEDED(_SBNormal); }

V_ATTRIB_TEXCOORD0_TYPE vGetAttribTexCoord0() { return _SBTexCoord0; }
vec4 vGetAttribTexCoord1() { return _SBTexCoord1; }
vec4 vGetAttribTexCoord2() { return _SBTexCoord2; }
vec3 vGetAttribTangent() { return V_DECODE_UNIT_VECTOR_IF_NEEDED(_SBTangent); }
vec3 vGetAttribBinormal() { return V_DECODE_UNIT_VECTOR_IF_NEEDED(_SBBinormal); }

#ifdef BoneInformation
  ivec4 vGetAttribBoneID() { return _SBBoneID; }
  vec4 vGetAttribBoneWeight() { return _SBBoneWeight; }
#endif

#ifdef VertexColor
  vec4 vGetAttribColor() { return V_CONVERT_TO_LINEAR_IF_NEEDED(_SBColor); }
#endif

#ifdef UseAttribUInt
  uvec2 vGetAttribUInt2() { return _SBAttribUInt2; }
#endif

#ifdef ZTestAnnotation
  vec3 vGetAttribAnchorPosition() { return _SBAnchorPosition; }
#endif

#ifdef FixedSize
  vec4 vGetAttribFixedSizeOriginAndLengthInMM() { return _SBFixedSizeOriginAndLengthInMM; }
#endif

#ifdef CameraFacingArrow
  vec4 vGetAttribArrowXAxisAndXValue() { return _SBArrowXAxisAndXValue; }
  vec4 vGetAttribArrowOriginAndYValue() { return _SBArrowOriginAndYValue; }
#endif

#ifdef CameraFacingArrowText
  vec4 vGetAttribArrowTextScreenAndTextureCoord() { return _SBArrowTextScreenAndTextureCoord; }
#endif

/*
** Compatibility with old shaders
*/
#ifdef BoneInformation
  #define vGetBoneID vGetAttribBoneID
  #define vGetBoneWeight vGetAttribBoneWeight
#endif

#ifdef ZTestAnnotation
  #define vGetAnchorPosition vGetAttribAnchorPosition
#endif

/* dangerous

#ifndef RayHitStage
  #define vGetTexCoord vGetAttribTexCoord0
  #define vGetUvs vGetAttribTexCoord0
  #define vGetTexCoord1 vGetAttribTexCoord1
  #define vGetTexCoord2 vGetAttribTexCoord2
  #define vGetFixedSizeOriginAndLengthInMM vGetAttribFixedSizeOriginAndLengthInMM
  #define vGetArrowTextScreenAndTextureCoord vGetAttribArrowTextScreenAndTextureCoord
  #define vGetArrowXAxisAndXValue() vGetAttribArrowXAxisAndXValue
  #define vGetArrowOriginAndYValue() vGetAttribArrowXAxisAndXValue
#endif
*/
