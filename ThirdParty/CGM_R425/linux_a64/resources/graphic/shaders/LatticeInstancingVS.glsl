vec3 ComputeObjectPosition()
{
#ifdef PDSFXInstancing
	int instanceID = vGetInstanceID(); // gl_InstanceID is hidden behind this function by NRE

	// transfo
	vec4 gridcoord = vGetInstanceData(instanceID);
	mat4 orient = cb_cbLatticeInstancing.orientation;
	vec4 translation = orient * gridcoord;
	mat4 transfo = mat4(1); // identity
	transfo[3] = translation;

	// normal
	vec4 norm = vec4(vGetAttribNormal().xyz, 0.0);
	customNormal = (vGetWorldViewInvTranspMatrix() * transfo * norm).xyz; // the normal must be in view space
	normalize(customNormal);

	// color
	outcolor = cb_cbLatticeInstancing.color;//vGetAttribColor();

	// position
	vec4 pos = vec4(vGetAttribPosition().xyz, 1.0);
	return (transfo * pos).xyz;
#else

  return vec3(0.0);
#endif
}
