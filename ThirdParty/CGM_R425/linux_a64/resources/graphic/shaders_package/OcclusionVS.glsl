#ifndef SHADER_BUILDER
#version 430
#endif

//#ifndef DebugBoxes
//layout(std430, binding = 0)buffer visibilityBuffer
//{
//  int visibles[];
//};
//#endif

in int bboxIndex;
in int matrixIndex;

//uniform samplerBuffer matricesTex;
//uniform samplerBuffer bboxesTex;

out VertexOut
{
  vec3 bboxCtr;
flat int matrixIndex;
vec3 bboxDim;
flat int objid;
// float bboxCornerRadii[8];
#ifdef DebugBoxes
vec4 color;
#endif
} OUT;

void main()
{
  vec3 bboxCenter = texelFetch(bboxesTex, bboxIndex * 2 + 0).xyz;
  vec3 bboxHalfSize = texelFetch(bboxesTex, bboxIndex * 2 + 1).xyz;

  int objid    = gl_VertexID;
  float maxRadius = 0.0;
  vec3 worldViewInverseScalingFactors = vec3(0.0, 0.0, 0.0); // factors to scale and stretch a distance from view space to object space

  vec3 absBboxCenter   = vAbs(bboxCenter);
  vec3 absBboxHalfSize = vAbs(bboxHalfSize);

  bool allCenterNull = all(lessThan(absBboxCenter,   vec3(1e-5)));
  bool allSizeNull   = all(lessThan(absBboxHalfSize, vec3(1e-5)));

  if (allCenterNull && allSizeNull)
  {
#ifndef DebugBoxes
    visibles[objid] = 1;
    objid |= 1 << 31;
#endif
  }
  else
  {
    int matindex = matrixIndex * 4;
    mat4 worldView = mat4(texelFetch(matricesTex, matindex + 0),
      texelFetch(matricesTex, matindex + 1),
      texelFetch(matricesTex, matindex + 2),
      texelFetch(matricesTex, matindex + 3));

  #if defined(StereoOcclusion)
    worldView = cb_OcclusionCamera.PassageMatrix * worldView; //Transform from 1 eye to the other
  #endif

    //We will detect if the box (or at least the sphere englobing the box) is before or after the near plane.
    //If the box is before the near, we early accept it.
    //We will easy accept more objects (than with the previous method) but we are faster. 
    //Moreover, to perform the exact test, we should test with the left, right, top and bottom planes. This will solve false early accept

    vec4 u = worldView * vec4(bboxCenter, 1.);
    vec4 v = vec4(0, 0, -1, 0);

    float d = abs(dot(u, v));
    float r = length(vec3(worldView * vec4(bboxHalfSize, 0.)));

    float t = d - r;
    float near = _sbCbCamera.NearFarLogFactor.x;


    if (t < near)
    {
#ifndef DebugBoxes
      visibles[objid] = 1;
      objid |= 1 << 31;
#else
      OUT.color = vec4(0.8, 0.4, 0.1, 0.1);
#endif
    }
    else
    {
#ifdef DebugBoxes
      OUT.color = vec4(0.2, 0.4, 0.9, 0.1);
#endif

      vec4 viewSpaceBBoxCenter = u;
      vec4 viewSpaceFrustumNearPlane = cb_cbFrustumPlanes.View[0];


      // Compute bounding box parameters using to inflate it
      const float kNumPixelsInflate = 5.0; // 5 pixels of dilatation

      vec4 screenBoundBL = vGetProjInverseMatrix() * vec4(-1.0, -1.0, -1.0, 1.0);
      vec4 screenBoundTR = vGetProjInverseMatrix() * vec4(1.0, 1.0, -1.0, 1.0);
      vec3 screenDiagonal = screenBoundBL.xyz / screenBoundBL.w - screenBoundTR.xyz / screenBoundTR.w;
      float screenWorldSpaceLength2 = dot(screenDiagonal, screenDiagonal);
      // Compute the pixel size in worldspace

      float viewportLength2 = dot(_sbCbCamera.ScreenSize.xy, _sbCbCamera.ScreenSize.xy);
      float frontPixelWorldSpaceRadius = sqrt(screenWorldSpaceLength2 / viewportLength2); // this is an estimate of the size of a pixel in world space on the near plane
      {
        vec3 viewSpaceEx = vec3(worldView[0]); // = coordinates in view space of unit object-space direction Ex
        vec3 viewSpaceEy = vec3(worldView[1]); // = coordinates in view space of unit object-space direction Ey
        vec3 viewSpaceEz = vec3(worldView[2]); // = coordinates in view space of unit object-space direction Ez
        worldViewInverseScalingFactors = vec3(dot(viewSpaceEx,viewSpaceEx), dot(viewSpaceEy, viewSpaceEy), dot(viewSpaceEz, viewSpaceEz));
        worldViewInverseScalingFactors = inversesqrt(worldViewInverseScalingFactors);
      }

#if defined(PROJECTION_CONIC)
      // if (perspective_mode)
      {
        /// Compute box orientation in object space
        ///    if X = cross(Y, Z) then
        ///    inverse(M) * X = (1.0 / det(M)) * cross(transpose(M) * Y, transpose(M) * Z)
        ///    and sign(lambda) = sgn(det(M))
        vec3 viewSpaceBoxDirection = normalize(viewSpaceBBoxCenter.xyz);
        float furthestCornerZ = 0.0;
      
        for (uint cornerIndex = 0; cornerIndex < 8; ++cornerIndex)
        {
          vec3 corner = vec3(
              (cornerIndex & 0x1) == 0 ? 1.0 : -1.0,
              (cornerIndex & 0x2) == 0 ? 1.0 : -1.0,
              (cornerIndex & 0x4) == 0 ? 1.0 : -1.0);
          corner *= bboxHalfSize;
          float cornerZ = -(worldView * vec4(bboxCenter + corner, 1.0)).z; // z coordinate of corner in view space
          if(cornerZ > furthestCornerZ)
            furthestCornerZ = cornerZ;
        }
        
        maxRadius = (kNumPixelsInflate * frontPixelWorldSpaceRadius * furthestCornerZ) / abs(viewSpaceFrustumNearPlane.w); // size in world space of kNumPixelsInflate pixels at depth furthestCornerZ
      }
#else
      // if (orthographic_mode)
      {
        maxRadius = max(maxRadius, kNumPixelsInflate * frontPixelWorldSpaceRadius);
      }
#endif
    }
  }

  OUT.bboxCtr = bboxCenter;
  OUT.matrixIndex = matrixIndex;
  OUT.bboxDim = bboxHalfSize + maxRadius * worldViewInverseScalingFactors;
  OUT.objid = objid;
}
