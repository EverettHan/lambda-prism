#version 130
uniform mat4 u_WVP;
uniform vec4 u_rgba;

in vec3 a_position;
in vec3 a_texcoord;
in vec4 a_color;

out vec4 v_frontcolor;
out vec2 v_texcoord;
out float v_usingFreeTypeTexture;

void main(void)
{
  //position
  gl_Position = u_WVP * vec4(a_position.xyz, 1.0);
  v_frontcolor = a_color;
  //texturing
  v_texcoord.xy = a_texcoord.xy;
  v_usingFreeTypeTexture = a_texcoord.z;
}
