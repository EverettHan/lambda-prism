
void main(void)
{
#ifdef TEXTURE_ARRAY_SLICE
  vec3 texCoord;
  texCoord.z = TEXTURE_ARRAY_SLICE;
#else
  vec2  texCoord;
#endif
 
  texCoord.xy = vTexCoord.xy*cb_PostEffect.u_Scale.xy + cb_PostEffect.u_Translate.xy;

  FRAGCOLOR = vTexture(s_EyeMap, texCoord);
}

