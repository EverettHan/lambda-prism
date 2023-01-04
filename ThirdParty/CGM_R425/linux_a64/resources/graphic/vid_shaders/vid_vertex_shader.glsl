const float c_zero = 0.0;
const float c_one = 1.0; 
const int indx_zero = 0;
const int indx_one = 1;

uniform mat4 u_WVP;
uniform vec4 u_rgba;

attribute vec3 a_position;
attribute vec3 a_texcoord;
attribute vec4 a_color;

varying vec4 v_frontcolor;
varying vec2 v_texcoord;
varying float v_usingFreeTypeTexture;

void main(void)
{
  //position
  gl_Position = u_WVP * vec4(a_position.xyz, c_one);
  v_frontcolor = a_color;
  //texturing
  v_texcoord.xy = a_texcoord.xy;
  v_usingFreeTypeTexture = a_texcoord.z;
}
