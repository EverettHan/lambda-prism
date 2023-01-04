//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobHashTableWithAssoc.h
//
//=================================================================================
//
// Usage notes: Hash table de pointeurs + pointeur associé.
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobHashTableWithAssoc_H
#define CATSobHashTableWithAssoc_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Classe mère
#include "CATSobHashTableBase.h"


class CATSobHashTableWithAssocAtom;
class CATSobHashTableWithAssocIterator;


class ExportedByCATSobUtilities CATSobHashTableWithAssoc: public CATSobHashTableBase
{
public:

  //Constructeurs
  CATSobHashTableWithAssoc();
  CATSobHashTableWithAssoc(const unsigned int iEstimatedSize);

  //Destructeur
  virtual ~CATSobHashTableWithAssoc();

  /********************* SERVICES *********************/
  //Insertion d'un élément et de sa donnée associée
  void Insert(const void* iElem, const void* iAssoc);
  
  //Récupération d'une donnée associée à un élément.
  //Renvoie TRUE si l'élément a été trouvé, FALSE sinon.
  CATBoolean GetAssoc(const void* iElem, void*& oAssoc) const;

  //Test d'appartenance
  CATBoolean Contains(const void* iElem) const;

  //Modification de l'association d'un élément
  CATBoolean ModifyAssoc(const void* iElem, const void* iNewAssoc);

  //Suppression d'un élément
  void Remove(const void* iElem);

  //Récupération d'une donnée associée à un élément et suppression de l'entrée dans la hash table
  //Renvoie TRUE si l'élément a été trouvé, FALSE sinon.
  CATBoolean GetAssocAndRemove(const void* iElem, void*& oAssoc);

  //Accès à un élément par rang
  CATBoolean GetElem(const int iIndex, void*& oElem) const;
  CATBoolean GetAssoc(const int iIndex, void*& oAssoc) const;
  CATBoolean GetElemAndAssoc(const int iIndex, void*& oElem, void*& oAssoc) const;

  //Récupération du rang d'un élément, 0 si pas trouvé
  int GetIndex(const void* iElem, const void* iAssoc) const;
  /****************************************************/

  //Création d'un itérateur, il doit être détruit par l'appelant.
  CATSobHashTableWithAssocIterator* GetIterator() const;


protected:

  /********************* A IMPLEMENTER *********************/
  //Allocation du tableau interne
  virtual CATSobHashTableAtomBase** Allocate(const int iSize) const;

  //Création d'un élément pour insertion
  virtual CATSobHashTableAtomBase* CreateNewAtom(const CATSobHashTableAtomBase* iAtom) const;
  /*********************************************************/

private:

  //Pas d'implémentation par défaut
  CATSobHashTableWithAssoc(const CATSobHashTableWithAssoc&);
  CATSobHashTableWithAssoc& operator=(const CATSobHashTableWithAssoc&);

};

#endif


