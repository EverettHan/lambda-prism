//===================================================================
//
// Copyright Dassault Systemes Provence 2005, all rights reserved
//
// HSW :  Header of the class CATSobVisuStore 
//
// 19/11/08 MMO Remise du virtual sur le destructeur
//
// Date : 11 March 2005 
//===================================================================

#ifndef CATSobVisuStore_H
#define CATSobVisuStore_H

#include "CATSobVisu.h"
#include "CATBoolean.h"
#include "CATDataType.h"




class ExportedByCATSobVisu CATSobVisuStore
{
public:

  //Constructeur
  CATSobVisuStore();

  //Destructeur
  virtual ~CATSobVisuStore();	

  //*************************************************************************//
  // Services à implémenter pour le stockage des résultats de la tesselation //
  //************************************************************************ //

  virtual int ComputeParamStatisticOfFace(CATLONG32  iTAGFace,
    int   *    iListTriangleIsolate,
    int        iNbTriangleIsolate,
    int   *    iListStripIndex,
    int        iNbStrip,
    int   *    iNbPtsPerStrip,
    int   *    iListFanIndex,
    int        iNbFan,
    int   *    iNbPtsPerFan);
  // méthode virtuelle qui permet de savoir si l'element que represente
  // le tag a été tessélé.
  virtual CATBoolean DoYouNeed(CATLONG32 iTAG)    ;

  // méthode virtuelle qui stocke l'arréte qui borde une face
  //Float IsSharpEdge : Sorte de vivicite de l'edge
  virtual int StoreEdge(CATLONG32  iTAGEdge,
    CATBoolean iNew,
    int        iNbPts,
    CATLONG32  iBoundedFace,
    CATLONG32  iBoundedFaceOpp,
    int *      iIndicesOnFace,
    short iIsSharpEdge=0)       ;

  // méthode virtuelle qui stocke la face
  virtual int StoreFace(CATLONG32  iTAGFace,
    CATBoolean iNew,
    float *    iCoordsVertices,
    int        iNbPts,
    float *    iCoordsNormals,
    int        iNbNormals,
    int   *    iListTriangleIsolate,
    int        iNbTriangleIsolate,
    int   *    iListStripIndex,
    int        iNbStrip,
    int   *    iNbPtsPerStrip,
    int   *    iListFanIndex,
    int        iNbFan,
    int   *    iNbPtsPerFan,
    int        iNbEdgesOfTheFace = 4) ;

  virtual int SetSTLFileName(char * iSTLFileName);

  virtual int CloseSTLFile();

  //************************************************************************//
  //                           Utilitaires divers                           //
  //*********************************************************************** //
  virtual int StoreFace(CATLONG32  iTAGFace,
    CATBoolean iNew,
    float *    iCoordsVertices,
    int        iNbPts,
    float *    iCoordsNormals,
    int        iNbNormals,
    int   *    iListTriangleIsolate,
    int        iNbTriangleIsolate,
    int   *    iListStripIndex,
    int        iNbStrip,
    int   *    iNbPtsPerStrip,
    int   *    iListFanIndex,
    int        iNbFan,
    int   *    iNbPtsPerFan,
    int        iNbEdgesOfTheFace,
    CATBoolean HasDetail) ;
};

#endif
