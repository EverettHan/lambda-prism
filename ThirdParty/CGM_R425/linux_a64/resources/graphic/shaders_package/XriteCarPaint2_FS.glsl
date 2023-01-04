// Base
float XRiteCarPaint2_ct_coeffs[4]; // CPA2_MAX_NUM_LOBES=4
float XRiteCarPaint2_ct_f0s[4]; // CPA2_MAX_NUM_LOBES=4
float XRiteCarPaint2_ct_spreads[4]; // CPA2_MAX_NUM_LOBES=4
int   XRiteCarPaint2_ct_n_lobes;
float XRiteCarPaint2_ct_diffuse;
// Flakes
float XRiteCarPaint2_flakes_uv_trf_scale;
//float XRiteCarPaint2_texture_transformation[5];
int   XRiteCarPaint2_num_thetaF;
int   XRiteCarPaint2_num_thetaI;
int   XRiteCarPaint2_max_thetaI;
// Clearcoat
//#ifdef SO_XRITE_CARPAINT2_CLEARCOAT
int   XRiteCarPaint2_clearcoat_no_refraction;
float XRiteCarPaint2_clearcoat_ior;
//#endif // SO_XRITE_CARPAINT2_CLEARCOAT
// Flakes
int   XRiteCarPaint2_thetaFI_sliceLUT[64];

vec3  XRiteCarPaint2_clearcoat_normal;

vec3  XRiteCarPaint2_tc_gpu_mapping;

//vec3 XRiteCarPaint2_clearcoat_contrib;

/*
struct commonIntermediateData {
  //vec3 Tc_vs; // unused
  //vec3 Bc_vs; // unused
  vec3 Nc_vs;
  vec3 wo_trans_vs;
  float f_trans_out;
  vec3 clearcoat_contrib;
};

commonIntermediateData XRiteCarPaint2_interm_data;
*/

mapping_result_t XRiteCarPaint2_mappings[SO_XRITECARPAINT2_MAPPING_COUNT];

void GetMapping(int iSlot, inout mapping_result_t oMapping) {
    int mapping = VisMapping.slot_to_mapping[iSlot];
    oMapping = XRiteCarPaint2_mappings[mapping];
}

void ComputeMapping(in int iIndex, inout mapping_result_t oMapping)
{
    const mat4 object_transform = VisMapping.object_transform[iIndex];
    const mat4 inv_object_transform = vTranspose(object_transform);

    mapping_info_t info;
    info.p = vec3(object_transform * vec4(XRiteCarPaint2_vLocalPosition, 1.0));
    info.n = vec3(object_transform * vec4(XRiteCarPaint2_vLocalNormal, 0.0));
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
    for (int i = 0; i < SO_XRITECARPAINT2_MAPPING_COUNT; ++i) {
        ComputeMapping(i, XRiteCarPaint2_mappings[i]);
    }
}

void XRiteCarPaint2_ComputeCommonValues()
{
    // Base
    XRiteCarPaint2_ct_coeffs[0]  = cb_XRiteCarPaint2.ct_coeffs[0];
    XRiteCarPaint2_ct_coeffs[1]  = cb_XRiteCarPaint2.ct_coeffs[1];
    XRiteCarPaint2_ct_coeffs[2]  = cb_XRiteCarPaint2.ct_coeffs[2];
    XRiteCarPaint2_ct_coeffs[3]  = cb_XRiteCarPaint2.ct_coeffs[3];
    //XRiteCarPaint2_ct_coeffs[4]  = cb_XRiteCarPaint2.ct_coeffs[4]; // CPA2_MAX_NUM_LOBES=4
    XRiteCarPaint2_ct_f0s[0]     = cb_XRiteCarPaint2.ct_f0s[0];
    XRiteCarPaint2_ct_f0s[1]     = cb_XRiteCarPaint2.ct_f0s[1];
    XRiteCarPaint2_ct_f0s[2]     = cb_XRiteCarPaint2.ct_f0s[2];
    XRiteCarPaint2_ct_f0s[3]     = cb_XRiteCarPaint2.ct_f0s[3];
    //XRiteCarPaint2_ct_f0s[4]     = cb_XRiteCarPaint2.ct_f0s[4]; // CPA2_MAX_NUM_LOBES=4
    XRiteCarPaint2_ct_spreads[0] = cb_XRiteCarPaint2.ct_spreads[0];
    XRiteCarPaint2_ct_spreads[1] = cb_XRiteCarPaint2.ct_spreads[1];
    XRiteCarPaint2_ct_spreads[2] = cb_XRiteCarPaint2.ct_spreads[2];
    XRiteCarPaint2_ct_spreads[3] = cb_XRiteCarPaint2.ct_spreads[3];
    //XRiteCarPaint2_ct_spreads[4] = cb_XRiteCarPaint2.ct_spreads[4]; // CPA2_MAX_NUM_LOBES=4
    XRiteCarPaint2_ct_n_lobes    = cb_XRiteCarPaint2.ct_n_lobes;
    XRiteCarPaint2_ct_diffuse    = cb_XRiteCarPaint2.ct_diffuse;
    // Flakes
    XRiteCarPaint2_flakes_uv_trf_scale = cb_XRiteCarPaint2.flakes_uv_trf_scale;
    //XRiteCarPaint2_texture_transformation[0] = cb_XRiteCarPaint2.texture_transformation[0];
    //XRiteCarPaint2_texture_transformation[1] = cb_XRiteCarPaint2.texture_transformation[1];
    //XRiteCarPaint2_texture_transformation[2] = cb_XRiteCarPaint2.texture_transformation[2];
    //XRiteCarPaint2_texture_transformation[3] = cb_XRiteCarPaint2.texture_transformation[3];
    //XRiteCarPaint2_texture_transformation[4] = cb_XRiteCarPaint2.texture_transformation[4];
    XRiteCarPaint2_num_thetaF    = cb_XRiteCarPaint2.num_thetaF;
    XRiteCarPaint2_num_thetaI    = cb_XRiteCarPaint2.num_thetaI;
    XRiteCarPaint2_max_thetaI    = cb_XRiteCarPaint2.max_thetaI;
    // Clearcoat
//#ifdef SO_XRITE_CARPAINT2_CLEARCOAT
    XRiteCarPaint2_clearcoat_no_refraction = cb_XRiteCarPaint2.clearcoat_no_refraction;
    XRiteCarPaint2_clearcoat_ior = cb_XRiteCarPaint2.clearcoat_ior;
//#endif // SO_XRITE_CARPAINT2_CLEARCOAT
    // Flakes
    for (int i = 0; i < 64; i++) {
        XRiteCarPaint2_thetaFI_sliceLUT[i] = cb_XRiteCarPaint2.thetaFI_sliceLUT[i];
    }

    ComputeMappings();
    // Pass the mapping results to the lightingHelpers.glsl
    mapping_result_t mapping;
    GetMapping(0, mapping);
    XRiteCarPaint2_tc_gpu_mapping = vec3(mapping.uv_mod, 0.0);

#ifndef SO_XRITE_CARPAINT2_CLEARCOAT
    XRiteCarPaint2_clearcoat_normal = vGetViewNormal();
#else
    XRiteCarPaint2_clearcoat_normal = texture(clearcoat_normal_map, XRiteCarPaint2_tc_gpu_mapping.xy).xyz;
    {
      mapping_result_t mapping;
      GetMapping(0, mapping);
      //TODO
      //XRiteCarPaint2_clearcoat_normal = vNormalize(
      //      XRiteCarPaint2_clearcoat_normal.x  * mapping.t +
      //      XRiteCarPaint2_clearcoat_normal.y  * mapping.b +
      //  abs(XRiteCarPaint2_clearcoat_normal.z) * XRiteCarPaint2_worldNormal);
      XRiteCarPaint2_clearcoat_normal = vec3(vGetViewMatrix() * vec4(XRiteCarPaint2_clearcoat_normal, 0.0));
    }
#endif // SO_XRITE_CARPAINT2_CLEARCOAT

    // Calculate clearcoat contribution. Must be done before any lighting calculations.
    // Fills XRiteCarPaint2_interm_data
    //XRiteCarPaint2_clearcoat_contrib = CPA2_ProcessLight_clearcoat_layer(
    //    XRiteCarPaint2_clearcoat_normal, XRiteCarPaint2_clearcoat_no_refraction, XRiteCarPaint2_clearcoat_ior,
    //    g_XRiteCarPaint2_interm_data);
}

void XRiteCarPaint2_ProcessBRDFParameters(inout BRDFParameters oParams)
{
    // Base
    oParams.ct_coeffs[0]  = XRiteCarPaint2_ct_coeffs[0];
    oParams.ct_coeffs[1]  = XRiteCarPaint2_ct_coeffs[1];
    oParams.ct_coeffs[2]  = XRiteCarPaint2_ct_coeffs[2];
    oParams.ct_coeffs[3]  = XRiteCarPaint2_ct_coeffs[3];
    //oParams.ct_coeffs[4]  = XRiteCarPaint2_ct_coeffs[4]; // CPA2_MAX_NUM_LOBES=4
    oParams.ct_f0s[0]     = XRiteCarPaint2_ct_f0s[0];
    oParams.ct_f0s[1]     = XRiteCarPaint2_ct_f0s[1];
    oParams.ct_f0s[2]     = XRiteCarPaint2_ct_f0s[2];
    oParams.ct_f0s[3]     = XRiteCarPaint2_ct_f0s[3];
    //oParams.ct_f0s[4]     = XRiteCarPaint2_ct_f0s[4]; // CPA2_MAX_NUM_LOBES=4
    oParams.ct_spreads[0] = XRiteCarPaint2_ct_spreads[0];
    oParams.ct_spreads[1] = XRiteCarPaint2_ct_spreads[1];
    oParams.ct_spreads[2] = XRiteCarPaint2_ct_spreads[2];
    oParams.ct_spreads[3] = XRiteCarPaint2_ct_spreads[3];
    //oParams.ct_spreads[4] = XRiteCarPaint2_ct_spreads[4]; // CPA2_MAX_NUM_LOBES=4
    oParams.ct_n_lobes    = XRiteCarPaint2_ct_n_lobes;
    oParams.ct_diffuse    = XRiteCarPaint2_ct_diffuse;
    // Flakes
    oParams.flakes_uv_trf_scale = XRiteCarPaint2_flakes_uv_trf_scale;
    //oParams.texture_transformation[0] = XRiteCarPaint2_texture_transformation[0];
    //oParams.texture_transformation[1] = XRiteCarPaint2_texture_transformation[1];
    //oParams.texture_transformation[2] = XRiteCarPaint2_texture_transformation[2];
    //oParams.texture_transformation[3] = XRiteCarPaint2_texture_transformation[3];
    //oParams.texture_transformation[4] = XRiteCarPaint2_texture_transformation[4];
    oParams.num_thetaF    = XRiteCarPaint2_num_thetaF;
    oParams.num_thetaI    = XRiteCarPaint2_num_thetaI;
    oParams.max_thetaI    = XRiteCarPaint2_max_thetaI;
    // Clearcoat
    oParams.clearcoat_no_refraction = XRiteCarPaint2_clearcoat_no_refraction;
    oParams.clearcoat_ior = XRiteCarPaint2_clearcoat_ior;
    // Flakes
    for (int i = 0; i < 64; i++) {
        oParams.thetaFI_sliceLUT[i] = XRiteCarPaint2_thetaFI_sliceLUT[i];
    }

    oParams.clearcoatNormal = XRiteCarPaint2_clearcoat_normal;

    oParams.tc_gpu_mapping = XRiteCarPaint2_tc_gpu_mapping;
}

#if !(defined(VertexStage) && defined(PDSFX1_VS_CommonValues_XRiteCarPaint2)) && !(defined(FragmentStage) && defined(PDSFX1_FS_CommonValues_XRiteCarPaint2))
void ComputeCommonValues()
{
    XRiteCarPaint2_ComputeCommonValues();
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Discard_XRiteCarPaint2))
bool ComputeDiscard()
{
    return false;
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Albedo_XRiteCarPaint2))
vec3 ComputeAlbedo()
{
    return vec3(0.4, 0.6, 0.8);
}
#endif

//vec3 ComputeViewPosition()
//{
//}

//vec3 ComputeViewNormal()
//{
//}

//vec3 ComputeSpecularReflectance()
//{
//}

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Roughness_XRiteCarPaint2))
float ComputeRoughness()
{
    return 0.0;
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Transparency_XRiteCarPaint2))
float ComputeTransparency()
{
    return 0.0;
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Emissive_XRiteCarPaint2))
vec3 ComputeEmissive()
{
    return vec3(0.0, 0.0, 0.0);
}
#endif

#if !(defined(FragmentStage) && defined(PDSFX1_FS_Opacity_XRiteCarPaint2))
float ComputeOpacity()
{
    return 0.9; //TODO 1.0?
}
#endif

void ProcessBRDFParameters(inout BRDFParameters oParams)
{
    XRiteCarPaint2_ProcessBRDFParameters(oParams);
}

void ProcessFinalColor(inout vec4 ioFinalColor)
{
    //ioFinalColor += vec4(XRiteCarPaint2_clearcoat_contrib, 0.0);
}
