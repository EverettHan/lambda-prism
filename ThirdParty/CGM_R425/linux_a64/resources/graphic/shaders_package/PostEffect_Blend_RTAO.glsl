
void main()
{
  float ao = 0.0;
  float alpha = 0.0;

  #ifdef IS_MSAA  
    for(int i=0; i<IS_MSAA; i++)
      ao += texelFetch(s_SourceTex, ivec2(gl_FragCoord.xy), i).x;

    ao /= float(IS_MSAA);
  #else
    ao = texelFetch(s_SourceTex, ivec2(gl_FragCoord.xy), 0).x;
  #endif
  
  //This works in both MSAA and non-MSAA (0 is the first MIP and also the first sample)
  //In the MSAA normal map, samples other than 0 don't have alpha information for some reason...
  alpha = texelFetch(AlphaMapForGround, ivec2(gl_FragCoord.xy), 0).w;

  FRAGCOLOR = vec4(0.0, 0.0, 0.0, (1.0 - ao) * alpha);
}
