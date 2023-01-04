
// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyIntIterator.h
// Header definition of CATIPolyIntIterator
//
//===================================================================
//
// Usage notes:
//
// CATIPolyIntIterator PartitionIterator;
// for (PartitionIterator.Begin (); !PartitionIterator.End(); ++PartitionIterator)
// {
//   int element = *PartitionIterator;
//   ...
// }
//
//===================================================================
//
// May 2008 Creation: zfi
//===================================================================


#ifndef CATIPolyIntIterator_H
#define CATIPolyIntIterator_H

#include "PolyMathContainers.h"
#include "CATBoolean.h"

class CATIPolyIntIterator;

class ExportedByPolyMathContainers CATIPolyIntIterator
{
public:
  CATIPolyIntIterator();
  virtual ~CATIPolyIntIterator();

public:
  virtual CATIPolyIntIterator& Begin () = 0;
  virtual CATBoolean End () const = 0;

public:

  virtual CATIPolyIntIterator& operator++ () = 0;

public:
  virtual int Get () const = 0;
  virtual int operator* () = 0;

private:
  CATIPolyIntIterator(CATIPolyIntIterator &);
  CATIPolyIntIterator &operator=(CATIPolyIntIterator&);
};


#endif
