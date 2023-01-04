//=======================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=======================================================================================
//
// CATSmoSplitEdgesOperator.h
//
//=======================================================================================
//
// Usage notes: Séparation d'une liste d'edges, le base mesh peut devenir non connexe
//              et peut contenir des ngones.
//
//=======================================================================================
// May,   2009 : RAQ : Creation
//=======================================================================================
#ifndef CATSmoSplitEdgesOperator_H
#define CATSmoSplitEdgesOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobListOfFace.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;

class ExportedByCATSmoOperators CATSmoSplitEdgesOperator
{
public:

  //Destructeur
  virtual ~CATSmoSplitEdgesOperator();

  //Set de la loop d'edge
  virtual void SetEdgesToSplit(const CATLISTP(CATSobEdge)& iEdgesToSplit) = 0;

  //Option d'update du mesh: si utilisé les pointeurs contenus dans les listes oEdgesToSplit et oVerticesToSplit
  //des méthodes GetNewEdges et GetNewVertices désigneront des objets déjà détruits
  virtual void SetMustUpdateMesh() = 0;

  //Run de l'opérateur
  virtual CATSobDiag Run() = 0;

  //Diag de l'opérateur
  virtual CATSobDiag GetDiag() const = 0;

  //DEPRECATED : Suivi des nouvelles edges et des nouveaux vertex
  virtual CATSobDiag GetNewEdges(CATLISTP(CATSobEdge)& oEdgesToSplit, CATLISTP(CATSobEdge)& oNewEdges) = 0;
  virtual CATSobDiag GetNewVertices(CATLISTP(CATSobVertex)& oVerticesToSplit, CATLISTP(CATSobVertex)& oNewVertices) = 0;

  //DEPRECATED : Obtention des sous-ensembles connexes de faces
  virtual CATSobDiag GetSubsetsOfFaces(CATLISTP(CATSobFace)*& oSubsetsOfFaces, int& oNbSubsets) = 0;

protected:

  //Constructeur
  CATSmoSplitEdgesOperator();
  
};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoSplitEdgesOperator* CATSmoCreateSplitEdgesOperator(CATSobMesh* iMesh, 
                                                         CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);



#endif


