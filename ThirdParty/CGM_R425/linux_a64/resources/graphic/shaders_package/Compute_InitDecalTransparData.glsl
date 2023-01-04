struct DecalTransparData_t
{
  uvec4 first;
  uvec4 second;
  uvec4 third;
};

//layout(std430) coherent restrict buffer DecalTransparData
//{
//  DecalTransparData_t g_DecalTransparData[];
//};

layout (local_size_x = 32, local_size_y = 1, local_size_z = 1) in;

void main() 
{
  if(gl_GlobalInvocationID.x == 0 && gl_GlobalInvocationID.y == 0 && gl_GlobalInvocationID.z == 0)
    g_DecalTransparData[0].first = floatBitsToUint(vec4(0.0, 0.0, 0.0, 0.0));
}
