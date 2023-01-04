#ifdef Lighting


#if defined(ShadowMap) && defined(CloudShadows)

struct Intersection
{
	bool  Intersects;
	float d;         // Along ray
};

float eps = 0.001;	// error epsilon
Intersection SphereIntersect(vec3 rayOrigin, vec3 rayDirection, float RadiiSquared)
{
	vec3 rayOriginSquared = rayOrigin * rayOrigin;
	vec3 v = -rayOrigin;
	float b = vDot(v, rayDirection);
	float disc = (b*b) - vDot(v, v) + RadiiSquared;
	Intersection i;
	if (disc <= 0)
	{
		i.Intersects = false;
		i.d = 0;
		// big value for min test
		i.d = 100000000;
	}
	else
	{

		disc = sqrt(disc);
		float t2 = b + disc;

		if (t2 <= eps)
		{
			i.Intersects = false;
			i.d = 0;
			// big value for min test
			i.d = 100000000;
		}
		else
		{
			float t1 = b - disc;
			if ((t1 > eps) && (t1 < t2))  // return nearest intersection
			{
				i.Intersects = true;
				i.d = t1;

			}
			else
			{
				i.Intersects = true;
				i.d = t2;
			}
		}

	}
	return i;
}


vec2 ComputeTextureCoordinates(vec3 normal)
{
	float OneOverPI = 0.318309886f;
	float OneOver2PI = 0.159154943f;
	return vec2((-atan(normal.x, normal.z) * OneOver2PI - 1), -(asin(normal.y) * OneOverPI + 0.5));
}


vec3 LatLonTo3DNormalized(float Lat, float Lon)
{
	float newLat = -2 * PI*Lat / 360.0f;
	float newLon = 2 * PI*Lon / 360.0f;
	return vec3(cos(newLat) * sin(newLon), -sin(newLat), -(cos(newLat) * cos(newLon)));
}

float GetCloudSpeed()
{
	return cb_CloudShadow.u_cloudSpeed;
}


float GetCloudDensitySimple(vec3 worldPosition)
{

	float cloudSpeed = GetCloudSpeed();
	float cloudShadowFactor = 5.0f;


	vec3 normal = vNormalize(worldPosition);
	float Height = vLength(worldPosition);

	vec2 uv = ComputeTextureCoordinates(normal);

	uv += cloudSpeed * vec2(1, 0);
	float lat = 180.0f*uv.y - 90.0f;
	float lon = 360.0f*uv.x - 180.0f;
	worldPosition = Height * LatLonTo3DNormalized(lat, lon);
	// update normal
	normal = normalize(worldPosition);
	normal = vec3(-normal.x, -normal.y, normal.z);
	float alpha = vTextureLod(CloudCoverCM, normal, 0).a;
	float minalpha = 0.02;
	alpha = vSmoothstep(minalpha, 0.6f, alpha) - minalpha;
	return vClamp(cloudShadowFactor*alpha, 0.0, 1.0);
}



float GetCloudShadows(vec3 viewPos)
{
  float Rg_CLOUDS = 6370999.0; // earth's mean radius


	vec4 worldPos4 = vGetViewInvMatrix() * vec4(viewPos.x, viewPos.y, viewPos.z, 1.0f);
	vec3 worldPos = worldPos4.xzy;

	// hard-coded parameters (cf clouds post process)
	float Thickness = 8000.0f;
	float HeightCloud = 10000.0f;



#ifdef NumberOfDirLights
	float shadow = 1.0f;
	if (NumberOfDirLights > 0)// compute this only if we have sun and moon
	{
		vec3 worldSunDir = vec3(0);
		vec3 worldMoonDir = vec3(0);

		// sun should be 1st light
		vec4 sundir4 = vGetViewInvMatrix() * vec4(-_sbLightsSB2.DirDirection[0].x, -_sbLightsSB2.DirDirection[0].y, -_sbLightsSB2.DirDirection[0].z, 0.0);
		vec4 moondir4 = vGetViewInvMatrix() * vec4(-_sbLightsSB2.DirDirection[1].x, -_sbLightsSB2.DirDirection[1].y, -_sbLightsSB2.DirDirection[1].z, 0.0);


		worldSunDir = sundir4.xzy;
		worldMoonDir = moondir4.xzy;



		float secondSphereHeight = Rg_CLOUDS + HeightCloud + Thickness;
		float RadiiSquared = secondSphereHeight * secondSphereHeight;

		float EarthSunShadow = vSmoothstep(-0.05, 0.05, vDot(vNormalize(worldPos), worldSunDir));
		float EarthMoonShadow = vSmoothstep(-0.15, 0.15, vDot(vNormalize(worldPos), worldMoonDir));

		// same formula in clouds
		float shadowfactor = EarthSunShadow + (1 - EarthSunShadow)*EarthMoonShadow;
		vec3 lightDir = EarthSunShadow * worldSunDir + (1 - EarthSunShadow)*worldMoonDir;


		Intersection i = SphereIntersect(worldPos, lightDir, RadiiSquared);

		float distToEarthCenter = vLength(worldPos);

		// shadows only under bottom 
		float fadedist = 1000.0f;//1000m
		float underClouds = vClamp(((Rg_CLOUDS + HeightCloud) - distToEarthCenter) / fadedist, 0.0, 1.0);
		if ((i.Intersects))
		{
			// earth shadow
			vec3 topPosition = worldPos + (i.d * lightDir);
			float clouddensity = underClouds * GetCloudDensitySimple(topPosition)*shadowfactor;
			shadow = vClamp(1.0f - clouddensity, 0.0, 1.0);
		}

		shadow = 0.05 + shadow; // we inject some ambient light into cloud shadow term (for contrast with standard shadows)

	}
	return shadow;
#else
	// no planet shadows
	return 0.0f;
#endif
}

#endif



#endif // Lighting
