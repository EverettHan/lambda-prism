//==============================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//==============================================================================
//
// CATSmoSplitVertexOperator.h
//
//==============================================================================
//
// Usage notes: Séparation d'un vertex.
//
//==============================================================================
// May,   2009 : RAQ : Creation
//==============================================================================
#ifndef CATSmoSplitVertexOperator_H
#define CATSmoSplitVertexOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"

class CATSobVertex;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoSplitVertexOperator
{
public:

  //Destructeur
  virtual ~CATSmoSplitVertexOperator();

  //Option d'update du mesh: si utilisé les pointeurs contenus dans les listes oEdgesToSplit et oVerticesToSplit
  //des méthodes GetNewEdges et GetNewVertices désigneront des objets déjà détruits
  virtual void SetMustUpdateMesh() = 0;

  //Run de l'opérateur
  virtual CATSobDiag Run() = 0;

  //Diag de l'opérateur
  virtual CATSobDiag GetDiag() const = 0;




protected:

  //Constructeur
  CATSmoSplitVertexOperator();

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoSplitVertexOperator* CATSmoCreateSplitVertexOperator(CATSobVertex* iVertexToSplit, 
                                                           CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);




#endif

