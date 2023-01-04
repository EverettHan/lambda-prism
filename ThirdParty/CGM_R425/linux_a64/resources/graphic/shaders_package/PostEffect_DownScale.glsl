
vec4 GetSourceTexture(const ivec2 iDelta)
{
#if !defined(GLES2Platform) && !defined(AMD) && !defined(MESA_SW)
  vec4 col = vTextureOffset(s_SourceTex, vTexCoord, iDelta);
#ifdef CHECK_NAN 
  if(isnan(col.x))
  {
    col = vec4(0);
  }
#endif
  return col;
#else
  ivec2 size = vTextureSize(s_SourceTex, 0);
  vec2 invSize = vec2(1.0/size.x, 1.0/size.y);

  vec2 coord = vTexCoord + iDelta * invSize;
  return vTexture(s_SourceTex, coord);
#endif
}

void main(void)
{   
#ifdef QUALITY_MAX
  vec4 col = GetSourceTexture(ivec2(0,0))*0.125;
  col += GetSourceTexture(ivec2(-1, -1))*0.125;
  col += GetSourceTexture(ivec2( 1, -1))*0.125;
  col += GetSourceTexture(ivec2( 1,  1))*0.125;
  col += GetSourceTexture(ivec2(-1,  1))*0.125;

  col += GetSourceTexture(ivec2(-2,  0))*0.0625;
  col += GetSourceTexture(ivec2( 2,  0))*0.0625;
  col += GetSourceTexture(ivec2( 0, -2))*0.0625;
  col += GetSourceTexture(ivec2( 0,  2))*0.0625;

  col += GetSourceTexture(ivec2(-2, -2))*0.03125;
  col += GetSourceTexture(ivec2( 2, -2))*0.03125;
  col += GetSourceTexture(ivec2( 2,  2))*0.03125;
  col += GetSourceTexture(ivec2(-2,  2))*0.03125;
#else
  vec4 col = GetSourceTexture(ivec2(0,0))*0.5;
  col += GetSourceTexture(ivec2(-1, -1))*0.125;
  col += GetSourceTexture(ivec2( 1, -1))*0.125;
  col += GetSourceTexture(ivec2( 1,  1))*0.125;
  col += GetSourceTexture(ivec2(-1,  1))*0.125;
#endif

  FRAGCOLOR = col;
}
