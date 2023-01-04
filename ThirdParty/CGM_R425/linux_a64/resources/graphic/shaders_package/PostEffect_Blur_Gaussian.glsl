// Pour info:
// une fonction gaussienne se presente sous la forme f(x) = exp(-x*x)
// L'integrale de de moins l'infini a plus l'infini  de:
//  * f(x)=exp(-x*x) est sqrt(pi)
//  * f(x)=a*exp(-sqr(x-b)/(2*sqr(c)) est a*c*sqrt(2*pi)
// 
// valeur de la fonction gaussienne
// pour sigma=0.8
// f(x) =(1/sqrt(2*pi*sqr(sigma))) * exp(-sqr(x)/(2*sqr(sigma))) 

// Code optimisé pour les kernel les plus courants

#if defined(GAUSSIAN_LEVEL2)
float g_GaussianKernel[3]=float[](0.02275,	0.9545,	0.02275);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL3)
float g_GaussianKernel[5]=float[](0.00135,	0.157305,	0.68269,	0.157305,	0.00135);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL4)
float g_GaussianKernel[7]=float[](0.000428,	0.022321,	0.229743,	0.495016,	0.229743,	0.022321,	0.000428);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL5)
float g_GaussianKernel[9]=float[](0.000229,	0.005977,	0.060598,	0.241732,	0.382928,	0.241732,	0.060598,	0.005977,	0.000229);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL6)
float g_GaussianKernel[11]=float[](0.000154,	0.002396,	0.020195,	0.092321,	0.229511,	0.310847,	0.229511,	0.092321,	0.020195,	0.002396,	0.000154);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL7)
float g_GaussianKernel[13]=float[](0.000116,	0.001227,	0.008466,	0.037976,	0.110867,	0.210789,	0.261121,	0.210789,	0.110867,	0.037976,	0.008466,	0.001227,	0.000116);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL8)
float g_GaussianKernel[15]=float[](0.000093,	0.000735,	0.004228,	0.017686,	0.053815,	0.119121,	0.191869,	0.224907,	0.191869,	0.119121,	0.053815,	0.017686,	0.004228,	0.000735,	0.000093);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL9)
float g_GaussianKernel[17]=float[](0.000078,	0.000489,	0.002403,	0.009245,	0.027835,	0.065592,	0.12098,	0.17467,	0.197417,	0.17467,	0.12098,	0.065592,	0.027835,	0.009245,	0.002403,	0.000489,	0.000078);
#define GAUSSIAN_FAST_MODE 1

#elif defined(GAUSSIAN_LEVEL10)
float g_GaussianKernel[19]=float[](0.000067,	0.00035,	0.001504,	0.005321,	0.015497,	0.037158,	0.073355,	0.119235,	0.159582,	0.175863,	0.159582,	0.119235,	0.073355,	0.037158,	0.015497,	0.005321,	0.001504,	0.00035,	0.000067);
#define GAUSSIAN_FAST_MODE 1

#endif

void main(void)
{   
  vec2  dir         = cb_Blur.u_Direction * cb_Blur.u_BlurSize * 0.5f/float(GAUSSIAN_LEVEL);
#ifdef INVERT_XY
  dir = vec2(dir.y, dir.x);
#endif
  dir *= cb_PostEffectAuto.u_ViewpointFixRatio;
  dir  = ConvertViewpointToViewportRatio(dir);

  float sigma       = GAUSSIAN_LEVEL/5.0;
  
  vec4  color       = vec4(0.0f);
  float totalWeight = 0;
  
  for(int i=-GAUSSIAN_LEVEL; i<=GAUSSIAN_LEVEL; i++)
  {
    vec2 texCoord   =  dir * i + vTexCoord;
    vec4 sampleCol  =  GetColor(texCoord);

#ifdef GAUSSIAN_FAST_MODE
    color += sampleCol * g_GaussianKernel[i+GAUSSIAN_LEVEL];
#else
    float weight = vExp(-(i*i)/(2*sigma*sigma));
    color += sampleCol * weight;
    totalWeight += weight;
#endif
  }
  
#ifdef GAUSSIAN_FAST_MODE
  FRAGCOLOR = color;
#else
  FRAGCOLOR = color/totalWeight;
#endif
}

