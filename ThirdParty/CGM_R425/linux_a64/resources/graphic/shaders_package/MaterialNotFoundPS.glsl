//---------------------------------------------
// color

#ifndef GLES2Platform
  layout(location = 0) out vec4 fragColor;
  #define FRAGCOLOR fragColor
  #if defined(OutputNormalMap)
    layout(location = 1) out vec4 fragNormal;
    #define FRAGNORMAL fragNormal
  #endif
#else
  #define FRAGCOLOR gl_FragColor
#endif


void main() 
{
  ivec2 coord = ivec2(gl_FragCoord.xy);
  ivec2 size = vTextureSize(s_ErrorTexture, 0);
  coord = coord % size;

  vec4  color = vTexelFetch(s_ErrorTexture, coord, 0);

  //Result
	FRAGCOLOR = color; 
}
