#ifndef GLES2Platform
  layout(location = 0) out vec4 fragColor;

#ifdef OutputGPUPicking
  layout(location = 1) out uint gpuPickingMap;
#endif
#endif

#ifndef GLES2Platform
  #define FRAGCOLOR fragColor
#else
  #define FRAGCOLOR gl_FragColor
#endif

void main()
{
  float alpha = vTexture(atlasTexture, vTexCoord.xy).r;

#if defined(HighlightAdvanced) 
  FRAGCOLOR = vec4(1-alpha);
#else
  FRAGCOLOR.rgb = cb_cbText_Default.u_Color.rgb;
  FRAGCOLOR.a = cb_cbText_Default.u_Color.a * alpha; 
#endif

#ifdef OutputGPUPicking
  gpuPickingMap = GetGPUPickingID();
#elif OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif
}
