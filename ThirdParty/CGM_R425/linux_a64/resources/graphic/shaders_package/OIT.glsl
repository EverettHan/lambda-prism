#ifdef OIT

#ifndef LogDepth
  //Enable early Z test because it's not enabled by default.
  layout(early_fragment_tests) in;
#endif

#ifdef OIT_HDR
#define OIT_NB_COMPO 2
#else
#define OIT_NB_COMPO 1
#endif


#if OIT_NB_COMPO == 1
#define OIT_COLOR_LAYOUT r32ui
#else
#define OIT_COLOR_LAYOUT rg32ui
#endif


//uniform coherent layout(OIT_COLOR_LAYOUT) uimage2DArray accumulateColor;
//uniform coherent layout(r32ui)            uimage2DArray semaphoreImg; //ugly, just to economise a HC texture slot...


#ifdef OIT_SORT_DEPTH

void StoreColor(float iDepth, inout vec4 iColor)
{
  const int nbLayerOIT = OIT_MAX_LIST;
  const int viewOffset = nbLayerOIT*int(vGetViewID());

#ifdef IS_MSAA
  if((gl_SampleMaskIn[0] & (1 << 0)) == 0) // if first sample is not covered
    discard;
#endif

  const uvec4 minValue = imageLoad(semaphoreImg, ivec3(gl_FragCoord.xy, nbLayerOIT-1 + viewOffset));
  
  if(IsPerspective(gl_FragCoord))
    iDepth = ZClipRemmapedInLinear(vGetNearFarLogFactor().x, vGetNearFarLogFactor().y, iDepth);

  uint myDepth = floatBitsToUint(iDepth);
  int i  = 0;
 
  if(myDepth <= minValue.x)
  {
    uvec4 fragInList;
    for (i  = 0; i < nbLayerOIT ; ++i )
    {
      ivec3 fragPosList = ivec3(gl_FragCoord.xy, i + viewOffset);

      uint oldZ = imageAtomicMin(semaphoreImg, fragPosList, myDepth);
            
      #if defined(OutputGPUPicking)
        if(i == 0 && vFloatBitsToUint(PushConstants.x) != 0 && (oldZ == 0xFFFFFFFFu || myDepth < oldZ))
          imageStore(OITGPUPickingMap, ivec2(gl_FragCoord.xy), uvec4(GetGPUPickingID()));
      #endif

      if(oldZ == 0xFFFFFFFFu)
        break;

      myDepth = max(oldZ, myDepth);

    }
  }
  
  return;
}
#else
#ifdef OIT_SORT_COLOR
void StoreColor(float iDepth, inout vec4 iColor)
#else //OIT_SORT_DEPTH
void StoreColor(float iDepth, in vec4 iColor, in vec4 iFresnel, in vec4 iAttenuation)
#endif
{
  const int nbLayerOIT = OIT_MAX_LIST;
  const int viewOffset = nbLayerOIT*int(vGetViewID());

#ifdef IS_MSAA
  if((gl_SampleMaskIn[0] & (1 << 0)) == 0) // if first sample is not covered
    discard;
#endif

  uvec4 minValue = imageLoad(semaphoreImg, ivec3(gl_FragCoord.xy, nbLayerOIT-1 + viewOffset));
  minValue.x = depthUntag(minValue.x);

  if(IsPerspective(gl_FragCoord))
    iDepth = ZClipRemmapedInLinear(vGetNearFarLogFactor().x, vGetNearFarLogFactor().y, iDepth);

  const uint myDepth = floatBitsToUint(iDepth);
  const uvec4 myFrag = _ConvertPixelToUint(iColor);
  #ifdef OIT_SORT_COLOR_AND_FRESNEL
  const uvec4 myFragFresnel = _ConvertPixelToUint(iFresnel); 
  const uvec4 myFragAttenuation = _ConvertPixelToUint(iAttenuation); 
  #endif
  int i  = 0;

  if(myDepth <= minValue.x)
  {
    for (i  = 0; i < nbLayerOIT ; ++i )
    {
      ivec3 fragPosList = ivec3(gl_FragCoord.xy, i + viewOffset);

      uvec4 depthInList     = imageLoad(semaphoreImg,    fragPosList);
      uvec4 fragColorInList = imageLoad(accumulateColor, fragPosList);

      if (abs(iDepth - uintBitsToFloat(depthUntag(depthInList.x))) <= g_depthFightThreshold)
      {

        uint oldDepth = imageAtomicOr(semaphoreImg, fragPosList, getDepthTag());
        if (isTagged(oldDepth))
          continue;
        imageStore(accumulateColor, fragPosList, myFrag);

		#ifdef OIT_SORT_COLOR_AND_FRESNEL
		imageStore(accumulateFresnel, fragPosList, myFragFresnel);
        imageStore(attenuations, fragPosList, myFragAttenuation);
		#endif
        break;
      }

    }

    discard;
  }
}

#endif //OIT
#endif //OIT
