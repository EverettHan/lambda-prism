#ifndef BLUR_LEVEL
#define BLUR_LEVEL 10
#endif


float ComputeWeight(const int iPos)
{
  float weight = 1.;

#if defined(BLUR_LINEAR)
  weight = float(BLUR_LEVEL-iPos);
#elif defined(BLUR_QUADRATIC)
  weight = float(BLUR_LEVEL-iPos);
  weight = weight*weight;
#endif
  return weight;
}

void main(void)
{
  vec2  dir;

#ifdef SHADOW_BOX
  vec2 shadowRatio = _sbcbShadowBlur.ShadowBlur;
    
  if(shadowRatio.x < shadowRatio.y)
    dir = cb_Blur.u_Direction * cb_Blur.u_BlurSize /float(BLUR_LEVEL) * vec2(1, shadowRatio.x / shadowRatio.y);
  else
    dir = cb_Blur.u_Direction * cb_Blur.u_BlurSize /float(BLUR_LEVEL) * vec2(shadowRatio.y / shadowRatio.x, 1);
#else //Shadow is a spehere
    dir   = cb_Blur.u_Direction * cb_Blur.u_BlurSize /float(BLUR_LEVEL);
#endif //SHADOW_BOX
    
#ifdef INVERT_XY
  dir = vec2(dir.y, dir.x);
#endif

  //dir = ConvertViewpointToViewportRatio(dir);
    
  vec4  color = ComputeWeight(0)*GetColor(vTexCoord);

  for(int i=1; i<=BLUR_LEVEL; i++)
  {
    float weight = ComputeWeight(i);
    vec2 delta = float(i)*dir;

    color += weight*GetColor(vTexCoord + delta);
    color += weight*GetColor(vTexCoord - delta);
  }

  float totalWeight = 1.;
#if defined(BLUR_LINEAR)
  totalWeight = float(BLUR_LEVEL*BLUR_LEVEL);
#elif defined(BLUR_QUADRATIC)
  totalWeight = float(BLUR_LEVEL*(2*BLUR_LEVEL*BLUR_LEVEL+1))/float(3);
#else
  totalWeight = float(2*BLUR_LEVEL+1);
#endif

  FRAGCOLOR = color/totalWeight;
}

