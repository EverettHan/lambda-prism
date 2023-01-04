
#ifdef TONEMAPPING_PHOTOGRAPHIC
float CIE_luminance_RGB(vec3 iColor)
{
   const vec3 CIE_luminance_weight = vec3(0.176204, 0.812985, 0.0108109);
   return vDot(iColor, CIE_luminance_weight);
}
#endif

vec3 ApplyColorProcessing(const vec3 iColor)
{
  vec3 color = iColor;
  
  //--------------------------------------------------
  // Bloom

#ifdef BLOOM
  color += vTexture(s_BloomTex, vTexCoord).xyz*cb_Bloom.u_BloomIntensity;
  color = vClamp(color, 0.0, 1e+10); // util, sinon on a des nan qui apparaissent ensuite
#endif

  //--------------------------------------------------
  // Exposure
  
#ifdef EXPOSURE_FIX
  color *= cb_Exposure.u_Exposure; // u_Exposure = 2^exposure

#elif  EXPOSURE_AUTO
  color *= vTexelFetch(s_ExposureTex, 0, 0).x;

#endif
  
  //--------------------------------------------------
  // Vignetting

#ifdef VIGNETTING_PHOTOGRAPHIC
  // L'intensité lumineuse diminue selon le carré de la distance parcourue
  // en se basant la dessus et avec pythagore, on obtient la diminuation
  // de l'intensité sur la capteur
  // Apres, il y a un coef de vignetting qui depend fortement de la lentille et de l'aperture

  vec2 pos = vTexCoord.xy;
  pos = pos*cb_Vignetting_Auto.u_ViewportToViewpointCoord.zw+cb_Vignetting_Auto.u_ViewportToViewpointCoord.xy;
  pos = pos - 0.5;

  pos.y *= cb_Vignetting_Auto.u_ViewpointSize.w; // Ratio Height/Width

  float focalLenght = cb_Vignetting_Auto.u_CameraFocalLength;
  float sensorSize  = cb_Vignetting_Auto.u_CameraSensorSize.y; 
  
  float f2 = focalLenght*focalLenght;

  color *= pow(f2/(sensorSize*sensorSize*(pos.x*pos.x+pos.y*pos.y)+f2), cb_Vignetting.u_Power);
#endif
    
  //--------------------------------------------------
  // Tone Mapping

#ifdef TONEMAPPING_REINHARD
   // Reinhard
  color.xyz = color.xyz/(1+color.xyz);

#elif   TONEMAPPING_FILMICALU
   // FIlmicALU
  vec4 tmpCol = vec4(color.xyz, cb_ToneMapping.u_W);

  tmpCol = ((tmpCol*(cb_ToneMapping.u_A*tmpCol+cb_ToneMapping.u_C*cb_ToneMapping.u_B)+cb_ToneMapping.u_D*cb_ToneMapping.u_E)
    /(tmpCol*(cb_ToneMapping.u_A*tmpCol+cb_ToneMapping.u_B)+cb_ToneMapping.u_D*cb_ToneMapping.u_F))
    -cb_ToneMapping.u_E/cb_ToneMapping.u_F;
  
  color.xyz = tmpCol.xyz/tmpCol.w;
  
#elif   TONEMAPPING_PHOTOGRAPHIC
  color.xyz *= cb_ToneMapping.u_ColorCorrection.xyz;
  color.xyz *= (color.xyz * cb_ToneMapping.u_BurnHighlights + 1.0) / (color.xyz + 1.0);
  color.xyz = vMix(vec3(CIE_luminance_RGB(color.xyz)), color.xyz, cb_ToneMapping.u_Saturation);

  float intens = CIE_luminance_RGB(color.xyz);
  if(intens < 1.0f)
  {
    float tm_crush_blacks = cb_ToneMapping.u_CrushBlacks+cb_ToneMapping.u_CrushBlacks+1.0;

    intens = vSqrt(intens);
    float oms2 = 1.0 - intens;
    color.x = color.x*intens + pow(color.x,tm_crush_blacks)*oms2;
    color.y = color.y*intens + pow(color.y,tm_crush_blacks)*oms2;
    color.z = color.z*intens + pow(color.z,tm_crush_blacks)*oms2;
  }

#endif

  //--------------------------------------------------
  // Gamma Correction

#ifdef GAMMACORRECTION
  color = vPow(color, vec3(1.0/cb_GammaCorrection.u_GammaCorrection));
#endif

  return color;
}

void main(void)
{
  vec4 color = vec4(0,0,0,0);

#ifdef MSAA_RESOLVE
  ivec2 iTexCoord = ivec2(vTexCoord * textureSize(s_SourceTex));
  for (int i=0; i<MSAA; i++)
  {
	  vec4 tmpColor = vTexelFetch(s_SourceTex, iTexCoord, i);

#if MSAA_RESOLVE==1
    color.xyz += vClamp(ApplyColorProcessing(tmpColor.xyz), 0, 1);
#else
    color.xyz += ApplyColorProcessing(tmpColor.xyz);
#endif

    color.w += tmpColor.w;
  }
  color *= (1.0/MSAA);
#else
#ifdef MSAA
  ivec2 iTexCoord = ivec2(vTexCoord*textureSize(s_SourceTex));
  color = vTexelFetch(s_SourceTex, iTexCoord, gl_SampleID);
#else
  color = vTexture(s_SourceTex, vTexCoord);
#endif
  color.xyz = ApplyColorProcessing(color.xyz);
#endif
  
  FRAGCOLOR = color;
}


