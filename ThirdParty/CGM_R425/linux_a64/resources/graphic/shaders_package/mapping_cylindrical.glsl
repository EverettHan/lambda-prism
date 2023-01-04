void mapping_cylindrical(in mapping_info_t info, out mapping_result_t result)
{
  vec3 n = info.n;

  if (dot(info.p, info.n) < 0.0)
    n = -info.n;

  vec3 absn = abs(n);
  float maxn = max(absn.x, max(absn.y, absn.z));
  float r_p = length(info.p.xy);


  if(maxn == absn.z)
  {
    float s = info.p.z >= 0.0 ?  1.0 : -1.0;
    result.uv.x = s * info.p.x;
    result.uv.y = info.p.y;

    result.t = s * info.x;
    result.b = info.y;
  }
  else
  {
    float theta = atan(info.p.y, info.p.x);

    result.uv.x = theta * r_p;
    result.uv.y = info.p.z;

    float cos_theta = cos(theta);
    float sin_theta = sin(theta);

    result.t = -sin_theta*info.x + cos_theta*info.y;
    result.b = info.z;
  }
}
