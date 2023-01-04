#if defined(BLUR_HORI) && defined(TEXTURE_ARRAY_ID)
  #define SAMPLER_SOURCE image2DArray
  #define MULTI_SOURCE
#else //!MULTI_SOURCE
  #define SAMPLER_SOURCE image2D
#endif //MULTI_SOURCE

#if defined(BLUR_VERTI) && defined(TEXTURE_ARRAY_ID)
  #define SAMPLER_DEST image2DArray
  #define MULTI_DEST
#else //!MULTI_DEST
  #define SAMPLER_DEST image2D
#endif //MULTI_DEST

//layout(binding = 0, r32f) uniform coherent SAMPLER_SOURCE i_source;
//layout(binding = 1, r32f) uniform coherent SAMPLER_DEST i_dest;

layout (local_size_x = 16, local_size_y = 16) in;

#define KERNEL_SIZE 5

float g_kernelCoef[KERNEL_SIZE] = {0.02956, 0.236009, 0.468863, 0.236009, 0.02956}; //Sigma 0.8


void main() 
{
#ifdef BLUR_HORI
  ivec2 samplingPos[KERNEL_SIZE] = { ivec2(-2, 0), ivec2(-1, 0), ivec2(0, 0), ivec2(1, 0), ivec2( 2, 0) };
#elif defined(BLUR_VERTI)
  ivec2 samplingPos[KERNEL_SIZE] = { ivec2(0, -2), ivec2( 0, -1), ivec2(0, 0), ivec2( 0, 1), ivec2(0, 2) };
#endif
	
#ifdef TSM_BLUR
  vec4 finalColor = vec4(0.);
#else
  float finalColor = 0;
#endif //TSM_BLUR

  ivec2 storePos   = ivec2(gl_GlobalInvocationID.xy);

  for(int i = 0 ; i < KERNEL_SIZE ; ++i)
  {
    ivec2 curSamplingPos = storePos + samplingPos[i];
    #ifndef MULTI_SOURCE
    	#ifdef TSM_BLUR
		  finalColor += imageLoad(i_source, curSamplingPos) * g_kernelCoef[i]; 
		#else
		  finalColor += imageLoad(i_source, curSamplingPos).x * g_kernelCoef[i]; 
		#endif //TSM_BLUR
    #else //MULTI_SOURCE
    	#ifdef TSM_BLUR
    	  finalColor += imageLoad(i_source, ivec3(curSamplingPos, TEXTURE_ARRAY_ID)) * g_kernelCoef[i]; 	  
		#else
		  finalColor += imageLoad(i_source, ivec3(curSamplingPos, TEXTURE_ARRAY_ID)).x * g_kernelCoef[i]; 
		#endif //TSM_BLUR
    #endif //MULTI_SOURCE
  }
 
  #ifndef MULTI_DEST
  	#ifdef TSM_BLUR
	  imageStore(i_dest, storePos, finalColor);
	#else
	  imageStore(i_dest, storePos, vec4(finalColor));
	#endif //TSM_BLUR
  #else //MULTI_DEST
	#ifdef TSM_BLUR
	  imageStore(i_dest, ivec3(storePos, TEXTURE_ARRAY_ID), finalColor);
	#else
	  imageStore(i_dest, ivec3(storePos, TEXTURE_ARRAY_ID), vec4(finalColor));
	#endif //TSM_BLUR
  #endif //MULTI_DEST
  
  
  
}
