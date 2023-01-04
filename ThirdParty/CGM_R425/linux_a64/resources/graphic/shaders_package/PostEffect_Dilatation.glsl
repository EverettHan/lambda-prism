
#ifdef POISSON
#define KERNEL_SIZE 12
const vec2 g_Kernel[KERNEL_SIZE] = vec2[]
(
  vec2(-0.326212f,  -0.405805f),
  vec2(-0.840144f,  -0.07358f ),
  vec2(-0.695914f,  0.457137f ),
  vec2(-0.203345f,  0.620716f ),
  vec2(0.96234f,    -0.194983f),
  vec2(0.473434f,   -0.480026f),
  vec2(0.519456f,   0.767022f ),
  vec2(0.185461f,   -0.893124f),
  vec2(0.507431f,   0.064425f ),
  vec2(0.89642f,    0.412458f ),
  vec2(-0.32194f,   -0.932615f),
  vec2(0.791559f,   -0.597705f)
);
#else
#define KERNEL_SIZE 4
const ivec2 g_Kernel[KERNEL_SIZE] = ivec2[]
(
  ivec2( 0,-1),
  ivec2( 0, 1),
  ivec2(-1, 0),
  ivec2( 1, 0)
  );
#endif


void main(void)
{ 
  vec4 colInit = GetColor(vTexCoord);
  vec4 deltaCol = vec4(0);

  for (int i=0; i<KERNEL_SIZE; i++)
  {
    vec4 col = (1.0+cb_PostEffect.u_Delta) * GetColor(vTexCoord, g_Kernel[i]*cb_PostEffect.u_Size) - colInit;
#ifdef EROSION
    deltaCol = vMax(col, deltaCol);
#else
    deltaCol = vMin(col, deltaCol);
#endif
  }

  vec4 resCol = colInit + deltaCol;
  resCol.w = 1.0;

  FRAGCOLOR = resCol;
}

