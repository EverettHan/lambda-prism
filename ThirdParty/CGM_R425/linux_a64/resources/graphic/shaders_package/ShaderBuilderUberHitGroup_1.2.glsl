layout(location = 0) rayPayloadInEXT Payload_t g_Payload;

hitAttributeEXT vec2 g_HitAttributes;

float CopySign(in float iBase, in float iSign)
{
  return iSign >= 0.0f ? vAbs(iBase) : -vAbs(iBase);
}

vec3 DecodeUnitVector(in uint iData)
{
  vec2 coords = unpackSnorm2x16(iData);
  float z = 1.0f - abs(coords.x) - abs(coords.y);
  vec3 n = (z >= 0.0f) ? vec3(coords, z) : vec3(CopySign(1.0f - abs(coords.y), coords.x), CopySign(1.0f - abs(coords.x), coords.y), z);
  return normalize(n);
}

void _FetchVertexAttrib2f(in int iAttribIndex, in uint iIndices[3], inout Vertex_t ioVertex[3], in ObjectDesc_t iObj, in ObjectFormat_t iObjFormat)
{  
  uint bufIndex = iObjFormat.attribMapping[iAttribIndex];
  Vertices ptr = Vertices(iObj.bufferAddr[bufIndex]);
  uint stride = iObjFormat.vertexStride[bufIndex] / 4;
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<2; j++)
        ioVertex[i].attrib[iAttribIndex][j] = uintBitsToFloat(ptr.data[stride * iIndices[i]+j]);
  }
}

void _FetchVertexAttrib3f(in int iAttribIndex, in uint iIndices[3], inout Vertex_t ioVertex[3], in ObjectDesc_t iObj, in ObjectFormat_t iObjFormat)
{  
  uint bufIndex = iObjFormat.attribMapping[iAttribIndex];
  Vertices ptr = Vertices(iObj.bufferAddr[bufIndex]);
  uint stride = iObjFormat.vertexStride[bufIndex] / 4;
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
        ioVertex[i].attrib[iAttribIndex][j] = uintBitsToFloat(ptr.data[stride * iIndices[i]+j]);
  }
}

void _FetchVertexAttrib3f_decode(in int iAttribIndex, in uint iIndices[3], inout Vertex_t ioVertex[3], in ObjectDesc_t iObj, in ObjectFormat_t iObjFormat)
{  
  uint bufIndex = iObjFormat.attribMapping[iAttribIndex];
  Vertices ptr = Vertices(iObj.bufferAddr[bufIndex]);
  uint stride = iObjFormat.vertexStride[bufIndex] / 4;
  for(int i=0; i<3; i++)
    ioVertex[i].attrib[iAttribIndex] = DecodeUnitVector(ptr.data[stride * iIndices[i]]);
}

uint ComputeVertexAttribs(in vec3 iBarycentrics)
{
  //Vertices
  int instanceIndex = vGetInstanceCustomIndex();
  
  ObjectDesc_t obj = g_ObjectDesc.data[instanceIndex];
  ObjectFormat_t objFormat = g_ObjectFormat.data[instanceIndex];
  
  int id = vGetPrimitiveID();

  uint ind[3];

  if(objFormat.indexSize == 2) // 16 bit indices
  {
    Indices16 ptrIndices = Indices16(obj.indexAddr);

    for(int i=0; i<3; i++)
      ind[i] = ptrIndices.data[3 * id + i];

  }
  else // 32 bit indices
  {
    Indices32 ptrIndices = Indices32(obj.indexAddr);
    
    for(int i=0; i<3; i++)
      ind[i] = ptrIndices.data[3 * id + i];
  }
  
  //Vertex attribs
  Vertex_t v[3];
  
  _FetchVertexAttrib3f(EAttribIndicesPosition, ind, v, obj, objFormat);
    
  if(objFormat.compressedNormal == 0)
  {
    #ifdef UseNormal
      _FetchVertexAttrib3f(EAttribIndicesNormal, ind, v, obj, objFormat);
    #endif

    #ifdef NeedTangent
      _FetchVertexAttrib3f(EAttribIndicesTangent, ind, v, obj, objFormat);
    #endif

    #ifdef NeedBinormal
      _FetchVertexAttrib3f(EAttribIndicesBinormal, ind, v, obj, objFormat);
    #endif
  }
  else
  {
    #ifdef UseNormal
      _FetchVertexAttrib3f_decode(EAttribIndicesNormal, ind, v, obj, objFormat);
    #endif

    #ifdef NeedTangent
      _FetchVertexAttrib3f_decode(EAttribIndicesTangent, ind, v, obj, objFormat);
    #endif

    #ifdef NeedBinormal
      _FetchVertexAttrib3f_decode(EAttribIndicesBinormal, ind, v, obj, objFormat);
    #endif
  }

  _FetchVertexAttrib2f(EAttribIndicesTexCoord0, ind, v, obj, objFormat);

  // interpolate
  vec3 attribs[EAttribIndicesCount];

  for(int i=0; i<EAttribIndicesCount; i++)
  {
    attribs[i] = vec3(0.0);

    for(int j=0; j<3; j++)
      attribs[i] += v[j].attrib[i] * iBarycentrics[j];
  }


  // assign to stream slots
  _SBPosition = attribs[EAttribIndicesPosition];

  #ifdef UseNormal
    _SBNormal = attribs[EAttribIndicesNormal];
  #endif

  #ifdef NeedUVs
    _SBTexCoord0.xy = attribs[EAttribIndicesTexCoord0].xy;
  #endif

  #ifdef NeedTangent
    _SBTangent = attribs[EAttribIndicesTangent];
  #endif
  
  #ifdef NeedBinormal
    _SBBinormal = attribs[EAttribIndicesBinormal];
  #endif

  return objFormat.material;
}

#ifdef EVisuPBR
  vec3 EVisuPBR_vLocalPosition;
  vec3 EVisuPBR_vLocalNormal;
#elif defined(PhysicalMaterial)
  vec3 v_ObjectSpacePosition;
  vec3 v_ObjectSpaceNormal;
#else
  vec3 vTexCoord;
#endif


vec3 FragmentMain()
{
  vec3 _worldNormal = vNormalize(VARYING_OUTPUT_NAME._SBWorldN);

  vec3 viewOrigin = vec3(vGetViewMatrix() * vec4(gl_WorldRayOriginEXT, 1.0));

  vec3 _view = vNormalize(viewOrigin - vGetViewPosition());

  //In otho we use the forward vector as the view vector.
  {
    mat4 viewMat = vGetViewMatrix();
    vec3 lookAt = vec3(viewMat * vec4(normalize(vec3(viewMat[0].z, viewMat[1].z, viewMat[2].z)), 0.0));
    float fact = vStep(0.0, vGetProjMatrix()[2].w);
    _view = mix(_view, lookAt, fact);
  }

  _SBModifiedWorldN = vNormalize(vGetOrientedNormal(_worldNormal, _view));

  #ifdef TangentSpaceGeneration

    _SBModifiedViewN = (vGetViewMatrix() * vec4(_SBModifiedWorldN, 0.)).xyz;

    _SBComputeTangentSpace(VARYING_OUTPUT_NAME._SBViewPos, VARYING_OUTPUT_NAME._SBuv, _SBModifiedViewN, _SBViewTangent, _SBViewBinormal);

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

  ComputeCommonValues();
  
  vec3 finalColor = vec3(0.0);
  vec3 albedo = ComputeAlbedo();
  float alpha = 1.0;

  #ifdef Lighting

    LightingData data;
    BRDFParameters brdf;

    vec3 viewNormal = ComputeViewNormal();
    vec3 myWorldNormal = vec3(vGetViewInvMatrix() * vec4(viewNormal, 0.0));

    #ifdef Coating
      vec3 myCoatingWorldNormal = ComputeWorldCoatingN();
    #endif
    
    vec3 viewPos = vGetViewPosition();
    

    data = ComputeStdLightingData(viewPos, vNormalize(viewNormal), _view);
    data.Vworld = (vGetViewInverseMatrix() * vec4(_view, 0.)).xyz;
    

    #ifdef ImageBasedLighting
      data.VworldTransformed = ComputeTransformation(data.Vworld);
    #endif

    data.Nworld = vNormalize(myWorldNormal);
    

    #if defined(EVisuPBR) || defined(XRiteCarPaint2)
    #else
      brdf.albedo = albedo;
      brdf.f0 = vec3(0.04);
      brdf.f90 = vec3(1.0);
      brdf.roughness = 1.0;
      brdf.transparency = 0.0;
    #endif
    
      ProcessBRDFParameters(brdf);
      
    #ifndef XRiteCarPaint2
      #ifndef V_DISABLE_GLOSSINESS_SMOOTHING
        ComputeGlossinessSmoothing(data, brdf); //See glossiness.glsl
      #endif
      ComputeGlossinessClamping(brdf); //See glossiness.glsl
    #endif // !XRiteCarPaint2

    #ifdef EVisuPBR
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
    vec3 fragIBLRefl = vec3(0.0);
    vec4 compositingColor = DoFragmentLightingCompositing(data, brdf, fragIBLRefl.xyz,fresnel);
    finalColor = compositingColor.rgb;
    alpha = compositingColor.a;
  #endif

  return finalColor;
}



void main()
{
  #ifdef DEBUG_BVH
    g_Payload.hitIndex = gl_InstanceID;
  #else
    const vec3 barycentrics = vec3(1.0 - g_HitAttributes.x - g_HitAttributes.y, g_HitAttributes.x, g_HitAttributes.y);
  
    uint matID = ComputeVertexAttribs(barycentrics);
  
    _ProcessVertexOperation(false);

    SBInitConstantBuffers(g_ObjectDesc.uniformsAddr, g_MaterialBuffer.data[matID].perMaterialConstantBufferOffsets);
    SBInitTextures(g_MaterialBuffer.data[matID].textures);

    #ifdef EVisuPBR
      EVisuPBR_vLocalPosition = _SBPosition;
      EVisuPBR_vLocalNormal = _SBNormal;
    #endif
  
    #ifdef PhysicalMaterial
      v_ObjectSpacePosition = _SBPosition;
      v_ObjectSpaceNormal = _SBNormal;
    #endif

    g_Payload.color = FragmentMain();
    g_Payload.isHit = true;
  #endif
}

