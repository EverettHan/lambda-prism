
#ifndef GeometryStage

#ifdef RayHitStage
  #define V_GET_PM_TEXTURE(iTexture) (GlobalTextures2D[nonuniformEXT(iTexture)])
#else
  #define V_GET_PM_TEXTURE(iTexture) (iTexture)
#endif

#if defined(heightMapEnabled) && defined(FragmentStage)
  vec2 vGetUvOffset();
#endif
  
vec2 _GetParameterUvs(mat3 iTransform)
{
  vec2 uvs = vec2(0.0);
  
#if defined(heightMapEnabled) && defined(FragmentStage)
  uvs = vGetUvOffset();
#endif

#if defined GPUMappingOperator || defined DecalLighting
  uvs = vec2(iTransform * vec3(uvs + vGetUvs().xy, 1.0));
#else
#if defined UsePMGeometryUVTransform
  uvs = vec2(iTransform * vec3(uvs + vGetUvs().xy, 1.0));
#else
  uvs += vGetUvs().xy;
#endif //UsePMGeometryUVTransform
#endif //GPUMappingOperator || defined DecalLighting

  return uvs;
}
#endif

#if defined(VertexStage) || defined(RayHitStage)
  #undef vGetUvs
#endif
