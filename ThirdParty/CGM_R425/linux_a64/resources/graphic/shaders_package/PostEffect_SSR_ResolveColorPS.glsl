
float ClipByFrustum(Ray ray)
{
	float t = uintBitsToFloat(0x7f7fffff);
	for (uint k = 0; k < 6; ++k)
	{
		ClipByPlane(ray, cb_cbFrustumPlanes.View[k], t);
	}
	return t;
}

//GGX Importance sampling to find cone theta
float SpecularPowerToConeAngle(float roughness)
{
  float a = roughness * roughness;
  float a2 = a * a;
  float Xi = 0.5; 
  return acos(vSqrt( (1 - Xi) / ( 1 + (a2 - 1) * Xi ) ));
}

float IsoscelesTriangleBase(float adjacentLength, float coneHalfAngle)
{
  return  tan(coneHalfAngle) * adjacentLength;
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
  vec3 viewNormal = (vGetViewMatrix() * vec4(normal, 0.)).xyz;

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
  vec4 resultColor = vec4(0.0);
  float weightSum = 0.0;
  float weight = 1.0;
  float screenFadeSize = 0.1;

  float maxMipLevel = float(cb_PostEffect_SSR_Radiance.u_EyeMapMipsCount);
      
  vec3 viewPos = UVToViewPos(vTexCoord.xy);
  vec2 UV = vTexCoord.xy;
  float coneHalfAngle = SpecularPowerToConeAngle(roughness);

  vec2 offset[28] ={vec2(0, 0), vec2(-1, 0), vec2(-1, 1), vec2(0, 1), 
                    vec2(1, 0), vec2(2, 0), vec2(1, -3), vec2(2, -3),
					vec2(0, 1), vec2(-3, 1), vec2(0, 2), vec2(-3, -2),
					vec2(0, 1), vec2(0, 2), vec2(-3, 1), vec2(-3, 2),
					vec2(0, 0), vec2(-1, 0), vec2(0, -3), vec2(-1, -3),
					vec2(1, 2), vec2(2, 2), vec2(1, -2), vec2(2, -2),
					vec2(1, 0), vec2(-2, 0), vec2(1, -3), vec2(-2, -3) };

    int startIndex = 0;

  #ifdef MultiPixel_Resolve_Jitter
    startIndex = int(vMod(cb_PostEffectAuto.u_FrameIdx, 7)) * 4;
  #endif

  for(int i=0; i < 4; i++)
  {
	  vec2 offsetUV = offset[startIndex + i] * vec2((1.0 / cb_PostEffectAuto.u_ViewpointSize.x), (1.0 / cb_PostEffectAuto.u_ViewpointSize.y)); //resolve map size is u_ViewpointSize
	  vec2 nextUV = UV + offsetUV;
	
	  vec4 hitpacked = GetEffectTexture(RaytraceMap, nextUV);
	  vec2 hitUV = hitpacked.xy;
	  float hitPDF = hitpacked.z;
	  float hitmask = hitpacked.w;

	  vec3 hitViewPos = UVToViewPos(hitUV);

      weight = localBRDF(vNormalize(-viewPos), vNormalize(hitViewPos - viewPos), vNormalize(viewNormal), roughness) / vMax(hitPDF,0.00001);
	  	   
	  #ifdef SSR_RadianceNoMip
		vec3 hitRadiance = GetColor(hitUV).xyz;
	  #else
		float adjacentLength = vLength(hitUV - UV);
		float intersectionCircleRadius = IsoscelesTriangleBase(adjacentLength, coneHalfAngle);		
		float mip = vClamp(vLog2(intersectionCircleRadius * vMax(cb_PostEffectAuto.u_ViewpointSize.x, cb_PostEffectAuto.u_ViewpointSize.y)), 0.0, maxMipLevel);
		vec3 hitRadiance = vTextureLod(EyeMapWithMips, hitUV, mip).xyz;
	  #endif

	  radColor.rgb = specular * hitRadiance;
	  //screen fade off
	  float borderDist = vMin(1 - vMax(hitUV.x, hitUV.y), vMin(hitUV.x, hitUV.y));
	  radColor.a = vSaturate((borderDist  > screenFadeSize) ? 1 : borderDist/screenFadeSize) * hitmask;

	  //reduce fireflies effect
	  float luminance = GetLuminance(radColor.rgb);
	  radColor.rgb /= 1 + luminance;

	  resultColor += radColor * weight;
      weightSum += weight;    
  }
   resultColor /= weightSum;

  //reduce fireflies effect
  float luminance =  GetLuminance(resultColor.rgb);
  resultColor.rgb /= 1 + luminance;
     
  resultColor.rgb = vMin(resultColor.rgb, vec3(1.0));
  FRAGCOLOR = resultColor;
}
