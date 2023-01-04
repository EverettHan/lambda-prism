#ifndef CATIPGMDistanceToolProtected_h_
#define CATIPGMDistanceToolProtected_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMModelInterfaces.h"
#include "CATIPGMDistanceTool.h"
#include "CATListOfDouble.h"

class CATIPGMOperator;
class CATCompositeLaw;
class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATGeometry;
class CATLaw;
class CATMathFunctionX;
class CATMathQuickDiscretizeFunctionX;
class CATMathSetOfPointsND;
class CATParallelComputer;
class CATIPGMParallelConnectTool;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATTopData;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMDistanceToolProtected;

/**
 * Class defined under CATIPGMDistanceTool so as to not modify CATIPGMDistanceTool.
   Initial use is for AutoParallel, wherein services of CATGeodesicDistanceToolOld are required at CATIPGMTopDistanceTool.
 */
class ExportedByCATGMModelInterfaces CATIPGMDistanceToolProtected: public CATIPGMDistanceTool
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceToolProtected();

  virtual void ComputeExplicitFunction(
    CATSoftwareConfiguration *iConfig,
    CATGeoFactory *iFactory,
    CATIPGMParallelConnectTool *iTool,
    CATListOfDouble &iListOfOffsets) = 0;

  virtual void RemoveExpliFunction() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceToolProtected(); // -> delete can't be called
};

#endif /* CATIPGMDistanceToolProtected_h_ */
