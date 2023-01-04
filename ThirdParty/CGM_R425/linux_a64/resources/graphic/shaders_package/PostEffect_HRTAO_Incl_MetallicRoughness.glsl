/*
* Copyright (c) 2017-2022, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#ifndef METALLIC_ROUGHNESS
#define METALLIC_ROUGHNESS

// GLTF material
#define MATERIAL_METALLICROUGHNESS 0
#define MATERIAL_SPECULARGLOSSINESS 1
#define ALPHA_OPAQUE 0
#define ALPHA_MASK 1
#define ALPHA_BLEND 2

#ifndef M_1_PI
#define M_1_PI 0.318309886183790671538  // 1/pi
#endif

#ifndef M_PI
#define M_PI 3.14159862f
#endif

//#ifdef __cplusplus
//// GLSL Type
//using ivec2 = nvmath::vec2i;
//using vec2  = nvmath::vec2;
//using vec3  = nvmath::vec3;
//using vec4  = nvmath::vec4;
//using mat4  = nvmath::mat4;
//using uint  = unsigned int;
//#endif
struct GltfShadeMaterial
{
  int shadingModel;  // 0: metallic-roughness, 1: specular-glossiness

  // PbrMetallicRoughness
  vec4  pbrBaseColorFactor;
  int   pbrBaseColorTexture;
  float pbrMetallicFactor;
  float pbrRoughnessFactor;
  int   pbrMetallicRoughnessTexture;

  // KHR_materials_pbrSpecularGlossiness
  vec4  khrDiffuseFactor;
  int   khrDiffuseTexture;
  vec3  khrSpecularFactor;
  float khrGlossinessFactor;
  int   khrSpecularGlossinessTexture;

  int   emissiveTexture;
  vec3  emissiveFactor;
  int   alphaMode;
  float alphaCutoff;
  int   doubleSided;

  int   normalTexture;
  float normalTextureScale;
  int   occlusionTexture;
  float occlusionTextureStrength;
};


#ifndef __cplusplus

#define C_Stack_Max 3.402823466e+38f
uint compressUnitVector(vec3 nv)
{
  // map to octahedron and then flatten to 2D (see 'Octahedron Environment Maps' by Engelhardt & Dachsbacher)
  if((nv.x < C_Stack_Max) && !isinf(nv.x))
  {
    const float d = 32767.0f / (abs(nv.x) + abs(nv.y) + abs(nv.z));
    int         x = int(roundEven(nv.x * d));
    int         y = int(roundEven(nv.y * d));

    if(nv.z < 0.0f)
    {
      const int maskx = x >> 31;
      const int masky = y >> 31;
      const int tmp   = 32767 + maskx + masky;
      const int tmpx  = x;
      x               = (tmp - (y ^ masky)) ^ maskx;
      y               = (tmp - (tmpx ^ maskx)) ^ masky;
    }

    uint packed = (uint(y + 32767) << 16) | uint(x + 32767);
    if(packed == ~0u)
      return ~0x1u;
    return packed;
  }
  else
  {
    return ~0u;
  }
}


vec3 decompressUnitVector(uint packed)
{
  if(packed != ~0u)  // sanity check, not needed as isvalid_unit_vec is called earlier
  {
    int x = int(packed & 0xFFFFu) - 32767;
    int y = int(packed >> 16) - 32767;

    const int maskx = x >> 31;
    const int masky = y >> 31;
    const int tmp0  = 32767 + maskx + masky;
    const int ymask = y ^ masky;
    const int tmp1  = tmp0 - (x ^ maskx);
    const int z     = tmp1 - ymask;
    float     zf;
    if(z < 0)
    {
      x  = (tmp0 - ymask) ^ maskx;
      y  = tmp1 ^ masky;
      zf = uintBitsToFloat((0x80000000u | 0x3F800000u) | (uint(-z) << 8)) + 1.0f;
    }
    else
    {
      zf = uintBitsToFloat(0x3F800000u | (uint(z) << 8)) - 1.0f;
    }

    return normalize(vec3(short_to_floatm11(x), short_to_floatm11(y), zf));
  }
  else
  {
    return vec3(C_Stack_Max);
  }
}

// Return the tangent and binormal from the incoming normal
void createCoordinateSystem(in vec3 N, out vec3 Nt, out vec3 Nb)
{
  if(abs(N.x) > abs(N.y))
    Nt = vec3(N.z, 0, -N.x) / sqrt(N.x * N.x + N.z * N.z);
  else
    Nt = vec3(0, -N.z, N.y) / sqrt(N.y * N.y + N.z * N.z);
  Nb = cross(N, Nt);
}

//-----------------------------------------------------------------------
vec3 cosineSampleHemisphere(float u1, float u2)
{
  vec3  dir;
  float r   = sqrt(u1);
  float phi = 2.0 * M_PI * u2;
  dir.x     = r * cos(phi);
  dir.y     = r * sin(phi);
  dir.z     = sqrt(max(0.0, 1.0 - dir.x * dir.x - dir.y * dir.y));

  return dir;
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Specular-Glossiness converter
// See: // https://github.com/KhronosGroup/glTF/blob/master/extensions/2.0/Khronos/KHR_materials_pbrSpecularGlossiness/examples/convert-between-workflows/js/three.pbrUtilities.js#L34
//-------------------------------------------------------------------------------------------------

// Basic Lambertian diffuse
// Implementation from Lambert's Photometria https://archive.org/details/lambertsphotome00lambgoog
// See also [1], Equation 1
vec3 diffuse(vec3 diffuseColor)
{
  return diffuseColor * M_1_PI;
}


// Smith Joint GGX
// Note: Vis = G / (4 * NdotL * NdotV)
// see Eric Heitz. 2014. Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs. Journal of Computer Graphics Techniques, 3
// see Real-Time Rendering. Page 331 to 336.
// see https://google.github.io/filament/Filament.md.html#materialsystem/specularbrdf/geometricshadowing(specularg)
float geometricOcclusion(float NdotL, float NdotV, float alphaRoughness)
{
  float alphaRoughnessSq = alphaRoughness * alphaRoughness;

  float GGXV = NdotL * sqrt(NdotV * NdotV * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);
  float GGXL = NdotV * sqrt(NdotL * NdotL * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);

  float GGX = GGXV + GGXL;
  if(GGX > 0.0)
  {
    return 0.5 / GGX;
  }
  return 0.0;
}


// The following equation models the Fresnel reflectance term of the spec equation (aka F())
// Implementation of fresnel from [4], Equation 15
vec3 specularReflection(vec3 reflectance0, vec3 reflectance90, float VdotH)
{
  return reflectance0 + (reflectance90 - reflectance0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}


// The following equation(s) model the distribution of microfacet normals across the area being drawn (aka D())
// Implementation from "Average Irregularity Representation of a Roughened Surface for Ray Reflection" by T. S. Trowbridge, and K. P. Reitz
// Follows the distribution function recommended in the SIGGRAPH 2013 course notes from EPIC Games [1], Equation 3.
float microfacetDistribution(float NdotH, float alphaRoughness)
{
  float alphaRoughnessSq = alphaRoughness * alphaRoughness;
  float f                = (NdotH * NdotH) * (alphaRoughnessSq - 1.0) + 1.0;

  return alphaRoughnessSq / (M_PI * f * f);
}

// The following equation models the Fresnel reflectance term of the spec equation (aka F())
// Implementation of fresnel from [4], Equation 15
vec3 F_Schlick(vec3 f0, vec3 f90, float VdotH)
{
  return f0 + (f90 - f0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}

// Smith Joint GGX
// Note: Vis = G / (4 * NdotL * NdotV)
// see Eric Heitz. 2014. Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs. Journal of Computer Graphics Techniques, 3
// see Real-Time Rendering. Page 331 to 336.
// see https://google.github.io/filament/Filament.md.html#materialsystem/specularbrdf/geometricshadowing(specularg)
float V_GGX(float NdotL, float NdotV, float alphaRoughness)
{
  float alphaRoughnessSq = alphaRoughness * alphaRoughness;

  float GGXV = NdotL * sqrt(NdotV * NdotV * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);
  float GGXL = NdotV * sqrt(NdotL * NdotL * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);

  float GGX = GGXV + GGXL;
  if(GGX > 0.0)
  {
    return 0.5 / GGX;
  }
  return 0.0;
}

// The following equation(s) model the distribution of microfacet normals across the area being drawn (aka D())
// Implementation from "Average Irregularity Representation of a Roughened Surface for Ray Reflection" by T. S. Trowbridge, and K. P. Reitz
// Follows the distribution function recommended in the SIGGRAPH 2013 course notes from EPIC Games [1], Equation 3.
float D_GGX(float NdotH, float alphaRoughness)
{
  float alphaRoughnessSq = alphaRoughness * alphaRoughness;
  float f                = (NdotH * NdotH) * (alphaRoughnessSq - 1.0) + 1.0;
  return alphaRoughnessSq / (M_PI * f * f);
}


//https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#acknowledgments AppendixB
vec3 BRDF_lambertian(vec3 f0, vec3 f90, vec3 diffuseColor, float VdotH, float metallic, vec3 F)
{
  // see https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/
  //  return (1.0 - F_Schlick(f0, f90, VdotH)) * (diffuseColor / M_PI);

  vec3 c_diff = (1.0 - metallic) * diffuseColor;
  return (vec3(1.0) - F) * (1.0 / M_PI) * c_diff;
}

//  https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#acknowledgments AppendixB
vec3 BRDF_specularGGX(vec3 f0, vec3 f90, float alphaRoughness, float VdotH, float NdotL, float NdotV, float NdotH)
{
  vec3  F   = F_Schlick(f0, f90, VdotH);
  float Vis = V_GGX(NdotL, NdotV, alphaRoughness);
  float D   = D_GGX(NdotH, max(0.001, alphaRoughness));

  return F * Vis * D;
}

//-----------------------------------------------------------------------
float BsdfPdf(in vec3 rayDirection, MaterialEval state, in vec3 bsdfDir)
{
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;
  vec3 L = bsdfDir;

  float specularAlpha = max(0.001, state.perceptualRoughness);

  float diffuseRatio  = 0.5 * (1.0 - state.metallic);
  float specularRatio = 1.0 - diffuseRatio;

  vec3  H     = normalize(L + V);
  float NdotH = clamp(dot(N, H), 0.0, 1);
  float LdotH = clamp(dot(L, H), 0.0, 1);
  float NdotL = clamp(dot(N, L), 0.0, 1);

  //float cosTheta = abs(dot(H, N));
  float pdfDs = D_GGX(NdotH, specularAlpha) * NdotH;

  // calculate diffuse and specular pdfs and mix ratio

  float pdfSpec = pdfDs / (4.0 * LdotH);
  float pdfDiff = NdotL * M_1_PI;

  // weight pdfs according to ratios
  return diffuseRatio * pdfDiff + specularRatio * pdfSpec;
}

float BsdfPdfSpecular(in vec3 rayDirection, MaterialEval state, in vec3 bsdfDir)
{
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;
  vec3 L = bsdfDir;

  float specularAlpha = max(0.001, state.perceptualRoughness);

  float diffuseRatio  = 0.5 * (1.0 - state.metallic);
  float specularRatio = 1.0 - diffuseRatio;

  vec3  H     = normalize(L + V);
  float NdotH = clamp(dot(N, H), 0.0, 1);
  float LdotH = clamp(dot(L, H), 0.0, 1);
  float NdotL = clamp(dot(N, L), 0.0, 1);

  //float cosTheta = abs(dot(H, N));
  float pdfDs = D_GGX(NdotH, specularAlpha) * NdotH;

  // calculate diffuse and specular pdfs and mix ratio

  float pdfSpec = pdfDs / (4.0 * LdotH);
  float pdfDiff = NdotL * M_1_PI;

  // weight pdfs according to ratios
  return pdfSpec;
}


//-----------------------------------------------------------------------
vec3 BsdfSample(in vec3 rayDirection, in vec3 sampleValue, in MaterialEval state)
{
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;

  vec3 dir;

  float probability  = sampleValue.x;
  float diffuseRatio = 0.5 * (1.0 - state.metallic);

  float r1 = sampleValue.y;
  float r2 = sampleValue.z;

  vec3 tangent_u = state.shadingTangentU;
  vec3 tangent_v = state.shadingTangentV;

  createCoordinateSystem(N, tangent_u, tangent_v);

  if(probability < diffuseRatio)  // sample diffuse
  //if(true)
  {
    dir = cosineSampleHemisphere(r1, r2);
    dir = tangent_u * dir.x + tangent_v * dir.y + N * dir.z;
  }
  else
  {
    float specularAlpha = max(0.001, state.perceptualRoughness);

    float phi = r1 * 2.0 * M_PI;

    float cosTheta = sqrt((1.0 - r2) / (1.0 + (specularAlpha * specularAlpha - 1.0) * r2));
    float sinTheta = clamp(sqrt(1.0 - (cosTheta * cosTheta)), 0.0, 1.0);
    float sinPhi   = sin(phi);
    float cosPhi   = cos(phi);

    vec3 halfVec = vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
    halfVec      = tangent_u * halfVec.x + tangent_v * halfVec.y + N * halfVec.z;

    dir = 2.0 * dot(V, halfVec) * halfVec - V;
  }
  return dir;
}

vec3 BsdfSampleSpecular(in vec3 rayDirection, in vec3 sampleValue, in MaterialEval state)
{
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;

  vec3 dir;

  float probability  = sampleValue.x;
  float diffuseRatio = 0.5 * (1.0 - state.metallic);

  float r1 = sampleValue.y;
  float r2 = sampleValue.z;

  vec3 tangent_u = state.shadingTangentU;
  vec3 tangent_v = state.shadingTangentV;

  createCoordinateSystem(N, tangent_u, tangent_v);

  //if(probability < diffuseRatio)  // sample diffuse
  ////if(true)
  //{
  //  dir = cosineSampleHemisphere(r1, r2);
  //  dir = tangent_u * dir.x + tangent_v * dir.y + N * dir.z;
  //}
  //else
  {
    float specularAlpha = max(0.001, state.perceptualRoughness);

    float phi = r1 * 2.0 * M_PI;

    float cosTheta = sqrt((1.0 - r2) / (1.0 + (specularAlpha * specularAlpha - 1.0) * r2));
    float sinTheta = clamp(sqrt(1.0 - (cosTheta * cosTheta)), 0.0, 1.0);
    float sinPhi   = sin(phi);
    float cosPhi   = cos(phi);

    vec3 halfVec = vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
    halfVec      = tangent_u * halfVec.x + tangent_v * halfVec.y + N * halfVec.z;

    dir = 2.0 * dot(V, halfVec) * halfVec - V;
  }
  return dir;
}


//-----------------------------------------------------------------------
vec3 BsdfEval(in vec3 rayDirection, in MaterialEval state, in vec3 bsdfDir)
{
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;
  vec3 L = bsdfDir;

  float NdotL = dot(N, L);
  float NdotV = dot(N, V);

  if(NdotL <= 0.0 || NdotV <= 0.0)
    return vec3(0.0);
  
  NdotL = clamp(NdotL, 0.001, 1.0);
  NdotV = clamp(abs(NdotV), 0.001, 1.0);

  vec3  H     = normalize(L + V);
  float NdotH = clamp(dot(N, H), 0, 1);
  float LdotH = clamp(dot(L, H), 0, 1);
  float VdotH = clamp(dot(V, H), 0.0, 1.0);

  // specular
  vec3 specularCol = mix(vec3(0.04), state.baseColor.xyz, state.metallic);

  // Compute reflectance.
  // Anything less than 2% is physically impossible and is instead considered to be shadowing. Compare to "Real-Time-Rendering" 4th edition on page 325.
  float reflectance = max(max(specularCol.r, specularCol.g), specularCol.b);
  vec3  f0          = specularCol.rgb;
  vec3  f90         = vec3(1.0);//vec3(clamp(reflectance * 50.0, 0.0, 1.0));

  vec3 F = F_Schlick(f0, f90, VdotH);

  // Calculation of analytical lighting contribution
  vec3 diffuseContrib = BRDF_lambertian(f0, f90, state.baseColor.xyz, VdotH, state.metallic, F);
  vec3 specContrib    = BRDF_specularGGX(f0, f90, state.perceptualRoughness, VdotH, NdotL, NdotV, NdotH);

  return diffuseContrib + specContrib;
}

//-----------------------------------------------------------------------
void BsdfEvalSeparate(in vec3 rayDirection, in MaterialEval state, in vec3 bsdfDir, out vec3 diffuseContrib, out vec3 specContrib)
{
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;
  vec3 L = bsdfDir;

  
  float NdotL = clamp(dot(N, L), 0.001, 1.0);
  float NdotV = clamp(abs(dot(N, V)), 0.001, 1.0);


  vec3  H     = normalize(L + V);
  float NdotH = clamp(dot(N, H), 0.0, 1.0);
  float LdotH = clamp(dot(L, H), 0.0, 1.0);
  float VdotH = clamp(dot(V, H), 0.0, 1.0);

  // specular
  vec3 specularCol = mix(vec3(0.04), state.baseColor.xyz, state.metallic);
  //vec3 specularCol = mix(vec3(0.0), state.baseColor.xyz, state.metallic);

  // Compute reflectance.
  // Anything less than 2% is physically impossible and is instead considered to be shadowing. Compare to "Real-Time-Rendering" 4th edition on page 325.
  //float reflectance = max(max(specularCol.r, specularCol.g), specularCol.b);
  vec3  f0          = specularCol.rgb;
  vec3  f90         = vec3(1.0);//vec3(clamp(reflectance * 50.0, 0.0, 1.0));
  
  vec3 F = F_Schlick(f0, f90, VdotH);

  // Calculation of analytical lighting contribution
  diffuseContrib = BRDF_lambertian(f0, f90, state.baseColor.xyz, VdotH, state.metallic, F);
  specContrib    = BRDF_specularGGX(f0, f90, state.perceptualRoughness, VdotH, NdotL, NdotV, NdotH);
}


//-----------------------------------------------------------------------
vec3 BsdfEvalDiffuseOnly(in vec3 rayDirection, in MaterialEval state, in vec3 bsdfDir)
{
  vec3 diffuseContrib;
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;
  vec3 L = bsdfDir;

  float NdotL = dot(N, L);
  float NdotV = dot(N, V);

  if(NdotL <= 0.0 || NdotV <= 0.0)
    return vec3(0.0f);
  
  NdotL = clamp(NdotL, 0.001, 1.0);
  NdotV = clamp(abs(NdotV), 0.001, 1.0);

  vec3  H     = normalize(L + V);
  float NdotH = clamp(dot(N, H), 0, 1);
  float LdotH = clamp(dot(L, H), 0, 1);
  float VdotH = clamp(dot(V, H), 0.0, 1.0);

  // specular
  vec3 specularCol = mix(vec3(0.04), state.baseColor.xyz, state.metallic);

  // Compute reflectance.
  // Anything less than 2% is physically impossible and is instead considered to be shadowing. Compare to "Real-Time-Rendering" 4th editon on page 325.
  float reflectance = max(max(specularCol.r, specularCol.g), specularCol.b);
  vec3  f0          = specularCol.rgb;
  vec3  f90         = vec3(1.0);//vec3(clamp(reflectance * 50.0, 0.0, 1.0));
  
  vec3 F = F_Schlick(f0, f90, VdotH);

  // Calculation of analytical lighting contribution
  diffuseContrib = BRDF_lambertian(f0, f90, state.baseColor.xyz, VdotH, state.metallic, F);
  return diffuseContrib;
}

//-----------------------------------------------------------------------
vec3 BsdfEvalSpecularOnly(in vec3 rayDirection, in MaterialEval state, in vec3 bsdfDir)
{
  vec3 specContrib;
  vec3 N = state.shadingNormal;
  vec3 V = -rayDirection;
  vec3 L = bsdfDir;

  float NdotL = dot(N, L);
  float NdotV = dot(N, V);

  if(NdotL <= 0.0 || NdotV <= 0.0)
    return vec3(0.0f);
  
  NdotL = clamp(NdotL, 0.001, 1.0);
  NdotV = clamp(abs(NdotV), 0.001, 1.0);

  vec3  H     = normalize(L + V);
  float NdotH = clamp(dot(N, H), 0, 1);
  float LdotH = clamp(dot(L, H), 0, 1);
  float VdotH = clamp(dot(V, H), 0.0, 1.0);

  // specular
  vec3 specularCol = mix(vec3(0.04), state.baseColor.xyz, state.metallic);

  // Compute reflectance.
  // Anything less than 2% is physically impossible and is instead considered to be shadowing. Compare to "Real-Time-Rendering" 4th editon on page 325.
  float reflectance = max(max(specularCol.r, specularCol.g), specularCol.b);
  vec3  f0          = specularCol.rgb;
  vec3  f90         = vec3(1.0);//vec3(clamp(reflectance * 50.0, 0.0, 1.0));


  // Calculation of analytical lighting contribution
  specContrib = BRDF_specularGGX(f0, f90, state.perceptualRoughness, VdotH, NdotL, NdotV, NdotH);
  //specContrib = BRDF_specularGGX(f0, f90, 0.f, VdotH, NdotL, NdotV, NdotH);
  return specContrib;
}


// sRGB to linear approximation
// see http://chilliant.blogspot.com/2012/08/srgb-approximations-for-hlsl.html
vec4 SRGBtoLINEAR22(vec4 srgbIn)
{
  float gamma = 2.2;
  return vec4(pow(srgbIn.xyz, vec3(gamma)), srgbIn.w);
}


#ifdef GLTF_TEXTURE_ARRAY_NAME

MaterialEval evaluateMaterial(GltfShadeMaterial material, vec3 geometricNormal, vec3 tangent_u, vec3 tangent_v, vec2 uv)
{
  // Metallic and Roughness material properties are packed together
  // In glTF, these factors can be specified by fixed scalar values
  // or from a metallic-roughness map
  MaterialEval res;
  res.perceptualRoughness = 0.0;
  res.metallic            = 0.0;
  res.baseColor           = vec4(0.0, 0.0, 0.0, 1.0);


  // Normal Map
  if(material.normalTexture > -1)
  {
    mat3 TBN = mat3(tangent_u, tangent_v, geometricNormal);
    vec3 normalVector = texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.normalTexture)], uv).xyz * material.normalTextureScale;
    normalVector      = normalize(normalVector * 2.0 - 1.0);
    res.shadingNormal = normalize(TBN * normalVector);
  }
  else
    res.shadingNormal = geometricNormal;

  // Retrieve the diffuse and specular color base on the shading model: Metal-Roughness or Specular-Glossiness
  if(material.shadingModel == MATERIAL_METALLICROUGHNESS)
  {
    // Metallic and Roughness material properties are packed together
    // In glTF, these factors can be specified by fixed scalar values
    // or from a metallic-roughness map
    res.perceptualRoughness = material.pbrRoughnessFactor;
    res.metallic            = material.pbrMetallicFactor;
    if(material.pbrMetallicRoughnessTexture > -1)
    {
      // Roughness is stored in the 'g' channel, metallic is stored in the 'b' channel.
      // This layout intentionally reserves the 'r' channel for (optional) occlusion map data
      vec4 mrSample = texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.pbrMetallicRoughnessTexture)], uv);
      res.perceptualRoughness = mrSample.g * res.perceptualRoughness;
      res.metallic            = mrSample.b * res.metallic;
    }
    else
    {
      res.perceptualRoughness = clamp(res.perceptualRoughness, c_MinReflectance, 1.0);
      res.metallic            = clamp(res.metallic, 0.0, 1.0);
    }

    // The albedo may be defined from a base texture or a flat color
    res.baseColor = material.pbrBaseColorFactor;
    if(material.pbrBaseColorTexture > -1)
    {
      res.baseColor *= SRGBtoLINEAR22(texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.pbrBaseColorTexture)], uv));
    }
  }


  // Specular-Glossiness which will be converted to metallic-roughness
  if(material.shadingModel == MATERIAL_SPECULARGLOSSINESS)
  {
    // Values from specular glossiness workflow are converted to metallic roughness
    if(material.khrSpecularGlossinessTexture > -1)
    {
      res.perceptualRoughness =
          1.0 - texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.khrSpecularGlossinessTexture)], uv).a;
    }
    else
    {
      res.perceptualRoughness = 0.0;
    }

    const float epsilon = 1e-6;

    vec4 diffuse = SRGBtoLINEAR22(texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.khrDiffuseTexture)], uv));
    vec3 specular =
        SRGBtoLINEAR22(texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.khrSpecularGlossinessTexture)], uv)).rgb;

    float maxSpecular = max(max(specular.r, specular.g), specular.b);

    // Convert metallic value from specular glossiness inputs
    res.metallic = solveMetallic(diffuse.rgb, specular, maxSpecular);

    vec3 baseColorDiffusePart = diffuse.rgb * ((1.0 - maxSpecular) / (1 - c_MinReflectance) / max(1 - res.metallic, epsilon))
                                * material.khrDiffuseFactor.rgb;
    vec3 baseColorSpecularPart =
        specular
        - (vec3(c_MinReflectance) * (1 - res.metallic) * (1 / max(res.metallic, epsilon))) * material.khrSpecularFactor.rgb;
    res.baseColor = vec4(mix(baseColorDiffusePart, baseColorSpecularPart, res.metallic * res.metallic), diffuse.a);
  }


  // Emissive term
  vec3 emissive = material.emissiveFactor;
  if(material.emissiveTexture > -1)
    emissive *= SRGBtoLINEAR22(texture(GLTF_TEXTURE_ARRAY_NAME[nonuniformEXT(material.emissiveTexture)], uv)).rgb;
  res.emissive = emissive;

  res.shadingTangentU = tangent_u;
  res.shadingTangentV = tangent_v;

  return res;
}
#endif  //GLTF_TEXTURE_ARRAY_NAME

#endif  // !__cplusplus

#endif  // METALLIC_ROUGHNESS
