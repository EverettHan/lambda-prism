//-----------------------------------------------------------------------------------------------------------------------------
// Define/Shader Options

#define TRANSMITTANCE_NON_LINEAR                    1
#define INSCATTER_NON_LINEAR                        1


//-----------------------------------------------------------------------------------------------------------------------------
// Global

float               g_AtmosphereRadiusTop           = g_AtmosphereRadiusGround+cb_SkyScattering.u_AtmosphereHeight*g_RatioToKm;
float               g_AtmosphereRadiusTopForReflectedLight = g_AtmosphereRadiusGround+(cb_SkyScattering.u_AtmosphereHeight*g_RatioToKm)*0.2;          

const float         g_EpsilonAtmosphere             = 0.002;
const float         g_EpsilonInScatter              = 0.004; 
const uint  		g_Res_r                         = 32;
const uint  		g_Res_mu                        = 128;
const uint  		g_Res_mus                       = 32;
const uint  		g_Res_nu                        = 8;

vec3                g_BetaM                         = cb_SkyScattering.u_BetaM/0.9;
float               g_HM                            = cb_SkyScattering.u_HM*g_RatioToKm;
float               g_HR                            = cb_SkyScattering.u_HR*g_RatioToKm;

const float         g_NightHazeStartAltitude        = 0;
float               g_NightHazeEndAltitude          = cb_SkyScattering.u_AtmosphereHeight*g_RatioToKm;

// MIE BOOST FOR HDR CUBEMAP GEN
const float         g_MieBoost                      = 0.0; //1.0;

//-----------------------------------------------------------------------------------------------------------------------------
// Info

/*
// DEFAULT
const float         cb_SkyScattering.u_HM           = 1.2;
const vec3          cb_SkyScattering.u_BetaM        = vec3(4e-3, 4e-3, 4e-3);
const float         cb_SkyScattering.u_MieG         = 0.8;

// CLOUDY
const float         cb_SkyScattering.u_HM           = 3.0;
const vec3          cb_SkyScattering.u_BetaM        = vec3(3e-3, 3e-3, 3e-3);
const float         cb_SkyScattering.u_MieG         = 0.65;


// CLEAR SKY
const float         cb_SkyScattering.u_HM           = 1.2;
const vec3          cb_SkyScattering.u_BetaM        = vec3(20e-3, 20e-3, 20e-3);
const float         cb_SkyScattering.u_MieG         = 0.76;
*/


//-----------------------------------------------------------------------------------------------------------------------------
// IntersectAtmosphere
//
// input: 
//    * iDir:           ray direction in world space
//    * iPos:           ray origin in world space
// output:
//    * oOffset:        distance to atmosphere or 0 if within atmosphere
//    * oMaxPathLength: distance traversed within atmosphere
// return value: 
//    * intersection occurred true/false

bool IntersectAtmosphere(in vec3 iPos, in vec3 iDir, 
                         out float oOffset, out float oMaxPathLength)
{
	oOffset        = 0.0;
	oMaxPathLength = 0.0;

	// vector from ray origin to center of the sphere
	vec3  l   = -iPos; 
	float l2  = vDot(l,l);
	float s   = vDot(l,iDir);

	// adjust top atmosphere boundary by small epsilon to prevent artifacts
	float r   = g_AtmosphereRadiusTop - g_EpsilonAtmosphere;
	float r2  = r*r;
	
	if(l2 <= r2)
	{
		// ray origin inside sphere, hit is ensured
		float m2 = l2 - (s * s);
		float q  = vSqrt(vMax(0.0, r2 - m2));

		oMaxPathLength = s + q;
		
		return true;
	}
	else if(s >= 0)
	{
		// ray starts outside in front of sphere, hit is possible
		float m2 = l2 - (s * s);
		
		if(m2 <= r2)
		{
			// ray hits atmosphere definitely
			float q = vSqrt(vMax(0.0, r2 - m2));

			oOffset         = s - q;
			oMaxPathLength  = (s + q) - oOffset;
			
			return true;
		}
		else
    {
			return false;
    }
	}

  return false;
}


//-----------------------------------------------------------------------------------------------------------------------------
// In Scattered Lights
//

// Texture4D
//
// TODO:  passer les constant resolues h devrait etre une constante
//        g_AtmosphereRadiusGround*g_AtmosphereRadiusGround
//        1.0/g_Res_mu
//        1.0/g_Res_mus
//        1.0/g_Res_nu

vec4 Texture4D(sampler3D iTable, float iR, float iMu, float iMuS, float iNu)
{
	float h       = vSqrt(vMax(0.0, g_AtmosphereRadiusTop * g_AtmosphereRadiusTop - g_AtmosphereRadiusGround * g_AtmosphereRadiusGround));
	float rho     = vSqrt(vMax(0.0, iR * iR - g_AtmosphereRadiusGround * g_AtmosphereRadiusGround));

#ifdef INSCATTER_NON_LINEAR
	float rmu     = iR * iMu;
	float delta   = rmu * rmu - iR * iR + g_AtmosphereRadiusGround * g_AtmosphereRadiusGround;
	vec4  cst     = rmu < 0.0 && delta > 0.0 ? vec4(1.0, 0.0, 0.0, 0.5 - 0.5 / float(g_Res_mu)) : vec4(-1.0, h*h, h, 0.5 + 0.5 / float(g_Res_mu));
	float uR      = 0.5 / float(g_Res_r) + rho / h * (1.0 - 1.0 / float(g_Res_r));
	float uMu     = cst.w + (rmu * cst.x + vSqrt(vMax(0.0, delta + cst.y)) ) / (rho + cst.z) * (0.5 - 1.0 / float(g_Res_mu));
	float uMuS    = 0.5 / float(g_Res_mus) + (vAtan(vMax(iMuS, -0.1975) * 5.34962349919) / 1.1 + 0.74) * 0.5 * (1.0 - 1.0 / float(g_Res_mus));
#else
	float uR      = 0.5 / float(g_Res_r) + rho / h * (1.0 - 1.0 / float(g_Res_r));
	float uMu     = 0.5 / float(g_Res_mu) + (mu + 1.0) / 2.0 * (1.0 - 1.0 / float(g_Res_mu));
	float uMuS    = 0.5 / float(g_Res_mus) + max(muS + 0.2, 0.0) / 1.2 * (1.0 - 1.0 / float(g_Res_mus));
#endif

	float lerpNu  = 0.5 * (iNu + 1.0) * (float(g_Res_nu) - 1.0);
	float uNu     = vFloor(lerpNu);
	lerpNu        = lerpNu - uNu;
   
	return	vMix(vTextureLod(iTable, vec3((uNu + uMuS) / float(g_Res_nu),       1.0-uMu, uR), 0),
			         vTextureLod(iTable, vec3((uNu + uMuS + 1.0) / float(g_Res_nu), 1.0-uMu, uR), 0), 
               lerpNu); 
}

// optical depth for ray (r,mu) of length d, using analytic formula
// (mu=cos(view zenith angle)), intersections with ground ignored
// H=height scale of exponential density function

float OpticalDepth(float iH, float iR, float iMu, float iD) 
{
	float a     = vSqrt(vMax(0.0, (0.5/iH)*iR));
	vec2  a01   = a*vec2(iMu, iMu+iD/iR);
	vec2  a01s  = vSign(a01);
	vec2  a01sq = a01*a01;
	float x     = a01s.y > a01s.x ? vExp(a01sq.x) : 0.0; 
	vec2  y     = a01s / (2.3193*vAbs(a01) + vSqrt(vMax(vec2(0.0), 1.52*a01sq + 4.0))) * vec2(1.0, vExp(-iD/iH*(iD/(2.0*iR)+iMu)));

  return vSqrt(vMax(0.0, (6.2831*iH)*iR)) * vExp((g_AtmosphereRadiusGround - iR) / iH) * (x + y.x - y.y);
}

// transmittance(=transparency) of atmosphere for ray (r,mu) of length d
// (mu=cos(view zenith angle)), intersections with ground ignored
// uses analytic formula instead of transmittance texture
vec3 AnalyticTransmittance(float iR, float iMu, float iD) 
{
	return vExp(-cb_SkyScattering.u_BetaR * OpticalDepth(g_HR, iR, iMu, iD) - g_BetaM * OpticalDepth(g_HM, iR, iMu, iD));
}

// Rayleigh phase function
float PhaseFunctionR(float iCosRayZenithAngle) 
{
	return 0.05968310366 * (1.0 + iCosRayZenithAngle * iCosRayZenithAngle);
}

// Mie phase function
float PhaseFunctionM(float iCosRayZenithAngle) 
{
	return 0.119366207319 * (1.0 - cb_SkyScattering.u_MieG*cb_SkyScattering.u_MieG) * vPow(vAbs(1.0 + (cb_SkyScattering.u_MieG*cb_SkyScattering.u_MieG) - 2.0*cb_SkyScattering.u_MieG*iCosRayZenithAngle), -1.5) * (1.0 + iCosRayZenithAngle * iCosRayZenithAngle) / (2.0 + cb_SkyScattering.u_MieG*cb_SkyScattering.u_MieG);
}

// approximated single Mie scattering 
// rayMie.rgb=C*, rayMie.w=Cm,r
vec3 GetMie(vec4 iRayMie) 
{ 
	return iRayMie.rgb * iRayMie.w / vMax(iRayMie.r, 1e-4) * (cb_SkyScattering.u_BetaR.r / cb_SkyScattering.u_BetaR);
}

// GetInscatteredLight
//
// input:
//    * iSurfacePos:        reconstructed position of current pixel
//    * iViewDir:            view ray in world space
// input/output:
//    * ioAttenuation:      extinction factor along view path
//    * ioIrradianceFactor: surface hit within atmosphere 1.0 otherwise 0.0
// return value: 
//    * total in-scattered light

// TODO: iViewDir est deja normalise normalement, donc pas besoin d'appeler vNormalize qui est couteux de plus
//       idem vNormalize(iSunDirection)

vec3 GetInscatteredLight(in vec3 iSurfacePos, in vec3 iCameraPos, in vec3 iViewDir, 
                         inout vec3 ioAttenuation, inout float ioIrradianceFactor)
{
	vec3 inscatteredLight           = vec3(0.0, 0.0, 0.0);
	vec3 nightHaze                  = vec3(0);
	float distanceThroughAtmosphere = 0;
	float distanceToAtmosphere      = 0;
    
	//float gammaFix                  = 1.0;

	// intersect view ray with atmosphere virtual sphere 
	// distanceToAtmosphere = distance to atmosphere (0 if camera inside)
	// distanceThroughAtmosphere = travel distance through atmosphere
	if(IntersectAtmosphere(iCameraPos, iViewDir, distanceToAtmosphere, distanceThroughAtmosphere))
	{
		float distanceToObject = vDistance(iCameraPos, iSurfacePos);

		// modulating gamma to get correct colors
	 //gammaFix += smoothstep(-0.1, 1.0, distanceToObject) * 1.2; // total = 2.2

		// check if object occludes atmosphere
		if(distanceToObject > distanceToAtmosphere)
		{
			// offsetting camera
			vec3  startPos        = iCameraPos + distanceToAtmosphere * iViewDir;
			float heightStartPos  = vLength(startPos);
			distanceToObject -= distanceToAtmosphere;
      
			// starting position of path is now ensured to be inside atmosphere
			// was either originally there or has been moved to top boundary
			float nu          = vDot(iViewDir, cb_Sun.u_SunDirection.xyz);
			float muStartPos  = vDot(startPos, iViewDir) / heightStartPos;
			float musStartPos = vDot(startPos, cb_Sun.u_SunDirection.xyz) / heightStartPos;
      			
			// in-scattering for infinite ray (light in-scattered when no surface hit or object behind atmosphere)
			vec4 inscatter = vMax(Texture4D(s_TexInscatter, heightStartPos, muStartPos, musStartPos, nu), 0.0);

      // reduce total in-scattered light when surface hit within atmosphere
      // fíx described in chapter 5.1.1
      ioAttenuation = AnalyticTransmittance(heightStartPos, muStartPos, distanceToObject);

			// taking into account surface position
			float heightEndPos = vLength(iSurfacePos);
			float musEndPos    = vDot(iSurfacePos, cb_Sun.u_SunDirection.xyz) / heightEndPos;	

      // Horizon
			float muHorizon = -vSqrt(vMax(0.0, 1.0 - (g_AtmosphereRadiusGround / heightStartPos) * (g_AtmosphereRadiusGround / heightStartPos)));
      
			// check if object hit is inside atmosphere
			if(distanceToObject < distanceThroughAtmosphere)
			{
				float muEndPos = vDot(iSurfacePos, iViewDir) / heightEndPos; 
        
				vec4 inscatterSurface = Texture4D(s_TexInscatter, heightEndPos, muEndPos, musEndPos, nu);
				inscatter = vMax(inscatter - ioAttenuation.rgbr * inscatterSurface, 0.0);

				ioIrradianceFactor = 1.0;
			}
			else
			{
				// Night haze
				float PlanetSunlightFactor = vSmoothstep(-0.05,0.05, musEndPos);
				nightHaze = vec3(1.0-abs(muStartPos - muHorizon));
				nightHaze = cb_SkyScattering.u_NightHazeColor*vPow(vAbs(nightHaze), vec3(cb_SkyScattering.u_NightHazeSkyPower)) * cb_SkyScattering.u_NightHazeSkyIntensity;
				float cameraAlt = vLength(iCameraPos) - g_AtmosphereRadiusGround;
				nightHaze *= vSmoothstep(g_NightHazeEndAltitude, g_NightHazeStartAltitude, cameraAlt);
				nightHaze = vSaturate(nightHaze); 
			}

			// avoids imprecision problems near horizon by interpolating between two points above and below horizon
			// fíx described in chapter 5.1.2
			
			if (vAbs(muStartPos - muHorizon) < g_EpsilonInScatter) 
			{
				float mu              = muHorizon - g_EpsilonInScatter;
				float heightSamplePos = vSqrt(vMax(0.0, heightStartPos*heightStartPos+distanceToObject*distanceToObject+2.0*heightStartPos*distanceToObject*mu));
				float muSamplePos     = (heightStartPos * mu + distanceToObject) / heightSamplePos;
				
				vec4 inScatter0       = Texture4D(s_TexInscatter, heightStartPos,   mu,           musStartPos,  nu);
				vec4 inScatter1       = Texture4D(s_TexInscatter, heightSamplePos,  muSamplePos,  musEndPos,    nu);
				vec4 inScatterA       = vMax(inScatter0 - ioAttenuation.rgbr * inScatter1, 0.0);

				mu                    = muHorizon + g_EpsilonInScatter;
				heightSamplePos       = vSqrt(vMax(0.0, heightStartPos*heightStartPos+distanceToObject*distanceToObject+2.0*heightStartPos*distanceToObject*mu));
				muSamplePos           = (heightStartPos * mu + distanceToObject) / heightSamplePos;
				
				inScatter0            = Texture4D(s_TexInscatter, heightStartPos,   mu,           musStartPos,  nu);
				inScatter1            = Texture4D(s_TexInscatter, heightSamplePos,  muSamplePos,  musEndPos,    nu);
				vec4 inScatterB       = vMax(inScatter0 - ioAttenuation.rgbr * inScatter1, 0.0);

				float t = ((muStartPos - muHorizon) + g_EpsilonInScatter) / (2.0 * g_EpsilonInScatter);
				inscatter = vMix(inScatterA, inScatterB, t);
			}

			// avoids imprecision problems in Mie scattering when sun is below horizon
			// fíx described in chapter 5.1.3
			inscatter.w *= vSmoothstep(0.00, 0.02, musStartPos);
			
			float phaseR = PhaseFunctionR(nu);
			float phaseM = PhaseFunctionM(nu);

			// Sun boost for HDR cube map
			float SunSize     = 10000.0;
			float sunFactor   = 0.001*SunSize;
		  float lerpFactor  = (vMax((1.0-sunFactor), vDot(iViewDir, cb_Sun.u_SunDirection.xyz))-(1.0-sunFactor))*(1.0/sunFactor);
		  float theta       = vSmoothstep(0, 2, vPow(lerpFactor, 8));
			float sunBoost    = 2+g_MieBoost*theta;
      		
			inscatteredLight = vMax(inscatter.rgb * phaseR + GetMie(inscatter) * phaseM*sunBoost, 0.0);
			inscatteredLight *= cb_SkyScattering.u_SunScatteringIntensity;			
		}
		else 
    {
			ioIrradianceFactor = 1; // CK : fixes a bug on objects when camera is at very small distance 
    }
	}

	vec3 inscattered = inscatteredLight*0.6; // CK special factor
	
	//return pow(abs(inscattered), vec3(1.0/gammaFix)) + nightHaze; 
	return abs(inscattered) + nightHaze;
}



//-----------------------------------------------------------------------------------------------------------------------------
// Reflected Lights
//

vec3 Irradiance(sampler2D iSmp, float iAlt, float iCosSunZenithAngle) 
{
  float uR    = (iAlt - g_AtmosphereRadiusGround) / (g_AtmosphereRadiusTop - g_AtmosphereRadiusGround);
	float uMuS  = (iCosSunZenithAngle + 0.2) / (1.0 + 0.2);

	return vTextureLod(iSmp, vec2(uMuS, 1.0-uR), 0).rgb;
}

// transmittance(=transparency) of atmosphere for infinite ray (alt,cosRayZenithAngle)
// (cosRayZenithAngle=cos(view zenith angle)), intersections with ground ignored
vec3 Transmittance(float iAlt, float iCosRayZenithAngle) 
{
  float uR, uMu;
#ifdef TRANSMITTANCE_NON_LINEAR
	uR  = vSqrt(vMax(0.0, (iAlt - g_AtmosphereRadiusGround) / (g_AtmosphereRadiusTop - g_AtmosphereRadiusGround)));
	uMu = vAtan((iCosRayZenithAngle + 0.15) / (1.0 + 0.15) * vTan(1.5)) / 1.5;
#else
	uR  = (iAlt - g_AtmosphereRadiusGround) / (g_AtmosphereRadiusTop - g_AtmosphereRadiusGround);
	uMu = (iCosRayZenithAngle + 0.15) / (1.0 + 0.15);
#endif

	return vTextureLod(s_TexTransmittance, vec2(uMu, 1.0-uR), 0).rgb;
}


// GetReflectedLight
//
// input:
//    * iSurfacePos:        reconstructed position of current pixel
//    * texC:               texture coordinates
//    * iAttenuation:       extinction factor along view path
//    * iIrradianceFactor:  surface hit within atmosphere 1.0f otherwise 0.0f
// return value: 
//    * total reflected light + direct sunlight
vec3 GetReflectedLight(in vec3 iSurfaceColor, in vec3 iSurfacePos, in vec3 iCameraPos, in vec3 iAttenuation, in float iIrradianceFactor)
{
	if (iIrradianceFactor == 0)
  {
#ifdef SCATTERING_REFLECTEDLIGHT_ATTENUATION
		return iSurfaceColor*iAttenuation;
#else
		return iSurfaceColor;
#endif
  }
	else
	{
		// decode normal and determine intensity of refected light at surface position
		//float lightScale = vSaturate(dot(surfaceNormal, cb_Sun.u_SunDirection.xyz)); // original
		float lightScale = 1; // CK : WE DO NOT USE lightscale !
		// irradiance at surface position due to sky light
		float surfacePosHeight	= vLength(iSurfacePos);				
		float dotSunSphere      = vDot(iSurfacePos, cb_Sun.u_SunDirection.xyz) / surfacePosHeight;
		float musSurfacePos     = vSaturate(dotSunSphere); // CK added saturate	

		vec3 irradianceSurface  = Irradiance(s_TexIrradiance, surfacePosHeight, musSurfacePos) * iIrradianceFactor;
		 
		// attenuate direct sun light on its path from top of atmosphere to surface position
		vec3 attenuationSunLight = Transmittance(surfacePosHeight, musSurfacePos);

		vec3 reflectedLight = iSurfaceColor * (lightScale * attenuationSunLight + irradianceSurface) * cb_SkyScattering.u_SunScatteringIntensity * (cb_SkyScattering.u_AverageGroundReflectance / PI);
	  
    // factor to avoid discontinuities on the atmosphere boundary (and black materials above atmosphere)
    float inSpaceFactor = vSmoothstep(g_AtmosphereRadiusTopForReflectedLight, g_AtmosphereRadiusTop, surfacePosHeight);
    reflectedLight = vMix(reflectedLight, iSurfaceColor, inSpaceFactor);

	  float cameraAlt               = vLength(iCameraPos) - g_AtmosphereRadiusGround;	
		float planetSunlightFactor    = vSmoothstep(-0.05,  0.05, dotSunSphere);
		float planetSunlightFactorBis = vSmoothstep(-0.05,  0.2,  dotSunSphere); // to avoid too much yellow in space (on shadow boundaries)
		float bisFactor               = vSmoothstep(300, 1000, cameraAlt);
		planetSunlightFactor = (1.0-bisFactor)*planetSunlightFactor + planetSunlightFactorBis*bisFactor;
    
		// Fog applied at night 
		vec3  fogColor    = cb_SkyScattering.u_NightHazeColor * cb_SkyScattering.u_NightHazeFogIntensity;
		float fogDensity  = 0.009;
		float fogFactor   = 1.0 - 1.0 / vPow(vExp(vLength(iSurfacePos-iCameraPos) * fogDensity), 2);
		fogFactor *= vSmoothstep(g_NightHazeEndAltitude, g_NightHazeStartAltitude, cameraAlt);

		iSurfaceColor = (1.0-fogFactor) * iSurfaceColor + fogFactor * fogColor;
    
		return planetSunlightFactor * reflectedLight + (1.0-planetSunlightFactor) * iSurfaceColor;
	}
}


//-----------------------------------------------------------------------------------------------------------------------------
//  ApplyScattering
//
  
vec3 ApplyScattering(in vec3 iColor, in vec3 iWorldPos, in vec3 iViewDir, in vec3 iCameraPos)
{ 
  // Compute InScattered lights and reflected lights
	vec3 attenuation        = vec3(1.0f, 1.0f, 1.0f);
	float irradianceFactor  = 0.0f;
	vec3 inscatteredLight   = GetInscatteredLight (iWorldPos, iCameraPos, iViewDir, attenuation, irradianceFactor);
	vec3 reflectedLight     = GetReflectedLight   (iColor, iWorldPos, iCameraPos, attenuation, irradianceFactor);
	
	return reflectedLight + inscatteredLight;
}




