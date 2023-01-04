// We assume that displacement can only be set using a texture, not assigned via the constant buffer
// Thus all of the displacement mapping code is wrapped with the EVisuPBR_displacement_textured shader option

vec3 EVisuPBR_displaced_vertex;
vec3 EVisuPBR_corrected_normal;

// [EOO2] see EVisuPBR_FS.glsl
#define SEMANTIC_DEFAULT_MULTIPLICATION 0
#define SEMANTIC_SEPARATE_TRANSLATION 1
#define SEMANTIC_ROTATION_AROUND_CENTER 2

void ComputeOneMapping(in int iIndex, inout mapping_result_t oMapping, in vec2 iUV,
  in vec3 iP, in vec3 iN, in vec3 iT, in vec3 iB)
{
  const mat4 object_transform = VisMapping.object_transform[iIndex];
  const mat4 inv_object_transform = vTranspose(object_transform);

  mapping_info_t info;
  info.p = vec3(object_transform * vec4(iP, 1.0));
  info.n = vec3(object_transform * vec4(iN, 0.0));
  info.x = vec3(inv_object_transform[0]);
  info.y = vec3(inv_object_transform[1]);
  info.z = vec3(inv_object_transform[2]);

  switch (VisMapping.projection[iIndex])
  {
    case 0:
      oMapping.uv = iUV;
      oMapping.t = iT;
      oMapping.b = iB;
      break;
    case 1:
      mapping_planar(info, oMapping);
      break;
    case 2:
      mapping_spherical(info, oMapping);
      break;
    case 3:
      mapping_spherical_normalized(info, oMapping);
      break;
    case 4:
      mapping_cubic(info, oMapping);
      break;
    case 5:
      mapping_cylindrical(info, oMapping);
      break;
    case 6:
      mapping_infinite_cylindrical(info, oMapping);
      break;
    case 7:
      mapping_infinite_cylindrical_normalized(info, oMapping);
      break;
    case 8:
      mapping_infinite_cylindrical_normalized_angle_pres(info, oMapping);
      break;
  }

  oMapping.semantic = VisMapping.uvtrf_semantic[iIndex];

  // Here, after the GPU mapping operator
  // mapping.uv = uv
  // Apply global (VisMaterialApplication) UV transform
  // and store the result in uv_mod
  // mapping.uv_mod = M0 * uv
  const mat3 transform = mat3(VisMapping.transform[iIndex]); // M0
  oMapping.uv_mod = vec2(transform * vec3(oMapping.uv, 1.0));
}

vec3 ComputeDisplacedPosition(in vec2 iUV, in vec3 iP, in vec3 iN, in vec3 iT, in vec3 iB)
{
#ifdef EVisuPBR_displacement_textured
  // Perform UV mapping
  mapping_result_t mapping;
  const int index = VisMapping.slot_to_mapping[cb_EVisuPBR.displacement_slot];
  ComputeOneMapping(index, mapping, iUV, iP, iN, iT, iB);
  // As result of this GPU procedural mapping operator the mapping.t and mapping.b together with the supplied iN
  // are not exactly the desired mutually orthogonal tuple of unit vectors which define the tangent space.
  // So appropriate recalculation has to be done.
  const vec3 locB = vCross(iN, mapping.t);
  const vec3 locT = vCross(mapping.b, iN);

  // Apply the UV transform, if needed
  const mat4 M0 = VisMapping.transform[index]; // global (VisMaterialApplication) UV transform matrix
  const vec2 T0 = M0[2].xy; // M0 translation only
  const mat2 R0 = mat2(M0); // M0 rotation only
  const vec2 offset = (mapping.semantic == SEMANTIC_ROTATION_AROUND_CENTER) ?
    vec2(0.5, 0.5) : vec2(0.0, 0.0);
  #ifdef EVisuPBR_displacement_uv_transform
    const mat4 paramUVTrf = cb_EVisuPBR_UVTransform.displacement_uv_transform;
    // Mi = paramUVTrf - per-parameter UV transform matrix
    const vec2 Ti = paramUVTrf[2].xy; // Mi translation only
    const mat2 Ri = mat2(paramUVTrf); // Mi rotation only
    const vec2 tc = (mapping.semantic == SEMANTIC_DEFAULT_MULTIPLICATION) ?
      vec2(mat3(paramUVTrf) * vec3(mapping.uv_mod, 1.0)) : // apply per-parameter UV transform
      Ri * R0 * (mapping.uv + T0 + Ti - offset) + offset;
  #else
    const vec2 tc = (mapping.semantic == SEMANTIC_DEFAULT_MULTIPLICATION) ?
      mapping.uv_mod :
      R0 * (mapping.uv + T0 - offset) + offset;
  #endif

  vec3 dv = vTexture(displacement_map, tc).xyz; // Sample the displacement map
  dv = vFma(dv, vec3(2.0), vec3(-1.0)); // Convert from color to vector in 3d space
  dv = vFma(dv, cb_EVisuPBR.displacement_m, cb_EVisuPBR.displacement_a); // apply MADD
  // The displacement dv must be transformed into the object space by multiplying by the TBN matrix
  return iP + mat3(locT, locB, iN) * dv;
#else
  return iP;
#endif
}

vec3 EVisuPBR_ComputeObjectPosition()
{
#ifdef EVisuPBR_displacement_textured
  EVisuPBR_displaced_vertex = ComputeDisplacedPosition(vec2(vGetUvs()),
    vGetAttribPosition(), vGetAttribNormal(), vGetAttribTangent(), vGetAttribBinormal());
  return EVisuPBR_displaced_vertex;
#else
  EVisuPBR_displaced_vertex = vec3(vGetAttribPosition());
  return EVisuPBR_displaced_vertex;
#endif // EVisuPBR_displacement_textured
}

vec3 EVisuPBR_ComputeObjectNormal()
{
#ifdef EVisuPBR_displacement_textured
  mapping_result_t mappingOO;
  ComputeOneMapping(VisMapping.slot_to_mapping[cb_EVisuPBR.displacement_slot], mappingOO, vec2(vGetUvs()),
    vGetAttribPosition(), vGetAttribNormal(), vGetAttribTangent(), vGetAttribBinormal());
  const vec3 locB = vCross(vGetAttribNormal(), mappingOO.t);
  const vec3 locT = vCross(mappingOO.b, vGetAttribNormal());
  const float displacementDelta = vLength(EVisuPBR_displaced_vertex - vGetAttribPosition());
  if (displacementDelta <= 1e-3) {
    EVisuPBR_corrected_normal = vec3(vGetAttribNormal());
    return EVisuPBR_corrected_normal;
  }
  const vec2 displacementMapSize = vTextureSize(displacement_map, 0);
  const vec2 k = 1.25 / displacementMapSize; // uvOffsetFactor

  #ifdef RayHitStage
    vec2 uvs = vec2(vGetAttribUvs());
  #else
    vec2 uvs = vec2(vGetUvs());
  #endif

  const vec3 pA = vNormalize(ComputeDisplacedPosition(uvs + vec2( 1.0, 0.0) * k,
   vGetAttribPosition() + locT       , vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pB = vNormalize(ComputeDisplacedPosition(uvs + vec2( 1.0, 1.0) * k,
   vGetAttribPosition() + locT + locB, vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pC = vNormalize(ComputeDisplacedPosition(uvs + vec2( 0.0, 1.0) * k,
   vGetAttribPosition()        + locB, vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pD = vNormalize(ComputeDisplacedPosition(uvs + vec2(-1.0, 1.0) * k,
   vGetAttribPosition() - locT + locB, vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pE = vNormalize(ComputeDisplacedPosition(uvs + vec2(-1.0, 0.0) * k,
   vGetAttribPosition() - locT       , vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pF = vNormalize(ComputeDisplacedPosition(uvs + vec2(-1.0,-1.0) * k,
   vGetAttribPosition() - locT - locB, vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pG = vNormalize(ComputeDisplacedPosition(uvs + vec2( 0.0,-1.0) * k,
   vGetAttribPosition()        - locB, vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 pH = vNormalize(ComputeDisplacedPosition(uvs + vec2( 1.0,-1.0) * k,
   vGetAttribPosition() + locT - locB, vGetAttribNormal(), locT, locB) - EVisuPBR_displaced_vertex);
  const vec3 displacedNormal = vCross(pA, pB) + vCross(pB, pC) + vCross(pC, pD) + vCross(pD, pE) +
                               vCross(pE, pF) + vCross(pF, pG) + vCross(pG, pH) + vCross(pH, pA);
  // displaced normal can not be flipped
  const float dotNdN = vDot(displacedNormal, vGetAttribNormal());
  EVisuPBR_corrected_normal = vNormalize((sign(dotNdN) + 1e-2) * displacedNormal);
  return EVisuPBR_corrected_normal;
#else
  EVisuPBR_corrected_normal = vec3(vGetAttribNormal());
  return EVisuPBR_corrected_normal;
#endif // EVisuPBR_displacement_textured
}

void EVisuPBR_ComputeVaryingValues()
{
#ifdef EVisuPBR_displacement_textured
  EVisuPBR_vLocalPosition = EVisuPBR_displaced_vertex;
  EVisuPBR_vLocalNormal = EVisuPBR_corrected_normal;
#else
  EVisuPBR_vLocalPosition = vec3(vGetAttribPosition());
  EVisuPBR_vLocalNormal = vec3(vGetAttribNormal());
#endif
#ifdef VertexColor
  EVisuPBR_vColor = vGetColor();
#endif // VertexColor
}

#if !(defined(VertexStage) && defined(PDSFX1_VS_Position_EVisuPBR))
vec3 ComputeObjectPosition()
{
  return EVisuPBR_ComputeObjectPosition();
}
#endif

#if !(defined(VertexStage) && defined(PDSFX1_VS_Normal_EVisuPBR))
vec3 ComputeObjectNormal()
{
  return EVisuPBR_ComputeObjectNormal();
}
#endif

#if !(defined(VertexStage) && defined(PDSFX1_VS_Varyings_EVisuPBR))
void ComputeVaryingValues()
{
  EVisuPBR_ComputeVaryingValues();
}
#endif
