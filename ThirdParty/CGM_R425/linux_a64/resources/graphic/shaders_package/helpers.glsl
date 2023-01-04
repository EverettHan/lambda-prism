const float kEpsilon = 0.00001;

// Tangent space
struct TangentSpace
{
  vec3 Pos;
  vec3 N;
#ifdef UseTangentSpace
  vec3 T;
  vec3 B;
#endif
};

//ftp://ftp.sgi.com/opengl/contrib/blythe/advanced99/notes/node177.html
vec2 ComputeSphereMapCoord(in vec3 r)
{
  r.z+=1.0;
  float m = 0.5/vSqrt(dot(r,r));
  return vec2(r.x*m+0.5, r.y*m+0.5);
}

vec3 vHalfVector(in vec3 L, in vec3 V)
{
  const vec3 res = L + V;
  const float len = length(res);
  return (len>kEpsilon) ? res*(1.0/len) : res; // avoid divide by 0
}

//A is the point
//B is a point on the line
//u is expected to be normalized and is a director vector of the line
float DistancePointToLine(vec3 A, vec3 B, vec3 u)
{
  vec3 C = cross(B-A, u);
  return sqrt(dot(C,C));
}

float vGaussian(in float x, in float mean, in float variance)
{
	float value = x - mean;
	value *= value;
	value /= 2.0 * variance;
	return vExp(-value);
}

float vGaussianKernel(in float x, in float mean, in float variance)
{
	float div = vSqrt(variance * 2.0 * PI);
	return vGaussian(x,mean,variance)/div;
}

// I am not sure that constant are optimized in branching code so I provide only a function per exponent
// Template code is note working on all platforms so now it is only for float

/////// FLOAT POW
float vPow2(in float iValue)
{
  return iValue*iValue;
}

float vPow3(in float iValue)
{
  return vPow2(iValue) * iValue;
}

float vPow4(in float iValue)
{
  float tmp = vPow2(iValue);
  return vPow2(tmp);
}

float vPow5(in float iValue)
{
  float tmp = vPow4(iValue);
  return tmp * iValue;
}

float vPow6(in float iValue)
{
  float tmp = vPow2(iValue);
  float tmp2 = vPow2(tmp);
  return tmp * tmp2;
}

float vPow7(in float iValue)
{
  float tmp = vPow6(iValue);
  return tmp * iValue;
}

float vPow8(in float iValue)
{
  float tmp = vPow4(iValue);
  return vPow2(tmp);
}

float vPow9(in float iValue)
{
  float tmp = vPow8(iValue);
  return tmp * iValue;
}

float vPow10(in float iValue)
{
  float tmp = vPow2(iValue);
  return vPow4(tmp) * tmp;
}



////// VEC3 pow
vec3 vPow2(in vec3 iValue)
{
  return iValue*iValue;
}

vec3 vPow3(in vec3 iValue)
{
  return vPow2(iValue) * iValue;
}

vec3 vPow4(in vec3 iValue)
{
  vec3 tmp = vPow2(iValue);
  return vPow2(tmp);
}

vec3 vPow5(in vec3 iValue)
{
  vec3 tmp = vPow4(iValue);
  return tmp * iValue;
}

////// saturates
float vSaturate(in float iValue)
{
	return vClamp(iValue,0.0,1.0);
}
vec2 vSaturate(in vec2 iValue)
{
	return vClamp(iValue,0.0,1.0);
}
vec3 vSaturate(in vec3 iValue)
{
	return vClamp(iValue,0.0,1.0);
}
vec4 vSaturate(in vec4 iValue)
{
	return vClamp(iValue,0.0,1.0);
}
////////
float vAffine(in float x, in float valueAt0, in float valueAt1) {
  return vFma(x,(valueAt1-valueAt0),valueAt0);
}

vec2 vAffine(in vec2 x, in vec2 valueAt0, in vec2 valueAt1) {
  return vFma(x,(valueAt1-valueAt0),valueAt0);
}

vec3 vAffine(in vec3 x, in vec3 valueAt0, in vec3 valueAt1) {
  return vFma(x,(valueAt1-valueAt0),valueAt0);
}

vec4 vAffine(in vec4 x, in vec4 valueAt0, in vec4 valueAt1) {
  return vFma(x,(valueAt1-valueAt0),valueAt0);
}

///////////
float vToTexCoord(in float x, in float minValue, in float maxValue) {
  return vClamp((vClamp(x, minValue, maxValue) - minValue) / (maxValue - minValue),0.0,1.0);
}

vec2 vToTexCoord(in vec2 x, in vec2 minValue, in vec2 maxValue) {
  return vClamp((vClamp(x, minValue, maxValue) - minValue) / (maxValue - minValue),0.0,1.0);
}

vec3 vToTexCoord(in vec3 x, in vec3 minValue, in vec3 maxValue) {
  return vClamp((vClamp(x, minValue, maxValue) - minValue) / (maxValue - minValue),0.0,1.0);
}

vec4 vToTexCoord(in vec4 x, in vec4 minValue, in vec4 maxValue) {
  return vClamp((vClamp(x, minValue, maxValue) - minValue) / (maxValue - minValue),0.0,1.0);
}


float vClampWithEpsilon(in float ioValue, in float iMin, in float iMax)
{
  return vClamp(ioValue, iMin+kEpsilon, iMax-kEpsilon);
}

///////////

vec3 getGeomTApprox(in vec3 N) {
  vec3 normN = vNormalize(N);
  float x = normN.x;
  float y = normN.y;
  float z = normN.z;

  vec3 T = vec3(0.0);

  if ( vAbs(z) > 0.0) {
    T.y = -vSign(z);
    T.x = vSign(z);
    T.z = - (T.x * x + T.y *y) / z;
    return vNormalize(T);
  }
  return vec3(0.0,0.0,1.0);
}

vec3 getGeomBApprox(in vec3 N, in vec3 T) {
  return vNormalize(vCross(vNormalize(N), vNormalize(T)));
}


vec3 Rotate3D(in vec3 iVec, in float iAngle, in vec3 iAxe) {
  float s = vSin(iAngle);
  float c = vCos(iAngle);
  float x = iAxe.x;
  float y = iAxe.y;
  float z = iAxe.z;

  mat3 I = mat3(1.0, 0.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 0.0, 1.0);

  mat3 Q = mat3(0.0, -z ,  y,
                 z , 0.0, -x,
                -y , x  , 0.0);

  mat3 rot = I + s * Q + (1.0 - c) * Q * Q;

  return rot * iVec;

}
/////// SphericalHarmonics

float zeroSphericalHarmonics() {
  return vSqrt(INV_PI) / 2.0;
}


///////////////////////////////////////////////////////////////////////////////
/// Unit vector compression
#if defined(V_NCOMPRESS_ENABLED) && (V_NCOMPRESS_ENABLED)

  #if defined(V_NCOMPRESS_OCT16)
    #define V_NCOMPUTE_COMPRESS_BSIZE 16
    #define NCompress_Project_Impl NCompress_Octahedron_Project
    #define NCompress_Unproject_Impl NCompress_Octahedron_Unproject

  #elif defined(V_NCOMPRESS_OCT24)
    #define V_NCOMPUTE_COMPRESS_BSIZE 24
    #define NCompress_Project_Impl NCompress_Octahedron_Project
    #define NCompress_Unproject_Impl NCompress_Octahedron_Unproject

  #elif defined(V_NCOMPRESS_OCT32)
    #define V_NCOMPUTE_COMPRESS_BSIZE 32
    #define NCompress_Project_Impl NCompress_Octahedron_Project
    #define NCompress_Unproject_Impl NCompress_Octahedron_Unproject

  #else
    #define NCompress_Project_Impl NCompress_Dummy_Project
    #define NCompress_Unproject_Impl NCompress_Dummy_Unproject
  #endif

  float vSigma(float x)
  {
    // uint signMask = 0x80000000 & floatBitsToUint(x);
    // return uintBitsToFloat(floatBitsToUint(1.0f) | signMask);
    return x >= 0.0f ? 1.0f : -1.0f;
  }

  float vCopySign(in float iBase, in float iSign)
  {
    return iSign >= 0.0f ? vAbs(iBase) : -vAbs(iBase);
  }

  // https://pdfs.semanticscholar.org/9f9e/9a03e932ffe8d95722721af8bfa36cb5e99b.pdf
  vec2 NCompress_Octahedron_Project(in vec3 iNormal)
  {
    vec3 normal = iNormal * 1.0f / (vAbs(iNormal.x) + vAbs(iNormal.y) + vAbs(iNormal.z));
    return normal.z >= 0.0f ?
      vec2(normal.x, normal.y) :
      vec2(vCopySign(1.0f - vAbs(normal.y), normal.x),
           vCopySign(1.0f - vAbs(normal.x), normal.y));
  }

  vec3 NCompress_Octahedron_Unproject(in vec2 iCoords)
  {
    float z = 1.0f - vAbs(iCoords.x) - vAbs(iCoords.y);
    vec3 n = z >= 0.0f ?
      vec3(iCoords, z) :
      vec3(vCopySign(1.0f - vAbs(iCoords.y), iCoords.x),
             vCopySign(1.0f - vAbs(iCoords.x), iCoords.y),
             z);
    return vNormalize(n);
  }

  vec2 NCompress_Dummy_Project(vec3 iRhs) { return vec2(0.0f); }

  vec3 NCompress_Dummy_Unproject(vec2 iRhs) { return vec3(0.0f); }

  uint NCompress_Compress16(vec3 iNormal)
  {
    return packSnorm4x8(vec4(NCompress_Project_Impl(iNormal), 0.0f, 0.0f));
  }

  vec3 NCompress_Uncompress16(uint iOct16)
  {
    return NCompress_Unproject_Impl(vec2(unpackSnorm4x8(iOct16)));
  }

  uint NCompress_Compress24(vec3 iNormal)
  {
    uint packedData = packSnorm2x16(NCompress_Project_Impl(iNormal));
    return ((packedData >> 4) & 0x000FFF) | ((packedData >> 8) & 0xFFF000);
  }

  vec3 NCompress_Uncompress24(uint iOct24)
  {
    uint packedData = ((iOct24 << 4) & 0x00FFF0) | ((iOct24 << 8) & 0xFFF00000);
    return NCompress_Unproject_Impl(unpackSnorm2x16(packedData));
  }

  uint NCompress_Compress32(vec3 iNormal)
  {
    return packSnorm2x16(NCompress_Project_Impl(iNormal));
  }

  vec3 NCompress_Uncompress32(uint iOct32)
  {
    return NCompress_Unproject_Impl(unpackSnorm2x16(iOct32));
  }

  vec3 NCompress_Uncompress(uint iOct)
  {
    #if V_NCOMPUTE_COMPRESS_BSIZE == 16
      return NCompress_Uncompress16(iOct);
    #elif V_NCOMPUTE_COMPRESS_BSIZE == 24
      return NCompress_Uncompress24(iOct);
    #elif V_NCOMPUTE_COMPRESS_BSIZE == 32
      return NCompress_Uncompress32(iOct);
    #else
      #error Not a valid compression size
    #endif
  }

  uint NCompress_Compress(vec3 iNormal)
  {
    #if V_NCOMPUTE_COMPRESS_BSIZE == 16
      return NCompress_Compress16(iNormal);
    #elif V_NCOMPUTE_COMPRESS_BSIZE == 24
      return NCompress_Compress24(iNormal);
    #elif V_NCOMPUTE_COMPRESS_BSIZE == 32
      return NCompress_Compress32(iNormal);
    #else
      #error Not a valid compression size
    #endif
  }

#endif
///////////////////////////////////////////////////////////////////////////////

#define D_C_STACK_MAX 3.402823466e+38f
  uint compress_unit_vec(vec3 nv)
  {
    // map to octahedron and then flatten to 2D (see 'Octahedron Environment Maps' by Engelhardt & Dachsbacher)
    if ((nv.x < D_C_STACK_MAX) && !isinf(nv.x))
    {
      const float d = 32767.0 / (abs(nv.x) + abs(nv.y) + abs(nv.z));
      int         x = int(roundEven(nv.x * d));
      int         y = int(roundEven(nv.y * d));

      if (nv.z < 0.0)
      {
        const int maskx = x >> 31;
        const int masky = y >> 31;
        const int tmp = 32767 + maskx + masky;
        const int tmpx = x;
        x = (tmp - (y ^ masky)) ^ maskx;
        y = (tmp - (tmpx ^ maskx)) ^ masky;
      }

      uint packd = (uint(y + 32767) << 16) | uint(x + 32767);
      if (packd == ~0u)
        return ~0x1u;
      return packd;
    }
    else
    {
      return ~0u;
    }
  }

  float short_to_floatm11(in int v)  // linearly maps a short 32767-32768 to a float -1-+1 //!! opt.?
  {
    return (v >= 0) ? (uintBitsToFloat(0x3F800000u | (uint(v) << 8)) - 1.0) :
      (uintBitsToFloat((0x80000000u | 0x3F800000u) | (uint(-v) << 8)) + 1.0);
  }

  vec3 decompress_unit_vec(uint packd)
  {
    if (packd != ~0u)  // sanity check, not needed as isvalid_unit_vec is called earlier
    {
      int x = int(packd & 0xFFFFu) - 32767;
      int y = int(packd >> 16) - 32767;

      const int maskx = x >> 31;
      const int masky = y >> 31;
      const int tmp0 = 32767 + maskx + masky;
      const int ymask = y ^ masky;
      const int tmp1 = tmp0 - (x ^ maskx);
      const int z = tmp1 - ymask;
      float     zf;
      if (z < 0)
      {
        x = (tmp0 - ymask) ^ maskx;
        y = tmp1 ^ masky;
        zf = uintBitsToFloat((0x80000000u | 0x3F800000u) | (uint(-z) << 8)) + 1.0;
      }
      else
      {
        zf = uintBitsToFloat(0x3F800000u | (uint(z) << 8)) - 1.0;
      }

      return normalize(vec3(short_to_floatm11(x), short_to_floatm11(y), zf));
    }
    else
    {
      return vec3(D_C_STACK_MAX);
    }
  }


#if defined(FragmentStage) || defined(RayHitStage)
//Expecting normalized vectors
//the view vector will be useless when the direct path will be ok
vec3 vGetOrientedNormal(in vec3 N, in vec3 V)
{
#if defined ForceNormalOrientation
 return vNormalize( ((vDot(V, N)>=0.)?1.:-1.0) * N); //this trick does not work...
#elif defined DoubleSidedLighting
  if (!vIsFrontFacing())
  {
    return -N;
  }
#endif
  return N;
}

//Two different point on the mesh should map to two different point in UV (COMPULSORY!)
//No discontinuties: UV mapping should not be discontinous on the mesh (note that if UV are accessed with wrapping, the UV space is toroidal...)
//No distortion: the shortest path between two points on the mesh should be the same as the distance in UV space up to a multiplicative constant
//Any point in UV space should map to a point on the mesh
#if !defined(GLESPlatform) && (GLSLVersion >= 400)
#define _RED fragColor = vec4(1.0,0.0,0.0,1.0); return;
#define _BLUE fragColor = vec4(0.0,1.0,0.0,1.0); return;
#define _GREEN fragColor = vec4(0.0,0.0,1.0,1.0); return;
//Some interestings links about Computing the cotangent space
//Normal Mapping without Pre-Computed Tangents by Christian Schueler
//http://www.thetenthplanet.de/archives/1180
//http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/
//http://c0de517e.blogspot.fr/2008/10/normals-without-normals.html
//http://mmikkelsen3d.blogspot.fr/2011/11/derivative-maps-in-xnormal.html
//Condtion to use the following algorithms
void _SBComputeTangentSpace(in vec3 iWorldPosition, in vec2 iTexCoords, in vec3 iNormal, out vec3 oTangent, out vec3 oBinormal)
{
  // compute derivations of the world position
  vec3 p_dx = vDFdx(iWorldPosition);
  vec3 p_dy = vDFdy(iWorldPosition);
  // compute derivations of the texture coordinate
  vec2 tc_dx = vDFdx(iTexCoords);
  vec2 tc_dy = vDFdy(iTexCoords);

  //Fallback for degenerate UV mappings.
  float alphaT = vStep(kEpsilon, abs(tc_dx.y) + abs(tc_dy.y)); //== 0.0 if no direction for tangent
  float alphaB = vStep(kEpsilon, abs(tc_dx.x) + abs(tc_dy.x)); //== 0.0 if no direction for binorm
  float alphaBT = 1.0 - vMax(alphaB, alphaT);               //== 0.0 if no direction for both

  //If both vectors are null, set them to canonical basis;
  //If only one is null, set it to be perpendicular to the other one.
  //Do not change anything otherwise.

  tc_dx.y = alphaT * tc_dx.y - (1.0 - alphaT)*(alphaB * tc_dy.x);
  tc_dy.y = alphaT * tc_dy.y + (1.0 - alphaT)*(alphaB * tc_dx.x) + alphaBT;

  tc_dx.x = alphaB * tc_dx.x - (1.0 - alphaB)*(alphaT * tc_dy.y) + alphaBT;
  tc_dy.x = alphaB * tc_dy.x + (1.0 - alphaB)*(alphaT * tc_dx.y);

  // new version for EVisuPBR

  #ifdef EVisuPBR

    // compute initial tangent and bi-tangent
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    vec3 b = normalize( tc_dx.x * p_dy - tc_dy.x * p_dx );

    float texDet = tc_dx.x * tc_dy.y - tc_dy.x * tc_dx.y;

    if(vIsFrontFacing() == false)
      texDet *= -1.0;

    // get new tangent from a given mesh normal
    vec3 x = cross(iNormal, t);
    t = cross(x, iNormal);
    oTangent = normalize(texDet*t);
    // get updated bi-tangent
    x = cross(b, iNormal);
    b = cross(iNormal, x);
    oBinormal = normalize(texDet*b);

  #else

    // compute initial tangent and bi-tangent
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    vec3 b = normalize( tc_dy.x * p_dx - tc_dx.x * p_dy ); // sign inversion

    // get new tangent from a given mesh normal
    vec3 x = cross(iNormal, t);
    t = cross(x, iNormal);
    oTangent = normalize(t);
    // get updated bi-tangent
    x = cross(b, iNormal);
    b = cross(iNormal, x);
    oBinormal = normalize(b);

  #endif
}
#else
void _SBComputeTangentSpace(in vec3 iWorldPosition, in vec2 iTexCoords, in vec3 iNormal, out vec3 oTangent, out vec3 oBinormal)
{
}
#endif //#ifndef GLESPlatform
#endif //#ifdef FragmentStage

float _SBsRGBToLinear(in float iValue)
{
  return (iValue < 0.04045) ? (iValue/12.92) : pow((iValue + 0.055)/1.055, 2.4);
}

vec3 _SBsRGBToLinear(in vec3 iValue)
{
  return vec3(_SBsRGBToLinear(iValue.x), _SBsRGBToLinear(iValue.y), _SBsRGBToLinear(iValue.z));
}
