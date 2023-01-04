#ifdef CascadedShadowGeometryNeeded
 
 
#ifdef CascadedShadow
in vec4 shadowMapCoordVS[NB_CASCADES]; //Pas besoin sur ios (pas de modif dans le master)
out vec4 shadowMapCoord[NB_CASCADES]; //Pas besoin sur ios (pas de modif dans le master)
#endif
 
void main()
{  

  for(int curCascade = 0 ; curCascade < NB_CASCADES ; ++curCascade)
  {
      shadowMapCoord[curCascade] = shadowMapCoordVS[curCascade];
      shadowMapCoord[curCascade].x = 1;

    for(int i = 0; i < 3; i++)
    {      
      gl_Layer = curCascade;  
      gl_Position = _sbcbCascadedShadow.LightViewProjMatrix[curCascade] * vec4(VertexIn[i]._SBViewPos, 1);//gl_in[i].gl_Position;    
      EmitVertex();
    }
    
    EndPrimitive();

  }
}
 
 
 #endif //CascadedShadow
