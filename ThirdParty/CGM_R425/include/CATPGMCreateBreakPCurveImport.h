#ifndef CATPGMCreateBreakPCurveImport_h_
#define CATPGMCreateBreakPCurveImport_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"

class CATPGMBreakPCurveImport;
class CATFrFNurbsMultiForm;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurfaceImport;

ExportedByCATGMModelInterfaces CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
  CATSoftwareConfiguration *iConfig,
  CATPCurve *initialPCurve,
  CATSurfaceImport *surfaceImport);

ExportedByCATGMModelInterfaces CATPGMBreakPCurveImport *CATPGMCreateBreakPCurveImport(
  CATSoftwareConfiguration *iConfig,
  CATFrFNurbsMultiForm *mf,
  CATLONG32 nbKnotsU,
  double *knotsU,
  CATLONG32 nbKnotsV,
  double *knotsV);

#endif /* CATPGMCreateBreakPCurveImport_h_ */
