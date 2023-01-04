void main()
{
  vec4 result = vec4(0);

#ifdef FIRSTPASS
  result = ComputeFirstPassHalo(s_EyeMap);

#else
  result = ComputeHalo(s_EyeMap);
#endif

  FRAGCOLOR = result;

}

