//===================================================================================
// Copyright Dassault Systemes Provence 2006-2007, All Rights Reserved 
//===================================================================================
//
// CATSmoFacesCreatorOperator.h
//
//===================================================================================
//
// Usage notes: 
//
//===================================================================================
// 21-11-07 MMO Correction des erreurs BAD004 (headerruler)
// 02-01-06 RAQ Création
//===================================================================================
#ifndef CATSmoFacesCreatorOperator_H
#define CATSmoFacesCreatorOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
// #include "CATSobFace.h" // MMO BAD004
#include "CATSobListOfFace.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoFacesCreatorOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Constructeur
  CATSmoFacesCreatorOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Destructeur
  virtual ~CATSmoFacesCreatorOperator();

  //Ajout d'une face quad le long d'une edge
  CATSobDiag SetAddQuadFace(CATSobEdge* iEdgeToExtrude);

  //Ajout d'une face quad le long d'une edge
  CATSobDiag SetAddTriangularFace(CATSobEdge* iEdgeToExtrude);

  //Ajout d'une face s'appuyant sur une liste d'edges libres (4 edges ou 3 edges)
  CATSobDiag SetAddFace(CATLISTP(CATSobEdge)& iEdgesOfNewFace);

protected:

  //Run de l'opérateur
  virtual CATSobDiag RunOperator();

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoFacesCreatorOperator* CATSmoCreateFacesCreatorOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

