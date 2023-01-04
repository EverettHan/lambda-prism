
vec4 gv4_color;

void ComputeCommonValues()
{
  if(vIsFrontFacing() )
    gv4_color = cb_cbSMAMpaFrontBackTranslucent.FrontColor;
  else
    gv4_color = cb_cbSMAMpaFrontBackTranslucent.BackColor;

  if (cb_cbSMAMpaFrontBackTranslucent.HasTexture != 0.0)
    gv4_color = vTexture(TextureName, v2_Tex);
}

vec3 ComputeAlbedo()
{
  return gv4_color.rgb;
}

float ComputeOpacity()
{
  return gv4_color.a;
}

vec3 ComputeSpecularReflectance()
{
  return 0.04 * gv4_color.rgb;
}

bool ComputeDiscard()
{
  return (!vIsFrontFacing() && cb_cbSMAMpaFrontBackTranslucent.ShowBackColor == 0.0);
}
