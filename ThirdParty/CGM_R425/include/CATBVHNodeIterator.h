// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHNodeIterator
//
//===================================================================
// 2009-04-28   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//===================================================================
#ifndef CATBVHNodeIterator_H
#define CATBVHNodeIterator_H

#include "BVHObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATBVHNode;


/**
 * Interface defined as a purely virtual and abstract class.
 * This interface defines an iterator through a set of CATBVHNode's.
 */
class ExportedByBVHObjects CATBVHNodeIterator
{

public:

  virtual ~CATBVHNodeIterator () {}

public:

  // Set the iterator to the beginning.
  virtual CATBVHNodeIterator& Begin () = 0;

  // Return TRUE if the iterator has reached the end and FALSE otherwise.
  virtual CATBoolean End () const = 0;

  // Increment the iterator to the next valid element.
  virtual CATBVHNodeIterator& operator++ () = 0;

public:

  // Return an instance of the CATBVHNode currently referenced by the iterator 
  // (or NULL if iterator has reached the end.)
  virtual CATBVHNode* operator* () const = 0;

};

#endif
