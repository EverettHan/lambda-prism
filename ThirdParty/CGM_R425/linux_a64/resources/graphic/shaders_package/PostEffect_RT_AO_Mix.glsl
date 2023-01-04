//uniform coherent layout(rgba8) image2D RaytraceOutput;

#ifdef IS_MSAA

vec4 ResolveColor(ivec2 iTexIndex)
{
  vec4 color = vec4(0.0);

  for (int i = 0; i < IS_MSAA; ++i)
    color += texelFetch(RaytraceColorMap, iTexIndex, i);

  return color/IS_MSAA;
}

#else

vec4 ResolveColor(ivec2 iTexIndex)
{
  return texelFetch(RaytraceColorMap, iTexIndex, 0);
}

#endif

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

void main()
{
  ivec2 p = ivec2(gl_GlobalInvocationID.xy);

  vec4 color = ResolveColor(p);

  color.xyz *= imageLoad(RaytraceOutput, p).x;

  imageStore(RaytraceOutput, p, pow(color, vec4(vec3(1/2.2), 1.0)));
}
