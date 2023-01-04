// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCGMPickOperatorResultIterator.h
//
//===================================================================
// May 2010  MPX/NDO
//===================================================================
#ifndef CATCGMPickOperatorResultIterator_H
#define CATCGMPickOperatorResultIterator_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

class CATCGMPickOperatorPickedObject;


/**
 * Iterator through picked objects as computed by the picking operator
 * @see CATCGMPickOperator.
 */
class ExportedByCATGMModelInterfaces CATCGMPickOperatorResultIterator
{

public:

  /**
   * Set the iterator to the beginning.
   */
  virtual void Begin() = 0;
  
  /**
   * Increment the iterator.
   */
  virtual CATCGMPickOperatorResultIterator& operator++() = 0;

  /**
   * Returns TRUE if the iterator has reached the end.
   * @return
   *   TRUE or FALSE
   */
  virtual CATBoolean End() const = 0;

public:

  /**
   * Returns the picked object at the current iterator position.
   * @return
   *   The picked object.
   */
  virtual const CATCGMPickOperatorPickedObject* Get() const = 0;

public:

  virtual ~CATCGMPickOperatorResultIterator();

};

#endif
