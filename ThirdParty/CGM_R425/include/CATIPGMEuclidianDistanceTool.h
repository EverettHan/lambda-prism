#ifndef CATIPGMEuclidianDistanceTool_h_
#define CATIPGMEuclidianDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDistanceTool.h"
#include "CATTopDefine.h"
#include "CATTopDef.h"
#include "CATDataType.h"
#include "CATBoolean.h"

class CATCompositeLaw;
class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATLaw;
class CATMathFunctionX;
class CATMathSetOfPointsND;
class CATParallelComputer;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATCompositeLaw;
class CATSoftwareConfiguration;
class CATIPGMOperator;
class CATTopData;
class CATGeometry;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMEuclidianDistanceTool;

/**
 * @deprecated V5R10 CATPGMCreateTopEuclidianDistanceTool
 * Class defining the euclidean parallel computation.
 * This class is used to define the parameters of a @href CATIPGMTopParallel operator.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMEuclidianDistanceTool: public CATIPGMDistanceTool
{
public:
  /**
   * Constructor
   */
  CATIPGMEuclidianDistanceTool();

  /** @nodoc */
  virtual short GetType() const = 0;

  /** @nodoc */
  virtual CATTopSign GetSign() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMEuclidianDistanceTool(); // -> delete can't be called
};

/**
 * @nodoc
 * Use the signature with CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATOrientation iOrientation,
  CATCompositeLaw *iDistance);

/**
 * @nodoc
 * Use the signature with CATSoftwareConfiguration and CATCompositeLaw.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATOrientation iOrientation,
  CATLaw *iDistance);

/**
 * @nodoc
 * Use the signature with CATCompositeLaw.
 * Constructs the object for the euclidean computation.
 * @param iGeoFactory
 * The pointer to geometry factory.
 * @param iSoftwareConfiguration
 * The pointer to the software configuration with which the code must be run.
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
ExportedByCATGMOperatorsInterfaces CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATOrientation iOrientation,
  CATLaw *iDistance);

/**
 * Constructs the object for the euclidean computation.
 * @param iGeoFactory
 * The pointer to geometry factory.
 * @param iSoftwareConfiguration
 * The pointer to the software configuration with which the code must be run.
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
ExportedByCATGMOperatorsInterfaces CATIPGMEuclidianDistanceTool *CATPGMCreateEuclidianDistanceTool(
  CATGeoFactory *iGeoFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATOrientation iOrientation,
  CATCompositeLaw *iDistance);

#endif /* CATIPGMEuclidianDistanceTool_h_ */
