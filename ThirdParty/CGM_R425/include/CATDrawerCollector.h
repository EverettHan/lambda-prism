#ifndef CATDrawerCollector_h
#define CATDrawerCollector_h
/*-*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//==========================================================================

#include "HashTableAssocHashTable.h"

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class CATCGMHashTable;

class ExportedByCATTopologicalObjects CATDrawerCollector : public HashTableAssocHashTable
{

  // CATDrawerCollector represente une HashTable avec Assoc dont l'elements associe a chaque element de la table est une hash table.

public :
 
  CATDrawerCollector(int iExpectedSize = 0);
  virtual ~CATDrawerCollector();

  //Les methodes suivantes ne sont que des alias des methodes de HashTableAssocHashTable
  INLINE void CreateDrawer(void * iElem, int iDrawerSize = 0) {this->AddLink(iElem, NULL, iDrawerSize);}
  INLINE void Insert(void * iElem, void * iAssoc) {this->AddLink(iElem, iAssoc);}

  //Methodes specifiques de CATDrawerCollector
  void SetDrawer(void * iElem, CATCGMHashTable * iDrawer);
  CATCGMHashTable * GetSharedElements(int iExpectedNumberOfSharedElements = 0); // Retourne une HT des elements qui sont communs a plusieurs tiroirs.
  CATCGMHashTable * FindAllHandles( void * iElem );

};
#endif
