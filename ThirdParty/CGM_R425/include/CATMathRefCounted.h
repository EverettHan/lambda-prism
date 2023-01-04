// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMathRefCounted.h
//
//===================================================================
//
// August 2009  Creation: NDO
//===================================================================
#ifndef CATMathRefCounted_H
#define CATMathRefCounted_H

#include "CATMathematics.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathAtomicOperations.h"

// System
#include "CATDataType.h"


/**
 * This class implements a counter of references (for instances that are ref-counted).
 */
class ExportedByCATMathematics CATMathRefCounted  
{

protected:

  inline CATMathRefCounted ();
  virtual ~CATMathRefCounted ();

public:

  void AddRef () const;
  void Release () const;

private:

  int _RefCount;
};


inline CATMathRefCounted::CATMathRefCounted () :
  _RefCount (1)
{
}

inline void CATMathRefCounted::AddRef () const
{
  CATMathAtomicOperations::Increment((int*)&_RefCount);
}

#endif
