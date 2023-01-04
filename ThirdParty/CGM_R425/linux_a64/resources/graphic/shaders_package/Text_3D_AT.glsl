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
  float dist = vTexture(atlasTexture, vTexCoord.xy).r;

  float soft_t = vFwidth(dist);
  float alpha = vSmoothstep(0.5 - soft_t, 0.5 + soft_t, dist);
  
  float outline_min = 0.5 - cb_cbText_3D_AT.u_OutlineThreshold;
  float outline_max = 0.5 + cb_cbText_3D_AT.u_OutlineThreshold;
  float weight = 1.0;

  if(dist > outline_min && dist < outline_max)
  {
    if(dist <= 0.5)
      weight = vSmoothstep(outline_min, 0.5, dist);
    else
      weight = vSmoothstep(0.5, outline_max, dist);
  }
  
  vec4 color;
  color = cb_cbText_3D_AT.u_Color;
  color = mix(cb_cbText_3D_AT.u_OutlineColor, color, vec4(weight));

  FRAGCOLOR = vec4(color.rgb, color.a * alpha);

#ifdef OutputGPUPicking
  gpuPickingMap = GetGPUPickingID();
#elif OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif
}
