
//#define SAMPLER_SOURCE image2D
//#define SAMPLER_DEST image2D

//layout(binding = 0, r32f) uniform coherent SAMPLER_SOURCE i_source;
//layout(binding = 1, r32f) uniform coherent SAMPLER_DEST i_dest;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
  #ifdef ZMAX_HORI
  #if ESM_KERNEL_SIZE ==5
  ivec2 samplingPos[ESM_KERNEL_SIZE] =  { ivec2(-2, 0), ivec2(-1, 0), ivec2(0, 0), ivec2(1, 0), ivec2( 2, 0) };
  #elif ESM_KERNEL_SIZE ==7
  ivec2 samplingPos[ESM_KERNEL_SIZE] =  { ivec2(-3, 0),ivec2(-2, 0), ivec2(-1, 0), ivec2(0, 0), ivec2(1, 0), ivec2( 2, 0), ivec2(3, 0)};
  #endif
  #elif defined(ZMAX_VERT)
  #if ESM_KERNEL_SIZE ==5
  ivec2 samplingPos[ESM_KERNEL_SIZE] = { ivec2(0, -2), ivec2( 0, -1), ivec2(0, 0), ivec2( 0, 1), ivec2(0, 2) };
  #elif ESM_KERNEL_SIZE ==7
  ivec2 samplingPos[ESM_KERNEL_SIZE] = { ivec2( 0, -3),ivec2(0, -2), ivec2( 0, -1), ivec2(0, 0), ivec2( 0, 1), ivec2(0, 2),ivec2( 0, 3) };
  #endif
  #endif
  
  ivec2 storePos   = ivec2(gl_GlobalInvocationID.xy);
  float maxZ = 0;
  for(int i = 0 ; i < ESM_KERNEL_SIZE ; ++i)
  {
    ivec2 curSamplingPos = storePos + samplingPos[i];
	maxZ = max(maxZ,imageLoad(i_source, curSamplingPos).x);
  }

   imageStore(i_dest, storePos, vec4(maxZ));
 }
