
void main()
{
  vec2 uvs = vTexCoord.xy / cb_PostEffect_SSR_Convolution.u_UVScale;

  vec4 color = vTextureLod(MapWithMips, uvs+vec2(-0.49,-0.49)*cb_PostEffect_SSR_Convolution.u_PixelSize, cb_PostEffect_SSR_Convolution.u_MipLevel);
  color = vMin(color, vTextureLod(MapWithMips, uvs+vec2(1.49,-0.49)*cb_PostEffect_SSR_Convolution.u_PixelSize, cb_PostEffect_SSR_Convolution.u_MipLevel));
  color = vMin(color, vTextureLod(MapWithMips, uvs+vec2(-0.49,1.49)*cb_PostEffect_SSR_Convolution.u_PixelSize, cb_PostEffect_SSR_Convolution.u_MipLevel));
  color = vMin(color, vTextureLod(MapWithMips, uvs+vec2(1.49,1.49)*cb_PostEffect_SSR_Convolution.u_PixelSize, cb_PostEffect_SSR_Convolution.u_MipLevel));

	FRAGCOLOR = color;
}
