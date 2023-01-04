//=================================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved
//=================================================================================
//
// CATSmoMeshFromSubdivisionOperator.h
//
//=================================================================================
//
// Usage notes: Création d'un base mesh à partir d'un maillage subdivisé
//
//=================================================================================
// 21/11/07 MMO Correction des erreurs BAD004 (headerruler)
// September,  2007 : RAQ : Creation
//=================================================================================
#ifndef CATSmoMeshFromSubdivisionOperator_H
#define CATSmoMeshFromSubdivisionOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

class CATSobMesh;


class ExportedByCATSmoOperators CATSmoMeshFromSubdivisionOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoMeshFromSubdivisionOperator();

protected:

  //Constructeur
  CATSmoMeshFromSubdivisionOperator(CATSobMesh* iInputMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoMeshFromSubdivisionOperator* CATSmoCreateMeshFromSubdivisionOperator(CATSobMesh* iInputMesh,
                                                                           const int iLevel,
                                                                           CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif


