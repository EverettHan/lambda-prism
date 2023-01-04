#ifndef CATHLRBodySubEdgeIterator_h
#define CATHLRBodySubEdgeIterator_h

// COPYRIGHT DASSAULT SYSTEMES  2014

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMOperatorsInterfaces.h"

#include "CATBoolean.h"
#include "CATSysErrorDef.h"
#include "CATIACGMLevel.h"
#include "CATHLRResult.h"
#include "CATLISTV_CATMathPoint2D.h"  

class CATCell;
class CATPCurve;


/**
 * Class defining an iterator over the sub-edges of an input body instance included in an HLR computation.

 * This iterator can only be accessed via a <tt>CATHLRBodyInstanceIterator</tt> object.
 * It iterates over all the sub-edges of a body instance and provides the capability to compute the projection of the current sub-edge
 * onto the projection plane.
 *
 * @see CATICGMHLROperator, CATHLRBodyInstanceIterator, CATHLRResult.
 */
class ExportedByCATGMOperatorsInterfaces CATHLRBodySubEdgeIterator
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
  * Returns the <tt>CATCell</tt> support for the current sub-edge.
  * The support cell could be a <tt>CATFace</tt> of the current body instance, 
  * if the sub-edge is a silhouette which is generated from the interior of 
  * the face. Otherwise, the support is the originating <tt>CATEdge</tt>.
  * This cell must be associated with the transformation of the current body
  * instance to be represented correctly in the context of the input HLR scene.
  * @return
  * The support <tt>CATCell</tt>.
  */
  virtual CATCell * GetCellSupport() const=0;

 /** 
  * Returns the computed visibility for the current sub-edge.
  * @return
  * The <tt>CATHLRVisibility</tt> value.
  */
  virtual CATHLRVisibility GetVisibility() const=0;

 /** 
  * Notifies if the current sub-edge is an outline.
  * @return
  * <tt>TRUE</tt> if the current sub-edge is an outline, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean IsAnOutline() const=0;

 /** 
  * Computes on the fly the projection of the current sub-edge on the projection plane.
  * Returns NULL if the current sub-edge is seen as "Degenerated" or if the projected curve cannot be computed.
  * It is the responsibility of the caller to manage the life cycle of the returned <tt>CATPCurve</tt>.
  * @return
  * The projected <tt>CATPCurve</tt>.
  */
  virtual CATPCurve * ComputeProjection() =0;

#ifdef CATIACGMR425CAA
  /** 
  * Computes on the fly the discrete projection of the current sub-edge on the projection plane.
  * Returns E_FAIL if the current sub-edge is seen as "Degenerated" or if the projected curve cannot be computed.
  * This API is dedicated to polyhedral entities, as complementary alternative of ComputeProjection, strictly dedicated to exact entities
  * @return S_OK if succeeded, else E_FAIL
  */
  virtual HRESULT ComputeDiscreteProjection(CATLISTV(CATMathPoint2D) &oListOfProjectedPts)=0;
#endif

};

#endif
