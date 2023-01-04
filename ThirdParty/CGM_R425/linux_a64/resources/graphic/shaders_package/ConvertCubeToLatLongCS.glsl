//Defines local size
layout (local_size_x = 16, local_size_y = 16) in;

//layout(binding = 0) uniform coherent writeonly image2D LatLongMap;

float _ConvertLinearToSRGB(float iValue)
{
  float value = iValue;

  if (iValue <= 0.0031308f)
    value = value*12.92f;
  else
    value = 1.055f*pow(value, 0.41666f) - 0.055f;

  return value;
}


//Start the compute shader body
void main() 
{
  ivec2 storePos   = ivec2(gl_GlobalInvocationID.xy);

  ivec2 size = imageSize(LatLongMap);
  
  vec2 texCoord = vec2(storePos) / vec2(size);
  texCoord.x += cb_ConvertCubeToLatLong.u_ThetaOffset;
  
  vec3 r = ComputeDirectionFromTexCoord(texCoord);
  
  vec4 color = vec4(vTexture(CubeMap, r).xyz, 1);  

 #ifdef SRGB
  color.r = _ConvertLinearToSRGB(color.r);
  color.g = _ConvertLinearToSRGB(color.g);
  color.b = _ConvertLinearToSRGB(color.b);
#endif
  
  imageStore(LatLongMap, storePos, color);  
}
