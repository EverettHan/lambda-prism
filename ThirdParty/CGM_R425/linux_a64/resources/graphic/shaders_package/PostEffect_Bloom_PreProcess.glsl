
vec4 WeightedAverageColor(const ivec2 iOffset)
{
#if !defined(GLES2Platform) && !defined(AMD) && !defined(MESA_SW)
  vec4 col = vTextureOffset(s_EyeMap, vTexCoord, iOffset);
#else
  vec2 coord = vTexCoord + iOffset * cb_PostEffectAuto.u_PixelSize;
  vec4 col = vTexture(s_EyeMap, coord);
#endif

  col = vec4(col.xyz, 1.0);
  
  float luminance = GetLuminance(col.xyz); //Max(col.x, vMax(col.y, col.z));
  col *= 1.0/(1.0+luminance);
  return col;
}

void main(void)
{   
  vec4 col = vec4(0,0,0,0);

#ifdef FILTER_FIREFLY
  col += WeightedAverageColor(ivec2(0, 0));
  col += WeightedAverageColor(ivec2(1, 0));
  col += WeightedAverageColor(ivec2(1, 1));
  col += WeightedAverageColor(ivec2(0, 1));

  col.xyz /= col.w;
#else
  col = vTexture(s_EyeMap, vTexCoord);
#endif

#ifdef LIGHTINTESITY_THRESHOLD
	float luminance = GetLuminance(col.xyz);
  if (luminance<cb_Bloom.u_LightIntensityThreshold) col = vec4(0);
#endif

#ifdef CHECK_NAN 
  if(isnan(col.x))
  {
    col = vec4(0);
  }
#endif

  FRAGCOLOR = col;
}
