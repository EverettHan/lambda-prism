/**
* @ fl9 QuickReview : Adapted to glsl
* © Dassault Systèmes 2014 – Do not reproduce, copy or use without a license from Dassault Systèmes
* CGFX Shader for CATIA V6
* Author: Andrea MACHIZAUD
* Date: U69 2014-02-04 - Mapping Operator w/o interfaces
* Date: U69 2014-03-08 - Aligned operator indexes on iRay MDL
*/

#if defined GPUMappingOperator && !defined DecalLighting
#define Planar 1
#define Spherical 2
#define Cubic 3
#define FiniteCylindrical 4
#define InfiniteCylindrical 5

vec2 pmTexCoords = vec2(0.0);
vec2 pmTexCoordsOffset = vec2(0.0);
vec3 pmTangent = vec3(0.0); 
vec3 pmBinormal = vec3(0.0); 

vec2 vGetUvs()
{
  return pmTexCoords;
}

#if defined(heightMapEnabled) && defined(FragmentStage)
  vec2 vGetUvOffset()
  {
    return pmTexCoordsOffset;
  }
#endif

vec3 vGetTangent()
{
  return pmTangent;
}

vec3 vGetBinormal()
{
  return pmBinormal;
}

vec2 ComputeDisplacement(in float displacement)
{
#ifdef heightMapEnabled
  vec3 t;
  vec3 b;
  vec3 n;

  vApplyWorldRotationOnVector(vGetTangent(), vGetBinormal(), v_ObjectSpaceNormal, t, b, n);

  t = vNormalize(t);
  b = vNormalize(b);
  n = vNormalize(n);

  mat3 worldToTangentSpace = mat3(t,b,n);

  vec3 eye = (vGetViewInvMatrix() * vec4(-vGetViewPosition(), 0.0)).xyz * worldToTangentSpace;
  vec3 normal = n * worldToTangentSpace;
  
  int nMinSamples = 8;
  int nMaxSamples = 32;
  
  float scale = sqrt(2.0)/length(mat2(PMat.heightMapUvTransform) * vec2(1.0));

  float l = length(eye.xy);
  float fParallaxLimit = -l / eye.z;
  fParallaxLimit *= displacement * scale;
  vec2 vOffsetDir = eye.xy*(1.0/l);
  vec2 vMaxOffset = vOffsetDir * fParallaxLimit;

  vec3 E = vNormalize(eye);
  vec3 N = vNormalize(normal);

  int nNumSamples = int(mix(float(nMaxSamples), float(nMinSamples), dot(E, N)));
  float fStepSize = 1.0 / float(nNumSamples);
  
  vec2 uvs = vGetUvs().xy;

  float fCurrRayHeight = 1.0;
  vec2 vCurrOffset = vec2(0.0);
  vec2 vLastOffset = vec2(0.0);

  float fLastSampledHeight = 1.0;
  float fCurrSampledHeight = 1.0;

  int nCurrSample = 0;

  while(nCurrSample < nNumSamples)
  {
    vec2 tmpuvs = uvs + vCurrOffset;

    #ifdef GPUMappingOperator
      tmpuvs = vec2(mat3(PMat.heightMapUvTransform) * vec3(tmpuvs, 1.0));
    #endif

    fCurrSampledHeight = textureLod(V_GET_TEXTURE_2D(heightMap), tmpuvs, 0.0).x;

    if(fCurrSampledHeight > fCurrRayHeight)
    {
      float delta1 = fCurrSampledHeight - fCurrRayHeight;
      float delta2 = ( fCurrRayHeight + fStepSize ) - fLastSampledHeight;

      float ratio = delta1/(delta1+delta2);

      vCurrOffset = (ratio) * vLastOffset + (1.0-ratio) * vCurrOffset;

      nCurrSample = nNumSamples + 1;
    }
    else
    {
      nCurrSample++;

      fCurrRayHeight -= fStepSize;

      vLastOffset = vCurrOffset;
      vCurrOffset += fStepSize * vMaxOffset;

      fLastSampledHeight = fCurrSampledHeight;
    }
  }

  return vCurrOffset;
#else
  return vec2(0.0);
#endif
}

void TransformUv()
{    
#ifdef TextureMatrix
  mat3 transformation = mat3(PMat.uvTransformation) * mat3(vGetTextureMatrix());
#else
  mat3 transformation = mat3(PMat.uvTransformation);
#endif
  pmTexCoords  = (transformation * vec3(pmTexCoords, 1.0)).xy;   
   
#if defined heightMapEnabled
  float displacement = pmGetDisplacement();

  #ifdef displacementMadModified
    displacement = vFma(PMadMat.m_displacement, displacement, PMadMat.a_displacement);
  #endif

  pmTexCoordsOffset = ComputeDisplacement(displacement);
#endif
}

#if (MappingOperator == Planar) /*******************************************************************************************************************/ 
void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
{// @NOTE This is the cartesian basis (same as the DS one), should we rotate that basis based on given mapping rotation ?  
  pmTexCoords = iPosition.xy ;    
#if defined PMComputeTB
  pmTangent = iX ;
  pmBinormal = iY;
#endif
}

#elif (MappingOperator == Spherical) /*******************************************************************************************************************/
void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
{  
  float radius3d = max(0.000001,length(iPosition.xyz));
  float z_by_radius3d = iPosition.z / radius3d;
  
  //trigo inverse  very bad for perfs!
  float theta = atan(iPosition.y, iPosition.x); //azimuth [-PI/2,+PI/2]
  float phi   = asin(z_by_radius3d );                      //polar   [-PI,+PI]

  pmTexCoords = vec2(theta, phi) * vec2(radius3d);

#if defined PMComputeTB
  float cos_theta = cos(theta), sin_theta = sin(theta), cos_phi = cos(phi), sin_phi = z_by_radius3d;
  pmTangent  = -sin_theta*iX + cos_theta*iY;
  pmBinormal = -cos_theta*sin_phi*iX - sin_theta*sin_phi*iY + cos_phi*iZ;
#endif

}

#elif (MappingOperator == Cubic) /*******************************************************************************************************************/
void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
{  
  vec3 absolute_normal = abs(iNormal);  
  float maxima_normal = max(absolute_normal.x, max(absolute_normal.y, absolute_normal.z));
  vec3 _sign;
  
  _sign.x = iPosition.x >= 0.0 ? 1.0 : -1.0;
  _sign.y = iPosition.y >= 0.0 ? -1.0 : 1.0;
  _sign.z = iPosition.z >= 0.0 ? 1.0 : -1.0;

  if(maxima_normal == absolute_normal.x)
  {    
    pmTexCoords = vec2(_sign.x * iPosition.y, iPosition.z );      
#if defined PMComputeTB
    pmTangent = _sign.x * iY;
    pmBinormal = iZ;
#endif

  } 

  else if(maxima_normal == absolute_normal.y)
  {    
    pmTexCoords = vec2(_sign.y * iPosition.x, iPosition.z );        
#if defined PMComputeTB
    pmTangent = _sign.y * iX;
    pmBinormal = iZ;
#endif
  }
  else
  {
    pmTexCoords = vec2(_sign.z * iPosition.x, iPosition.y);        
#if defined PMComputeTB
    pmTangent = _sign.z * iX;
    pmBinormal = iY;
#endif
  }
}

#elif (MappingOperator == FiniteCylindrical) /*******************************************************************************************************************/
void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
{  
  vec3 absolute_normal = abs(iNormal);    
  float maxima_normal = max(absolute_normal.x, max(absolute_normal.y, absolute_normal.z));

  if(maxima_normal == absolute_normal.z)
  {
    float signPosZ = vSignf(iPosition.z);
    pmTexCoords = vec2(signPosZ*iPosition.x, iPosition.y);        
#if defined PMComputeTB
    pmTangent = signPosZ*iX;
    pmBinormal = iY;
#endif
  }
  else
  {
    float radius2d = length(iPosition.xy);
    float radius3d = length(iPosition.xyz);
    float z_by_radius3d = v_ObjectSpacePosition.z/radius3d;
    float theta = atan(iPosition.y, iPosition.x); //azimuth [-PI/2,+PI/2]
    float phi = asin(z_by_radius3d);                      //polar   [-PI,+PI]    
    pmTexCoords = vec2(theta, iPosition.z) * vec2(radius2d, 1.0);       

#if defined PMComputeTB
    float cos_theta = cos(theta), sin_theta = sin(theta);
    pmTangent = -sin_theta*iX + cos_theta*iY;
    pmBinormal = iZ;
#endif
  }
}

#elif (MappingOperator == InfiniteCylindrical) /*******************************************************************************************************************/
void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
{  
  float radius2d = length(iPosition.xy);
  float radius3d = max(0.000001,length(iPosition.xyz));
  float z_by_radius3d = iPosition.z/radius3d;

  float theta = atan(iPosition.y, iPosition.x); //azimuth [-PI/2,+PI/2]
  float phi   = asin(z_by_radius3d);                      //polar   [-PI,+PI] 

  pmTexCoords = vec2(theta, iPosition.z) * vec2(radius2d, 1.0);  
#if defined PMComputeTB
  float cos_theta = cos(theta), sin_theta = sin(theta);
  pmTangent = -sin_theta*iX + cos_theta*iY;
  pmBinormal = iZ;
#endif
}
#endif
#endif
