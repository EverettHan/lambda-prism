// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATRefCounted.h
//
//===================================================================
//
// August 2009  Creation: NDO
//===================================================================
#ifndef CATRefCounted_H
#define CATRefCounted_H

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATPolyAtomicOperations.h"

// System
#include "CATDataType.h"


/**
 * This class implements a counter of references (for instances that are ref-counted).
 */
class ExportedByPolyMathContainers CATRefCounted  
{

protected:

  inline CATRefCounted ();
  virtual ~CATRefCounted ();

public:

  void AddRef ();
  void Release ();

private:

  int _RefCount;
};


inline CATRefCounted::CATRefCounted () :
  _RefCount (1)
{
}

inline void CATRefCounted::AddRef ()
{
  CATPolyAtomicOperations::Increment(&_RefCount);
}

#endif
