layout(std430) buffer hashMapBuffer
{
  uint data[];
};

layout(local_size_x = 32, local_size_y = 1, local_size_z = 1) in;

void main(void)
{
  data[gl_GlobalInvocationID.x] = 0;
}
