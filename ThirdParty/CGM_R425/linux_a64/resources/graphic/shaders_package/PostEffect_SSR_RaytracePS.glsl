
float ClipByFrustum(Ray ray)
{
  float t = uintBitsToFloat(0x7f7fffff);
  for (uint k = 0; k < 6; ++k)
  {
	 ClipByPlane(ray, cb_cbFrustumPlanes.View[k], t);
  }
  return t;
}

void main()
{
  vec4 f0Rough = GetEffectTexture(F0RoughnessMap, vTexCoord.xy);
  vec3 f0 = f0Rough.rgb;
  float roughness = f0Rough.a;	
  if (roughness > 0.99)
  {
    FRAGCOLOR = vec4(0.0);
    return;
  }

  roughness = vMax(roughness, 0.025);
  vec3 normal = GetNormal(vTexCoord.xy).xyz;
  if (vDot(normal, normal) < 0.01)
  {
    FRAGCOLOR = vec4(0.0);
    return;
  }

  vec3 viewVect = UVToViewVect(vTexCoord.xy);
  vec3 specular = OptimizedSchlickFresnel(f0, vec3(1.0), vAbs(vDot(normal, viewVect)));
  if (vDot(specular, specular) < 0.0001)
  {
    FRAGCOLOR = vec4(0.0);
    return;
  }
   
  vec4 radColor = vec4(0.0);
  const float prec = cb_PostEffect_SSR_Radiance.u_RayMarchingPrecision;
  vec2 xi = vec2(0.0); // random variable for microfacet distribution		
 // xi =  vTexture(HaltonTex, vTexCoord.xy  * cb_PostEffectAuto.u_ViewpointSize.xy / 1024.).xy;
   xi =  vTexture(HaltonTex, (vTexCoord.xy  + cb_PostEffectAuto.u_JitterOffset.yx) * cb_PostEffectAuto.u_ViewpointSize.xy / 1024.).yx; //changes per frame and per pixel
  xi.y = vMix(xi.y, 0.0, 0.8);// BRDF Bias 0.8 to reduce noise

  vec4 H = ImportanceSampleWithPDF(xi, roughness, normal);
  vec3 reflVect = vReflect(viewVect, H.xyz);

  float RoN = vDot(reflVect, normal);
  if (RoN < 0.0) reflVect = reflVect - 2.0 * normal * RoN;

  Ray ray;
  {
    ray.Dir = reflVect;
	#ifdef SSR_GroundCorrection
	  float z = GetZ(vTexCoord.xy);
      if ( z < 0.0001 || z > 0.9999 )
      {
        // Compute ray from ground plane
        ray.Start = GetViewRayPlaneInter(vTexCoord.xy, viewVect, cb_GroundPlane.ViewEquation);
        #ifdef SSR_GroundInDepth
        // Compute ray from near/far plane (when "useGroundBe" is disabled)
        float inter = ClipByFrustum(ray);
        ray.Start += 1.001 * inter * ray.Dir;
        #endif
      }
    else
	  #endif
	  {
        ray.Start = UVToViewPos(vTexCoord.xy);
      }
  }

  #ifdef SSR_GroundBE
   const float sceneSize = 2.0 * cb_Ground_Auto.u_GroundRadius;
  #else
   const float sceneSize = 2.0 * cb_PostEffectAuto.u_SceneRadius;
  #endif
  const float maxRayLength = sceneSize * cb_PostEffect_SSR_Radiance.u_SceneRadiusRateFalloff.y;

  float t = ClipByFrustum(ray);

  vec3 hitPos;
  vec2 hitUV;
  bool hit = false;
  if ( t > 0.0 )
  {
	  vec3 outPos = ray.Start + vMin(t, maxRayLength) * ray.Dir;
	  vec2 uv0 = ViewPosToUV(ray.Start);
	  vec2 uv1 = ViewPosToUV(outPos);
	  float depthDiscontinuity = cb_PostEffect_SSR_Radiance.u_DepthDiscontinuity;
	  float rayZBias = cb_PostEffect_SSR_Radiance.u_RayZBias;
	  vec2 rtSize = vec2(1.0 / (cb_PostEffect_SSR_Radiance.u_ZMapPixelSize.x), 1.0 / (cb_PostEffect_SSR_Radiance.u_ZMapPixelSize.y));
	  int rayMarchingLowRes = cb_PostEffect_SSR_Radiance.u_RayMarchingLowRes;

	  #ifdef SSR_ZHierarchyRayMarching
	  if(roughness < 0.7)
	  {
		hitUV = hierarchicalRayMarching(uv0, uv1, ray.Start.z, outPos.z, depthDiscontinuity, rayZBias, hitPos, hit);	
	  }
	  else
	  #endif
	  {
	     hitUV = linearRayMarching(prec, uv0, uv1, ray.Start.z, outPos.z, rtSize, rayMarchingLowRes, depthDiscontinuity, rayZBias, hitPos, hit);
	  }
  }

  radColor = vec4(hitUV, H.w, float(hit));

  FRAGCOLOR = radColor;
}
