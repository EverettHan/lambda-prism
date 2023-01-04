// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveIterator.h
//
//===================================================================
//
// Iterate through CATIPolyCurve's. 
// Example:
//
// CATIPolyCurveIterator* it = 0;
// if (SUCCEDED (MyObject.GetCurveIterator (it) && it))
// {
//   for (it->Begin (); !it->End (); ++(*it))
//   {
//     CATIPolyCurve* curve = it->Get ();   
//     //OR: CATIPolyCurve* curve = **it;
//     if (surface)
//     {
//     }
//   }
//   delete it;
//   it = 0;
// }
//
//=============================================================================
// 2009-03-13   JXO: Friday the 13th 's new iterator
//=============================================================================
#ifndef CATIPolyCurveIterator_H
#define CATIPolyCurveIterator_H

#include "PolyhedralModel.h"

#include "CATPolyDeprecated.h"
#include "CATBoolean.h"


class CATIPolyCurve;


class ExportedByPolyhedralModel CATIPolyCurveIterator
{

public:

  virtual ~CATIPolyCurveIterator () {}

public:

  // Sets the iterator to the beginning.
  virtual CATIPolyCurveIterator& Begin () = 0;

  // Returns TRUE if the iterator has reached the end and FALSE otherwise.
  virtual CATBoolean End () const = 0;

public:

  // Increments the iterator to the next valid element.
  virtual CATIPolyCurveIterator& operator++ () = 0;

public:

  /* Release the curve returned by the iterator. No need to do an AddRef (). */
  virtual CATIPolyCurve* GetAndRelease ();

/**
 * @deprecated R419 GetAndRelease
 * (The comment is wrong, you need to do a Release.)
 */
 /* Don't release the curve returned by the iterator unless you do an AddRef () explicitely. */
  POLY_DEPRECATED("Deprecated, use GetAndRelease instead.", virtual CATIPolyCurve* Get (){return DummyGet();});
  POLY_DEPRECATED("Deprecated, use GetAndRelease instead.", virtual CATIPolyCurve* operator* (){return DummyGet();});


protected:
  virtual CATIPolyCurve * DummyGet() = 0;

};

#endif // !CATIPolyCurveIterator_H
