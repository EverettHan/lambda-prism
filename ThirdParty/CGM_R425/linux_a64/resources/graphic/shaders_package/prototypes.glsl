//DSFX protoypes declaration
//Prototypes of functions called by the master shader
//Should not be dclared elsewhere 

#if defined VertexStage || defined TessEvaluationStage

//Returns position in object space
vec3 GetLocalPosition();

//position is the position after the WorldViewProj transformation
//Expected behaviour : gl_Position = position
void TransformFinalPosition(inout vec4 position);

// place common computation here : to check
void ComputeCommonValues();

// customize this function to handle additionnal vertex transformations
// 'Pos' in vOut will already have been written when this function is called, and can be modified is desired
void ProcessVertexCustom();

// Customize this function to change the tangent space
// Tangent space coordinates are in world
void ProcessTangentSpaceCustom(inout TangentSpace worldTS);

#ifdef PDSFX1
void ProcessClipSpacePosition(inout vec4 ioPosition);
void ComputeVaryingValues();
float ComputePointSize();
vec3 ComputeObjectPosition();
vec3 ComputeObjectNormal();
vec3 ComputeObjectTangent();
vec3 ComputeObjectBinormal();
void ProcessViewTangentSpace(inout TangentSpace viewTS);
vec4 ComputeObjectTexCoord0();
vec4 ComputeObjectTexCoord1();
vec4 ComputeObjectTexCoord2();

#ifdef ZTestAnnotation
bool ProcessAnchorPosition();
#endif // ZTestAnnotation

#endif

#elif defined TessControlStage

// Do not use it !
void ComputeTessellation();

#elif defined GeometryStage

void ProcessVertexCustom(in int iVertex);
void TransformFinalPosition(in int i, inout vec4 position);

#ifdef PDSFX1
void ComputeCommonValues();
void ProcessClipSpacePosition(in int iVertexID, inout vec4 ioPosition);
void ComputeVaryingValues(in int iVertexID);
void ComputeCustomStreams();
#endif

#elif defined(FragmentStage) || defined(RayHitStage)

#ifdef Coating
  vec3 ComputeWorldCoatingN();
#endif

#ifdef Flakes
  vec3 ComputeWorldMetalFlakesN();
  vec3 ComputeWorldPearlFlakesN();
#endif

//Initialization of the cv object
void ComputeCommonValues();

// NOT AVAILABLE IN PDSFX0
// Multiple Render Targets support. The default is to output the lit or (unlit if lighting disabled)
// fragment color (the 'fragColor' input parameter) to the first render target, but additionnal 
// value may be added here
void OutputMRT(vec4 finalColor);

//returns the emissive contribution at the fragment
vec3 ComputeEmissive();

void ProcessBRDFParameters(inout BRDFParameters ioParams);

#ifdef PDSFX1
  bool ComputeDiscard();
  vec3 ComputeViewPosition();
  vec3 ComputeViewNormal();
  vec3 ComputeSpecularReflectance();
  float ComputeOpacity();
  float ComputeRoughness();
  float ComputeTransparency();
#else
  // for transparency (1 is completely opaque material)
  float ComputeAlpha();

  //Returns Normal Vector in WorldSpace
  vec3 ComputeWorldNormal();

  // additionnal clip instruction go here (example : alpha test)
  void PerformClipping();

  //Specular Color used in the lighting
  vec3 ComputeSpecularColor();
#endif

//Modifies the final color of the fragment 
#ifdef PDSFX1
  void ProcessCappingParameters(in vec3 iViewPos, inout vec3 iViewNorm, inout vec3 iAlbedo);
  void ProcessFinalColor(inout vec4 ioFinalColor);
#elif defined(PDSFX0)
  void ProcessFinalColor(inout vec3 ioFinalColor);
#endif

vec3 ComputeAlbedo();


#ifdef SparseTexturePrepass
  void ComputeSparseTextureData(out float oMipmalLevel, out ivec3 oFragmentTexelCoord);
#endif

#endif

#ifdef ClosestHitStage
  vec3 ComputeViewNormal();
  vec3 ComputeAlbedo();
  void ComputeCommonValues();
#endif
