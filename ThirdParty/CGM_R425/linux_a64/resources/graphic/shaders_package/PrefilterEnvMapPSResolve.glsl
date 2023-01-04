layout (location = 0) out vec4 fragColor;

void main()
{
  vec4 color = texture(s_EnvMap, vTexCoord.xy);

  fragColor = vec4(color.xyz/color.w, 1.0);
}
