// Shadow
#ifdef GROUND_SHADOW
out vec4 vShadowTexCoord;

#ifndef GROUND_FIRST_SHADOW
#define GROUND_FIRST_SHADOW 0
#endif

void ComputeShadows(vec4 iLocalPosition)
{
  vShadowTexCoord = iLocalPosition;
}

void ComputeGroundShadowTexCoord()
{
  vec4 viewPos= vGetWorldViewMatrix() * vec4(vGetPosition(), 1.0);

  ComputeShadows(viewPos);
}
#endif
