void main()
{
  vec3 normal = vec3(-cbBackground.Normal.xyz);
  vec3 ray    = vNormalize(vRay);
 
  float scale = vClamp(vDot(normal, ray)*cbBackground.Ratio, 0.0, 1.0);
#if defined(GRADIENT_BICUBIC) || defined (GRADIENT_CUBIC)
  scale *= scale;
#if defined(GRADIENT_BICUBIC)
  scale *= scale;
#endif
#endif

  vec4 col = vMix(cbBackground.ColorHorizon, cbBackground.ColorTop, scale);
  col.xyz *= cbBackground.Intensity;

  FRAGCOLOR = col;
}
