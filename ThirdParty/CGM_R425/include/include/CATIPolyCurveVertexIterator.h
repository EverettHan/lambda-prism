//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATIPolyCurveVertexIterator.h
//
// Iterate over a set of vertices of a CATIPolyCurve. 
// Return the vertices in the sequential order that defines the CATIPolyCurve.
//
// CATIPolyCurveVertexIterator *it = 0;
// if (SUCCEDED(Curve.GetVertexIterator(it) && it))
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
// 2009-01-15 NDO: New.
//=============================================================================
#ifndef CATIPolyCurveVertexIterator_H
#define CATIPolyCurveVertexIterator_H

#include "PolyhedralModel.h"
#include "CATIPolyIndexIterator.h"


/**
* Interface to a curve vertex iterator.
* 
* It iterates through the vertices of a curve.  This iterator returns the vertices in the sequential order along
* the curve.
*/
class ExportedByPolyhedralModel CATIPolyCurveVertexIterator : public CATIPolyIndexIterator
{

protected:

  CATIPolyCurveVertexIterator() {}
  virtual ~CATIPolyCurveVertexIterator() {}

};

#endif // !CATIPolyCurveVertexIterator_H
