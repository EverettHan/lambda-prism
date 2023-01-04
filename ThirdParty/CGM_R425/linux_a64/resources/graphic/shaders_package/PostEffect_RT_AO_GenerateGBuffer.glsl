
//#ifdef IS_MSAA
//  uniform coherent layout(rgba32f) image2DMS GBuffer;
//#else
//  uniform coherent layout(rgba32f) image2D GBuffer;
//#endif

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

vec2 ComputeUV()
{
  vec2 pixelCenter = vec2(gl_GlobalInvocationID.xy) + 0.5;
  uvec3 globalSize = gl_WorkGroupSize * gl_NumWorkGroups;
  return pixelCenter / vec2(globalSize.xy);
}
vec3 ComputeWorldPositionFromDepth(in float iDepth)
{
  vec3 coord = vec3(ComputeUV(), iDepth) * 2.0 - 1.0;
  vec4 viewPosition = _sbCbCamera.ProjInverseMatrix * vec4(coord, 1.0);
  viewPosition /= viewPosition.w;
  return vec3(_sbCbCamera.ViewInverseMatrix * viewPosition);
}

#ifdef IS_MSAA
  float GetDepth(int iSample)
  {
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    return texelFetch(ZMap, coord, iSample).x;
  }

  vec3 GetNormal(int iSample)
  {
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    vec3 viewNormal = texelFetch(NormalMap, coord, iSample).xyz*2.0 - 1.0;

    return normalize((_sbCbCamera.ViewInverseMatrix * vec4(viewNormal, 0.0)).xyz);
  }

  vec3 GetWorldPosition(int iSample)
  {
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    return texelFetch(WorldPosMap, coord, iSample).xyz;
  }
#else
  float GetDepth()
  {
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    return texelFetch(ZMap, coord, 0).x;
  }

  vec3 GetNormal()
  {
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    vec3 viewNormal = texelFetch(NormalMap, coord, 0).xyz*2.0-1.0;

    vec4 worldNormal = _sbCbCamera.ViewInverseMatrix * vec4(viewNormal, 0.0);

    return normalize(worldNormal.xyz);
  }

  vec3 GetWorldPosition()
  {
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    return texelFetch(WorldPosMap, coord, 0).xyz;
  }
#endif


void main(void)
{
  ivec2 coord = ivec2(gl_GlobalInvocationID.xy);

#ifdef IS_MSAA
  for (int i = 0; i<IS_MSAA; ++i)
  {
    float depth = GetDepth(i);
    uint normal = compress_unit_vec(GetNormal(i));

    if (depth == 1.0)
    {
      imageStore(GBuffer, coord, i, vec4(0.0));
    }
    else
    {
      vec3 worldPos;

    #ifdef UseWorldPos
      worldPos = GetWorldPosition(i);
    #else
      worldPos = ComputeWorldPositionFromDepth(depth);
    #endif

      imageStore(GBuffer, coord, i, vec4(worldPos, uintBitsToFloat(normal)));
    }
  }
#else
  float depth = GetDepth();
  uint normal = compress_unit_vec(GetNormal());

  if(depth == 1.0)
  {
    imageStore(GBuffer, coord, vec4(0.0));
  }
  else
  {
    vec3 worldPos;

  #ifdef UseWorldPos
    worldPos = GetWorldPosition();
  #else
    worldPos = ComputeWorldPositionFromDepth(depth);
  #endif

    imageStore(GBuffer, coord, vec4(worldPos, uintBitsToFloat(normal)));
  }
#endif
}
