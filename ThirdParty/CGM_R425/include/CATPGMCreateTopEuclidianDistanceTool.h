#ifndef CATPGMCreateTopEuclidianDistanceTool_h_
#define CATPGMCreateTopEuclidianDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATTopDefine.h"
#include "CATIACGMLevel.h"

/**
 * @level Protected
 * @usage U1
 */

#include "CATCompositeLaw.h" // CATCompositeLaw is replaced by its parent class CATLaw
class CATIPGMDistanceTool;
class CATGeoFactory;
class CATTopData;

/**
 * Constructs the object for the euclidean computation.
 * This class is to be used when you wan to create a parallel curve onto a suppport.
 * It does not create directly a curve onto 
 * a support. To do this, you must:
 * <ol>
 * <li>Specify the parameters of the offset distance by using CATIPGMDistanceTool. This parameters are: 
 * <ul>
 * <li> the parallelism mode: euclidian (use CATPGMCreateTopEuclidianDistanceTool)
 * or geodesic (use CATPGMCreateTopGeodesicDistanceTool)
 * <li> the side on which the wire is offset, it is computed from the support normal and the wire tangent: Side = Normal^Tangent 
 * <li> the law which defines the distance evolution along the wire.
 * </ul>
 * and they are specified as the arguments of CATPGMCreateTopGeodesicDistanceTool.
 * <li>Specify the type of relimitation: sharp or round and the support on which the wire is offset.
 * This is done by creating the CATIPGMExtrapolParallelTool object. 
 * <li>Create and run the CATIPGMTopParallel operator.
 * </ol>
 * @param iGeoFactory
 * The pointer to geometry factory.
 * @param iData
 * The pointer to the CATTopData.
 * @param iOrientation
 * The side on which the parallel is computed.
 * The cross product between the shell normal and the wire tangent define the
 * left side.
 * <br><b>Legal values </b>: <tt>CATOrientationPositive</tt> for the left side,
 * <tt>CATOrientationNegative</tt> for the right side.
 * @param iDistance
 * The pointer to the law defining the parallel offset.
 * @return [out, IUnknown#Release]
 */
#ifndef CATIACGMR214CAA
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceTool *CATPGMCreateTopEuclidianDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATOrientation iOrientation,
  CATCompositeLaw *iDistance);

#else
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceTool *CATPGMCreateTopEuclidianDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATOrientation iOrientation,
  CATLaw *iDistance);
#endif

#endif /* CATPGMCreateTopEuclidianDistanceTool_h_ */
