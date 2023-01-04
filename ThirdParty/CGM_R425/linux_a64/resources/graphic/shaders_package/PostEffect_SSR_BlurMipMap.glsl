#define KERNEL_SIZE 7

const float g_kernelCoef[KERNEL_SIZE] = float[] (0.002, 0.028, 0.233, 0.474, 0.233, 0.028, 0.002); 

#ifdef BLUR_HORI
  const ivec2 offsets[KERNEL_SIZE] = ivec2[KERNEL_SIZE](ivec2(-3, 0), ivec2(-2, 0), ivec2(-1, 0), ivec2(0, 0), ivec2(1, 0), ivec2(2, 0), ivec2(3, 0));
#elif defined(BLUR_VERTI)
  const ivec2 offsets[KERNEL_SIZE] = ivec2[KERNEL_SIZE](ivec2(0, -3), ivec2(0, -2), ivec2(0, -1), ivec2(0, 0), ivec2(0, 1), ivec2(0, 2), ivec2(0, 3));
#endif

void main()
{
  vec4 finalColor = vec4(0.0);
  vec2 uvs =  vTexCoord.xy / cb_PostEffect_SSR_BlurMipMap.u_uvScale;
    
  for(int i = 0 ; i < KERNEL_SIZE ; ++i)
  {
    #ifdef SSR_MAPS_ARRAY_ID
       finalColor += vTextureLod(MapWithMips, vec3(uvs + (offsets[i] * cb_PostEffect_SSR_BlurMipMap.u_pixelSize), cb_PostEffect_SSR_BlurMipMap.u_mipLevel), float(SSR_MAPS_ARRAY_ID)), cb_PostEffect_SSR_BlurMipMap.u_mipLevel) * g_kernelCoef[i];     
    #else
       finalColor += vTextureLod(MapWithMips, uvs + (offsets[i] * cb_PostEffect_SSR_BlurMipMap.u_pixelSize),cb_PostEffect_SSR_BlurMipMap.u_mipLevel) * g_kernelCoef[i]; 
    #endif
  }

  FRAGCOLOR = finalColor;
}


