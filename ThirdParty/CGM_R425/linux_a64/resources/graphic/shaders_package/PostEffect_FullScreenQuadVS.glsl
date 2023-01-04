void main(void)
{
  vec4 vPosition = vec4(vGetPosition(), 1);

#ifdef POSTEFFECT_INVERTY
  vTexCoord = vGetTexCoord();
#else
  vTexCoord = vec2(vGetTexCoord().x, 1.0-vGetTexCoord().y);
#endif
  
#if defined(POSTEFFECT_RAY) || defined(POSTEFFECT_VIEWRAY)
  vec4 ray;
  ray.w = 0;
  ray.z = -cb_PostEffectAuto.u_NearFar.x;
  ray.xy = vFma(vTexCoord.xy, cb_PostEffectAuto.u_BufferToViewNearPlane.zw, cb_PostEffectAuto.u_BufferToViewNearPlane.xy);
#ifndef POSTEFFECT_VIEWRAY
  ray =  cb_PostEffectAuto.u_ViewInverseMatrix * ray;
#endif
  vRay = ray.xyz;
#endif

  gl_Position = vPosition;
}
