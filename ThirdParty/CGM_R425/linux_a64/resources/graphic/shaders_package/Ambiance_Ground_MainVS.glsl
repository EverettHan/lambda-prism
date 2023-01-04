void main()
{
  vec4 localPosition = vec4(vGetPosition(), 1.0);
  localPosition.xy += cb_Ground.u_DeltaPosition.xy;
  vLocalPosition = localPosition;

  vec4 worldNormal = vec4(0, 0, 1.0, 0);

  vWorldPosition = cb_Ground_Matrix.u_GroundWorldMatrix * localPosition;

#ifdef UsePassThroughTransition
  mat4 groundMat = _vPrivGetViewTransition() * cb_Ground_Matrix.u_GroundMatrix;
  vec4 viewPosition = groundMat * localPosition;
  vWorldNormal = vNormalize(vGetViewInverseMatrix() * groundMat * worldNormal);
#else
  vec4 viewPosition = cb_Ground_Matrix.u_GroundMatrix * localPosition;
  vWorldNormal = vNormalize(vGetViewInverseMatrix() * cb_Ground_Matrix.u_GroundMatrix * worldNormal);
#endif

  vViewPosition     = viewPosition;

  // Shadow
#ifdef GROUND_SHADOW
  ComputeShadows(viewPosition);
#endif

#ifdef OutputMotionVectorMap
  vSetClipPos(vGetProjMatrix() * vec4(worldTS.Pos, 1.0));
  vSetPrevClipPos(vGetProjMatrix() * (vGetViewDeltaMatrix() * vec4(worldTS.Pos, 1.0)));
#endif

  gl_Position  = vGetProjMatrix() * viewPosition;
}
