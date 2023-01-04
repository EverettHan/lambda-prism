#ifndef GLES2Platform
layout(location = 0) out vec4 fragColor;
#define FRAGCOLOR fragColor
#else
#define FRAGCOLOR gl_FragColor
#endif
