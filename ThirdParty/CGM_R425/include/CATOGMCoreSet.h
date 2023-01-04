#ifndef CATOGMCoreSet_H
#define CATOGMCoreSet_H
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
//    Change management as elementary set of todo item 
//----------------------------------------------------------------------------------------------
#include "CATOGMCore.h"
#include "CATOGMCoreSetIterator.h"
#include "CATBoolean.h"
 


//------------ ----------- ---------- 
//    Set is a set of Atoms 
//------------ ----------- ---------- 

class ExportedByCATOGMCore CATOGMCoreSet
{
public :
 
 
  //------------ ----------- ---------- 
  // LifeCycle
  //------------ ----------- ---------- 
 
  static CATOGMCoreSet *Create(const CATULONG64 iStamp);

 
  static CATOGMCoreSet *Duplicate(CATOGMCoreSet              * iOriginalSet,
                                  const CATOGMCORE_DUPLICATE   iDuplicateManagement,
                                  const CATOGMCORE_INTENTSTATE iFilterTodo = 
                                    CATOGMCORE_INTENTSTATE_TO_REMAIN 
                                  | CATOGMCORE_INTENTSTATE_TO_CREATE 
                                  | CATOGMCORE_INTENTSTATE_TO_UPDATE
                                  | CATOGMCORE_INTENTSTATE_TO_DELETE );
   

  /** LifeCycle protection and management */
  INLINE void DecreaseCounter();

  /** LifeCycle protection and management  */
  INLINE void IncreaseCounter();

  /** GetStamp  */
  INLINE CATULONG64 GetStamp() const;

  //------------ ----------- ---------- 
  // Single Set Management
  //------------ ----------- ---------- 

  /* Insert */
  virtual CATOGMCoreAtom*  Insert(CATOGMCoreAtom* ipCoreAtom) = 0;


  /** Next */
  virtual CATOGMCoreAtom* Next(CATOGMCoreSetIterator & ioIterator) = 0;

  /** Search */
  virtual CATOGMCoreAtom* Search(CATOGMCoreAtom* iAtom) = 0;
 
  
  //------------ ----------- ---------- 
  // Statistics
  //------------ ----------- ---------- 
  virtual void Statistics( int & oAllSize, int * oRemain = 0, int * oCreate = 0, int * oUpdate  = 0, int * oDelete  = 0 )  = 0;
 

  //------------ ----------- ----------  ----------- ---------- 
  // For Differential Management ; About contents as Atoms 
  //------------ ----------- ----------  ----------- ---------- 
  //
  //    +------------+-------------+--------------------------+
  //    | Next\Prev  |   NotFound  |   Found                  |
  //    +------------+-------------+--------------------------+
  //    | NotFound   |             |   ToDelete               |
  //    +------------+-------------+--------------------------+
  //    | Found      |  ToCreate   |   Remain or Update *     |
  //    +------------+-------------+--------------------------+
  //
  //  NothingToDo*, option iWithDataComparison
  //
  static CATOGMCoreSet *CreateDifferential(const CATULONG64  iNewStamp,
                                           CATOGMCoreSet *iNext,
                                           CATOGMCoreSet *iPrevious,
                                           CATBoolean     iWithDataComparison = FALSE,
                                           CATBoolean     iWithKept = FALSE);
 

protected :

  
  INLINE CATOGMCoreSet(const CATULONG64 iStamp);

  virtual ~CATOGMCoreSet();
 

private :

  // Counter
  unsigned int    _Counter;

  CATULONG64      _Stamp;

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATOGMCoreSet(const CATOGMCoreSet &iCopy);
  CATOGMCoreSet& operator=(const CATOGMCoreSet &iCopy);
};


INLINE CATOGMCoreSet::CATOGMCoreSet(const CATULONG64 iStamp) : _Counter(0), _Stamp(iStamp) {}

  /** GetStamp  */
INLINE CATULONG64 CATOGMCoreSet::GetStamp() const { return _Stamp; }

INLINE void CATOGMCoreSet::IncreaseCounter()
{ ++_Counter; }

INLINE void CATOGMCoreSet::DecreaseCounter()
{ if (( 0 == _Counter ) || (0 == --_Counter)) delete this; }


#endif
