
layout(location = 0) out uint gpuPickingID;

void main()
{
  ivec2 iTexCoord = ivec2(vTexCoord * textureSize(s_SrcTex));
  gpuPickingID  = vTexelFetch(s_SrcTex, iTexCoord, 0).x;
}
