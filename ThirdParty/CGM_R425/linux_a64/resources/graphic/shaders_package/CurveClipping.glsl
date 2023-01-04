#if defined(CurveClipping) && (defined(GLES2Platform) || !defined(CurveClippingAllowed))
  // Disable sectioning for mobile and some passes (like mirroring)
  #undef CurveClipping
#endif

#ifdef CurveClipping

  void PerformCurveClippingDiscard()
  {
    // Structure of the TBO:
    // 1st vec4: buffer status, curve count, padding, padding

    // 1st curve data info:
    // 2nd vec4: curve clipping direction in view space + curve id
    // 3rd vec4: 1st vertex position in view space, number of sub-curves
    // 4th vec4: flag to determine if curve discards or not its exterior, flag to determine if curve self-intersects, 2x padding
    // 5th vec4: number of segments, start of vertex list clipping planes, min projected distance, max projected distance
    // nth vec4: list of vertex projected distances to the first vertex
    // mth vec4: clipping planes list

    // 2nd+ curve data info:
    // same structure as first curve info, starting with 5th vec4

    if (_sbCurveClipping.u_CurveClippingIDs == 0)
      return;

    vec4 v0 = vTexelFetch(curveClippingData, 0);
    int curveCount = int(v0.y); 

    int nextCurveOffset = 1; // set 1 here to get the 1st curve index correct

    vec3 fragPos = vGetViewPosition();
    
    int shouldDiscard = 0;
    int curveIdx = 0; // for splitted curves: index of current curve fragment
    
    vec3 ccDir;
    vec3 p0;
    int splitCurveCount = 0;
    bool discardExterior = false;
    bool selfIntersects = false;
    int curveID = 0;

    for(int k = 0; k < curveCount; k++)
    {
      // Next curve index
      int curveOffset = nextCurveOffset;
       
      // Get curve info
      if (curveIdx == 0)
      {
        vec4 curveData0 = vTexelFetch(curveClippingData, curveOffset);
        ccDir = curveData0.xyz;
        curveID = int(curveData0.w);

        vec4 curveData1 = vTexelFetch(curveClippingData, curveOffset + 1);
        p0 = curveData1.xyz;
        splitCurveCount = int(curveData1.w);

        vec4 curveData2 = vTexelFetch(curveClippingData, curveOffset + 2);
        discardExterior = curveData2.x > 0;
        selfIntersects = curveData2.y > 0;
      }

      vec4 curveData3 = vTexelFetch(curveClippingData, curveOffset + ((curveIdx == 0) ? 3 : 0));
      int segCount = int(curveData3.x);
      int clippingPlaneListOffset = int(curveData3.y);
      float minProjectedDistance = curveData3.z;
      float maxProjectedDistance = curveData3.w;

      nextCurveOffset = clippingPlaneListOffset + segCount;

      // Check if this curve is applied to this fragment
      if ((_sbCurveClipping.u_CurveClippingIDs & curveID) == 0)
      {
        shouldDiscard = 0;
        curveIdx = 0;
        continue;
      }

      // Compute projected distance to the first vertex
      float projectedDistance = vDot(fragPos - p0, (curveIdx % 2 > 0) ? -ccDir : ccDir);

      int segmentIndex = -1;

      // 1st vertex projected distance is minProjectedDistance
      if (projectedDistance < minProjectedDistance)
      {
        if (curveIdx == 0)
          segmentIndex = 0;
      }

      // last vertex projected distance is maxProjectedDistance
      else if (projectedDistance >= maxProjectedDistance)
      {
        if (curveIdx == splitCurveCount - 1)
          segmentIndex = segCount - 1;
      }

      // Find the interval which contains the fragment projected distance
      else
      {
        int clippingPlaneListOffset = curveOffset + ((curveIdx == 0) ? 4 : 1);
        for (int i = 0, j = 0; i < segCount; i += 4, j++)
        {
          vec4 distances = vTexelFetch(curveClippingData, j + clippingPlaneListOffset);
          for (int c = 0; c < 4; ++c)
          {
            if ((distances[c] > projectedDistance) && (i + c < segCount))
            {
              segmentIndex = i + c;
              break;
            }
          }

          if (segmentIndex != -1)
            break;
        }
      }

      if (segmentIndex != -1)
      {
        vec4 clippingPlane = vTexelFetch(curveClippingData, clippingPlaneListOffset + segmentIndex);
        float planeProj = vDot(vec4(fragPos, 1.0), clippingPlane);

        shouldDiscard += (planeProj <= 0) ? 1 : -1;
      }
     
      curveIdx++;

      // Check if the fragment is discarded because the last curve is detected
      if(curveIdx == splitCurveCount)
      {
        // A fragment is discarded if it has been discarded by a majority of sub-curves
        // If there is no majority (shouldDiscard == 0), it is an exterior point, 
        // and the curve's global orientation tells us wether it should be discarded or not
        if (!selfIntersects)
        {
          if (shouldDiscard > 0 || (discardExterior && shouldDiscard == 0))
            discard;
        }
        // If the curve self-intersects (can be closed), we consider as exterior all fragments with shouldDiscard in [-1, 1]
        else
        {
          if (shouldDiscard >= 2 || (discardExterior && shouldDiscard >= -1))
            discard;
        }
          
        shouldDiscard = 0;
        curveIdx = 0;
      }
    } // Next curve
  }

#endif
