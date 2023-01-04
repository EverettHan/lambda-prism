//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobHashTableIterator.h
//
//=================================================================================
//
// Usage notes: Itérateur pour les hash tables de type CATSobHashTable.
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobHashTableIterator_H
#define CATSobHashTableIterator_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Classe mère
#include "CATSobHashTableBaseIterator.h"

//Divers
#include "CATBoolean.h"


class ExportedByCATSobUtilities CATSobHashTableIterator: public CATSobHashTableBaseIterator
{
public:

  //Replace l'itérateur au début
  virtual void Begin() = 0;

  //Test si l'itéraeur est à la fin
  virtual CATBoolean End() const = 0;

  //Incrémente l'itérateur
  virtual void operator++() = 0;  //pre increment
  virtual void operator++(int) = 0; //post increment

  //Récupére l'élement actuellement pointé par l'itérateur
  virtual void* GetElem() const = 0;


protected:

  //Constructeur
  CATSobHashTableIterator(const CATSobHashTableBase* iHashTableBase):CATSobHashTableBaseIterator(iHashTableBase) {}

  //Destructeur
  virtual ~CATSobHashTableIterator() {}

private:

  //Pas d'implémentation par défaut
  CATSobHashTableIterator(const CATSobHashTableIterator&);
  CATSobHashTableIterator& operator=(const CATSobHashTableIterator&);

};

#endif

