//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATIPolySurfaceVertexIterator.h
//
// Iterate over a set of vertices of a CATIPolySurface. Usage:
//
// CATIPolySurfaceVertexIterator *it = 0;
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
//
// 2008-02-13 NDO: Added standard iterator methods (Begin, End, operator++, Get, operator*).
//                 Deprecated obsolete methods (Next ()).
//
// 2007-07-11 BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceVertexIterator_H
#define CATIPolySurfaceVertexIterator_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "PolyhedralModel.h"
#include "CATIPolyIndexIterator.h"
#include "CATBoolean.h"


/**
* Interface to a surface vertex iterator.
*/
class ExportedByPolyhedralModel CATIPolySurfaceVertexIterator : public CATIPolyIndexIterator
{
protected:

  CATIPolySurfaceVertexIterator () {}
  virtual ~CATIPolySurfaceVertexIterator ();

};

#endif // !CATIPolySurfaceVertexIterator_H
