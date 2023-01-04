void mapping_spherical_normalized(in mapping_info_t info, out mapping_result_t result)
{
  const float r = length(info.p);
  const float ratio = info.p.z / r;

  const float theta = atan(info.p.y, info.p.x);
  const float phi = asin(ratio);

  result.uv.x = theta * INV_PI;
  result.uv.y = phi * INV_PI;

  const float cos_theta = cos(theta);
  const float sin_theta = sin(theta);
  const float cos_phi = cos(phi);
  const float sin_phi = ratio;

  result.t = -sin_theta*info.x + cos_theta*info.y;
  result.b = -cos_theta*sin_phi*info.x - sin_theta*sin_phi*info.y + cos_phi*info.z;
}
