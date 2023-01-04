//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobHashTableBaseIterator.h
//
//=================================================================================
//
// Usage notes: Itérateur de base pour les hash tables.
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobHashTableBaseIterator_H
#define CATSobHashTableBaseIterator_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Divers
#include "CATBoolean.h"

class CATSobHashTableBase;
class CATSobHashTableAtomBase;


class ExportedByCATSobUtilities CATSobHashTableBaseIterator
{
public:

  //Gestion références
  int AddRef();
  void Release();


protected:

  //Constructeur
  CATSobHashTableBaseIterator(const CATSobHashTableBase* iHashTableBase);

  //Destructeur
  virtual ~CATSobHashTableBaseIterator();

  //Replace l'itérateur au début
  void Begin();

  //Test si l'itéraeur est à la fin
  CATBoolean End() const;

  //Incrémente l'itérateur
  virtual void operator++();  //pre increment
  virtual void operator++(int); //post increment

  //Récupére l'élement actuellement pointé par l'itérateur
  CATSobHashTableAtomBase* GetElem() const;

private:

  //Pas d'implémentation par défaut
  CATSobHashTableBaseIterator(const CATSobHashTableBaseIterator&);
  CATSobHashTableBaseIterator& operator=(const CATSobHashTableBaseIterator&);


  //---------- Data:
  int _RefCounter, _CurrentElemRank;
  const CATSobHashTableBase* _HashTableBase;
  CATSobHashTableAtomBase* _CurrentAtom;
};


#endif


