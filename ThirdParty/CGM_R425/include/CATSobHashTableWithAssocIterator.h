//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobHashTableWithAssocIterator.h
//
//=================================================================================
//
// Usage notes: Itérateur pour les hash tables de type CATSobHashTableWithAssoc.
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobHashTableWithAssocIterator_H
#define CATSobHashTableWithAssocIterator_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Classe mère
#include "CATSobHashTableBaseIterator.h"


class ExportedByCATSobUtilities CATSobHashTableWithAssocIterator: public CATSobHashTableBaseIterator
{
public:

  //Replace l'itérateur au début
  virtual void Begin() = 0;

  //Test si l'itéraeur est à la fin
  virtual CATBoolean End() const = 0;

  //Incrémente l'itérateur
  virtual void operator++(int) = 0;

  //Récupére l'élement actuellement pointé par l'itérateur
  virtual void* GetElem() const = 0;

  //Récupére l'association de l'élement actuellement pointé par l'itérateur
  virtual void* GetAssoc() const = 0;

  //Récupére l'élement et l'association actuellement pointés par l'itérateur
  virtual void GetElemAndAssoc(void*& oElem, void*& oAssoc) const = 0;


protected:

  //Constructeur
  CATSobHashTableWithAssocIterator(const CATSobHashTableBase* iHashTableBase):CATSobHashTableBaseIterator(iHashTableBase) {}

  //Destructeur
  virtual ~CATSobHashTableWithAssocIterator() {}

private:

  //Pas d'implémentation par défaut
  CATSobHashTableWithAssocIterator(const CATSobHashTableWithAssocIterator&);
  CATSobHashTableWithAssocIterator& operator=(const CATSobHashTableWithAssocIterator&);

};

#endif

