void mapping_planar(in mapping_info_t info, out mapping_result_t result)
{
  result.uv = info.p.xy;
  result.t = info.x;
  result.b = info.y;
}
