#ifndef LogDepth
  #if defined(DecalTranspar) && !defined(DecalLighting)
    layout(early_fragment_tests) in;
  #endif
#endif

#if defined(DecalTranspar)
  //uniform coherent layout(r32ui) uimage2DArray DecalTransparZMap;

  struct DecalTransparData_t
  {
    uvec4 first;
    uvec4 second;
    uvec4 third;
  };

  //layout(std430) coherent restrict buffer DecalTransparData
  //{
  //  DecalTransparData_t g_DecalTransparData[];
  //};
#endif

#if !defined(GLESPlatform) && (GLSLVersion >= 400)
// Operators << and >> are not compatible on mobile

uint _CompactDepthStencil(in float iDepth, in uint iStencil)
{
  float normz = clamp(iDepth, -1.0, 1.0);
  float linz = floor(normz * (1 << 23));
  uint linUintZ = uint(int(linz) + (1 << 23)); // faudrait peut etre clamp à 1 << 24 - 1
  uint res = (linUintZ << 8) | iStencil; 
  return res;
}

void _UnpackDepthStencil(in uint iValue, out float oDepth, out uint oStencil)
{
  uint linUintZ = iValue >> 8;
  int linIntZ = int(linUintZ  - (1 << 23) ); 
  oDepth = (float(linIntZ) / float(1 << 23)); 
  oStencil = (iValue & 0xFFu);
}

#endif

vec4 ComputeViewPositionFromDepth(in vec2 iProjPos, in float iDepth)
{
  vec4 viewPos;

  #ifndef LogDepth
    viewPos = vGetProjInverseMatrix() * vec4(iProjPos, iDepth*2.0-1.0, 1.0);
    viewPos /= viewPos.w;
  #else
    float NearPlane = vGetNearFarLogFactor().x;
    float LogZFactor = vGetNearFarLogFactor().z;
  
    viewPos.z = -vExp(iDepth/LogZFactor) * NearPlane;

    vec4 screenPos = (vGetProjMatrix() * vec4(0.0, 0.0, viewPos.z, 1.0));
    screenPos.z /= screenPos.w;
    
    viewPos.xyw = (vGetProjInverseMatrix() * vec4(iProjPos, screenPos.z, 1.0)).xyw;
    viewPos.xyw /= viewPos.w;
  #endif

  return viewPos;
}

void ComputeDecals(out vec3 oViewPos, out float oDepth)
{
  #ifdef DecalLighting
    float depth;
    vec4 viewPos;
    vec3 localPos;
  
    //Convert depth to position in the decal's object space
    vec4 projPos = vGetProjPos();
    projPos/=projPos.w;
    
    vec3 normalFromNormalMap;
    vec2 decaluvs;

    #ifdef DecalTranspar
      if(!gl_FrontFacing)
        discard;

      int i;
      const uint numLayers = 5;
      uint ind = uint(gl_FragCoord.y) * uint(imageSize(DecalTransparZMap).x) + uint(gl_FragCoord.x);
      for(i=0; i<numLayers; ++i)
      {
        ivec3 fragPosList = ivec3(gl_FragCoord.xy, i);
        uint depthInList = imageLoad(DecalTransparZMap, fragPosList).x;

        if(depthInList == 0xFFFFFFFFu)
          discard;

        uint stencil;
        _UnpackDepthStencil(depthInList, depth, stencil);
        //depth = uintBitsToFloat(depthInList);

        if(stencil == 0x0u)
          continue;

        if(stencil < cb_cbVolMaterial.u_DecalID)
          continue;

        viewPos = ComputeViewPositionFromDepth(projPos.xy, depth);
        localPos = vec3(transpose(vGetWorldViewInverseTransposeMatrix()) * viewPos);
        //localPos = vec3(transpose(_vPrivGetWorldInverseTransposeMatrix()) * vGetViewInverseMatrix() * viewPos);

        if(all(lessThanEqual(abs(localPos), vec3(0.5))))
        {
          vec4 data2 = uintBitsToFloat(g_DecalTransparData[numLayers * ind + i].second);
          normalFromNormalMap = vec3(data2.xy, sqrt(1.0 - dot(data2.xy, data2.xy)));
          decaluvs = data2.zw;
          break;
        }
      }

      if(i==numLayers)
        discard;

    #else
      #if defined(IS_MSAA)
        depth = vTexelFetch(DecalZMap, ivec2(gl_FragCoord.xy), gl_SampleID).x;
        normalFromNormalMap = vNormalize(vTexelFetch(DecalNormalMap, ivec2(gl_FragCoord.xy), gl_SampleID).xyz*2-1);
        decaluvs = vTexelFetch(DecalUVMap, ivec2(gl_FragCoord.xy), gl_SampleID).xy;
      #else
        depth = vTexelFetch(DecalZMap, ivec2(gl_FragCoord.xy), 0).x;
        normalFromNormalMap = vNormalize(vTexelFetch(DecalNormalMap, ivec2(gl_FragCoord.xy), 0).xyz*2-1);
        decaluvs = vTexelFetch(DecalUVMap, ivec2(gl_FragCoord.xy), 0).xy;
      #endif

      viewPos = ComputeViewPositionFromDepth(projPos.xy, depth);
      localPos = vec3(transpose(vGetWorldViewInverseTransposeMatrix()) * viewPos);
      //localPos = vec3(transpose(_vPrivGetWorldInverseTransposeMatrix()) * vGetViewInverseMatrix() * viewPos);

    #endif

    //Discard if position is outside the decal box
    if(any(greaterThan(abs(localPos), vec3(0.5))))
      discard;

    //Update normal for decal normal mapping 
    _decalNormal = normalize(vec3(vGetViewInverseMatrix() * vec4(normalFromNormalMap, 0.0)));

    //normal for decal mapping operator
    vec3 localNormal = normalize(vec3(transpose(_vPrivGetWorldInverseTransposeMatrix()) * vec4(_decalNormal, 0.0)));
  
    #ifdef PhysicalMaterial
      _worldNormal = normalFromNormalMap;
    #endif

    #if !defined(DecalMappingOperator) || (DecalMappingOperator == DecalMappingExplicit) //Explicit mapping
      pmDecalTexCoords = decaluvs;
    #else
        vec3 X = vec3(1.0, 0.0, 0.0);
        vec3 Y = vec3(0.0, 1.0, 0.0);
        vec3 Z = vec3(0.0, 0.0, 1.0);

        ComputeMapping(localPos, localNormal, X, Y, Z);
    #endif
  
    //Update view pos for ibl parallax correction
    oViewPos = viewPos.xyz;

    oDepth = depth;
  #endif
}
