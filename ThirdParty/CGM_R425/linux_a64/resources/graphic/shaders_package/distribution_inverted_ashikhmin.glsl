struct distribution_inverted_ashikhmin_parameters
{
  float m_Alpha;
};

void distribution_inverted_ashikhmin_initialize(out distribution_inverted_ashikhmin_parameters oParameters, in float iRoughness)
{
  oParameters.m_Alpha = vPow2(iRoughness);
}

float cot2(in float iCosTheta)
{
  float cosTheta2 = vPow2(iCosTheta);
  return cosTheta2/(1.0-cosTheta2);
}

float invSin4FromCos(in float iCosTheta)
{
  float s = 1.0 - iCosTheta*iCosTheta;
  return 1.0/(s*s);
}

float distribution_inverted_ashikhmin(in distribution_inverted_ashikhmin_parameters iParameters, in float iNoH)
{
  float d1 = 1.0 / (PI * (1.0 + 4.0 * iParameters.m_Alpha));
  float d2 = 1.0 + 4.0 * exp(-cot2(iNoH) / iParameters.m_Alpha) * invSin4FromCos(iNoH);
  return d1*d2;
}
