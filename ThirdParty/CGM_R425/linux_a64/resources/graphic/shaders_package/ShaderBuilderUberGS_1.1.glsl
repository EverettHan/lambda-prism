
#ifndef CascadedShadowGeometryNeeded

/* NJ3 Cascaded Test
in vec4 shadowMapCoordVS[2]; //Pas besoin sur ios (pas de modif dans le master)
out vec4 shadowMapCoord[2]; //Pas besoin sur ios (pas de modif dans le master)
*/ 

void main()
{  
  for(int i = 0; i < gl_in.length(); i++)
  {
  /*
   NJ3 Czascaded Test
    for(int curCascade = 0 ; curCascade < 2 ; ++curCascade)
    {
      shadowMapCoord[curCascade] = shadowMapCoordVS[curCascade];
      //shadowMapCoord[curCascade].x = 0.5;
    }
    */

    vec4 pos = gl_in[i].gl_Position;

    TransformFinalPosition(i, pos);

    gl_Position = pos;    

#ifndef VIEW_SPACE_ONLY
    GeomOut._SBWorldPos = VertexIn[i]._SBWorldPos;
#endif
     
    GeomOut._SBViewPos = VertexIn[i]._SBViewPos;

    GeomOut._SBWorldN = VertexIn[i]._SBWorldN;
#ifdef NeedUVs
    GeomOut._SBuv = VertexIn[i]._SBuv;
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
    
    ProcessVertexCustom(i);

    EmitVertex();
  }



  EndPrimitive();
}
#endif //CascadedShadowGeometryNeeded

