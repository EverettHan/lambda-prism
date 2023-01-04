void main()
{
  vec4 color = vec4(0,0,0,1);
  
  vec2 coord = ConvertViewportToViewpoint(vTexCoord);
  color = DrawPicture(s_Picture, coord,  cb_PostEffectAuto.u_ViewpointSize.xy, cb_Background.u_Mip);
  color.xyz *= cb_Background.u_Intensity;

#ifndef PICTURE_SHOW_ALPHA
  color.w = 1.f;
#endif
    
#ifdef PICTURE_BORDER_TRANSPARENT
  if (vTexCoord.x < cb_Background.u_VisibleArea.x || vTexCoord.y < cb_Background.u_VisibleArea.y
      || vTexCoord.x > cb_Background.u_VisibleArea.z || vTexCoord.y > cb_Background.u_VisibleArea.w)
  {
    color.w *= cb_Background.u_AlphaBlending;
  }
#endif

  FRAGCOLOR = color;
}
