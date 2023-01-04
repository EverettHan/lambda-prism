//layout(r32ui) uniform coherent uimage2DArray textureToClear;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
  ivec3 storePos = ivec3(gl_GlobalInvocationID.xy, 0);

  for(int i = 0 ; i < NB_LAYER ; ++i)
  {
    storePos.z = i;
    imageStore(textureToClear, storePos, uvec4(0xFFFFFFFF));
  }
}
