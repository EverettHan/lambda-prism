//=================================================================================
// Copyright Dassault Systemes Provence 2006, All Rights Reserved 
//=================================================================================
//
// CATSmoMergeFacesOperator.h
//
//=================================================================================
//
// Usage notes:
//
//=================================================================================
// June,      2014 : RBD : Gestion de l'autoweight sur les vertices 
// February,  2006 : RAQ : Creation
//=================================================================================
#ifndef CATSmoMergeFacesOperator_H
#define CATSmoMergeFacesOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Classe mère
#include "CATSmoSubdivisionMeshOperator.h"

//Objets Subdivision
#include "CATSobListOfFace.h"

class CATSobMesh;
class CATSobEdge;


class ExportedByCATSmoOperators CATSmoMergeFacesOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoMergeFacesOperator();

  //Set des faces à merger
  virtual void SetFacesToMerge(CATSobFace* iFace1, CATSobFace* iFace2, const double iRatio = 0.0,
                               CATSobEdge* iEdge1OnFace1 = 0, CATSobEdge* iEdge2OnFace2 = 0) = 0;

  // Activation du poid automatique sur les vertex DES FACES SELECTIONNEES.
  // Pour activer le report automatique du poids des edges DES FACES SELECTIONNEES vers les vertex commun, 
  // mettre iAutoWeight à TRUE.
  // Il faut qu'il y ai au moins 3 edges de poids > 0 (et < 999) pour que le poids du vertex commun soit modifié.
  // Pour désactiver le poids automatique, remettre iAutoWeight à FALSE.
  virtual void SetAutoWeight(const CATBoolean iAutoWeight = FALSE) = 0;

  //Obtention des faces modifiées -> A SUPPRIMER
  virtual int GetModifications(CATLISTP(CATSobFace)*& ioToReplaceFaces,
                               CATLISTP(CATSobFace)*& ioSubstitutFaces) const = 0;

  
protected:
  
  //Constructeur
  CATSmoMergeFacesOperator(CATSobMesh* iMesh,
                           CATSmoMeshTopoModifOperator* iTopoModifOpe);

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoMergeFacesOperator* CATSmoCreateMergeFacesOperator(CATSobMesh* iMesh,
                                                         CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif



