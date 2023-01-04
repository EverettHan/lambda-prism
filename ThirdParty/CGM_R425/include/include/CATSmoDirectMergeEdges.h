//=================================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved 
//=================================================================================
//
// CATSmoDirectMergeEdges.h
//
//=================================================================================
//
// Usage notes:
//
//=================================================================================
// Juin,  2007 : ANR : Creation
//=================================================================================
#ifndef CATSmoDirectMergeEdges_H
#define CATSmoDirectMergeEdges_H

//Pour l'export
#include "CATSmoOperators.h"
 
#include "CATSobDiag.h"

class CATSobMesh;
class CATSobEdge;


class ExportedByCATSmoOperators CATSmoDirectMergeEdges
{
public:

  //Constructeur
  CATSmoDirectMergeEdges(CATSobMesh* ioMesh);

  //Destructeur
  virtual ~CATSmoDirectMergeEdges();

  //Set des edges à merger
  void SetEdgesToMerge(CATSobEdge* iEdge1, CATSobEdge* iEdge2) ; 
  
  CATSobDiag Run()  ;

  private:

  //-------- Data:
  CATSobEdge *_Edge1, *_Edge2; 
  CATSobMesh* _Mesh ;

};

#endif



