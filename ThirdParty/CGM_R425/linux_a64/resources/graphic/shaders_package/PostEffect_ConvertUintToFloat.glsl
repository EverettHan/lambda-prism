// TODO : XML EFFECTS MIGRATION !

void main()
{
  //uvec4 texelValue = texture(sourceTex, vTexCoord);
  float depth = vUintBitsToFloat(vTexture(s_SourceTex, vTexCoord).x);
  
  vec4 finalColor = vec4(depth, depth, depth, 1);
  
  FRAGCOLOR = finalColor;
}
