//layout(binding = 0, rgba8) uniform coherent image2D textureDesaturate;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
  ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);

  vec4 curColor =   imageLoad(textureDesaturate, storePos);

  float desaturateCoef = 0.80; //80%
  float L = 0.3 * curColor.r + 0.6 * curColor.g + 0.1 * curColor.b;
  
  vec4 newColor = curColor + desaturateCoef * (L - curColor);
  
  imageStore(textureDesaturate, storePos,vec4(newColor.rgb, curColor.a));
}
