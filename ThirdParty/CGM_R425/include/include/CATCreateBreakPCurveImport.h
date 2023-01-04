#ifndef CATCreateBreakPCurveImport_H
#define CATCreateBreakPCurveImport_H

#include "Y300IINT.h"
#include "CATDataType.h"
#include "CATTolerance.h"

class CATBreakPCurveImport;
class CATSoftwareConfiguration;
class CATFrFNurbsMultiForm;
class CATPCurve;
class CATSurfaceImport;

ExportedByY300IINT
CATBreakPCurveImport * CATCreateBreakPCurveImport(CATSoftwareConfiguration * iConfig,
                                                  CATFrFNurbsMultiForm* mf,
                                                  CATLONG32 nbKnotsU, double* knotsU,
                                                  CATLONG32 nbKnotsV, double* knotsV,
                                                  const CATTolerance & iTolObject = CATGetDefaultTolerance());
ExportedByY300IINT
CATBreakPCurveImport * CATCreateBreakPCurveImport(CATSoftwareConfiguration * iConfig,
                                                  CATPCurve* initialPCurve,
                                                  CATSurfaceImport* surfaceImport);


#endif






