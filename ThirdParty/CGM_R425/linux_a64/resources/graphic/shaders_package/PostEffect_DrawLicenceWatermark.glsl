
void main()
{
  vec2 watermarkTexSize = vTextureSize(s_WatermarkTex, 0);
  vec2 screenSize = gl_FragCoord.xy / vTexCoord.xy;

  if (watermarkTexSize.x < screenSize.x) {
    float xMin = (screenSize.x - watermarkTexSize.x) * 0.5;
    float xMax = xMin + watermarkTexSize.x;

    const float yMin = cb_PostEffect_DrawLicenceWatermark.u_VerticalOffset;
    float yMax = yMin + watermarkTexSize.y;

    if (gl_FragCoord.x >= xMin && gl_FragCoord.x <= xMax && gl_FragCoord.y >= yMin && gl_FragCoord.y <= yMax) {
      vec2 watermarkTexCoord;
      watermarkTexCoord.x = (gl_FragCoord.x - xMin) / watermarkTexSize.x;
      watermarkTexCoord.y = (gl_FragCoord.y - yMin) / watermarkTexSize.y;

      FRAGCOLOR = vTexture(s_WatermarkTex, watermarkTexCoord);
    }
    else {
      discard;
    }
  }
  else {
    const float yMin = cb_PostEffect_DrawLicenceWatermark.u_VerticalOffset;
    float yMax = yMin + watermarkTexSize.y;

    float dx = (watermarkTexSize.x - screenSize.x) * 0.5;

    if (gl_FragCoord.y >= yMin && gl_FragCoord.y <= yMax) {
      vec2 watermarkTexCoord;
      watermarkTexCoord.x = (gl_FragCoord.x + dx)  / watermarkTexSize.x;
      watermarkTexCoord.y = (gl_FragCoord.y - yMin) / watermarkTexSize.y;

      FRAGCOLOR = vTexture(s_WatermarkTex, watermarkTexCoord);
    }
    else {
      discard;
    }
  }
}
