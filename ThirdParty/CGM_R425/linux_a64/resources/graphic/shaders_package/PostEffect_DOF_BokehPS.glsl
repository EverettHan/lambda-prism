
in vec4 vPosition;
in vec2 vTexCoordGS;
in vec4 vColorGS;

void main()
{
  vec4 texelValue = vTexture(s_BokehPatternTex, vTexCoordGS.xy) * vColorGS.a;// + vec4(0.2);
  FRAGCOLOR.xyz = texelValue.a * vColorGS.xyz;
  FRAGCOLOR.a = texelValue.a;
}
