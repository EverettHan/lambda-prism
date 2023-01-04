#define NUM_BLUR 12
#define INV_NUM_BLUR 0.08333334
const vec2 g_FilterBlurData[NUM_BLUR] = vec2[]
(
  vec2(-0.326212f,  -0.405805f),
  vec2(-0.840144f,  -0.07358f ),
  vec2(-0.695914f,  0.457137f ),
  vec2(-0.203345f,  0.620716f ),
  vec2(0.96234f,    -0.194983f),
  vec2(0.473434f,   -0.480026f),
  vec2(0.519456f,   0.767022f ),
  vec2(0.185461f,   -0.893124f),
  vec2(0.507431f,   0.064425f ),
  vec2(0.89642f,    0.412458f ),
  vec2(-0.32194f,   -0.932615f),
  vec2(0.791559f,   -0.597705f)
);


void UnrollFetch(const int i, inout vec4 ioColor)
{
#ifdef SIZE_IN_PIXEL
  // on rajoute 1.0 pour compenser l'arrondis qui arrive ensuite a cause du call a textureOffset
  vec4 col = GetColor(vTexCoord, g_FilterBlurData[i] * (cb_PostEffect_Blur_Poisson.u_BlurSize));
#else
  vec4 col = GetColor(vTexCoord + ConvertViewpointToViewportRatio(g_FilterBlurData[i] * cb_PostEffect_Blur_Poisson.u_BlurSize * cb_PostEffectAuto.u_ViewpointFixRatio));
#endif

#ifdef ALPHA_MODE
  ioColor.xyz += col.xyz*col.w;
  ioColor.w += col.w;
#else
  ioColor += col;
#endif
}

void main(void)
{ 
  vec4 result = vec4(0, 0, 0, 0);  
  
  UnrollFetch(0 , result);
  UnrollFetch(1 , result);
  UnrollFetch(2 , result);
  UnrollFetch(3 , result);
  UnrollFetch(4 , result);
  UnrollFetch(5 , result);
  UnrollFetch(6 , result);
  UnrollFetch(7 , result);
  UnrollFetch(8 , result);
  UnrollFetch(9 , result);
  UnrollFetch(10, result);
  UnrollFetch(11, result);
  
#ifdef ALPHA_MODE
  if (result.w!=0) 
  {
    result.xyz *= 1.f/result.w;
    result.w *= INV_NUM_BLUR;
  }
#else
  result *= INV_NUM_BLUR;
#endif

  FRAGCOLOR = result;
}
