void main(void)
{    
  vec4 col = GetColor(vTexCoord);
  float luminance = GetLuminance(col.xyz);

	vec2 screenCoord  = vTexCoord*cb_PostEffect.u_Scale;
	vec2 screenCoord2 = vec2(screenCoord.y, screenCoord.x);
	vec2 screenCoord3 = vec2(screenCoord.x*0.707-screenCoord.y*0.707, screenCoord.x*0.707+screenCoord.y*0.707);
		
	float visbility = 1.f;
	if (luminance<cb_PostEffect.u_S0) visbility *= vSaturate((luminance+cb_PostEffect.u_SMini)/cb_PostEffect.u_S0);
	if (luminance<cb_PostEffect.u_S1) visbility *= vSaturate(vTexture(s_PenTexture, screenCoord).x  + vSaturate((luminance-cb_PostEffect.u_S0)/(cb_PostEffect.u_S1-cb_PostEffect.u_S0)));
	if (luminance<cb_PostEffect.u_S2) visbility *= vSaturate(vTexture(s_PenTexture, screenCoord2).x + vSaturate((luminance-cb_PostEffect.u_S1)/(cb_PostEffect.u_S2-cb_PostEffect.u_S1)));
	if (luminance<cb_PostEffect.u_S3) visbility *= vSaturate(vTexture(s_PenTexture, screenCoord3).x + vSaturate((luminance-cb_PostEffect.u_S2)/(cb_PostEffect.u_S3-cb_PostEffect.u_S2)));
	
	col.xyz = vec3(luminance);
  col.xyz = (1.0-visbility) * col.xyz + visbility;
  col.w = 1.f;
  
  FRAGCOLOR = col;
}

