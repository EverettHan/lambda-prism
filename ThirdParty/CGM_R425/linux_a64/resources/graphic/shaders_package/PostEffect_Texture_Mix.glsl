
void main(void)
{ 
  vec4 color = GetColor(vTexCoord);
  vec4 bgCol = vTexture(s_BackgroundTexture,	ConvertViewportToViewpoint(vTexCoord));

	color = (2-4*bgCol)*(color*color)+(4*bgCol-1)*color;
	color.w = cb_PostEffect.u_Alpha;
	
  FRAGCOLOR = color;
}

