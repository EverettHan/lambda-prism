void mapping_cubic(in mapping_info_t info, out mapping_result_t result)
{
  vec3 absn = abs(info.n);
  float maxn = max(absn.x, max(absn.y, absn.z));

  vec3 n = info.n;

  if(dot(info.p, info.n) < 0.0)
    n = -info.n;
  
  vec3 s;
  s.x = n.x >= 0.0 ?  1.0 : -1.0;
  s.y = n.y >= 0.0 ? -1.0 :  1.0;
  s.z = n.z >= 0.0 ?  1.0 : -1.0;

  if(maxn == absn.x)
  {
    result.uv = vec2(s.x * info.p.y, info.p.z);
    result.t = s.x * info.y;
    result.b = info.z;
  }
  else if(maxn == absn.y)
  {
    result.uv = vec2(s.y * info.p.x, info.p.z);
    result.t = s.y * info.x;
    result.b = info.z;
  }
  else
  {
    result.uv = vec2(s.z * info.p.x, info.p.y);
    result.t = s.z * info.x;
    result.b = info.y;
  }
}
