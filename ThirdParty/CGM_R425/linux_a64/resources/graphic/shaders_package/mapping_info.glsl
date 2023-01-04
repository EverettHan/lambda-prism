struct mapping_info_t
{
  vec3 n;
  vec3 p;
  vec3 x;
  vec3 y;
  vec3 z;
};

struct mapping_result_t
{
  vec2 uv;
  vec2 uv_mod; // uv after global (VisMaterialApplication) UV transform
  vec3 t;
  vec3 b;
  int semantic;
};
