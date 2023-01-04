// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntInt.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// jun 2004 Creation: dhp
//===================================================================
#ifndef CATMapOfIntInt_h
#define CATMapOfIntInt_h

#include "PolyMathContainers.h"
#include "CATBoolean.h"

#include "CATHashTable.h"
#include "CATListOfInt.h"
#include "CATListPV.h"

class ExportedByPolyMathContainers CATMapOfIntInt
{

public :

  CATMapOfIntInt (int size);
  ~CATMapOfIntInt (void);

  CATBoolean Insert (const int index0,
    const int index1,
    void * value);

  CATBoolean Locate (const int index0,
    const int index1,
    void *& value) const;

  CATBoolean Locate (const int index0,
    const int index1) const;

  CATBoolean Remove (const int index0,
    const int index1,
    void *& value);

  CATBoolean Remove (const int index0,
    const int index1);

  CATBoolean GetValues (CATListOfInt & indices0,
    CATListOfInt & indices1,
    CATListPV & values) const;

  CATBoolean RemoveAll (void);

  CATBoolean RemoveAll (CATListPV & values);

private :

  void Clear (void);

  CATHashTable _hashTable;

};

#endif
