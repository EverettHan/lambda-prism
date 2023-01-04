#ifndef CATPolygonToSurfMeshFunction_h
#define CATPolygonToSurfMeshFunction_h

#define  PolygonToSurfMeshFunction
#define  PolygonToSurfMeshFuncion
//  mesh  function  prototype
typedef  int (*MeshFunc4P2S)( int iNbPoints , const  float * iXYZ ,  int  & oNbVtx,  int ** oVtx ) ;

#endif
