
const int   NUM_AO_SAMPLE_DIR     = 6;
const float NUM_AO_SAMPLE_DIR_INV = 0.166666667;

#ifndef NUM_AO_STEPS
#define NUM_AO_STEPS 10
#endif

vec3 g_SampleDirs[NUM_AO_SAMPLE_DIR] = vec3[NUM_AO_SAMPLE_DIR]
(
  cb_VoxelAO.u_SamplingDir0,
  cb_VoxelAO.u_SamplingDir1,
  cb_VoxelAO.u_SamplingDir2,
  cb_VoxelAO.u_SamplingDir3,
  cb_VoxelAO.u_SamplingDir4,
  cb_VoxelAO.u_SamplingDir5
  );

void main()
{
  vec4 col = vec4(0, 0, 0, 1.0);

  vec4 pt;
  if (!ComputePointInViewSpace(vTexCoord.xy, pt)) discard;

#ifdef DYNAMIC_RADIUS
  float radius  = cb_VoxelAO.u_Radius * cb_VoxelAO_Auto.u_ViewBoundingBox.w;
#else
  float radius  = cb_VoxelAO.u_Radius;
#endif

  // Compute tangente and binormal
  vec3  origin      = cb_VoxelAO_Auto.u_ViewBoundingBox.xyz;
  vec3  normal      = GetNormal(vTexCoord.xy).xyz;
  vec3  tangente    = vNormalize(origin - normal * vDot(normal, origin));
  vec3  bitangente  = vCross(normal, tangente);

  mat3  transfoToNormal;
  transfoToNormal[0] = tangente;
  transfoToNormal[1] = bitangente;
  transfoToNormal[2] = normal;

#if MIPMAP_MODE==3
  // Main axis in View space
  vec3 viewMainAxis[3];
  viewMainAxis[0] = (cb_VoxelAO_Auto.u_ViewInverseTranspose * vec4(1,0,0,0)).xyz; 
  viewMainAxis[1] = (cb_VoxelAO_Auto.u_ViewInverseTranspose * vec4(0,1,0,0)).xyz; 
  viewMainAxis[2] = (cb_VoxelAO_Auto.u_ViewInverseTranspose * vec4(0,0,1,0)).xyz; 
#endif

  float voxelNum  = float(VOXEL_SIZE);
  float voxelSize = cb_VoxelAO_Auto.u_ViewBoundingBox.w / voxelNum;

  vec3  startSamplePos      = pt.xyz  + cb_VoxelAO.u_OffsetMultiplier * normal * 1.732050808 * voxelSize;
  float startSampleDistance = cb_VoxelAO.u_StartDistanceMultiplier * voxelSize; //1.4142 * voxelSize; 

  float totalAo         = 0;
  float angleMultiplier = cb_VoxelAO.u_AngleMultiplier / voxelSize;

  for (int sampleDir = 0; sampleDir < NUM_AO_SAMPLE_DIR; sampleDir++)
  {
    vec3  coneDir         = transfoToNormal * g_SampleDirs[sampleDir];
    float ao              = 0;
    float sampleDistance  = startSampleDistance;

    for (int i = 0; i < NUM_AO_STEPS; i++)
    {
      float mipLevel        = vClamp(vLog2(vMax(1.0, angleMultiplier * sampleDistance)), 0.0, float(VOXEL_MIP_MAX - 1));
      vec3  samplePos       = vFma(coneDir, vec3(sampleDistance), startSamplePos);
      vec3  sampleVoxelPos  = (cb_VoxelAO_Auto.u_TransfoViewToVoxel * vec4(samplePos, 1.0)).xyz;

#if MIPMAP_MODE==3
      vec3  occValues = vTextureLod(s_VoxelMap, sampleVoxelPos, mipLevel).xyz;
      occValues.x *= vAbs(vDot(viewMainAxis[0], coneDir));
      occValues.y *= vAbs(vDot(viewMainAxis[1], coneDir));
      occValues.z *= vAbs(vDot(viewMainAxis[2], coneDir));
      float occValue = occValues.x + occValues.y + occValues.z;
#else
      float occValue = vTextureLod(s_VoxelMap, sampleVoxelPos, mipLevel).x;
#endif

      ao              = vFma(ao, 1.0-occValue, occValue);
      sampleDistance *= cb_VoxelAO.u_DistanceMultiplier;

      if (sampleDistance > radius || ao >= 1.0)
        break;
    }

    totalAo += vClamp(ao, 0.0, 1.0);
  }

  if (totalAo > 0)
  {
    //-------------------------------------
    // Average

    totalAo *=  NUM_AO_SAMPLE_DIR_INV;

    //-------------------------------------
    // Weighted 

    totalAo = 1.0 - vPow(1.0 - totalAo, cb_VoxelAO.u_Power);
    totalAo = smoothstep(cb_VoxelAO.u_AOMin, cb_VoxelAO.u_AOMax, totalAo);
    totalAo = vClamp(totalAo * cb_VoxelAO.u_Color.w, 0.0, 1.0);
  }

#ifdef OUTPUT_AO_VALUE
  FRAGCOLOR = vec4(totalAo);
#else
  FRAGCOLOR = vec4(cb_VoxelAO.u_Color.xyz, totalAo);
#endif
}
