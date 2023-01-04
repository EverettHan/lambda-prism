// This shader is not used as PDSFX so we force "ComputeVaryingValues" function call at the 'main' function end
#define _PDSFX1_VS_Varyings

void ComputeVaryingValues()
{ 
  vec4 viewPos = vec4(vGetPosition().xyz, 1.0);
  viewPos = vGetWorldViewMatrix() * viewPos;
  vec4 position = vGetProjMatrix() * viewPos;

  // passage dans le monde ecran
  // en utlisant le hack avec le floor pour avoir le bon point de rasterization
  position.xy  = position.xy / position.w;
  position.xy = vFma(position.xy, vec2(0.5), vec2(0.5)); 
  position.xy = vFloor(position.xy * cb_Viewport.u_ViewportSize) + 0.5;

  // ajout de l'offset
  position.xy += cb_cbVolImagePixelMaterial.u_ImageOffset;

  // stockage du point de rasterization de l'image pour l'utiliser dans le PixelShader
  vTexCoord.xy = position.xy;
  
  // calcul de la position du vertex dans l'espace ecran
  position.xy += vGetTexCoord().xy * (cb_cbVolImagePixelMaterial.u_ImageSize);

  // retour au monde view
  position.xy *= cb_Viewport.u_PixelSize;
  position.xy = vFma(position.xy, vec2(2.0), vec2(-1.0));
  position.xy = position.xy*position.w;
  
  gl_Position = position; // PDSFX blacklist check is not performed
}
