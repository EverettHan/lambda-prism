#ifdef TILING_ACTIVATION
vec2 ConvertViewportToViewpoint(const vec2 iCoord)
{
  vec2 coord = vFma(iCoord, cb_PostEffectAuto.u_ViewportToViewpointCoord.zw, cb_PostEffectAuto.u_ViewportToViewpointCoord.xy); 
  return coord;
}

vec2 ConvertViewpointToViewport(const vec2 iCoord)
{
  vec2 coord = vFma(iCoord, cb_PostEffectAuto.u_ViewpointToViewportCoord.zw, cb_PostEffectAuto.u_ViewpointToViewportCoord.xy);
  return coord;
}

vec2 ConvertViewpointToViewportRatio(const vec2 iRatio)
{
  vec2 ratio = iRatio*cb_PostEffectAuto.u_ViewpointToViewportRatio.xy;
  return ratio;
}

#else

#ifndef GLES2Platform

#define ConvertViewportToViewpoint(iCoord)          (iCoord)
#define ConvertViewpointToViewport(iCoord)          (iCoord)
#define ConvertViewpointToViewportRatio(iRatio)     (iRatio) 

#else

vec2 ConvertViewportToViewpoint(const vec2 iCoord)      {return iCoord;}
vec2 ConvertViewpointToViewport(const vec2 iCoord)      {return iCoord;}
vec2 ConvertViewpointToViewportRatio(const vec2 iRatio) {return iRatio;}

#endif

#endif





