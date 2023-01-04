// GGX micro facet model
vec3 ImportanceSampleGGX( vec2 Xi, float Roughness, vec3 N )
{
  Xi.x = vMod(Xi.x, 1.0);
  Xi.y = vMod(Xi.y, 1.0);
  float a = Roughness * Roughness;
  float a2 = a * a;
  float Phi = 2 * PI * Xi.x;
  float CosTheta = vSqrt( (1 - Xi.y) / ( 1 + (a2 - 1) * Xi.y ) );
  float SinTheta = vSqrt( 1 - CosTheta * CosTheta );
  vec3 H;
  H.x = SinTheta * cos( Phi );
  H.y = SinTheta * sin( Phi );
  H.z = CosTheta;
  vec3 UpVector = abs(N.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
  vec3 TangentX = vNormalize( vCross( UpVector, N ) );
  vec3 TangentY = vCross( N, TangentX );
  
  // Tangent to world space
  return TangentX * H.x + TangentY * H.y + N * H.z;
}

vec4 ImportanceSampleWithPDF( vec2 Xi, float Roughness, vec3 N )
{
  Xi.x = vMod(Xi.x, 1.0);
  Xi.y = vMod(Xi.y, 1.0);
  float a = Roughness * Roughness;
  float a2 = a * a;
  float Phi = 2 * PI * Xi.x;
  float CosTheta = vSqrt( (1.0 - Xi.y) / ( 1.0 + (a2 - 1.0) * Xi.y ));
  float SinTheta = vSqrt(1.0 - CosTheta * CosTheta);
  vec3 H;
  H.x = SinTheta * cos( Phi );
  H.y = SinTheta * sin( Phi );
  H.z = CosTheta;

  //pdf
  float d = (CosTheta * a2 - CosTheta) * CosTheta + 1;
  float D = a2 / (PI * d * d);
  float pdf = D * CosTheta;

  // Tangent to world space
  vec3 UpVector = abs(N.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
  vec3 TangentX = vNormalize( vCross( UpVector, N ) );
  vec3 TangentY = vCross( N, TangentX );

  return vec4((TangentX * H.x + TangentY * H.y + N * H.z), pdf);
}

// Plane tools
struct Ray
{
	vec3 Start;
	vec3 Dir;
};

void ClipByPlane(Ray ray, vec4 plane, inout float t)
{
	float clipVal = vDot(plane, vec4(ray.Start, 1.0));
	float k = -clipVal / vDot(plane.xyz, ray.Dir);
	if (k < 0.0) return; // going out ?
	t = vMin(t, k);
}

// get linear z from "hyperbolic zbuffer"
float getLinearDepth(vec2 uv)
{
  float z = GetZ(uv);
  return ConvertZBufferToZView(z);
}

vec3 UVToViewVect(vec2 uv)
{
#ifdef PROJECTION_CONIC
	vec4 clipSpaceVect;
	clipSpaceVect.xy = 2.0 * uv - 1.0;
	clipSpaceVect.zw = vec2(0.0, 1.0);
	vec3 viewVect = vNormalize((cb_PostEffectAuto.u_ProjectionInverseMatrix * clipSpaceVect).xyz);
  return viewVect;
#else
  return vec3(0.0,0.0,-1.0);
#endif
}

vec3 UVToScreenEyeViewPos(vec2 uv)
{
#ifdef PROJECTION_CONIC
  return vec3(0.0);
#else
  vec4 clipSpaceVect;
	clipSpaceVect.xy = 2.0 * uv - 1.0;
	clipSpaceVect.zw = vec2(0.0, 1.0);
	return vec3((cb_PostEffectAuto.u_ProjectionInverseMatrix * clipSpaceVect).xy , 0.0);
#endif
}

vec3 UVAndDepthToViewPos(vec2 uv, float depth)
{
  vec3 viewVect = UVToViewVect(uv);
#ifdef PROJECTION_CONIC
  viewVect /= -viewVect.z;
#endif
  return depth*viewVect + UVToScreenEyeViewPos(uv);
}

vec3 GetViewRayPlaneInter(vec2 uv, vec3 vect, vec4 plane)
{
  Ray viewRay;
  viewRay.Start = UVToScreenEyeViewPos(uv);
  viewRay.Dir = vect;
  float inter = uintBitsToFloat(0x7f7fffff);
  ClipByPlane(viewRay, plane, inter);
  return viewRay.Start + inter * viewRay.Dir;
}

vec2 ViewPosToUV(vec3 viewPos)
{  
  vec4 hCoord = cb_PostEffectAuto.u_ProjectionMatrix * vec4(viewPos, 1.);
  vec2 uv;
  uv.x = 0.5 * hCoord.x / hCoord.w + 0.5;
  uv.y = 0.5 * hCoord.y / hCoord.w + 0.5;	
  return uv;
}

vec3 UVToViewPos(vec2 uv)
{
  float geomDepth = getLinearDepth(uv);
  return UVAndDepthToViewPos(uv, geomDepth);
}

vec3 GetViewPos(vec2 uv)
{
  float geomDepth = getLinearDepth(uv);
  vec3 screenPos = vec3(uv.xy * 2 - 1, geomDepth);
  vec4 viewPos = (cb_PostEffectAuto.u_ProjectionInverseMatrix *  vec4(screenPos,1.0));
  return viewPos.xyz / viewPos.w;
}

#ifdef SSR_ZHierarchyRayMarching
float getLinearDepthMip(vec2 uv, int mipLvl)
{
  float z = vTextureLod(ZMapWithMips, uv, float(mipLvl)).x;
  return ConvertZBufferToZView(z);
}

vec3 UVToViewPosMip(vec2 uv, int mipLvl)
{
  float geomDepth = getLinearDepthMip(uv, mipLvl);
  return UVAndDepthToViewPos(uv, geomDepth);
}
#endif

#ifdef SSR_LowResRayMarching
float getLinearDepthLowRes(vec2 uv)
{
  float z = vTexture(LowResZMap, uv).x;
  return ConvertZBufferToZView(z);
}

vec3 UVToViewPosLowRes(vec2 uv)
{
  float geomDepth = getLinearDepthLowRes(uv);
  return UVAndDepthToViewPos(uv, geomDepth);
}
#endif

#ifdef SSR_CustomZMap
float getLinearDepthCustom(vec2 uv)
{
  float z = vTexture(CustomZMap, uv).x;
  return ConvertZBufferToZView(z);
}

vec3 UVToViewPosCustom(vec2 uv)
{
  float geomDepth = getLinearDepthCustom(uv);
  return UVAndDepthToViewPos(uv, geomDepth);
}
#endif

float localBRDF(vec3 V, vec3 L, vec3 N, float Roughness)
{
  vec3 H = vNormalize(L + V);

  float NdotH = vSaturate(vDot(N,H));
  float NdotL = vSaturate(vDot(N,L));
  float NdotV = vSaturate(vDot(N,V));

  float a = Roughness * Roughness;
  float a2 = a * a;

  //D term
  float D = a2 / (PI * vSqrt(vSqrt(NdotH) * (a2 - 1) + 1));

  //G term
  float G_L = 1.0f / (NdotL + vSqrt(a2 + (1 - a2) * NdotL * NdotL));
  float G_V = 1.0f / (NdotV + vSqrt(a2 + (1 - a2) * NdotV * NdotV));
  float G = G_L * G_V;
 
  return D * G;
}

float SmithJointGGXVisibilityTerm(float NdotL, float NdotV, float roughness)
{
  float a = roughness;
  float lambdaV = NdotL * (NdotV * (1 - a) + a);
  float lambdaL = NdotV * (NdotL * (1 - a) + a);

  return 0.5f / (lambdaV + lambdaL + 1e-5f);
}

float GGXTerm(float NdotH, float roughness)
{
  float a = roughness * roughness;
  float d = (NdotH * a - NdotH) * NdotH + 1.0f; 
  return INV_PI * a / (d * d + 1e-7f);
}

float BRDF_Weight(vec3 V, vec3 L, vec3 N, float Roughness)
{
  vec3 H = vNormalize(L + V);

  float NdotH = vSaturate(vDot(N,H));
  float NdotL = vSaturate(vDot(N,L));
  float NdotV = vSaturate(vDot(N,V));

  float G = SmithJointGGXVisibilityTerm(NdotL, NdotV, Roughness);
  float D = GGXTerm(NdotH, Roughness);
  //vec3 specular = OptimizedSchlickFresnel(f0, vec3(1.0), vAbs(vDot(L, H)));
  return (D * G)* (PI / 4.0);
}

float GetLuminance(const vec3 iColor)
{ 
  const vec3 LUMINANCE = vec3(0.3, 0.6, 0.1);
	return vDot(LUMINANCE, iColor.xyz);
}

#ifdef SSR_ZHierarchyRayMarching

vec2 hierarchicalRayMarching(in vec2 uv0, in vec2 uv1, in float z0, in float z1, in float depthDiscontinuity, in float rayZBias, out vec3 hitPos, out bool hit)
{
  float invZ0 = 1.0 / z0;
  float invZ1 = 1.0 / z1;

  // We don't use custom Z map on this path because perfomance gain is not high enough and quality drop is really bad.
  vec2 rtSize = vec2(1.0 / (cb_PostEffectAuto.u_PixelSize.x ), 1.0 / (cb_PostEffectAuto.u_PixelSize.y));
  vec2 uvDir = uv1 - uv0;
  float uvLength = vLength(uvDir);
  vec2 dirSteps = vAbs(rtSize * uvDir / uvLength);
	uint nbSteps = uint(vMax(dirSteps.x, dirSteps.y));
  nbSteps = vMax(1, nbSteps);

  vec2 uv;
  vec3 geomPos;
  float geomBiasedPosZ;
  float rayPosZ;
  int mipLvl = 0;
  int powMip = 1;
  int k = 0;
  float ratio = 0.0;

  while ( mipLvl > -1 && k < nbSteps )
  {
    k += powMip;
    ratio = float(k) / float(nbSteps-1);
    uv = vMix(uv0, uv1, ratio);

#ifdef PROJECTION_CONIC
    float iz = vMix(invZ0, invZ1, ratio);
    rayPosZ = 1.0 / iz;
#else
    float z = vMix(z0, z1, ratio);
    rayPosZ = z;
#endif

    geomPos = UVToViewPosMip(uv, mipLvl);
    geomBiasedPosZ = geomPos.z * rayZBias;

    // Readable
    /*if ( rayPosZ < geomBiasedPosZ )
    {
      k -= powMip;
      mipLvl--;
      powMip /= 2;
    }
    else
    {
      mipLvl++;
      powMip *= 2;
    }*/

    // Optimized
    float state = vStep(geomBiasedPosZ, rayPosZ);
    k -= int((1.0-state)*float(powMip));
    mipLvl += int(vMix(-1.0, 1.0, state));
    float newPowMip = float(powMip) * vMix(0.5, 2.0, state);
    powMip = int(newPowMip);
  }

  if ( k >= nbSteps || vAbs(1.0 - rayPosZ / geomBiasedPosZ) > depthDiscontinuity )
  {
    hit = false;
    return vec2(0.0);
  }

  float z = vTextureLod(ZMapWithMips, uv, 0.0).x;
  if ( z < 0.0001 || z > 0.9999 )
  {
    hit = false;
    return vec2(0.0);
  }

  hitPos = geomPos;
  hit = true;
  return uv;
}

#endif

vec2 linearRayMarching(in float prec, in vec2 uv0, in vec2 uv1, in float z0, in float z1, in vec2 rtSize, in int rayMarchingLowRes, in float depthDiscontinuity, in float rayZBias, out vec3 hitPos, out bool hit)
{
  float invZ0 = 1.0 / z0;
  float invZ1 = 1.0 / z1;

  //vec2 rtSize = vec2(1.0 / cb_PostEffect_SSR_Radiance.u_ZMapPixelSize.x, 1.0 / cb_PostEffect_SSR_Radiance.u_ZMapPixelSize.y);
  vec2 _rtSize = rtSize;
  vec2 uvDir = uv1 - uv0;
  float uvLength = vLength(uvDir);
  vec2 dirSteps = vAbs(_rtSize * uvDir / uvLength);
	uint nbSteps = uint(prec * vMax(dirSteps.x, dirSteps.y));
  nbSteps = vMax(1, nbSteps);
  
  uint kStart = 1;
  uint kEnd = nbSteps;
  vec2 uv;
  uint k;
  float rayPosZ;
  vec3 geomPos;
  float geomBiasedPosZ;

#ifdef SSR_LowResRayMarching
  for (k = rayMarchingLowRes; k < kEnd; k += rayMarchingLowRes)
	{
    float ratio = float(k) / float(nbSteps-1);
    uv = vMix(uv0, uv1, ratio);

#ifdef PROJECTION_CONIC
    float iz = vMix(invZ0, invZ1, ratio);
    rayPosZ = 1.0 / iz;
#else
    float z = vMix(z0, z1, ratio);
    rayPosZ = z;
#endif

    geomPos = UVToViewPosLowRes(uv);
    geomBiasedPosZ = geomPos.z * rayZBias;

    if ( rayPosZ < geomBiasedPosZ )
    {
      kStart = k - rayMarchingLowRes;
      break;
    }
  }

  kEnd = kStart + rayMarchingLowRes + 2;
#endif

	for (k = kStart; k < kEnd; ++k)
	{
    float ratio = float(k) / float(nbSteps-1);
    uv = vMix(uv0, uv1, ratio);

#ifdef PROJECTION_CONIC
    float iz = vMix(invZ0, invZ1, ratio);
    rayPosZ = 1.0 / iz;
#else
    float z = vMix(z0, z1, ratio);
    rayPosZ = z;
#endif

#ifdef SSR_CustomZMap
    geomPos = UVToViewPosCustom(uv);
#else
    geomPos = UVToViewPos(uv);
#endif
    geomBiasedPosZ = geomPos.z * rayZBias;
    
    if ( rayPosZ < geomBiasedPosZ )
    {
      if (vAbs(1.0 - rayPosZ / geomBiasedPosZ) > depthDiscontinuity)
      {
        hit = false;
        return vec2(0.0);
      }
      break;
    }
  }

  if ( k < kEnd )
  {
#ifdef SSR_CustomZMap
    float z = vTexture(CustomZMap, uv).x;
#else
    float z = GetZ(uv);
#endif
    if ( z < 0.0001 || z > 0.9999 )
    {
      hit = false;
      return vec2(0.0);
    }
    hitPos = geomPos;
    hit = true;
    return uv;
  }

  hit = false;
  return vec2(0.0);
}

