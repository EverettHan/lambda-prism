#ifndef CATDistanceToolProtected_H
#define CATDistanceToolProtected_H

#include "CATDistanceTool.h"
 
#include "Connect.h"
#include "CATDataType.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

#include "CATBoolean.h"
#include "CATDistanceToolDef.h"
#include "CATListOfDouble.h"

class CATGeoFactory;
class CATLaw;
class CATCompositeLaw;
class CATParallelComputer;

class CATMathSetOfPointsND;
class CATMathFunctionX;
class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATLaw;
class CATParallelConnectTool;
class CATCGMOperator;
class CATTopData;
class CATGeometry;
class CATMathQuickDiscretizeFunctionX;
class CATSoftwareConfiguration;

/**
 * Class defined under CATDistanceTool so as to not modify CATDistanceTool.
   Initial use is for AutoParallel, wherein services of CATGeodesicDistanceToolOld are required at CATTopDistanceTool.
 */

class ExportedByConnect CATDistanceToolProtected : public CATDistanceTool
{
  CATCGMVirtualDeclareClass(CATDistanceToolProtected);
 public:

  CATDistanceToolProtected (CATGeoFactory * iGeoFactory, CATLaw *iDistance);
  CATDistanceToolProtected (CATGeoFactory * iGeoFactory, CATCompositeLaw *iDistance);


  virtual ~CATDistanceToolProtected();

  virtual void ComputeExplicitFunction(CATSoftwareConfiguration * iConfig,
                                                     CATGeoFactory * iFactory,
                                                     CATParallelConnectTool * iTool,
                                                     CATListOfDouble &iListOfOffsets);

  void RemoveExpliFunction();

  CATMathQuickDiscretizeFunctionX * _ExplicitFuncForAutoParallel;
};

#endif
