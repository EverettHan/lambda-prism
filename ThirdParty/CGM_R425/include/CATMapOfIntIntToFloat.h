// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntIntToFloat.h
//
//===================================================================
//
// Usage notes: 
//
//===================================================================
//
// Sep 2008  Creation: ZFI
//===================================================================

#ifndef CATMapOfIntIntToFloat_h
#define CATMapOfIntIntToFloat_h

#include "PolyMathContainers.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMapOfIntToPtr.h"


class ExportedByPolyMathContainers CATMapOfIntIntToFloat
{

public:

  CATMapOfIntIntToFloat ();
  ~CATMapOfIntIntToFloat ();

public:

  HRESULT Insert (const int key1, const int key2, const float value);

  HRESULT Update (const int key1, const int key2, const float value);

  CATBoolean Locate (const int key1, const int key2, float& value) const;

//public:
//  HRESULT Remove (const int key1, const int key2);
//  HRESULT Remove (const int key2);
//  HRESULT RemoveAll ();

private:
  CATMapOfIntToPtr _MapToFinalMap;

};

#endif
