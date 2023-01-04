//uniform sampler2D s_Cloud;

float GetCloudDensity(const vec2 iUV)
{
  vec2 uv = (cb_Cloud.u_UVTransfo * vec4(iUV,0,1.0)).xy;
  uv.xy = uv.xy*0.5+0.5;

  float densitymax = cb_Cloud.u_DensityMax;

#if defined CLOUD_CENTRAL_CLIPPING
  float d  = iUV.x*iUV.x+iUV.y*iUV.y;
  float d1 = cb_Cloud.u_CentralClipping_Begin;
  float d2 = cb_Cloud.u_CentralClipping_End;
  densitymax *= vSmoothstep(d1*d1, d2*d2, d);
#endif
 
  float density = vTexture(s_Cloud, uv).x;
  density = vSmoothstep(1.0-densitymax, 1.0, density);

  return density;
}


void main()
{
  vec4 col = vec4(0,0,0,0);

  vec3 ray = vNormalize(vRay);

  float tSun = IntersectPlane(vec3(0,0,0), cb_Sun.u_SunDirection.xyz, vec3(0,0,cb_Cloud.u_Height), vec3(0,0,-1));
  vec2 sunUV = (tSun*cb_Sun.u_SunDirection.xyz).xy;
  
  float t = IntersectPlane(vec3(0,0,0), ray, vec3(0,0,cb_Cloud.u_Height), vec3(0,0,-1));
  if (t>0)
  {
    vec2 uv = (t*ray).xy;
    
    float cloudDensity = GetCloudDensity(uv);
        
    //vec2 sampleRay = cb_Sun.u_SunDirection.xy * cb_Cloud.u_SampleStep;	
    vec2 sampleRay = vNormalize(sunUV-uv) * cb_Cloud.u_SampleStep;	

    float density = cloudDensity;

  	for(int i=0; i<cb_Cloud.u_NumStep; i++)
  	{
  		uv += sampleRay;

  		density += GetCloudDensity(uv);
  	}
  	
  	density = vPow(density, cb_Cloud.u_DensitySharpness);

  	float sunSkyFactor = density/(density + cb_Cloud.u_DensityBias);
  	col.xyz = vMix(cb_Sun.u_SunIntensity * cb_Cloud.u_SunBoost, cb_Cloud.u_SkyColor.xyz, sunSkyFactor);
  	
    col.w = cloudDensity*cb_Cloud.u_DensityScale;        

#ifdef CLOUD_EXPONENTIAL_FADDING
    col.w *= (vExp(-t*cb_Cloud.u_FadingFactor));
#else
    col.w *= vClamp(1-t*cb_Cloud.u_FadingFactor, 0.0, 1.0);
#endif
  }

  FRAGCOLOR = col;
}
