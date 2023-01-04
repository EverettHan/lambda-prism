//=================================================================================
// Copyright Dassault Systemes Provence 2006-2007, All Rights Reserved 
//=================================================================================
//
// CATSmoOffsetMeshOperator.h
//
//=================================================================================
//
// Usage notes:
//
//=================================================================================
// November,  2007 : MMO : Correction des erreurs BAD004 (headerruler)
// February,  2006 : RAQ : Creation
//=================================================================================
#ifndef CATSmoOffsetMeshOperator_H
#define CATSmoOffsetMeshOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Classe mère
#include "CATSmoSubdivisionMeshOperator.h"

#include "CATSobListOfVertex.h" // MMO BAD004


class ExportedByCATSmoOperators CATSmoOffsetMeshOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoOffsetMeshOperator();

  //Set de la valeur d'Offset
  virtual void SetOffsetValue(const double iOffsetValue) = 0;
  virtual void SetOffsetRatio(const int iOffsetRatio) = 0;

  //Set des points susceptibles d'être déplacés
  virtual void SetVerticesToOffset(CATLISTP(CATSobVertex)* iVerticesToOffset) = 0;


protected:

  //Constructeur
  CATSmoOffsetMeshOperator(CATSobMesh* iMesh,
                           CATSmoMeshTopoModifOperator* iTopoModifOpe);


};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoOffsetMeshOperator* CATSmoCreateOffsetMeshOperator(CATSobMesh* iMesh,
                                                         CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif


