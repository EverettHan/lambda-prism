void main(void)
{
  vec2 coord = ConvertViewportToViewpoint(vTexCoord);

#ifdef STEREO_MODE
  #if defined(VIEW_ID) && VIEW_ID==1
  vec4 color = vTexture(s_BackgroundTexture_Right, coord);
  #else
  vec4 color = vTexture(s_BackgroundTexture_Left, coord);
  #endif
  
#else
  vec4 color = vTexture(s_BackgroundTexture, coord);

#endif
    
  color.xyz *= cb_Background.u_Intensity;
  FRAGCOLOR = color;
}
