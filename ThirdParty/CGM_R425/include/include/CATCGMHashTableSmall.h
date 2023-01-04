/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//===========================================================================
//
// Implementation generique d'une hash table de petite taille
// SANS check sur l'unicite du stockage (avec gestion des adresses > 2 Go)
//
// Utilisez CATCGMHashTableTiny pour une hash table de petite taille avec les
// memes fonctionnalites que CATCGMHashTable.
//
// Avr. 2002   Creation                            HCN
//
//===========================================================================

#ifndef  CATCGMHashTableSmall_h
#define  CATCGMHashTableSmall_h

#include "CATCGMHashTable.h"
#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

#define CATCGM_DEFAULT_HASH_TABLE_DIMENSION_SMALL 4

class ExportedByCATMathematics CATCGMHashTableSmall  : public CATCGMVirtual
{
public:

  CATCGMHashTableSmall(int iEstimatedSize = 0,
                       PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                       PFCOMPAREFUNCTION	ipCompareFunction = NULL);

  virtual ~CATCGMHashTableSmall();

  int           Insert(void* ipElem);

  //void*         Locate(void* ipElem) const;
  int           LocateReturnPos(void* ipElem) const;

  //void*         KeyLocate(unsigned int iKey) const;

  //INLINE void*  Get(int iPos) const;
  INLINE void*  operator[](int iPos) const;

  //void*         Next(void* ipElem) const;

  //int           Remove(void* ipElem);
  int           RemoveReturnPos(void* ipElem);

  //void          RemoveAll();

  int           Size() const;

  //void          PrintStats() const;

protected :

  PFHASHKEYFUNCTION	_pHashKeyFunction;
  PFCOMPAREFUNCTION	_pCompareFunction;

  int          _NbAllocatedBuckets; // Dimension of the hashtab (maximum number of buckets to be stored in the Hashtable)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // CATULONGPTR  _StaticBuckets[3 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION];
  CATULONGPTR  _StaticBuckets[CATCGM_DEFAULT_HASH_TABLE_DIMENSION_SMALL];

  int          _NbFreeBuckets;      // Number of free buckets 
  int          _NbStoredElems;      // Number of stored elements in the hashtable

  // Pour debug
  unsigned int        _Tag;
  static unsigned int _Tag_Counter;

  void ReAllocate();
};


//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
/*INLINE void* CATCGMHashTableSmall::Get(int iPos) const
{
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  return (void *) *(_pAllocatedBuckets + _NbAllocatedBuckets + 2 * iPos);
};*/

//-----------------------------------------------------------------------------
// operateur []
//-----------------------------------------------------------------------------
INLINE void* CATCGMHashTableSmall::operator[](int iPos) const
{  
  if (iPos < 0 || iPos >= _NbStoredElems)
    return NULL;
  else
  if (_NbAllocatedBuckets == CATCGM_DEFAULT_HASH_TABLE_DIMENSION_SMALL)
    return (void*)*(_pAllocatedBuckets + iPos);
  else
    return (void *)*(_pAllocatedBuckets + _NbAllocatedBuckets + 2 * iPos);
}

#endif
