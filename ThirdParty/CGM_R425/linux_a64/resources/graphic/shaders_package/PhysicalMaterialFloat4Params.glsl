#ifndef GeometryStage

/************************************************FLOAT4 PARAM **********************************************************/
vec4 _diffuse;
#ifndef diffuseAsTexture
vec4 pmGetDiffuse()
{
  return vec4(PMat.diffuse,0.0);
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture

vec4 pmGetDiffuse()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.diffuseUvTransform));

#ifndef DecalLighting
  return vTexture(V_GET_PM_TEXTURE(diffuse), uvs);
#else
  //Force mip 0 for decals since the derivatives are all wrong and often produce blurry samples
  return vTextureLod(V_GET_PM_TEXTURE(diffuse), uvs, 0.0); 
#endif
}

#endif // diffuseAsTexture
/********************************************/
vec4 _emissive;
#ifndef emissiveAsTexture
vec4 pmGetEmissive()
{
  return vec4(PMat.emissive, 0.0);
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
vec4 pmGetEmissive()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.emissiveUvTransform));

  return vTexture(V_GET_PM_TEXTURE(emissive), uvs);
}
#endif // emissiveAsTexture

/********************************************/
vec4 _fresnelCoefficient;
#ifndef fresnelCoefficientAsTexture
vec4 pmGetFresnelCoefficient()
{
    return vec4(PMat.fresnelCoefficient,0.);
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
vec4 pmGetFresnelCoefficient()
{
    vec2 uvs = _GetParameterUvs(mat3(PMat.fresnelCoefficientUvTransform));
    return vTexture(V_GET_PM_TEXTURE(fresnelCoefficient), uvs);
}
#endif // fresnelCoefficientAsTexture

/********************************************/
vec4 _edgeColor;
#ifndef edgeColor
vec4 pmGetEdgeColor()
{
    return vec4(PMat.edgeColor,0.);
}
#else
#ifndef PMUniformAsTexture
#define PMUniformAsTexture
#endif // PMUniformAsTexture
vec4 pmGetEdgeColor()
{
    vec2 uvs = _GetParameterUvs(mat3(PMat.edgeColorUvTransform));
    return vTexture(V_GET_PM_TEXTURE(edgeColor), uvs);
}
#endif // edgeColo


/********************************************/

vec4 _normalMap;
#ifndef normalMapEnabled
vec4 pmGetNormalMap()
{
  return vec4(0.0);
}
#else
vec4 pmGetNormalMap()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.normalMapUvTransform));

  vec4 normal;

#ifdef CompressedNormalMap
  normal   = vec4( vFma(vTexture(V_GET_PM_TEXTURE(normalMap), uvs).rg, vec2(2.0), vec2(-1.0)), 0.0, 0.0 );  
  normal.z = vSqrt(vAbs( 1.0 - vDot( normal.xy,normal.xy ) ));  
  normal   = vFma(normal, vec4(0.5), vec4(0.5));
#else //Not a compressed Normap map
  normal = vTexture(V_GET_PM_TEXTURE(normalMap), uvs);
#endif
#ifdef SubSurface
  float mipLevel = textureQueryLevels(normalMap);
  float mipmapLevel = textureQueryLod(normalMap, uvs).x;
  mipmapLevel = vMin(mipmapLevel + 5, mipLevel-1);
  vec4 aux;
  #ifdef CompressedNormalMap
  aux   = vec4( vFma(vTextureLod(V_GET_PM_TEXTURE(normalMap), uvs, mipmapLevel).rg, vec2(2.0), vec2(-1.0)), 0.0, 0.0 );  
  aux.z = vSqrt(vAbs( 1.0 - vDot( aux.xy,aux.xy ) ));  
  aux   = vFma(normal, vec4(0.5), vec4(0.5));
  #else //Not a compressed Normap map
  aux = vTextureLod(V_GET_PM_TEXTURE(normalMap), uvs, mipmapLevel);
  #endif
  normal = vMix(normal,aux,0.5);
#endif
  return normal;
}
#endif // normalMapEnabled


/********************************************/
vec4 _heightMap;
#ifndef heightMapEnabled
vec4 pmGetHeightMap()
{
  return vec4(0.0);
}
#else
vec4 pmGetHeightMap()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.heightMapUvTransform));
  vec4 height =  vTexture(V_GET_PM_TEXTURE(heightMap), uvs);
#ifdef SubSurface
  float mipLevel = textureQueryLevels(heightMap);
  float mipmapLevel = textureQueryLod(heightMap, uvs).x;
  mipmapLevel = vMin(mipmapLevel + 5, mipLevel-1);
  vec4 aux;
  aux = vTextureLod(V_GET_PM_TEXTURE(heightMap), uvs, mipmapLevel);
  height = vMix(height,aux,0.5);
#endif // SSS
  return height;
}
#endif // heightMapEnabled


/********************************************/
vec4 _bumpMap;
#ifndef bumpMapEnabled
vec4 pmGetBumpMap()
{
  return vec4(0.0);
}
#else
vec4 pmGetBumpMap()
{
  vec2 uvs = _GetParameterUvs(mat3(PMat.bumpMapUvTransform));
  return vTexture(V_GET_PM_TEXTURE(bumpMap), uvs);
}
#endif // bumpMapEnabled

/***********************************************************************************************************************/

#endif
