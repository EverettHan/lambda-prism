float GetBlurRadius(float distance)
{
	float aperture = cb_PostEffectAuto.u_ApertureFocalLength.x;
	float focalLength = cb_PostEffectAuto.u_ApertureFocalLength.y;
	
	float minBound, maxBound;

#ifdef DOF_FRONT
		minBound = -1.0;
    maxBound = 0.0;
#else
		minBound = 0.0;
		maxBound = 1.0;
#endif
	
	float radius = vClamp(aperture * focalLength * (distance - cb_PostEffectAuto.u_FocusDistance) / (distance * (cb_PostEffectAuto.u_FocusDistance - focalLength)), minBound, maxBound);
	
	return radius;
}
