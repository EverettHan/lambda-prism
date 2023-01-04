
ivec2 nj3Modulo(in ivec2 x, in ivec2 y)
{
  return ivec2(x - y * floor(x/y));
}

void main()
{
  ivec3 texSize    = vTextureSize(s_SourceTex, 0);
  ivec2 screenSize = ivec2(cb_Viewport.u_ViewportSize);
  ivec2 fragPos    = ivec2(gl_FragCoord.xy);
  
  int nbTile = texSize.z;
  
  int gridConfig = int(vCeil(vSqrt(nbTile)));
  
  //Grid config will contain the tile number in X and Y. For example if we have 3 it represents :
  //  ____________
  // | 6 | 7 | 8 |
  // | 3 | 4 | 5 |
  // | 0 | 1 | 2 |
  //  ___________
  
  //Now we just have to kown which tile we must draw.
  ivec2 pixelPerTile = screenSize / gridConfig;
  
  vec2 samplePos = gl_FragCoord.xy / pixelPerTile - ivec2(gl_FragCoord.xy/pixelPerTile);
  
  int curTile = fragPos.x / pixelPerTile.x + gridConfig * (fragPos.y / pixelPerTile.y);
  
  
  vec4 texelValue = vTexture(s_SourceTex, vec3(samplePos, curTile/(nbTile-1.)));
  FRAGCOLOR = vec4(texelValue.x, texelValue.x, texelValue.x, 1);
}
