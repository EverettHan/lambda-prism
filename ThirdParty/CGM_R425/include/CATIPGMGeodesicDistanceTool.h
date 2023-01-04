#ifndef CATIPGMGeodesicDistanceTool_h_
#define CATIPGMGeodesicDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDistanceTool.h"
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
class CATIPGMOperator;
class CATTopData;
class CATGeometry;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMGeodesicDistanceTool;

/**
 * @deprecated V5R10 CATPGMCreateTopGeodesicDistanceTool
 * Class defining the geodesic parallel computation.
 * This class is used to define the parameters of a @href CATIPGMTopParallel operator.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMGeodesicDistanceTool: public CATIPGMDistanceTool
{
public:
  /**
   * Constructor
   */
  CATIPGMGeodesicDistanceTool();

  /** @nodoc */
  virtual short GetType() const = 0;

  /** @nodoc */
  virtual CATTopSign GetSign() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMGeodesicDistanceTool(); // -> delete can't be called
};

#endif /* CATIPGMGeodesicDistanceTool_h_ */
