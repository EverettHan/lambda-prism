
#define KERNEL_SIZE 7


//remove 0 in final version
float kernel[KERNEL_SIZE][KERNEL_SIZE] =
{
{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
{0.0, 0.014556070492362651, 0.028509874613867527, 0.034516650982046634, 0.028509874613867527, 0.014556070492362651, 0.0}, 
{0.0, 0.028509874613867527, 0.05584013562760078, 0.06760515429662843, 0.05584013562760078, 0.028509874613867527, 0.0}, 
{0.0, 0.034516650982046634, 0.06760515429662843, 0.08184895749450581, 0.06760515429662843, 0.034516650982046634, 0.0}, 
{0.0, 0.028509874613867527, 0.05584013562760078, 0.06760515429662843, 0.05584013562760078, 0.028509874613867527, 0.0}, 
{0.0, 0.014556070492362651, 0.028509874613867527, 0.034516650982046634, 0.028509874613867527, 0.014556070492362651, 0.0}, 
{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
};


float kernelSamplPos[KERNEL_SIZE] =
{
//-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0 //We should normally use this pos, but the result is too blurry...
-0.75, -0.5, -0.25, 0.0, 0.25, 0.5, 0.75 
};


const int kernelMedian = KERNEL_SIZE;

layout(location = 0) out vec4 fragColor;

vec4 fetchTexture(float i, float j)
{
  ivec2 dim = textureSize(s_SourceTex, 0);
  vec2 step = 1.0 / vec2(dim);

  vec2 iPos = vec2(i, j);
  vec2 samplingPos = vTexCoord + iPos * step;

  return vTexture(s_SourceTex, samplingPos);
}

void main(void)
{
  vec4 col = vec4(0.0);
 
  for(int i = 0 ; i < kernelMedian ; ++i)
  {
    for(int j = 0 ; j < kernelMedian ; ++j)
      col += fetchTexture(kernelSamplPos[i], kernelSamplPos[j]) * kernel[i][j];
  }

  fragColor = col;
}
