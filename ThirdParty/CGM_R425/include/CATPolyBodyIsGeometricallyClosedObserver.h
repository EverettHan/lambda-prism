//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyIsGeometricallyClosedObserver.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2014-11-14   E3H: New
//===================================================================
#ifndef CATPolyBodyIsGeometricallyClosedObserver_H
#define CATPolyBodyIsGeometricallyClosedObserver_H

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATPolyBodyIsGeometricallyClosed.h"

/**
 * Observer class to CATPolyBodyIsGeometricallyClosedOper.
 */
class ExportedByPolyBodyTools CATPolyBodyIsGeometricallyClosedObserver
{
public:

  virtual ~CATPolyBodyIsGeometricallyClosedObserver ();

public:
  ///////////////////////
  //ReactTo methods
  virtual void ReactToInputBody (const CATPolyBody& iPolyBody) = 0;
  virtual void ReactToCompareFunction (CATBoolean iCompareFunction) = 0;
  virtual void ReactToNbOpenBars (int* NbOpenBars) = 0;
  virtual void ReactToOperResult (HRESULT OperResult) = 0;

public:
  virtual void AfterConstructor () = 0;
  virtual void BeforeRun () = 0;
  virtual void AfterRun () = 0;
  virtual void BeforeDestructor () = 0;
  
};

#endif
