#if defined(Capping) && !defined(GLESPlatform) && (GLSLVersion > 420)


#ifdef SO_MRT_LOCATION_FRAGNORMAL
  layout(location = SO_MRT_LOCATION_FRAGNORMAL) out vec4 fragNormal;
#endif

#ifdef SO_MRT_LOCATION_FRAGF0ROUGH
  layout(location = SO_MRT_LOCATION_FRAGF0ROUGH) out vec4 fragF0Rough;
#endif

#ifdef SO_MRT_LOCATION_GPUPICKINGMAP
  layout(location = SO_MRT_LOCATION_GPUPICKINGMAP) out uint gpuPickingMap;
#endif

void main(void)
{
#ifdef IS_MSAA
  ivec3 imgCoord = ivec3(gl_FragCoord.xy, gl_SampleID);
#else
  ivec2 imgCoord = ivec2(gl_FragCoord.xy);
#endif

  // Check if this fragment has a valid ID
  uint counterMapValue = vTexelFetch(s_DataMap, imgCoord, 0).x;

  uint storedID = counterMapValue & 0xFFFF;

  if(storedID == 0)
  {
    discard;
  }
  
  // Get the front and back faces counter
  uint frontFaceCounter = (counterMapValue & 0xFF000000);
  uint backFaceCounter  = (counterMapValue & 0x00FF0000);

  // Get the stored Z value
  uvec4 colorData = vTexelFetch(s_ColorMap, imgCoord, 0);

  uvec2 storedValue = colorData.xy;
  uvec2 lastValue = uvec2(0);

  uint storedZuint = storedValue.x;
  float storedZ = vUintBitsToFloat(storedZuint);
  float storedDepth = (storedZuint == kDefaultDepth) ? 1.0 : ConvertZViewToZBuffer(storedZ);
  
  // Final capping depth default init
  float cappingZDepth = storedDepth;

  // Check if the last data must be used instead of the stored one
  bool useLastData = false;

  // Make sure the last volume generated capping
  float lastDepth = 0.0;
  if(frontFaceCounter != (backFaceCounter << 8))
  {
    // Check last Z
    lastValue = colorData.zw;
    uint lastZuint = lastValue.x;
    lastDepth = ConvertZViewToZBuffer(vUintBitsToFloat(lastZuint));

    useLastData = (storedDepth > lastDepth) ? true : false;
    cappingZDepth = (storedDepth > lastDepth) ? lastDepth : cappingZDepth;
  }

#ifdef OutputGPUPicking
      uint imgValue = vTexelFetch(s_GPUPickingMap, ivec2(gl_FragCoord.xy), 0).x;
      if(imgValue != 0)
        gpuPickingMap = imgValue;
#endif

  // Resolve
  {
    uint packedColor, packedNormal;

    packedColor = (useLastData == false) ? storedValue.y : lastValue.y;

#ifdef OutputNormalMap
    packedNormal = (useLastData == false) ? 
      vTexelFetch(s_NormalMap, imgCoord, 0).x :
      vTexelFetch(s_NormalMap, imgCoord, 0).y;
#endif

    // Write the color
    vec4 color = unpackUnorm4x8(packedColor);
    FRAGCOLOR = color;

    // Write the depth (with black capping issue by-pass)
    gl_FragDepth = (color.a > 0.5) ? (cappingZDepth + kOffset) : 1.0;

#ifdef OutputNormalMap
    // Write the normal
    fragNormal = unpackSnorm4x8(packedNormal);
#endif

#ifdef OutputF0RoughMap
    // Write material properties to disable any algo using them
    fragF0Rough = vec4(0.0, 0.0, 0.0, 1.0);
#endif
  }
}

#else

void main(void)
{ 
  FRAGCOLOR = vec4(1.0);
  discard;
}

#endif
