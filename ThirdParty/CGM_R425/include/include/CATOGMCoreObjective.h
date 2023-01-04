#ifndef CATOGMCoreObjective_H
#define CATOGMCoreObjective_H
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
#include "CATThrowForNullPointer.h"
#include "ExportedByCATOGMCore.h"
 
#ifndef CATCGMStreamVersion
#define CATCGMStreamVersion int
#endif

#ifndef CatCGMStream_UnknownVersion
#define CatCGMStream_UnknownVersion +999
#endif

//------------ ----------- ---------- 
//  CATOGMCoreObjective
//------------ ----------- ---------- 
class ExportedByCATOGMCore CATOGMCoreObjective 
{
public :

  INLINE CATOGMCoreObjective(const CATOGMCORE_OBJECTIVE iTarget);

  INLINE CATOGMCoreObjective(const CATOGMCORE_OBJECTIVE iTarget, const CATCGMStreamVersion iPreviousMajorVersion);

  INLINE ~CATOGMCoreObjective();

  /** CompareValue 
    * 0:equal 1:distinct */
  INLINE CATOGMCORE_OBJECTIVE  GetObjective() const;

  /** CATOGMCORE_OBJECTIVE_MaxMlcVersionOfInstances  management */

  /** GetCurrentMaxVersion */
  INLINE CATCGMStreamVersion  GetCurrentMaxVersion() const;

  /** SetCurrentMaxVersion */
  INLINE void  SetCurrentMaxVersion(const CATCGMStreamVersion iTargetVersion);
 
  /** Copy constructor and constructor by copy */
  INLINE CATOGMCoreObjective(const CATOGMCoreObjective &iCopy);
  INLINE CATOGMCoreObjective& operator=(const CATOGMCoreObjective &iCopy);

protected :
  CATOGMCORE_OBJECTIVE  _Target;
  CATCGMStreamVersion   _MaxMlcVersionOfInstances;

};


INLINE  CATOGMCoreObjective::CATOGMCoreObjective(const CATOGMCORE_OBJECTIVE iTarget)
: _Target(iTarget), _MaxMlcVersionOfInstances(CatCGMStream_UnknownVersion)
{ if (_Target == CATOGMCORE_OBJECTIVE_MaxMlcVersionOfInstances) CATThrowForNullPointer()  ;}

INLINE  CATOGMCoreObjective::CATOGMCoreObjective(const CATOGMCORE_OBJECTIVE iTarget, const CATCGMStreamVersion iPreviousMajorVersion)
: _Target(iTarget), _MaxMlcVersionOfInstances(iPreviousMajorVersion)
{ }


INLINE CATOGMCORE_OBJECTIVE  CATOGMCoreObjective::GetObjective() const
{ return _Target; }


/** GetCurrentMaxVersion */
INLINE CATCGMStreamVersion  CATOGMCoreObjective::GetCurrentMaxVersion() const 
{ return _MaxMlcVersionOfInstances; }

/** SetCurrentMaxVersion */
INLINE void  CATOGMCoreObjective::SetCurrentMaxVersion(const CATCGMStreamVersion iTargetVersion) 
{ _MaxMlcVersionOfInstances = iTargetVersion; }


INLINE  CATOGMCoreObjective::~CATOGMCoreObjective() {} 




/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATOGMCoreObjective& CATOGMCoreObjective::operator=(const CATOGMCoreObjective &iOther)
{
  if (&iOther == this)  return *this;
  _Target                   =  iOther._Target;
  _MaxMlcVersionOfInstances =  iOther._MaxMlcVersionOfInstances;
  return *this;
}
 
 
CATOGMCoreObjective::CATOGMCoreObjective(const CATOGMCoreObjective &iOther) 
{
  _Target                   =  iOther._Target;
  _MaxMlcVersionOfInstances =  iOther._MaxMlcVersionOfInstances;
}
 
 

#endif
