#ifndef CATIPGMDistanceTool_h_
#define CATIPGMDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Protected
 * @usage U1
 */
#include "CATGMModelInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDistanceToolDef.h"

class CATCompositeLaw;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMDistanceTool;

/**
 * Class defining the type of parallel computation and is to be used when you want to 
 * create a parallel curve onto a support. This class does not create directly a curve onto 
 * a support. To do this, you must:
 * <ol>
 * <li>Specify the parameters of the offset distance by using CATIPGMDistanceTool: 
 * <ul>
 * <li> the parallelism mode: euclidian or geodesic 
 * <li> the side on which the wire is offset, it is computed from the support normal and the wire tangent: Side = Normal^Tangent 
 * <li> the law which defines the distance evolution along the wire.
 * </ul>
 * <li>Specify the type of relimitation: sharp or round and the support on which the wire is offset.
 * This is done by creating the CATIPGMExtrapolParallelTool object. 
 * <li>Create and run the CATIPGMTopParallel operator.
 * </ol>
 * The CATIPGMDistanceTool class is created by :
 * <ul> 
 * <li> either @href CATPGMCreateTopEuclidianDistanceTool that computes the parallel
 * with an euclidian distance
 * <li> or @href CATCGMCreateTopGeodesicDistanceTool that computes the parallel
 * with a geodesic distance.
 * </ul>
 * This class is the base class for some supplied classes, but you must not derive it yourself.
 */
class ExportedByCATGMModelInterfaces CATIPGMDistanceTool: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceTool();

  /**
 * Returns the type of parallelism.
 * @return
 * <ul>
 * <li>1 = GeodesicDistanceToolType_Euclidian
 * <li>or 2 = GeodesicDistanceToolType_Geodesic.
 * </ul>
 */
  virtual short GetType() const = 0;

  /**
  * Returns the law used to compute the distance.
  * <br>Note that this operator converts the law provided to CATPGMCreateTopEuclidianDistanceTool
  * and CATCGMCreateTopGeodesicDistanceTool into a CATCompositeLaw (if it is not already one).
  * @return
  * The pointer to the law.
  */
  virtual CATCompositeLaw *GetCompositeLaw() = 0;

  /** 
 * @deprecated V5R11 GetCompositeLaw.
 */
  virtual CATCompositeLaw *GetLaw() = 0;

  /**
  * Returns the side on which the parallel is computed.
  * @return
  * The side value defined when standing along the face direction and watching in the wire direction.
  * <ul>
  * <li><tt>1</tt> for the left side
  * <li><tt>-1</tt> for the right side.
  * </ul>
  */
  virtual short GetSide() = 0;

  /** 
  * @nodoc
  * Specifies the side on which the parallel is computed.
  * @param iSide
  * The side value defined when standing along the face direction and watching in the wire direction.
  * <ul>
  * <li><tt>1</tt> for the left side
  * <li><tt>-1</tt> for the right side.
  * </ul>
  */
  virtual void SetSide(short iSide) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceTool(); // -> delete can't be called
};

#endif /* CATIPGMDistanceTool_h_ */
