#ifdef VoxelMapGeneration
flat out int v_MainDirection;
#endif

float _GetPointToPlaneDistance(int pt, int clipPlane)
{
#ifdef Clipping 
  if(clipPlane == 0)
    return VertexIn[pt]._SBSignedDistance4.x;
  else if(clipPlane == 1)
    return VertexIn[pt]._SBSignedDistance4.y;
  else if(clipPlane == 2)
    return VertexIn[pt]._SBSignedDistance4.z;
  else if(clipPlane == 3)
    return VertexIn[pt]._SBSignedDistance4.w;
  else if(clipPlane == 4)
    return VertexIn[pt]._SBSignedDistance2.x;
  else if(clipPlane == 5)
    return VertexIn[pt]._SBSignedDistance2.y;
#else
  return 0.0;
#endif
}


bool _CalculateSectionProfile(int clipPlane, int stPt, inout vec4 oPtIntersection)
{
#if defined(GPUSectionProfile) && defined(Clipping) 
  int endPt = stPt + 1;
  if(endPt == gl_in.length())
    endPt = 0;

  float distStPt = _GetPointToPlaneDistance(stPt, clipPlane);
  float distEndPt = _GetPointToPlaneDistance(endPt, clipPlane);
  
  if( (distStPt * distEndPt < -1e-6) // end points are on both sides on clip plane
  || ( (abs(distStPt) < 1e-6) && (distEndPt > 1e-6)) // start pt is on clip plane and end pt in visible space
  || ( (abs(distEndPt) < 1e-6) && (distStPt > 1e-6)) // end pt is on clip plane and start pt in visible space 
  )
  { 
    distStPt = abs(distStPt);
    distEndPt = abs(distEndPt);
    float ratio = distStPt / (distStPt + distEndPt);
    vec3 ptInt = mix(VertexIn[stPt]._SBViewPos, VertexIn[endPt]._SBViewPos, ratio); // st + ratio * (end - st)    
        
#ifdef ComputeSectionProfileInGS_SinglePass
   	oPtIntersection = vec4(ptInt, 1); 
#else
	vec4 ptView = vec4(ptInt, 1);
    vec4 signedDistance4;
    vec2 signedDistance2;  	    
    _vComputePlaneClipping(ptView, signedDistance4, signedDistance2);	    
	signedDistance4 += vec4(0.0005);
    vSetClippingDistance(signedDistance4, signedDistance2);

	GeomOut._SBWorldPos = (vGetWorldViewInverseTransposeMatrix() * ptView).xyz;
	//GeomOut._SBViewPos = ptView.xyz;
	GeomOut._SBWorldN = VertexIn[stPt]._SBWorldN;

	oPtIntersection = vGetProjMatrix() * ptView; 
#endif

	return true;
  }
#endif

  return false;
}

void GetClipPlaneDistance(in vec3 iPt, out float oClipDist[6])
{
  vec4 clipDist4;
  vec2 clipDist2;
  _vComputePlaneClipping(vec4(iPt, 1.0), clipDist4, clipDist2);	
  oClipDist[0] = clipDist4.x;
  oClipDist[1] = clipDist4.y;
  oClipDist[2] = clipDist4.z;
  oClipDist[3] = clipDist4.w;
  oClipDist[4] = clipDist2.x;
  oClipDist[5] = clipDist2.y;
}

vec3 RecomputeStartPoint(in vec3 iStPt, in vec3 iEndPt, in float iStDist, in float iEndDist)
{
  float ratio = abs(iStDist) / (abs(iStDist) + abs(iEndDist));
  return mix(iStPt, iEndPt, ratio);
}

void main()
{
#if defined(ComputeSectionProfileInGS_AdditionalPass) && !defined(Clipping)
  return; // doesn't make sense to draw section profile in additional pass when there is no clipping
#endif

#ifdef _PDSFX1_GS_CommonValues
  ComputeCommonValues();
#endif

#ifdef VoxelMapGeneration
  vec3 n = vAbs(vCross((VertexIn[1]._SBViewPos - VertexIn[0]._SBViewPos).xyz, (VertexIn[2]._SBViewPos - VertexIn[0]._SBViewPos).xyz));
  
  mat4 voxelTransfoProj;
  if (n.z > n.x && n.z > n.y)       v_MainDirection = 0;  // oX
  else if (n.x > n.y && n.x > n.z)  v_MainDirection = 1;  // oY
  else                              v_MainDirection = 2;  // oZ

  voxelTransfoProj = cb_Voxel_Auto.tranfoViewToViewProj[v_MainDirection];
#endif

#if defined(GPUSectionProfile) && defined(Clipping) 
  for(int clipPlane = 0; clipPlane < kClipPlanesCount; clipPlane++)
  {
#ifdef ComputeSectionProfileInGS_SinglePass
  vec3 clipResultPts[3];
  int nbClipResultPts = 0;
#endif
#endif

  for(int i = 0; i < gl_in.length(); i++)
  {
    vec4 pos = gl_in[i].gl_Position;

#ifdef _PDSFX1_GS_ClipSpacePos
    ProcessClipSpacePosition(i, pos);
#endif

#ifdef VoxelMapGeneration
    pos = voxelTransfoProj * vec4(VertexIn[i]._SBViewPos, 1.0);
#endif

    gl_Position = pos;   

#ifndef VIEW_SPACE_ONLY
    GeomOut._SBWorldPos = VertexIn[i]._SBWorldPos;
#endif
    
    GeomOut._SBViewPos = VertexIn[i]._SBViewPos;
    GeomOut._SBWorldN = VertexIn[i]._SBWorldN;

#ifdef NeedUVs
    GeomOut._SBuv = VertexIn[i]._SBuv;
#endif

#ifdef HasDecal
    GeomOut._SBLegUVCoord = VertexIn[i]._SBLegUVCoord;
#endif

#ifdef PDSFX1
    GeomOut._SBstpq1 = VertexIn[i]._SBstpq1;
    GeomOut._SBstpq2 = VertexIn[i]._SBstpq2;
#endif

#ifdef LightMap
    GeomOut._SBLightMapUVs = VertexIn[i]._SBLightMapUVs;
#endif

#ifdef UseTangentSpace
    GeomOut._SBWorldT = VertexIn[i]._SBWorldT;
    GeomOut._SBWorldB = VertexIn[i]._SBWorldB;
#endif

#if defined NeedProjPos
    GeomOut._SBProjPos = VertexIn[i]._SBProjPos;
#endif

#if defined NeedViewPos
    GeomOut._SBViewPosPostTransform = VertexIn[i]._SBViewPosPostTransform;
#endif

#ifdef Clipping 
    GeomOut._SBSignedDistance4 = VertexIn[i]._SBSignedDistance4;
    GeomOut._SBSignedDistance2 = VertexIn[i]._SBSignedDistance2;
#endif     
    
#ifdef GroundClipping
    GeomOut._SBSignedDistanceGround = VertexIn[i]._SBSignedDistanceGround;
#endif

#ifdef DecalLighting
    GeomOut.vObjectSpacePosition = VertexIn[i].vObjectSpacePosition;
#endif

#ifdef _PDSFX1_GS_Varyings
    ComputeVaryingValues(i);
#endif

    _CopyVaryings(i); //Automatic copy of needed varyings

#if defined(GPUSectionProfile) && defined(Clipping) 
  #ifdef ComputeSectionProfileInGS_SinglePass
    if(_CalculateSectionProfile(clipPlane, i, pos))
	{
      clipResultPts[nbClipResultPts] = pos.xyz;
      nbClipResultPts++;
    }
    EmitVertex();
  #else
    if(_CalculateSectionProfile(clipPlane, i, pos))
	{
      gl_Position = pos;   
      EmitVertex();
    } 
  #endif
#else 
    EmitVertex();
#endif
  }

  EndPrimitive();

#if defined(GPUSectionProfile) && defined(Clipping) 
#ifdef ComputeSectionProfileInGS_SinglePass
  // check if we have section profile result (line segment) for this triangle and this clip plane
  if(nbClipResultPts == 2)
  {
    bool lineVisible = true;

    float clipDistSt[6], clipDistEnd[6];
    if(kClipPlanesCount > 1) // avoid calculation if no other clip plane is there
    {
      GetClipPlaneDistance(clipResultPts[0], clipDistSt);
      GetClipPlaneDistance(clipResultPts[1], clipDistEnd);
    }

    // calculate final line seg by intersecting it with other clip planes
    for(int iClip = 0; iClip < kClipPlanesCount; iClip++)
    {
      if(iClip == clipPlane)
        continue;
      
      if(clipDistSt[iClip] < 0.0 && clipDistEnd[iClip] < 0.0)
      {
        lineVisible = false;
        break; // line not visible
      }
            
      if(clipDistSt[iClip] > 0.0 && clipDistEnd[iClip] > 0.0)
        continue; // line not cut by current clipping plane

      // line is cut by this clipping plane.. calculate new line 
      // point which is in clipped space will be moved to be on the plane
      if(clipDistSt[iClip] < 0.0) // pt0 is in clipped side ... recompute it
      {
        clipResultPts[0] = RecomputeStartPoint(clipResultPts[0], clipResultPts[1], -clipDistSt[iClip], clipDistEnd[iClip]);  
        GetClipPlaneDistance(clipResultPts[0], clipDistSt);
      }
      if(clipDistEnd[iClip] < 0.0) // pt1 is in clipped side ... recompute it
      {
        clipResultPts[1] = RecomputeStartPoint(clipResultPts[1], clipResultPts[0], -clipDistEnd[iClip], clipDistSt[iClip]);  
        GetClipPlaneDistance(clipResultPts[1], clipDistEnd);
      }
    }

    if(lineVisible)
    {
      // store final line seg result in SSBO
      uint startPt = atomicAdd(indirectCount, nbClipResultPts);

      if((indirectCount * 3) < sectionProfilePoints.length())
      {
        for(int iPt = 0; iPt < nbClipResultPts; iPt++)
        {
          sectionProfilePoints[(startPt + iPt) * 3]     = clipResultPts[iPt].x;
          sectionProfilePoints[(startPt + iPt) * 3 + 1] = clipResultPts[iPt].y;
          sectionProfilePoints[(startPt + iPt) * 3 + 2] = clipResultPts[iPt].z;
        }
      }
    }
  }
#endif
  }// for all clipping planes
#endif


#ifdef _PDSFX1_GS_OutputStreams
  ComputeCustomStreams();
#endif
}
