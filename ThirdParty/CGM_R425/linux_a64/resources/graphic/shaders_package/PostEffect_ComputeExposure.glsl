#ifndef EXPOSURE_MODE
#define EXPOSURE_MODE 0
#endif

//#if EXPOSURE_MODE==1  // Histogram
//layout(r32ui) uniform restrict coherent readonly  uimage1D  i_HistogramMap;
//#else                 // Basic
//layout(r32f) uniform restrict coherent readonly   image2D   i_LuminanceMap;
//#endif
//
//layout(r32f)  uniform restrict coherent writeonly image1D   i_ExposureMap;
//
//#ifdef EYE_ADAPTATION
//layout(r32f) uniform restrict coherent image1D i_LastLuminanceMap;
//#endif

layout (local_size_x = 1, local_size_y = 1) in;

void main() 
{
  float ev  = 0;

#if EXPOSURE_MODE==1  
  //--------------------
  // Histogram
  
  int   histoSize   = vImageSize(i_HistogramMap);
  float deltaEV     = (cb_Luminance.u_HistoMax - cb_Luminance.u_HistoMin) / float(histoSize);

  float  numCurrent  = 0.0;
  float  numTotal    = cb_Luminance.u_TotalLuminance;
  float  numMin      = numTotal * cb_Luminance.u_Low;
  float  numMax      = numTotal * cb_Luminance.u_High;

  float numSelected = 0;

  for (int i = 0; i < histoSize; i++)
  {
    float num = float(vImageLoad (i_HistogramMap, i).x);
    numCurrent += num;

    if (numCurrent < numMin)
      continue;

    num     = numCurrent - numMin;
    numMin  = numCurrent;

    if (numCurrent >= numMax)
    {
      num -= (numCurrent - numMax);
    }

    ev  += num * (cb_Luminance.u_HistoMin + (i + 0.5) * deltaEV);
    numSelected += num;

    if (numCurrent >= numMax)
      break;
  }

  ev = ev/numSelected;

#else           
  //--------------------
  // Basic

  ev = vImageLoad (i_LuminanceMap, ivec2(0,0)).x;
#endif

  ev = vMin(ev, cb_Luminance.u_EVMax);
  ev = vMax(ev, cb_Luminance.u_EVMin);

  float luminance = vExp(ev);

#ifdef EYE_ADAPTATION
  if (cb_Luminance_Auto.u_InitPass == 0)
  {
    float lastluminance = vImageLoad(i_LastLuminanceMap, int(0)).x;

    float speed = luminance > lastluminance ? cb_Luminance.u_SpeedUp : cb_Luminance.u_SpeedDown;

    float alpha = 1.0 - vExp(-speed * cb_Time.u_DeltaTime);
    luminance = lastluminance + (luminance - lastluminance)*alpha;
  }

  vImageStore (i_LastLuminanceMap, 0, vec4(luminance));
#endif

  luminance *= vExp(-cb_Luminance.u_EVC);
  float exposure =  0.2176 / luminance; 
  // NB: 0.217 = 0.5^(1/2.2) by this way after gamma correction of 2.2 we have a default luminance of 0.5 

  vImageStore (i_ExposureMap, 0, vec4(exposure));
}
