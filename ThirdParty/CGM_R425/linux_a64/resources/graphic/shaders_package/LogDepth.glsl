
#ifdef LogDepth
float ComputeLogDepth(float projPos)
{
  float NearPlane = vGetNearFarLogFactor().x;
  //float LogZFactor = 1 / vLog(FarPlane / NearPlane);
  float LogZFactor = vGetNearFarLogFactor().z;
  return vLog(projPos / NearPlane) * LogZFactor;
}
#endif

