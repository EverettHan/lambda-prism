
void main(void)
{ 
  vec4 color = GetColor(vTexCoord);

  vec3 eyePos = vec3(0,0,0);
  eyePos = ConvertViewToEarthCoord(eyePos);
  eyePos = UpdateEarthPosition(eyePos);
    
  // World Direction
#ifdef RAYTRACED_EARTH
  // Utile surtout en mode MSAA et lorsque le sol est dessiné sous forme de sphere raytracee
  // car GetWorldCameraRay prend en compte la position du sample
  vec3 viewDir = GetWorldCameraRay(vTexCoord, cb_PostEffectAuto.u_BufferToViewNearPlane, cb_PostEffectAuto.u_NearFar.x, cb_PostEffectAuto.u_ViewInverseMatrix, cb_PostEffectAuto.u_PixelSize);
#else
  vec3 viewDir = vRay;
#endif
  viewDir  = vNormalize(viewDir);

  vec4 pos = vec4(0,0,0,1.0);

  // color.a >= 0.99 is a hack to avoid artefacts on ground
  // ground is the only transparent object with scatering
  // and we want to avoid it like other transparent objects
  if (ComputePointInViewSpace(vTexCoord, pos)==true 
#ifdef RAYTRACED_EARTH
      && color.a >= 0.99
#endif
      )
  {
    pos.xyz = ConvertViewToEarthCoord(pos.xyz);
  }
#ifdef RAYTRACED_EARTH
  else
  {
    float depth = IntersectSphere(eyePos, viewDir, vec3(0,0,0), g_AtmosphereRadiusGround);
    if (depth<=0) 
    {
      depth = 100000;
    }
    pos.xyz = depth*viewDir + eyePos;
  }
#endif
  pos.xyz = UpdateEarthPosition(pos.xyz);

  // Apply Scattering
  color.xyz = ApplyScattering(color.xyz, pos.xyz, viewDir, eyePos);
  
  FRAGCOLOR = vec4(color.xyz, 1.0);

}

