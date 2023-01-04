#if TEXTURE_DIMENSION==2

  #define LOCAL_SIZE_Y 16
  #define LOCAL_SIZE_Z 1

#elif TEXTURE_DIMENSION==3

  #define LOCAL_SIZE_Y 16
  #define LOCAL_SIZE_Z 16

#else

  #define LOCAL_SIZE_Y 1
  #define LOCAL_SIZE_Z 1

#endif

layout (local_size_x = 16, local_size_y = LOCAL_SIZE_Y, local_size_z = LOCAL_SIZE_Z) in;

void main() 
{
  vec3 size = vec3(1,1,1);

#if TEXTURE_DIMENSION==2
  size.xy = vImageSize(i_SrcMap).xy;
#elif TEXTURE_DIMENSION==3
  size.xyz = vImageSize(i_SrcMap).xyz;
#else
  size.x = vImageSize(i_SrcMap);
#endif
  
  if ( gl_GlobalInvocationID.x    >= size.x 
      || gl_GlobalInvocationID.y  >= size.y  
      || gl_GlobalInvocationID.z  >= size.z)
    return;

#if TEXTURE_DIMENSION==2
  ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
#elif TEXTURE_DIMENSION==3
  ivec3 coord = ivec3(gl_GlobalInvocationID.xyz);
#else
  int coord = int(gl_GlobalInvocationID.x);
#endif

#ifdef MSAA
for(int i=0; i<MSAA; i++)
{
  vec4 value = vImageLoad (i_SrcMap, coord, i);
  value = (value - cb_ConvertIntegerTexture.u_Min)/(cb_ConvertIntegerTexture.u_Max - cb_ConvertIntegerTexture.u_Min);
  vImageStore(i_DstMap, coord, i, value);
}
#else
  vec4 value = vImageLoad (i_SrcMap, coord);
  value = (value - cb_ConvertIntegerTexture.u_Min)/(cb_ConvertIntegerTexture.u_Max - cb_ConvertIntegerTexture.u_Min);
  vImageStore(i_DstMap, coord, value);
#endif

}
