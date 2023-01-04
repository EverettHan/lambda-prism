
// TODO
// Ce shader devra etre le base shader pour tous les types de blur possible
// sampling:
//  * directionnel
//  * poisson
// ponderation:
//  * lineaire
//  * carré
//  * cubic
//  * gaussien

/*float CalcGaussianWeight(int sampleDist, float sigma)
{
	float g = 1.0f / vSqrt(2.f * 3.14159 * sigma * sigma);
	return (g * vExp(-(sampleDist * sampleDist) / (2 * sigma * sigma)));
}

void main(void)
{
  ivec2 texSize = vTextureSize(sourceTex, 0);
  vec2 texSizef = vec2(1.0f/texSize.x, 1.0f/texSize.y);
  vec4 color = vec4(0.0f);
  float sigma = 0.8f;

  for(int i = -6; i <= 6; i++)
  {
    float weight = CalcGaussianWeight(i, sigma);
    vec2 texCoord = vTexCoord + i * texSizef * cb_cbPostEffect_Blur.Direction;
    vec4 sampleCol = vTexture(sourceTex, texCoord);
    color += sampleCol * weight;
  }

  fragColor = color;
}*/
