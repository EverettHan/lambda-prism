
void main(void)
{ 
  vec2 coord = ConvertViewportToViewpoint(vTexCoord)*cb_Displacement.u_DisplacementScale;
  vec2 delta = cb_Displacement.u_DisplacementStrength*vTexture(s_DisplacementMap, coord).xy;
  
  delta *= cb_PostEffectAuto.u_ViewpointFixRatio;
  delta = ConvertViewpointToViewportRatio(delta);

  coord = vTexCoord + delta;

  vec4 color = GetColor(vTexCoord + delta);
	color.w = 1;

  FRAGCOLOR = color;
}

