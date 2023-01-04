
const float FEEDBACK_MIN = 0.88;
const float FEEDBACK_MAX = 0.97;

#define CLOSEST_9TAP
//#define EDGE_AA_CLOSEST
#define EDGE_AA_MAXVELOCITY

vec3 RGB2YCoCg(vec3 RGBColor)
{
  mat3 m = mat3(
    0.25, 0.5, -0.25, 
    0.5, 0, 0.5, 
    0.25, -0.5, -0.25  
  );
  return m * RGBColor;
}

float luminance_RGB(vec3 iColor) {
  vec3 luminance_weight = vec3(0.176204, 0.812985, 0.0108109);
  return dot(iColor, luminance_weight);
}

vec4 clip_aabb_opti(const in vec4 minimum, const in vec4 maximum, const in vec4 color) {
  const float eps = 0.00000001;
  vec4 center = 0.5 * (maximum + minimum);
  vec4 extents = 0.5 * (maximum - minimum) + eps;
  vec4 offset = color - center;
  vec4 ts = abs(offset / extents);
  float t = max(max(ts.r, ts.g), max(ts.b, ts.a));
  return center + offset / max(1.0, t);
  // return t > 1.0 : center + offset / t : color;
}

vec4 taa(const in vec2 ssVel, const in vec2 texelSize) {
  vec4 tl = vTexture(s_CurrentFrame, vTexCoord + vec2(-texelSize.x, texelSize.y));
  vec4 t  = vTexture(s_CurrentFrame, vTexCoord + vec2(0.0, texelSize.y));
  vec4 tr = vTexture(s_CurrentFrame, vTexCoord + vec2(texelSize.x, texelSize.y));
  vec4 ml = vTexture(s_CurrentFrame, vTexCoord + vec2(-texelSize.x, 0.0));
  vec4 m  = vTexture(s_CurrentFrame, vTexCoord);
  vec4 mr = vTexture(s_CurrentFrame, vTexCoord + vec2(texelSize.x, 0.0));
  vec4 bl = vTexture(s_CurrentFrame, vTexCoord + vec2(-texelSize.x, -texelSize.y));
  vec4 b  = vTexture(s_CurrentFrame, vTexCoord + vec2(0.0, -texelSize.y));
  vec4 br = vTexture(s_CurrentFrame, vTexCoord + vec2(texelSize.x, -texelSize.y));

  // sharpen
  // https://github.com/Unity-Technologies/PostProcessing/blob/v1/PostProcessing/Resources/Shaders/TAA.cginc#L143
  // reduces blurring, but increases flickering with dense geometry
  vec4 corners = 2.0 * (tr + bl + br + tl) - 2.0 * m;
  m += (m - (corners * 0.166667)) * 2.718282 * 0.3;
  m = max(vec4(0.0), m);

  // Brian Karis neighbourhood rounding: http://advances.realtimerendering.com/s2014/epic/TemporalAA.pptx
  // average of rounded pattern with cross pattern
  vec4 cmin5 = min(mr, min(m, min(ml, min(t, b))));
  vec4 cmin = min(cmin5, min(tl, min(tr, min(bl, br))));
  vec4 cmax5 = max(mr, max(m, max(ml, max(t, b))));
  vec4 cmax = max(cmax5, max(tl, max(tr, max(bl, br))));
  cmin = 0.5 * (cmin + cmin5);
  cmax = 0.5 * (cmax + cmax5);

  // variance clamping
  // https://developer.download.nvidia.com/gameworks/events/GDC2016/msalvi_temporal_supersampling.pdf
  vec4 m1 = tl + t + tr + ml + m + mr + bl + b + br;
  vec4 m2 = tl*tl + t*t + tr*tr + ml*ml + m*m + mr*mr + bl*bl + b*b + br*br;

  vec4 mu = m1 / 9.0;
  vec4 sigma = sqrt(m2 / 9.0 - mu*mu);

  float gamma = 0.75;
  cmin = max(mu - gamma*sigma, cmin);
  cmax = min(mu + gamma*sigma, cmax);

  vec4 previousColor = vTexture(s_PreviousFrame, vTexCoord - ssVel);  
  vec4 previousColor_clipped = clip_aabb_opti(cmin, cmax, previousColor);
  
  if(length(ssVel) == 0.0) {        
    //return mix(vTexture(s_CurrentFrame, vTexCoord), previousColor_clipped, 0.985);
    return mix(m, previousColor_clipped, 0.985);
  }

  float lum0 = luminance_RGB(m.rgb);
  float lum1 = luminance_RGB(previousColor_clipped.rgb);
  float diff = abs(lum0 - lum1) / max(lum0, max(lum1, 0.2));
  float unbiased_weight = 1.0 - diff;
  float feedback = mix(FEEDBACK_MIN, FEEDBACK_MAX, unbiased_weight * unbiased_weight);
  return mix(m, previousColor_clipped, feedback);
}

#define NEIGHBOUR_SET_IF_DMIN_Z_GREATER(d, xx, yy) if(d < dmin.z) dmin = vec3(xx, yy, d);
#define NEIGHBOUR_CREATE_FROM_OFFSET(d, xx, yy) d = vTexture(s_CurrentDepthMap, uv + vec2(xx,yy)).x;//if (d < 0.1) d = 1.0; 
#define FIND_NEIGHBOUR_MIN(d, xx, yy) NEIGHBOUR_CREATE_FROM_OFFSET(d, xx, yy); NEIGHBOUR_SET_IF_DMIN_Z_GREATER(d, xx, yy)

vec3 closestDepthFragmentTexCoord(vec2 uv, vec2 texelSize) {
  float d;
  vec2 size = 2.0 * texelSize;
  vec3 dmin = vec3(0,0,0);
  NEIGHBOUR_CREATE_FROM_OFFSET(dmin.z, 0.0, 0.0);
  FIND_NEIGHBOUR_MIN(d, -size.x, size.y);
  FIND_NEIGHBOUR_MIN(d, size.x, size.y);
  FIND_NEIGHBOUR_MIN(d, -size.x, -size.y);
  FIND_NEIGHBOUR_MIN(d, size.x, -size.y);
  #ifdef CLOSEST_9TAP
    FIND_NEIGHBOUR_MIN(d, 0.0, size.y);
    FIND_NEIGHBOUR_MIN(d, -size.x, 0.0);
    FIND_NEIGHBOUR_MIN(d, size.x, 0.0);
    FIND_NEIGHBOUR_MIN(d, 0.0, -size.y);
  #endif
  return vec3(uv + dmin.xy, dmin.z);
}	

#define MAX_MOTION_VECTOR(a, b) length(a) > length(b) ? a : b
vec2 maxVeclocity(vec2 uv, vec2 texelSize) {
  vec2 m = vTexture(s_MotionVectorMap, uv).xy;
  vec2 size = 2.0 * texelSize;
  m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(-size.x, size.y)).xy);
  m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(size.x, size.y)).xy);
  m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(-size.x, -size.y)).xy);
  m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(size.x, -size.y)).xy);
  #ifdef CLOSEST_9TAP
    m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(0, size.y)).xy);
    m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(-size.x, 0)).xy);
    m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(size.x, 0)).xy);
    m = MAX_MOTION_VECTOR(m, vTexture(s_MotionVectorMap, uv + vec2(0, -size.y)).xy);
  #endif
  return m;
}

void main(void)
{
  vec2 texelSize = vec2(1.0) / textureSize(s_CurrentFrame, 0).xy;

  #ifdef EDGE_AA_CLOSEST
  vec3 closestDepthUVZ = closestDepthFragmentTexCoord(vTexCoord, texelSize);
  if (closestDepthUVZ.z == 0.0) {
      FRAGCOLOR = vTexture(s_CurrentFrame, vTexCoord);
      return;
  }
  vec2 fragMotionVector = GetEffectTexture(s_MotionVectorMap, closestDepthUVZ.xy).xy; // works for sampler2D as well as sampler2DMS contrarily to vTexture
  #elif defined EDGE_AA_MAXVELOCITY
  vec2 fragMotionVector = maxVeclocity(vTexCoord, texelSize);
  #else 
  vec2 fragMotionVector = GetEffectTexture(s_MotionVectorMap, vTexCoord).xy;
  #endif

  FRAGCOLOR = taa(fragMotionVector, texelSize); 
}
