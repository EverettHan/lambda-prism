void ProcessClipSpacePosition(inout vec4 position)
{
  vec4 pos = vec4(vGetPosition(), 1.0);
#ifdef NoViewProj
  pos = cb_cbPDSFXWorldMatrix.WorldMatrix * pos;
#else
  pos = vGetProjMatrix() * vGetWorldViewMatrix() * pos;
#endif

  position = pos;
}

void ComputeVaryingValues()
{
  vTexCoord = vGetTexCoord0();
}

vec3 ComputeClippingViewPosition()
{
  // Set the clipping point as the anchor point
#ifdef ZTestAnnotation
  return (vGetViewMatrix() * vec4(vGetAnchorPosition(), 1.0)).xyz;
#else
  return (vGetWorldViewMatrix() * vec4(cb_cbText_Default.u_AnchorPoint, 1.0)).xyz;
#endif

}

#ifdef ZTestAnnotation
bool ProcessAnchorPosition()
{
#if defined(ZMapAccess) || defined(ManualZTest) 
  vec4 anchorPoint = vec4(vGetAnchorPosition(), 1.0);
  anchorPoint = vGetViewProjMatrix() * anchorPoint;
  return vGetClipSpaceDepthTest(anchorPoint);
#else
  return false;
#endif
}
#endif
