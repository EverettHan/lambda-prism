/************************************************************************************************* GL Platform ****************************************************************************/

#ifndef GLESPlatform
/***************************************************************************** Geometry Stage Input ****************************************************************************/
//The structure should be the same as VertexOut, but I have to duplicate the code due to lack in the glsl language -> I could use a macro but I need the #ifdef inside
//I could define a struct to pass as varying and usable in a macro, but it is then gramatically incorrect then to add a qualifier for interpolation inside the block
//My only solution here is to duplicate the code

#if defined(UseTessControlStage) || defined(UseTessEvaluationStage)
  #define UseTessellationStage
#endif


//// DEFINE the shader Inputs

#if defined VertexStage


#elif defined TessControlStage

  #define VARYING_INPUT_INTERFACE_NAME VertexToTessControl
  #define VARYING_INPUT_NAME           VertexIn[]
  #define VARYING_INPUT_LAYOUT

#elif defined TessEvaluationStage

  #define VARYING_INPUT_INTERFACE_NAME TessControlToTessEval
  #define VARYING_INPUT_NAME           TessControlIn[]
  #define VARYING_INPUT_LAYOUT

#elif defined GeometryStage

  #ifdef UseTessellationStage

    #define VARYING_INPUT_INTERFACE_NAME TessEvalToGeometry
    #define VARYING_INPUT_NAME           VertexIn[3]
    #define VARYING_INPUT_LAYOUT

  #else //UseTessellationStage
  
    #ifdef GEOMETRY_SHADER_PASSTHROUGH
      #define VARYING_INPUT_INTERFACE_NAME VertexToFragment
      #define VARYING_INPUT_NAME           VertexIn[]
      #define VARYING_INPUT_LAYOUT         layout(passthrough) 
    #else
      #define VARYING_INPUT_INTERFACE_NAME VertexToGeometry
      #define VARYING_INPUT_NAME           VertexIn[3]
      #define VARYING_INPUT_LAYOUT
    #endif

  #endif

#elif defined FragmentStage

  #if defined UseTessellationStage && !defined(UseGeometryStage)
    
    #define VARYING_INPUT_INTERFACE_NAME TessEvalToFragment
    #define VARYING_INPUT_NAME 
    #define VARYING_INPUT_LAYOUT

  #elif defined UseGeometryStage && !defined(GEOMETRY_SHADER_PASSTHROUGH)

    #define VARYING_INPUT_INTERFACE_NAME GeomToFragment
    #define VARYING_INPUT_NAME
    #define VARYING_INPUT_LAYOUT

  #else //Only a Vertex shader

    #define VARYING_INPUT_INTERFACE_NAME VertexToFragment
    #define VARYING_INPUT_NAME
    #define VARYING_INPUT_LAYOUT

  #endif

#endif //End Input Name definition


#ifdef VARYING_INPUT_INTERFACE_NAME

VARYING_INPUT_LAYOUT V_IN VARYING_INPUT_INTERFACE_NAME
  {
    vec3 _SBViewPos;
    vec3 _SBWorldN;
  #ifndef VIEW_SPACE_ONLY
    vec3 _SBWorldPos;
  #endif


  #ifdef NeedUVs
    vec2 _SBuv;
  #endif

  #ifdef HasDecal
    vec2 _SBLegUVCoord;
  #endif

  #ifdef PDSFX1
    vec4 _SBstpq1;
    vec4 _SBstpq2;
  #endif

  #ifdef LightMap
    vec2 _SBLightMapUVs;
  #endif

    // (T, B, N) are the tangent space vectors
  #ifdef UseTangentSpace
    vec3 _SBWorldT;
    vec3 _SBWorldB;
  #endif

  #if defined NeedProjPos
    vec4 _SBProjPos;
  #endif

  #if defined NeedViewPos
    vec4 _SBViewPosPostTransform;
  #endif
  
  #ifdef Clipping //array are not well packed in glsl, I prefer use those kind of datas
  #ifndef kClipPlanesCount //to avoid compilation issue
  #define kClipPlanesCount 1
  #endif
    vec4 _SBSignedDistance4;
    vec2 _SBSignedDistance2;
  #endif    

  #ifdef GroundClipping
    float _SBSignedDistanceGround;
  #endif

  #ifdef DecalLighting
    vec3 vObjectSpacePosition;
  #endif

  #ifdef OutputMotionVectorMap
    vec4 _ClipPos;
    vec4 _PrevClipPos; 
  #endif

  } VARYING_INPUT_NAME;

#endif //VARYING_INPUT_INTERFACE_NAME




  //// DEFINE the shader Outputs

#if defined VertexStage


  #if defined UseTessellationStage

    #define VARYING_OUTPUT_INTERFACE_NAME VertexToTessControl
    #define VARYING_OUTPUT_NAME           
    #define VARYING_OUTPUT_LAYOUT

  #elif defined UseGeometryStage && !defined(GEOMETRY_SHADER_PASSTHROUGH)

    #define VARYING_OUTPUT_INTERFACE_NAME VertexToGeometry
    #define VARYING_OUTPUT_NAME 
    #define VARYING_OUTPUT_LAYOUT

  #else //Only a fragment shader

    #define VARYING_OUTPUT_INTERFACE_NAME VertexToFragment
    #define VARYING_OUTPUT_NAME 
    #define VARYING_OUTPUT_LAYOUT

  #endif

#elif defined TessControlStage

  #define VARYING_OUTPUT_INTERFACE_NAME TessControlToTessEval
  #define VARYING_OUTPUT_NAME TessControlOut[]
  #define VARYING_OUTPUT_LAYOUT

#elif defined TessEvaluationStage

  #ifdef UseGeometryStage

    #define VARYING_OUTPUT_INTERFACE_NAME TessEvalToGeometry
    #define VARYING_OUTPUT_NAME TessEvalOut
    #define VARYING_OUTPUT_LAYOUT

  #else //Directly to the fragment

    #define VARYING_OUTPUT_INTERFACE_NAME TessEvalToFragment
    #define VARYING_OUTPUT_NAME TessEvalOut
    #define VARYING_OUTPUT_LAYOUT

  #endif

#elif GeometryStage

  #ifndef GEOMETRY_SHADER_PASSTHROUGH
    #define VARYING_OUTPUT_INTERFACE_NAME GeomToFragment
    #define VARYING_OUTPUT_NAME GeomOut
    #define VARYING_OUTPUT_LAYOUT
  #endif

#elif defined(RayHitStage)

    #define VARYING_OUTPUT_INTERFACE_NAME IRaytracingVertexInfo
    #define VARYING_OUTPUT_NAME RaytracingVertexInfo
    #define VARYING_OUTPUT_LAYOUT struct

#endif //End Input Name definition


#ifdef VARYING_OUTPUT_INTERFACE_NAME

  VARYING_OUTPUT_LAYOUT V_OUT VARYING_OUTPUT_INTERFACE_NAME
  {
    vec3 _SBViewPos;
    vec3 _SBWorldN;
  #ifndef VIEW_SPACE_ONLY
    vec3 _SBWorldPos;
  #endif

  #ifdef NeedUVs
    vec2 _SBuv;
  #endif

  #ifdef HasDecal
    vec2 _SBLegUVCoord;
  #endif

  #ifdef PDSFX1
    vec4 _SBstpq1;
    vec4 _SBstpq2;
  #endif

  #ifdef LightMap
    vec2 _SBLightMapUVs;
  #endif

    // (T, B, N) are the tangent space vectors
  #ifdef UseTangentSpace
    vec3 _SBWorldT;
    vec3 _SBWorldB;
  #endif

  #if defined NeedProjPos
    vec4 _SBProjPos;
  #endif

  #if defined NeedViewPos
    vec4 _SBViewPosPostTransform;
  #endif

  #ifdef Clipping //array are not well packed in glsl, I prefer use those kind of datas
  #ifndef kClipPlanesCount //to avoid compilation issue
  #define kClipPlanesCount 1
  #endif
    vec4 _SBSignedDistance4;
    vec2 _SBSignedDistance2;
  #endif    

  #ifdef GroundClipping
    float _SBSignedDistanceGround;
  #endif

  #ifdef DecalLighting
    vec3 vObjectSpacePosition;
  #endif

  #ifdef OutputMotionVectorMap
    vec4 _ClipPos;
    vec4 _PrevClipPos; 
  #endif

  } VARYING_OUTPUT_NAME;

#endif //VARYING_OUTPUT_INTERFACE_NAME

#if defined GeometryStage
  #if !defined TrianglePrimitives && !defined LinePrimitives && !defined PointPrimitives
    #define TrianglePrimitives
  #endif

  #if defined TrianglePrimitives

    #define _LAYOUT_IN triangles
	#ifdef ComputeSectionProfileInGS_AdditionalPass
		#define _LAYOUT_OUT line_strip
		#define _MAX_VERTICES 6
	#else
		#define _LAYOUT_OUT triangle_strip
        #define _MAX_VERTICES 3
	#endif
  #elif defined LinePrimitives

    #define _MAX_VERTICES 2
    #define _LAYOUT_IN lines
    #define _LAYOUT_OUT line_strip

  #elif defined PointPrimitives

    #define _MAX_VERTICES 1
    #define _LAYOUT_IN points
    #define _LAYOUT_OUT points

  #endif


  #ifndef CascadedShadow
    #define NB_CASCADES 1
  #endif // CascadedShadow


#ifndef GEOMETRY_SHADER_PASSTHROUGH
  layout(_LAYOUT_IN) in;
  layout(_LAYOUT_OUT, max_vertices=_MAX_VERTICES * NB_CASCADES) out;
  #define _NB_INVOCATION _MAX_VERTICES * NB_CASCADES
#else 
  layout(_LAYOUT_IN) in;
  #define _NB_INVOCATION _MAX_VERTICES * NB_CASCADES
#endif 



  //#ifndef VIEW_SPACE_ONLY
  //vec3 vGetWorldPos(int i){return VertexIn[i]._SBWorldPos;}
  //#endif

#ifndef PDSFX1
  vec3 vGetViewPos(int i){return VertexIn[i]._SBViewPos;}
#endif

  vec3 vGetViewPosition(int i){return VertexIn[i]._SBViewPos;}

#endif

/***************************************************************************** VertexStage and GeometryStage Output, Fragemnt Stage Input****************************************************************************/

#if defined FragmentStage || defined(RayHitStage)
  vec3 _SBModifiedWorldN;
  
  #ifdef TangentSpaceGeneration 
  //Not varyings
    vec3 _SBtangent, _SBbinormal; 
  #endif
#endif


#elif defined GLES3Platform
/************************************************************************************************* GLES3Platform ****************************************************************************/

#if defined VertexStage
#define VertexToFragment out
#elif defined FragmentStage
#define VertexToFragment in
#endif

#if defined VertexStage || defined FragmentStage

VertexToFragment vec3 _SBViewPos;
VertexToFragment vec3 _SBWorldN;
#ifndef VIEW_SPACE_ONLY
VertexToFragment vec3 _SBWorldPos;
#endif

#ifdef NeedUVs
VertexToFragment vec2 _SBuv;
#endif

#ifdef HasDecal
VertexToFragment vec2 _SBLegUVCoord;
#endif

#ifdef PDSFX1
VertexToFragment vec4 _SBstpq1;
VertexToFragment vec4 _SBstpq2;
#endif

  // (T, B, N) are the tangent space vectors
#ifdef UseTangentSpace
VertexToFragment vec3 _SBWorldT;
VertexToFragment vec3 _SBWorldB;
#endif

#if defined NeedProjPos
VertexToFragment vec4 _SBProjPos;
#endif

#if defined NeedViewPos
VertexToFragment vec4 _SBViewPosPostTransform;
#endif

#ifdef Clipping //array are not well packed in glsl, I prefer use those kind of datas
#ifndef kClipPlanesCount //to avoid compilation issue
#define kClipPlanesCount 1
#endif
VertexToFragment vec4 _SBSignedDistance4;
VertexToFragment vec2 _SBSignedDistance2;
#endif    

#ifdef GroundClipping
VertexToFragment float _SBSignedDistanceGround;
#endif

#ifdef OutputMotionVectorMap
VertexToFragment vec4 _ClipPos;
VertexToFragment vec4 _PrevClipPos; 
#endif

#endif

#if defined FragmentStage
  vec3 _SBModifiedWorldN;

  #ifdef TangentSpaceGeneration
    //Not varyings
    vec3 _SBtangent, _SBbinormal;
  #endif
#endif

#else
/************************************************************************************************* GLES2Platform ****************************************************************************/

/************************************************************************************************* GLES Fragment Stage ****************************************************************************/

#ifdef FragmentStage
varying vec3 _SBViewPos;
varying vec3 _SBWorldN;

#ifndef VIEW_SPACE_ONLY
  varying vec3 _SBWorldPos;
#endif

vec3 _SBModifiedWorldN;

#ifdef UseTangentSpace // (T, B, N) are the tangent space vectors
varying vec3 _SBWorldT;
varying vec3 _SBWorldB;
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

#if defined(TiledLighting) || defined(LogDepth)  || defined(Fog)
varying vec4 _SBProjPos;
#endif //UseTangentSpace

#ifdef Clipping
#ifndef kClipPlanesCount
#define kClipPlanesCount 1
#endif
varying vec4 _SBSignedDistance4;
varying vec2 _SBSignedDistance2;
#endif

#ifdef TangentSpaceGeneration
//Not varyings
vec3 _SBtangent, _SBbinormal;
#endif

#ifdef OutputMotionVectorMap
  varying vec4 _ClipPos;
  varying vec4 _PrevClipPos; 
#endif

#endif //VertexStage
#endif

/************************************************************************************************* Common API ****************************************************************************/
 
/************************************************************************************************* FragmentStage Common API ****************************************************************************/
#if defined(FragmentStage) || defined(RayHitStage)


#ifndef VIEW_SPACE_ONLY
  vec3 vGetWorldPos()
  {
    #ifdef RayHitStage
      return VARYING_OUTPUT_NAME._SBWorldPos;
    #else
      return _SBWorldPos;
    #endif
  }
#endif

#ifndef PDSFX1
  vec3 vGetViewPos()
  {
    #ifdef RayHitStage
      return VARYING_OUTPUT_NAME._SBViewPos;
    #else
      return _SBViewPos;
    #endif
  }

  vec3 vGetWorldN()
  {
    return _SBModifiedWorldN;
  }
#endif

vec3 vGetViewPosition()
{
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBViewPos;
  #else
    return _SBViewPos;
  #endif
}

vec2 _vPrivGetLightMapUVs()
{
#ifdef LightMap
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBLightMapUVs;
  #else
  return _SBLightMapUVs;
  #endif
#else
  return vec2(0.);
#endif
}


vec2 _vPrivGetLegacyUVs()
{
#ifdef HasDecal
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBLegUVCoord;
  #else
  return _SBLegUVCoord;
  #endif
#else
  return vec2(0.);
#endif
}

#if defined GPUMappingOperator || defined DecalLighting
//defined in  PhysicalMaterialMapping.glsl or DecalMapping.glsl
vec2 vGetUvs();
vec3 vGetTangent();
vec3 vGetBinormal();
#else

vec2 vGetUvs()
{
#ifdef NeedUVs
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBuv;
  #else
  return _SBuv;
  #endif
#else
  return vec2(0.);
#endif
}

vec3 vGetTangent()
{
#if defined TangentSpaceGeneration
  return _SBtangent;
#elif defined UseTangentSpace
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBWorldT;
  #else
  return _SBWorldT;
  #endif
#else
  return vec3(0.);
#endif
}

vec3 vGetBinormal()
{
#if defined TangentSpaceGeneration
  return _SBbinormal;
#elif defined UseTangentSpace  
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBWorldB;
  #else
  return _SBWorldB;
  #endif
#else
  return vec3(0.);
#endif  
}
#endif

vec4 vGetProjPos()
{
#if defined NeedProjPos
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBProjPos;
  #else
  return _SBProjPos;
  #endif
#else
  return vec4(0.);
#endif
}

vec4 vGetViewPosPostTransform()
{
#if defined NeedViewPos
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBViewPosPostTransform;
  #else
  return _SBViewPosPostTransform;
  #endif
#else
  return vec4(0.);
#endif
}

vec3 _SBModifiedViewN;
vec3 _SBViewTangent;
vec3 _SBViewBinormal;

vec3 vGetViewNormal()
{
  return _SBModifiedViewN;
}

vec3 vGetViewTangent()
{
  return _SBViewTangent;
}

vec3 vGetViewBinormal()
{
  return _SBViewBinormal;
}

#ifdef PDSFX1
vec4 vGetTexCoord0()
{
  return vec4(vGetUvs(), 0.0, 0.0);
}

vec4 vGetTexCoord1()
{
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBstpq1;
  #else
  return _SBstpq1;
  #endif
}

vec4 vGetTexCoord2()
{
  #ifdef RayHitStage
    return VARYING_OUTPUT_NAME._SBstpq2;
  #else
  return _SBstpq2;
  #endif
}
#endif

vec4 vGetClipSpacePosition()
{
  return vGetProjPos();
}

vec2 vGetMotionVector()
{
#ifdef OutputMotionVectorMap
  vec2 p = (_ClipPos.xy / _ClipPos.w) * 0.5 + 0.5;
  vec2 pp = (_PrevClipPos.xy / _PrevClipPos.w) * 0.5 + 0.5;
  return p - pp;
#else
  return vec2(0.0);
#endif
}

#ifndef GLES2Platform
  bool vGetZTestResult(inout bool oResult); //implemented in the file pdsfxCommons.glsl
#endif

#endif //defined FragmentStage || defined RayHitStage

#if defined(VertexStage) || defined(TessEvaluationStage) || defined(GeometryStage) || defined(RayHitStage)

/************************************************************************************************* VertexStage or Evaluation Stage Common API ****************************************************************************/

#ifdef NeedProjPos

  void vSetProjPos(vec4 iProjPos)
  {
    #ifdef VertexStage
        _SBProjPos = iProjPos;
    #else
        VARYING_OUTPUT_NAME._SBProjPos = iProjPos;
    #endif
  }

#endif

#ifdef NeedViewPos

  void vSetViewPosPostTransform(vec4 iViewPos)
  {
    #ifdef VertexStage
        _SBViewPosPostTransform = iViewPos;
    #else
        VARYING_OUTPUT_NAME._SBViewPosPostTransform = iViewPos;
    #endif
  }

#endif

#ifdef NeedUVs
  
  void vSetUV(vec2 iUV)
  {
  #ifdef VertexStage
      _SBuv = iUV;
  #else
      VARYING_OUTPUT_NAME._SBuv = iUV;
  #endif
  }
#endif

#ifdef HasDecal
  
  void _vPrivSetLegacyUVs(vec2 iUV)
  {
  #ifdef VertexStage
      _SBLegUVCoord = iUV;
  #else
      VARYING_OUTPUT_NAME._SBLegUVCoord = iUV;
  #endif
  }
#endif

#ifdef PDSFX1
  void _vPrivSetSTPQ1(vec4 iSTPQ)
  {
  #ifdef VertexStage
      _SBstpq1 = iSTPQ;
  #else
      VARYING_OUTPUT_NAME._SBstpq1 = iSTPQ;
  #endif
  }

  void _vPrivSetSTPQ2(vec4 iSTPQ)
  {
  #ifdef VertexStage
      _SBstpq2 = iSTPQ;
  #else
      VARYING_OUTPUT_NAME._SBstpq2 = iSTPQ;
  #endif
  }
#endif

#ifdef LightMap
  void _vPrivSetLightMapUVs(vec2 iUV)
  {
  #ifdef VertexStage
    _SBLightMapUVs = iUV;
  #else
    VARYING_OUTPUT_NAME._SBLightMapUVs = iUV;
  #endif
  }
#endif

  void vSetViewPos(vec3 iViewPos)
  {
    #ifdef VertexStage
        _SBViewPos = iViewPos;
    #else
        VARYING_OUTPUT_NAME._SBViewPos = iViewPos;
    #endif
  }

  void vSetWorldN(vec3 iWorldNormal)
  {
    #ifdef VertexStage
        _SBWorldN = iWorldNormal;
    #else
        VARYING_OUTPUT_NAME._SBWorldN = iWorldNormal;
    #endif
  }

 #ifdef UseTangentSpace

  void vSetTangentBiNorm(vec3 iT, vec3 iN)
  {
    #ifdef VertexStage
        _SBWorldT = iT;
        _SBWorldB = iN;
    #else
        VARYING_OUTPUT_NAME._SBWorldT = iT;
        VARYING_OUTPUT_NAME._SBWorldB = iN;
    #endif
  }
 #endif

 #ifndef VIEW_SPACE_ONLY

  void vSetWorldPos(vec3 iWorldPos)
  {
    #ifdef VertexStage
      _SBWorldPos = iWorldPos;
    #else
      VARYING_OUTPUT_NAME._SBWorldPos = iWorldPos;
    #endif
  }

 #endif

 #ifdef Clipping
  void vSetClippingDistance(vec4 iDistance4, vec2 iDistance2)
  {
    #ifdef VertexStage
      _SBSignedDistance4 = iDistance4;
      _SBSignedDistance2 = iDistance2;
    #else
      VARYING_OUTPUT_NAME._SBSignedDistance4 = iDistance4;
      VARYING_OUTPUT_NAME._SBSignedDistance2 = iDistance2;
    #endif
  }
 #endif

 #ifdef GroundClipping
   void vSetGroundClipping(float iDistance)
   {
      #ifdef VertexStage
        _SBSignedDistanceGround = iDistance;
      #else
        VARYING_OUTPUT_NAME._SBSignedDistanceGround   = iDistance;
      #endif
   }
 #endif

#ifdef OutputMotionVectorMap
  void vSetClipPos(vec4 iPos)
   {
      #ifdef VertexStage
        _ClipPos = iPos;
      #else
        VARYING_OUTPUT_NAME._ClipPos = iPos;
      #endif
   }

   void vSetPrevClipPos(vec4 iPos)
   {
      #ifdef VertexStage
        _PrevClipPos = iPos;
      #else
        VARYING_OUTPUT_NAME._PrevClipPos = iPos;
      #endif
   }
#endif

#endif

#ifdef TessControlStage

#ifndef PDSFX1
  vec3 vGetViewPos(int i)
  {
    return VertexIn[i]._SBViewPos;
  }
#endif

  vec3 vGetViewPosition(int i)
  {
    return VertexIn[i]._SBViewPos;
  }

#endif //TessEvaluationStage


