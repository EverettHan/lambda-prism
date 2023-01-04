
vec4 GetColor(const vec2 iCoord, const vec2 iPixelOffset)
{
  vec4 col = vec4(0);
#ifndef TEXTURE_ARRAY
  col = GetEffectTexture(s_EyeMap, iCoord, iPixelOffset);
#else
  col = GetEffectTexture(s_EyeMap, vec3(iCoord, TEXTURE_ARRAY_SLICE), iPixelOffset);
#endif

#ifndef GLES2Platform
#ifdef CHECK_NAN 
    if(isnan(col.x))
    {
      col = vec4(0);
    }
#endif
#endif

  return col;
}

vec4 GetColor(const vec2 iCoord)
{
  vec4 col = vec4(0);
#ifndef TEXTURE_ARRAY
  col = GetEffectTexture(s_EyeMap, iCoord);
#else
  col = GetEffectTexture(s_EyeMap, vec3(iCoord, TEXTURE_ARRAY_SLICE) );
#endif
    
#ifndef GLES2Platform
#ifdef CHECK_NAN 
   if(isnan(col.x))
    {
      col = vec4(0);
    }
#endif
#endif

  return col;
}

