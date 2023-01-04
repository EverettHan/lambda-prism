//====================================================================
// Copyright Dassault Systemes Provence 2006, all rights reserved 
//====================================================================
//
// CATSmoSymmetryType.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// October,      2014 : RBD : Ajout enum CATSmoTrtTriQuadFaces
// October,      2006 : RBD : Creation
//====================================================================
#ifndef CATSmoSymmetryType_H
#define CATSmoSymmetryType_H

//Pour l'export
#include "CATSobOperators.h"

//---------------------------------------------------------------//
//                      For Symmetry operator                    //
//---------------------------------------------------------------//

// CATSmoSymSide Type concernant la symetrie
// CATSmoInvertSide : Invert side
// CATSmoDirectSide : Same side 
typedef enum 
{ 
  CATSmoInvertSide = -1           ,
  CATSmoDirectSide =  1 
} CATSmoSymSide;

// CATSmoSymSideInfo Type d'information sur la symmetrie
// CATSmoInfoInvertOnly : Invert side Only
// CATSmoInfoInvert     : Invert side prefered
// CATSmoInfoUndefined  : Undefined (Error)
// CATSmoInfoDirect     : Same side prefered 
// CATSmoInfoDirectOnly : Same side Only
typedef enum 
{ 
  CATSmoInfoInvertOnly = -2       ,
  CATSmoInfoInvert     = -1       ,
  CATSmoInfoUndefined  =  0       ,
  CATSmoInfoDirect     =  1       ,
  CATSmoInfoDirectOnly =  2 
} CATSmoSymSideInfo;

// CATSmoSymMode : Mode de l'opérateur
// CATSmoSymmetry       : Mode Symetrie
// CATSmoCutByPlane     : Mode Coupe / Plan
// CATSmoSymMirror      : Mode Miroir
typedef enum 
{ 
  CATSmoSymmetry   =  0           ,
  CATSmoCutByPlane =  1           ,
  CATSmoSymMirror  =  2 
} CATSmoSymMode;

// Variable de traitement des faces 
//  - triangulaire avec un côté sur le plan de symetrie
//  - quad-triangulaire avec 2 côtés sur le plan de symetrie (face triquad)
// = 0 : Ancien algorithme (suppression des triangles et quad-triangles) DEFAUT
// = 1 : Triangle et quad-triangle supprimés (donnent un quad avec la symétrie)
// = 2 : Triangle et Quad-triangle (transformé en triangle) donnent un triangle par symétrie
// = 3 : Triangle et quad triangle absorbé par ses 2 faces voisines (fusion)
typedef enum 
{ 
  CATSmoEraseTriQuads      =  0,
  CATSmoReplaceByQuads     =  1           ,
  CATSmoReplaceByTriangles =  2           ,
  CATSmoReplaceByFusion    =  3
}
CATSmoTrtTriQuadFaces;

ExportedByCATSobOperators
const char* ToString(CATSmoSymSide iSymSide);

ExportedByCATSobOperators
const char* ToString(CATSmoSymSideInfo iSymSideInfo);

ExportedByCATSobOperators
const char* ToString(CATSmoSymMode iSymMode);

#endif
