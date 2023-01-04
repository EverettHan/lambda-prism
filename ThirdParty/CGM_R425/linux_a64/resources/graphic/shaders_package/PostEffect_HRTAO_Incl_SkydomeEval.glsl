//-------------------------------------------------------------------------------------------------
// Environment - Sampling
//-------------------------------------------------------------------------------------------------
#define ONE_OVER_PI  0.318309886183790671538

vec2 getSphericalUv(vec3 v)
{
  float theta = acos(v.z);
  float phi = atan(v.x, v.y);

  return vec2(phi * ONE_OVER_PI * 0.5 + 0.5, 1.0 - theta * ONE_OVER_PI);
}

vec3 sphericalToCartesian(in float theta, in float phi)
{
  float cos_phi = cos(phi);
  float cos_theta = cos(theta);
  float sin_phi = sin(phi);
  float sin_theta = sin(theta);

  return vec3(sin_phi * cos_theta, sin_phi * sin_theta, cos_phi);
}

struct Environment_sample_data
{
  uint  alias;
  float q;
  float pdf;
  float aliasPdf;
};

Environment_sample_data getSampleData(sampler2D sample_buffer, ivec2 idx)
{
  vec4 data = texelFetch(sample_buffer, idx, 0);

  Environment_sample_data sample_data;
  sample_data.alias    = floatBitsToInt(data.x);
  sample_data.q        = data.y;
  sample_data.pdf      = data.z;
  sample_data.aliasPdf = data.w;
  return sample_data;
}

Environment_sample_data getSampleData(sampler2D sample_buffer, uint idx)
{
  uvec2 size = textureSize(sample_buffer, 0);
  uint  px   = idx % size.x;
  uint  py   = idx / size.x;
  return getSampleData(sample_buffer, ivec2(px, size.y - py - 1));  // Image is upside down
}

vec3 environment_evaluate_simple(vec3 normalized_dir)
{
  // assuming lat long
  const vec2 uv = getSphericalUv(normalized_dir);

  // get radiance
  return texture(hdrEnv, uv).rgb;
}

vec2 environment_sample_uv(sampler2D sample_buffer, vec3 sample_value, out vec3 to_light, out float pdf)
{
  vec3 xi = sample_value;

  uvec2 tsize  = textureSize(sample_buffer, 0);
  uint  width  = tsize.x;
  uint  height = tsize.y;

  const uint size = width * height;
  const uint idx  = min(uint(xi.x * float(size)), size - 1);

  Environment_sample_data sample_data = getSampleData(sample_buffer, idx);

  uint env_idx;
  if(xi.y < sample_data.q)
  {
    env_idx = idx;
    xi.y /= sample_data.q;
    pdf = sample_data.pdf;
  }
  else
  {
    env_idx = sample_data.alias;
    xi.y    = (xi.y - sample_data.q) / (1.0f - sample_data.q);
    pdf     = sample_data.aliasPdf;
  }

  uint       py = env_idx / width;
  const uint px = env_idx % width;

  // uniformly sample spherical area of pixel
  const float u       = float(px + xi.y) / float(width);
  const float phi     = u * (2.0f * M_PI) - M_PI;
  float       sin_phi = sin(phi);
  float       cos_phi = cos(phi);

  const float step_theta = M_PI / float(height);
  const float theta0     = float(py) * step_theta;
  const float cos_theta  = cos(theta0) * (1.0f - xi.z) + cos(theta0 + step_theta) * xi.z;
  const float theta      = acos(cos_theta);
  const float sin_theta  = sin(theta);
  to_light               = vec3(cos_phi * sin_theta, cos_theta, sin_phi * sin_theta);

  //to_light = -to_light.xzy;

  to_light = vec3(to_light.z, to_light.x, -to_light.y);

  // lookup filtered value
  const float v = theta * M_ONE_OVER_PI;
  return vec2(u, v);
}


float environment_get_pdf(sampler2D lat_long_tex, sampler2D sample_buffer, vec3 normalizedDir)
{
  vec2 uv = getSphericalUv(normalizedDir);

  uvec2 tsize  = textureSize(lat_long_tex, 0);
  uint  width  = tsize.x;
  uint  height = tsize.y;

  ivec2 idx = ivec2(uv.x * width, uv.y * height);

  Environment_sample_data sample_data = getSampleData(sample_buffer, idx);

  return sample_data.pdf;
}
