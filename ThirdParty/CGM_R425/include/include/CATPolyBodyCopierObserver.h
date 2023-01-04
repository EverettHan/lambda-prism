// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyCopierObserver.h
//
//===================================================================
// 
//===================================================================
#ifndef CATPolyBodyCopierObserver_H
#define CATPolyBodyCopierObserver_H

#include "PolyBodyTools.h"
#include "CATPolyBodyCopier.h"
#include "CATIPolyMesh.h"
#include "CATErrorDef.h"
/**
 * Observer class to CATPolyBodyCopierOper.
 */
class ExportedByPolyBodyTools CATPolyBodyCopierObserver
{

public:

  virtual ~CATPolyBodyCopierObserver ();

public:

  ///////////////////////
  //ReactTo methods
  virtual void ReactToSetInputBody (const CATPolyBody &iBody) = 0;
  virtual void ReactToSetOutputBody (CATPolyBody &iBody) = 0;

  virtual void ReactToMeshImplType (int iMeshImplementation) = 0;
  //virtual void ReactToOutputTransfo (CATMathTransformation & iTransfo) = 0;

public:
  virtual void AfterConstructor () = 0;
  virtual void BeforeRun () = 0;
  virtual void AfterRun () = 0;
  virtual void BeforeDestructor () = 0;
  
};

#endif
