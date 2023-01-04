void main()
{
  float zWithTransp = GetZ(vTexCoord.xy);
  float zNoTransp = GetEffectTexture(ZMapOpaque, vTexCoord.xy).x;

  if (zWithTransp > 0.999 && zNoTransp > 0.999)
  {
    FRAGCOLOR = vec4(0.0);
    return;
  }
  else if (zNoTransp <= zWithTransp)
  {
    FRAGCOLOR = vec4(GetNormal(vTexCoord.xy).xyz * 0.5 + vec3(0.5), 1.0);
    return;
  }

  // Compute normal from depth
  vec3 posX0 = UVToViewPos(vTexCoord.xy-vec2(cb_PostEffectAuto.u_PixelSize.x, 0.0));
  vec3 posX1 = UVToViewPos(vTexCoord.xy+vec2(cb_PostEffectAuto.u_PixelSize.x, 0.0));
  vec3 posY0 = UVToViewPos(vTexCoord.xy-vec2(0.0, cb_PostEffectAuto.u_PixelSize.y));
  vec3 posY1 = UVToViewPos(vTexCoord.xy+vec2(0.0, cb_PostEffectAuto.u_PixelSize.y));
  vec3 diffX = posX1 - posX0;
  vec3 diffY = posY1 - posY0;

  vec3 normal = vNormalize(vCross(diffX, diffY));
  vec3 viewVect = UVToViewVect(vTexCoord.xy);
  float NoV = vDot(normal, viewVect);
  if (NoV > 0.0) normal = -normal;

  FRAGCOLOR = vec4(normal * 0.5 + vec3(0.5), GetColor(vTexCoord.xy).a);
}
