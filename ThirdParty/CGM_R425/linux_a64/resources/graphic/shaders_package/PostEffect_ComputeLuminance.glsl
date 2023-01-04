
void main()
{
  vec3 color  = vTexture(s_SourceTex, vTexCoord).xyz;
  float ev    = vDot(color, vec3(0.299, 0.587, 0.114)); 
  ev          = vMax(ev, 1e-6);
    
  ev          = vLog(ev); 
     
  FRAGCOLOR = vec4(ev);
}
