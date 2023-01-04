
void main(void)
{
  float u_strength = cb_FOVDistorsion.u_strength;
  float u_height = cb_FOVDistorsion.u_height;
  float u_aspectRatio = cb_FOVDistorsion.u_aspectRatio;
  float u_cylindricalRatio = cb_FOVDistorsion.u_cylindricalRatio;
  
  u_strength = 0.5;
  u_height = 0.46153333;//cb_FOVDistorsion.u_height;
  u_aspectRatio = 0.9;
  u_cylindricalRatio = 0.6;
  
  float scaledHeight = u_strength * u_height;
  float cylAspectRatio = u_aspectRatio * u_cylindricalRatio;
  float aspectDiagSq = u_aspectRatio * u_aspectRatio + 1.0;
  float diagSq = scaledHeight * scaledHeight * aspectDiagSq;
  vec2 signedUV = (2.0 * vTexCoord.xy + vec2(-1.0, -1.0));

  float z = 0.5 * sqrt(diagSq + 1.0) + 0.5;
  float ny = (z - 1.0) / (cylAspectRatio * cylAspectRatio + 1.0);

  vec2 vUVDot = sqrt(ny) * vec2(cylAspectRatio, 1.0) * signedUV;
  vec3 vUV = vec3(0.5, 0.5, 1.0) * z + vec3(-0.5, -0.5, 0.0);
  vUV.xy += vTexCoord.xy;
  vec3 uv = dot(vUVDot, vUVDot) * vec3(-0.5, -0.5, -1.0) + vUV;
  
  vec2 finalUV = uv.xy / uv.z;
  finalUV.y = (1.0 - finalUV.y);
  FRAGCOLOR = vTexture(s_EyeMap, finalUV);
  
  //FRAGCOLOR = vTextureProj(s_EyeMap, uv);
  
  //FRAGCOLOR = vec4(1, 0, 1, 1.0);
  //FRAGCOLOR = vec4(0.1 * z, 0.1 * z, 0.1 * z, 1.0);
  //FRAGCOLOR = vTexture(s_EyeMap, vTexCoord.xy);
  //FRAGCOLOR = vec4(vTexCoord.xy, 0, 1);
}
