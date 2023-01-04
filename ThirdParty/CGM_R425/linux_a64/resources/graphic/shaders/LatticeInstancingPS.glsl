vec3 ComputeAlbedo()
{
	return outcolor.rgb;
}

float ComputeOpacity()
{
	return outcolor.a;
}

vec3 ComputeSpecularReflectance()
{
	return vec3(0.4, 0.4, 0.4); // issue with specular: <<multiplication by "0.04" is new required.>>, check with LIA
}

vec3 ComputeViewNormal()
{
	return customNormal;
}

