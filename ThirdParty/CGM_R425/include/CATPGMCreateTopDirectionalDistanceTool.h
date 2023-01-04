#ifndef CATPGMCreateTopDirectionalDistanceTool_h_
#define CATPGMCreateTopDirectionalDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATTopDefine.h"
#include "CATIACGMLevel.h"

class CATIPGMDistanceTool;
class CATGeoFactory;
class CATMathDirection;
class CATTopData;
class CATLaw;

/**
 * Constructs the object for the directional computation.
 * This class is to be used when you want to create a parallel curve onto a suppport.
 * It does not create directly a curve onto 
 * a support. To do this, you must:
 * <ol>
 * <li>Specify the parameters of the offset distance by using CATIPGMDistanceTool. This parameters are: 
 * <ul>
 * <li> the parallelism mode: Directional (use CATPGMCreateTopDirectionalDistanceTool)
 * or geodesic (use CATPGMCreateTopGeodesicDistanceTool) or euclidian (use CATPGMCreateTopEuclidianDistanceTool)
 * <li> the direction defining the 2 projections before and after the parallel computation
 * before : from the surfacic support to a working plane on which the parallel wire will be computed
 * after : from the working plane to the surfacic support
 * <li> the side on which the wire is offset, it is computed from the support normal and the wire tangent: Side = Normal^Tangent 
 * <li> the law which defines the distance evolution along the wire.
 * </ul>
 * and they are specified as the arguments of CATPGMCreateTopDirectionalDistanceTool.
 * <li>Specify the type of relimitation: sharp or round and the support on which the wire is offset.
 * This is done by creating the CATIPGMExtrapolParallelTool object. 
 * <li>Create and run the CATIPGMTopParallel operator.
 * </ol>
 * @param iGeoFactory
 * The pointer to geometry factory.
 * @param iData
 * The pointer to the CATTopData.
 * @param iDirection
 * the mathematical direction defining the projection onto a working plane on which the parallel curve will be computed
 * and then projected onto the shell along the same direction 
 * @param iOrientation
 * The side on which the parallel is computed.
 * The cross product between the shell normal and the wire tangent define the
 * left side.
 * <br><b>Legal values </b>: <tt>CATOrientationPositive</tt> for the left side,
 * <tt>CATOrientationNegative</tt> for the right side.
 * @param iDistance
 * The pointer to the law defining the parallel offset.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceTool *CATPGMCreateTopDirectionalDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATMathDirection &iDirection,
  CATOrientation iOrientation,
  CATLaw *iDistance);

#endif /* CATPGMCreateTopDirectionalDistanceTool_h_ */
