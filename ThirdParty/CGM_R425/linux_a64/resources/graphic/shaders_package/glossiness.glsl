#ifdef Lighting

#ifndef XRiteCarPaint2

#ifndef V_DISABLE_GLOSSINESS_SMOOTHING
void ComputeGlossinessSmoothing(in LightingData iData, inout BRDFParameters ioParameters)
{
  #ifdef RayHitStage
    return; // no partial derivatives yet
  #endif

  float diff_threshold_start = 0.005;
  float diff_threshold_end = 0.01;

  vec3 dx = vDFdx(iData.N);
  vec3 dy = vDFdy(iData.N);

  float ddx = vDot(dx, dx);
  float ddy = vDot(dy, dy);

  float dot_N_V = max(0.0, dot(iData.V, iData.N));
  float glossiness_factor = 1.0-vClamp((10.0*(ddx + ddy)), 0.0, 1.0);
  glossiness_factor = vClamp(glossiness_factor, 1.0-dot_N_V, 1.0);
  ioParameters.roughness = (1.0-(1.0-ioParameters.roughness)*glossiness_factor);
  #ifdef Coating
// TODO: implement for EVisuPBR !!!
    ioParameters.coatingRoughness = 1.0-(1.0-ioParameters.coatingRoughness)*glossiness_factor;
  #endif
}
#endif

void ComputeGlossinessClamping(inout BRDFParameters ioParameters)
{
#if defined(EVisuPBR) || defined(XRiteCarPaint2)
  // TODO: implement for EVisuPBR !!!
#else
    ioParameters._unclampedRoughness = ioParameters.roughness; //used for ibl sampling (because clamping has already been done when prefiltering)
    ioParameters.roughness = vClamp(ioParameters.roughness,0.0,0.999);
  #ifdef Coating
    ioParameters.coatingRoughness = vClamp(ioParameters.coatingRoughness,0.0,0.999);
  #endif
  #ifdef Flakes
	  ioParameters.metallicFlakesRoughness = vClamp(ioParameters.metallicFlakesRoughness,0.0,0.999);
	  ioParameters.metalRoughness = vClamp(ioParameters.metalRoughness,0.0,0.999);
	  ioParameters.pearlFlakesRoughness = vClamp(ioParameters.pearlFlakesRoughness,0.0,0.999);
	  ioParameters.pearlRoughness = vClamp(ioParameters.pearlRoughness,0.0,0.999);
  #endif
#endif
}

#endif // XRiteCarPaint2

#endif // Lighting
