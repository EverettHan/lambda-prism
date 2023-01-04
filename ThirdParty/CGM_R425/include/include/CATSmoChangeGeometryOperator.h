//===================================================================================
// Copyright Dassault Systemes Provence 2006, All Rights Reserved 
//===================================================================================
//
// CATSmoChangeGeometryOperator.h
//
//===================================================================================
//
// Usage notes: 
//
//===================================================================================
// July,      2009 : RBD : Ajout SetAutoWeight sur les vertex
// October,   2008 : RAQ : Ajout gestion détails
// February,  2006 : RAQ : Création
//===================================================================================
#ifndef CATSmoChangeGeometryOperator_H
#define CATSmoChangeGeometryOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"

class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobVertex;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoChangeGeometryOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Constructeur
  CATSmoChangeGeometryOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Destructeur
  virtual ~CATSmoChangeGeometryOperator();

  //Changement des coordonnées d'un vertex
  virtual CATSobDiag SetVertexCoordinates(CATSobVertex* iVertex, const double* iCoords);
  virtual CATSobDiag SetVertexCoordinates(CATSobVertex* iVertex, const double iX, const double iY, const double iZ);

  //Changement du poids d'un vertex
  virtual CATSobDiag SetVertexWeight(CATSobVertex* iVertex, const double iWeight);

  //Set d'un poids pour tous les vertex de bord
  virtual CATSobDiag SetWeightOnAllBoundaryVertices(const double iWeight);

  //Changement du Sharpness d'une edge
  CATSobDiag SetSharpnessOnEdge(CATSobEdge* iEdge, const short iSharpness);
  CATSobDiag SetSharpnessOnEdge(CATSobEdge* iEdge, const short iSharpness, const CATBoolean iSmoothEdge);

  //Type de raccord à effectuer le long de l'edge: G0 (FALSE) / G1 (TRUE)
  CATSobDiag SetSmoothingOnEdge(CATSobEdge* iEdge, const CATBoolean iSmoothEdge);
  
  // Activation du poid automatique sur les vertex.
  // Pour activer le report automatique du poids des edges vers les vertex commun, mettre iAutoWeight à 1.
  // PUIS utiliser les méthodes SetSharpnessOnEdge ou SetSmoothingOnEdge.
  // Il faut qu'il y ai au moins 3 edges de poids > 0 pour que le poids du vertex commun soit modifié.
  // Pour désactiver le poids automatique, remettre iAutoWeight à 0.
  virtual void SetAutoWeightOnVertices(const CATBoolean iAutoWeight = 0);

  //////////////////////// Gestion des détails ////////////////////////
  //Set de détails
  virtual CATSobDiag SetDetail(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const double* iDetail, const int iDaughterFaceIndex = 0);
  virtual CATSobDiag SetDetail(CATSobEdge* iEdge, const int iU, const int iLevel, const double* iDetail);
  virtual CATSobDiag SetDetail(CATSobVertex* iVertex, const int iLevel, const double* iDetail);

  //Ajout de détails
  virtual CATSobDiag AddDetail(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const double* iDetail, const int iDaughterFaceIndex = 0);
  virtual CATSobDiag AddDetail(CATSobEdge* iEdge, const int iU, const int iLevel, const double* iDetail);
  virtual CATSobDiag AddDetail(CATSobVertex* iVertex, const int iLevel, const double* iDetail);

  //Suppression de détails
  virtual CATSobDiag RemoveDetail(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const int iDaughterFaceIndex = 0);
  virtual CATSobDiag RemoveDetail(CATSobEdge* iEdge, const int iU, const int iLevel);
  virtual CATSobDiag RemoveDetail(CATSobVertex* iVertex, const int iLevel);

  //Suppression d'un niveau de détails
  virtual CATSobDiag RemoveLOD(CATSobFace* iFace, const int iLevel);
  virtual CATSobDiag RemoveLOD(CATSobEdge* iEdge, const int iLevel);

  //Suppression de tous les détails
  virtual CATSobDiag RemoveAllDetails();

  //Conversion des détails en local frame
  virtual CATSobDiag ConvertDetailsToLocalFrame();
  
  //Conversion des détails en global frame
  virtual CATSobDiag ConvertDetailsToGlobalFrame();


protected:

  //Run de l'opérateur
  virtual CATSobDiag RunOperator();

private:
  int _AutoWeight;

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoChangeGeometryOperator* CATSmoCreateChangeGeometryOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

