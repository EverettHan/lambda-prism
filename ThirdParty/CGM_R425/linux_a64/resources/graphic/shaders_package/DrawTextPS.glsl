#ifndef GLES2Platform
in vec2 vTexCoord;
layout(location = 0) out vec4 vFragColor;
#else
varying vec2 vTexCoord;
#define vFragColor gl_FragColor
#endif

void main()
{
  vec4 colorText  = vTexture(sourceTex, vTexCoord);
  float l =  vDot(vec3(0.3, 0.6, 0.1), colorText.rgb);
    
  vec4 color;

  float a = cb_cbDrawText.u_BackgroundColor.a;
  color.a = (1.0-l)*(1.0-a);
  
  color.rgb = l*cb_cbDrawText.u_Color.rgb + (1.0-l)*a*cb_cbDrawText.u_BackgroundColor.rgb;
    
  vFragColor = color;
}
