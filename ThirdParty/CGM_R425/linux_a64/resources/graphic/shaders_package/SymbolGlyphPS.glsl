float ComputeOpacity()
{ 
#if defined HLSecondPolite
  return 1.0;
#elif HLFirstPolite
  return 0.55;
#else
  return 1.0;
#endif
}

void ProcessFinalColor(inout vec4 ioFinalColor)
{
  //Find the texture coordinate's distance from the edge
  float distFromEdge = vMin(
    vMin(vTexCoord.x, 1.0 - vTexCoord.x),
    vMin(vTexCoord.y, 1.0 - vTexCoord.y) );

  //If the coordinate is within L1 distance from
  //edge, we will darken the color to make a border.
  float borderWidth = 0.20;
  float colorMultiplier = 1.0 - .5*(1.0 - step(borderWidth, distFromEdge));
  vec4 glyphColor = cb_cbSymbol.GlyphColor /cb_cbSymbol.GlyphColor.a;

#if defined HLFirstPolite 
  ioFinalColor.rgb = glyphColor.rgb;
#elif HLSecondPolite
  ioFinalColor.rgb = vec3 (glyphColor.r * colorMultiplier, glyphColor.g * colorMultiplier, glyphColor.b * colorMultiplier);
#endif
}
