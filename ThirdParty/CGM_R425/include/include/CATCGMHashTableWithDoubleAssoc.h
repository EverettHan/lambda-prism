/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//===========================================================================
//
// Implementation generique d'une hash table avec stockage
// de deux donnees associees (avec gestion des adresses > 2 Go)
//  
//
//   /05/02 HCN Creation
// 21/01/10 NLD Definition de CATCGMHashTableWithDoubleAssoc_SizeByBucket qui remplace la valeur 5
//              et         de CATCGMHashTableWithDoubleAssoc_BucketUserSize
//              Ajout methode Next()
//===========================================================================

#ifndef  CATCGMHashTableWithDoubleAssoc_h
#define  CATCGMHashTableWithDoubleAssoc_h

#include "CATCGMHashTable.h"
#include "CATMathematics.h"
#include "CATCGMVirtual.h"

class ExportedByCATMathematics CATCGMHashTableWithDoubleAssoc  : public CATCGMVirtual
{
public:

  CATCGMHashTableWithDoubleAssoc(int iEstimatedSize = 0,
                                 PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                                 PFCOMPAREFUNCTION   ipCompareFunction = NULL);

  virtual ~CATCGMHashTableWithDoubleAssoc();

  int          Insert(void* ipElem, void* ipAssoc1, void* ipAssoc2);
  int          LocateItemAssoc1ReturnBoolean(void* ipElem, void* ipAssoc1, void** oppAssoc2) const;
  int          Size() const;

  // Methode de scan des enregistrements a partir du premier
  //
  // Usage:
  //   CATULONGPTR* Current = NULL;
  //   do
  //     {
  //      HashTable->Next(Current,
  //                      Elem, Assoc1, Assoc2);
  //      if (Current)
  //         Management(elem, Assoc1, Assoc2);
  //     }
  //   while (Current);
  void Next(CATULONGPTR*& ioCurrent,
            void*& oElem, void*& oAssoc1, void*& oAssoc2) ;

protected:

  PFHASHKEYFUNCTION   _pHashKeyFunction;
  PFCOMPAREFUNCTION   _pCompareFunction;

  int          _NbAllocatedBuckets; // Dimension of the hashtab (maximum number of buckets to be stored in the Hashtable)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // Definition des tailles
  //   CATCGMHashTableWithDoubleAssoc_BucketUserSize est la taille des donnees utilisateur d'un bucket soit 3
  //   CATCGMHashTableWithDoubleAssoc_SizeByBucket   est la taille a allouer pour chaque bucket
  //                                                 soit 
  //                                                        1 (pointeur vers la sous-liste en tete d'allocation)
  //                                                      + 3 (le bucket)
  //                                                      + 1 (pour pointeur vers bucket suivant apres le bucket)
  #define CATCGMHashTableWithDoubleAssoc_BucketUserSize 3
  // #define CATCGMHashTableWithDoubleAssoc_SizeByBucket 5
  #define CATCGMHashTableWithDoubleAssoc_SizeByBucket (2 + CATCGMHashTableWithDoubleAssoc_BucketUserSize)
  // Par defaut, un bucket est un CATULONGPTR
  // CATULONGPTR  _StaticBuckets[3 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];
  //CATULONGPTR  _StaticBuckets[5 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];
  CATULONGPTR  _StaticBuckets[CATCGMHashTableWithDoubleAssoc_SizeByBucket * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];

  int          _NbFreeBuckets;      // Number of free buckets 
  int          _NbStoredElems;      // Number of stored elements in the hashtable

  // Pour debug
  unsigned int        _Tag;
  static unsigned int _Tag_Counter;

  void ReAllocate();
};


#endif

