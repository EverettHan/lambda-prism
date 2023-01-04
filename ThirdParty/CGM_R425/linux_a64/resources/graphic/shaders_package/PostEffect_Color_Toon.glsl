void main(void)
{ 
  vec4 resCol = vec4(0.0);
  if (IsBackground(vTexCoord)==false)
  {   
	  vec3 col  = GetColor(vTexCoord).xyz;  
	  col = ConvertRGBToHSV(col.xyz);
    float value = col.z;
    col.z = 1.0;
	  col = ConvertHSVToRGB(col);

    if (value<cb_PostEffect.u_S0)         col *= cb_PostEffect.u_V0;
    else if (value<cb_PostEffect.u_S1Min) col *= vMix(cb_PostEffect.u_V0, cb_PostEffect.u_V1, (value-cb_PostEffect.u_S0)/(cb_PostEffect.u_S1Min-cb_PostEffect.u_S0));
    else if (value<cb_PostEffect.u_S1Max) col *= cb_PostEffect.u_V1;
    else if (value<cb_PostEffect.u_S2Min) col *= vMix(cb_PostEffect.u_V1, cb_PostEffect.u_V2, (value-cb_PostEffect.u_S1Max)/(cb_PostEffect.u_S2Min-cb_PostEffect.u_S1Max));
    else if (value<cb_PostEffect.u_S2Max) col *= cb_PostEffect.u_V2;
    else if (value<cb_PostEffect.u_S3)    col *= vMix(cb_PostEffect.u_V2, cb_PostEffect.u_V3, (value-cb_PostEffect.u_S2Max)/(cb_PostEffect.u_S3-cb_PostEffect.u_S2Max));
    else                                  col *= cb_PostEffect.u_V3;

    resCol = vec4(col, 1.0);
  }

  FRAGCOLOR = resCol;
}

