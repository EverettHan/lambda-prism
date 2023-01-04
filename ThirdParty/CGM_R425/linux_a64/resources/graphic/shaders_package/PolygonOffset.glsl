
/**
* Defines depth offset constants based on OptionsGrammer pushed
*/
#if defined(UseFragmentDepthOffset) && (UseFragmentDepthOffset==16)
#	define ConstantDepthOffset 0.00001525902
#elif defined(UseFragmentDepthOffset) && (UseFragmentDepthOffset==32)
#	define ConstantDepthOffset 2.3283064e-10
#else
#	define ConstantDepthOffset 5.96046483e-8
#endif

#define ePolygonOffsetBackward2   0
#define ePolygonOffsetBackward1   1
#define ePolygonOffsetBackward0   2
#define ePolygonOffsetNeutral     3 // SAX Parser will not activate polygon offset in this case
#define ePolygonOffsetFrontward0  4 // NTS manipulators in front of everyone but the curves
#define ePolygonOffsetFrontward1  5 // NTS curves in front of every one
#define ePolygonOffsetDefault     6 // Don't care, just default
#define ePolygonOffsetFrontward2  7 // To draw polygon in view mode polygon VIEW_POLYGON_WITH_MESH (when offset mode is set to edge)

// This condition means, nobody overrid the polygon offset value in their PDSFX and 
// we use the default offset
#if  !defined(FragmentDepthOffsetForSurface) && defined(FragmentDepthOffsetForLogZ)
# define FragmentDepthOffsetForSurface  ePolygonOffsetDefault
#endif

#ifndef IS_SSAA
# define IS_SSAA 1.0
#endif
// Ideally we should test these values (eBackward..eFrontward) for the case where 
// surfaces (skin/vloumes) are not pushed back and lines are pushed forward
// We probably do not need to offset by same factors for this case
// and we should adjust these values correctly. Currently I set it to 0 for all cases,
// I need to do some manual testing and find the cases where Frontward0 is used for eg..
#ifdef UseFragmentDepthOffset
# define PolygonOffsetSlopeAdjustment  0.0
# define PolygonOffsetConstAdjustment  0.0
#else
# define PolygonOffsetSlopeAdjustment  0.0
# define PolygonOffsetConstAdjustment  0.0
#endif

#if  defined(FragmentDepthOffsetForLines)

# define PolygonOffsetSlopeFactor -1.1
# define PolygonOffsetConstFactor -1.0

#elif defined(FragmentDepthOffsetForSurface)

#if FragmentDepthOffsetForSurface == ePolygonOffsetBackward2

# define PolygonOffsetSlopeFactor 4.0
# define PolygonOffsetConstFactor 4.0

#elif FragmentDepthOffsetForSurface == ePolygonOffsetBackward1

# define PolygonOffsetSlopeFactor 2.2
# define PolygonOffsetConstFactor 3.0

#elif FragmentDepthOffsetForSurface == ePolygonOffsetBackward0

# define PolygonOffsetSlopeFactor 1.0
# define PolygonOffsetConstFactor 1.0

#elif FragmentDepthOffsetForSurface == ePolygonOffsetNeutral

# define PolygonOffsetSlopeFactor 0.0
# define PolygonOffsetConstFactor 0.0

#elif FragmentDepthOffsetForSurface == ePolygonOffsetFrontward0

# define PolygonOffsetSlopeFactor -0.9
# define PolygonOffsetConstFactor -1.0

#elif FragmentDepthOffsetForSurface == ePolygonOffsetFrontward1

# define PolygonOffsetSlopeFactor -2.0
# define PolygonOffsetConstFactor -2.0

#elif FragmentDepthOffsetForSurface == ePolygonOffsetFrontward2

# define PolygonOffsetSlopeFactor -4.0
# define PolygonOffsetConstFactor -4.0

#else

# define PolygonOffsetSlopeFactor 1.1
# define PolygonOffsetConstFactor 1.0

#endif

#else

# define PolygonOffsetSlopeFactor 1.1
# define PolygonOffsetConstFactor 1.0

#endif


#if defined(FragmentDepthOffsetForSurface) && defined(FragmentStage)

float GetPolygonOffset(float depth)
{
  float constFactor = PolygonOffsetConstFactor + PolygonOffsetConstAdjustment;
  float slopeFactor = PolygonOffsetSlopeFactor + PolygonOffsetSlopeAdjustment;

  float dFdxOfZ = abs(vDFdx(depth));
  float dFdyOfZ = abs(vDFdy(depth));
  float slope = vClamp(vMax(dFdxOfZ, dFdyOfZ), 1e-6, 0.001);
  return (slope * slopeFactor) + (ConstantDepthOffset * constFactor);
}

#elif defined(FragmentDepthOffsetForLines) && defined(FragmentStage)

vec2 GetScreenRatio()
{
  // Compute fragments near value from [0,1] to [-1,+1] in clip space
  return vec2(2.0 / IS_SSAA) / vec2(_sbCbCamera.ScreenSize);
}


#ifdef LogDepth
float GetPolygonOffset(float depth)
#else
float GetPolygonOffset(float depth)
#endif
{
  float constFactor = PolygonOffsetConstFactor;
  float slopeFactor = PolygonOffsetSlopeFactor;

  vec3 vN;
  vec2 vTexPos = (gl_FragCoord.xy - 0.5) / _sbCbCamera.ScreenSize;
  vec2 vC = vFma(vTexPos, vec2(2.0), vec2(-1.0));

#if !defined(IS_MSAA)
  vN = texture(DepthOffsetNormalMap, vTexPos).xyz;
#else
  ivec2 texCoord = ivec2(gl_FragCoord.xy);
  vN = texelFetch(DepthOffsetNormalMap, texCoord, gl_SampleID).xyz;
#endif
  vN = vFma(vN, vec3(2.0), vec3(-1.0));
  vN = normalize(vN);
  
  vec2 sr = GetScreenRatio();

#ifdef PROJECTION_CONIC
  
  mat4 P = vGetProjMatrix();
  float K = vDot(vec3(P[1][1] * (vC.x + P[2][0]), P[0][0] * (vC.y + P[2][1]), -P[0][0] * P[1][1]), vN);
  vec2 offset = vec2(P[1][1] * vN.x*sr.x, P[0][0] * vN.y*sr.y);
#ifdef LogDepth
  float logFactor = vGetNearFarLogFactor().z;
  float dFdxOfZ = abs(vLog((K + offset.x) / K) * logFactor);
  float dFdyOfZ = abs(vLog((K + offset.y) / K) * logFactor);
  float slope = vClamp(vMax(dFdxOfZ, dFdyOfZ), 1e-5, 0.001);
#else
  float factor = (-depth - 0.5 * (P[2][2] - 1)) / K;
  
  float dFdxOfZ = abs(offset.x * factor);
  float dFdyOfZ = abs(offset.y * factor);
  float slope = vClamp(vMax(dFdxOfZ, dFdyOfZ), 1e-6, 0.001);
#endif

#else

  mat4 P = vGetProjMatrix();
  // problem is, the slope will be huge as the normal deviates away from view
  // but we dont care about offsetting if the normal is not looking towards us
  // so we clamp the z half way through, although this makes the equation incorrect.
  float z = vClamp(abs(vN.z), 0.01, 1.0);
  vec2 fac = vec2(P[0][0], P[1][1]) * z;
  // calculate absolute values for the clamp to work (hence the negation)
  vec2 d = abs(vN.xy) * sr * -P[2][2];
  vec2 dFdz = d / fac;
  float slope = vClamp(vMax(dFdz.x, dFdz.y), 1e-5, 0.001);

#endif
  return (slope * slopeFactor) + (ConstantDepthOffset * constFactor);
}

#endif

