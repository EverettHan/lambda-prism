void main()
{	
  vec3 viewDir  = vNormalize(vRay);

#if defined(SUN_MODE ) && SUN_MODE == 1
  // Globe
  vec3  sunColor  = vec3(0.9911, 0.8308, 0.6172);
  float sunFactor = vSmoothstep(0.9994, 0.9999, vDot(viewDir, cb_Sun.u_SunDirection));
  vec3  sun       = sunFactor * sunColor * 60.0;
  float sunAlpha  = sun.x;

#elif defined(SUN_MODE ) && SUN_MODE == 2
  // CATVisAmbiance API
  // sun's angle = 0.5334 degrees
  float sunFactor = vSmoothstep(0.999983, 0.99998916647, vDot(viewDir, cb_Sun.u_SunDirection));

  vec3  sunColor  = vec3(1.0, 1.0, 1.0);
  vec3  sun       = sunFactor * sunColor * 75;
  float sunAlpha  = 1.0;
  
#else
  // LRE

  float EdotL = vMin(vDot(viewDir, -cb_Sun.u_SunDirection), 0.99999);
	float g = -0.9996;
	float g2 = g * g;
	float intensity = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + EdotL * EdotL) / vPow(1.0 + g2 - 2.0 * g * EdotL, 1.5);
  
#ifndef GLES2Platform
	if(isnan(intensity))
	{
		intensity = 10000.0;
	}
#endif
  vec3  sun       = vec3(intensity);
  float sunAlpha  = 1.0;
#endif

  sun *= cb_BgSun.u_SunBoost;
  FRAGCOLOR = vec4(sun, sunAlpha);

}
