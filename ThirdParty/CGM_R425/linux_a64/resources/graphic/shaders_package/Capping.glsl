#if defined(Clipping) && defined(Capping) && defined(CappingFromPassSystem) && !defined(GLESPlatform) && (GLSLVersion >= 400)
#define CappingEnabled
#endif

#ifdef CappingEnabled

struct RayClipSection
{
  vec4 viewSpaceClipData;         // xy : position, z : front Z, w : back Z
  vec4 viewSpaceFrontClipPlane;   // Clipping plane normal
};

// The clipping plan normal points to the geometry that is not clipped
void RayIntersectClippingPlane(in vec4 ro, in vec4 rd, in vec4 plane, inout vec4 intersection)
{
  float num = vDot(ro, plane);
  float den = vDot(rd, plane);
  float t = -num / den;
  intersection = ro + (rd * t);
}

void InitCappingIntersectionFromPlane(inout RayClipSection ioClipSection, in vec4 iRo, in vec4 iRd, in vec4 iClipPlane)
{
  // Front facing test
  float nDotRay = vDot(iClipPlane, iRd);

  // View vector and clipping plane normal are orthogonal
  if(nDotRay == 0.0)
  {
    // No capping if the eye is behind the clipping plane
    ioClipSection.viewSpaceClipData.w = vDot(iRo, iClipPlane) < 0.0 ? -kInfiniteFloat : ioClipSection.viewSpaceClipData.w;
    return;
  }

  vec4 intersectionPosition = vec4(0.0);
  RayIntersectClippingPlane(iRo, iRd, iClipPlane, intersectionPosition);
  float viewSpaceZ = -intersectionPosition.z;

  // Maximize the front test
  ioClipSection.viewSpaceClipData.z = nDotRay > 0.0 ? vMax(ioClipSection.viewSpaceClipData.z, viewSpaceZ) : ioClipSection.viewSpaceClipData.z;

  // Update clipping plane normal and intersection position
  ioClipSection.viewSpaceFrontClipPlane = ioClipSection.viewSpaceClipData.z == viewSpaceZ ? iClipPlane : ioClipSection.viewSpaceFrontClipPlane;
  ioClipSection.viewSpaceClipData.xy = ioClipSection.viewSpaceClipData.z == viewSpaceZ ? intersectionPosition.xy : ioClipSection.viewSpaceClipData.xy;

  // Compute the back z if no front facing
  ioClipSection.viewSpaceClipData.w = nDotRay > 0.0 ? ioClipSection.viewSpaceClipData.w : vMin(ioClipSection.viewSpaceClipData.w, viewSpaceZ);
}

// Compute the intersections and init the intersection structures
// Maximum of 6 clipping planes
RayClipSection InitCappingIntersections(in vec4 iRo, in vec4 iRd)
{
  // Default init
  RayClipSection oRayClipSection;
  oRayClipSection.viewSpaceClipData.xy = vec2(0.0);
  //oRayClipSection.viewSpaceClipData.z = vGetNearFarLogFactor().x; // not ok in ortho
  oRayClipSection.viewSpaceClipData.z = -kInfiniteFloat;
  oRayClipSection.viewSpaceClipData.w = kInfiniteFloat;
  oRayClipSection.viewSpaceFrontClipPlane = vec4(0.0);

  InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(0));

  if(kClipPlanesCount > 5)
  {
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(1));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(2));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(3));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(4));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(5));
  }
  else if(kClipPlanesCount > 4)
  {
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(1));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(2));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(3));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(4));
  }
  else if(kClipPlanesCount > 3)
  {
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(1));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(2));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(3));
  }
  else if(kClipPlanesCount > 2)
  {
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(1));
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(2));
  }
  else if(kClipPlanesCount > 1)
  {
    InitCappingIntersectionFromPlane(oRayClipSection, iRo, iRd, _vPrivGetViewClipPlaneEq(1));
  }

  return oRayClipSection;
}

// Compute the lighting for a capping fragment
vec3 DoCappingLighting(in vec3 iAlbedo, in vec3 iP, in vec3 iN)
{
  // Set the default color
  vec3 cappingColor = iAlbedo;

  // Given Z position must be corrected
  iP = vec3(iP.xy, -iP.z);

#ifdef Lighting
  vec3 view = vNormalize(-vGetViewPosition());
  LightingData data = ComputeStdLightingData(iP, iN, view);
  data.minVisibility = 1.0;

  #ifdef EVisuPBR
    //improvise tangent / binormal vectors on the clipping plane
    data.T = vec3(data.N.z, data.N.y, data.N.x);
    data.B = vec3(data.N.x, data.N.z, data.N.y);
  #endif

  #ifdef ImageBasedLighting
    //IBL needs world space vectors
    data.Nworld = (vGetViewInverseMatrix() * vec4(data.N, 0.0)).xyz;
    data.Vworld = (vGetViewInverseMatrix() * vec4(data.V, 0.0)).xyz;
  #endif

  // Default capping BRDF
  #ifdef EVisuPBR
    BRDFParameters brdf;
    brdf.thinWalled = 1;
    brdf.albedo = iAlbedo;
    brdf.specularTint = vec3(1.0);
    brdf.metallic = 0.0;
    brdf.specular = 1.0;
    #ifdef SO_EVISUPBR_TRANSLUCENCY
      brdf.translucency = 0.0;
    #endif
    brdf.transparency = 0.0;
    brdf.ior = 1.4;
    brdf.roughness = 0.5;
    brdf.anisotropy = 0.0;
    brdf.anisotropyRotation = 0.0;
    #ifdef SO_EVISUPBR_SHEEN
      brdf.sheen = 0.0;
    #endif
    #ifdef SO_EVISUPBR_CLEARCOAT
      brdf.clearcoat = 0.0;
      brdf.clearcoatRoughness = 0.0;
    #endif
  #else
    BRDFParameters brdf;
    brdf.albedo = iAlbedo;
    brdf.f0 = vec3(0.04);
    brdf.f90 = vec3(1.0);
    brdf.roughness = 0.5;
    brdf.transparency = 0.0;
  #endif

  #ifdef _PDSFX1_FS_Capping
    ProcessCappingParameters(data.P, data.N, brdf.albedo);
  #endif

  vec3 dummyIBLContrib;
  vec3 dummyFresnelContrib;
  cappingColor = DoFragmentLightingCompositing(data, brdf, dummyIBLContrib,dummyFresnelContrib).rgb;

#elif defined(_PDSFX1_FS_Capping)
  ProcessCappingParameters(iP, iN, cappingColor);
#endif

  // Code from the master shader
#ifndef HighlightAdvanced
#ifdef LowLight
  cappingColor = DoLowlighting(cappingColor);
#endif
#ifdef GhostLook
  cappingColor = vec3(1.); // ghost color is white
#endif
#endif

  return cappingColor;
}

// Capping algorithm
void UpdateCapping()
{
  // Remove fragment helper computations
  if (gl_SampleMaskIn[0] == 0)
  {
    return;
  }

#ifdef StencilTest
  // When using scissor, do not compute capping for fragments discarded by the stencil test
  if(vTexelFetch(pdsfxStencilMap, ivec2(gl_FragCoord.xy), gl_SampleID).x == 0)
  {
    return;
  }
#endif

  // Safety check
  if(kClipPlanesCount <= 0)
  {
    return;
  }

  // Get the viewport dimension
  ivec2 viewportDimension = vImageSize(capDataMap).xy;
  
  // Coordinates between [0,1]
  vec2 fragCoordUV = (vGetFragCoord().xy + vGetSamplePosition() - vec2(0.5)) / viewportDimension.xy;

  // Compute fragments near value from [0,1] to [-1,+1] in clip space
  vec3 fragNearClipSpace = vec3(vFma(fragCoordUV.xy, vec2(2.0), vec2(-1.0)), -1.0);

    // Compute fragments far value from [0,1] to [-1,+1] in clip space
  vec3 fragFarClipSpace = vec3(vFma(fragCoordUV.xy, vec2(2.0), vec2(-1.0)), 1.0);

  // Compute fragment near and far values in view space and unproject it
  mat4 tempViewSpaceMat = vGetProjInverseMatrix() * mat4(vec4(fragNearClipSpace, 1.0), vec4(fragFarClipSpace, 1.0), vec4(0.0), vec4(0.0));
  vec4 viewSpaceFragNear = tempViewSpaceMat[0];
  viewSpaceFragNear.xyz /= viewSpaceFragNear.w;

  vec4 viewSpaceFragFar = tempViewSpaceMat[1];
  viewSpaceFragFar.xyz /= viewSpaceFragFar.w;

  // The ray origin is the near fragment in view space coordinates
  // This works for both the orthographic and perspective modes
  vec4 ro = vec4(viewSpaceFragNear.xyz, 1.0);
  vec4 rd = vec4(viewSpaceFragFar.xyz - viewSpaceFragNear.xyz, 0.0);

  // Compute the intersections with the clipping planes
  RayClipSection rayClipSection = InitCappingIntersections(ro, rd);

  // Compute the fragment distance to the camera
  float fragmentZ = -vGetViewPosition().z;

  // Returns 1 if fragmentZ >= viewSpaceZFront
  float frontCapTest = vStep(rayClipSection.viewSpaceClipData.z, fragmentZ);
  float rayValidity = vStep(rayClipSection.viewSpaceClipData.z, rayClipSection.viewSpaceClipData.w) - vStep(rayClipSection.viewSpaceClipData.z, -kInfiniteFloat);

  // True if the fragment is valid for capping (must be in the convex plans volume)
  float updateCapping = rayValidity * frontCapTest;

  // Update the capping maps
  if(updateCapping != 0.0)
  {
    // Get the current ID
    uint newID = _sbCapping.u_CCID;

    // Get the stored ID
  #ifdef IS_MSAA
    ivec3 imgCoord = ivec3(gl_FragCoord.xy, gl_SampleID);
  #else
    ivec2 imgCoord = ivec2(gl_FragCoord.xy);
  #endif
    uint counterMapValue = vImageLoad(capDataMap, imgCoord).x;
    
    uint storedID = counterMapValue & 0xFFFF;

    // Only update the data for a new volume
    // Make sure we modify the right pixel for a new ID
    if((storedID != newID) &&
        (vImageAtomicCompSwap(capDataMap, imgCoord, counterMapValue , newID) == counterMapValue))
    {
    // Write the ID where capping is visible
  #if defined(OutputGPUPicking)
    imageStore(GPUPickingCappingMap, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
  #endif

      // Get the values
      uvec4 colorData = vImageLoad(capColorMap, imgCoord);
      
#ifdef OutputNormalMap
      uvec4 normalData = vImageLoad(capNormalMap, imgCoord);
#endif

      // Get the front and back faces counter
      uint frontFaceCounter = (counterMapValue & 0xFF000000);
      uint backFaceCounter  = (counterMapValue & 0x00FF0000);

      if(frontFaceCounter != (backFaceCounter << 8))
      {
        // Get the values
        float lastZ = vUintBitsToFloat(colorData.z);
        float storedZ = (colorData.x == kDefaultDepth) ? lastZ + 1.0 : vUintBitsToFloat(colorData.x);

        // Update the data only if necessary
        colorData.x = (storedZ > lastZ) ? colorData.z : colorData.x;
        colorData.y = (storedZ > lastZ) ? colorData.w : colorData.y;

#ifdef OutputNormalMap
        normalData.x = (storedZ > lastZ) ? normalData.y : normalData.x;
#endif
      }

      // Pack the new Z
      uint fragZInUint = 0;
      fragZInUint = vFloatBitsToUint(rayClipSection.viewSpaceClipData.z);

      // Capping fragment normal is facing the opposite direction of the clipping plane normal
      // The normal must be normalized otherwise the capping color will not be the same when the clipping plane is rescaled
      vec3 cappingFragNormal = vNormalize(-rayClipSection.viewSpaceFrontClipPlane.xyz);

#ifdef OutputNormalMap
      // Pack the capping normal
      vec4 normalInMap = vec4(cappingFragNormal, 0.0) * 0.5 + vec4(0.5);
      normalInMap.w = 1.0;
      normalData.y = packSnorm4x8(normalInMap);

      // Pack the capping normal
      vImageStore(capNormalMap, imgCoord, normalData);
#endif

#ifdef USE_MULTICOLOR_CAPPING
    // Multicolor capping
    vec3 albedo = _sbCapping.u_CappingColor.rgb;
#else
    // Compute the capping color, lowlight color by default
    vec3 albedo = vGetLowlightColor();
#endif

      // Lighting
      vec3 finalColor = DoCappingLighting(albedo, rayClipSection.viewSpaceClipData.xyz, cappingFragNormal);

      // Pack the color (alpha is used for black capping issue by-pass)
      uint finalColorInUint = packUnorm4x8(vec4(finalColor, vStep(0.0, cappingFragNormal.z)));

      // Update the Z, color and normal values
      colorData.z = fragZInUint;
      colorData.w = finalColorInUint;

      // Store the values
      vImageStore(capColorMap, imgCoord, colorData);
      
    } // if(storedID != newID && CAS)

    // Increment the counter for a front or a back face
    uint incrementCounter = vIsFrontFacing() ? 0x01000000 : 0x00010000;
    vImageAtomicAdd(capDataMap, imgCoord, incrementCounter);

    // Avoid face count overflow
    vImageAtomicAnd(capDataMap, imgCoord, 0x7F7FFFFF);

  }// if(updateCapping == true)

  // Discard back faces
  // Discarding back faces might lead to white dots artifacts in white ambiances
  if(!vIsFrontFacing())
  {
    discard;
  }
}

#endif // CappingEnabled
