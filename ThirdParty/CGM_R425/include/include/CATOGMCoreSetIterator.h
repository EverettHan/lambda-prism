#ifndef CATOGMCoreSetIterator_H
#define CATOGMCoreSetIterator_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
 * @level Private
 * @usage U1
 */


//-------------------------------------------------------------------------------------------------
// Be Carefull about limited scope of this interface
//   high performance computation could not rely on central main memory management 
//
// Short term local transaction (change set acquisition)   
//    for extended N1 Operators on statefull modelisation
// Not to used by applied integration 
//    Dedicated to core kernel GM Component based modeler
//
// Cf  Oxxx Geomerical Modeler 
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Core Persistent Structure  
//----------------------------------------------------------------------------------------------
#include "CATOGMCore.h"
 
class CATOGMCoreSetAtoms;

//------------ ----------- ---------- 
// Helpers for iteration
//------------ ----------- ---------- 
class ExportedByCATOGMCore CATOGMCoreSetIterator
{
public :
  INLINE  CATOGMCoreSetIterator();
  INLINE  CATOGMCoreSetIterator(const CATOGMCoreSetIterator &iCopy);
  INLINE  CATOGMCoreSetIterator& operator=(const CATOGMCoreSetIterator &iCopy);
  INLINE  ~CATOGMCoreSetIterator();

private :
  int _NumBucket;
  int _Position;

  friend class CATOGMCoreSetAtoms;
};


INLINE  CATOGMCoreSetIterator::CATOGMCoreSetIterator()
: _NumBucket(0), _Position(0) {}

INLINE  CATOGMCoreSetIterator::~CATOGMCoreSetIterator()
{ _NumBucket=0; _Position=0; }

INLINE  CATOGMCoreSetIterator::CATOGMCoreSetIterator(const CATOGMCoreSetIterator &iCopy)
{ _NumBucket=iCopy._NumBucket; _Position=iCopy._Position; }

INLINE  CATOGMCoreSetIterator& CATOGMCoreSetIterator::operator = (const CATOGMCoreSetIterator &iCopy)
{ _NumBucket=iCopy._NumBucket; _Position=iCopy._Position; return *this; }

 

#endif
