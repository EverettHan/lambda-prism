
void main(void)
{
#ifdef TEXTURE_ARRAY_ID
  vec3 texCoord;
  texCoord.z = TEXTURE_ARRAY_ID;
#else
  vec2  texCoord;
#endif

  texCoord.xy = vTexCoord.xy;

#ifdef TransparentShadow
  vec4 fullShadow = vec4(0.0, 0.0, 0.0, 1.0);
#else
  vec4 fullShadow = vec4(1.0);
#endif
  vec4 noShadow   = vec4(0.0);

  float z   = vTexture(s_SourceTex, texCoord).x;
  vec4 col  = (z >= 0.999) ? noShadow : fullShadow;
  
  FRAGCOLOR = col;
}

