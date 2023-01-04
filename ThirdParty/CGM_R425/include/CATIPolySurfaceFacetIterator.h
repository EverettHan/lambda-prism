//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATIPolySurfaceFacetIterator.h
//
// Iterate over a set of vertices of a CATIPolySurface. Usage:
//
// CATIPolySurfaceFacetIterator *it = 0;
// if (SUCCEDED(Surface.GetFacetIterator(it) && it))
// {
//   for (it->Begin (); !it->End(); ++(*it))
//   {
//     int f = it->Get();  // Also: "int f = **it;"
//   }
//   it->Release();
//   it = 0;
// }
//
//=============================================================================
//
// 2008-02-13 NDO: Added standard iterator methods (Begin, End, operator++, Get, operator*).
//                 Deprecated obsolete methods (Next ()).
//
// 2007-10-22 BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceFacetIterator_H
#define CATIPolySurfaceFacetIterator_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"


/**
* Interface to a surface facet iterator.
*/
class ExportedByPolyhedralModel CATIPolySurfaceFacetIterator : public CATPolyRefCounted
{
protected:

  CATIPolySurfaceFacetIterator ();
  virtual ~CATIPolySurfaceFacetIterator ();

public:

  /**
  * Returns a deep copy of the iterator. It is unimplemented and returns NULL by default.
  * @return
  *   A pointer to the copy of this iterator, or NULL if the pointer implementation does not support cloning.
  */
  virtual CATIPolySurfaceFacetIterator* Clone () const;

public:

  /**
   * Set the iterator to the beginning.
   */
  virtual CATIPolySurfaceFacetIterator& Begin () = 0;

  /**
   * Return TRUE if the iterator has reached the end and FALSE otherwise.
   * @return
   *   A boolean.
   */
  virtual CATBoolean End () const = 0;

public:

  /**
   * Increment the iterator to the next valid element.
   */
  virtual CATIPolySurfaceFacetIterator& operator++ () = 0;

public:

  /**
   * Return the index of the current facet.
   * @return
   *   An integer index.
   */
  virtual int Get () const = 0;

  /**
   * Return the index of the current facet.
   * @return
   *   An integer index.
   */
  virtual int operator* () = 0;

  /**
   * Return the index of the current facet.
   * @return
   *   An integer index.
   */
  virtual int operator-> () = 0;

};

#endif // !CATIPolySurfaceFacetIterator_H
