in vec4 vPosition;

layout(location = 0) out vec4 fragColor;

void main()
{
  vec4 col1 = cb_cbAmbiance_Background_2DGraduated_Auto.Color;
  vec4 col2 = cb_cbAmbiance_Background_2DGraduated_Auto.ColorGraduated;

  float ratio = vClamp((vPosition.y+1)*0.5, 0.12, 0.67);
  if (ratio<0.338) ratio = (ratio-0.12)/(0.338-0.12);
  else             ratio = 1-(ratio-0.338)/(0.67-0.338);
  
  vec4 col = vMix(col1, col2, ratio);
  col.w = 1;
  fragColor = col;
}
