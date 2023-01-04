layout (location = 0) out vec4 oFragColor;

#ifdef OutputGPUPicking
  layout(location = 1) out uint gpuPickingMap;
#endif

void main()
{    
  oFragColor = vec4(1, 1, 1, 1); 

#ifdef OutputGPUPicking
	gpuPickingMap = GetGPUPickingID();
#elif OutputGPUPickingImage
  imageStore(GPUPickingImage, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
#endif
}
