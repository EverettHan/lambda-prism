//layout(r8) uniform coherent image3D i_SourceImage;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
  ivec3 storePos      = ivec3(gl_GlobalInvocationID.xy, 0);
  int groundAltitude  = int(cb_Clear_Auto.u_GroundVoxelPosition * float(IMAGE_DEPTH)); 
  groundAltitude -= 1;
  
#ifndef IMAGE_DEPTH
  int depthSize = vImageSize(i_SourceImage).x; // z should be used but it doesn't work, why ????
#else
  int depthSize = IMAGE_DEPTH;
#endif

  for(int i = 0 ; i < IMAGE_DEPTH; ++i)
  {
    storePos.z = i;
    imageStore(i_SourceImage, storePos, i <= groundAltitude ? vec4(1.0) : vec4(0.0));
  }
}
