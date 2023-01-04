layout (location = 0) out vec4 fragColor;

void main()
{
  vec3 ray = GetDirectionFromCube(gl_Layer, TEXCOORD);
  fragColor = vec4(textureLod(s_EnvMapCube, ray, 0.0).rgb, 1.0);
}
