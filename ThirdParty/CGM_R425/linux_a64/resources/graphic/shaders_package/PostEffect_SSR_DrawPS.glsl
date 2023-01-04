
void main()
{
  vec4 fallbackColor = GetColor(vTexCoord.xy);
  vec4 reflContrib = vTexture(ReflRadianceMap, vTexCoord.xy);
  vec4 iblContrib = GetEffectTexture(IBLSpecContribMap, vTexCoord.xy);
  vec3 colorWithRefl = vMax(vec3(0.0), fallbackColor.rgb - iblContrib.rgb) + reflContrib.rgb;
  FRAGCOLOR = vec4(vMix(fallbackColor.rgb, colorWithRefl, iblContrib.a*reflContrib.a), fallbackColor.a);
}
