void main(void)
{
  vec2 texCoord = vGetPosition().xy*0.5+0.5;

#ifdef BACKGROUND_TEXCOORD
	vTexCoord = texCoord;
#endif

#ifdef BACKGROUND_RAY
  vec4 ray;
  ray.w = 0.0;
  ray.z = -vGetNearFarLogFactor().x;
  ray.xy = vFma(texCoord.xy, vGetBufferToViewNearPlane().zw, vGetBufferToViewNearPlane().xy);
  ray = vGetViewInverseMatrix() * ray;
  vRay = ray.xyz;
#endif

#if defined(BACKGROUND_GEOMETRY) && !defined(BACKGROUND_GEOMETRY_AUTO)
  vDomePosition = vec3(dvec3(cb_Background.u_PositionLow) + dvec3(cb_Background.u_PositionHigh) - dvec3(vGetWorldEyePos()) - dvec3(vGetWorldEyePosLow()));
#endif

  gl_Position = vec4(vGetPosition(), 1.0);
}
