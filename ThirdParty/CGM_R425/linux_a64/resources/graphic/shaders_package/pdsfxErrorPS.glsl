const vec3 red = vec3(1.0,0.0,0.0);
const vec3 white = vec3(1.0);

float hash(in vec2 uv) 
{
  return fract(sin(dot(uv.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec3 ComputeAlbedo()
{      
  vec2 uv = vNormalize(vGetFragCoord().xy);
  float tt = hash(uv);
  return mix(red, white, tt);  
}
