//======================================================================
// Copyright Dassault Systemes Provence 2006-2007, all rights reserved 
//======================================================================
//
// CATSmoRemoveEdgesOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
// 21-11-07 MMO Correction des erreurs BAD004 (headerruler)
// 01-10-06 RBD Creation
//======================================================================
#ifndef CATSmoRemoveEdgesOperator_H
#define CATSmoRemoveEdgesOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
// #include "CATSobEdge.h" // MMO BAD004
#include "CATSobListOfEdge.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoRemoveEdgesOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoRemoveEdgesOperator();

  //Remove  d'une liste d'aretes
  virtual void SetEdgesToRemove(CATLISTP(CATSobEdge)* iEdgesToRemove) = 0;

  // Verification input
  virtual CATSobDiag VerifInputEdges() = 0;


protected:

  //Constructeur
  CATSmoRemoveEdgesOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoRemoveEdgesOperator* CATSmoCreateRemoveEdgesOperator(CATSobMesh* iMesh, 
                                                           CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

