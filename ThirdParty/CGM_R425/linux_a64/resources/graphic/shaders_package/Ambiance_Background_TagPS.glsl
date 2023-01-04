
void main()
{
  vec3 ray = vNormalize(vRay);

  float u = 0;
  float v = 0;

  vec3 tmp = vNormalize(vec3(ray.x, ray.y, 0));

  v = ray.z*0.5+0.5;
  v = (v-0.5) * cbBackground.V_Scale +0.5 + cbBackground.V_Delta;

  u = 0.5*vAcos(tmp.y)/3.141;
  u = (tmp.x>=0 ? u : 1-u); 
  u = vMod(u * cbBackground.Number, 1);
  u = (u-0.5) * cbBackground.U_Scale + 0.5 + cbBackground.U_Delta;

  vec4 col = vTexture(Texture, vec2(u,v));

  FRAGCOLOR = col;

 /* 
 // methode plus rapide si probleme de perf
 vec2 uv = vec2(0, -vRay.z);

  float x = vAbs(vRay.x);
  float y = vAbs(vRay.y);
  float max = 0;
  if (x>y) 
  {
     uv.x = vSign(vRay.x)*vRay.y;
     max = x;
  }
  else
  {
     uv.x = -vSign(vRay.y)*vRay.x;
     max = y;
  }
  
  uv = uv/max;
    
  uv.x = vMod((uv.x+1) * cbAmbiance_Background_Tag.Number, 2)-1;

  uv = vec2(cbAmbiance_Background_Tag.U_Scale, cbAmbiance_Background_Tag.V_Scale) * uv + vec2(cbAmbiance_Background_Tag.U_Delta, cbAmbiance_Background_Tag.V_Delta);
  uv =  uv * 0.5  + 0.5;

  vec4 col = vTexture(Texture, uv);
  fragColor = col;*/
}
