#ifndef CATPGMCreateLiss_h_
#define CATPGMCreateLiss_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATIPGMLiss;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

/**
 * Creates the operator that smoothes a set of points to create a curve.
 * <br>By default, the degree of the smoothed curve is 5, the continuity constraint is C2, the
 * parameterization is free.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iPoints
 * The pointer to the set of points. Its dimension can be 2 (for a planar curve) or 3
 * @param iTol
 * The maximum distance between an input point and the smoothed curve. 
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 * @see CATLiss
 */
ExportedByCATGMOperatorsInterfaces CATIPGMLiss *CATPGMCreateLiss(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMathSetOfPointsND *iPoints,
  double &iTol,
  CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R14 CATPGMCreateLiss
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMLiss *CATPGMCreateLiss(
  CATGeoFactory *iFactory,
  CATMathSetOfPointsND *iPoints,
  double &iTol,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateLiss_h_ */
