// shortcuts for some of the more commonly used UBO members
  
#define resX (uint(cb_PostEffect_HRTAO.resX))
#define resY (uint(cb_PostEffect_HRTAO.resY))

#ifdef IS_MSAA
  #define resZ (uint(IS_MSAA))
#else
  #define resZ (1u)
#endif

#define vpX (_sbCbCamera.EyeWorldPos.x)
#define vpY (_sbCbCamera.EyeWorldPos.y)
#define vpZ (_sbCbCamera.EyeWorldPos.z)

//These come from GL_EXT_shader_explicit_arithmetic_types
// but this extension is only supported by glslang it seems.
// We have to use this workaround for now
#define uint16BitsToHalf(a) float16_t(unpackHalf2x16(a).x)
#define halfBitsToUint16(a) (packHalf2x16(vec2(a)) & 0xFFFF)
#define uint16_t uint

float CIELuminance(vec3 rgb)
{
  return 0.2126 * rgb.r + 0.7152 * rgb.g + 0.0722 * rgb.b;
}

