
#ifdef TextureFontText
float g_TextAlpha = 0.0;
#endif // ifdef TextureFontText
bool g_ZTestResult = true;

void ComputeCommonValues()
{
#ifdef TextureFontText
  g_TextAlpha = vTexture(atlasTexture, vGetTexCoord0().xy).a;
#endif // ifdef TextureFontText
  g_ZTestResult = vGetZTestResult();
}

bool ComputeDiscard()
{
#ifdef DRAW_MIRROR
  return true;
#elif defined(LinePrimitives)
  return false;
#elif defined(HighlightAdvanced)
  return true;
#elif defined(TextureFontText)
  if(g_TextAlpha < 0.1)
    return true;
#endif
  return !g_ZTestResult;
}

vec3 ComputeAlbedo()
{
  return vColorToUse;
}


float ComputeOpacity()
{
#ifdef TextureFontText
  return g_TextAlpha;
#elif defined(LinePrimitives)
  if(!g_ZTestResult)
    return 0.1;
  else
    return 1.0;
#endif
  return cb_cbVolMaterial.u_DiffuseColor.a;
}

void ProcessFinalColor(inout vec4 ioFinalColor)
{
#ifdef TextureFontText
  //vSetFragDepth(1.0);
#endif
}
