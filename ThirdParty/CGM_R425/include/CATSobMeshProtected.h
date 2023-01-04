//=======================================================================================
// Copyright Dassault Systemes Provence 2006, All Rights Reserved 
//=======================================================================================
//
// CATSobMeshProtected.h
//
//=======================================================================================
//
// Usage notes: ***************** DON'T INCLUDE THIS HEADER *****************
//              Classe n'exposant en Protected que les méthodes de CATSobMesh
//              dont les services ne sont pas ouverts aux utilisateurs mais
//              utilisables par les frameworks de subdivision
//
//=======================================================================================
// January,    2008 : RAQ : Déplacement des méthodes GetMaxTagXXX de protected à public
// December,   2006 : RAQ : Ajout gestion freeze du mesh
// February,   2006 : RAQ : Création
//=======================================================================================
#ifndef CATSobMeshProtected_H
#define CATSobMeshProtected_H


//Check de la possibilité d'inclure ce fichier
/*
#infdef XXXXX
#error Interdiction de tirer cette interface
#endif
*/


//Classe mère
#include "CATSobMesh.h"



class CATSobMeshProtected: public CATSobMesh
{
public:

  //Destructeur
  virtual ~CATSobMeshProtected();

  //Flag d'indication que le mesh a déjà été subdivisé
  virtual void SetExistsSubdivMesh(const CATBoolean iExists = TRUE) = 0;

  //Séparation de vertex
  virtual CATSobDiag SeparateVertex(CATSobVertex* iVertexToSeparate, CATLISTP(CATSobVertex)* oNewVerticesList = 0) = 0;

  //Merge de deux vertex: iVertex1 est conservé et iVertex2 est supprimé
  //0.0 (iVertex1) <= Ratio <= 1.0 (iVertex2), ratio linéaire
  virtual CATSobDiag MergeVertices(CATSobVertex* iVertex1, CATSobVertex* iVertex2, const double iRatio = 0.5) = 0;

  //Merge de deux edges, Edge1 est conservée et Edge2 est supprimée
  virtual CATSobDiag MergeEdges(CATSobEdge* iEdge1, CATSobEdge* iEdge2, const double iRatio = 0.5) = 0;

  //Changement d'orientation d'une sous partie connexe du mesh (pas de gestion des détails)
  virtual CATSobDiag ReverseOrientation(CATLISTP(CATSobFace)* iConnexZoneFaces, CATLISTP(CATSobEdge)* iConnexZoneEdges) = 0;

  //Echange de la DirectFace et de l'InvertFace d'une edge (InvertFace doit exister)
  virtual CATSobDiag SwapDirectAndInvertFaceOfEdge(CATSobEdge* iEdge) = 0;

  //Set du tag d'une face
  virtual void SetTagOnFace(CATSobFace* iFace, const unsigned int iTagForFace) = 0;

  //Set du tag d'un vertex
  virtual void SetTagOnVertex(CATSobVertex* iVertex, const unsigned int iTagForVertex) = 0;

  //Freeze du mesh
  virtual void SetFreezeMesh(const CATBoolean iMustFreeze) = 0;
  virtual CATBoolean IsMeshFrozen() const = 0;

  //Compactage des listes internes de cellules (suppression des éléments nuls)
  virtual void CompactCellsList() = 0;


protected:

  //Constructeur
  CATSobMeshProtected();


private:

  //Copy constructor and equal operator
  CATSobMeshProtected(CATSobMeshProtected&);
  CATSobMeshProtected& operator=(CATSobMeshProtected&);


};

#endif



