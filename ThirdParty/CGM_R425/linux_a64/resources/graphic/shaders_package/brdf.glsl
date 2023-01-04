// XRite CarPaint2 ------------------------------------------------------------

#ifdef XRiteCarPaint2

struct BRDFParameters
{
  // Base
  float   ct_coeffs[4]; // CPA2_MAX_NUM_LOBES=4
  float   ct_f0s[4]; // CPA2_MAX_NUM_LOBES=4
  float   ct_spreads[4]; // CPA2_MAX_NUM_LOBES=4
  int     ct_n_lobes;
  float   ct_diffuse;
  // Flakes
  float   flakes_uv_trf_scale;
  //float   texture_transformation[5];
  int     num_thetaF;
  int     num_thetaI;
  int     max_thetaI;
  // Clearcoat

  int     clearcoat_no_refraction;
  float   clearcoat_ior;

  // Flakes
  int     thetaFI_sliceLUT[64];

  vec3    clearcoatNormal; // Same name as in EVisuPBR

  vec3    tc_gpu_mapping;
};

/*
struct commonIntermediateData {
  vec3 wo_trans;
  float f_trans_out;
};

commonIntermediateData g_XRiteCarPaint2_interm_data;
*/

#else

// DSPBR ----------------------------------------------------------------------

#ifdef EVisuPBR

struct BRDFParameters
{
  int   thinWalled;
  vec3  albedo;
  vec3  specularTint;
  float metallic;
  float specular;
  #ifdef SO_EVISUPBR_TRANSLUCENCY
    float translucency;
  #endif
  float transparency;
  float ior;
  float roughness;
  float anisotropy;
  float anisotropyRotation;
  vec3 attenuationColor;
  float attenuationDistance;
  float opacity;
  #ifdef SO_EVISUPBR_SHEEN
    #if defined(SO_EVISUPBR_ver19x) || defined(SO_EVISUPBR_ver21x)
      float sheen;
    #endif // SO_EVISUPBR_ver19x || SO_EVISUPBR_ver21x
    #if defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x)
      vec3  sheenColor;
      float sheenRoughness;
    #endif // SO_EVISUPBR_ver21x || SO_EVISUPBR_ver22x
  #endif // SO_EVISUPBR_SHEEN

  #ifdef SO_EVISUPBR_FLAKES
    float flakeCoverage;
    float flakeSize;
    float flakeRoughness;
    vec3  flakeColor;
    float flipFlop;
    vec3  flipFlopColor;
  #endif // SO_EVISUPBR_FLAKES

  #ifdef SO_EVISUPBR_CLEARCOAT
    float clearcoat;
    float clearcoatRoughness;
    vec3  clearcoatNormal;
  #endif // SO_EVISUPBR_CLEARCOAT

  #ifdef SO_EVISUPBR_SUBSURFACE
    float curvature;
  #endif // SO_EVISUPBR_SUBSURFACE

  vec3 emission;
};

#else // ----------------------------------------------------------------------

  // if not EVisuPBR

// BRDF Structure Definition
/*************************************************************************************************/

struct BRDFParameters
{
  //Diffuse BRDF
  vec3 albedo;
  float roughness;

  #ifdef Flakes
  float metallicFlakesRoughness;
  float metalRoughness;
  float pearlFlakesRoughness;
  float pearlRoughness;
  #endif

  #ifdef Coating
  float coatingRoughness;
  #endif

  //Specular BRDF
  vec3 f0; //Specular Reflectance, actually the specular color
  vec3 f90;
  #ifdef Flakes
  vec3 metallicFlakesF0;
  vec3 metalF0;
  vec3 pearlFlakesF0;
  vec3 pearlF0;
  #endif

  #ifdef Coating
  vec3 coatingF0;
  #endif

#ifdef AnisotropicDistribution
  float anisotropy;
  float anisotropyAngle;
#endif

  float transparency;

#ifdef PDSFX_ENABLE_BRDF_CONTROL
  float diffuseBRDFFactor;
  float specularBRDFFactor;
#endif

#ifdef PDSFX_ENABLE_IBL_CONTROL
  float diffuseIBLFactor;
  float specularIBLFactor;
#endif

#ifdef PDSFX_ENABLE_IBL_MIRROR_MAP
  vec2 iblMirrorMapCoords;
#endif

  float _unclampedRoughness;
};

#ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
  struct BRDFLayerParameters
  {
    int lightID;
    int lightType;
    vec3 fresnel;
    vec3 irradiance;
    float shadowTerm;
  };
#endif // PDSFX_ENABLE_CUSTOM_BRDF_LAYER

/*************************** Microfacet Distribution *********************************************/

// The Blinn Phong NDF comes from Globe
#ifdef PDSFX_ENABLE_BLINN_PHONG_NDF

float NormalDistribution(in float dot_N_H, in float roughness)
{
  float a = vMax(roughness, 0.0);
  float specExp = -10.0 / vLog2( (1.0 - a)*0.968 + 0.03 );
  specExp *= specExp;
  float phongNormalize = (specExp + 4.0)/(8.0*3.141592);
  return phongNormalize * vPow( vClamp( dot_N_H,0,1 ), specExp );
}

#else

float NormalDistribution(in float dot_N_H, in float roughness)
{
  #ifdef Fabrics
  float a2 = vMax(vPow4(roughness),kEpsilon);
  // cos^2
  float cosine = vMax(dot_N_H,kEpsilon);
  float cosine2 = vPow2(cosine);
  // sin^2
  float sine2 = vMax(1-cosine2,kEpsilon);

  //
  float D = 1;
  float normalisationTerm = INV_PI;
  #if defined(UseVelvet) || defined(UseSilkVelvet)
    normalisationTerm = 1/(1 + 8*a2) * INV_PI;
    // sin^4
    float sine4 = vMax(vPow2(sine2),kEpsilon);
    // cotan^2
    float cotan2 = vMax(cosine2/sine2,kEpsilon);
    float value = -cotan2 / a2;
    // result
    D = 1 + 8 * vExp(value)/ sine4;
  #endif // (defined(UseVelvet) || defined(UseSilkVelvet))
  #if defined(UseSatin)
    normalisationTerm = 1/(8*a2) * INV_PI;
    // cos^4
    float cosine4 = vMax(vPow2(cosine2),kEpsilon);
    // cotan^2
    float tan2 = vMax(sine2/cosine2,kEpsilon);
    float value = -tan2/vMax( a2*8,kEpsilon);
    // result
    D = vExp(value) / cosine4 ;
  #endif // (defined(UseSatin)

  return D * normalisationTerm;
  #else // GGX
    float a2 = vPow4(roughness);
    float D = vPow2(dot_N_H) * (a2 - 1.0) + 1.0;
    return a2 / (PI * vPow2(D));
  #endif
}

#endif // PDSFX_ENABLE_BLINN_PHONG_NDF

float AnisotropicGGXNormalDistribution(vec3 T, vec3 B, vec3 N, vec3 H, float dot_N_H, float iRoughness, float iAnisotropyAngle, float iAnisotropy)
{
  //T = getGeomTApprox(N);
  //B = getGeomBApprox(N,T);
  vec3  rot_X = vCos(iAnisotropyAngle *2. * PI) * T + vSin(iAnisotropyAngle * 2.* PI) * B;
  vec3  rot_Y = vCross(N, rot_X);

  float dot_t_h = vDot(rot_X, H); // sin(theta) cos(phi)
  float dot_b_h = vDot(rot_Y, H); // sin(theta) sin(phi)
  float alpha_T = vPow2(iRoughness);
  float alpha_B = vMix(0., alpha_T, 1. - iAnisotropy);

  alpha_T = vMax(alpha_T, kEpsilon);
  alpha_B = vMax(alpha_B, kEpsilon);
  float a = vPow2(dot_t_h / alpha_T);
  float b = vPow2(dot_b_h / alpha_B);
  float D = a + b + vPow2(dot_N_H);
  D = PI * alpha_T * alpha_B * vPow2(D);
  D = 1. / vMax(D, kEpsilon);
  return D;
}

/*************************** Geometric Attenuation ***********************************************/

float GeometricAttenuation(in float roughness, in float dot_N_L, in float dot_N_V) {
  #ifdef Fabrics
    return 1.0;
  #else
    float k = roughness * roughness * 0.5;
    float one_minus_k = 1.0 - k;
    float v = dot_N_V / (dot_N_V*one_minus_k+k);
    float l = dot_N_L / (dot_N_L*one_minus_k+k);
    return l*v;
  #endif
}

float UnrealVisibility(in float roughness, in float dot_N_L, in float dot_N_V)
{
  float Visib = GeometricAttenuation(roughness, vMax(dot_N_L,kEpsilon),vMax(dot_N_V,kEpsilon));
  #ifdef Fabrics
    float div = 4.0 * vMax(dot_N_L + dot_N_V - dot_N_L*dot_N_V, kEpsilon);
    return vClamp(Visib / div, 0.0, 5.0);
  #else
    float div = 4.0 *vMax(dot_N_L,kEpsilon) * vMax(dot_N_V,kEpsilon);
    return Visib / div;
  #endif
}

float CGX_V1(in float iAlpha2, in float dot_n_X)
{
  return 1.0/(dot_n_X+vSqrt(iAlpha2+(1.-iAlpha2)*vPow2(dot_n_X)));
}

float Visibility(in float a, in float dot_N_L, in float dot_N_V)
{
  return CGX_V1(a, dot_N_L) * CGX_V1(a, dot_N_V);
}

/*************************** Fresnel *************************************************************/

const float fresnel_exp0 = -5.55473;
const float fresnel_exp1 = -6.98316;

vec3 OptimizedSchlickFresnel(in vec3 iF0, in vec3 iF90, in float dot_L_H)
{
  float power = vPow(2.0, (vFma(fresnel_exp0, dot_L_H, fresnel_exp1)) * dot_L_H);
  return vMix(iF0,iF90,power);
}

vec2 OptimizedSchlickFresnel(in float dot_L_H)
{
  float power = vPow(2.0, (vFma(fresnel_exp0, dot_L_H, fresnel_exp1)) * dot_L_H);
  return vec2((1.0-power),power);
}

vec2 SchlickFresnel(in float dot_L_H) {
  float power = vPow5(1.0 - dot_L_H);
  return vec2((1.0-power),power);
}

#endif // EVisuPBR

#endif // XRiteCarPaint2

// Make it common for all materials
vec3 SchlickFresnel(in vec3 iF0, in vec3 iF90, in float dot_L_H) //C'est un schlick type
{
  float power = vPow5(1.0 - dot_L_H);
  return vMix(iF0, iF90, power);
}
