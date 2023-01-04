//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyIsClosedObserver.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// 2014-11-14   E3H: New
//===================================================================
#ifndef CATPolyBodyIsClosedObserver_H
#define CATPolyBodyIsClosedObserver_H

#include "CATPolyBodyIsClosed.h"
#include "CATErrorDef.h"


/**
 * Observer class to CATPolyBodyIsClosedOper.
 */
class ExportedByPolyBodyTools CATPolyBodyIsClosedObserver
{

public:

  virtual ~CATPolyBodyIsClosedObserver ();

public:

  ///////////////////////
  //ReactTo methods
  virtual void ReactToInputBody (const CATPolyBody& iPolyBody) = 0;
  virtual void ReactToNbOpenBars (int* NbOpenBars) = 0;
  virtual void ReactToOperResult (HRESULT OperResult) = 0;

public:
  virtual void AfterConstructor () = 0;
  virtual void BeforeRun () = 0;
  virtual void AfterRun () = 0;
  virtual void BeforeDestructor () = 0;
  
};

#endif
