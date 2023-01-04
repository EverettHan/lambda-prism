
float offset_ray_origin_component(const float positionComponent, const float normalComponent)
{
  const float c_threshold = 1.0f / 32.0f; // threshold for position value to choose between two offset strategies
  const float c_normalScaleFactor = 1.0f / 65536.0f;
  const float c_integerNormalScale = 256.0f;

  if(abs(positionComponent) < c_threshold)
    return positionComponent + c_normalScaleFactor * normalComponent;

  int intNormalComponent = int(normalComponent * c_integerNormalScale);
  if(positionComponent < 0)
    intNormalComponent = -intNormalComponent;
  return intBitsToFloat(floatBitsToInt(positionComponent) + intNormalComponent); // with this trick, offset is proportional to positionComponent
}

// algo from ray tracing gems book
// TODO: explanation of the algo
vec3 offset_ray_origin(const vec3 position, const vec3 normal)
{
  return vec3(
    offset_ray_origin_component(position.x, normal.x),
    offset_ray_origin_component(position.y, normal.y),
    offset_ray_origin_component(position.z, normal.z)
  );
}


