int   EVisuPBR_UseGASColor;
int   EVisuPBR_IsAlphaTestEnabled;
int   EVisuPBR_IsPostOpaque;

int   EVisuPBR_thinWalled;
vec4  EVisuPBR_albedo;
vec3  EVisuPBR_specularTint;
float EVisuPBR_metallic;
float EVisuPBR_specular;
#ifdef SO_EVISUPBR_TRANSLUCENCY
  float EVisuPBR_translucency;
#endif
float EVisuPBR_transparency;
float EVisuPBR_ior;
float EVisuPBR_roughness;
float EVisuPBR_anisotropy;
float EVisuPBR_anisotropyRotation;
vec3 EVisuPBR_attenuationColor;
float EVisuPBR_attenuationDistance;
float EVisuPBR_opacity;
vec3  EVisuPBR_normal;
vec3  EVisuPBR_worldNormal;

#ifdef SO_EVISUPBR_SHEEN
  #if defined(SO_EVISUPBR_ver19x) || defined(SO_EVISUPBR_ver21x)
    float EVisuPBR_sheen;
  #endif // SO_EVISUPBR_ver19x || SO_EVISUPBR_ver21x
  #if defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x)
    vec3  EVisuPBR_sheenColor;
    float EVisuPBR_sheenRoughness;
  #endif // SO_EVISUPBR_ver21x || SO_EVISUPBR_ver22x
#endif // SO_EVISUPBR_SHEEN

#ifdef SO_EVISUPBR_FLAKES
  vec3  EVisuPBR_flakeColor;
  float EVisuPBR_flakeCoverage;
  float EVisuPBR_flakeSize;
  float EVisuPBR_flakeRoughness;
  float EVisuPBR_flipFlop;
  vec3 EVisuPBR_flipFlopColor;
#endif

#ifdef SO_EVISUPBR_CLEARCOAT
  float EVisuPBR_clearcoat;
  float EVisuPBR_clearcoatRoughness;
  vec3  EVisuPBR_clearcoatNormal;
#endif

float EVisuPBR_cutoutOpacity;

vec3 EVisuPBR_emission;

// [EOO2]
// SEMANTIC_DEFAULT_MULTIPLICATION is the default (old) and
// SEMANTIC_SEPARATE_TRANSLATION is the new way of combining
// per-parameter and global (VisMaterialApplication) UV transform matrices
// SEMANTIC_ROTATION_AROUND_CENTER is almost the same as SEMANTIC_SEPARATE_TRANSLATION
// but there is a shift by (0.5, 0.5)
// Detailed description is given in the documentation
#define SEMANTIC_DEFAULT_MULTIPLICATION 0
#define SEMANTIC_SEPARATE_TRANSLATION 1
#define SEMANTIC_ROTATION_AROUND_CENTER 2

void ApplyMAD1f(inout float ioValue, in float iM, in float iA)
{
  ioValue = vFma(ioValue, iM, iA);
}

void ApplyMAD3f(inout vec3 ioValue, in vec3 iM, in vec3 iA)
{
  ioValue = vFma(ioValue, iM, iA);
}

mapping_result_t EVisuPBR_mappings[SO_EVISUPBR_MAPPING_COUNT];

void GetMapping(int iSlot, inout mapping_result_t oMapping)
{
  int mapping = VisMapping.slot_to_mapping[iSlot];
  oMapping = EVisuPBR_mappings[mapping];
}

vec4 SampleTexture4fWithUVTransform(sampler2D iTexture, int iSlot, mat4 paramUVTrf)
{
  // This method is called when Mi is not identity (per-parameter UV transform is present).
  // Depending on the semantic:
  // SEMANTIC_DEFAULT_MULTIPLICATION - take mapping.uv_mod = M0 * uv and multiply it by Mi, thus:
  // tc = Mi * mapping.uv_mod = Mi * M0 * uv
  // SEMANTIC_SEPARATE_TRANSLATION - start with mapping.uv = uv
  // Extract rotations (R0, Ri) and translations (T0, Ti) from M0 and Mi separately.
  // Apply translations first: uv_shifted = mapping.uv + T0 + Ti
  // Then apply rotations: tc = Ri * R0 * uv_shifted
  // tc = Ri * R0 * (mapping.uv + T0 + Ti)
  // SEMANTIC_ROTATION_AROUND_CENTER:
  // offset = vec2(0.5, 0.5)
  // tc = Ri * R0 * (mapping.uv + T0 + Ti - offset) + offset

  mapping_result_t mapping;
  GetMapping(iSlot, mapping);
  const int index = VisMapping.slot_to_mapping[iSlot];

  const mat4 M0 = VisMapping.transform[index]; // global (VisMaterialApplication) UV transform matrix
  const vec2 T0 = M0[2].xy; // M0 translation only
  const mat2 R0 = mat2(M0); // M0 rotation only
  // Mi = paramUVTrf - per-parameter UV transform matrix
  const vec2 Ti = paramUVTrf[2].xy; // Mi translation only
  const mat2 Ri = mat2(paramUVTrf); // Mi rotation only

  const vec2 offset = (mapping.semantic == SEMANTIC_ROTATION_AROUND_CENTER) ?
    vec2(0.5, 0.5) : vec2(0.0, 0.0);
  const vec2 tc = (mapping.semantic == SEMANTIC_DEFAULT_MULTIPLICATION) ?
    vec2(mat3(paramUVTrf) * vec3(mapping.uv_mod, 1.0)) : // apply per-parameter UV transform
    Ri * R0 * (mapping.uv + T0 + Ti - offset) + offset;

  return vTexture(iTexture, tc);
}

vec4 SampleTexture4f(sampler2D iTexture, int iSlot)
{
  // This method is called when Mi is identity (no per-parameter UV transform).
  // Depending on the semantic:
  // SEMANTIC_DEFAULT_MULTIPLICATION - tc = mapping.uv_mod = M0 * uv
  // SEMANTIC_SEPARATE_TRANSLATION - start with mapping.uv = uv
  // Extract rotation R0 and translation T0 from M0.
  // Apply translation first: uv_shifted = mapping.uv + T0
  // Then apply rotation: tc = R0 * uv_shifted
  // tc = R0 * (mapping.uv + T0)
  // SEMANTIC_ROTATION_AROUND_CENTER:
  // offset = vec2(0.5, 0.5)
  // tc = R0 * (mapping.uv + T0 - offset) + offset

  mapping_result_t mapping;
  GetMapping(iSlot, mapping);
  const int index = VisMapping.slot_to_mapping[iSlot];

  const mat4 M0 = VisMapping.transform[index]; // global (VisMaterialApplication) UV transform matrix
  const vec2 T0 = M0[2].xy; // M0 translation only
  const mat2 R0 = mat2(M0); // M0 rotation only

  const vec2 offset = (mapping.semantic == SEMANTIC_ROTATION_AROUND_CENTER) ?
    vec2(0.5, 0.5) : vec2(0.0, 0.0);
  const vec2 tc = (mapping.semantic == SEMANTIC_DEFAULT_MULTIPLICATION) ?
    mapping.uv_mod :
    R0 * (mapping.uv + T0 - offset) + offset;

  return vTexture(iTexture, tc);
}

vec3 SampleTexture3fWithUVTransform(sampler2D iTexture, int iSlot, mat4 paramUVTrf)
{
  return vec3(SampleTexture4fWithUVTransform(iTexture, iSlot, paramUVTrf));
}

vec3 SampleTexture3f(sampler2D iTexture, int iSlot)
{
  return vec3(SampleTexture4f(iTexture, iSlot));
}

float SampleTexture1fWithUVTransform(sampler2D iTexture, int iSlot, mat4 paramUVTrf)
{
  return float(SampleTexture4fWithUVTransform(iTexture, iSlot, paramUVTrf));
}

float SampleTexture1f(sampler2D iTexture, int iSlot)
{
  return float(SampleTexture4f(iTexture, iSlot));
}

//TODO make oMapping only 'out'
void ComputeMapping(in int iIndex, inout mapping_result_t oMapping)
{
  const mat4 object_transform = VisMapping.object_transform[iIndex];
  const mat4 inv_object_transform = vTranspose(object_transform);

  mapping_info_t info;
  info.p = vec3(object_transform * vec4(EVisuPBR_vLocalPosition, 1.0));
  info.n = vec3(object_transform * vec4(EVisuPBR_vLocalNormal, 0.0));
  info.x = vec3(inv_object_transform[0]);
  info.y = vec3(inv_object_transform[1]);
  info.z = vec3(inv_object_transform[2]);

  switch (VisMapping.projection[iIndex])
  {
    case 0:
      oMapping.uv = vGetUvs();
      oMapping.t = vGetTangent();
      oMapping.b = vGetBinormal();
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

void ComputeMappings()
{
  for (int i = 0; i < SO_EVISUPBR_MAPPING_COUNT; ++i) {
    ComputeMapping(i, EVisuPBR_mappings[i]);
  }
}

void EVisuPBR_ComputeCommonValues()
{
  EVisuPBR_worldNormal = vec3(vGetViewInvMatrix() * vec4(vGetViewNormal(), 0.0));

  ComputeMappings();

  //UseGASColor
  EVisuPBR_UseGASColor = cb_EVisuPBR.UseGASColor;

  //IsAlphaTestEnabled
  EVisuPBR_IsAlphaTestEnabled = cb_EVisuPBR.IsAlphaTestEnabled;

  //IsPostOpaque
  EVisuPBR_IsPostOpaque = cb_EVisuPBR.IsPostOpaque;

  //albedo
#ifdef VertexColor
  EVisuPBR_albedo = vec4(EVisuPBR_vColor.rgb, 1.0);
#else
#ifndef EVisuPBR_albedo_textured
  EVisuPBR_albedo = vec4(cb_EVisuPBR.albedo, 1.0);
#elif defined EVisuPBR_albedo_uv_transform
  EVisuPBR_albedo = SampleTexture4fWithUVTransform(V_GET_TEXTURE_2D(albedo_map), cb_EVisuPBR.albedo_slot, cb_EVisuPBR_UVTransform.albedo_uv_transform);
#else
  EVisuPBR_albedo = SampleTexture4f(V_GET_TEXTURE_2D(albedo_map), cb_EVisuPBR.albedo_slot);
#endif
  ApplyMAD3f(EVisuPBR_albedo.xyz, cb_EVisuPBR.albedo_m, cb_EVisuPBR.albedo_a);
#endif // VertexColor

  //specularTint
#ifndef EVisuPBR_specularTint_textured
  EVisuPBR_specularTint = cb_EVisuPBR.specularTint;
#elif defined EVisuPBR_specularTint_uv_transform
  EVisuPBR_specularTint = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(specularTint_map), cb_EVisuPBR.specularTint_slot, cb_EVisuPBR_UVTransform.specularTint_uv_transform);
#else
  EVisuPBR_specularTint = SampleTexture3f(V_GET_TEXTURE_2D(specularTint_map), cb_EVisuPBR.specularTint_slot);
#endif
  ApplyMAD3f(EVisuPBR_specularTint, cb_EVisuPBR.specularTint_m, cb_EVisuPBR.specularTint_a);

  //roughness
#ifndef EVisuPBR_roughness_textured
  EVisuPBR_roughness = cb_EVisuPBR.roughness;
#elif defined EVisuPBR_roughness_uv_transform
  EVisuPBR_roughness = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(roughness_map), cb_EVisuPBR.roughness_slot, cb_EVisuPBR_UVTransform.roughness_uv_transform);
#else
  EVisuPBR_roughness = SampleTexture1f(V_GET_TEXTURE_2D(roughness_map), cb_EVisuPBR.roughness_slot);
#endif
  ApplyMAD1f(EVisuPBR_roughness, cb_EVisuPBR.roughness_m, cb_EVisuPBR.roughness_a);

  EVisuPBR_roughness = vClampWithEpsilon(EVisuPBR_roughness, 0.0, 1.0);

  //anisotropy
#ifndef EVisuPBR_anisotropy_textured
  EVisuPBR_anisotropy = cb_EVisuPBR.anisotropy;
#elif defined EVisuPBR_anisotropy_uv_transform
  EVisuPBR_anisotropy = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(anisotropy_map), cb_EVisuPBR.anisotropy_slot, cb_EVisuPBR_UVTransform.anisotropy_uv_transform);
#else
  EVisuPBR_anisotropy = SampleTexture1f(V_GET_TEXTURE_2D(anisotropy_map), cb_EVisuPBR.anisotropy_slot);
#endif
  ApplyMAD1f(EVisuPBR_anisotropy, cb_EVisuPBR.anisotropy_m, cb_EVisuPBR.anisotropy_a);

  EVisuPBR_anisotropy = vClamp(EVisuPBR_anisotropy, 0.0, 1.0 - kEpsilon);

  //anisotropyRotation
#ifndef EVisuPBR_anisotropyRotation_textured
  EVisuPBR_anisotropyRotation = cb_EVisuPBR.anisotropyRotation;
#elif defined EVisuPBR_anisotropyRotation_uv_transform
  EVisuPBR_anisotropyRotation = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(anisotropyRotation_map), cb_EVisuPBR.anisotropyRotation_slot, cb_EVisuPBR_UVTransform.anisotropyRotation_uv_transform);
#else
  EVisuPBR_anisotropyRotation = SampleTexture1f(V_GET_TEXTURE_2D(anisotropyRotation_map), cb_EVisuPBR.anisotropyRotation_slot);
#endif
  ApplyMAD1f(EVisuPBR_anisotropyRotation, cb_EVisuPBR.anisotropyRotation_m, cb_EVisuPBR.anisotropyRotation_a);

  //metallic
#ifndef EVisuPBR_metallic_textured
  EVisuPBR_metallic = cb_EVisuPBR.metallic;
#elif defined EVisuPBR_metallic_uv_transform
  EVisuPBR_metallic = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(metallic_map), cb_EVisuPBR.metallic_slot, cb_EVisuPBR_UVTransform.metallic_uv_transform);
#else
  EVisuPBR_metallic = SampleTexture1f(V_GET_TEXTURE_2D(metallic_map), cb_EVisuPBR.metallic_slot);
#endif
  ApplyMAD1f(EVisuPBR_metallic, cb_EVisuPBR.metallic_m, cb_EVisuPBR.metallic_a);

  //specular
#ifndef EVisuPBR_specular_textured
  EVisuPBR_specular = cb_EVisuPBR.specular;
#elif defined EVisuPBR_specular_uv_transform
  EVisuPBR_specular = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(specular_map), cb_EVisuPBR.specular_slot, cb_EVisuPBR_UVTransform.specular_uv_transform);
#else
  EVisuPBR_specular = SampleTexture1f(V_GET_TEXTURE_2D(specular_map), cb_EVisuPBR.specular_slot);
#endif
  ApplyMAD1f(EVisuPBR_specular, cb_EVisuPBR.specular_m, cb_EVisuPBR.specular_a);

  //transparency
#ifndef EVisuPBR_transparency_textured
  EVisuPBR_transparency = cb_EVisuPBR.transparency;
#elif defined EVisuPBR_transparency_uv_transform
  EVisuPBR_transparency = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(transparency_map), cb_EVisuPBR.transparency_slot, cb_EVisuPBR_UVTransform.transparency_uv_transform);
#else
  EVisuPBR_transparency = SampleTexture1f(V_GET_TEXTURE_2D(transparency_map), cb_EVisuPBR.transparency_slot);
#endif
  ApplyMAD1f(EVisuPBR_transparency, cb_EVisuPBR.transparency_m, cb_EVisuPBR.transparency_a);

  EVisuPBR_transparency = vClamp(EVisuPBR_transparency, 0.0, 1.0);

EVisuPBR_attenuationColor = cb_EVisuPBR.attenuationColor;
EVisuPBR_attenuationDistance = cb_EVisuPBR.attenuationDistance;

#ifdef SO_EVISUPBR_SHEEN

#if defined(SO_EVISUPBR_ver19x) || defined(SO_EVISUPBR_ver21x)
  //sheen
  #ifndef EVisuPBR_sheen_textured
    EVisuPBR_sheen = cb_EVisuPBR.sheen;
  #elif defined EVisuPBR_sheen_uv_transform
    EVisuPBR_sheen = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(sheen_map), cb_EVisuPBR.sheen_slot, cb_EVisuPBR_UVTransform.sheen_uv_transform);
  #else
    EVisuPBR_sheen = SampleTexture1f(V_GET_TEXTURE_2D(sheen_map), cb_EVisuPBR.sheen_slot);
  #endif // EVisuPBR_sheen_textured
  ApplyMAD1f(EVisuPBR_sheen, cb_EVisuPBR.sheen_m, cb_EVisuPBR.sheen_a);
#endif // defined(SO_EVISUPBR_ver19x) || defined(SO_EVISUPBR_ver21x)

#if defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x)
  //sheenColor
  #ifndef EVisuPBR_sheenColor_textured
    EVisuPBR_sheenColor = cb_EVisuPBR.sheenColor;
  #elif defined EVisuPBR_sheenColor_uv_transform
    EVisuPBR_sheenColor = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(sheenColor_map), cb_EVisuPBR.sheenColor_slot, cb_EVisuPBR_UVTransform.sheenColor_uv_transform);
  #else
    EVisuPBR_sheenColor = SampleTexture3f(V_GET_TEXTURE_2D(sheenColor_map), cb_EVisuPBR.sheenColor_slot);
  #endif // EVisuPBR_sheenColor_textured
  ApplyMAD3f(EVisuPBR_sheenColor, cb_EVisuPBR.sheenColor_m, cb_EVisuPBR.sheenColor_a);

  //sheenRoughness
  #ifndef EVisuPBR_sheenRoughness_textured
    EVisuPBR_sheenRoughness = cb_EVisuPBR.sheenRoughness;
  #elif defined EVisuPBR_sheenRoughness_uv_transform
    EVisuPBR_sheenRoughness = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(sheenRoughness_map), cb_EVisuPBR.sheenRoughness_slot, cb_EVisuPBR_UVTransform.sheenRoughness_uv_transform);
  #else
    EVisuPBR_sheenRoughness = SampleTexture1f(V_GET_TEXTURE_2D(sheenRoughness_map), cb_EVisuPBR.sheenRoughness_slot);
  #endif
  ApplyMAD1f(EVisuPBR_sheenRoughness, cb_EVisuPBR.sheenRoughness_m, cb_EVisuPBR.sheenRoughness_a);
  EVisuPBR_sheenRoughness = vClamp(EVisuPBR_sheenRoughness, 0.0, 1.0);
#endif // SO_EVISUPBR_ver21x || SO_EVISUPBR_ver22x

#endif // SO_EVISUPBR_SHEEN

  //normal
#ifndef EVisuPBR_normal_textured
  EVisuPBR_normal = vGetViewNormal();
#else

#ifdef EVisuPBR_normal_uv_transform
  EVisuPBR_normal = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(normal_map), cb_EVisuPBR.normal_slot, cb_EVisuPBR_UVTransform.normal_uv_transform);
#else
  EVisuPBR_normal = SampleTexture3f(V_GET_TEXTURE_2D(normal_map), cb_EVisuPBR.normal_slot);
#endif
  EVisuPBR_normal = vFma(EVisuPBR_normal, vec3(2.0), vec3(-1.0));

  #ifdef CompressedNormalMap
    EVisuPBR_normal.z = vSqrt(vAbs(1.0 - vDot(EVisuPBR_normal.xy, EVisuPBR_normal.xy)));
  #endif

  ApplyMAD3f(EVisuPBR_normal, cb_EVisuPBR.normal_m, cb_EVisuPBR.normal_a);

  { //Compensate for UV transform on normal map
    int index = VisMapping.slot_to_mapping[cb_EVisuPBR.normal_slot];
    mat2 transform_rotation = inverse(mat2(VisMapping.transform[index]));
    float scale = sqrt(abs(determinant(transform_rotation)));
    transform_rotation /= scale;
    EVisuPBR_normal.xy = transform_rotation * EVisuPBR_normal.xy;
  }

  {
    mapping_result_t mapping;
    GetMapping(cb_EVisuPBR.normal_slot, mapping);
    #ifndef DecalLighting
      EVisuPBR_normal = vNormalize(EVisuPBR_normal.x*mapping.t + EVisuPBR_normal.y*mapping.b + abs(EVisuPBR_normal.z)*EVisuPBR_worldNormal);
      EVisuPBR_normal = vec3(vGetViewMatrix() * vec4(EVisuPBR_normal, 0.0));
    #endif
  }
#endif // EVisuPBR_normal_textured

#ifdef SO_EVISUPBR_CLEARCOAT

    //clearcoat
  #ifndef EVisuPBR_clearcoat_textured
    EVisuPBR_clearcoat = cb_EVisuPBR.clearcoat;
  #elif defined EVisuPBR_clearcoat_uv_transform
    EVisuPBR_clearcoat = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(clearcoat_map), cb_EVisuPBR.clearcoat_slot, cb_EVisuPBR_UVTransform.clearcoat_uv_transform);
  #else
    EVisuPBR_clearcoat = SampleTexture1f(V_GET_TEXTURE_2D(clearcoat_map), cb_EVisuPBR.clearcoat_slot);
  #endif
    ApplyMAD1f(EVisuPBR_clearcoat, cb_EVisuPBR.clearcoat_m, cb_EVisuPBR.clearcoat_a);

    //clearcoatRoughness
  #ifndef EVisuPBR_clearcoatRoughness_textured
    EVisuPBR_clearcoatRoughness = cb_EVisuPBR.clearcoatRoughness;
  #elif defined EVisuPBR_clearcoatRoughness_uv_transform
    EVisuPBR_clearcoatRoughness = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(clearcoatRoughness_map), cb_EVisuPBR.clearcoatRoughness_slot, cb_EVisuPBR_UVTransform.clearcoatRoughness_uv_transform);
  #else
    EVisuPBR_clearcoatRoughness = SampleTexture1f(V_GET_TEXTURE_2D(clearcoatRoughness_map), cb_EVisuPBR.clearcoatRoughness_slot);
  #endif
    ApplyMAD1f(EVisuPBR_clearcoatRoughness, cb_EVisuPBR.clearcoatRoughness_m, cb_EVisuPBR.clearcoatRoughness_a);

    EVisuPBR_clearcoatRoughness = vClampWithEpsilon(EVisuPBR_clearcoatRoughness, 0.0, 1.0);

    //clearcoatNormal
  #ifndef EVisuPBR_clearcoatNormal_textured
    EVisuPBR_clearcoatNormal = vGetViewNormal();
  #else
  {
    #ifdef EVisuPBR_clearcoatNormal_uv_transform
    EVisuPBR_clearcoatNormal = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(clearcoatNormal_map), cb_EVisuPBR.clearcoatNormal_slot, cb_EVisuPBR_UVTransform.clearcoatNormal_uv_transform);
    #else
    EVisuPBR_clearcoatNormal = SampleTexture3f(V_GET_TEXTURE_2D(clearcoatNormal_map), cb_EVisuPBR.clearcoatNormal_slot);
    #endif
    EVisuPBR_clearcoatNormal = vFma(EVisuPBR_clearcoatNormal, vec3(2.0), vec3(-1.0));
    ApplyMAD3f(EVisuPBR_clearcoatNormal, cb_EVisuPBR.clearcoatNormal_m, cb_EVisuPBR.clearcoatNormal_a);

    { //Compensate for UV transform on normal map
      int index = VisMapping.slot_to_mapping[cb_EVisuPBR.clearcoatNormal_slot];
      mat2 transform_rotation = inverse(mat2(VisMapping.transform[index]));
      float scale = sqrt(abs(determinant(transform_rotation)));
      transform_rotation /= scale;
      EVisuPBR_clearcoatNormal.xy = transform_rotation * EVisuPBR_clearcoatNormal.xy;
    }

    {
      mapping_result_t mapping;
      GetMapping(cb_EVisuPBR.clearcoatNormal_slot, mapping);
      EVisuPBR_clearcoatNormal = vNormalize(EVisuPBR_clearcoatNormal.x*mapping.t + EVisuPBR_clearcoatNormal.y*mapping.b + abs(EVisuPBR_clearcoatNormal.z)*EVisuPBR_worldNormal);
      EVisuPBR_clearcoatNormal = vec3(vGetViewMatrix() * vec4(EVisuPBR_clearcoatNormal, 0.0));
    }
  }
  #endif

#endif //SO_EVISUPBR_CLEARCOAT

  //cutoutOpacity
#ifndef EVisuPBR_cutoutOpacity_textured
  EVisuPBR_cutoutOpacity = cb_EVisuPBR.cutoutOpacity;
#elif defined EVisuPBR_cutoutOpacity_uv_transform
  EVisuPBR_cutoutOpacity = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(cutoutOpacity_map), cb_EVisuPBR.cutoutOpacity_slot, cb_EVisuPBR_UVTransform.cutoutOpacity_uv_transform);
#else
  EVisuPBR_cutoutOpacity = SampleTexture1f(V_GET_TEXTURE_2D(cutoutOpacity_map), cb_EVisuPBR.cutoutOpacity_slot);
#endif
  ApplyMAD1f(EVisuPBR_cutoutOpacity, cb_EVisuPBR.cutoutOpacity_m, cb_EVisuPBR.cutoutOpacity_a);

#ifdef SO_EVISUPBR_CUTOUT_FROM_ALBEDO_ALPHA
  EVisuPBR_cutoutOpacity *= EVisuPBR_albedo.w;
#endif

// Emission

  //emissionColor
#ifndef EVisuPBR_emissionColor_textured
  vec3 EVisuPBR_emissionColor = cb_EVisuPBR.emissionColor;
#elif defined EVisuPBR_emissionColor_uv_transform
  vec3 EVisuPBR_emissionColor = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(emissionColor_map), cb_EVisuPBR.emissionColor_slot, cb_EVisuPBR_UVTransform.emissionColor_uv_transform);
#else
  vec3 EVisuPBR_emissionColor = SampleTexture3f(V_GET_TEXTURE_2D(emissionColor_map), cb_EVisuPBR.emissionColor_slot);
#endif
  ApplyMAD3f(EVisuPBR_emissionColor, cb_EVisuPBR.emissionColor_m, cb_EVisuPBR.emissionColor_a);
  //emissionValue
  const float EVisuPBR_emissionValue = cb_EVisuPBR.emissionValue;
  //emissionMode
  const int EVisuPBR_emissionMode = cb_EVisuPBR.emissionMode;
  //emissionEnergyNormalization
  const int EVisuPBR_emissionEnergyNormalization = cb_EVisuPBR.emissionEnergyNormalization;

  // If emission color is black, it is forced to be white, k becomes 1
  // IR-939911
  const float emission_k = vDot(EVisuPBR_emissionColor, vec3(0.2126729, 0.7151522, 0.0721750));
  EVisuPBR_emission = (vIsFrontFacing()) ?
    INV_PI * EVisuPBR_emissionValue * EVisuPBR_emissionColor *
    (((EVisuPBR_emissionEnergyNormalization>0) && (emission_k>1e-6)) ? (1.0/emission_k) : 1.0) :
    vec3(0.0);

// end of emission

#ifdef SO_EVISUPBR_FLAKES
    //flakeColor
  #ifndef EVisuPBR_flakeColor_textured
    EVisuPBR_flakeColor = cb_EVisuPBR.flakeColor;
  #elif defined EVisuPBR_flakeColor_uv_transform
    EVisuPBR_flakeColor = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(flakeColor_map), cb_EVisuPBR.flakeColor_slot, cb_EVisuPBR_UVTransform.flakeColor_uv_transform);
  #else
    EVisuPBR_flakeColor = SampleTexture3f(V_GET_TEXTURE_2D(flakeColor_map), cb_EVisuPBR.flakeColor_slot);
  #endif
    ApplyMAD3f(EVisuPBR_flakeColor, cb_EVisuPBR.flakeColor_m, cb_EVisuPBR.flakeColor_a);

    //flakeCoverage
  #ifndef EVisuPBR_flakeCoverage_textured
    EVisuPBR_flakeCoverage = cb_EVisuPBR.flakeCoverage;
  #elif defined EVisuPBR_flakeCoverage_uv_transform
    EVisuPBR_flakeCoverage = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(flakeCoverage_map), cb_EVisuPBR.flakeCoverage_slot, cb_EVisuPBR_UVTransform.flakeCoverage_uv_transform);
  #else
    EVisuPBR_flakeCoverage = SampleTexture1f(V_GET_TEXTURE_2D(flakeCoverage_map), cb_EVisuPBR.flakeCoverage_slot);
  #endif
    ApplyMAD1f(EVisuPBR_flakeCoverage, cb_EVisuPBR.flakeCoverage_m, cb_EVisuPBR.flakeCoverage_a);

    //flakeSize
  #ifndef EVisuPBR_flakeSize_textured
    EVisuPBR_flakeSize = cb_EVisuPBR.flakeSize;
  #elif defined EVisuPBR_flakeSize_uv_transform
    EVisuPBR_flakeSize = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(flakeSize_map), cb_EVisuPBR.flakeSize_slot, cb_EVisuPBR_UVTransform.flakeSize_uv_transform);
  #else
    EVisuPBR_flakeSize = SampleTexture1f(V_GET_TEXTURE_2D(flakeSize_map), cb_EVisuPBR.flakeSize_slot);
  #endif
    ApplyMAD1f(EVisuPBR_flakeSize, cb_EVisuPBR.flakeSize_m, cb_EVisuPBR.flakeSize_a);

    //flakeRoughness
  #ifndef EVisuPBR_flakeRoughness_textured
    EVisuPBR_flakeRoughness = cb_EVisuPBR.flakeRoughness;
  #elif defined EVisuPBR_flakeRoughness_uv_transform
    EVisuPBR_flakeRoughness = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(flakeRoughness_map), cb_EVisuPBR.flakeRoughness_slot, cb_EVisuPBR_UVTransform.flakeRoughness_uv_transform);
  #else
    EVisuPBR_flakeRoughness = SampleTexture1f(V_GET_TEXTURE_2D(flakeRoughness_map), cb_EVisuPBR.flakeRoughness_slot);
  #endif
    EVisuPBR_flakeRoughness = vClamp(EVisuPBR_flakeRoughness, 0.01, 0.99);
    ApplyMAD1f(EVisuPBR_flakeRoughness, cb_EVisuPBR.flakeRoughness_m, cb_EVisuPBR.flakeRoughness_a);
    EVisuPBR_flakeRoughness = vClampWithEpsilon(EVisuPBR_flakeRoughness, 0.0, 1.0);

    //flipFlop
  #ifndef EVisuPBR_flipFlop_textured
    EVisuPBR_flipFlop = cb_EVisuPBR.flipFlop;
  #elif defined EVisuPBR_flipFlop_uv_transform
    EVisuPBR_flipFlop = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(flipFlop_map), cb_EVisuPBR.flipFlop_slot, cb_EVisuPBR_UVTransform.flipFlop_uv_transform);
  #else
    EVisuPBR_flipFlop = SampleTexture1f(V_GET_TEXTURE_2D(flipFlop_map), cb_EVisuPBR.flipFlop_slot);
  #endif
    ApplyMAD1f(EVisuPBR_flipFlop, cb_EVisuPBR.flipFlop_m, cb_EVisuPBR.flipFlop_a);
	EVisuPBR_flipFlop = vClamp(EVisuPBR_flipFlop, 0.0, 1.0);

   //flipFlopColor
  #ifndef EVisuPBR_flipFlopColor_textured
    EVisuPBR_flipFlopColor = cb_EVisuPBR.flipFlopColor;
  #elif defined EVisuPBR_flipFlopColor_uv_transform
    EVisuPBR_flipFlopColor = SampleTexture3fWithUVTransform(V_GET_TEXTURE_2D(flipFlopColor_map), cb_EVisuPBR.flipFlopColor_slot, cb_EVisuPBR_UVTransform.flipFlopColor_uv_transform);
  #else
    EVisuPBR_flipFlopColor = SampleTexture3f(V_GET_TEXTURE_2D(flipFlopColor_map), cb_EVisuPBR.flipFlopColor_slot);
  #endif
    ApplyMAD3f(EVisuPBR_flipFlopColor, cb_EVisuPBR.flipFlopColor_m, cb_EVisuPBR.flipFlopColor_a);

#endif // SO_EVISUPBR_FLAKES

#ifdef SO_EVISUPBR_TRANSLUCENCY
    //translucency
  #ifndef EVisuPBR_translucency_textured
    EVisuPBR_translucency = cb_EVisuPBR.translucency;
  #elif defined EVisuPBR_translucency_uv_transform
    EVisuPBR_translucency = SampleTexture1fWithUVTransform(V_GET_TEXTURE_2D(translucency_map), cb_EVisuPBR.translucency_slot, cb_EVisuPBR_UVTransform.translucency_uv_transform);
  #else
    EVisuPBR_translucency = SampleTexture1f(V_GET_TEXTURE_2D(translucency_map), cb_EVisuPBR.translucency_slot);
  #endif
    ApplyMAD1f(EVisuPBR_translucency, cb_EVisuPBR.translucency_m, cb_EVisuPBR.translucency_a);
    EVisuPBR_translucency = vClamp(EVisuPBR_translucency, 0.0, 1.0);
#endif // SO_EVISUPBR_TRANSLUCENCY

  //thinWalled
  EVisuPBR_thinWalled = cb_EVisuPBR.thinWalled;

  //ior
  EVisuPBR_ior = cb_EVisuPBR.ior;
}

float AdjustTransparency(in float iTransparency)
{
  float adjust = sqrt(dot(vec3(EVisuPBR_albedo), vec3(0.299, 0.587, 0.114))); // luminance of the color
  adjust *= exp(-0.125 * EVisuPBR_roughness * EVisuPBR_roughness); // roughness squared as in the brdf, the higher the roughness is, the lower is transparency
  return iTransparency * adjust;
}

void EVisuPBR_ProcessBRDFParameters(inout BRDFParameters oParams)
{
  oParams.thinWalled = EVisuPBR_thinWalled;
  oParams.albedo = vec3(EVisuPBR_albedo);
  oParams.specularTint = EVisuPBR_specularTint;
  oParams.metallic = EVisuPBR_metallic;
  oParams.specular = EVisuPBR_specular;
  #ifdef SO_EVISUPBR_TRANSLUCENCY
    oParams.translucency = EVisuPBR_translucency;
  #endif
  oParams.transparency = AdjustTransparency(EVisuPBR_transparency);
  oParams.ior = EVisuPBR_ior;
  oParams.roughness = EVisuPBR_roughness;
  oParams.anisotropy = EVisuPBR_anisotropy;
  oParams.anisotropyRotation = EVisuPBR_anisotropyRotation;

  oParams.attenuationColor = EVisuPBR_attenuationColor;
  oParams.attenuationDistance = EVisuPBR_attenuationDistance;
  oParams.opacity = EVisuPBR_cutoutOpacity;

  #ifdef SO_EVISUPBR_SHEEN
  #if defined(SO_EVISUPBR_ver19x) || defined(SO_EVISUPBR_ver21x)
    oParams.sheen = EVisuPBR_sheen;
  #endif // SO_EVISUPBR_ver19x || SO_EVISUPBR_ver21x
  #if defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x)
    oParams.sheenColor = EVisuPBR_sheenColor;
    oParams.sheenRoughness = EVisuPBR_sheenRoughness;
  #endif // SO_EVISUPBR_ver21x || SO_EVISUPBR_ver22x
  #endif // SO_EVISUPBR_SHEEN

  #ifdef SO_EVISUPBR_FLAKES
    oParams.flakeCoverage = EVisuPBR_flakeCoverage;
    oParams.flakeSize = EVisuPBR_flakeSize;
    oParams.flakeRoughness = EVisuPBR_flakeRoughness;
    oParams.flakeColor = EVisuPBR_flakeColor;
    oParams.flipFlop = EVisuPBR_flipFlop;
    oParams.flipFlopColor = EVisuPBR_flipFlopColor;
  #endif // SO_EVISUPBR_FLAKES

  #ifdef SO_EVISUPBR_CLEARCOAT
    oParams.clearcoat = EVisuPBR_clearcoat;
    oParams.clearcoatRoughness = EVisuPBR_clearcoatRoughness;
    oParams.clearcoatNormal = EVisuPBR_clearcoatNormal;
  #endif // SO_EVISUPBR_CLEARCOAT

  #ifdef SO_EVISUPBR_SUBSURFACE
    oParams.curvature = length(fwidthFine(EVisuPBR_worldNormal)) / length(fwidthFine(EVisuPBR_vLocalPosition));
  #endif // SO_EVISUPBR_SUBSURFACE

  oParams.emission = EVisuPBR_emission;
}

vec3 EVisuPBR_ComputeViewNormal()
{
  return EVisuPBR_normal;
}

float EVisuPBR_ComputeOpacity()
{
  return EVisuPBR_cutoutOpacity;
}

bool EVisuPBR_ComputeDiscard()
{
  return false;
}

vec3 EVisuPBR_ComputeAlbedo()
{
  return vec3(EVisuPBR_albedo);
}

vec3 EVisuPBR_ComputeEmissive()
{
  return EVisuPBR_emission;
}

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Normal_EVisuPBR))
vec3 ComputeViewNormal()
{
  return EVisuPBR_ComputeViewNormal();
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Albedo_EVisuPBR))
vec3 ComputeAlbedo()
{
#ifdef VertexColor
  return EVisuPBR_vColor.rgb;
#else
  return EVisuPBR_ComputeAlbedo();
#endif
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Emissive_EVisuPBR))
vec3 ComputeEmissive()
{
  return EVisuPBR_ComputeEmissive();
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Discard_EVisuPBR))
bool ComputeDiscard()
{
  return EVisuPBR_ComputeDiscard();
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Opacity_EVisuPBR))
float ComputeOpacity()
{
  return EVisuPBR_ComputeOpacity();
}
#endif

#if !(defined(VertexStage) && defined(PDSFX1_VS_CommonValues_EVisuPBR)) && !(defined(FragmentStage) && defined(PDSFX1_FS_CommonValues_EVisuPBR))
void ComputeCommonValues()
{
  EVisuPBR_ComputeCommonValues();
}
#endif

#if !(defined(VertexStage) && defined(PDSFX1_PVL_AdvancedBRDFUser_EVisuPBR)) && !(defined(FragmentStage) && defined(PDSFX1_FS_AdvancedBRDFUser_EVisuPBR))
void ProcessBRDFParameters(inout BRDFParameters oParams)
{
  EVisuPBR_ProcessBRDFParameters(oParams);
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_FinalColor_EVisuPBR))
void ProcessFinalColor(inout vec4 ioFinalColor)
{
}
#endif
