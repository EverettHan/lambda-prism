

#ifdef IS_MSAA
//uniform coherent layout(r8) image2DMS RaytraceOutput;

vec3 ResolveNormal(ivec2 iTexIndex)
{
  vec3 normal = vec3(0.0);

  for (int i = 0; i < IS_MSAA; ++i)
    normal += texelFetch(RaytraceNormalMap, iTexIndex, i).xyz * 2.0 - vec3(1.0);

  return normalize(normal);
}

float ResolveDepth(ivec2 iTexIndex)
{
  float depth = 1e24;
  for (int i = 0; i < IS_MSAA; ++i)
  {
    depth = min(depth, texelFetch(RaytraceZMap, iTexIndex, i).r);
  }

  return depth;
}
#else
//uniform coherent layout(r8) image2D RaytraceOutput;

vec3 ResolveNormal(ivec2 iTexIndex)
{
  return texelFetch(RaytraceNormalMap, iTexIndex, 0).xyz * 2.0 - vec3(1.0);
}

float ResolveDepth(ivec2 iTexIndex)
{
  return texelFetch(RaytraceZMap, iTexIndex, 0).r;
}
#endif

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

float gauss(float d, float sigma)
{
  float a = d/sigma;
  return exp(-0.5 * a * a);
}

float calculateBilateralWeight(ivec2 p, ivec2 q, int stepwidth, float cphi, float nphi, float dphi, float ctmp, vec3 normal, float depth, float ao, float dx, float dy)
{
  float eps = 1e-6;
  float t = max(ao - ctmp, 0.0);
  float w_c = exp(-t/cphi);
  
  float dtmp = ResolveDepth(q);
  float dt = abs(depth-dtmp);
  float dz = length(vec2(dx, dy) * vec2(p-q));
  float w_d = exp(-dt/(dphi*dz+eps));

  vec3 ntmp = ResolveNormal(q);
  vec3 nt = normal - ntmp;
  float dist2 = max(dot(nt,nt), 0.0);
  float w_n = min(exp(-dist2/nphi), 1.0);

  return pow(w_n * w_n * w_d * w_c, cb_PostEffect_RT_AO.u_DenoiserExponent);
}

void applyFilter(in int dirX, in int dirY)
{
  ivec2 p = ivec2(gl_GlobalInvocationID.xy);
  int it = D_ITERATION;
  int stepwidth = 1 << it;

  float sum_w = 0.0;
  float sum = 0.0;

  const int m = 5;

  vec3 normal = ResolveNormal(p);
  float depth = ResolveDepth(p);

  #ifdef IS_MSAA
    float ao = imageLoad(RaytraceOutput, p, int(gl_GlobalInvocationID.z)).x;
  #else
    float ao = imageLoad(RaytraceOutput, p).x;
  #endif
  float dx = ResolveDepth(p + ivec2(1, 0)) - ResolveDepth(p + ivec2(-1, 0));
  float dy = ResolveDepth(p + ivec2(0, 1)) - ResolveDepth(p + ivec2(0, -1));


  const float c_phi = pow(2.0, -float(it - 1)) * cb_PostEffect_RT_AO.u_DenoiserCPhi;
  const float d_phi = cb_PostEffect_RT_AO.u_DenoiserDPhi;
  const float n_phi = cb_PostEffect_RT_AO.u_DenoiserNPhi;
  const float sigma = cb_PostEffect_RT_AO.u_DenoiserSigma;

  for (int i = 0; i < m; i++)
  {
    const int offset = i - m/2;
    ivec2 q = p + offset * stepwidth * ivec2(D_FILTER_DIR_X, D_FILTER_DIR_Y);

    q = clamp(q, ivec2(0), imageSize(RaytraceOutput)-ivec2(1));
  #ifdef IS_MSAA
    float ctmp = imageLoad(RaytraceOutput, q, int(gl_GlobalInvocationID.z)).x;
  #else
    float ctmp = imageLoad(RaytraceOutput, q).x;
  #endif
    float weight = calculateBilateralWeight(p, q, stepwidth, c_phi, n_phi, d_phi, ctmp, normal, depth, ao, dx, dy);

    float k = gauss(abs(offset), sigma);
    sum += ctmp * weight * k;
    sum_w += weight * k;
  }

  #ifdef IS_MSAA
    imageStore(RaytraceOutput, p, int(gl_GlobalInvocationID.z), vec4(sum/sum_w));
  #else
    imageStore(RaytraceOutput, p, vec4(sum/sum_w));
  #endif
}

void main()
{
  applyFilter(D_FILTER_DIR_X, D_FILTER_DIR_Y);
}
