//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobHashTable.h
//
//=================================================================================
//
// Usage notes: Hash table de pointeurs.
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobHashTable_H
#define CATSobHashTable_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Hash table & cie
#include "CATSobHashTableBase.h"

class CATSobHashTableIterator;


class ExportedByCATSobUtilities CATSobHashTable: public CATSobHashTableBase
{
public:

  //Constructeurs
  CATSobHashTable();
  CATSobHashTable(const unsigned int iEstimatedSize);

  //Destructeur
  virtual ~CATSobHashTable();

  /********************* SERVICES *********************/
  //Insertion d'un élément
  void Insert(const void* iElem);

  //Test d'appartenance
  CATBoolean Contains(const void* iElem) const;

  //Suppression d'un élément
  void Remove(const void* iElem);

  //Accès à un élément par rang
  CATBoolean GetElem(const int iIndex, void*& oElem) const;

  //Récupération du rang d'un élément, 0 si pas trouvé
  int GetIndex(const void* iElem) const;
  /****************************************************/

  //Création d'un itérateur, il doit être détruit par l'appelant.
  CATSobHashTableIterator* GetIterator() const;


protected:

  /********************* A IMPLEMENTER *********************/
  //Allocation du tableau interne
  CATSobHashTableAtomBase** Allocate(const int iSize) const;

  //Création d'un élément pour insertion
  CATSobHashTableAtomBase* CreateNewAtom(const CATSobHashTableAtomBase* iAtom) const;
  /*********************************************************/

private:

  //Pas d'implémentation par défaut
  CATSobHashTable(const CATSobHashTable&);
  CATSobHashTable& operator=(const CATSobHashTable&);
 
};


#endif

