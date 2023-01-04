void ProcessClipSpacePosition(inout vec4 position)
{
  // Complex code, if it is changed, please check:
  //  - "Explore parents" in a product search result
  //  - Rep tree icons in a VisVolatileSample
  //  - Simulia result panel manager icons
  //  - Output results from: mkrun -c "VisTestApplication VisBatchUnitTests CreateDraw2DImgApp Path\For\Output"
  //  - ODT Vis_UnitTest_GPUGrab
  position.xy /= position.w;
  position.xy = vFma(position.xy, vec2(0.5), vec2(0.5));
  position.xy = vRound(position.xy * cb_Viewport.u_ViewportSize); 
  position.xy *= cb_Viewport.u_PixelSize;
  position.xy += (cb_Image_2D.Image_Offset + vGetTexCoord0().xy * cb_Image_2D.Image_Size) / cb_Image_2D.Image_Viewport;
  position.xy = vFma(position.xy, vec2(2.0), vec2(-1.0));
  position.xy *= position.w;
}

void ComputeVaryingValues()
{
  vTexCoord0 = vGetTexCoord0().xy;
}
