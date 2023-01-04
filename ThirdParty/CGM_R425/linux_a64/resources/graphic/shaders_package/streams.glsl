#if defined VertexStage

#ifndef GLES2Platform
/************************************************************************************************* Vertex Stage Inputs ****************************************************************************/
//no need to specify the location
#ifndef PositionAsVec2
in vec3 _SBPosition;
#else
in vec2 _SBPosition;
#endif

// XK7 GPU_SKINNING ++
#ifdef BoneInformation
in ivec4 _SBBoneID;
in vec4  _SBBoneWeight;
#endif
// XK7 GPU_SKINNING --

#ifdef UseNormal
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    in uint _SBNormal;
  #else
    in vec3 _SBNormal;
  #endif
#else
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    uint _SBNormal = 0;
  #else
    vec3 _SBNormal = vec3(0.);
  #endif
#endif

#ifdef NeedUVs
#ifndef TexCoordAsVec2
in vec3 _SBTexCoord0;
#else
in vec2 _SBTexCoord0;
#endif
#else
#ifndef TexCoordAsVec2
const vec3 _SBTexCoord0 = vec3(1.);
#else
const vec2 _SBTexCoord0 = vec2(1.);
#endif
#endif

#ifdef HasDecal
in vec2 _SBLegacyUV;
#endif

#ifdef NeedTexCoord1
in vec4 _SBTexCoord1;
#endif

#ifdef NeedTexCoord2
in vec4 _SBTexCoord2;
#endif

#ifdef LightMap
in vec2 _SBLightMapCoord;
#endif

#ifdef VertexColor
in vec4 _SBColor;
#endif

//#ifdef UseTangentSpace
//in vec3 _SBTangent;
//#endif

#ifdef NeedTangent
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    in uint _SBTangent;
  #else
    in vec3 _SBTangent;
  #endif
#else
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    uint _SBTangent = 0;
  #else
    vec3 _SBTangent = vec3(0.0);
  #endif
#endif

#ifdef ZTestAnnotation
    in vec3 _SBAnchorPosition;
#endif

#ifdef NeedBinormal
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    in uint _SBBinormal;
  #else
    in vec3 _SBBinormal;
  #endif
#else
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    uint _SBBinormal = 0;
  #else
    vec3 _SBBinormal = vec3(0.0);
  #endif
#endif

#if defined(FixedSize) || defined(RefPlane)
in vec4 _SBFixedSizeOriginAndLengthInMM;
#endif

#ifdef CameraFacingArrow
in vec4 _SBArrowXAxisAndXValue;
in vec4 _SBArrowOriginAndYValue;
#endif

#ifdef TextureFontText 
in vec4 _SBTextScreenAndTextureCoord;
#endif

#ifdef UseAttribUInt
in uvec2 _SBAttribUInt2;
#endif

#ifdef Skinning
vec4 _SBBlendIndices;
#endif

#ifdef Instancing
in int _SBDRAWID;
#endif


/***************************************************************************** Geometry Stage Input ****************************************************************************/
//The structure should be the same as VertexOut, but I have to duplicate the code due to lack in the glsl language -> I could use a macro but I need the #ifdef inside
//I could define a struct to pass as varying and usable in a macro, but it is then gramatically incorrect then to add a qualifier for interpolation inside the block
//My only solution here is to duplicate the code

#else
/************************************************************************************************* GLES2Platform ****************************************************************************/

/************************************************************************************************* GLES Vertex Stage ****************************************************************************/
// ====  incoming vertex attributes ==== //
#ifndef PositionAsVec2
attribute vec3 _SBPosition;
#else
attribute vec2 _SBPosition;
#endif

#ifdef UseNormal
attribute vec3 _SBNormal;
#else
const vec3 _SBNormal = vec3(0.);
#endif

#ifdef NeedUVs
#ifndef TexCoordAsVec2
attribute vec3 _SBTexCoord0; //to check has been recently modified
#else
attribute vec2 _SBTexCoord0; //to check has been recently modified
#endif
#endif

#ifdef NeedTexCoord1
attribute vec4 _SBTexCoord1;
#endif

#ifdef NeedTexCoord2
attribute vec4 _SBTexCoord2;
#endif

#ifdef HasDecal
attribute vec2 _SBLegacyUV;
#endif

#ifdef LightMap
attribute vec2 _SBLightMapCoord;
#endif


#ifdef VertexColor
attribute vec4 _SBColor;
#endif

#ifdef NeedUVs
varying vec2 _SBuv;
#endif

#ifdef HasDecal
varying vec2 _SBLegUVCoord;
#endif

#ifdef PDSFX1
varying vec4 _SBstpq1;
varying vec4 _SBstpq2;
#endif

#ifdef LightMap
varying vec2 _SBLightMapUVs;
#endif

#ifdef UseTangentSpace
attribute vec3 _SBTANGENT;
#endif

#ifdef NeedTangent
attribute vec3 _SBTangent;
#else
vec3 _SBTangent = vec3(0.);
#endif

#ifdef NeedBinormal
attribute vec3 _SBBinormal;
#else
vec3 _SBBinormal = vec3(0.);
#endif

// ====  vert to frag varyings ==== //
varying vec3 _SBViewPos;
varying vec3 _SBWorldN;

#ifndef VIEW_SPACE_ONLY
varying vec3 _SBWorldPos;
#endif


#ifdef UseTangentSpace // (T, B, N) are the tangent space vectors
varying vec3 _SBWorldT;
varying vec3 _SBWorldB;
#endif

#ifdef Clipping
#ifndef kClipPlanesCount
#define kClipPlanesCount 1
#endif
varying vec4 _SBSignedDistance4;
varying vec2 _SBSignedDistance2;
#endif

#endif

/************************************************************************************************* Common API ****************************************************************************/

// Custom clipping point view position
vec3 _SBClippingViewPosition;

/************************************************************************************************* VertexStage Common API ****************************************************************************/

//no need to specify the location
#ifndef PositionAsVec2
vec3 vGetPosition(){return _SBPosition;}
#else
vec2 vGetPosition(){return _SBPosition;}
#endif

// XK7 GPU_SKINNING ++
#ifdef BoneInformation
ivec4 vGetBoneID(){return _SBBoneID;}
vec4 vGetBoneWeight(){return _SBBoneWeight;}
#endif
// XK7 GPU_SKINNING --

vec3 vGetNormal()
{
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    return NCompress_Uncompress(_SBNormal);
  #else
    return _SBNormal;
  #endif
}

#ifdef NeedUVs
#ifndef TexCoordAsVec2
vec3 vGetTexCoord(){return _SBTexCoord0;} //deprecated
vec3 vGetTexCoord0(){return _SBTexCoord0;} //Alias
vec3 vGetUvs(){return _SBTexCoord0;} //deprecated
#else
vec2 vGetTexCoord(){return _SBTexCoord0;} //deprecated
vec2 vGetTexCoord0(){return _SBTexCoord0;} //Alias
vec2 vGetUvs(){return _SBTexCoord0;} //deprecated
#endif
#endif

#ifdef NeedTexCoord1
vec4 vGetTexCoord1(){return _SBTexCoord1;}
#endif

#ifdef NeedTexCoord2
vec4 vGetTexCoord2(){return _SBTexCoord2;}
#endif

#ifdef VertexColor
vec4 vGetColor()
{
  vec4 col = _SBColor;

#ifdef VertexColorSRGB
  //Ugly, needs refactoring
  col.r = (col.r < 0.04045) ? (col.r/12.92) : pow((col.r + 0.055)/1.055, 2.4);
  col.g = (col.g < 0.04045) ? (col.g/12.92) : pow((col.g + 0.055)/1.055, 2.4);
  col.b = (col.b < 0.04045) ? (col.b/12.92) : pow((col.b + 0.055)/1.055, 2.4);
#endif

  return col;
}
#endif

#ifdef UseAttribUInt
uvec2 vGetAttribUInt2()
{
  return _SBAttribUInt2;
}
#endif

vec3 vGetAttribPosition()
{
#ifndef PositionAsVec2
  return vGetPosition();
#else
  return vec3(vGetPosition(), 0.0);
#endif
}

vec3 vGetAttribNormal()
{
  return vGetNormal();
}

vec4 vGetAttribColor()
{
#ifdef VertexColor
  return vGetColor();
#else
  return vec4(0.0);
#endif
}

vec4 vGetAttribTexCoord0()
{
#ifdef NeedUVs
  #ifndef TexCoordAsVec2
    return vec4(vGetTexCoord0(), 0.0);
  #else
    return vec4(vGetTexCoord0(), 0.0, 0.0);
  #endif
#else
  return vec4(0.0);
#endif
}

vec4 vGetAttribTexCoord1()
{
#ifdef NeedTexCoord1
  return vGetTexCoord1();
#else
  return vec4(0.0);
#endif
}

vec4 vGetAttribTexCoord2()
{
#ifdef NeedTexCoord2
  return vGetTexCoord2();
#else
  return vec4(0.0);
#endif
}

vec3 vGetAttribTangent()
{
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    return NCompress_Uncompress(_SBTangent);
  #else
    return _SBTangent;
  #endif
}

vec3 vGetAttribBinormal()
{
  #if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)
    return NCompress_Uncompress(_SBBinormal);
  #else
    return _SBBinormal;
  #endif
}

#ifdef ZTestAnnotation
vec3 vGetAnchorPosition()
{
  return _SBAnchorPosition;
}
#endif

#if defined(FixedSize) || defined(RefPlane)
vec4 vGetFixedSizeOriginAndLengthInMM()
{
  return _SBFixedSizeOriginAndLengthInMM;
}
#endif

#ifdef CameraFacingArrow
vec4 vGetArrowXAxisAndXValue()
{
  return _SBArrowXAxisAndXValue;
}

vec4 vGetArrowOriginAndYValue()
{
  return _SBArrowOriginAndYValue;
}
#endif

#ifdef TextureFontText 
vec4 vGetTextScreenAndTextureCoord()
{
  return _SBTextScreenAndTextureCoord;
}
#endif

#elif defined TessEvaluationStage

// Custom clipping point view position
vec3 _SBClippingViewPosition;


//Call that must be overloaded

vec3 vGetPosition();

vec3 vGetNormal();


#ifdef NeedUVs
  #ifndef TexCoordAsVec2
    vec3 vGetTexCoord0();
  #else
    vec2 vGetTexCoord0();
  #endif
#endif

#endif //Evaluation stage
