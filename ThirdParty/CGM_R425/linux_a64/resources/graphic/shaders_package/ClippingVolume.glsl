#if defined(ClippingVol) && (defined(GLESPlatform) || !defined(kClipVolMethod) || !defined(ClippingVolAllowed) || 0 == ((1 << kClipVolMethod) & ClippingVolAllowed))
  // Disable sectioning for mobile and some passes (like mirroring)
  #undef ClippingVol
#endif

#ifdef ClippingVol

  struct ClippingVolumeData_t
  {
    mat4 boundingBoxInverseTransform;
    uvec2 octreeOffsetDepth;
    vec2 padding;
  };

  struct OctreeNodeData_t
  {
    // for leaf nodes : 8 signed distances packed into 8x8 bit integers
    // for non leaf nodes : children offset (uint), children mask (uint)
    uvec2 nodeData;
  };

  #define ClipVolMethod_TriangleListOctree 1
  #define ClipVolMethod_DistanceFieldOctree 2
  #define ClipVolMethod_FullscreenMap 3

  #if (kClipVolMethod == ClipVolMethod_FullscreenMap)

    //uniform samplerBuffer clippingVolumeData;

    void PerformClippingVolumeDiscard()
    {
      ivec2 screenSize = vTextureSize(clippingVolumeTex, 0).xy;
      vec2 screenCoord = vec2(gl_FragCoord.x/float(screenSize.x), gl_FragCoord.y/float(screenSize.y));

      #ifdef ClipVolMapAsArray
        int offsetInt = vTexture(clippingVolumeTex, vec3(screenCoord,float(cb_ClippingAdvanced.u_ClipVolMapID))).r;
      #else
        int offsetInt = vTexture(clippingVolumeTex, screenCoord).r;
      #endif

      vec4 clipData = vTexelFetch(clippingVolumeData, offsetInt);
      int nbClipPlanes = int(floor(clipData.x+0.5));

      vec4 pos = vec4(vGetViewPosition(), 1.0);
      vec3 eyeDir = vec3(0.0,0.0,1.0); // Orthogonal
      if ((vGetProjMatrix())[2].w < 0.0) // Perspective
        eyeDir = vNormalize(_vPrivGetViewEyePos()-vGetViewPosition());

      vec4 clipEq = vec4(0.0);
      int planeAfterCount = 0;
      int i = 0;
      for(i = 0; i < nbClipPlanes; i++)
      {
        offsetInt += 1;
        clipEq = vTexelFetch(clippingVolumeData, offsetInt);

        float clipVal = dot(clipEq, pos);
        float k = -clipVal / dot(clipEq.xyz, eyeDir);
        if (k < 0.0)
          planeAfterCount++;
      }
      #ifdef kClipVolDirMode
        if ((planeAfterCount%2) == (1-kClipVolDirMode))
          discard;
      #else
        if ((planeAfterCount%2) == 1)
          discard;
      #endif
    }


  #else

    #if (kClipVolMethod == ClipVolMethod_DistanceFieldOctree)

      //layout(std430) readonly restrict buffer ClippingVolumeData
      //{
      //  ClippingVolumeData_t g_ClippingVolumeData[];
      //};

      //layout(std430) readonly restrict buffer OctreeData
      //{
      //  OctreeNodeData_t g_OctreeData[];
      //};
     
     #ifdef ClipVolDebug
     float PerformDistanceFieldDiscard(uvec2 n, vec3 cellCoordinates)
     #else
     bool PerformDistanceFieldDiscard(uvec2 n, vec3 cellCoordinates)
     #endif
     {
        // trilinear interpolation
        vec4 distances[] = {vUnpackSnorm4x8(n[0]), vUnpackSnorm4x8(n[1])};
        const vec4 dXY = vMix(distances[0], distances[1], cellCoordinates.z);
        const vec2 dY = vMix(dXY.xz, dXY.yw, cellCoordinates.x);
        const float interpolatedDistance = vMix(dY.x, dY.y, cellCoordinates.y);
        
      #ifdef ClipVolDebug
        return interpolatedDistance;
      #else
        return interpolatedDistance < 0.0;
      #endif
      }

    #elif (kClipVolMethod == ClipVolMethod_TriangleListOctree)
    
      float copySign(in float iBase, in float iSign)
      {
        return iSign >= 0.0f ? vAbs(iBase) : -vAbs(iBase);
      }
      vec3 compress_Octahedron_Unproject(in vec2 iCoords)
      {
        float z = 1.0f - vAbs(iCoords.x) - vAbs(iCoords.y);
        vec3 n = z >= 0.0f ?
          vec3(iCoords, z) :
          vec3(copySign(1.0f - vAbs(iCoords.y), iCoords.x),
                 copySign(1.0f - vAbs(iCoords.x), iCoords.y),
                 z);
        return vNormalize(n);
      }

      struct VertexData_t
      {
        vec3 position;
        float padding;
        vec3 normal;
        float padding2;
      };

      struct TriangleData_t
      {
//        vec3 normal;
//        uint vertexA;
//        vec3 edgeNormalAB;
//        uint vertexB;
//        vec3 edgeNormalBC;
//        uint vertexC;
//        vec3 edgeNormalAC;
//        float invDenom; // = 1.0 / (uDotV * uDotV - uDotU * vDotV)
        uvec3 indices;
        float invDenom;
        uvec4 normals;
      };

      struct TriangleReference_t
      {
        uint reference;
      };

      //layout(std430) readonly restrict buffer ClippingVolumeData
      //{
      //  ClippingVolumeData_t g_ClippingVolumeData[];
      //};

      //layout(std430) readonly restrict buffer VertexData
      //{
      //  VertexData_t g_VertexData[];
      //};
      //
      //layout(std430) readonly restrict buffer TriangleData
      //{
      //  TriangleData_t g_TriangleData[];
      //};

      //layout(std430) readonly restrict buffer OctreeData
      //{
      //  OctreeNodeData_t g_OctreeData[];
      //};

      //layout(std430) readonly restrict buffer TriangleReferences
      //{
      //  TriangleReference_t g_TriangleReferences[];
      //};

      bool PerformTriangleListDiscard(const uint triangleRefBegin, const uint triangleRefEnd, const vec3 point)
      {
        vec3 normal;
        vec3 minProjection;
        float minDistance = 4.0; // all distances are less than sqr(sqrt(3)) since all points are contained inside an unit cube

        //mat2x4 minPointInfo; // 1st column : normal, 2nd column : point position, squared distance
        //minPointInfo[1].w = 4.0;

        for (uint j = triangleRefBegin; j < triangleRefEnd; j++)
        {
          const TriangleData_t triangleData = g_TriangleData[g_TriangleReferences[j].reference];
          VertexData_t vertices[3];

          for (int i = 0; i < 3; ++i)
            vertices[i] = g_VertexData[triangleData.indices[i]];

//          const VertexData_t vertexA = g_VertexData[triangleData.indices[0]],
//            vertexB = g_VertexData[triangleData.indices[1]],
//            vertexC = g_VertexData[triangleData.indices[2]];
          
          const vec2 uncompressedNormals[4] = {
            vUnpackSnorm2x16(triangleData.normals[0]),
            vUnpackSnorm2x16(triangleData.normals[1]),
            vUnpackSnorm2x16(triangleData.normals[2]),
            vUnpackSnorm2x16(triangleData.normals[3])
          };
          const vec3 triangleNormal = compress_Octahedron_Unproject(uncompressedNormals[0]);
          const vec3 edgeNormals[3] = {
            compress_Octahedron_Unproject(uncompressedNormals[1]),
            compress_Octahedron_Unproject(uncompressedNormals[2]),
            compress_Octahedron_Unproject(uncompressedNormals[3])
          };
//          const VertexData_t vertexA = g_VertexData[triangleData.vertexA],
//            vertexB = g_VertexData[triangleData.vertexB],
//            vertexC = g_VertexData[triangleData.vertexC];
//
          const float distanceToPlane = vDot(triangleNormal, vertices[0].position - point);
//          const float distanceToPlane = vDot(triangleData.normal, vertexA.position - point);
          const float squaredDistanceToPlane = distanceToPlane * distanceToPlane;
          const vec3 projection = point + distanceToPlane * triangleNormal;
//          const vec3 projection = point + distanceToPlane * triangleData.normal;
          const vec3 u = vertices[1].position - vertices[0].position;
          const vec3 v = vertices[2].position - vertices[0].position;
          const vec3 m = vertices[2].position - vertices[1].position;
          const vec3 w = projection - vertices[0].position;
//          const vec3 u = vertexB.position - vertexA.position;
//          const vec3 v = vertexC.position - vertexA.position;
//          const vec3 m = vertexC.position - vertexB.position;
//          const vec3 w = projection - vertexA.position;

          const float uDotU = vDot(u, u);
          const float uDotV = vDot(u, v);
          const float vDotV = vDot(v, v);
          const float wDotU = vDot(w, u);
          const float wDotV = vDot(w, v);
          const float lambda = (uDotV * wDotV - vDotV * wDotU) * triangleData.invDenom,
            mu = (uDotV * wDotU - uDotU * wDotV) * triangleData.invDenom;

          if (squaredDistanceToPlane < minDistance && lambda > 0.0 && mu > 0.0 && lambda + mu < 1.0)
          {
            minProjection = point - projection;
            minDistance = squaredDistanceToPlane;
            normal = triangleNormal;
//            normal = triangleData.normal;
            //minPointInfo = mat2x4(vec4(triangleData.normal, 0.0),
            //  vec4(point - projection, squaredDistanceToPlane));
          }
          else
          {
            vec3 candidate = point - vertices[0].position - vClamp(vDot(w, u) / uDotU, 0.0, 1.0) * u;
//            vec3 candidate = point - vertexA.position - vClamp(vDot(w, u) / uDotU, 0.0, 1.0) * u;
            float candidateMinDistance = vDot(candidate, candidate);
            if (candidateMinDistance < minDistance)
            {
              minProjection = candidate;
              minDistance = candidateMinDistance;
              normal = edgeNormals[0];
//              normal = triangleData.edgeNormalAB;
            }
            //smaller = vStep(candidateMinDistance, minPointInfo[1].w);
            //minPointInfo[0] = vMix(minPointInfo[0],
            //  vec4(triangleData.edgeNormalAB, 0.0), smaller);
            //minPointInfo[1] = vMix(minPointInfo[1],
            //  vec4(candidate, candidateMinDistance), smaller);

            candidate = point - vertices[0].position - vClamp(vDot(w, v) / vDotV, 0.0, 1.0) * v;
//            candidate = point - vertexA.position - vClamp(vDot(w, v) / vDotV, 0.0, 1.0) * v;
            candidateMinDistance = vDot(candidate, candidate);
            if (candidateMinDistance < minDistance)
            {
              minProjection = candidate;
              minDistance = candidateMinDistance;
              normal = edgeNormals[2];
//              normal = triangleData.edgeNormalAC;
            }
            //smaller = vStep(candidateMinDistance, minPointInfo[1].w);
            //minPointInfo[0] = vMix(minPointInfo[0],
            //  vec4(triangleData.edgeNormalAC, 0.0), smaller);
            //minPointInfo[1] = vMix(minPointInfo[1],
            //  vec4(candidate, candidateMinDistance), smaller);

            candidate = point - vertices[1].position - vClamp((wDotV - wDotU + uDotU - uDotV) / (vDotV - 2 * uDotV + uDotU), 0.0, 1.0) * m;
//            candidate = point - vertexB.position - vClamp((wDotV - wDotU + uDotU - uDotV) / (vDotV - 2 * uDotV + uDotU), 0.0, 1.0) * m;
            candidateMinDistance = vDot(candidate, candidate);
            if (candidateMinDistance < minDistance)
            {
              minProjection = candidate;
              minDistance = candidateMinDistance;
              normal = edgeNormals[1];
//              normal = triangleData.edgeNormalBC;
            }
            //smaller = vStep(candidateMinDistance, minPointInfo[1].w);
            //minPointInfo[0] = vMix(minPointInfo[0],
            //  vec4(triangleData.edgeNormalBC, 0.0), smaller);
            //minPointInfo[1] = vMix(minPointInfo[1],
            //  vec4(candidate, candidateMinDistance), smaller);

            candidate = point - vertices[0].position;
//            candidate = point - vertexA.position;
            candidateMinDistance = vDot(candidate, candidate);
            if (candidateMinDistance < minDistance)
            {
              minProjection = candidate;
              minDistance = candidateMinDistance;
              normal = vertices[0].normal;
//              normal = vertexA.normal;
            }
            //float smaller = vStep(candidateMinDistance, minPointInfo[1].w);
            //minPointInfo[0] = vMix(minPointInfo[0],
            //  vec4(vertexA.normal, 0.0), smaller);
            //minPointInfo[1] = vMix(minPointInfo[1],
            //  vec4(candidate, candidateMinDistance), smaller);

            candidate = point - vertices[1].position;
//            candidate = point - vertexB.position;
            candidateMinDistance = vDot(candidate, candidate);
            if (candidateMinDistance < minDistance)
            {
              minProjection = candidate;
              minDistance = candidateMinDistance;
              normal = vertices[1].normal;
//              normal = vertexB.normal;
            }
            //smaller = vStep(candidateMinDistance, minPointInfo[1].w);
            //minPointInfo[0] = vMix(minPointInfo[0],
            //  vec4(vertexB.normal, 0.0), smaller);
            //minPointInfo[1] = vMix(minPointInfo[1],
            //  vec4(candidate, candidateMinDistance), smaller);

            candidate = point - vertices[2].position;
//            candidate = point - vertexC.position;
            candidateMinDistance = vDot(candidate, candidate);
            if (candidateMinDistance < minDistance)
            {
              minProjection = candidate;
              minDistance = candidateMinDistance;
              normal = vertices[2].normal;
//              normal = vertexC.normal;
            }
            //smaller = vStep(candidateMinDistance, minPointInfo[1].w);
            //minPointInfo[0] = vMix(minPointInfo[0],
            //  vec4(vertexC.normal, 0.0), smaller);
            //minPointInfo[1] = vMix(minPointInfo[1],
            //  vec4(candidate, candidateMinDistance), smaller);
          }
        }

        return vDot(normal, minProjection) > 0.0;
        //return vDot(minPointInfo[0].xyz, minPointInfo[1].xyz) > 0.0;
      }
    #endif

    #ifdef ClipVolDebug
    vec3 DebugColor(uint i, uint maxDepth)
    {
      return vMix(vec3(0.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0), float(i) / float(maxDepth - 1));
    }
    #endif

    #ifdef ClipVolDebug
    vec3 PerformClippingVolumeDiscard()
    #else
    void PerformClippingVolumeDiscard()
    #endif
    {
      const uint maxClippingVolumes = 10;
      const uint maxDepth = 12;

      vec3 pos = vGetViewPosition();
      uint insideClippingVolumeCount = 0;

      for (uint n = 0; n < maxClippingVolumes; n++)
      {
        if (n >= g_ClippingVolumeData.length())
        {
          break;
        }

        const uvec2 octreeOffsetDepth = g_ClippingVolumeData[n].octreeOffsetDepth;

      #ifdef UsePassThroughTransition
        vec3 normalizedCoordinates = (g_ClippingVolumeData[n].boundingBoxInverseTransform *
                                     (cb_ClippingVolume.Matrix * _vPrivGetViewInverseTransition() * vec4(pos, 1.0))).xyz;
      #else
        vec3 normalizedCoordinates = (g_ClippingVolumeData[n].boundingBoxInverseTransform *
                                     (cb_ClippingVolume.Matrix * vec4(pos, 1.0))).xyz;
      #endif
        vec3 initialNormalizedCoordinates = normalizedCoordinates;

        uint octreePointer = octreeOffsetDepth.x;
        OctreeNodeData_t data = g_OctreeData[octreePointer];

        if (vAny(vLessThan(normalizedCoordinates, vec3(0.0)))
          || vAny(vGreaterThan(normalizedCoordinates, vec3(1.0))))
        {
        #ifdef ClipVolDebug
          discard;
        #else
          continue;
        #endif
        }

        // we assume that the root is not a leaf
        for (uint i = 0; i < maxDepth; i++)
        {
          const vec3 childNode = vFloor(2.0 * normalizedCoordinates);
          const uint childIndex = uint(vDot(childNode, vec3(1.0, 2.0, 4.0)) + 0.5);
          
          const uvec2 nodeData = data.nodeData.xy;

          // count the number of children before the relevant one
          uint childMask = nodeData.y;
          const uint childOffset = vBitCount(((1U << childIndex) - 1U) & childMask);
          childMask = (childMask >> childIndex) & 0x101;

          octreePointer += nodeData.x + childOffset;
          data = g_OctreeData[octreePointer];
          normalizedCoordinates = normalizedCoordinates * 2.0 - childNode;

          if (childMask == 0x100)
          {
          // outer leaf
          #ifdef ClipVolDebug
            return DebugColor(i, octreeOffsetDepth.y);
          #else
            break;
          #endif
          }
          if (childMask == 0x000)
          {
          // inner leaf
          #ifdef ClipVolDebug
            return DebugColor(i, octreeOffsetDepth.y);
          #else
            insideClippingVolumeCount++;
            break;
          #endif
          }
          if (childMask == 0x101)
          {
            // border leaf
            #ifdef ClipVolDebug
              #if (kClipVolMethod == ClipVolMethod_DistanceFieldOctree)
                const float signedDistance = PerformDistanceFieldDiscard(data.nodeData, normalizedCoordinates);
                if (vAbs(signedDistance) < 0.006)
                {
                  return vec3(1.0, 0.3, 0.4);
                }
                else
                {
                  return ((signedDistance + 1.0) * 0.5).xxx;
                }
              #endif
              return DebugColor(i, octreeOffsetDepth.y);
            #else
            
              #if (kClipVolMethod == ClipVolMethod_DistanceFieldOctree)
                if (PerformDistanceFieldDiscard(data.nodeData, normalizedCoordinates))
              #elif (kClipVolMethod == ClipVolMethod_TriangleListOctree)
                const uvec2 interval = data.nodeData;
                if (PerformTriangleListDiscard(interval.x, interval.y, initialNormalizedCoordinates))
              #endif
                {
                  insideClippingVolumeCount++;
                }
              break;

            #endif
          }
        }
      #ifdef ClipVolDebug
        return vec3(1.0);
      #endif
      }

    #ifdef kClipVolDirMode
      if (insideClippingVolumeCount%2 == (1-kClipVolDirMode))
    #else
      if (insideClippingVolumeCount%2 == 1)
    #endif
      {
        discard;
      }
    }
  #endif
#endif
