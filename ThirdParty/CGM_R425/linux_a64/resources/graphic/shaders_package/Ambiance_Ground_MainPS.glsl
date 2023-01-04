
void main() 
{
  if(cb_Ground.u_GroundColor.a == 0.f)
    discard;

  // normal
  vec3 worldNormal = ComputeNormal();
    
  // couleur final
  vec4 resCol      = ComputeLighting(worldNormal); 
  
  float distanceFromCenter = vLength(vLocalPosition.xy);
  float fading = ComputeFading(distanceFromCenter, cb_Ground.u_RadiusRatio.x, cb_Ground.u_RadiusRatio.y);
  
  resCol.w *= fading;
 
#ifdef OutputIBLReflMap
  FRAGREFLECT.a *= fading;
#endif

#ifdef OutputNormalMap
  vec4 resNormal = vec4(1,1,1, 0); 
  resNormal = (vGetViewMatrix() * vec4(worldNormal,0)) * 0.5 + vec4(0.5);
  resNormal.w = 0.99 * ComputeFading(distanceFromCenter, cb_Ground.u_RadiusRatio.z, cb_Ground.u_RadiusRatio.w); // on ne met pas 1 pour pour pouvoir se servir de cette map pour differencier la scene 3D du plan et du fond
  FRAGNORMAL = resNormal;
#endif

#ifdef OutputF0RoughMap
#ifdef GROUND_MIRRORING
  FRAGMATPROP = vec4(cb_Ground.u_MirrorSpecularReflectance, cb_Ground.u_MirrorRoughness);
#else
  FRAGMATPROP = vec4(0.0);
#endif
#endif

#ifdef LogDepth
  gl_FragDepth  = vLog(-vViewPosition.z / vGetNearFarLogFactor().x) * vGetNearFarLogFactor().z;
#endif

#ifdef OutputWorldPos
  fragWorldPos.xyz = floatBitsToUint(vWorldPosition.xyz);
  fragWorldPos.w = compress_unit_vec(worldNormal);
  #ifndef UseLegacyRayOriginOffset
  {
    vec4 localPosVec4 = vec4(vWorldPosition.xyz, 1.0) * cb_Ground_Matrix.u_GroundWorldInverseTransposeMatrix; // <=> worldInverse * worldPos
    vec3 localPos = localPosVec4.xyz / localPosVec4.w;
    vec3 localNormal = normalize((vec4(worldNormal, 0.0) * cb_Ground_Matrix.u_GroundWorldInverseTransposeMatrix).xyz); //  <=> worldInverse * worldNormal; actually,
    // we would want worldInverseTransposeInverse * worldNormal but it looks like worldNormal is, in current code, by mistake, computed as world * localNormal instead
    // of worldInverseTranspose * localNormal
    float localOffset = distance(localPos, offset_ray_origin(localPos, localNormal));
    float worldScaleAlongNormal = 1.0;
    float worldScaleInvAlongNormal = length((vec4(worldNormal, 0.0) * cb_Ground_Matrix.u_GroundWorldInverseTransposeMatrix).xyz);
    if(worldScaleInvAlongNormal != 0.0)
      worldScaleAlongNormal = 1.0 / worldScaleInvAlongNormal;
    fragGBufferAdditionalData.x = worldScaleAlongNormal * localOffset;
  }
  #endif // ifndef UseLegacyRayOriginOffset

  #ifdef OutputWorldPosOnly
    return;
  #endif
#endif

#ifdef OutputMotionVectorMap
	fragMotionVector = vGetMotionVector();
#endif

  //Result
	FRAGCOLOR = resCol; 
}
