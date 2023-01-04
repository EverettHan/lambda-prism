void main(void)
{ 
  vec4 color = GetColor(vTexCoord);
  
#ifdef SEUIL_WITHMAX
  float value = vMax(color.x, vMax(color.y, color.z));
#else
  float value = GetLuminance(color.xyz);
#endif

	if (value<=cb_PostEffect.u_SeuilMin)      value = cb_PostEffect.u_ValueMin;
	else if (value>=cb_PostEffect.u_SeuilMax) value = cb_PostEffect.u_ValueMax;
	else                                      value = vMix(cb_PostEffect.u_ValueMin, cb_PostEffect.u_ValueMax,float(value-cb_PostEffect.u_SeuilMin)/float(cb_PostEffect.u_SeuilMax-cb_PostEffect.u_SeuilMin));
		
  FRAGCOLOR = vec4(value, value, value, 1.f);
}

