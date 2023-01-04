// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATIPolyIndexIterator.h
//
// Iterate over a set of indices. Usage:
//
// CATIPolyIndexIterator *it = 0;
// if (SUCCEDED(Surface.GetVertexIterator(it) && it))
// {
//   for (it->Begin (); !it->End (); ++(*it))
//   {
//     int v = it->Get();   // Also: "int v = **it;"
//   }
//   it->Release();
//   it = 0;
// }
//
//=============================================================================
// 2010-05-20 NDO: CAA
//=============================================================================
#ifndef CATIPolyIndexIterator_H
#define CATIPolyIndexIterator_H

class CATIPolyIndexIterator;

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"


/**
* Interface to an integer index iterator.
*/
class ExportedByPolyhedralModel CATIPolyIndexIterator : public CATPolyRefCounted
{
protected:

  CATIPolyIndexIterator () {}
  virtual ~CATIPolyIndexIterator ();

public:

  /**
   * Sets the iterator to the beginning.
   */
  virtual CATIPolyIndexIterator &Begin() = 0;

  /**
   * Returns <tt>TRUE</tt> if the iterator has reached the end and <tt>FALSE</tt> otherwise.
   */
  virtual CATBoolean End() const = 0;

public:

  /**
   * Returns the current index.
   * @return
   *   An integer index.
   */
  virtual int Get() const = 0;

  /**
   * Returns the current index.
   * @return
   *   An integer index.
   */
  virtual int operator*() = 0;

public:

  /** 
   * Increments the iterator to the next valid index.
   */
  virtual CATIPolyIndexIterator &operator++() = 0;

};

#endif // !CATIPolyVertexIterator_H
