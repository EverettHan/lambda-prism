vec4 MotionBlur(float strength,vec2 velocityVec)
{
	vec4 finalColor = vTexture(CurrentColorBuffer, vTexCoord);
	  
	float maxSamples = 5.0;
	velocityVec = velocityVec*strength;
	  
	for (float i = 1.0; i < maxSamples; i += 1.0)
	{
		finalColor += vTexture(CurrentColorBuffer, vTexCoord + velocityVec * i / maxSamples);
	}
	return finalColor/maxSamples;
}

void main(void)
{
	vec2 velocityVec = GetEffectTexture(MotionVectorMap,vTexCoord).xy;
	FRAGCOLOR =  MotionBlur(cbMotionBlur.MotionBlurSize,velocityVec);
}

