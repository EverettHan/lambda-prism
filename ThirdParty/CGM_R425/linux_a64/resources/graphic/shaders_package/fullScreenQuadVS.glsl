// TODO : XML EFFECTS MIGRATION !

#ifndef GLES2Platform

#if !defined(SHADER_BUILDER) && !defined(GLESPlatform)
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
  vPosition = vec4(_SBPosition, 1.0);
	vTexCoord = vec2(_SBTexCoord0.x, 1.0-_SBTexCoord0.y);
  gl_Position = vPosition;
}
