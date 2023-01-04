//====================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved
//====================================================================================
//
// CATSmoAdvancedMeshFromSubdivisionOperator.h
//
//====================================================================================
//
// Usage notes: Création d'un base mesh à partir de la subdivision d'une sous partie
//              d'un maillage et fonctionnalité d'identification des vertex en tant
//              que points de subdivision.
//
//====================================================================================
// October,  2008 : RAQ : Creation
//====================================================================================
#ifndef CATSmoAdvancedMeshFromSubdivisionOperator_H
#define CATSmoAdvancedMeshFromSubdivisionOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

class CATSobMesh;


class ExportedByCATSmoOperators CATSmoAdvancedMeshFromSubdivisionOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoAdvancedMeshFromSubdivisionOperator();

  //Check de la connexité de la working zone, par défaut pas de check
  virtual void SetCheckConnexity() = 0;

  //Option d'ajout d'un attribut sur chacun des sous-vertex pour indiquer la cellule de provenance, par défaut pas d'attribut
  virtual void SetPutAttributesOnVertices() = 0;
 
  //Suivi de l'arbre de détails pour la sous partie, par défaut pas de suivi
  virtual void SetAddDetailsInWorkingZone() = 0;

protected:

  //Constructeur
  CATSmoAdvancedMeshFromSubdivisionOperator(CATSobMesh* iInputMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoAdvancedMeshFromSubdivisionOperator* CATSmoCreateAdvancedMeshFromSubdivisionOperator(CATSobMesh* iInputMesh, const int iLevel, const CATLISTP(CATSobFace)* iWorkingZone,
                                                                                           CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif


