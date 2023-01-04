void mapping_infinite_cylindrical(in mapping_info_t info, out mapping_result_t result)
{
  const float r_p = length(info.p.xy);

  const float theta = atan(info.p.y, info.p.x);

  result.uv.x = theta * r_p;
  result.uv.y = info.p.z;

  const float cos_theta = cos(theta);
  const float sin_theta = sin(theta);

  result.t = -sin_theta*info.x + cos_theta*info.y;
  result.b = info.z;
}
