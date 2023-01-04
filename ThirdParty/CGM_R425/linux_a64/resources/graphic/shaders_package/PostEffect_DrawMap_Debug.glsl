
void main()
{
#if defined(TEXTURE_ARRAY) || TEXTURE_DIMENSION==3
  vec4 col = DrawPicture(s_SourceTex, vTexCoord.xy, cb_PostEffectAuto.u_ViewpointSize.xy, _sbCbLayer.u_Mip, _sbCbLayer.u_Layer);
#else
  vec4 col = DrawPicture(s_SourceTex, vTexCoord.xy, cb_PostEffectAuto.u_ViewpointSize.xy, _sbCbLayer.u_Mip);
#if defined(TEXTURE_HISTOGRAM) && TEXTURE_DIMENSION==1
  if (col.x > vTexCoord.y)
  {
    float ratio = (col.x-vTexCoord.y) / col.x;
    col = vec4(ratio, ratio, ratio, 1);
  }
  else
  {
    col = vec4(1, 1, 1, 0);
  }
#endif

#endif

#ifdef FORCE_ONECHANEL
  col.rgb = vec3(col.r);
#endif

#ifdef FORCE_NOALPHA
  col.a = 1.0;
#endif

  FRAGCOLOR = col;
}
