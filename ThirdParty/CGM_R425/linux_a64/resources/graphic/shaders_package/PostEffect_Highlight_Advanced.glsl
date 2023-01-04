
vec3 hsv2rgb(vec3 c)
{
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 rgb2hsv(vec3 c)
{
  vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
  vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
  vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

  float d = q.x - min(q.w, q.y);
  float e = 1.0e-10;
  return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec4 ScanEffectAndOutline(const vec4	iColor)
{
  vec4 result = iColor;

  float outline = 0.0;
  outline += vFloor(vTextureOffset(s_EyeMap, vTexCoord, ivec2( 0, -1)).a);
  outline += vFloor(vTextureOffset(s_EyeMap, vTexCoord, ivec2( 0,  1)).a);
  outline += vFloor(vTextureOffset(s_EyeMap, vTexCoord, ivec2(-1,  0)).a);
  outline += vFloor(vTextureOffset(s_EyeMap, vTexCoord, ivec2( 1,  0)).a);

  // Outline 
  if (outline != 0)
  {
#if defined MultiColorHighlight
    // outline color is automaticaly computed from highlight color
    vec3 hsv = rgb2hsv(result.xyz);
    hsv.z = 100;

    result = vec4(hsv2rgb(hsv), 1.0);
#else
    result = cb_PostEffect_Highlight_Advanced.u_OutlineColor;
#endif
  }
  // Scan effect
  else
  {
#if defined MultiColorHighlight
    // scan effect color is automaticaly computed from highlight color
    vec3 hsv = rgb2hsv(result.xyz);
    hsv.z = hsv.z * 0.90;

    result.xyz = hsv2rgb(hsv);
#endif

    result.a = 1 - result.a;
    result.a *= result.a;
    result.a = (0.6*result.a + 0.2)*cb_PostEffect_Highlight_Advanced.u_ScanEffectIntensity;
  }

  return result;
}


void main()
{
  vec4 result = GetColor(vTexCoord);

  // Halo
  if ((result.a) == 1)
  {
#ifdef MULTIPASS
    result = ComputeHalo(s_HaloTex);
#else
    result = ComputeFirstPassHalo(s_EyeMap);
#endif

#ifdef MultiColorHighlight
    vec3 hsv = rgb2hsv(result.xyz);
    hsv.z = hsv.z * 0.80;

    result.xyz = hsv2rgb(hsv);
#else
    result.xyz = cb_PostEffect_Highlight_Advanced.u_HaloColor.xyz;
#endif

    result.a = (1 - result.a)*cb_PostEffect_Highlight_Advanced.u_HaloIntensity;
  }
  // Highlighted Object itslef
  else
  {
    // to manage totally opaque objects
    // transparency is mapped under 0/0.9
    // we habe to unmap to retrieve the right transparency value
    result.a /= 0.9;

    result = ScanEffectAndOutline(result);
  }

  FRAGCOLOR = result;
}
