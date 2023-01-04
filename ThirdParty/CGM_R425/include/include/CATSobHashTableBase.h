//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobHashTableBase.h
//
//=================================================================================
//
// Usage notes: Classe de base pour les hash tables.
//
//=================================================================================
// 30.01.2018 : RAQ : Optimisation perfos
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobHashTableBase_H
#define CATSobHashTableBase_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Divers
#include "CATBoolean.h"
#include "CATDataType.h"

class CATSobHashTableAtomBase;
class CATSobHashTableBaseIterator;

class ExportedByCATSobUtilities CATSobHashTableBase
{
public:

  //Constructeurs
  CATSobHashTableBase();
  CATSobHashTableBase(const unsigned int iEstimatedSize);

  //Destructeur
  virtual ~CATSobHashTableBase();

  /********************* SERVICES *********************/
  //Test d'appartenance
  virtual CATBoolean Contains(const void* iElem) const;

  //Suppression d'un élément
  virtual void Remove(const void* iElem);

  //Accès à un élément par rang
  CATBoolean GetElem(const int iIndex, void*& oElem) const;
  /****************************************************/

  //Suppression de tous les éléments
  void RemoveAll();

  //Récupération du nombre d'éléments
  int GetNbElems() const { return _NbElems; }

protected:

  /********************* A IMPLEMENTER *********************/
  //Allocation du tableau interne + initialisation du tableau à 0
  virtual CATSobHashTableAtomBase** Allocate(const int iSize) const = 0;

  //Création d'un élément pour insertion
  virtual CATSobHashTableAtomBase* CreateNewAtom(const CATSobHashTableAtomBase* iAtom) const = 0;

  //Evaluation de l'index, renvoie -1 en cas d'erreur
  virtual int EvalIndex(const void* iElem) const
  {
    CATULONGPTR PtrToInt=(CATULONGPTR) iElem;
    return (PtrToInt % GetHashTableSize());
  }
  /*********************************************************/

  //Taille de la hash table
  inline int GetHashTableSize() const { return _HashTableSize; }

  //Insertion d'un élément
  void InsertAtom(const CATSobHashTableAtomBase* iAtom);

  //Récupération d'un élément
  CATSobHashTableAtomBase* GetAtomFromElem(const void* iElem) const;

  //Récupération d'un élément et extraction de l'atom (il n'est pas détruit mais n'est plus référencé dans la liste chaînée).
  CATSobHashTableAtomBase* GetAndDetachAtomFromElem(const void* iElem);

  //Récupération d'un élément via un index avec 1<= iIndex <= Max
  CATSobHashTableAtomBase* GetAtom(const int iIndex) const;

  //Récupération du rang d'un élément, 0 si pas trouvé
  int GetIndex(const CATSobHashTableAtomBase* iAtomToFind) const;

  //Changement dynamique de la taille de la hash table
  int Resize();

private:

  //Pas d'implémentation par défaut
  CATSobHashTableBase(const CATSobHashTableBase&);
  CATSobHashTableBase& operator=(const CATSobHashTableBase&);

  friend class CATSobHashTableBaseIterator;

  //---------- Data:
  int _HashTableSize, _NbElems;
  CATSobHashTableAtomBase** _HashTableAtomPointerArray;
  CATSobHashTableAtomBase *_FirstRankAtom, *_LastRankAtom;

};

#endif

