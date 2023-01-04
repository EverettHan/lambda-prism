// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPGMPickOperatorResultIterator.h
//
//===================================================================
// May 2010  MPX/NDO
//===================================================================
#ifndef CATPGMPickOperatorResultIterator_H
#define CATPGMPickOperatorResultIterator_H

#include "CATGMModelInterfaces.h"
#include "CATCGMPickOperatorResultIterator.h"
#include "CATBoolean.h"

class CATCGMPickOperatorPickedObject;
class CATPGMPickOperatorPickedObject;


/**
 * Iterator through picked objects as computed by the picking operator
 * @see CATCGMPickOperator.
 */
class ExportedByCATGMModelInterfaces CATPGMPickOperatorResultIterator : public CATCGMPickOperatorResultIterator
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
   */
  virtual CATBoolean End() const = 0;

public:

  // ******* Not yet supported *********
  // Set filter, so that only results passing the filter are iterated
  //virtual HRESULT SetFilter (const CATPGMPickOperator::FilterType& iFilterType) = 0;

public:

  /**
   * Returns the picked object at the current iterator position.
   * @return
   *   The picked object.
   */
  virtual const CATCGMPickOperatorPickedObject* Get() const = 0;

  /**
   * Returns the picked object at the current iterator position.
   * @return
   *   The picked object.
   */
  virtual const CATPGMPickOperatorPickedObject* GetPGM () const = 0;

public:

  virtual ~CATPGMPickOperatorResultIterator();

};

#endif
