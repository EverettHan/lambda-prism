
void main(void)
{
#ifdef TEXTURE_ARRAY_ID
  vec3 texCoord;
  texCoord.z = TEXTURE_ARRAY_ID;
#else
  vec2  texCoord;
#endif

  texCoord.xy = vTexCoord.xy;

  vec4 col = vTexture(s_SourceTex, texCoord);
  if (col.w > 0)
  {
    col.xyz -= (1.0 - col.w);
    col.xyz *= (1.0 - col.w) / col.w;
  }
  else
  {
    col.xyz = vec3(0);
  }
  
  FRAGCOLOR = col;
}

