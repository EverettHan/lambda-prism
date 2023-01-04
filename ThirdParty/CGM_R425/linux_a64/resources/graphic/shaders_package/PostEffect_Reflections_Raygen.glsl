
#define RTAO_RADIUS cb_PostEffect_HRTAO.aoRadius
#define RTAO_POWER 1.0

// Ray payload, which will be set to false if no geometry is hit
layout(location = 0) rayPayloadEXT Payload_t g_Payload;

vec3 getPosition(ivec2 pixel
#ifdef IS_MSAA
, int iSample
#endif
)
{
#ifdef IS_MSAA
  return uintBitsToFloat(imageLoad(positionNormals, pixel, iSample).xyz);
#else
  return uintBitsToFloat(imageLoad(positionNormals, pixel).xyz);
#endif
}

vec3 getNormal(ivec2 pixel
#ifdef IS_MSAA
, int iSample
#endif
)
{
  //uint compressedNormal = floatBitsToUint(imageLoad(positionNormals, pixel).y);
#ifdef IS_MSAA
  uint compressedNormal = imageLoad(positionNormals, pixel, iSample).w;
#else
  uint compressedNormal = imageLoad(positionNormals, pixel).w;
#endif

  if (compressedNormal == 0)
    return vec3(0);

  return decompress_unit_vec(compressedNormal);
} 

int traceRaysAmbientOcclusion(in vec3 origin, in vec3 direction)
{
  g_Payload.isHit = false;
  
  uint mask = 0xFF;
  
  traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, 99999999.0, 0);
  
  if(g_Payload.isHit)
    return 1;

  return 0;
}

#define vpX (_sbCbCamera.EyeWorldPos.x)
#define vpY (_sbCbCamera.EyeWorldPos.y)
#define vpZ (_sbCbCamera.EyeWorldPos.z)

float getFeatureSizeInWorldUnits(float distance, uint featureSizeInPixels, float minFeatureSize, uint lodOffset)
{

  float featureSize = tan(cb_PostEffect_HRTAO_Auto.pixelAngle*featureSizeInPixels) * distance;

  float log2Size = log2(featureSize/minFeatureSize)+lodOffset;
  float featureSizeRound = exp2(floor(log2Size))*minFeatureSize;

  return featureSizeRound;


}

void raygen()
{
  uvec3 launchSize = vGetLaunchSize();
  uvec3 launchID = vGetLaunchID();

  vec3 pos, normal;

  #ifdef IS_MSAA
    pos = getPosition( ivec2(launchID.xy), int(launchID.z));
    normal = getNormal(ivec2(launchID.xy), int(launchID.z));
  #else
    pos = getPosition( ivec2(launchID.xy));
    normal = getNormal(ivec2(launchID.xy));
  #endif

  if(all(equal(normal, vec3(0.0, 0.0, 0.0))))
  {
    #ifdef IS_MSAA
      imageStore(reflectionsOutput, ivec2(launchID.xy), int(launchID.z), vec4(0.0));
    #else
      imageStore(reflectionsOutput, ivec2(launchID.xy), vec4(0.0));
    #endif

    return;
  }

  // Move origin slightly away from the surface to avoid self-occlusion
  float posOffset = 4*getFeatureSizeInWorldUnits(length(pos - vec3(vpX, vpY, vpZ)), 1, 1e-10, 0);
  const vec3 origin = pos + normal * posOffset; 

  vec3 eye = vec3(vpX, vpY, vpZ);

  vec3 viewDir = normalize(origin - eye);

  vec3 direction = reflect(viewDir, normal);

  uint hit = traceRaysAmbientOcclusion(origin, direction);

  vec4 value;

  if(hit == 1)
  {
    //viewDir = normalize(origin - g_Payload.position);
    //
    //vec3 hitNormal = g_Payload.normal;
    //
    //if(dot(hitNormal, viewDir) < 0.0)
    //  hitNormal = -hitNormal;
    //
    //value = vec4(g_Payload.albedo * vec3(dot(viewDir, hitNormal)), 1.0);

    value = vec4(g_Payload.color, 1.0);
  }
  else
    value = vec4(0.0);

  #ifdef IS_MSAA
    imageStore(reflectionsOutput, ivec2(launchID.xy), int(launchID.z), value);
  #else
    imageStore(reflectionsOutput, ivec2(launchID.xy), value);
  #endif
}

void main()
{
  raygen();
}
