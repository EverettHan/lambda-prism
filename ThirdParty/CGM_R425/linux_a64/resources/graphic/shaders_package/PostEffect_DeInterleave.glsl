layout(location = 0, index = 0) out float fragColor[NUM_MRT];
#define FRAGCOLOR fragColor

#if (INTERLEAVE_SIZE==4  && !defined(DST_MSAA) && !defined(SRC_MSAA)) || defined(NoPerSampleShading)
#define OPTIM_GATHER_4 1
#endif

#if !defined(OPTIM_GATHER_4)
void UpdateOffset(inout ivec2 ioOffset)
{
  ioOffset.x++;
  if (ioOffset.x >= INTERLEAVE_SIZE)
  {
    ioOffset.x = 0;
    ioOffset.y++;
  }
}
#endif

void main()
{ 
#ifdef OPTIM_GATHER_4
  //--------------------------------------------
  // Mode optimisé pour une size de 4

  vec2 uv = vFloor(gl_FragCoord.xy) * INTERLEAVE_SIZE + cb_PostEffect.u_Offset + 0.5;
  uv *= cb_PostEffect.u_SrcPixelSize;


  // Gather: retourne:
  // x : pixel decalé d'un offset de (0,1) par rapport a uv
  // y : pixel decalé d'un offset de (1,1) par rapport a uv
  // z : pixel decalé d'un offset de (1,0) par rapport a uv
  // w : pixel decalé d'un offset de (0,0) par rapport a uv
  vec4 S0 = vTextureGather       (s_SourceTexture, uv, 0);
  vec4 S1 = vTextureGatherOffset (s_SourceTexture, uv, ivec2(2, 0), 0);

  FRAGCOLOR[0] = S0.w;
#if NUM_MRT>1
  FRAGCOLOR[1] = S0.z;
#endif
#if NUM_MRT>2
  FRAGCOLOR[2] = S1.w;
#endif
#if NUM_MRT>3
  FRAGCOLOR[3] = S1.z;
#endif
#if NUM_MRT>4
  FRAGCOLOR[4] = S0.x;
#endif
#if NUM_MRT>5
  FRAGCOLOR[5] = S0.y;
#endif
#if NUM_MRT>6
  FRAGCOLOR[6] = S1.x;
#endif
#if NUM_MRT>7
  FRAGCOLOR[7] = S1.y;
#endif
  

#else
  //--------------------------------------------
  // Mode Generique

  ivec2 uv = ivec2((vFloor(gl_FragCoord.xy) * INTERLEAVE_SIZE + cb_PostEffect.u_Offset));
  
  ivec2 offset = ivec2(0, 0);
  FRAGCOLOR[0] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;

#if NUM_MRT>1
  UpdateOffset(offset);
  FRAGCOLOR[1] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#if NUM_MRT>2
  UpdateOffset(offset);
  FRAGCOLOR[2] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#if NUM_MRT>3
  UpdateOffset(offset);
  FRAGCOLOR[3] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#if NUM_MRT>4
  UpdateOffset(offset);
  FRAGCOLOR[4] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#if NUM_MRT>5
  UpdateOffset(offset);
  FRAGCOLOR[5] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#if NUM_MRT>6
  UpdateOffset(offset);
  FRAGCOLOR[6] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#if NUM_MRT>7
  UpdateOffset(offset);
  FRAGCOLOR[7] = vTexelFetch(s_SourceTexture, uv + offset, gl_SampleID).x;
#endif

#endif
}



