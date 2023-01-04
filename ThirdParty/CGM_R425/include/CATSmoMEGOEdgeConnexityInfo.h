
#ifndef CATSmoMEGOEdgeConnexityInfo_H
#define CATSmoMEGOEdgeConnexityInfo_H
//===============================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved 
//===============================================================================
//
// CATSmoExtractGridOperator.h
//
//===============================================================================
//
// Usage notes: A small Class to describe the connexity in generalised cas (Grid)
//
//===============================================================================
// 03-02-09 : RNO : Création
//===============================================================================

//Pour l'export
#include "CATSmoOperators.h"




class CATSobMesh;
class CATSobFace;
class CATSobVertex;

//Structure subdivision

class CATSmoElementaryGrid;


class ExportedByCATSmoOperators CATSmoMEGOEdgeConnexityInfo
{
public:
  CATSmoMEGOEdgeConnexityInfo();
  ~CATSmoMEGOEdgeConnexityInfo(){};
  //
  //Edge Libre ? retourne vrai si l'edge est une edge de bord
  int IsFreeEdge();

  //Some Basic operator to simplify
  int operator ==(const CATSmoMEGOEdgeConnexityInfo & i1);
  int operator !=(const CATSmoMEGOEdgeConnexityInfo & i1);

  CATSmoMEGOEdgeConnexityInfo& operator=(const CATSmoMEGOEdgeConnexityInfo &i);
  int _GridorFaceIdx[2];//Either give the Rank of Grid (if Type==0) or the Rank Of Face (if Type>0) in the Triangular ListOfFace, <0 if nothing on that side
  short _Type[2];// 0 for a Grid else Give the edge's index in the face
  
  short _Side[2];
  short _IdxOnSide[2];
};


#endif
