uniform sampler2D s_SourceTex;

void main(void)
{
  FRAGCOLOR = vTexture(s_SourceTex, vTexCoord);
}
