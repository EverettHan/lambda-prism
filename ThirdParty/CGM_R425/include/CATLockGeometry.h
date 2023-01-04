#ifndef CATLockGeometry_h
#define CATLockGeometry_h
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2008
//
// Lock/Unlock tools for industrial use and debug
//
// 
//=============================================================================
// see CATAddRef
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
// History
//
// 26/11/09 NLD Creation.
//              CATLockSurface()/CATUnlockSurface()
//              CATLockCurve()/CATUnlockCurve()
// 02/12/09 NLD Documentation: adhesion aux bonnes recettes
//=============================================================================
class CATSurface;//#include <CATSurface.h>
class CATCurve;//#include <CATCurve.h>
#include <ExportedByGeometricObjects.h>
//---------------------------------------------------------------------------------------------------
// Lock geometry with
//---------------------------------------------------------------------------------------------------
extern  "C"  ExportedByGeometricObjects  
void  CATLockSurface(CATSurface*  iSurface,  void*  iReferencing=0);  
extern  "C"  ExportedByGeometricObjects  
void  CATLockCurve(CATCurve*  iCurve,  void*  iReferencing=0);  
//---------------------------------------------------------------------------------------------------
// Unlock geometry
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
extern  "C"  ExportedByGeometricObjects  
void  CATUnlockSurface(CATSurface*  iSurface,  void*  iReferencing=0);  
extern  "C"  ExportedByGeometricObjects  
void  CATUnlockCurve(CATCurve*  iCurve,  void*  iReferencing=0);  
//---------------------------------------------------------------------------------------------------
#include <LesBonnesRecettesDuPereLochard.h>
LesBonnesRecettesDuPereLochard(Unpublished021209_CATLockGeometry, "Debug fin des Lock()/Unlock() via CATLockGeometry.h");
/*
Complex unsymmetric lock/unlock call problems, for example in a scenario with errors, are difficult to solve.

Migrating locks and unlocks on curves and surfaces on signed lock with referencing objects, allow easy and quick
debugging.

for example
Curve->Lock() may be replaced by CATLockCurve(Curve, object)
and
Curve->Unlock() by CATUnlockCurve(Curve, object)
as long as the same object (for example: "this") is used for corresponding lock and unlock.

In standard mode, nothing more that a simple lock or unlock is done.
There is no impact on software behaviour.

In debug mode, the unsymmetric dynamic behaviour can easily be find.

There are 2 debug modes:
- set CGMDebugRefForLock=1
  each lock generates a CATCGMDebugReference object associating the locked object and the locking object.
  The unsymmetric call will lead to a leak on a CATCGMDebugReference object, and an exit code 77 for the test case.
  Code must be equipped, using catcxtag() breakpoint on followed object, until the CATCGMDebugReference leak appears.
  Then, if the error is not obvious, see CATCGMDebugReference debugging tools (traces and breakpoints) for further debug
  using target values.
- set CGMDebugRefForLock=2
  Same as above, but in addition, reals locks and unlocks are suppressed, as long as a first lock is active
  (first lock necessary for correct object life cycle)
  This dramatically reduces the number of breakpoint hits, and quickly leads to the error.

It is not necessary to migrate all locks, but only to follow the track given by the debugging session.
*/
#endif
