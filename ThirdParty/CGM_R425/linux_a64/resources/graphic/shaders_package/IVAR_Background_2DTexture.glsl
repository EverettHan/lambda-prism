
vec4 GetTexture(sampler2D iTexture, vec2 iCoord)
{
#ifdef GLESPlatform
  // Simulate ClampToBorder
  const vec4 borderColor = vec4(0.0);
  if (iCoord.x < 0.0 || iCoord.x > 1.0 || iCoord.y < 0.0 || iCoord.y > 1.0)
    return borderColor;
#endif
  return vTexture(iTexture, iCoord.xy);
}

vec2 GetTextureSize(sampler2D iTexture)
{
  // Texture size is given as a uniform for OpenGL ES 2.0 compatibility
  //return vec2(vTextureSize(iTexture, 0).xy);
  return cb_IVARBackground.u_TextureSize;
}

void main(void)
{
  vec2 texSize  = GetTextureSize(s_BackgroundTexture);
  vec2 vpSize   = cb_PostEffectAuto.u_ViewpointSize.xy;
  vec2 fit      = cb_IVARBackground.u_TextureFit;
  //vec2 fit      = vec2(0.0, 1.0); // TEST: fit Height

  float vpRatio   = vpSize.x/vpSize.y;
  float texRatio  = texSize.x/texSize.y;

  float ratio     = vpRatio/texRatio;

  vec2 delta = vec2(0.0);
  vec2 scale = vec2(1.0); 

  // TODO: also support the 3 following modes for BG rendering and AR overlay
  // => Use u_FitTexture flags:
  // 0, 0 => fit nothing == always zoom, always crop
  // 0, 1 => fit height : default behaviour
  // 1, 0 => fit width
  // 1, 1 => always fit : initial shader behaviour

  /*
  // 0, 0
  // Always zoom
  if (ratio<=1.0)
  {
    scale.x = ratio;
  }
  else
  {
    scale.y = 1.0/ratio;
  }
  */
  
  /*
  // 0, 1
  // => Fit height, width is filled / cropped
  // Never change y: should be full height, whatever the width of the viewer (which will be cropped)
  // AR is correct: we use the height of the viewer to set the focal
  scale.x = ratio; 
  */

  /*
  // 1, 0
  // => Fit width, height is filled / cropped 
  // FIXME: AR is wrong: viewer height is used to set the focal: we should use effective texture height instead...
  scale.y = 1.0/ratio; 
  */

  /*
  // 1, 1
  // Always fit
  // Initial shader behaviour
  if (ratio>=1.0) // e.g trying to fit a 4/3 texture inside a 16/9 viewer
  {
    scale.x = ratio;
  }
  else
  {
    scale.y = 1.0/ratio;
  }
  */

  /*
  // The above code without branching
  if(ratio >= 1.0)
  {
    scale.x = mix(1.0, ratio, fit.y);
    scale.y = mix(1.0/ratio, 1.0, fit.y);
  }
  else
  {
    scale.x = mix(ratio, 1.0, fit.x);
    scale.y = mix(1.0, 1.0/ratio, fit.x);
  }
  */

  // Reducing the branching even further
  // if ratio <= 1.0, sign(ratio - 1.0) == -1
  scale.x = mix(mix(ratio, 1.0, fit.x), mix(1.0, ratio, fit.y), 0.5*sign(ratio - 1.0) + 0.5);
  scale.y = mix( mix(1.0, 1.0/ratio, fit.x), mix(1.0/ratio, 1.0, fit.y), 0.5*sign(ratio - 1.0) + 0.5);
  
  
  delta = 0.5*(vec2(1.0) - scale.xy); // scale.xy is necessary to compensate the vertex shader

  vec2 coord = ConvertViewportToViewpoint(vTexCoord);
  vec2 flip = cb_IVARBackground.u_Flip;

  // mirror
  // x => 1-x
  coord = flip + (1.0 - 2.0*flip)*coord;
  coord = coord*scale+delta;
	
  vec4 color = GetTexture(s_BackgroundTexture, coord);
  color.xyz *= cb_Background.u_Intensity;

  FRAGCOLOR = color;
}
