//=======================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved
//=======================================================================
//
// CATSmoEdgeJournalItem.h
//
//=======================================================================
//
// Usage notes: Objet de suivi pour le journal topologique
//              (attribut des edges du base mesh)
//
//=======================================================================
// 25.05.2020 : RAQ : Ajout AddAncestorFace pour meilleur suivi dans le match
// 23.03.2016 : RAQ : Ajout Set/GetInheritSobProperties + duplication pour meilleur suivi
// November,     2007 : RBD : Modif de la signature de GetAncestorEdges
//                            et de GetParentsObjects pour protéger 
//                            les données membres de la classe
// November,     2007 : RNO : Nouvelle Gestion des Attributs (Support du Multi Attribut)
// February,     2007 : RAQ : Creation
//=======================================================================
#ifndef CATSmoEdgeJournalItem_H
#define CATSmoEdgeJournalItem_H

//Classe mère
#include "CATSobAttributes.h"

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATSmoAncestorFace.h"
#include "CATSmoListVOfAncestorFace.h"
#include "CATDataType.h"
#include "CATListOfULONG32.h"
#include "CATListOfInt.h"
#include "CATListPV.h"

class CATGeometry;


CATDECLARESOBATTRIBUTE(CATSmoEdgeJournalItem, CATSmoEdgeJournalItemID)


class ExportedByCATSmoOperators CATSmoEdgeJournalItem: public CATSobAttributes
{
public:
  
  //Constructeur
  CATSmoEdgeJournalItem(CATSmoEdgeJournalItem* ipToCopy = NULL);

  //Ajout d'une cellule mère par son tag
  void AddAncestorFaceTag(const CATSmoAncestorFace& iAncestorFace);

  //Récupération des tags des cellules mères
  int GetAncestorFacesTags(CATSmoListVOfAncestorFace& oAncestorFaces) const;

  // Existe-t-il des faces mères ?
  CATBoolean HasAncestorFace() const;

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
  int GetParentsObjects(CATListPV& ioParentsObjects);

  //Indique que la cellule doit avoir les mêmes propriétés que son parent si c'est une CATSobCell
  inline void SetInheritSobProperties(const CATBoolean iMustInherit = TRUE) { m_inheritSobProperties=iMustInherit; }
  inline CATBoolean GetInheritSobProperties() const { return m_inheritSobProperties; }


protected:

  //Destructeur
  virtual ~CATSmoEdgeJournalItem();

private:


  //------- Data:
  CATSmoListVOfAncestorFace _AncestorFaces;
  CATListOfULONG32 _ExtremityVerticesTags;  
  CATListPV         _TopologicalParents;
  CATBoolean m_inheritSobProperties;
};


//Création de l'attribut
ExportedByCATSmoOperators
CATSmoEdgeJournalItem* CATSmoCreateEdgeJournalItem(CATSmoEdgeJournalItem* ipToCopy = NULL);


#endif



