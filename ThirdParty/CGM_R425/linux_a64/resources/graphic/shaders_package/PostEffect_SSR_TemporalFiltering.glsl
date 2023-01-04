vec4 clip_aabb(const in vec4 minimum, const in vec4 maximum, const in vec4 color) 
{
  const float eps = 0.00000001;
  vec4 center = 0.5 * (maximum + minimum);
  vec4 extents = 0.5 * (maximum - minimum) + eps;
  vec4 offset = color - center;
  vec4 ts = vAbs(offset / extents);
  float t = vMax(vMax(ts.r, ts.g), vMax(ts.b, ts.a));

  if(t > 1.0)
    return center + offset / vMax(1.0, t);
  else
    return color; // point inside aabb
}

vec3 GetWorldPos(vec3 screenPos)
{
  vec4 worldPos = vec4(cb_PostEffectAuto.u_ViewProjInverseMatrix *  vec4(screenPos,1.0));
  return worldPos.xyz / worldPos.w;
}

vec2 GetVelocity(vec2 uv)
{
    return GetEffectTexture(MotionVectorMap, uv).xy;
}

vec3 GetViewRay(vec2 uv)
{
    vec4 _CamScreenDir = vec4(1.0 / cb_PostEffectAuto.u_ProjectionMatrix[0][0], 1.0 / cb_PostEffectAuto.u_ProjectionMatrix[1][1], 1, 1);
    vec3 ray = vec3(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, 1.0);
    ray *= _CamScreenDir.xyz;
    ray = ray * (cb_PostEffectAuto.u_NearFar.y / ray.z);
    return ray;
}

vec2 CalculateMotion(float depth, vec2 inUV)
{
  vec3 ray = GetViewRay(inUV);
  vec3 vPos = ray * depth;
  vec4 worldPos = cb_PostEffectAuto.u_ViewInverseMatrix * vec4(vPos, 1.0);

  vec4 prevClipPos = (cb_PostEffectAuto.u_PrevViewProjMatrix * worldPos);
  vec4 curClipPos = (cb_PostEffectAuto.u_ViewProjMatrix * worldPos);

  vec2 vPosHCur  = (curClipPos.xy / curClipPos.w);
  vec2 vPosHPrev  = (prevClipPos.xy / prevClipPos.w);

  vec2 vPosCur  = (vPosHCur.xy + 1.0) / 2.0;
  vec2 vPosPrev  = (vPosHPrev.xy + 1.0) / 2.0;

  return vPosCur - vPosPrev;
}

vec2 offset[9] ={vec2(-2.0, 2.0), vec2(0.0, 2.0), vec2(2.0, 2.0), vec2(-2.0, 0.0), vec2(0.0, 0.0),
                   vec2(2.0, 0.0), vec2(-2.0, -2.0), vec2(0.0, -2.0), vec2(2.0, -2.0)};


void main()
{
  vec2 texelSize = vec2(1.0) / vTextureSize(CurrentFrame, 0).xy;
  vec2 currentUV = vTexCoord;
  vec2 MotionVector = GetEffectTexture(MotionVectorMap, vTexCoord).xy;
 
  vec4 hitPacked = GetEffectTexture(RaytraceMap, vTexCoord);
  vec3 hitViewPos = UVToViewPos(hitPacked.xy);

  vec2 CurrentVelocity  = GetVelocity(currentUV);
  float geomDepth = getLinearDepth(currentUV);
  float hitDepth = getLinearDepth(hitPacked.xy);

  vec2 reflectionCameraVelocity = CalculateMotion(hitDepth, currentUV);
  vec2 hitCameraVelocity = CalculateMotion(hitDepth, hitPacked.xy);
  vec2 cameraVelocity = CalculateMotion(geomDepth, currentUV);
  vec2 hitVelocity = GetVelocity(hitPacked.xy);

  vec2 velocityDiff = cameraVelocity - CurrentVelocity;

  vec2 hitVelocityDiff = hitCameraVelocity - hitVelocity;
  float objectVelocityMask = vSaturate(dot(velocityDiff, velocityDiff) * cb_PostEffectAuto.u_ViewpointSize.x * 100);
  float hitObjectVelocityMask = vSaturate(dot(hitVelocityDiff, hitVelocityDiff) * cb_PostEffectAuto.u_ViewpointSize.x * 100);
  vec2 objectVelocity = CurrentVelocity * objectVelocityMask;
  vec2 hitObjectVelocity = hitVelocity * hitObjectVelocityMask;

  vec2 reflectVelocity = vMix(vMix(reflectionCameraVelocity, hitObjectVelocity, hitObjectVelocityMask), objectVelocity, objectVelocityMask);

  vec2 velocity = MotionVector;
  #ifdef RayBasedReprojection
  velocity = reflectVelocity;
  #endif

  vec2 prevUV = currentUV - velocity;
  
  vec4 currentColor = vTexture(CurrentFrame, currentUV);
  vec4 prevColor = vTexture(PreviousFrame, prevUV);

  vec4 cmin = vec4(100.0);
  vec4 cmax = vec4(0.0);

  for(int i = 0; i < 9; ++i)
  {
     vec2 OffsetUV = offset[i] * texelSize;
     vec4 val  = vTexture(CurrentFrame, currentUV + OffsetUV);
     cmin = vMin(cmin, val);
     cmax = vMax(cmax, val);
  }

  prevColor = clip_aabb(cmin, cmax, prevColor);
  float lum0 = GetLuminance(currentColor.rgb);
  float lum1 = GetLuminance(prevColor.rgb);

  float unbiased_diff = vAbs(lum0 - lum1) / vMax(lum0, vMax(lum1, 0.2));
  float unbiased_weight = 1.0 - unbiased_diff;
  float unbiased_weight_sqr = unbiased_weight * unbiased_weight;
  float k_feedback = vMix(0.88,0.91, unbiased_weight_sqr);

  FRAGCOLOR = vMix(currentColor, prevColor, k_feedback);
 
}

