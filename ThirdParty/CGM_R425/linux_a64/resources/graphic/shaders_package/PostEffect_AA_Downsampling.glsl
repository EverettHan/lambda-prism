

vec4 PatternSampling(sampler2D iTexture, vec2 iTexCoord, vec2 iOffset)
{
  ivec2 texSize = vTextureSize(iTexture, 0);
  vec2 SSTexelSize = 1./vec2(texSize);

  vec4 tap1 = vTexture(iTexture, iTexCoord + SSTexelSize * (vec2(  0.4,  0.9 ) + iOffset) );
  vec4 tap2 = vTexture(iTexture, iTexCoord + SSTexelSize * (vec2( -0.4, -0.9 ) + iOffset) );
  vec4 tap3 = vTexture(iTexture, iTexCoord + SSTexelSize * (vec2( -0.9,  0.4 ) + iOffset) );
  vec4 tap4 = vTexture(iTexture, iTexCoord + SSTexelSize * (vec2(  0.9, -0.4 ) + iOffset) );
  
  return (tap1 + tap2 + tap3 + tap4);
}

#if (SSScale == 4)

vec4 DownSample(sampler2D iTexture, vec2 iTexCoord)
{
  vec4 color = vTexture(iTexture, iTexCoord);
  
  color += PatternSampling(iTexture, iTexCoord, vec2(-1,  1));
  color += PatternSampling(iTexture, iTexCoord, vec2( 1,  1));
  color += PatternSampling(iTexture, iTexCoord, vec2( 1, -1));
  color += PatternSampling(iTexture, iTexCoord, vec2(-1, -1));
  
    
  return 0.0588235 * color;
}
#else

vec4 DownSample(sampler2D iTexture, vec2 iTexCoord)
{
  vec4 color = PatternSampling(iTexture, iTexCoord, vec2(0));
  color += vTexture(iTexture, iTexCoord);
  
  color *= 0.2;
  
  return color;
}

#endif

void main(void)
{ 
 vec4 col = DownSample(s_EyeMap, vTexCoord); 
 
  FRAGCOLOR = col;
}
