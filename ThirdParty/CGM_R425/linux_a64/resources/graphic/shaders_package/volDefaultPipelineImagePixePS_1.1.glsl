layout(location = 0) out vec4 fragColor;
#ifdef WeightedAverage
  layout(location = 1) out vec4 fragDepthWA;
  #define volDefaultPipelineImagePixePS_MRT_1_TAKEN
#endif //WeightedAverage

#ifdef OutputGPUPicking
  #if defined(volDefaultPipelineImagePixePS_MRT_1_TAKEN)
    layout(location = 2) out uint gpuPickingMap;
    #define volDefaultPipelineImagePixePS_MRT_2_TAKEN
  #else
    layout(location = 1) out uint gpuPickingMap;
    #define volDefaultPipelineImagePixePS_MRT_1_TAKEN
  #endif
#endif //OutputGPUPicking

// Avoid issue with SSR activation
vec4 fragNormal;
vec4 fragIBLRefl;
vec4 fragF0Rough;

vec3 ComputeEmissive()
{
  return vec3(0.0);
}

// Multiple Render Targets support. The default is to output the lit or (unlit if lighting disabled) fragment color (the 'fragColor' input parameter) to the first render target, but additionnal value may be added here
void OutputMRT(vec4 finalColor)
{
  vec2 coord = gl_FragCoord.xy - vTexCoord.xy;
  vec4 texelValue = vTexelFetch(imageTexture, ivec2(coord), 0);

#ifdef HighlightAdvanced
  fragColor = vec4(cb_cbVolImagePixelMaterial.u_Color.xyz, 0.0);
#elif defined(HLSecondPolite) || defined(HLFirstPolite)
  fragColor = vec4(cb_cbVolImagePixelMaterial.u_Color*texelValue);
#elif defined(AdvancedHLFirstPolite)
  fragColor.rgb = vec3(cb_cbVolImagePixelMaterial.u_Color.xyz*texelValue.xyz);
#else
  fragColor = texelValue;
#endif

  if( cb_cbVolImagePixelMaterial.u_ImageAlpha != 0 )
  {
	if (texelValue.a < 0.5)
		discard;
  }
}

#ifdef CUSTOM_COVERAGE
void PerformCustomCoverage()
{
}
#endif
