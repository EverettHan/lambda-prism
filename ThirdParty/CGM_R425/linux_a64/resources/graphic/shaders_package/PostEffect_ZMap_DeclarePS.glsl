// FORCE_Z
// It allows to not use ZMap and defined 0 or 1 value for all Z

#ifndef FORCE_Z
  #if defined(ZMAP_ARRAY) && !defined(ZMAP_ARRAY_ID)
    #define ZMAP_ARRAY_ID gl_Layer
  #endif

  #ifdef ZMAP_ARRAY_ID
    #define ZMAP_ARRAY_ID_FLOAT float(ZMAP_ARRAY_ID)
  #endif
#endif

//--------------------------------------------------------------------------------------------------
// GetZ
//
// retourne le Z tel qu'il est stocke dans le ZBuffer [0,1]
// cette valeur n'est pas stockee de maniere lineaire
//
// iCoord:        coordon�e entre 0 et 1 du pixel a l'ecran
// iPixelOffset:  offset en pixel
// iSampleId:     id du sample MSAA dont on veut retourner la valeur

float GetZ(const vec2 iCoord)
{
#ifdef FORCE_Z
  return FORCE_Z;
#elif defined(ZMAP_ARRAY_ID)
  return GetEffectTexture(s_ZMap, vec3(iCoord.xy, ZMAP_ARRAY_ID_FLOAT)).x;
#else
  // Fix for: GetEffectTexture(sampler2DMS, vec2) does not exist
  #if (defined(NORMAL_Z_MSAA) || defined (Z_MSAA)) && !defined(GLESPlatform) && defined(FragmentStage)
    return GetEffectTexture(s_ZMap, iCoord, gl_SampleID).x;
  #else
    return GetEffectTexture(s_ZMap, iCoord).x;
  #endif
#endif
}

float GetZ(const vec2 iCoord, const vec2 iPixelOffset)
{
#ifdef FORCE_Z
  return FORCE_Z;
#elif defined(ZMAP_ARRAY_ID)
  return GetEffectTexture(s_ZMap, vec3(iCoord.xy, ZMAP_ARRAY_ID_FLOAT), iPixelOffset).x;
#else
  return GetEffectTexture(s_ZMap, iCoord, iPixelOffset).x;
#endif
}

float GetZSample(const vec2 iCoord, int iSampleId)
{
#ifdef FORCE_Z
  return FORCE_Z;
#elif defined(ZMAP_ARRAY_ID)
  return GetEffectTexture(s_ZMap, vec3(iCoord.xy, ZMAP_ARRAY_ID_FLOAT), iSampleId).x;
#else
  return GetEffectTexture(s_ZMap, iCoord, iSampleId).x;
#endif
}

//--------------------------------------------------------------------------------------------------
// Conversion z view [abs(Near), abs(Far)] <-> ZBuffer [0,1]


// Convertit une vraie valeur de z vers une valeur telle qu'elle est stock�e dans le ZBuffer
// input:    valeur positive situ�e [near, far]
// outpout:  z tel qu'il est stock� dans le ZBuffer (valeur entre [0,1])

#if defined(LINEAR_DEPTH) && !defined(GLES2Platform)
#define ConvertZViewToZBuffer(iZ) (iZ)
#else
float ConvertZViewToZBuffer(const float iZ)
{
#ifdef LINEAR_DEPTH
  return iZ;
#else
  float z = iZ;

  // projection conic
#ifdef PROJECTION_CONIC
#ifdef LOG_DEPTH
    z = vLog(z*cb_PostEffectAuto.u_NearFarLogZ.x)*cb_PostEffectAuto.u_NearFarLogZ.z;
#else
    z  = -cb_PostEffectAuto.u_NearFar.w/z + cb_PostEffectAuto.u_NearFar.z;
#endif
#else
    z = (-z-cb_PostEffectAuto.u_NearFar.w)/cb_PostEffectAuto.u_NearFar.z;
#endif
  return z;
#endif
}
#endif


// Convertit un z tel qu'il est stock�e dans le ZBuffer vers une vraie valeur de depth positive entre near et far
// input:   z tel qu'il est stock� dans le ZBuffer (valeur entre [0,1])
// outpout: valeur positive situ�e [near, far]


#if defined(LINEAR_DEPTH) && !defined(GLES2Platform)
#define ConvertZBufferToZView(iZ) (iZ)
#else
float ConvertZBufferToZView(const float iZ)
{
#ifdef LINEAR_DEPTH
  return iZ;
#else
  float z = iZ;

  // projection conic
#ifdef PROJECTION_CONIC
#ifdef LOG_DEPTH
  z = vExp(z *cb_PostEffectAuto.u_NearFarLogZ.y)*cb_PostEffectAuto.u_NearFar.x;
#else
  z  = cb_PostEffectAuto.u_NearFar.w/(cb_PostEffectAuto.u_NearFar.z-z);
#endif
#else
  z = -vFma(cb_PostEffectAuto.u_NearFar.z, z, cb_PostEffectAuto.u_NearFar.w);
#endif
  return z;
#endif
}
#endif

//--------------------------------------------------------------------------------------------------
// ComputeWorldPosition
//
// iCoord: entre [0,1], c'est la coordonee dans la texture
// oPoint: coordonee du point dans le ViewSpace

bool ComputePointInViewSpace(const vec2 iCoord, out vec3 oPoint)
{
  // Amelioration pour prendre en compte le MSAA dans le calcul de la viewdir
  // A priori, ne semble pas apporter grand chose
  // vec2 texCoord = iCoord + cb_PostEffectAuto.u_PixelSize * gl_SamplePosition;

  oPoint.xy = vFma(iCoord, cb_PostEffectAuto.u_BufferToViewNearPlane.zw, cb_PostEffectAuto.u_BufferToViewNearPlane.xy);

  float z = GetZ(iCoord);
  oPoint.z = -ConvertZBufferToZView(z);

#ifdef PROJECTION_CONIC
  oPoint.xy = oPoint.xy*(oPoint.z*(-cb_PostEffectAuto.u_NearFarLogZ.x));
#endif

#ifdef LINEAR_DEPTH
  return (z<=cb_PostEffectAuto.u_NearFar.y && z>=cb_PostEffectAuto.u_NearFar.x);
#else
  return (z!=0.0 && z!=1.0);
#endif
}

bool ComputePointInViewSpace(const vec2 iCoord, out vec4 oPoint)
{
  oPoint.w = 1.0;
  return ComputePointInViewSpace(iCoord, oPoint.xyz);
}

//--------------------------------------------------------------------------------------------------
// Linearisation
//
// linearise le Z tel qu'il est stock dans le ZBuffer
// input:    z du zBuffer [0,1]
// outpout:  z lineaire   [0,1]

float LinearizeZ(const float iZ)
{
  float zView   = ConvertZBufferToZView(iZ);
  float linearZ = (zView-cb_PostEffectAuto.u_NearFar.x)/(cb_PostEffectAuto.u_NearFar.y-cb_PostEffectAuto.u_NearFar.x);

  return linearZ;
}

float GetLinearZ(const vec2 iCoord)
{
  return LinearizeZ(GetZ(iCoord));
}

float GetLinearZ(const vec2 iCoord, ivec2 iOffset)
{
  return LinearizeZ(GetZ(iCoord, vec2(float(iOffset.x), float(iOffset.y))));
}
