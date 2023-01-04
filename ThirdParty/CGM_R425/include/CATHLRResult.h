#ifndef CATHLRResult_h
#define CATHLRResult_h

// COPYRIGHT DASSAULT SYSTEMES  2014

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMRefCounted.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATErrorDef.h"

#include "CATCrvParam.h"

class CATHLRResultImpl;
class CATHLRBodyInstanceIterator;


/**
 * Defines edge part visibility types resulting from an HLR computation.
 * @param CATHLRVisible
 * The view of the edge part is unobstructed.
 * @param CATHLRHidden
 * The view of the edge part is obscured by other objects in front of it.
 * @param CATHLROccluded
 * The view of the edge part is redundant with another edge part in front of it.
 * @param CATHLRDegenerated
 * The view of the edge part has degenerated to a point.
 */
enum CATHLRVisibility { CATHLRVisible, CATHLRHidden, CATHLROccluded, CATHLRDegenerated };

#include "CATHLRBodyInstanceIterator.h"
#include "CATHLRBodySubEdgeIterator.h"

/**
 * Class defining an object to access the results of an HLR operation.

 * The <tt>CATHLRResult</tt> object is created by the method
 * <tt>CATICGMHLROperator::GetResult()</tt> after a successful run of the operator. It is the user's 
 * responsibility to release the result object after it has been used.
 *
 * The HLR result provides access to the <tt>CATHLRBodyInstanceIterator</tt> iterator 
 * which in turn provides access to the <tt>CATHLRBodySubEdgeIterator</tt> iterator.
 * These iterators can then be used to retrieve visibility information and compute the projection
 * of selected edges onto the projection plane.
 *
 * @see CATICGMHLROperator, CATHLRBodyInstanceIterator, CATHLRBodySubEdgeIterator.
 */
class ExportedByCATGMOperatorsInterfaces CATHLRResult : public CATCGMRefCounted
{

public:

  
 /**
  * Returns an iterator over the input body instances.
  *
  * @return
  * A reference to an <tt>CATHLRBodyInstanceIterator</tt>.
  * This iterator is owned by the <tt>CATHLRResult</tt> which manages its life cycle.
  */
  virtual CATHLRBodyInstanceIterator & GetBodyInstanceIterator()=0;


  
public:

 /** @nodoc */
  virtual CATHLRResultImpl * GetImpl()=0;



protected :
  
 /** @nodoc */
  virtual ~CATHLRResult() {};

};

#endif
