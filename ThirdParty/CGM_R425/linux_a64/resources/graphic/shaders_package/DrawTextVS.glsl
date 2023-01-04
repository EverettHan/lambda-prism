// TODO : XML EFFECTS MIGRATION !

#ifndef GLES2Platform

#ifndef SHADER_BUILDER
#version 420
#endif

in vec3 _SBPosition;
in vec2 _SBTexCoord0;

out vec4 vPosition;
out vec2 vTexCoord;

#else

attribute vec3 _SBPosition;
attribute vec2 _SBTexCoord0;

varying vec4 vPosition;
varying vec2 vTexCoord;

#endif

void main(void)
{
  vec2 vRatio = vec2(cb_cbDrawText.u_FontAtlasSize.x / cb_cbDrawText.u_ViewportSize.x, cb_cbDrawText.u_FontAtlasSize.y / cb_cbDrawText.u_ViewportSize.y);

  vPosition = vec4(_SBPosition, 1.0);
    
  // Make the font squared for any viewport aspect ratio
  vPosition.xy *= vRatio * cb_cbDrawText.u_Scale;
  
  // Translate
  vPosition.xy += (cb_cbDrawText.u_Position);
  
  // Get the texture coordinates
  vTexCoord = vec2(_SBTexCoord0.x, 1.0 - _SBTexCoord0.y);
  
  // Get the final position
  gl_Position = vPosition;
  
}
