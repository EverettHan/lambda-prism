//=======================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved
//=======================================================================
//
// CATSmoFaceJournalItem.h
//
//=======================================================================
//
// Usage notes: Objet de suivi pour le journal topologique
//              (attribut des faces du base mesh)
//
//=======================================================================
// 23.03.2016 : RAQ : Ajout Set/GetInheritSobProperties + duplication pour meilleur suivi
// November,     2007 : RBD : Modif de la signature de GetAncestorFacesTags
//                            et de GetParentsObjects pour protéger 
//                            les données membres de la classe
// February,     2007 : RAQ : Creation
//=======================================================================
#ifndef CATSmoFaceJournalItem_H
#define CATSmoFaceJournalItem_H

//Classe mère
#include "CATSobAttributes.h"

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATBoolean.h"
#include "CATSmoAncestorFace.h"
#include "CATSmoListVOfAncestorFace.h"
#include "CATDataType.h"
#include "CATListOfULONG32.h"
#include "CATListPV.h"

class CATGeometry;

CATDECLARESOBATTRIBUTE(CATSmoFaceJournalItem, CATSmoFaceJournalItemID)

//********************************************************************************
// Classe de base, il faut décliner suivant que la face est quad ou tri.
//********************************************************************************
class CATSmoQuadFaceJournalItem;
class CATSmoTriFaceJournalItem;
class CATSmoNGonFaceJournalItem;

class ExportedByCATSmoOperators CATSmoFaceJournalItem: public CATSobAttributes
{
public:

  //Les casts
  virtual CATSmoQuadFaceJournalItem* CastToQuadFaceJournalItem() { return 0; }
  virtual CATSmoTriFaceJournalItem* CastToTriFaceJournalItem() { return 0; }
  virtual CATSmoNGonFaceJournalItem* CastToNGonFaceJournalItem() { return 0; }

  //Indique que la cellule doit avoir les mêmes propriétés que son parent si c'est une CATSobCell
  inline void SetInheritSobProperties(const CATBoolean iMustInherit = TRUE) { m_inheritSobProperties=iMustInherit; }
  inline CATBoolean GetInheritSobProperties() const { return m_inheritSobProperties; }

  //Duplicate a journal item depending on its type
  static CATSmoFaceJournalItem* Duplicate(CATSmoFaceJournalItem* ipToCopy);

protected:

  //Constructeur
  CATSmoFaceJournalItem():
    CATSobAttributes(CATSmoFaceJournalItemID),
    m_inheritSobProperties(FALSE)
  {}

  //Destructeur
  virtual ~CATSmoFaceJournalItem() {}

  //----- Data :
  CATBoolean m_inheritSobProperties;
};


//********************************************************************************
// Journaux pour les faces QUAD
//********************************************************************************
class ExportedByCATSmoOperators CATSmoQuadFaceJournalItem: public CATSmoFaceJournalItem
{
public:
  
  //Constructeur
  CATSmoQuadFaceJournalItem(CATSmoQuadFaceJournalItem* ipToCopy = NULL);

  //Le cast
  virtual CATSmoQuadFaceJournalItem* CastToQuadFaceJournalItem() { return this; }

  //Ajout d'une cellule mère par son tag
  void AddAncestorFaceTag(const CATSmoAncestorFace& iAncestorFace);

  //Récupération des tags des cellules mères
  int GetAncestorFacesTags(CATSmoListVOfAncestorFace& oAncestorFacesTags);

  //Ajout d'une edge mère par les tags de ses vertex extrémités
  void AddAncestorEdge(const CATULONG32 iStartVertexTag, const CATULONG32 iEndVertexTag);

  //Récupération des infos des edges mères : tags des vertex extrémités des edges mères, ils sont rangés à la suite dans la liste
  // ie. SVTagOfParentEdge1, EVTagOfParentEdge1, SVTagOfParentEdge2, EVTagOfParentEdge2, ....
  //La méthode renvoie le nombre d'EDGES mères.
  int GetAncestorEdges(CATListOfULONG32& oExtremityVerticesTags);

  // Existe-t-il des edges mères ?
  CATBoolean HasAncestorEdge() const;

  //Ajout d'un parent topologique
  void AddParentObject(CATGeometry* iParentObject);

  //Obtention des parents topologiques
  int GetParentsObjects(CATListPV& oParentsObjects);

protected:

  //Destructeur
  virtual ~CATSmoQuadFaceJournalItem();


private:

  //------- Data:
  CATSmoListVOfAncestorFace _AncestorFaces;
  CATListOfULONG32 _ExtremityVerticesTags;
  CATListPV _TopologicalParents;
};

//Création de l'objet
ExportedByCATSmoOperators
CATSmoQuadFaceJournalItem* CATSmoCreateQuadFaceJournalItem(CATSmoQuadFaceJournalItem* ipToCopy = NULL);


//********************************************************************************
// Journaux pour les faces TRI
//********************************************************************************
class ExportedByCATSmoOperators CATSmoTriFaceJournalItem: public CATSmoFaceJournalItem
{

public:
  
  //Constructeur
  CATSmoTriFaceJournalItem(CATSmoTriFaceJournalItem* ipToCopy = NULL);

  //Le cast
  virtual CATSmoTriFaceJournalItem* CastToTriFaceJournalItem() { return this; }

  //Ajout d'une cellule mère par son tag
  void AddAncestorFaceTag(const CATSmoAncestorFace& iAncestorFace, const int iDaughterFaceIndex);
  void AddAncestorFaceTag(const CATSmoAncestorFace& iAncestorFace);

  //Récupération des tags des cellules mères
  int GetAncestorFacesTags(CATSmoListVOfAncestorFace& oAncestorFacesTags, const int iDaughterFaceIndex);

  //Ajout d'un parent topologique, 1 <= iDaughterFaceIndex <= 3
  void AddParentObject(CATGeometry* iParentObject, const int iDaughterFaceIndex);

  //Obtention des parents topologiques, 1 <= iDaughterFaceIndex <= 3
  int GetParentsObjects(CATListPV& oParentsObjects, const int iDaughterFaceIndex);


protected:

  //Destructeur
  virtual ~CATSmoTriFaceJournalItem();


private:


  //------- Data:
  CATSmoListVOfAncestorFace _AncestorFaces[3];
  CATListPV _TopologicalParents[3];
};

//Création de l'objet
ExportedByCATSmoOperators
CATSmoTriFaceJournalItem* CATSmoCreateTriFaceJournalItem(CATSmoTriFaceJournalItem* ipToCopy = NULL);


//********************************************************************************
// Journaux pour les faces NGones
//********************************************************************************
class ExportedByCATSmoOperators CATSmoNGonFaceJournalItem: public CATSmoFaceJournalItem
{

public:
  
  //Constructeur
  CATSmoNGonFaceJournalItem(CATSmoNGonFaceJournalItem* ipToCopy = NULL);

  //Le cast
  virtual CATSmoNGonFaceJournalItem* CastToNGonFaceJournalItem() { return this; }

  //Ajout d'une cellule mère par son tag
  void AddAncestorFaceTag(const CATSmoAncestorFace& iAncestorFace);

  //Récupération des tags des cellules mères
  int GetAncestorFacesTags(CATSmoListVOfAncestorFace& oAncestorFacesTags);

  //Ajout d'un parent topologique
  void AddParentObject(CATGeometry* iParentObject);

  //Obtention des parents topologiques
  int GetParentsObjects(CATListPV& oParentsObjects);


protected:

  //Destructeur
  virtual ~CATSmoNGonFaceJournalItem();


private:


  //------- Data:
  CATSmoListVOfAncestorFace _AncestorFaces;
  CATListPV _TopologicalParents;
};

//Création de l'objet
ExportedByCATSmoOperators
CATSmoNGonFaceJournalItem* CATSmoCreateNGonFaceJournalItem(CATSmoNGonFaceJournalItem* ipToCopy = NULL);



#endif



