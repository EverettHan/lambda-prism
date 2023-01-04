//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyRefCounted.h
// Reference counting
//
//=============================================================================
// 2007-06-08   BPG: New.
// 2016-01-19   NDO: AddRef () and Release () methods become const.
//=============================================================================
#ifndef CATPolyRefCounted_H
#define CATPolyRefCounted_H

#include "PolyhedralModel.h"

/**
 * A class implementing reference-counting.
 */
class ExportedByPolyhedralModel CATPolyRefCounted
{

protected:

  inline CATPolyRefCounted ();
  virtual ~CATPolyRefCounted ();

public:

  /**
   * Increments the reference count of the instance.
   */
  void AddRef () const;

  /**
   * Decrements the reference count of the instance.  When the counter reaches 0, the instance is deleted.
   */
  void Release () const;

  /**
   * Returns the number of references made to this instance.
   * @return 
   *   Return the number of references made to the instance.
   */
  unsigned int GetNbReferences () const;

private:
  mutable unsigned int _Ref;
};


inline CATPolyRefCounted::CATPolyRefCounted ():
  _Ref (1)
{
}

#endif // !CATPolyRefCounted_H
