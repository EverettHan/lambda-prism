
#if defined(VIEW_ARRAY_ID) || (defined(MultiviewSinglePass) && (MultiviewSinglePass > 1))
  #ifndef VIEW_ARRAY_ID
    #define VIEW_ARRAY_ID int(vGetViewID())
  #endif
#endif


#if defined(LINEAR_DEPTH) && !defined(GLES2Platform)
#define ConvertZBufferToZView(iZ) (iZ)
#else
float ConvertZBufferToZView(const float iZ)
{
#ifdef LINEAR_DEPTH
  return iZ;
#else
  float z = iZ;

  // projection conic
#ifdef PROJECTION_CONIC
#ifdef LOG_DEPTH
  z = vExp(z *cb_PostEffectAuto.u_NearFarLogZ.y)*cb_PostEffectAuto.u_NearFar.x;
#else
  z  = cb_PostEffectAuto.u_NearFar.w/(cb_PostEffectAuto.u_NearFar.z-z);
#endif
#else
  z = -vFma(cb_PostEffectAuto.u_NearFar.z, z, cb_PostEffectAuto.u_NearFar.w);
#endif
  return z;
#endif
}
#endif



void updateFinalColor(inout vec4 finalColor, inout vec4 weightedColorSum, uint nbOfFragmentsWithSameDepth, vec4 iFresnel)
{
  if (nbOfFragmentsWithSameDepth > 1)
  { // then we turn weightedColorSum into a final aggregated weighted color
    if (weightedColorSum.a > 0.f)
      weightedColorSum.rgb /= weightedColorSum.a; // weighted average (at that point, weightedColorSum.a is the sum of alphas)
    weightedColorSum.a /= float(nbOfFragmentsWithSameDepth); // average alpha
    weightedColorSum.a = 1 - max(vPow(1.0 - weightedColorSum.a, nbOfFragmentsWithSameDepth), 0); // heuristic for final aggregated alpha (ensures that it gives the correct result if all alphas are the same, in particular)
    weightedColorSum.rgb *= weightedColorSum.a; // we alpha-weight the weighted average color with the value of the final aggregated alpha
  }
  // now weightedColorSum is actually an alpha-weighted color (which possibly aggregates several fragments with same depths)
#ifdef OIT_FRESNEL
  
  finalColor.rgb = weightedColorSum.rgb  + iFresnel.rgb * finalColor.rgb;
  finalColor.a = weightedColorSum.a + (1-weightedColorSum.a) * finalColor.a;
#else
	finalColor.rgb = weightedColorSum.rgb + (1.0 - weightedColorSum.a) * finalColor.rgb;
	finalColor.a = weightedColorSum.a + (1.0 - weightedColorSum.a) * finalColor.a;

#endif
}

void main()
{
#ifdef VIEW_ARRAY_ID
  ivec3 fragCoord = ivec3(gl_FragCoord.xy, VIEW_ARRAY_ID);
#else
  ivec2 fragCoord = ivec2(gl_FragCoord.xy);
#endif

#ifndef IS_MSAA

	vec4 finalColor = texelFetch(s_BackBuffer, fragCoord, 0);
  

#else
  vec4 finalColor = texelFetch(s_BackBuffer, fragCoord, gl_SampleID);
#endif
#ifdef OIT_TAIL_WA

#ifdef VIEW_ARRAY_ID
  vec3 texCoord = vec3(vTexCoord.xy, float(VIEW_ARRAY_ID));
#else
  vec2 texCoord = vec2(vTexCoord.xy);
#endif

  vec4 sumColor = texelFetch(s_Tail, fragCoord, gl_SampleID);
  float n = texelFetch(s_TailDepth, fragCoord, gl_SampleID).r;

  if(n > 0.01 && sumColor.a > 0.01)
  {
    vec3  avgColor = max(sumColor.rgb, vec3(0.0)) / sumColor.a;
    float avgAlpha = sumColor.a   / n;

    float tmp = max(vPow(1.0 - avgAlpha, n),0);

    vec4 src = vec4(avgColor, 1.0-tmp);
    finalColor.rgb = src.a * src.rgb + (1.0-src.a) * finalColor.rgb;
    finalColor.a = src.a + (1-src.a)*finalColor.a;
  //  finalColor = sumColor / n;
  }

#endif

  const int nbLayerOIT = OIT_MAX_LIST;
#ifdef VIEW_ARRAY_ID
  const int viewOffset = nbLayerOIT * VIEW_ARRAY_ID;
#else
  const int viewOffset = 0;
#endif


#ifdef OIT_DEBUG_LAYER

  float layerId = float(viewOffset) + OIT_DEBUG_LAYER - 1;
  if(int(OIT_DEBUG_LAYER-1) < OIT_MAX_LIST)
  {
    vec3 texCoord = vec3(vTexCoord.xy, layerId);
    uvec4 texelValue = vTexture(s_FresnelTex, texCoord);
	float lastDepth = uintBitsToFloat(depthUntag(vTexture(s_DepthsTex, texCoord).x));
	 finalColor = vec4(10.0,0.0,0.0,1.0);
	/*if(_GetColor(texelValue).w >= 0.5 && _GetColor(texelValue).w < 0.7)
    finalColor = vec4(1.0,0.0,0.0,1.0);
	else if(_GetColor(texelValue).w == 1.0)
		finalColor = vec4(1.0,1.0,0.0,1.0);*/
	
	finalColor = vec4(pow(_GetColor(texelValue).rgb,vec3(10.0)),1.0);
  }
  else
  {
  }

#else

  {
    int i = viewOffset + nbLayerOIT - 1;
    vec3 texCoord = vec3(vTexCoord.xy, i);

    float lastDepth = uintBitsToFloat(depthUntag(vTexture(s_DepthsTex, texCoord).x));
    vec4 weightedColorSum = _GetColor(vTexture(s_SourceTex, texCoord));
    weightedColorSum.rgb *= weightedColorSum.a;
    uint nbOfFragmentsWithSameDepth = 1;
   
#ifdef OIT_FRESNEL  
	int maxLayer = viewOffset + nbLayerOIT - 1;

	  vec4 prevColor = vec4(0.0);
	  vec4 preAttenuation = vec4(0.0);
	  vec4 prevFresnel = vec4(0.0);
	  float prevDepth = 0.0;
	  float curDepth= 0.0;
	  vec4 color = finalColor;
	 
	 bool enterVolume = false;
	 int j = 0;
	for (i = maxLayer; i >= 0; i--)
    {
		vec3 texCoord = vec3(vTexCoord.xy, i);
		vec4 curFresnel = _GetColor(vTexture(s_FresnelTex, texCoord));
		vec4 curColor = _GetColor(vTexture(s_SourceTex, texCoord));
		float curDepth = depthUntag(vTexture(s_DepthsTex, texCoord).x);
		vec4 curAttenuation = _GetColor(vTexture(s_Attenuations, texCoord));
		curColor.xyz *= curColor.w;
		

		if(curFresnel.w == 0.0 )
		{
			vec4 col =  vec4(curColor.xyz,0.0);
			updateFinalColor(color,col, 1,vec4(1.0));
		}
		else if(curFresnel.w == 1.0)
		{	
			updateFinalColor(color, curColor, 1,vec4(curFresnel.xyz,1.0));
			if(enterVolume == false)
			{
				enterVolume = true;
				prevColor = curColor;
				prevFresnel = curFresnel;
				prevDepth = (uintBitsToFloat(depthUntag(vTexture(s_DepthsTex, texCoord).x)));
			}
		}
		else if(curFresnel.w >= 0.5 &&  curFresnel.w < 0.7)
		{
			if(enterVolume == true)
			{
				enterVolume = false;
				float distanceToAttenuate = abs(prevDepth - (uintBitsToFloat(depthUntag(vTexture(s_DepthsTex, texCoord).x))))*(cb_PostEffectAuto.u_NearFar.y-cb_PostEffectAuto.u_NearFar.x);

				if(distanceToAttenuate > 0 && curAttenuation.xyz != vec3(0.0))
				{
				vec3 extinction = -log(curAttenuation.xyz) /  curAttenuation.w;
				vec3 scattering = extinction;
				vec3 attenuation = max(vec3(0.0),exp(-extinction*distanceToAttenuate));
				vec3 lp = attenuation*0.079617;
				color.xyz = lp + attenuation.xyz *color.xyz;
				color.w =  color.w*attenuation.x;
				}
			}
			updateFinalColor(color, curColor, 1,vec4(curFresnel.xyz,1.0) );
		}
	}
	
    finalColor = color;
#else
   for (i = viewOffset + nbLayerOIT - 2; i >= viewOffset; i--)
    {
      texCoord = vec3(vTexCoord.xy, i);
      vec3 texCoord1 = vec3(vTexCoord.xy, i-1);
      float depth = uintBitsToFloat(depthUntag(vTexture(s_DepthsTex, texCoord).x));
      vec4 weightedColor = _GetColor(vTexture(s_SourceTex, texCoord));
	  vec4 fresnelColor = vec4(0.0);
	  vec4 attenuation = vec4(1.0);
	  #ifdef OIT_FRESNEL
	  fresnelColor = _GetColor(vTexture(s_FresnelTex, texCoord));
	  attenuation = _GetColor(vTexture(s_Attenuations, texCoord1));
	  #endif
      weightedColor.rgb *= (weightedColor.a);
     
      if (abs(depth - lastDepth) <= g_depthFightThreshold)
      { // fragments have same depth or are depth fighting; we cannot say which is in front of which so we fall back to a commutative weighted average
        nbOfFragmentsWithSameDepth++;
        weightedColorSum += weightedColor;
        lastDepth = depth;
      }
      else
      {
        if(fresnelColor.w == 0.0)
          fresnelColor = vec4(1.0);
		
		vec3 attCoef =  exp(-attenuation.xyz*attenuation.w);
		//fresnelColor.xyz *= attenuation.xyz;
        updateFinalColor(finalColor, weightedColorSum, nbOfFragmentsWithSameDepth, fresnelColor);
		//finalColor.xyz = finalColor.xyz*(attCoef);
        nbOfFragmentsWithSameDepth = 1;
        weightedColorSum = weightedColor;
        lastDepth = depth;
      }
    }
   updateFinalColor(finalColor, weightedColorSum, nbOfFragmentsWithSameDepth, vec4(1.0));
   #endif
  }

#endif

  FRAGCOLOR =  finalColor ; 
}
