#ifdef Lighting
#ifdef ImageBasedLighting

#if defined(MultiBRDFIBL)
  //uniform samplerCubeArray IBLSpecularTexture;
  //uniform sampler2DArray LookUpTexture2D;

  //vec4 vSamplingCubeMapArrayLod_IBLSpecularTexture(vec4 iRay, float iLOD)
  //{
  //mat3 PassageMatrix = mat3(
  //  #ifndef V_BC6H_IBLSpecularTexture
  //    0.0,  0.0, -1.0,
  //    1.0,  0.0,  0.0,
  //    0.0, -1.0,  0.0
  //  #else
  //    0.0,  0.0, -1.0,
  //    1.0,  0.0,  0.0,
  //    0.0,  1.0,  0.0
  //  #endif
  //  );
  //
  //  return vTextureLod(IBLSpecularTexture, vec4(PassageMatrix * iRay.xyz, iRay.w), iLOD);
  //}

  #ifdef EVisuPBR
    float g_IBLLayer = 0.0;
    float g_IBLLayerEnv = 3.0;
    float g_IBLLayer19xSheen = 3.0; // Preconvoluted environment image (1st integral) for DSPBR 2019x
    float g_IBLLayer21xSheen = 4.0; // Preconvoluted environment image (1st integral) for DSPBR 2021x
    float g_IBLLayerEnv19xSheen = 4.0; // Preconvoluted BRDF (2nd integral) for DSPBR 2019x
    float g_IBLLayerEnv21xSheen = 5.0; // Preconvoluted BRDF (2nd integral) for DSPBR 2021x
  #else
    #ifdef Fur
      float g_IBLLayer = 1.0;
      float g_IBLLayerEnv = 1.0;
    #elif defined(noFur)
      float g_IBLLayer = 2.0;
      float g_IBLLayerEnv = 2.0;
    #else
      float g_IBLLayer = 0.0;
      float g_IBLLayerEnv = 0.0;
    #endif
  #endif

#else
  //uniform samplerCube IBLSpecularTexture;
  //uniform sampler2D LookUpTexture2D;

  //vec4 vSamplingCubeMapLod_IBLSpecularTexture(vec3 iRay, float iLOD)
  //{
  //mat3 PassageMatrix = mat3(
  //  #ifndef V_BC6H_IBLSpecularTexture
  //    0.0,  0.0, -1.0,
  //    1.0,  0.0,  0.0,
  //    0.0, -1.0,  0.0
  //  #else
  //    0.0,  0.0, -1.0,
  //    1.0,  0.0,  0.0,
  //    0.0,  1.0,  0.0
  //  #endif
  //  );
  //
  //  return vTextureCubeLod(IBLSpecularTexture, PassageMatrix * iRay.xyz, iLOD);
  //}
#endif

#if defined(IBLLocal_Transfo) || defined(ImageBasedLighting_Transfo)
#define IBL_Transfo
#endif

#ifdef IBLLocal
  #define SpecularIBL IBLLocalSpecularTexture
  #define SpecularFactor cb_IBLLocal.Params.SpecularScaleFactor
  #define DiffuseIBL IBLLocalDiffuseTexture
  #define DiffuseFactor cb_IBLLocal.Params.DiffuseScaleFactor
  #define Transfo cb_IBLLocal.Params.TransfoMatrix
#else
  #define SpecularIBL IBLSpecularTexture
  #define SpecularFactor cb_IBL.u_IBLSpecularScaleFactor
  #define DiffuseIBL IBLDiffuseTexture
  #define DiffuseFactor cb_IBL.u_IBLDiffuseScaleFactor
  #define Transfo cb_IBL.u_IBLTransfoMatrix
#endif

#define IBLCorrectionNone 0
#define IBLCorrectionBox 1
#define IBLCorrectionCylinder 2
#define IBLCorrectionSphere 3
#define IBLCorrectionCutSphere 4

vec3 CorrectedDirection(in vec3 iWorldDir, in vec3 iViewPos)
{
#ifdef IBLParallaxCorrection
  if (IBLParallaxCorrection == IBLCorrectionNone)
    return iWorldDir;

#if !defined(IBLLocal) && defined(IBLDefaultCorrection)
  IBLShapeParams corrShape = cb_IBLDefaultCorrection.Shape;
#else
  IBLShapeParams2 corrShape = cb_IBLCorrection.Shape;
#endif

#ifdef UsePassThroughTransition
  vec3 posInShape = iViewPos - (_vPrivGetViewTransition() * vec4(corrShape.ViewPosition, 1.0)).xyz;
#else
  vec3 posInShape = iViewPos - corrShape.ViewPosition;
#endif
  posInShape = (vGetViewInverseMatrix()*vec4(posInShape, 0.0)).xyz;
  posInShape = (corrShape.Space*vec4(posInShape, 0.0)).xyz;

  vec3 reflVecInShape = (corrShape.SpaceNoIBLTransform*vec4(iWorldDir,0.0)).xyz;
  vNormalize(reflVecInShape);

  float rayDist = 0.0;

  if (IBLParallaxCorrection == IBLCorrectionBox)
  {
    vec3 boxMax = 0.5*corrShape.Dimensions;
    vec3 boxMin = -0.5*corrShape.Dimensions;

    vec3 firstPlaneIntersect = (boxMax - posInShape) / reflVecInShape;
    vec3 secondPlaneIntersect = (boxMin - posInShape) / reflVecInShape;

    vec3 furthestPlane = vMax(firstPlaneIntersect, secondPlaneIntersect);
    rayDist = vMin(vMin(furthestPlane.x, furthestPlane.y), furthestPlane.z);
  }
  if (IBLParallaxCorrection == IBLCorrectionCylinder)
  {
    float firstPlaneIntersect = (0.5*corrShape.Dimensions.y - posInShape.z) / reflVecInShape.z;
    float secondPlaneIntersect = (-0.5*corrShape.Dimensions.y - posInShape.z) / reflVecInShape.z;
    rayDist = vMax(firstPlaneIntersect, secondPlaneIntersect);

    float A = vDot(reflVecInShape.xy, reflVecInShape.xy);
    float B = 2.0 * vDot(reflVecInShape.xy, posInShape.xy);
    float C = vDot(posInShape.xy, posInShape.xy) - corrShape.Dimensions.x*corrShape.Dimensions.x;
    float delta = B*B - 4.0*A*C;

    if (delta > 0.0)
    {
      float deltaSqrt = vSqrt(delta);
      float d1 = (- B + deltaSqrt) / (2.0*A);
      float d2 = (- B - deltaSqrt) / (2.0*A);
      rayDist = vMin(rayDist, vMax(d1, d2));
    }
}
  if (IBLParallaxCorrection == IBLCorrectionSphere || IBLParallaxCorrection == IBLCorrectionCutSphere)
  {
    float A = vDot(reflVecInShape, reflVecInShape);
    float B = 2.0 * vDot(reflVecInShape, posInShape);
    float C = vDot(posInShape, posInShape) - corrShape.Dimensions.x*corrShape.Dimensions.x;
    float delta = B*B - 4.0*A*C;

    if (delta > 0.0)
    {
      float deltaSqrt = vSqrt(delta);
      float d1 = (- B + deltaSqrt) / (2.0*A);
      float d2 = (- B - deltaSqrt) / (2.0*A);
      rayDist = vMax(d1, d2);
    }
  }
  if (IBLParallaxCorrection == IBLCorrectionCutSphere)
  {
    float planeDist = (corrShape.Property - posInShape.z) / reflVecInShape.z;
    if ( planeDist > 0.0 )
      rayDist = vMin(rayDist, planeDist);
  }

  vec3 intersectPosInShape = posInShape + reflVecInShape * rayDist;
  vec3 reflDirInShape = intersectPosInShape - corrShape.CubeMapShotPosition;

  return (corrShape.SpaceNoIBLTransformInv*vec4(reflDirInShape,0.0)).xyz;
#else
  return iWorldDir;
#endif
}

vec3 ComputeTransformation(in vec3 iVec)
{
#ifdef IBLLocal
  #ifdef IBLLocal_Transfo
    return (cb_IBLLocal.Params.TransfoMatrix*vec4(iVec, 0.0)).xyz;
  #endif
#else
  #ifdef ImageBasedLighting_Transfo
    return (cb_IBL.u_IBLTransfoMatrix*vec4(iVec, 0.0)).xyz;
  #endif
#endif
  return iVec;
}
#if defined(FragmentStage) || defined(RayHitStage)

////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef GLES2Platform
vec3 ComputeDiffuseIBL(in vec3 iN)
{
  return vTextureCubeMap(DiffuseIBL, iN).rgb * DiffuseFactor;
}
#else // !GLES2Platform
vec3 ComputeDiffuseIBL(in vec3 iN)
{
  return vTextureCubeMapLod(DiffuseIBL, iN, 0.0).rgb * DiffuseFactor;
}
#endif

vec3 ComputeSpecularIBL(in vec3 iR, in float iMipMapLevel)
{
  #ifdef MultiBRDFIBL
    return vTextureCubeMapArrayLod(SpecularIBL, vec4(iR, g_IBLLayer), iMipMapLevel).rgb * SpecularFactor;
  #else
    return vTextureCubeMapLod(SpecularIBL, iR, iMipMapLevel).rgb * SpecularFactor;
  #endif
}

// Return preconvoluted environment image (1st integral) sample
vec3 ComputeSheenIBL(in vec3 iR, in float iMipMapLevel)
{
  #if defined(MultiBRDFIBL) && defined(EVisuPBR)
    #ifdef SO_EVISUPBR_ver19x
      return vTextureCubeMapArrayLod(SpecularIBL, vec4(iR, g_IBLLayer19xSheen), iMipMapLevel).rgb;
    #endif
    #if defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x)
      return vTextureCubeMapArrayLod(SpecularIBL, vec4(iR, g_IBLLayer21xSheen), iMipMapLevel).rgb;
    #endif
    return vec3(0.0); // Default
  #else
    return vec3(0.0);
  #endif
}

#if defined(AnisotropicDistribution) || defined(EVisuPBR)
vec3 ComputeSpecularIBL(in float iAnisotropy, in float iRoughness, in vec3 iT, in vec3 iB, in vec3 iR, in float iMipMapLevel)
{
  #ifdef MultiBRDFIBL
    vec3 contrib = vTextureCubeMapArrayLod(SpecularIBL, vec4(iR, g_IBLLayer), iMipMapLevel).rgb;
  #else
    vec3 contrib = vTextureCubeMapLod(SpecularIBL, iR, iMipMapLevel).rgb;
  #endif

  contrib *= 2.0;

  #ifdef MultiBRDFIBL
    contrib += vTextureCubeMapArrayLod(SpecularIBL, vec4(normalize(iR + iAnisotropy * iT), g_IBLLayer), iMipMapLevel).rgb;
  #else
    contrib += vTextureCubeMapLod(SpecularIBL, normalize(iR + iAnisotropy * iT), iMipMapLevel).rgb;
  #endif

  #ifdef MultiBRDFIBL
    contrib += vTextureCubeMapArrayLod(SpecularIBL, vec4(normalize(iR + iAnisotropy * iB), g_IBLLayer), iMipMapLevel).rgb;
  #else
    contrib += vTextureCubeMapLod(SpecularIBL, normalize(iR + iAnisotropy * iB), iMipMapLevel).rgb;
  #endif

  contrib *= 0.25;
  return contrib * SpecularFactor;
}
#endif // AnisotropicDistribution

#if defined(GLES2Platform)

vec2 ComputeEnvBRDF_Approximate(in float iRoughness, in float iDot_N_V)
{
  vec4 c0 = vec4(-1.0, -0.0275, -0.572, 0.022);
  vec4 c1 = vec4(1.0, 0.0425, 1.04, -0.04);
  vec4 r = iRoughness * c0 + c1;
  float a004 = vMin(r.x*r.x, vExp(-9.28 * iDot_N_V)) * r.x + r.y;
  vec2 AB = vec2(-1.04, 1.04) * a004 + r.zw;
  return AB;
}

#endif // defined(GLES2Platform)

vec2 ComputeEnvBRDF(in float iRoughness, in vec3 iN, in vec3 iV)
{
  #if defined(GLES2Platform)
    return ComputeEnvBRDF_Approximate(iRoughness, vMax(0.0, vDot(iN,iV)));
  #else // defined(GLES2Platform)
    #ifndef MultiBRDFIBL
      return vTextureLod(LookUpTexture2D, vec2(vMax(0.0, vDot(iN,iV)), iRoughness), 0.0).xy;
    #else
      return vTextureLod(LookUpTexture2D, vec3(vMax(0.0, vDot(iN,iV)), iRoughness, g_IBLLayerEnv), 0.0).xy;
    #endif
  #endif // defined(GLES2Platform)
}

// Return preconvoluted BRDF (2nd integral) sample
float ComputeEnvSheenBRDF(in float iRoughness, in vec3 iN, in vec3 iV)
{
  #if defined(EVisuPBR) && defined(MultiBRDFIBL)
    #ifdef SO_EVISUPBR_ver19x
      return vTextureLod(LookUpTexture2D, vec3(vMax(0.0, vDot(iN,iV)), iRoughness, g_IBLLayerEnv19xSheen), 0.0).x;
    #endif
    #if defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x)
      return vTextureLod(LookUpTexture2D, vec3(vMax(0.0, vDot(iN,iV)), iRoughness, g_IBLLayerEnv21xSheen), 0.0).x;
    #endif
    return 0.0; // Default
  #else
    return 0.0;
  #endif
}

float getMipMapLevel(in float iRoughness, in float iMaxLevel)
{
  #ifdef IBLLocal
    return vSqrt(iRoughness) * iMaxLevel;
  #else
    float minRoughnessSqrt = 0.1;
    return (vSqrt(iRoughness) - minRoughnessSqrt) / (1.0 - minRoughnessSqrt) * iMaxLevel;
  #endif // IBLLocal
}

float getMipMapLevelSheen(in float iRoughness, in float iMaxLevel)
{
  #ifdef IBLLocal
    return vSqrt(iRoughness) * iMaxLevel;
  #else
    float minRoughnessSqrt = 0.1;
    return (vSqrt(1.0 - iRoughness) - minRoughnessSqrt) / (1.0 - minRoughnessSqrt) * iMaxLevel;
  #endif // IBLLocal
}

vec3 computeBaseIBL(in LightingData iData, in BRDFParameters iParameters,
    in float numMaps, out vec3 specContrib, out vec3 diffuseContrib)
{
#ifdef XRiteCarPaint2

    const vec3 N_ss   = ComputeTransformation(iData.Nworld);
    const vec3 V_ss   = ComputeTransformation(iData.Vworld);
    //const vec3 Nc_ss_ = vec3(vGetViewInvMatrix() * vec4(iParameters.clearcoatNormal, 0.0));
    //const vec3 Nc_ss  = ComputeTransformation(Nc_ss_);

    const vec3 Nc_ss = N_ss;

    const vec3 Rc_ss  = vNormalize(-vReflect(V_ss, Nc_ss));
    const vec3 tex_sample = ComputeSpecularIBL(Rc_ss, 0.0);

    vec3 outRad_sum = vec3(0.0, 0.0, 0.0);

    vec3 wo_trans;
    float f_trans_out;
    const float f_refl_out = CPA2_ProcessLight_clearcoat_layer(V_ss, Nc_ss, Rc_ss,
        iParameters.clearcoat_no_refraction, iParameters.clearcoat_ior, wo_trans, f_trans_out);

    outRad_sum += CPA2_MultMaterialLight(f_refl_out, tex_sample.xyz);

    // ss - scene space = world space
    for (int iDirLight = 0; iDirLight < 16; iDirLight++) {
        const vec3 L_ss_ = cb_IBLDirLightsApprox.u_IBLDirLightsApprox[iDirLight].direction;
        //const vec3 L_ss = ComputeTransformation(L_ss_);

        const float solid_angle = cb_IBLDirLightsApprox.u_IBLDirLightsApprox[iDirLight].solid_angle;
        const vec3 inRad = cb_IBLDirLightsApprox.u_IBLDirLightsApprox[iDirLight].color;

        const vec3 bsdf = CPA2_ProcessLightAxfCpa2(N_ss, V_ss, Nc_ss, L_ss_, solid_angle, wo_trans, f_trans_out, iParameters);

        outRad_sum += CPA2_MultMaterialLight(bsdf, inRad);
    }

    return outRad_sum;

#endif // XRiteCarPaint2

// ----------------------------------------------------------------------------

#ifdef EVisuPBR

    const vec3 N = ComputeTransformation(iData.Nworld);
    const vec3 V = ComputeTransformation(iData.Vworld);
    const vec3 R = vNormalize(-vReflect(V, N));
    const vec3 Normal = CorrectedDirection(N, iData.P);
    const vec3 Reflected = CorrectedDirection(R, iData.P);
    const vec3 View = CorrectedDirection(V, iData.P);
    const float NoV = max(0.0, dot(N, V));

    fresnel_dielectric_parameters params;
    params.specularTint = iParameters.specularTint;
    params.ior = iParameters.ior;
    params.albedo = iParameters.albedo;
    params.specular = iParameters.specular;
    params.metallic = iParameters.metallic;

    const vec3 F = fresnel_dielectric(params, NoV);

    const vec3 diffuseIBLSample = ComputeDiffuseIBL(Normal);

    diffuseContrib = diffuseIBLSample;

    #ifdef SO_EVISUPBR_TRANSLUCENCY
      const vec3 transluIBLSample = ComputeDiffuseIBL(-Normal); // First invert then correct, or the other way around?
    #endif
    vec3 specularIBLSample = vec3(0.0);

    const float mipLevel = getMipMapLevel(iParameters.roughness, numMaps);

    if (iParameters.anisotropy > 0.0) {
      float angle = iParameters.anisotropyRotation * 2.0 * PI;
      vec3 rot_T = vCos(angle) * ComputeTransformation(iData.T) + vSin(angle) * ComputeTransformation(iData.B);
      vec3 rot_B = vCross(iData.N, rot_T);
      rot_T = CorrectedDirection(rot_T, iData.P);
      rot_B = CorrectedDirection(rot_B, iData.P);
      specularIBLSample = ComputeSpecularIBL(iParameters.anisotropy, iParameters.roughness, rot_T, rot_B, Reflected,getMipMapLevel(iParameters.roughness,numMaps));
    } else {
      specularIBLSample = ComputeSpecularIBL(Reflected, mipLevel);
    }

    vec2 envBRDF = ComputeEnvBRDF(iParameters.roughness, N, V);

    vec3 sheen19x = vec3(0.0);
    float sheenDiffuseWeight = 1.0;

    #if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver19x)
    {
      const float sheenMipLevel = getMipMapLevelSheen(iParameters.sheen, numMaps);
      sheenDiffuseWeight = vPow5(1.0 - iParameters.sheen);
      const vec3 sheenIBLSample = ComputeSheenIBL(Reflected, sheenMipLevel);
      const float envSheenBRDF = ComputeEnvSheenBRDF(clamp(iParameters.sheen, 1e-6, 1.0-1e-6), N, V);
      const vec3 rho_b = iParameters.albedo * (1.0 - iParameters.metallic) * (1.0 - iParameters.transparency) * (1.0 - sheenDiffuseWeight);
      sheen19x = (vec3(1.0) - F) * rho_b * sheenIBLSample * envSheenBRDF;
    }
    #endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver19x

    vec3 rho_d = iParameters.albedo * (1.0 - iParameters.metallic) * (1.0 - iParameters.transparency) * sheenDiffuseWeight;
    #ifdef SO_EVISUPBR_TRANSLUCENCY
      vec3 diffuse = (vec3(1.0) - F) * rho_d * ((1.0 - iParameters.translucency) * diffuseIBLSample + iParameters.translucency * transluIBLSample);
    #else
      vec3 diffuse = (vec3(1.0) - F) * rho_d * diffuseIBLSample;
    #endif

    const float F_0 = vPow2((1.0 - iParameters.ior) / (1.0 + iParameters.ior));
    const vec3 rho_sr0 = (1.0 - iParameters.metallic) * F_0 * iParameters.specularTint * iParameters.specular + iParameters.metallic * iParameters.albedo;
    const vec3 rho_sr90 = vec3((1.0-iParameters.metallic) * iParameters.specular + iParameters.metallic);
    const vec3 GFLoH = rho_sr0 * envBRDF.x + rho_sr90 * envBRDF.y;

    vec3 specular = GFLoH * specularIBLSample;

    #if defined(LightMap) && (LightMap == LightMapIlluminanceMode)
      diffuse = vec3(0.0);
      vec3 lightMapAtt = vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
      specular *= lightMapAtt;
      sheen19x *= lightMapAtt;
    #endif

  vec3 f_s = vec3(0.0);
  float base_weight = 1.0;

  #ifdef SO_EVISUPBR_FLAKES
  {
    float total_flake_roughness = iParameters.flakeRoughness*iParameters.flakeRoughness;

    float flake_orientation_roughness;
    float flake_cos_cone_angle;

    float flake_coverage = iParameters.flakeCoverage;
    float flake_cone_roughness;

    distribute_flake_roughness(total_flake_roughness, flake_orientation_roughness, flake_cos_cone_angle, flake_cone_roughness);

    vec3 flakeLight = normalize(mix(Reflected, Normal, iParameters.flakeRoughness));

    vec3 H = normalize(flakeLight + View);

    float a = 0.001 * (iParameters.flakeSize * 0.5);
    float avg_cell_area = 1.5 * sqrt(3.0) * a * a;
    float cells_per_area = 1.0 / avg_cell_area;

    mat3 mat = transpose(mat3(_vPrivGetWorldMatrix()));
    float scale = max(max(length(mat[0]), length(mat[1])), length(mat[2]));

    vec3 position_object = EVisuPBR_vLocalPosition;
    vec3 position_object_meters = 0.001 * scale * position_object;

    vec3 p_ddx = dFdxFine(position_object_meters);
    vec3 p_ddy = dFdyFine(position_object_meters);

    vec2 footprint_uv;
    vec2 footprint_uv_ddx;
    vec2 footprint_uv_ddy;
    triplanar_mapping(position_object_meters, p_ddx, p_ddy, EVisuPBR_vLocalNormal, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);

    float footprint_det = footprint_uv_ddx.x * footprint_uv_ddy.y - footprint_uv_ddx.y * footprint_uv_ddy.x;
    float footprint_area = abs(footprint_det);

    float flakes_per_area = flake_coverage * cells_per_area;
    float expected_num_flakes_inside_footprint = footprint_area * flakes_per_area;

    float log_cells_in_footprint = log(footprint_area / avg_cell_area);

    #ifdef SO_EVISUPBR_FLAKE_ACCURACY_GOAL
      #if SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 0
        //Quality
        const float closeup_stochastic_transition = 1.0;
        const float closeup_smooth_transition = 64.0;
        const float stochastic_smooth_transition = 131072.0;
      #elif SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 1
        //Performance
        const float closeup_stochastic_transition = 1.0;
        const float closeup_smooth_transition = 4.0;
        const float stochastic_smooth_transition = 1024.0;
      #endif
    #endif

    // Filled inside the model_weights() below
    float closeup_weight = 0.0;
    float stochastic_weight = 0.0;
    float smooth_weight = 0.0;
    vec3 voronoi_cell_orientation = vec3(0.0);

    model_weights(closeup_stochastic_transition, closeup_smooth_transition, stochastic_smooth_transition,
        flake_coverage, log_cells_in_footprint,
        base_weight, closeup_weight, stochastic_weight, smooth_weight, voronoi_cell_orientation,
        flake_orientation_roughness, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);

    vec3 T = ComputeTransformation(iData.T);
    vec3 B = ComputeTransformation(iData.B);
    T = CorrectedDirection(T, iData.P);
    B = CorrectedDirection(B, iData.P);
    float NoL = max(0.0, dot(flakeLight, Normal));
    float NoH = max(0.0, dot(H, Normal));
    float LoH = max(0.0, dot(H, flakeLight));
    float upLimit = 1.0 / max(1.0 - iParameters.flakeRoughness, 1e-6);

    float cos_cone_angle = flake_cos_cone_angle;
    vec3 front_flake_orientation = voronoi_cell_orientation;
    float cone_solid_angle = 2.0 * PI * (1.0 - cos_cone_angle);
    vec3 front_flake_orientation_view = normalize(front_flake_orientation.x*T + front_flake_orientation.y*B + front_flake_orientation.z*Normal);
    vec3 r = normalize(reflect(-View, front_flake_orientation_view));

    vec2 envBRDF = ComputeEnvBRDF(iParameters.flakeRoughness, Normal, View);
    //float GFLoH = envBRDF.x + envBRDF.y;

    #ifdef SO_EVISUPBR_ver22x
      // flake color accounting flip-flop effect, avaliable since DSPBR22x
      // If iParameters.flipFlop equals zero, flake_color should be iParameters.flakeColor
      // Blending parameter clamped to zero to avoid calculation problem when iParameters.flipFlop equals zero
      const vec3 flake_color = vMix(iParameters.flakeColor, iParameters.flipFlopColor, vMax(0.0, vPow(LoH, 1.0 / vPow2(iParameters.flipFlop))));
    #else
      const vec3 flake_color = iParameters.flakeColor;
    #endif // SO_EVISUPBR_ver22x

    if(closeup_weight > 1e-6 && dot(View, front_flake_orientation_view) > 0.0)
    {
      vec3 cubeColor = ComputeSpecularIBL(r, getMipMapLevel(iParameters.flakeRoughness, numMaps));
      vec3 cubeColorLarge = cubeColor;
      float single_flake_eval = 1.0 / (cone_solid_angle * abs(dot(View, Normal)));
      f_s += cubeColorLarge * flake_color * clamp(single_flake_eval, 0.0, 1.0) * closeup_weight;
    }

    if(stochastic_weight > 1e-6)
    {
      vec3 cubeColor = ComputeSpecularIBL(Reflected, getMipMapLevel(iParameters.flakeRoughness, numMaps));
      float flakes_contributing = 0.0;
      float flakes_in_footprint = 0.0;
      stochastic_flakes(flake_orientation_roughness, cos_cone_angle, expected_num_flakes_inside_footprint, cells_per_area,
        footprint_uv, footprint_uv_ddx, footprint_uv_ddy, flake_coverage, -View, flakeLight, Normal, flakes_contributing, flakes_in_footprint);

      float flake_count_threshold = 10.0;
      float alpha = min(1.0, flakes_in_footprint / flake_count_threshold);
      float reference_flake_count = mix(expected_num_flakes_inside_footprint, flakes_in_footprint, alpha);
      reference_flake_count = max(0.01, reference_flake_count);

      float d = clamp(flakes_contributing / (cone_solid_angle * reference_flake_count), 0.0, upLimit);
      f_s += cubeColor * flake_color * d * stochastic_weight;
    }

    if(smooth_weight > 1e-6)
    {
      vec3 cubeColor = ComputeSpecularIBL(Reflected, getMipMapLevel(iParameters.flakeRoughness, numMaps));
      f_s += cubeColor * flake_color * smooth_weight;
    }
  }
  #endif // SO_EVISUPBR_FLAKES

  specContrib = mix(f_s, specular + sheen19x, base_weight);

  vec3 result = mix(f_s, diffuse + specular + sheen19x, base_weight);

  #if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver21x)
  {
    const float sheenMipLevel = getMipMapLevelSheen(iParameters.sheenRoughness, numMaps);
    const float sheen_alpha = max(iParameters.sheenRoughness, 0.07);
    const float sheenCoreWeight = DSPBR21xSheen_core_att_2(NoV, iParameters.sheen, iParameters.sheenColor, sheen_alpha);
    const vec3 sheenIBLSample = ComputeSheenIBL(Reflected, sheenMipLevel);
    const float envSheenBRDF = ComputeEnvSheenBRDF(clamp(iParameters.sheenRoughness, 1e-6, 1.0-1e-6), N, V);
    const vec3 sheen21x = iParameters.sheenColor * iParameters.sheen * sheenIBLSample * envSheenBRDF;
    result *= sheenCoreWeight;
    result += sheen21x;
  }
  #endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver21x

  #if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver22x)
  {
    const float sheenMipLevel = getMipMapLevelSheen(iParameters.sheenRoughness, numMaps);
    // For DSPBR22x iParameters.sheen = 1
    const float sheenCoreWeight = DSPBR21xSheen_core_att_2(NoV, 1.0, iParameters.sheenColor, iParameters.sheenRoughness);
    const vec3 sheenIBLSample = ComputeSheenIBL(Reflected, sheenMipLevel);
    const float envSheenBRDF = ComputeEnvSheenBRDF(clamp(iParameters.sheenRoughness, 1e-6, 1.0-1e-6), N, V);
    const vec3 sheen22x = iParameters.sheenColor * sheenIBLSample * envSheenBRDF;
    result *= sheenCoreWeight;
    result += sheen22x;
  }
  #endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver22x

  #ifdef SO_EVISUPBR_CLEARCOAT
  {
    const vec3 clearcoatNormalWorld = vec3(vGetViewInvMatrix() * vec4(iParameters.clearcoatNormal, 0.0));
    const vec3 Nc = ComputeTransformation(clearcoatNormalWorld);

    const float NcoV = vMax(vDot(Nc, V), 0.0);
    const vec2 clearcoatEnvBRDF = ComputeEnvBRDF(iParameters.clearcoatRoughness, Nc, V);
    const float clearcoatF = 0.04 * clearcoatEnvBRDF.x + clearcoatEnvBRDF.y;
    const float clearcoatF1 = clearcoatF;
    const float clearcoatF2 = 0.04 + 0.96 * vPow5(1.0 - NcoV);

    const vec3 R = vNormalize(-vReflect(V, Nc));
    const vec3 Reflected = CorrectedDirection(R, iData.P);

    const float clearcoat_att_fac = (1.0 - iParameters.clearcoat * vMax(clearcoatF1, clearcoatF2));
    vec3 f_coat = ComputeSpecularIBL(Reflected, getMipMapLevel(iParameters.clearcoatRoughness, numMaps));
    f_coat *= iParameters.clearcoat * clearcoatF;

    result *= clearcoat_att_fac;
    result += f_coat;

    specContrib *= clearcoat_att_fac;
    specContrib += f_coat;
  }
  #endif // SO_EVISUPBR_CLEARCOAT

  return result;

#else // ----------------------------------------------------------------------

#ifndef XRiteCarPaint2

    // if not EVisuPBR and not XRiteCarPaint2

    // TODO: implement for EVisuPBR !!!
      vec3 N = ComputeTransformation(iData.Nworld);
      vec3 V = iData.VworldTransformed;
      vec3 R = vNormalize(-vReflect(V, N));
      vec3 Normal = CorrectedDirection(N, iData.P);
      vec3 Reflected = CorrectedDirection(R, iData.P);

    #ifdef GLESPlatform
      vec3 diffuseIBLSample = vec3(vDot(N,V)) * vec3(INV_PI) * DiffuseFactor;
    #else
      vec3 diffuseIBLSample = ComputeDiffuseIBL(Normal);
    #endif
    
    diffuseContrib = diffuseIBLSample;

    #ifdef AnisotropicDistribution
      vec3 rot_T = vCos(iParameters.anisotropyAngle * 2.0 * PI) * ComputeTransformation(iData.T) +
                   vSin(iParameters.anisotropyAngle * 2.0 * PI) * ComputeTransformation(iData.B);
      vec3 rot_B = vCross(iData.N, rot_T);
      rot_T = CorrectedDirection(rot_T, iData.P);
      rot_B = CorrectedDirection(rot_B, iData.P);
      vec3 specularIBLSample = ComputeSpecularIBL(iParameters.anisotropy, iParameters.roughness, rot_T, rot_B, Reflected,getMipMapLevel(iParameters.roughness,numMaps));
    #else
      vec3 specularIBLSample = ComputeSpecularIBL(Reflected,getMipMapLevel(iParameters.roughness,numMaps));
    #endif

    #ifdef PDSFX_ENABLE_IBL_CONTROL
      diffuseIBLSample *= iParameters.diffuseIBLFactor;
      specularIBLSample *= iParameters.specularIBLFactor;
    #endif // PDSFX_ENABLE_IBL_CONTROL

    vec2 envBRDF = ComputeEnvBRDF(iParameters.roughness, N, V);

    vec3 f0 = iParameters.f0 * envBRDF.x + iParameters.f90 * envBRDF.y;

  #if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
    vec3 diffuse = diffuseIBLSample * iParameters.albedo;
    vec3 specular = specularIBLSample;
  #else
    vec3 diffuse = vec3(0.0);
    vec3 specular = specularIBLSample * vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
  #endif
    specContrib = specular * f0;

    return diffuse * (1.0-vDot(f0, vec3(0.299, 0.587, 0.114))) + specContrib;

#endif // XRiteCarPaint2

#endif
}

#ifdef Coating

vec3 computeCoatingIBL(in LightingData iData, in BRDFParameters iParameters, in float numMaps)
{
  if (vLength(iParameters.coatingF0) < kEpsilon)
    return vec3(0.0);

  // TODO: implement for EVisuPBR !!!
  vec3 N = ComputeTransformation(iData.coatingNWorld);
  vec3 V = iData.VworldTransformed;

  vec3 R = vNormalize(-vReflect(V, N));
  vec3 Normal = CorrectedDirection(N, iData.P);
  vec3 Reflected = CorrectedDirection(R, iData.P);

  vec3 coatingSpecularIBLSample = ComputeSpecularIBL(Reflected, getMipMapLevel(iParameters.coatingRoughness,numMaps));

  #ifdef PDSFX_ENABLE_IBL_CONTROL
    coatingSpecularIBLSample *= iParameters.specularIBLFactor;
  #endif // PDSFX_ENABLE_IBL_CONTROL

  vec2 coatingEnvBRDF = ComputeEnvBRDF(iParameters.coatingRoughness, N, V);
  vec3 coatingF0 = iParameters.coatingF0* coatingEnvBRDF.x + coatingEnvBRDF.y;

  return coatingSpecularIBLSample * coatingF0;
}

#endif // Coating

#ifdef Flakes

vec3 computeMetallicFlakesIBL(in LightingData iData, in BRDFParameters iParameters, in float numMaps)
{
  if (vLength(iParameters.metallicFlakesF0) < kEpsilon)
    return vec3(0.0);

  // TODO: implement for EVisuPBR !!!
  vec3 N = ComputeTransformation(iData.metalFlakesNWorld);
  vec3 V = iData.VworldTransformed;

  vec3 R = vNormalize(-vReflect(V, N));
  vec3 Normal = CorrectedDirection(N, iData.P);
  vec3 Reflected = CorrectedDirection(R, iData.P);

  vec3 flakesSpecularIBLSample = ComputeSpecularIBL(Reflected, getMipMapLevel(iParameters.metallicFlakesRoughness,numMaps));

  #ifdef PDSFX_ENABLE_IBL_CONTROL
    flakesSpecularIBLSample *= iParameters.specularIBLFactor;
  #endif // PDSFX_ENABLE_IBL_CONTROL

  vec2 flakesEnvBRDF = ComputeEnvBRDF(iParameters.metallicFlakesRoughness,N, V);
  vec3 flakesF0 = iParameters.metallicFlakesF0* flakesEnvBRDF.x;

  return flakesSpecularIBLSample * flakesF0;
}

vec3 computeMetalIBL(in LightingData iData, in BRDFParameters iParameters, in float numMaps)
{
  if (vLength(iParameters.metalF0) < kEpsilon)
    return vec3(0.0);

  // TODO: implement for EVisuPBR !!!
  #ifdef Coating
    vec3 metalN = ComputeTransformation(iData.coatingNWorld);
  #else // Coating
    vec3 metalN = ComputeTransformation(iData.Nworld);
  #endif // Coating

  vec3 V = iData.VworldTransformed;

  vec3 metalR = vNormalize(-vReflect(V, metalN));
  vec3 metalReflected = CorrectedDirection(metalR, iData.P);

  vec3 metalSpecularIBLSample = ComputeSpecularIBL(metalReflected,getMipMapLevel(iParameters.metalRoughness,numMaps));

  #ifdef PDSFX_ENABLE_IBL_CONTROL
    metalSpecularIBLSample *= iParameters.specularIBLFactor;
  #endif // PDSFX_ENABLE_IBL_CONTROL

  vec2 metalEnvBRDF = ComputeEnvBRDF(iParameters.metalRoughness, metalN, V);
  vec3 metalF0 = iParameters.metalF0* metalEnvBRDF.x;

  return metalSpecularIBLSample * metalF0;
}

vec3 computePearlFlakesIBL(in LightingData iData, in BRDFParameters iParameters, in float numMaps)
{
  if (vLength(iParameters.pearlFlakesF0) < kEpsilon)
    return vec3(0.0);

  // TODO: implement for EVisuPBR !!!
  vec3 N = ComputeTransformation(iData.pearlFlakesNWorld);
  vec3 V = iData.VworldTransformed;

  vec3 R = vNormalize(-vReflect(V, N));
  vec3 Normal = CorrectedDirection(N, iData.P);
  vec3 Reflected = CorrectedDirection(R, iData.P);

  vec3 flakesSpecularIBLSample = ComputeSpecularIBL(Reflected,getMipMapLevel(iParameters.pearlFlakesRoughness,numMaps));

  #ifdef PDSFX_ENABLE_IBL_CONTROL
    flakesSpecularIBLSample *= iParameters.specularIBLFactor;
  #endif // PDSFX_ENABLE_IBL_CONTROL

  vec2 flakesEnvBRDF = ComputeEnvBRDF(iParameters.pearlFlakesRoughness,N, V );
  vec3 flakesF0 = iParameters.pearlFlakesF0* flakesEnvBRDF.x;

  return flakesSpecularIBLSample * flakesF0;
}

vec3 computePearlIBL(in LightingData iData, in BRDFParameters iParameters, in float numMaps)
{
  if (vLength(iParameters.pearlF0) < kEpsilon)
    return vec3(0.0);

  // TODO: implement for EVisuPBR !!!
  #ifdef Coating
    vec3 pearlN = ComputeTransformation(iData.coatingNWorld);
  #else // Coating
    vec3 pearlN = ComputeTransformation(iData.Nworld);
  #endif // Coating

  vec3 V = iData.VworldTransformed;

  vec3 pearlR = vNormalize(-vReflect(V, pearlN));
  vec3 pearlReflected = CorrectedDirection(pearlR, iData.P);

  vec3 pearlSpecularIBLSample = ComputeSpecularIBL(pearlReflected,getMipMapLevel(iParameters.pearlRoughness,numMaps));

#ifdef PDSFX_ENABLE_IBL_CONTROL
  pearlSpecularIBLSample *= iParameters.specularIBLFactor;
#endif // PDSFX_ENABLE_IBL_CONTROL

  vec2 pearlEnvBRDF = ComputeEnvBRDF(iParameters.pearlRoughness, pearlN, V);
  vec3 pearlF0 = iParameters.pearlF0* pearlEnvBRDF.x;

  return pearlSpecularIBLSample * pearlF0;
}
#endif // Flakes

#endif // fragment stage
#endif // ImageBasedLighting
#endif // Lighting
