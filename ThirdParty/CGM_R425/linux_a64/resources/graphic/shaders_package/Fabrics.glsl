#ifdef Fabrics

//#define superSample
// some params
#if (defined(UseVelvet) || defined(UseSilkVelvet))
  #define Fur
  #define MAX_Rough 1.0
  #define MIN_Rough 0.85
#endif

#if defined(UseSatin)
  #define noFur
  #define MAX_Rough 0.85
  #define MIN_Rough 0.15
#endif

#if defined(EVisuPBR)
  #define MAX_Rough 1.0
  #define MIN_Rough 0.0
#endif

// ibl convolution
vec3 Tangent2World(in vec3 iH, in vec3 iNormal)
{
  vec3 up = vAbs(iNormal.z) < 0.9999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 rot_X = vNormalize(vCross(up, iNormal));
  vec3 rot_Y = vNormalize(vCross(iNormal, rot_X));
 
  return iH.x * rot_X + iH.y * rot_Y + iH.z * iNormal;
}


vec3 ComputeLightVector(in vec3 iView, in vec3 iH)
{
  return vNormalize(2.0 * vDot(iView, iH) * iH - iView);
}

float VanDerCorput(uint iIndex)
{
  iIndex = (iIndex << 16u) | (iIndex >> 16u);
  iIndex = ((iIndex & 0x55555555u) << 1u) | ((iIndex & 0xAAAAAAAAu) >> 1u);
  iIndex = ((iIndex & 0x33333333u) << 2u) | ((iIndex & 0xCCCCCCCCu) >> 2u);
  iIndex = ((iIndex & 0x0F0F0F0Fu) << 4u) | ((iIndex & 0xF0F0F0F0u) >> 4u);
  iIndex = ((iIndex & 0x00FF00FFu) << 8u) | ((iIndex & 0xFF00FF00u) >> 8u);

  return float(iIndex) * 2.3283064365386963e-10;
}

vec2 Hammersley2D(uint i, uint N)
{
  return vec2(float(i)/float(N), VanDerCorput(i));
}


vec3 GetSampleVector(in float iX, in float iY, in float a2, in vec3 iN)
{
  float phi = 2*iX * PI;
  float value = 1.0;

  #ifdef Fur 
  float interiorTerm = 4*a2*vExp(1/a2)/(4*a2*iY + iY - 1);
  float exteriorTerm = a2*vLog(interiorTerm);
  value /= exteriorTerm;
  #endif

  #ifdef noFur
  float loga = 8*a2*vLog(1-iY);
  value = loga / (loga - 1);
  #endif

  float sinTheta = vSqrt(vSaturate(value));
  float cosTheta = vSqrt(1 - sinTheta * sinTheta);
  vec3 H;
  H.x = sinTheta*vCos(phi);
  H.y = sinTheta*vSin(phi);
  H.z = cosTheta;

  return Tangent2World(H, iN);
}

vec2 IntegrateFabricsBRDF( in float Roughness, in vec3 N , in vec3 V) {
  float r = vAffine(Roughness, MIN_Rough, MAX_Rough);
  float a2 = vPow4(r);
  float NoV = vMax(vDot(N,V),0.0);
  float A = 0;
  float B = 0;
  int samples = 0;
  #ifdef superSample
  const uint NumSamples = 1024;
  #else
  const uint NumSamples = 64;
  #endif
  for( uint i = 0; i < NumSamples; i++ ) {
    vec2 Xi = Hammersley2D( i, NumSamples );

    vec3 H = GetSampleVector( Xi.x, Xi.y, a2 , N );

    vec3 L = ComputeLightVector(V,H);

    float VoH = vMax(vDot(V, H), 0.0);
    float NoH = vMax(vDot(N, H), 0.0);
    float NoL = vMax(vDot(N,L),0.0);
    float LoH = vMax(vDot(L,H),0.0);
    if( NoL > kEpsilon){
    #ifdef EVisuPBR
      float Vis = 0.25 / max(NoL + NoV - NoV * NoL, 1e-6);
      Vis *= 4.0 * NoL * VoH / max(NoH, 1e-6);
    #else
      float Vis = UnrealVisibility(r,NoL,NoV);
    #endif
      vec2 Fc = OptimizedSchlickFresnel(LoH);
      A += Fc.x * Vis;  
      B += Fc.y * Vis;
      samples += 1;
    }
  }
  vec2 res = vec2( A, B ) / vMax(samples,1);
  return res;
}
#endif // Fabrics
