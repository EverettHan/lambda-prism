/**
 * @fullReview  HCN 02:09:04
 */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//===========================================================================
//
// Version de CATCGMHashTable de petite taille
// (Cette classe ne se comporte pas comme CATCGMHasTableSmall)
//
// Sep. 02   Creation                                               HCN
//===========================================================================

#ifndef  CATCGMHashTableTiny_h
#define  CATCGMHashTableTiny_h

#include "CATCGMHashTableBase.h"

#define CATCGM_DEFAULT_HASH_TABLE_DIMENSION_TINY 3

class ExportedByCATMathematics CATCGMHashTableTiny : public CATCGMHashTableBase
{
public:

  CATCGMHashTableTiny(int iEstimatedSize = 0,
                  PFHASHKEYFUNCTION ipHashKeyFunction = NULL,
                  PFCOMPAREFUNCTION	ipCompareFunction = NULL);

  virtual ~CATCGMHashTableTiny();

protected :

  // Par defaut, un bucket est un CATULONGPTR
  CATULONGPTR  _StaticBuckets[3 * CATCGM_DEFAULT_HASH_TABLE_DIMENSION_TINY];
};
#endif
