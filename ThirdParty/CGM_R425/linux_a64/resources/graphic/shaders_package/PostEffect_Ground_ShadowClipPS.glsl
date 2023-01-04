
void main(void)
{ 
  //We linearize the Z if we have a perspective projection (means w != 1)
  float depth = gl_FragCoord.z;
  if (vAbs(gl_FragCoord.w - 1.0) > 0.001)
  {
    depth = ZClipRemmapedInLinear(_sbCbCamera.NearFarLogFactor.x, _sbCbCamera.NearFarLogFactor.y, depth);
  }
  gl_FragDepth = depth;

  FRAGCOLOR = vec4(0.0);
}

