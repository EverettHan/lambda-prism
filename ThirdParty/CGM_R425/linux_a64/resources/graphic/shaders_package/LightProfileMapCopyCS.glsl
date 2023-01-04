#ifdef SourceIsArray
layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
#else
layout (local_size_x = 16, local_size_y = 16) in;
#endif

//layout(binding = 0) uniform restrict writeonly image2DArray profileMap;

//Start the compute shader body
void main() 
{
  ivec3 storePos = ivec3(vGetGlobalInvocationID().xy, vGetGlobalInvocationID().z+int(cb_LightProfileMapCopy.u_SliceStart));
  vec2 texCoord = vec2(vGetGlobalInvocationID().xy) / vec2(imageSize(profileMap).xy);
#ifdef SourceIsArray
  float intensity = texture(sourceMapArray, vec3(texCoord, float(vGetGlobalInvocationID().z))).r;
#else
  float intensity = texture(sourceMap, texCoord).r;
#endif

  imageStore(profileMap, storePos, vec4(intensity));  
}
