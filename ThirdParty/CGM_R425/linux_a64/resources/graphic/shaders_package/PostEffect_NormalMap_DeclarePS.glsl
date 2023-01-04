bool IsBackground(const vec2 iCoord)
{  
  vec4 n = GetEffectTexture(s_NormalMap, iCoord);
  return (n.w!=1.f ? true : false);
}

bool IsBackground(const vec2 iCoord, const vec2 iPixelOffset)
{ 
  vec4 n = GetEffectTexture(s_NormalMap, iCoord, iPixelOffset);
  return (n.w!=1.f ? true : false);
}

vec4 GetNormal(const vec2 iCoord)
{
  vec4 n = GetEffectTexture(s_NormalMap, iCoord);
  n.xyz = vFma(n.xyz, vec3(2.0), vec3(-1.0));
  return n;
}

vec4 GetNormal(const vec2 iCoord, const vec2 iPixelOffset)
{
  vec4 n = GetEffectTexture(s_NormalMap, iCoord, iPixelOffset);
  n.xyz = vFma(n.xyz, vec3(2.0), vec3(-1.0));
  return n;
}
