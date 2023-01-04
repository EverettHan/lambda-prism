void main()
{
  vec2 texCoord = vTexCoord; 
  float z = GetZ(texCoord);

  // si on est sur les limites du frustrum on definit un near plus petit que le near ou un far plus grand que le far
  // car ensuite, on peut etre ammener a faire des test pour savoir si un point est ou non dans le frustrum
  // et si on ne fait pas ce petit trick, on peut avoir des erreurs d'arrondis lors de test
  // car le z lineaire peut passer par une texture float sur 16 bit et non pas 32.
  if (z==1.0) 
    z = cb_PostEffectAuto.u_NearFar.x + 1.01*(cb_PostEffectAuto.u_NearFar.y-cb_PostEffectAuto.u_NearFar.x);
  else if (z==0.0) 
    z = cb_PostEffectAuto.u_NearFar.y - 1.01*(cb_PostEffectAuto.u_NearFar.y-cb_PostEffectAuto.u_NearFar.x);
  else
    z = ConvertZBufferToZView(z);

  FRAGCOLOR = vec4(z);
}
