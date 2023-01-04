#ifdef SphereClipping

void PerformSphereClippingDiscard()
{
  vec3 fragmentPos = vGetViewPosition();
  for(int i=0; i < kClipSpheresCount; i++)
  {
    vec3 spherePos = _sbCbClippingSpheres.clipSpheres[i].xyz;
  #ifdef UsePassThroughTransition
    spherePos = (_vPrivGetViewTransition() * vec4(spherePos, 1.0)).xyz;
  #endif
    float radiusSquared = _sbCbClippingSpheres.clipSpheres[i].w * _sbCbClippingSpheres.clipSpheres[i].w;
    vec3 sphereToFrag = fragmentPos - spherePos;
    float distanceSquared = vDot(sphereToFrag, sphereToFrag);
    if(distanceSquared < radiusSquared)
      discard;
  }
}

#endif
