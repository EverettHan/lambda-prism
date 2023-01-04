
void main()
{
  ivec2 pos = ivec2(gl_FragCoord.xy);

#if INTERLEAVE_SIZE==4
  ivec2 offset  = pos & 3;
  ivec2 uv      = pos >> 2;
#else
  ivec2 offset  = pos % INTERLEAVE_SIZE;
  ivec2 uv      = pos / INTERLEAVE_SIZE;
#endif

  int  sliceId = offset.y * INTERLEAVE_SIZE + offset.x;
  
  FRAGCOLOR = vec4(vTexelFetch(s_SourceMapArray, ivec3(uv, sliceId), 0).xxx, 0);
}



