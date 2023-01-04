//layout(r32ui) uniform coherent uimage2DArray DecalTransparZMap;

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

void main() 
{
  imageStore(DecalTransparZMap, ivec3(gl_GlobalInvocationID.xyz), uvec4(0xFFFFFFFFu));
}
