// all shaders that require a payload (raygen, miss, hit groups) should use this file to define it

struct Payload_t
{
#ifdef DEBUG_BVH
  int hitIndex;
#else
  vec3 color;
  bool isHit;
#endif
};
