#ifndef AO_RANDOM_KERNEL_SIZE
#define AO_RANDOM_KERNEL_SIZE 5
#endif 

//-----------------------------------------------------------------------
// Données pour le sampling

#if AO_QUALITY == 3
#define NUM_AO_SAMPLE       64
#define INV_NUM_AO_SAMPLE   0.015625
#define NUM_HBAO_STEP       8
#define INV_NUM_HBAO_STEP   0.125
#define NUM_HBAO_DIR        8
#define INV_NUM_HBAO_DIR    0.125

#elif AO_QUALITY == 2
#define NUM_AO_SAMPLE       32
#define INV_NUM_AO_SAMPLE   0.03125
#define NUM_HBAO_STEP       4
#define INV_NUM_HBAO_STEP   0.25
#define NUM_HBAO_DIR        8
#define INV_NUM_HBAO_DIR    0.125

#elif AO_QUALITY == 1
#define NUM_AO_SAMPLE       16
#define INV_NUM_AO_SAMPLE   0.0625
#define NUM_HBAO_STEP       2
#define INV_NUM_HBAO_STEP   0.5
#define NUM_HBAO_DIR        8
#define INV_NUM_HBAO_DIR    0.125

#else
#define NUM_AO_SAMPLE       8
#define INV_NUM_AO_SAMPLE   0.125
#define NUM_HBAO_STEP       2
#define INV_NUM_HBAO_STEP   0.5
#define NUM_HBAO_DIR        4
#define INV_NUM_HBAO_DIR    0.25

#endif

#ifdef HBAO_MODE

// HBAO
// sampling directions

#if NUM_HBAO_DIR == 16
const vec2 g_SamplingDirections[NUM_HBAO_DIR] = vec2[]
( 
  vec2( 1.0,        0.0),
  vec2( 0.923880,   0.382683),
  vec2( 0.707107,   0.707107),
  vec2( 0.382683,   0.923880),
  vec2( 0.0,        1.0),
  vec2(-0.382683,   0.923880),
  vec2(-0.707107,   0.707107),
  vec2(-0.923880,   0.382683),
  vec2(-1.0,        0.0),
  vec2(-0.923880,  -0.382683),
  vec2(-0.707107,  -0.707107),
  vec2(-0.382683,  -0.923880),
  vec2( 0.0,       -1.0),
  vec2( 0.382683,  -0.923880),
  vec2( 0.707107,  -0.707107),
  vec2( 0.923880,  -0.382683)
  );
#elif NUM_HBAO_DIR == 8
const vec2 g_SamplingDirections[NUM_HBAO_DIR] = vec2[]
( 
  vec2( 1.0,        0.0),
  vec2( 0.707107,   0.707107),
  vec2( 0.0,        1.0),
  vec2(-0.707107,   0.707107),
  vec2(-1.0,        0.0),
  vec2(-0.707107,  -0.707107),
  vec2( 0.0,       -1.0),
  vec2( 0.707107,  -0.707107)
  );
#elif NUM_HBAO_DIR == 4
const vec2 g_SamplingDirections[NUM_HBAO_DIR] = vec2[]
( 
  vec2( 1.0,  0.0),
  vec2( 0.0,  1.0),
  vec2(-1.0,  0.0),
  vec2( 0.0, -1.0)
  );
#endif

#else

// SSAO
// sampling sphere

const vec3 g_SamplingPoints[NUM_AO_SAMPLE] = vec3[]
( 
  vec3(0.334033, -0.00485205, -0.00401396)
  ,vec3(-0.453196, -0.267136, 0.16953)
  ,vec3(-0.147833, 0.413971, -0.106289)
  ,vec3(0.0909656, -0.10026, -0.646145)
  ,vec3(0.150717, 0.422825, 0.407178)
  ,vec3(-0.141224, -0.0126533, 0.671199)
  ,vec3(-0.568417, 0.123185, -0.109986)
  ,vec3(-0.0231788, -0.733836, 0.0740228)
#if AO_QUALITY >= 1
  ,vec3(-0.00159637, -0.000498002, 0.00229559)
  ,vec3(0.411656, -0.16241, 0.505242)
  ,vec3(-0.373892, 0.115395, -0.594764)
  ,vec3(0.236072, 0.72466, 0.0524527)
  ,vec3(-0.0849139, -0.231345, -0.121562)
  ,vec3(-0.0492975, -0.409624, 0.508015)
  ,vec3(0.363041, -0.233737, -0.358279)
  ,vec3(0.209588, 0.103554, -0.290493)
#endif
#if AO_QUALITY >= 2
  ,vec3(0.401735, -0.318318, 0.174997)
  ,vec3(-0.436293, 0.0988326, 0.230372)
  ,vec3(-0.00129735, -0.00939224, -0.102806)
  ,vec3(0.0474442, 0.094537, -0.0300616)
  ,vec3(-0.180245, 0.307443, 0.33575)
  ,vec3(0.0280045, 0.00316191, 0.201276)
  ,vec3(-0.487838, -0.48419, -0.148956)
  ,vec3(-0.207171, -0.0813871, -0.133753)
  ,vec3(0.43206, 0.435895, -0.210157)
  ,vec3(-0.333923, -0.35392, -0.450399)
  ,vec3(0.314904, -0.343625, -0.0974952)
  ,vec3(0.0534175, -0.0530132, -0.0137891)
  ,vec3(-0.0964412, 0.115755, 0.0301087)
  ,vec3(0.659795, -0.251509, -0.00948616)
  ,vec3(0.284603, -0.679033, 0.192659)
  ,vec3(-0.594049, -0.128511, -0.149513)
#endif
#if AO_QUALITY >= 3
  ,vec3(-0.0993712, -0.0448935, 0.131123)
  ,vec3(0.0378642, 0.0295742, 0.0420798)
  ,vec3(0.318821, 0.420695, 0.144036)
  ,vec3(-0.124789, 0.0113346, 0.00851022)
  ,vec3(0.0211496, -0.0700782, 0.0765306)
  ,vec3(0.10541, -0.385341, -0.223015)
  ,vec3(0.210974, 0.375526, -0.337413)
  ,vec3(0.143094, -0.0378247, 0.0881666)
  ,vec3(0.0316028, 0.00835372, -0.0194719)
  ,vec3(-0.105174, -0.0819994, -0.361506)
  ,vec3(-0.0668625, 0.11353, -0.206509)
  ,vec3(0.462185, 0.22895, 0.486543)
  ,vec3(-0.184853, 0.194595, -0.0915696)
  ,vec3(-0.691531, -0.139222, 0.253244)
  ,vec3(-0.0168934, 0.170312, 0.116528)
  ,vec3(-0.365722, 0.408222, 0.119991)
  ,vec3(-0.150832, -0.250913, 0.0894447)
  ,vec3(0.497968, -0.138399, -0.179585)
  ,vec3(-0.26334, 0.0724986, -0.179802)
  ,vec3(-0.170023, 0.381626, -0.374499)
  ,vec3(0.337389, 0.140773, 0.0734069)
  ,vec3(-0.0903141, -0.598759, -0.390624)
  ,vec3(0.0306866, 0.442725, -0.0222724)
  ,vec3(-0.266095, -0.672842, 0.184069)
  ,vec3(0.120698, -0.157573, -0.186859)
  ,vec3(-0.0323982, -0.0443528, -0.0156539)
  ,vec3(-0.275836, -0.0973231, -0.00244651)
  ,vec3(-0.361215, -0.105988, 0.300299)
  ,vec3(-0.0153334, 0.00449912, -0.0127475)
  ,vec3(0.261372, 0.111645, 0.201578)
  ,vec3(-0.432727, 0.525492, -0.2274)
  ,vec3(0.71651, 0.213321, 0.126158)
#endif
  );

#endif

//-----------------------------------------------------------------------
// Gestion de l'interleaving

#if defined(AO_STATIC_ARRAY) 

#if AO_RANDOM_KERNEL_SIZE==5
#define RANDOM_KERNEL_SIZE 25
#elif AO_RANDOM_KERNEL_SIZE==4
#define RANDOM_KERNEL_SIZE 16
#elif AO_RANDOM_KERNEL_SIZE==3
#define RANDOM_KERNEL_SIZE 9
#else
#define RANDOM_KERNEL_SIZE 4
#endif

const vec3 g_RandomVec[RANDOM_KERNEL_SIZE] = vec3[]
(
#ifdef HBAO_MODE

  //-------------------
  // HBAO
  
#if NUM_HBAO_DIR==8
    vec3(1.0,       0.0,      0.028384)
  , vec3(0.984807,  0.173648, 0.687323)
  , vec3(0.920504,  0.390731, 0.984566)
  , vec3(0.829037,  0.559192, 0.324061)
#if AO_RANDOM_KERNEL_SIZE>=3
  , vec3(0.996194,  0.087155, 0.402579)
  , vec3(0.970295,  0.241921, 0.804062)
  , vec3(0.945518,  0.325568, 0.606592)
  , vec3(0.891006,  0.453990, 0.110385)
  , vec3(0.754709,  0.656059, 0.226094)
#endif
#if AO_RANDOM_KERNEL_SIZE>=4
  , vec3(0.998629,  0.052335, 0.190385)
  , vec3(0.990268,  0.139173, 0.175609)
  , vec3(0.978147,  0.207911, 0.502579)
  , vec3(0.956304,  0.292371, 0.356592)
  , vec3(0.857167,  0.515038, 0.640062)
  , vec3(0.798635,  0.601815, 0.736592)
  , vec3(0.743144,  0.669130, 0.910062)
#endif
#if AO_RANDOM_KERNEL_SIZE>=5
  , vec3(0.983902,  0.178708, 0.982788)
  , vec3(0.759928,  0.650007, 0.717464)
  , vec3(0.872795,  0.488087, 0.183325)
  , vec3(0.966858,  0.255314, 0.139195)
  , vec3(0.918,     0.396579, 0.583697)
  , vec3(0.816095,  0.577918, 0.891568)
  , vec3(0.999992,  0.004074, 0.172613)
  , vec3(0.949442,  0.313941, 1)
  , vec3(0.910644,  0.413192, 0.833827)
#endif
#else
    vec3(0.999991, 0.00431444, 0.48384)
  , vec3(0.835038, 0.550193, 0.824061)
  , vec3(0.241266, 0.970459, 0.0878323)
  , vec3(0.0229604, 0.999736, 0.93466)
#if AO_RANDOM_KERNEL_SIZE >= 3
  , vec3(0.963209, 0.268753, 0.00140385)
  , vec3(0.730056, 0.683387, 0.35609)
  , vec3(0.0661545, 0.997809, 0.502579)
  , vec3(0.999854, 0.0170652, 0.976592)
  , vec3(0.478202, 0.87825, 0.704062)
#endif
#if AO_RANDOM_KERNEL_SIZE>=4
  , vec3(0.691707, 0.722178, 0.0141606)
  , vec3(0.581882, 0.813273, 0.994201)
  , vec3(0.890878, 0.454242, 0.561693)
  , vec3(0.959839, 0.280553, 0.278237)
  , vec3(0.979375, 0.20205, 0.748161)
  , vec3(0.389107, 0.921193, 0.369701)
  , vec3(0.0119363, 0.999929, 0.275704)
#endif
#if AO_RANDOM_KERNEL_SIZE>=5
  , vec3(0.936127, 0.351662, 0.982788)
  , vec3(0.154981, 0.987917, 0.71746)
  , vec3(0.523543, 0.852, 0.183325)
  , vec3(0.86963, 0.493704, 0.139195)
  , vec3(0.68545, 0.72812, 0.583697)
  , vec3(0.33202, 0.943272, 0.891568)
  , vec3(0.999967, 0.00814943, 0.172613)
  , vec3(0.802882, 0.596138, 1)
  , vec3(0.658545, 0.752541, 0.833827)
#endif

#endif
#else

  //-------------------
  // SSAO

#if AO_RANDOM_KERNEL_SIZE == 2
  vec3(0.976169, -0.216268, -0.0179732)
  , vec3(-0.27869, 0.960246, -0.0161202)
  , vec3(-0.234653, -0.163321, 0.958261)
  , vec3(-0.247553, -0.445313, -0.860473)
#elif AO_RANDOM_KERNEL_SIZE==3
  vec3(0.950112, -0.00278162, 0.311897)
  , vec3(0.0321772, 0.946652, 0.320646)
  , vec3(0.0303765, 0.000100603, 0.999539)
  , vec3(-0.0104614, -0.46911, -0.883078)
  , vec3(0.621298, -0.084058, 0.779052)
  , vec3(-0.821613, 0.195965, -0.535304)
  , vec3(0.3475, -0.521818, -0.77907)
  , vec3(-0.963802, -0.210932, 0.163075)
  , vec3(-0.428059, 0.0338914, -0.903115)
#elif AO_RANDOM_KERNEL_SIZE==4
  vec3(0.982499, 0.185745, -0.013958)
  , vec3(-0.0614875, 0.998045, -0.0111898)
  , vec3(-0.072059, 0.17451, 0.982015)
  , vec3(-0.109307, -0.156293, -0.981644)
  , vec3(0.733442, 0.0733636, 0.675781)
  , vec3(-0.668731, 0.302614, -0.679134)
  , vec3(0.167801, -0.218003, -0.961414)
  , vec3(-0.983072, -0.0233597, -0.181727)
  , vec3(-0.376318, 0.194556, -0.905833)
  , vec3(0.752839, -0.59258, 0.286499)
  , vec3(-0.926657, -0.205532, -0.314743)
  , vec3(0.0620897, 0.0404059, 0.997252)
  , vec3(0.85844, -0.493997, 0.138018)
  , vec3(-0.598125, -0.159037, 0.785464)
  , vec3(0.181803, -0.155114, 0.971024)
  , vec3(0.690564, -0.422964, -0.586704)
#elif AO_RANDOM_KERNEL_SIZE==5
  vec3(0.960296, 0.274776, -0.0482711)
  , vec3(-0.0217867, 0.999033, -0.0381943)
  , vec3(-0.0281167, 0.280583, 0.959418)
  , vec3(-0.0622982, -0.0498126, -0.996814)
  , vec3(0.762197, 0.178997, 0.622106)
  , vec3(-0.610721, 0.38519, -0.691844)
  , vec3(0.209116, -0.106236, -0.972103)
  , vec3(-0.971866, 0.0766489, -0.222714)
  , vec3(-0.321656, 0.280776, -0.904269)
  , vec3(0.836284, -0.48659, 0.252705)
  , vec3(-0.924106, -0.109391, -0.366145)
  , vec3(0.110424, 0.149603, 0.982561)
  , vec3(0.92149, -0.376162, 0.0967352)
  , vec3(-0.592781, -0.0588162, 0.803213)
  , vec3(0.238876, -0.0463654, 0.969942)
  , vec3(0.728274, -0.299609, -0.61632)
  , vec3(-0.389309, -0.215351, 0.895579)
  , vec3(0.775002, -0.220267, -0.59233)
  , vec3(-0.681002, -0.359332, -0.638056)
  , vec3(-0.13823, -0.980038, 0.142888)
  , vec3(0.860016, -0.165527, -0.482673)
  , vec3(-0.599353, -0.659337, 0.453928)
  , vec3(0.416823, -0.908951, -0.00818423)
  , vec3(-0.793046, -0.0722135, 0.604866)
  , vec3(-0.188499, 0.945449, 0.265696)
#endif

#endif
  );
#endif

vec2 GetTexCoord()
{
  return (vFloor(gl_FragCoord.xy) + 0.5)*cb_PostEffect_SSAO.u_PixelSize.xy;
}

vec3 ComputeRandomVec()
{
#if defined(ZMAP_ARRAY_ID) && defined(AO_STATIC_ARRAY)
  return g_RandomVec[ZMAP_ARRAY_ID];
#else
#if defined(ZMAP_ARRAY_ID)
  ivec2 coord = ivec2(ZMAP_ARRAY_ID % AO_RANDOM_KERNEL_SIZE, ZMAP_ARRAY_ID / AO_RANDOM_KERNEL_SIZE);
#else
  ivec2 coord = ivec2(vFloor(gl_FragCoord.xy)) % AO_RANDOM_KERNEL_SIZE;
#endif

#ifndef AO_MSAA
  return vTexelFetch(s_RandomTexture, coord, 0).xyz;
#else
  return vTexelFetch(s_RandomTexture, ivec3(coord.yx, gl_SampleID), 0).xyz;
#endif

#endif
}

vec4 ComputeNormal(vec2 iCoord)
{
  vec2 fullResCoord = vFloor(gl_FragCoord.xy);

#ifdef ZMAP_ARRAY_ID
#if AO_RANDOM_KERNEL_SIZE==4
  ivec2 offset = ivec2(ZMAP_ARRAY_ID & 3, ZMAP_ARRAY_ID >> 2);
#else
  ivec2 offset = ivec2(ZMAP_ARRAY_ID % AO_RANDOM_KERNEL_SIZE, ZMAP_ARRAY_ID / AO_RANDOM_KERNEL_SIZE);
#endif

  fullResCoord = vFma(fullResCoord, ivec2(AO_RANDOM_KERNEL_SIZE), offset); 
#else
  fullResCoord *= cb_PostEffect_SSAO.u_AOScale;
#endif
  vec4 normal = vTexelFetch(s_NormalMap, ivec2(fullResCoord), gl_SampleID);
  normal.xyz = vFma(normal.xyz, vec3(2.0), vec3(-1.0));
  return normal;
}


//-----------------------------------------------------------------------
// Calcul AO

struct AOData
{
  vec2  texCoord;
  vec3  viewPosition;
  vec3  viewNormal;
  vec3  randVec;
  float radius;
  float attenuation;
  float pixelDelta;
};

vec2 RotateDirection(const vec2 iDir, const vec2 iCosSin)
{
  return vec2(iDir.x*iCosSin.x - iDir.y*iCosSin.y,
    iDir.x*iCosSin.y + iDir.y*iCosSin.x);
}

float CommputeAO(const vec3 iSamplePosition, const AOData iData)
{
  vec3 dir = iSamplePosition - iData.viewPosition;

  float l2    = vDot(dir, dir);
  float angle = vDot(iData.viewNormal, dir) * vInversesqrt(l2);

#ifdef COMPUTEAO_LINEAR
  return vClamp(angle - cb_PostEffect_SSAO.u_SlotAngle, 0, 1) * vClamp(vFma(l2, iData.attenuation, 1.0), 0,1);

#else
  float occ = 0;
  if (l2>0.0  && angle>cb_PostEffect_SSAO.u_SlotAngle)
  {
    occ = 1.0/(vFma(l2, iData.attenuation, 1.0));

#ifdef AO_OPTIM_NORMAL_PONDERATION
    angle = 1.0-angle;
    angle = angle*angle;
    angle = angle*angle;
    occ *= (1.0-angle);
#endif
  }
  return occ;

#endif
}


#ifdef HBAO_MODE
//-------------------------------------------------
// HBAO
//-------------------------------------------------

float ComputeSampleHBAO(const int iDirIndex, const int iStepIndex, const AOData iData)
{
  float occ = 0.0;

  vec2  direction = RotateDirection(g_SamplingDirections[iDirIndex], iData.randVec.xy);
  float length    = vFma(iStepIndex + iData.randVec.z, iData.pixelDelta, 1.0); 
  vec2  coord     = vRound(direction * length) * cb_PostEffect_SSAO.u_PixelSize + iData.texCoord;

  vec3 samplePos;
  ComputePointInViewSpace(coord, samplePos);
  occ = CommputeAO(samplePos, iData);

  return occ;
}

#else

//-------------------------------------------------
// SSAO
//-------------------------------------------------

float ComputeSampleSSAO(const int iIndex, const AOData iData)
{
  float occ = 0.0;

  vec3 rayDir = g_SamplingPoints[iIndex];
  rayDir = vReflect(rayDir, iData.randVec);

  float delta = iData.radius*vSignf(vDot(rayDir, iData.viewNormal));
  vec3  newPt = delta*rayDir + iData.viewPosition;

  vec2 coord = ProjectPtOnScreen(newPt);

#ifdef AO_OPTIM_MINIMUM_PIXELSIZE
  // Permet d'eliminer les point qui seraient projet au meme endroit que le centre
  // ce qui cree du bruit pour rien
  vec2 tmp = coord-iData.texCoord;
  coord = iData.texCoord + vSign(tmp.xy)*vMax(cb_PostEffect_SSAO.u_PixelSize.xy, vAbs(tmp.xy));
#endif

  vec3 samplePos;
  if (ComputePointInViewSpace(coord, samplePos)==true && (samplePos.z>newPt.z))
  {
    occ = CommputeAO(samplePos, iData);
  }

  return occ;
}
#endif


//-----------------------------------------------------------------------
// Code principale

void main()
{ 
  float occ  = 0.0;

  float radius        = 0.0;
  float screenRadius  = 0.0;
  vec3 pt;
  
  vec2 coord = GetTexCoord(); 
  
  if (ComputePointAndRadiusInViewSpace(coord, pt, radius, screenRadius))
  {
    vec4 normal = ComputeNormal(coord);
    
    AOData aoData;

    aoData.texCoord         = coord;
    aoData.viewPosition     = pt.xyz;
    aoData.viewNormal       = normal.xyz;
    aoData.radius           = radius;
    aoData.attenuation = cb_PostEffect_SSAO.u_Attenuation/(radius*radius);
#ifdef COMPUTEAO_LINEAR
    aoData.attenuation      = -aoData.attenuation; 
#endif

    // texture random contenant une perturbation pour chacun des pixels du kernel de bruit
    aoData.randVec = ComputeRandomVec();

#ifdef HBAO_MODE
    
    float pixelRadius = screenRadius * cb_PostEffect_SSAO.u_AOMapSize.x;

    aoData.pixelDelta = (pixelRadius-1) * INV_NUM_HBAO_STEP;

    occ += ComputeSampleHBAO(0, 0, aoData);
    occ += ComputeSampleHBAO(1, 0, aoData);
    occ += ComputeSampleHBAO(2, 0, aoData);
    occ += ComputeSampleHBAO(3, 0, aoData);

    occ += ComputeSampleHBAO(0, 1, aoData);
    occ += ComputeSampleHBAO(1, 1, aoData);
    occ += ComputeSampleHBAO(2, 1, aoData);
    occ += ComputeSampleHBAO(3, 1, aoData);

#if AO_QUALITY >= 1  
    occ += ComputeSampleHBAO(4, 0, aoData);
    occ += ComputeSampleHBAO(5, 0, aoData);
    occ += ComputeSampleHBAO(6, 0, aoData);
    occ += ComputeSampleHBAO(7, 0, aoData);

    occ += ComputeSampleHBAO(4, 1, aoData);
    occ += ComputeSampleHBAO(5, 1, aoData);
    occ += ComputeSampleHBAO(6, 1, aoData);
    occ += ComputeSampleHBAO(7, 1, aoData);
#endif

#if AO_QUALITY >= 2  
    occ += ComputeSampleHBAO(0, 2, aoData);
    occ += ComputeSampleHBAO(1, 2, aoData);
    occ += ComputeSampleHBAO(2, 2, aoData);
    occ += ComputeSampleHBAO(3, 2, aoData);
    occ += ComputeSampleHBAO(4, 2, aoData);
    occ += ComputeSampleHBAO(5, 2, aoData);
    occ += ComputeSampleHBAO(6, 2, aoData);
    occ += ComputeSampleHBAO(7, 2, aoData);

    occ += ComputeSampleHBAO(0, 3, aoData);
    occ += ComputeSampleHBAO(1, 3, aoData);
    occ += ComputeSampleHBAO(2, 3, aoData);
    occ += ComputeSampleHBAO(3, 3, aoData);
    occ += ComputeSampleHBAO(4, 3, aoData);
    occ += ComputeSampleHBAO(5, 3, aoData);
    occ += ComputeSampleHBAO(6, 3, aoData);
    occ += ComputeSampleHBAO(7, 3, aoData);
#endif

#if AO_QUALITY >= 3
    occ += ComputeSampleHBAO(0, 4, aoData);
    occ += ComputeSampleHBAO(1, 4, aoData);
    occ += ComputeSampleHBAO(2, 4, aoData);
    occ += ComputeSampleHBAO(3, 4, aoData);
    occ += ComputeSampleHBAO(4, 4, aoData);
    occ += ComputeSampleHBAO(5, 4, aoData);
    occ += ComputeSampleHBAO(6, 4, aoData);
    occ += ComputeSampleHBAO(7, 4, aoData);

    occ += ComputeSampleHBAO(0, 5, aoData);
    occ += ComputeSampleHBAO(1, 5, aoData);
    occ += ComputeSampleHBAO(2, 5, aoData);
    occ += ComputeSampleHBAO(3, 5, aoData);
    occ += ComputeSampleHBAO(4, 5, aoData);
    occ += ComputeSampleHBAO(5, 5, aoData);
    occ += ComputeSampleHBAO(6, 5, aoData);
    occ += ComputeSampleHBAO(7, 5, aoData);

    occ += ComputeSampleHBAO(0, 6, aoData);
    occ += ComputeSampleHBAO(1, 6, aoData);
    occ += ComputeSampleHBAO(2, 6, aoData);
    occ += ComputeSampleHBAO(3, 6, aoData);
    occ += ComputeSampleHBAO(4, 6, aoData);
    occ += ComputeSampleHBAO(5, 6, aoData);
    occ += ComputeSampleHBAO(6, 6, aoData);
    occ += ComputeSampleHBAO(7, 6, aoData);

    occ += ComputeSampleHBAO(0, 7, aoData);
    occ += ComputeSampleHBAO(1, 7, aoData);
    occ += ComputeSampleHBAO(2, 7, aoData);
    occ += ComputeSampleHBAO(3, 7, aoData);
    occ += ComputeSampleHBAO(4, 7, aoData);
    occ += ComputeSampleHBAO(5, 7, aoData);
    occ += ComputeSampleHBAO(6, 7, aoData);
    occ += ComputeSampleHBAO(7, 7, aoData);
#endif

#else

    occ += ComputeSampleSSAO(0,  aoData);
    occ += ComputeSampleSSAO(1,  aoData);
    occ += ComputeSampleSSAO(2,  aoData);
    occ += ComputeSampleSSAO(3,  aoData);
    occ += ComputeSampleSSAO(4,  aoData);
    occ += ComputeSampleSSAO(5,  aoData);
    occ += ComputeSampleSSAO(6,  aoData);
    occ += ComputeSampleSSAO(7,  aoData);

#if AO_QUALITY >= 1       
    occ += ComputeSampleSSAO(8,  aoData);
    occ += ComputeSampleSSAO(9,  aoData);
    occ += ComputeSampleSSAO(10, aoData);
    occ += ComputeSampleSSAO(11, aoData);
    occ += ComputeSampleSSAO(12, aoData);
    occ += ComputeSampleSSAO(13, aoData);
    occ += ComputeSampleSSAO(14, aoData);
    occ += ComputeSampleSSAO(15, aoData);
#endif                       

#if AO_QUALITY >= 2           
    occ += ComputeSampleSSAO(16, aoData);
    occ += ComputeSampleSSAO(17, aoData);
    occ += ComputeSampleSSAO(18, aoData);
    occ += ComputeSampleSSAO(19, aoData);
    occ += ComputeSampleSSAO(20, aoData);
    occ += ComputeSampleSSAO(21, aoData);
    occ += ComputeSampleSSAO(22, aoData);
    occ += ComputeSampleSSAO(23, aoData);
    occ += ComputeSampleSSAO(24, aoData);
    occ += ComputeSampleSSAO(25, aoData);
    occ += ComputeSampleSSAO(26, aoData);
    occ += ComputeSampleSSAO(27, aoData);
    occ += ComputeSampleSSAO(28, aoData);
    occ += ComputeSampleSSAO(29, aoData);
    occ += ComputeSampleSSAO(30, aoData);
    occ += ComputeSampleSSAO(31, aoData);
#endif                       

#if AO_QUALITY >= 3          
    occ += ComputeSampleSSAO(32, aoData);
    occ += ComputeSampleSSAO(33, aoData);
    occ += ComputeSampleSSAO(34, aoData);
    occ += ComputeSampleSSAO(35, aoData);
    occ += ComputeSampleSSAO(36, aoData);
    occ += ComputeSampleSSAO(37, aoData);
    occ += ComputeSampleSSAO(38, aoData);
    occ += ComputeSampleSSAO(39, aoData);
    occ += ComputeSampleSSAO(40, aoData);
    occ += ComputeSampleSSAO(41, aoData);
    occ += ComputeSampleSSAO(42, aoData);
    occ += ComputeSampleSSAO(43, aoData);
    occ += ComputeSampleSSAO(44, aoData);
    occ += ComputeSampleSSAO(45, aoData);
    occ += ComputeSampleSSAO(46, aoData);
    occ += ComputeSampleSSAO(47, aoData);
    occ += ComputeSampleSSAO(48, aoData);
    occ += ComputeSampleSSAO(49, aoData);
    occ += ComputeSampleSSAO(50, aoData);
    occ += ComputeSampleSSAO(51, aoData);
    occ += ComputeSampleSSAO(52, aoData);
    occ += ComputeSampleSSAO(53, aoData);
    occ += ComputeSampleSSAO(54, aoData);
    occ += ComputeSampleSSAO(55, aoData);
    occ += ComputeSampleSSAO(56, aoData);
    occ += ComputeSampleSSAO(57, aoData);
    occ += ComputeSampleSSAO(58, aoData);
    occ += ComputeSampleSSAO(59, aoData);
    occ += ComputeSampleSSAO(60, aoData);
    occ += ComputeSampleSSAO(61, aoData);
    occ += ComputeSampleSSAO(62, aoData);
    occ += ComputeSampleSSAO(63, aoData);
#endif

#endif
    
    occ *= cb_PostEffect_SSAO.u_Contrast * INV_NUM_AO_SAMPLE;
    
#ifdef AO_POWER
    occ = vClamp(1-occ, 0.0, 1.0);
    occ = 1.0-vPow(occ, cb_PostEffect_SSAO.u_Power);
#endif
    
    // prise en compte de la transparence du plan
    // pour eviter les artefact sur la plan lui meme
    occ *= normal.w;
  }

#ifdef AO_WRITE_DELTAZ
  // on encode le delta Z car on utilise un buffer un float16 ce qui n'est pas suffisant 
  // niveau precision pour y mettre directement le z
  float z2 = GetZ(coord + vec2(cb_PostEffect_SSAO.u_PixelSize.x,0.0));
  z2 = -ConvertZBufferToZView(z2);

  FRAGCOLOR = vec4(occ, z2-pt.z, 0.0, 0.0);
#else
  FRAGCOLOR = vec4(occ, occ, occ, 0.0);
#endif
}


