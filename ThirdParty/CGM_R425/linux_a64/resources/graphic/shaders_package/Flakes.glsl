#if defined(FragmentStage) || defined(RayHitStage)


#ifdef Flakes

///////////////////// FLAKES HELPER

#define FREQUENCY 0.6

#ifndef INTERNAL_FLAKES_PERFORMANCE_MODE
#define INTERNAL_FLAKES_PERFORMANCE_MODE 0 //max quality by default (shouldn't happen here)
#endif

void flakesVisibility(out float flakesLODLevel, out float metallicFlakesBlending, out float pearlFlakesBlending, out float flakesMask, in float scaling) {   
  // params to make stuff independant of world matrix
  vec3 worldScaling = vComputeWorldScaling();
	// max distance
  vec3 V = -(vGetViewInvMatrix() * vec4(vGetViewPosition(), 0.0)).xyz;
  float dist = vLength(worldScaling*V);
	// locality
	V = vNormalize(V);
	float NdotV = vDot(_worldNormal, V);
	float locality = (NdotV > 0.0) ? 1.0 : 0.0;
  //
	if (locality == 0.0) {
    flakesLODLevel = 0.0;
    metallicFlakesBlending = 0.0;
    pearlFlakesBlending = 0.0;
    flakesMask = 0.0;
		return;
	}
  float normDist = vSaturate(scaling*dist/800.0);
  float shortDist = vSaturate(1-normDist);
	// LOD distance
  flakesLODLevel = scaling*dist;  
	// blending
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 2
  metallicFlakesBlending = normDist * (0.5*PMat.flakesDensity + 0.25);
  pearlFlakesBlending = normDist * (0.5*PMat.pearlFlakesDensity + 0.25);
#else
  metallicFlakesBlending = normDist * 0.5;
  pearlFlakesBlending = normDist * 0.5;
#endif
	// near distance
  flakesMask= shortDist;
}
///////////////////// END FLAKES HELPER


///////////////////// MAIN METHODS

void metallicFlakes(out float metallicFlakesPresence, out vec3 metallicFlakesBaseColor, in float presenceNoise,
                 in float presenceNoise2, in float noisePositive, in float noiseNegative,
                 in vec3 T, in vec3 B) {
  if (vLength(PMadMat.m_flakesColor.xyz) < kEpsilon) {
    return;
  }
  //// metallic flakes
  metallicFlakesPresence = vPow5(presenceNoise);//, 10*vMix(0.5,0.9,1-PMat.flakesDensity));
  float aux = vPow5(presenceNoise2);
  metallicFlakesPresence += vMix(-aux,aux,PMat.flakesDensity);
  // scale and saturate (after density, flakesPresence is too small which makes the flakes too dark)
  metallicFlakesPresence *= 5;
  metallicFlakesPresence = vSaturate(metallicFlakesPresence);
  // color - to remove the uniformity
  metallicFlakesBaseColor = vMix(2*PMat.flakesColor,vec3(0.0),vAffine(noiseNegative,0.5,1.0));
  // metal Flakes normal  
  float theta = metallicFlakesPresence*noisePositive * PI/8;
  float phi =  metallicFlakesPresence*noiseNegative * PI/8;
  _metallicFlakesNormal = Rotate3D(_metallicFlakesNormal,theta, B);
  _metallicFlakesNormal = Rotate3D(_metallicFlakesNormal,phi,T);
}

void pearlFlakes(out float pearlFlakesPresence, out vec3 pearlFlakesBaseColor, in float presenceNoise,
                 in float presenceNoise2, in float noisePositive, in float noiseNegative,
                 in vec3 T, in vec3 B) {
  if (vLength(PMadMat.m_pearlFlakesColor.xyz) < kEpsilon) {
    return;
  }
  //// pearl flakes
  pearlFlakesPresence = vPow6(presenceNoise2);
  float aux = vPow6(presenceNoise);
  pearlFlakesPresence += vMix(-aux,aux,PMat.pearlFlakesDensity);
  // scale and saturate (after density, flakesPresence is too small which makes the flakes too dark)
  pearlFlakesPresence *= 6;
  pearlFlakesPresence = vSaturate(pearlFlakesPresence);
  // threshold to make the flakes sparkle, it simulates a higher frequency
  if (pearlFlakesPresence < 0.2) {
      return;
  }
  // color - to remove the uniformity
  pearlFlakesBaseColor = vMix(2*PMat.pearlFlakesColor,vec3(0.0),vAffine(noisePositive,0.5,1.0));
  // pearl Flakes normal  
  float theta = pearlFlakesPresence*noisePositive * PI/4;
  float phi =  pearlFlakesPresence*noiseNegative * PI/4;
  _pearlFlakesNormal = Rotate3D(_pearlFlakesNormal,theta, B);
  _pearlFlakesNormal = Rotate3D(_pearlFlakesNormal,phi,T);
}

void blendMetalFlakes(in float flakesMask, in float metallicFlakesBlending, in float metallicFlakesPresence, in vec3 metallicFlakesBaseColor) {
  if (vLength(PMadMat.m_flakesColor.xyz) < kEpsilon) {
    return;
  }
  float metallicFlakesStrength =  flakesMask * metallicFlakesPresence;
  // metal effect
  float metalPerturbateNormal = 0.1*PMat.flakesBump ;
#if INTERNAL_FLAKES_PERFORMANCE_MODE > 0
  metalPerturbateNormal = 0.0;
#endif
  _metallicFlakesGlossiness = vMix(0.75,0.55,PMat.flakesRoughness);
  _metalGlossiness =  _metallicFlakesGlossiness - metalPerturbateNormal;
  // fresnel
  _metalFresnel = PMadMat.m_flakesColor.xyz * metallicFlakesBlending * PMat.flakesColor;
  _metallicFlakesFresnel = PMadMat.m_flakesColor.xyz * metallicFlakesBaseColor * metallicFlakesStrength;
  // nomals
  metalPerturbateNormal *= 10 * flakesMask; // glossiness is low, so we take a big perturbation (else there is no visible effect)
  _metallicFlakesNormal = vNormalize(_worldNormal+metalPerturbateNormal*_metallicFlakesNormal);
}

void blendPearlFlakes(in float flakesMask, in float pearlFlakesBlending, in float pearlFlakesPresence, in vec3 pearlFlakesBaseColor) {
  if (vLength(PMadMat.m_pearlFlakesColor.xyz) < kEpsilon) {
    return;
  }
  float pearlFlakesStrength =  flakesMask * pearlFlakesPresence;
  // pearl effect
  float pearlPerturbateNormal = 0.05*PMat.pearlFlakesBump ;
#if INTERNAL_FLAKES_PERFORMANCE_MODE > 0
  pearlPerturbateNormal = 0.0;
#endif
  _pearlFlakesGlossiness = 1.0;
  _pearlGlossiness =  _pearlFlakesGlossiness - pearlPerturbateNormal;
  // fresnel
  // compared to metal flakes, the dye on pearl flakes is weaker
  _pearlFresnel = PMadMat.m_pearlFlakesColor.xyz * pearlFlakesBlending * PMat.pearlFlakesColor * 0.25; // pearls leave practicaly no dye
  _pearlFlakesFresnel = PMadMat.m_pearlFlakesColor.xyz * pearlFlakesBaseColor * pearlFlakesStrength;
  // normals
  pearlPerturbateNormal *= 10 * vSqrt(flakesMask); // The sqrt is here to further simulate the idea of higher frequency
  _pearlFlakesNormal = vNormalize(_worldNormal+pearlPerturbateNormal*_pearlFlakesNormal);
}


void doFlakes() {
  /////
  float flakesMask = 0.0;
  float flakesLODLevel = 0.0;
  //float scaling = 0.01/PMat.flakesScale;
  float scaling = vMix(0.0, 0.9, atan(PI*PMat.flakesScale)*2.0/PI);
  vec3 T = getGeomTApprox(_worldNormal);
  vec3 B = getGeomBApprox(_worldNormal, T);

  // metal
  float metallicFlakesBlending = 0.0;
  float metallicFlakesPresence = 0.0;
  vec3 metallicFlakesBaseColor = vec3(0.0);

  _metallicFlakesFresnel = vec3(0.0);
  _metalFresnel = vec3(0.0);
  _metallicFlakesNormal = _worldNormal;

  // pearl
  float pearlFlakesBlending = 0.0;
  float pearlFlakesPresence = 0.0;
  vec3 pearlFlakesBaseColor = vec3(0.0);

  _pearlFlakesFresnel = vec3(0.0);
  _pearlFresnel = vec3(0.0);
  _pearlFlakesNormal = _worldNormal;

  // visib

  flakesVisibility(flakesLODLevel, metallicFlakesBlending, pearlFlakesBlending, flakesMask, scaling);

  /////////////

  if (vLength(PMadMat.m_pearlFlakesColor.xyz) < kEpsilon && vLength(PMadMat.m_flakesColor.xyz) < kEpsilon) {
		return;
  }

  if (flakesMask < kEpsilon) {
      blendMetalFlakes(flakesMask, metallicFlakesBlending, metallicFlakesPresence, metallicFlakesBaseColor);
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
      blendPearlFlakes(flakesMask, pearlFlakesBlending, pearlFlakesPresence, pearlFlakesBaseColor);
#endif
      return;
  }

  // simplex 3D, because of periodicity, introduces patterns on some planes, limit the simplex to an area with no visible pattern
  vec3 tex = scaling*v_ObjectSpacePosition;
  tex.y = -vAbs(tex.y);
  tex.x = -vAbs(tex.x);
	// noises
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
  float noisePositive = arrayFBMMixer(0.85*tex,flakesLODLevel,FREQUENCY);
  float noiseNegative = arrayFBMMixer(0.85*tex.yxz,flakesLODLevel,FREQUENCY);
#else
  float noisePositive = 0.0;
  float noiseNegative = 0.0;
#endif 
  // presence
  float presenceNoise = vAffine(arrayFBMMixer(tex,flakesLODLevel,FREQUENCY),0.5,1.0);
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 2
  float presenceNoise2 = vAffine(arrayFBMMixer(tex.yxz,flakesLODLevel,FREQUENCY),0.5,1.0);
#else
  float presenceNoise2 = 0.0;
#endif
  metallicFlakes(metallicFlakesPresence,metallicFlakesBaseColor,presenceNoise, presenceNoise2, noisePositive, noiseNegative,T,B);
  blendMetalFlakes(flakesMask, metallicFlakesBlending, metallicFlakesPresence, metallicFlakesBaseColor);
  //////
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
  pearlFlakes(pearlFlakesPresence,pearlFlakesBaseColor,presenceNoise, presenceNoise2, noisePositive, noiseNegative,T,B);
  blendPearlFlakes(flakesMask, pearlFlakesBlending, pearlFlakesPresence, pearlFlakesBaseColor);
#endif

}

///////////////////// END MAIN METHODS
#endif // Flakes

#ifdef ProceduralCoating

void orangePeelVisibility(out float peelMask) {
  // params to make stuff independant of world matrix
  vec3 worldScaling = vComputeWorldScaling();
  //
  vec3 V = -(vGetViewInvMatrix() * vec4(vGetViewPosition(), 0.0)).xyz;
	const float dist = vLength(worldScaling*V);
	const float normDist = vSaturate(dist/20000.0);
  const float shortDist = vSaturate(1.0-normDist);
	// locality
	V = vNormalize(V);
	float NdotV = vDot(_worldNormal, V);
	float locality = (NdotV > 0.0) ? 1.0 : 0.0;
  if (locality == 0.0) {
		// forced exit
		peelMask = 0.0;
		return;
	}
	peelMask = shortDist;	
}

void doOrangePeel() {
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
  float peelMask = 0.0 ;
  float peelScaling = 100 * PMat.coatingScale;
  orangePeelVisibility(peelMask);
	if (PMat.coatingBump < kEpsilon || peelMask < kEpsilon) {
		return;
	}
	// low frequency noise
  vec3 tex = peelScaling*v_ObjectSpacePosition / 1000.0;
  float noise = FBM(tex);
	vec3 peelNormal = vec3(noise);
	// small perturbation
	_coatingNormal = vNormalize(_coatingNormal + 0.05*PMat.coatingBump*peelMask*peelNormal);
#endif
}

#endif // ProceduralCoating

#endif // FragmentStage
