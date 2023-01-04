const float c_zero = 0.0;
const float c_one = 1.0; 
const int indx_zero = 0;
const int indx_one = 1;

uniform sampler2D u_textureUnit;
uniform sampler2D u_freeTypeTextureUnit;
uniform int       u_texturing2DEnable;
uniform int       u_alphaTexturing2DEnable;

uniform float u_gamma;

varying vec4 v_frontcolor;
varying vec2 v_texcoord;
varying float v_usingFreeTypeTexture;

layout(location = 0) out vec4 fragColor;

void main(void)
{
  //main color
  vec4 fragColor=v_frontcolor;
  
  //texturing
  vec4 texelValue = vec4(c_one,c_zero,c_zero,c_one);
  if(u_texturing2DEnable > 0)
  {
    if (v_usingFreeTypeTexture < 0.5)
    {
      texelValue=texture2D(u_textureUnit,v_texcoord.xy);
      if (u_alphaTexturing2DEnable == 0)
      {
        texelValue.a=1.0;
      }
      //Modulate
      fragColor = texelValue * fragColor; 
    }
    else
    {
    // alpha mask from luminance texture
      float mask = texture2D(u_freeTypeTextureUnit,v_texcoord.xy).r;
      // mask gamma correction
      mask = pow(mask, u_gamma);
      fragColor.a *= mask; 
    }
  }
  //final color
  fragColor = fragColor;
}
