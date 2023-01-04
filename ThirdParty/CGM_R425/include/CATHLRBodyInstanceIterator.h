#ifndef CATHLRBodyInstanceIterator_h
#define CATHLRBodyInstanceIterator_h

// COPYRIGHT DASSAULT SYSTEMES  2014

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMOperatorsInterfaces.h"

#include "CATBoolean.h"
#include "CATIACGMLevel.h"

class CATBody;
class CATMathTransformation;
class CATHLRBodySubEdgeIterator;


/**
 * Class defining an iterator over the input body instances used by the <tt>CATICGMHLROperator</tt> operator.

 * This iterator can only be accessed via a <tt>CATHLRResult</tt> object.
 * It provides result information for each body instance and gives access
 * to the <tt>CATHLRBodySubEdgeIterator</tt> iterator.
 *
 * @see CATICGMHLROperator, CATHLRResult, CATHLRBodySubEdgeIterator.
 */
class ExportedByCATGMOperatorsInterfaces CATHLRBodyInstanceIterator
{

public :

 /**
  * Sets the iterator to the beginning.
  */
  virtual void Begin() = 0;

 /**
  * Increments the iterator.
  */
  virtual void operator++() = 0;

 /**
  * Notifies if the iterator has reached the end.
  * @return
  * <tt>TRUE</tt> if the iterator has reached the end, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean End() const = 0;


public :

  /**
   * Returns the iterator to get the HLR subdivision applied on the edges of the current Body instance
   * @return
   *   a reference on the CATHLRBodySubEdgeIterator instance
   * This iterator instance is owned by the CATHLRBodyInstanceIterator which will release it.
   * This iterator can be get only once and its content depends automatically on the master CATHLRBodyInstanceIterator current status
   */
  virtual CATHLRBodySubEdgeIterator & GetSubEdgeIterator() = 0;


public :

 /**
  * Returns the ID of the current body instance.
  * @return
  * A <tt>CATULONG32</tt> integer ID.
  */
  virtual CATULONG32 GetID() const=0;

 /**
  * Returns the body pointer of the current body instance.
  * @return
  * A <tt>CATBody</tt> object.
  */
  virtual CATBody * GetBody() const=0;

 /**
  * Returns the transformation associated with the current body instance.
  * @return
  * A <tt>CATMathTransformation</tt> object.
  */
  virtual CATMathTransformation * GetTransformation() const=0;

 /**
  * Notifies if the HLR calculation for the current body instance failed.
  * @return
  * <tt>TRUE</tt> if the HLR calculation failed, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean HasFailed() const=0;

 /**
  * Returns the full occlusion status for the current body instance.
  * This situation might happen if two instances of the same body, each with a different transformation, are positioned 
  * so that one is exactly placed in front of the other from the observer point of view.
  * @return
  * <tt>TRUE</tt> if the current body instance is fully occluded, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean IsFullyOccluded(CATULONG32 &oOccludingInstanceID) const=0;


#ifdef CATIACGMR419CAA
 /**
  * Returns TRUE if the geometry of body is Polyhedral, else FALSE
  */
  virtual CATBoolean IsPolyhedral() const=0;
#endif

};

#endif
