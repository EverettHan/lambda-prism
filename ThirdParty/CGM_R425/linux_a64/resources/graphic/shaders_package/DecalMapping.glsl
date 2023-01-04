#ifdef DecalLighting

#define DecalMappingExplicit 0
#define DecalMappingPlanar 1
#define DecalMappingFiniteCylindrical 2
#define DecalMappingInfiniteCylindrical 3
#define DecalMappingSpherical 4
#define DecalMappingCubical 5
#define DecalMappingInfiniteCylindricalAnglePreserving 6

  //_decalNormal is used in ShaderBuilderUberPS
  vec3 _decalNormal = vec3(0.0);
  vec2 pmDecalTexCoords = vec2(0.0);
  vec2 pmDecalTexCoordsOffset = vec2(0.0);
  vec3 pmDecalTangent = vec3(0.0);
  vec3 pmDecalBinormal = vec3(0.0);

  vec3 vComputeDecalNormal(vec3 iU, vec3 iV, vec3 iDecalNormal, vec3 iSurfaceNormal)
  {
    vec3 worldUPrime = vNormalize(iU - dot(iU, iSurfaceNormal) * iSurfaceNormal);
    vec3 worldVPrime = vNormalize(iV - dot(iV, iSurfaceNormal) * iSurfaceNormal);

    return vNormalize(
        iDecalNormal.x*worldUPrime
      + iDecalNormal.y*worldVPrime
      + iDecalNormal.z*iSurfaceNormal);
  }

  vec2 vGetUvs()
  {
  #if DecalMappingOperator == DecalMappingExplicit
    #ifdef PhysicalMaterial
      vec2 tc = vec2(mat3(PMat.uvTransformation) * vec3(pmDecalTexCoords, 1.0));
    #else
      vec2 tc = pmDecalTexCoords;
    #endif
  #else
    vec2 tc = pmDecalTexCoords;
  #endif

  #if defined(TextureMatrix)
    tc = (vGetTextureMatrix() * vec4(tc, 0.0, 1.0)).xy;
  #endif

  #if DecalMappingOperator != DecalMappingExplicit
    tc += 0.5;
  #endif

    return tc;
  }

#if defined(heightMapEnabled) && defined(FragmentStage)
  vec2 vGetUvOffset()
  {
    return pmDecalTexCoordsOffset;
  }
#endif

  vec3 vGetTangent()
  {
    return pmDecalTangent;
  }

  vec3 vGetBinormal()
  {
    return pmDecalBinormal;
  }

#if (DecalMappingOperator == DecalMappingExplicit)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
  }
#elif (DecalMappingOperator == DecalMappingPlanar)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
    //const float fact = iPosition.z >= 0.0 ? 1.0 : -1.0;
    pmDecalTexCoords = iPosition.xy;
    pmDecalTangent = iX;
    pmDecalBinormal = iY;
  }
#elif (DecalMappingOperator == DecalMappingSpherical)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
    //const vec3 pos = iPosition;
    const float radius3d = max(0.000001, length(iPosition.xyz));
    const float z_by_radius3d = iPosition.z / radius3d;
    const float theta = atan(iPosition.y, iPosition.x);
    const float phi = asin(z_by_radius3d);
    pmDecalTexCoords = vec2(theta, phi) * vec2(radius3d);
    const float cos_theta = cos(theta);
    const float sin_theta = sin(theta);
    const float cos_phi = cos(phi);
    const float sin_phi = z_by_radius3d;
    pmDecalTangent = -sin_theta*iX + cos_theta*iY;
    pmDecalBinormal = -cos_theta*sin_phi*iX - sin_theta*sin_phi*iY + cos_phi*iZ;
  }
#elif (DecalMappingOperator == DecalMappingCubical)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
    vec3 absn = abs(iNormal);
    float maxn = max(absn.x, max(absn.y, absn.z));

    vec3 n = iNormal;

    if(dot(iPosition, iNormal) < 0.0)
      n = -iNormal;
  
    vec3 s;
    s.x = n.x >= 0.0 ?  1.0 : -1.0;
    s.y = n.y >= 0.0 ? -1.0 :  1.0;
    s.z = n.z >= 0.0 ?  1.0 : -1.0;

    if(maxn == absn.x)
    {
      pmDecalTexCoords = vec2(s.x * iPosition.y, iPosition.z);
      pmDecalTangent = s.x * iY;
      pmDecalBinormal = iZ;
    }
    else if(maxn == absn.y)
    {
      pmDecalTexCoords = vec2(s.y * iPosition.x, iPosition.z);
      pmDecalTangent = s.y * iX;
      pmDecalBinormal = iZ;
    }
    else
    {
      pmDecalTexCoords = vec2(s.z * iPosition.x, iPosition.y);
      pmDecalTangent = s.z * iX;
      pmDecalBinormal = iY;
    }
  }
#elif (DecalMappingOperator == DecalMappingFiniteCylindrical)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
    const vec3 pos = iPosition;
    const vec3 absolute_normal = abs(iNormal);
    const float maxima_normal = max(absolute_normal.x, max(absolute_normal.y, absolute_normal.z));

    if (maxima_normal == absolute_normal.z)
    {
      const float signPosZ = vSignf(iPosition.z);
      pmDecalTexCoords = vec2(signPosZ*pos.x, pos.y);
      pmDecalTangent = iX;
      pmDecalBinormal = iY;
    }
    else
    {
      const float radius2d = length(iPosition.xy);
      //const float radius3d = length(iPosition.xyz);
      //const float z_by_radius3d = iPosition.z / radius3d;
      const float theta = atan(iPosition.y, iPosition.x);
      //const float phi = asin(z_by_radius3d);
      pmDecalTexCoords = vec2(theta, iPosition.z) * vec2(radius2d, 1.0);
      const float cos_theta = cos(theta);
      const float sin_theta = sin(theta);
      pmDecalTangent = -sin_theta*iX + cos_theta*iY;
      pmDecalBinormal = iZ;
    }
  }
#elif (DecalMappingOperator == DecalMappingInfiniteCylindrical)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
    const float radius2d = length(iPosition.xy);
    //const float radius3d = max(0.000001, length(iPosition.xyz));
    //const float z_by_radius3d = iPosition.z / radius3d;
    const float theta = atan(iPosition.y, iPosition.x);
    //const float phi = asin(z_by_radius3d);
    pmDecalTexCoords = vec2(theta, iPosition.z) * vec2(radius2d, 1.0);
    const float cos_theta = cos(theta);
    const float sin_theta = sin(theta);
    pmDecalTangent = -sin_theta*iX + cos_theta*iY;
    pmDecalBinormal = iZ;
  }
#elif (DecalMappingOperator == DecalMappingInfiniteCylindricalAnglePreserving)
  void ComputeMapping(in vec3 iPosition, in vec3 iNormal, in vec3 iX, in vec3 iY, in vec3 iZ)
  {
    //const float radius3d = max(0.000001, length(iPosition.xyz));
    //const float z_by_radius3d = iPosition.z / radius3d;
    const float theta = atan(iPosition.y, iPosition.x);
    //const float phi = asin(z_by_radius3d);
    pmDecalTexCoords = vec2(theta * INV_PI, iPosition.z);
    const float cos_theta = cos(theta);
    const float sin_theta = sin(theta);
    pmDecalTangent = -sin_theta*iX + cos_theta*iY;
    pmDecalBinormal = iZ;
  }
#endif
  void TransformUv()
  {
  }
#endif
