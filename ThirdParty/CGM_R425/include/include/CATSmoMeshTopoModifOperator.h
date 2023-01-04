//====================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//====================================================================
//
// CATSmoMeshTopoModifOperator.h
//
//====================================================================
//
// Usage notes: Opérateur effectuant les modifications topologiques
//              sur le mesh
//
//====================================================================
// June,      2010 : RAQ : Changement d'archi pour Phase 2
// October,   2008 : RAQ : Ajout gestion détails
// November,  2005 : RAQ : Création
//====================================================================
#ifndef CATSmoMeshTopoModifOperator_H
#define CATSmoMeshTopoModifOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Diag
#include "CATSobDiag.h"

//Objets Subdivision
#include "CATSobListOfFace.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"

//Divers
#include "CATBoolean.h"

class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobVertex;


class ExportedByCATSmoOperators CATSmoMeshTopoModifOperator
{
public:

  //Destruction par release
  virtual void Release() = 0;

  //Gestion du compteur de référence
  virtual int GetNbRef() const = 0;
  virtual void AddRef() = 0;

  //Obtention du diag
  virtual CATSobDiag GetDiag() const = 0;

  //Set/Get du Mesh
  virtual void SetMesh(CATSobMesh* iMesh) = 0;
  virtual CATSobMesh* GetMesh() const = 0;

  /////////////////////////////////////////////////////////////////////////
  //----- Options de suivi des cellules pour le journal topologique -----//
  /////////////////////////////////////////////////////////////////////////
  virtual CATBoolean MustFollowCells() const = 0;

  /////////////////////////////////////////////////////////////////
  //---------- Modifications géométriques du base mesh ----------//
  /////////////////////////////////////////////////////////////////

  //Changement des coordonnées d'un vertex
  virtual CATSobDiag SetVertexCoordinates(CATSobVertex* iVertex, const double* iCoords) = 0;
  virtual CATSobDiag SetVertexCoordinates(CATSobVertex* iVertex, const double iX, const double iY, const double iZ) = 0;

  //Changement du poids d'un vertex
  virtual CATSobDiag SetVertexWeight(CATSobVertex* iVertex, const double iWeight) = 0;

  //Changement du sharpness d'une edge
  virtual CATSobDiag SetSharpnessOnEdge(CATSobEdge* iEdge, const short iSharpness) = 0;
  virtual CATSobDiag SetSharpnessOnEdge(CATSobEdge* iEdge, const short iSharpness, const CATBoolean iSmoothEdge) = 0;

  //Vivicité d'une edge: G0 (FALSE) / G1 (TRUE)
  virtual CATSobDiag SetSmoothingOnEdge(CATSobEdge* iEdge, const CATBoolean iSmoothEdge) = 0;

  //Mise à jour des cellules autour d'un vertex
  virtual CATSobDiag SetVertexModified(CATSobVertex* iVertex, const int iNbRings) = 0;

  //Mise en modification d'une face
  virtual CATSobDiag SetFaceModified(CATSobFace* iSobFace) = 0;

  //Force la reconstruction topologique de l'image d'une face subdiv sur le body associé (purement topo)
  virtual CATSobDiag SetForceTopoReconstruction(CATSobFace* iSobFace) = 0;


  /////////////////////////////////////////////////////////////////
  //-------------------- Gestion des détails --------------------//
  /////////////////////////////////////////////////////////////////

  //Set de détails
  virtual CATSobDiag SetDetail(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const double* iDetail, const int iDaughterFaceIndex = 0) = 0;
  virtual CATSobDiag SetDetail(CATSobEdge* iEdge, const int iU, const int iLevel, const double* iDetail) = 0;
  virtual CATSobDiag SetDetail(CATSobVertex* iVertex, const int iLevel, const double* iDetail) = 0;

  //Ajout de détails
  virtual CATSobDiag AddDetail(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const double* iDetail, const int iDaughterFaceIndex = 0) = 0;
  virtual CATSobDiag AddDetail(CATSobEdge* iEdge, const int iU, const int iLevel, const double* iDetail) = 0;
  virtual CATSobDiag AddDetail(CATSobVertex* iVertex, const int iLevel, const double* iDetail) = 0;

  //Suppression de détails
  virtual CATSobDiag RemoveDetail(CATSobFace* iFace, const int iU, const int iV, const int iLevel, const int iDaughterFaceIndex = 0) = 0;
  virtual CATSobDiag RemoveDetail(CATSobEdge* iEdge, const int iU, const int iLevel) = 0;
  virtual CATSobDiag RemoveDetail(CATSobVertex* iVertex, const int iLevel) = 0;

  //Suppression d'un niveau de détails
  virtual CATSobDiag RemoveLOD(CATSobFace* iFace, const int iLevel) = 0;
  virtual CATSobDiag RemoveLOD(CATSobEdge* iEdge, const int iLevel) = 0;

  //Suppression de tous les détails
  virtual CATSobDiag RemoveAllDetails() = 0;

  //Conversion des détails en local frame
  virtual CATSobDiag ConvertDetailsToLocalFrame() = 0;
  
  //Conversion des détails en global frame
  virtual CATSobDiag ConvertDetailsToGlobalFrame() = 0;


  /////////////////////////////////////////////////////////////////
  //---------- Modifications topologiques du base mesh ----------//
  /////////////////////////////////////////////////////////////////
  
  //Création du Current Mesh
  virtual CATSobMesh* CreateCurrentMesh(CATSobMesh* iMesh, const CATBoolean iReportCellCreation = TRUE) = 0;

  //Création d'une face
  virtual CATSobDiag CreateFace(CATLISTP(CATSobEdge)& iEdgesOfFace, CATSobFace*& oNewFace) = 0;

  //Ajout de plusieurs faces dans un mesh (sans join !!!), possibilité de suivi
  virtual CATSobDiag AddFaces(CATLISTP(CATSobFace)& iFacesToAdd, CATLISTP(CATSobFace)* ioCopiedFaces,
                              CATLISTP(CATSobEdge)* iInputEdges = 0, CATLISTP(CATSobEdge)* ioCopiedEdges = 0,
                              CATLISTP(CATSobVertex)* iInputVertices = 0, CATLISTP(CATSobVertex)* ioCopiedVertices = 0) = 0;

  //Destruction d'une face
  virtual CATSobDiag RemoveFace(CATSobFace* iFaceToRemove) = 0;

  //Création d'une edge
  virtual CATSobDiag CreateEdge(CATSobVertex* iStartVertex, CATSobVertex* iEndVertex, CATSobEdge*& oCreatedEdge) = 0;

  //Destruction d'une edge
  virtual CATSobDiag RemoveEdge(CATSobEdge* iEdgeToRemove, const int* iEdgeIndex = 0) = 0;

  //Création d'un vertex
  virtual CATSobDiag CreateVertex(const double* iVertexCoords, CATSobVertex*& oCreatedVertex) = 0;
  virtual CATSobDiag CreateVertex(const double iX, const double iY, const double iZ, CATSobVertex*& oCreatedVertex) = 0;

  //Destruction d'un vertex
  virtual CATSobDiag RemoveVertex(CATSobVertex* iVertexToRemove, const int* iVertexIndex = 0) = 0;

  //Merge de deux edges
  virtual CATSobDiag MergeEdges(CATSobEdge* iEdgeToKeep, CATSobEdge* iEdgeToMerge, const double iRatio = 0.5) = 0;

  //Merge de deux vertex
  virtual CATSobDiag MergeVertices(CATSobVertex* iVertexToKeep, CATSobVertex* iVertexToMerge, const double iRatio = 0.5) = 0;

  //Mise à jour du mesh courant
  virtual CATSobDiag UpdateCurrentMesh() = 0;

  //Vérification du mesh courant
  virtual CATSobDiag CheckCurrentMeshBasic(const CATBoolean iAllowNullCells = FALSE) = 0;
  virtual CATSobDiag CheckCurrentMesh(const CATBoolean iAllowNullCells = FALSE) = 0;

  //Activation/Désactivation des checks sur le base mesh, par défaut les checks sont actifs
  virtual void SetEnableChecks(const CATBoolean iOnOff) = 0;
  virtual CATBoolean GetEnableChecks() const = 0;


  
  //DO NOT USE - Set des faces et vertex créés en externe
  virtual void SetNewSobFaces(CATLISTP(CATSobFace)& iNewSobFaces, const CATBoolean iReportCellCreation = TRUE) = 0;
  virtual void SetNewSobVertices(CATLISTP(CATSobVertex)& iNewSobVertices, const CATBoolean iReportCellCreation = TRUE) = 0;

  //DO NOT USE - Duplication
  virtual CATSobDiag Duplicate(CATSobMesh* iMeshForDuplication, CATSmoMeshTopoModifOperator** opDuplicatedOperator) const = 0;


protected:

  //Destructeur
  virtual ~CATSmoMeshTopoModifOperator() {}

};


/**
 * Builds a CATSmoMeshTopoModifOperator object.
 *
 * @param iMesh
 * The mesh the operator will modify, it can be NULL.
 *
 * @return
 * The operator.
 **/
ExportedByCATSmoOperators
CATSmoMeshTopoModifOperator* CATSmoCreateMeshTopoModifOperator(CATSobMesh* iMesh);


#endif



