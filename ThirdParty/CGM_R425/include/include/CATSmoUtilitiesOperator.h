//===================================================================================
// Copyright Dassault Systemes Provence 2003-2007, All Rights Reserved 
//===================================================================================
//
// CATSmoUtilitiesOperator.h
//
//===================================================================================
//
// Usage notes:
//
//===================================================================================
//  June       2008 : PMG : Ajout CATSmoExtractVerticesRing
//  November,  2007 : MMO : Correction des erreurs BAD004 (headerruler)
//  January,   2006 : RAQ : Modif pour nouveaux opérateurs topo sur CATSubdivMesh
//  August,    2005 : RNO : Ajout Operateur de split
//  January,   2004 : RAQ : Changement d'architecture des subdivisions
//  August,    2003 : jcv : Ajout Offset et AutoFaces
//  Marsh,     2003 : jcv : Creation CATSmoUtilitiesOperator
//===================================================================================
#ifndef CATSmoUtilitiesOperator_H
#define CATSmoUtilitiesOperator_H

#include "CATSmoOperators.h"

// #include "CATSobMesh.h"  // MMO BAD004
// #include "CATSobCell.h"  // MMO BAD004
#include "CATSobDiag.h"
#include "CATSobListOfFace.h"
#include "CATSobListOfVertex.h"

class CATSobEdge;
class CATMathPoint;
class CATSobMesh; // MMO BAD004
class CATSobCell; // MMO BAD004

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateMergeFaces(CATSobFace*           iFace1,
                                  CATSobFace*           iFace2,
                                  const double          iRatio           = 0.,
                                  CATSobEdge*           iEdgeOnFace1     = 0,
                                  CATSobEdge*           iEdgeOnFace2     = 0,
                                  CATLISTP(CATSobFace)* ioToReplaceFaces = 0,
                                  CATLISTP(CATSobFace)* ioSubstitutFaces = 0);

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateMergeEdges(CATSobEdge*           iEdge1,
                                  CATSobEdge*           iEdge2,
                                  const double          iRatio           = 0.,
                                  CATLISTP(CATSobFace)* ioToReplaceFaces = 0,
                                  CATLISTP(CATSobFace)* ioSubstitutFaces = 0);

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateOffsetMesh(CATSobMesh*             iMesh,
                                  const double            iOffset,
                                  const int               iPercent = 0,
                                  CATLISTP(CATSobVertex)* iVerticesToOffset = 0);

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateAutoClose(CATSobMesh* iMesh);

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateLenghtEdges(CATSobMesh* iMesh);

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateCutFaces(CATSobEdge*   iEdge,
                                const int     iNbCut   = 1,
                                const double* iPercent = 0);

ExportedByCATSmoOperators 
CATSobDiag CATSmoCreateSubdivFaces(CATLISTP(CATSobFace)* iFacesToSubdiv,
                                   const double          iRatio = 0.5);

//Split Mesh By Boundary :
// Donne pour une frontiere de vertex etanche, tous les vertex du cote de iOptionalInit (si!=0)
// Si iOptionalInit==0 renvoi un des deux cotes de la frontiere
// On a MeshAllVertices=iBoundarySize U oInnerVerticesSize U (MeshAllVertices/(iBoundarySize U oInnerVerticesSize))
// Contrainte : Il faut que tous les vertex du domaine sans la frontiere 
// soient connectes entre-eux par une arete au moins.
//
ExportedByCATSmoOperators 
CATSobDiag CATSmoSplitMeshByBoundary(CATSobMesh* iMesh,
                           CATLISTP(CATSobVertex)* iBoundary,
                            CATSobVertex * iOptionalInit,
                            CATLISTP(CATSobVertex)* oInnerVertices);


// CATSmoSmallDeformation : Small deformation on the base mesh to reach a point in the space.
// Usefull eg to fit a cote !
// Input : - Mesh : Mesh to modify
//         - Face : The center of this face (at level 2) will reach the  iTarget
//         - iMovingVertices : Vertices that are allowed to move (must contain at least vertices of "Face");
//         - iTarget : the target.
//         - iCoeff : Coefficient of speed to apply on vertices... (1=FullSpeed)
// Return : Distance to the target.
// 
ExportedByCATSmoOperators
double CATSmoSmallDeformation(CATSobMesh * Mesh,CATSobFace * Face,CATLISTP(CATSobVertex) & iMovingVertices, CATMathPoint& iTarget);

// CATSmoExtractVerticesRing : 
// Search the 1 or 2 ring set around a set of verticies

// Input : - iVerticesToAnalyse : Vertices a the center of the rings.
//         - oRingVertices : the verticies found in the rings
//            Here the ring is the vercicies in the Face Ring, not in the input list.
//         - iRingsNumber  : the number of ring to extract 
//           LIMITATION only 1 or 2 rings.
// Return : Diag 
// 
ExportedByCATSmoOperators
CATSobDiag CATSmoExtractVerticesRing(const CATLISTP(CATSobVertex) & iVerticesToAnalyse, 
                                 CATLISTP(CATSobVertex) & oRingVertices, const int iRingsNumber = 1);

#endif
