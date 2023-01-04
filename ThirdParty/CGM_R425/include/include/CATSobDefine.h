//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobDefine.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// July,      2006 : RAQ : Ajout type de cellule
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// Marsh      2003 : JVC : Creation SdoDefine
//====================================================================
#ifndef CATSobDefine_H
#define CATSobDefine_H


//---------------------------------------------------------------//
//                    Subdivision Cell Type                      //
//---------------------------------------------------------------//
#define CATSobCellType  unsigned int

// Subdivision Vertex type
#define CATSobVertexType  0x01000000

// Subdivision Edge type
#define CATSobEdgeType    0x02000000

// Subdivision Face type
#define CATSobFaceType    0x03000000

//Subdivision Undefined type
#define CATSobUndefType   0x00000000


//---------------------------------------------------------------//
//                      Subdivision Enums                        //
//---------------------------------------------------------------//

typedef enum 
{ 
  CATSobSon_UP_LEFT    = 1,
  CATSobSon_DOWN_LEFT  = 2,
  CATSobSon_DOWN_RIGHT = 3,
  CATSobSon_UP_RIGHT   = 4
} CATSobSonFace;

typedef enum 
{ 
  CATSobSide_LEFT    = 1,
  CATSobSide_DOWN    = 2,
  CATSobSide_RIGHT   = 3,
  CATSobSide_UP      = 4
} CATSobSideFace;

typedef enum 
{ 
  CATSobQuad_Undef   =1,
  CATSobQuad_Yes     =2,
  CATSobQuad_No      =3,
  CATSobQuad_TriQuad =4
} CATSobQuadState;


#endif
