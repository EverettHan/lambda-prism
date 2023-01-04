#ifndef CATGMIfWePurgeNonPersistent_H
#define CATGMIfWePurgeNonPersistent_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "CATDataType.h"

// Noeud d un empilage
typedef struct sCATIfWePurgeNonPersistent
{
  CATULONG64             _ExpectedNumberOfPurged;
  CATULONG64             _EffectiveNumberOfPurged;
  CATLONG64              _DifferentialWorkingSet;

  INLINE sCATIfWePurgeNonPersistent()  
    : _ExpectedNumberOfPurged(0)
    , _EffectiveNumberOfPurged(0)
    , _DifferentialWorkingSet(0)
  {};

} 
CATGMIfWePurgeNonPersistent;
 


typedef void (*CATCGAMeasureUserExit)(const int    iBeforeOneShotAfter,  const char * iKindOfOperation,  const char * iDataDomain,  void * iObject) ;


 
#endif
