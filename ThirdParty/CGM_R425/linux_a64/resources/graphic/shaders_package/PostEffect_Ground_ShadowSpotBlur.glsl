
void main(void)
{
  vec2  coord = vFma(vTexCoord.xy, vec2(2.0), vec2(-1.0));
  float ratio = vMax(0, 1.0 - vDot(coord, coord));

  FRAGCOLOR = vec4(ratio*ratio);
}

