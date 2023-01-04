layout(location = 0) rayPayloadEXT Payload_t g_Payload;

float rand(float n){return fract(sin(n) * 43758.5453123);}

vec3 ComputeColor(uint iIndex)
{
	return vec3(rand(iIndex), rand(iIndex+1), rand(iIndex+2));
}

void ComputeRayDirection(ivec2 iScreenPos, out vec3 oOrigin, out vec3 oDirection)
{
	const vec2 pixelCenter = vec2(vGetLaunchID().xy) + vec2(0.5);
  const vec2 inUV = pixelCenter/vec2(vGetLaunchSize().xy);
  
  vec2 d = inUV * 2.0 - 1.0;
	
	vec4 origin    = _sbCbCamera.ViewInverseMatrix * vec4(0, 0, 0, 1);
	vec4 target    = _sbCbCamera.ProjInverseMatrix * vec4(d.x, d.y, 1, 1);
	vec4 direction = _sbCbCamera.ViewInverseMatrix * vec4(normalize(target.xyz), 0);

	oOrigin    = origin.xyz;
	oDirection = direction.xyz;
}


void main()
{
  ivec2 texIndex = ivec2(vGetLaunchID().xy);
    
  float tmin = _sbCbCamera.NearFarLogFactor.x;//0.0f;
  float tmax = _sbCbCamera.NearFarLogFactor.y; //100000.f;

  vec3 cameraPos, direction;
  ComputeRayDirection(texIndex, cameraPos, direction);
  
  g_Payload.hitIndex = -1;
  
  traceRayEXT(TopLevelAS, gl_RayFlagsOpaqueEXT, 0xff, 0, 0, 0, cameraPos, tmin, direction, tmax, 0);


  if(g_Payload.hitIndex != -1)
 
	imageStore(DebugMap, texIndex, vec4(ComputeColor(g_Payload.hitIndex), 1.0));
	  
  else
	  imageStore(DebugMap, texIndex, vec4(1.0, 0.0, 0.0, 1.0));
 
}


