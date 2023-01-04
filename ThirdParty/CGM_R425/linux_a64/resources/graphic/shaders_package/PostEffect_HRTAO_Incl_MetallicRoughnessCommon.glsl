struct MaterialEval
{
  vec4  baseColor;
  float perceptualRoughness;
  float metallic;
  vec3  shadingNormal;
  vec3  shadingTangentU;
  vec3  shadingTangentV;
  vec3  emissive;
};

const float c_MinReflectance = 0.04;

float getPerceivedBrightness(vec3 vector)
{
  return sqrt(0.299 * vector.r * vector.r + 0.587 * vector.g * vector.g + 0.114 * vector.b * vector.b);
}


float solveMetallic(vec3 diffuse, vec3 specular, float oneMinusSpecularStrength)
{
  float specularBrightness = getPerceivedBrightness(specular);

  if(specularBrightness < c_MinReflectance)
  {
    return 0.0;
  }

  float diffuseBrightness = getPerceivedBrightness(diffuse);

  float a = c_MinReflectance;
  float b = diffuseBrightness * oneMinusSpecularStrength / (1.0 - c_MinReflectance) + specularBrightness - 2.0 * c_MinReflectance;
  float c = c_MinReflectance - specularBrightness;
  float D = b * b - 4.0 * a * c;

  return clamp((-b + sqrt(D)) / (2.0 * a), 0.0, 1.0);
}

#ifdef OutputMaterialEval
  void encodeMaterialEval(MaterialEval m, out uvec4 v1, out uvec4 v2)
  {
    f16vec4 baseColor         = f16vec4(m.baseColor);
    f16vec2 roughnessMetallic = f16vec2(m.perceptualRoughness, m.metallic);
    uint    shadingNormal     = compress_unit_vec(m.shadingNormal);

    uint      shadingTangentU    = compress_unit_vec(m.shadingTangentU);
    float16_t shadingTangentSign = float16_t(sign(dot(m.shadingTangentV, cross(m.shadingNormal, m.shadingTangentU))));
    f16vec3   emissive           = f16vec3(m.emissive);


    v1.x = packHalf2x16(baseColor.xy);
    v1.y = packHalf2x16(baseColor.zw);
    v1.z = packHalf2x16(roughnessMetallic);
    v1.w = shadingNormal;

    v2.x = shadingTangentU;
    v2.y = packHalf2x16(f16vec2(shadingTangentSign, emissive.x));
    v2.z = packHalf2x16(emissive.yz);
  }
#endif

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  MaterialEval decodeMaterialEval(uvec4 v1, uvec4 v2)
  {
    MaterialEval m;
 
    // v1.x <- baseColor.r(float16) & baseColor.g(float16)
    // v1.y <- baseColor.b(float16) & baseColor.a(float16)
    // v1.z <- roughness(float16) & metallic(float16)
    // v1.w <- shadingNormal(uint32)
  
    // v2.x <- shadingTangentU(uint32)
    // v2.y <- tangentSign(float16) & emissive.r(float16)
    // v2.z <- emissive.g(float16) & emissive.b(float16)

    m.baseColor.xy         = unpackFloat2x16(v1.x);
    m.baseColor.zw         = unpackFloat2x16(v1.y);
    vec2 roughnessMetallic = unpackFloat2x16(v1.z);
    m.perceptualRoughness  = roughnessMetallic.x;
    m.metallic             = roughnessMetallic.y;
    m.shadingNormal        = decompress_unit_vec(v1.w);

    m.shadingTangentU = decompress_unit_vec(v2.x);

    vec2 tangentSignEmissiveX = unpackFloat2x16(v2.y);
    m.shadingTangentV         = tangentSignEmissiveX.x * cross(m.shadingNormal, m.shadingTangentU);
    m.emissive.x              = tangentSignEmissiveX.x;
    m.emissive.yz             = unpackFloat2x16(v2.z);

    return m;
  }
#endif
