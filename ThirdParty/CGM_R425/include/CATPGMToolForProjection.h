#ifndef CATPGMToolForProjection_h_
#define CATPGMToolForProjection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

class CATSimplifyParallelTool; // Not interfaced for the moment
class CATICGMHybProject;

ExportedByCATGMOperatorsInterfaces void CATPGMSetSimplifyTool(
  CATICGMHybProject *iProjection,
  CATSimplifyParallelTool *iCurSimplif);

ExportedByCATGMOperatorsInterfaces void CATPGMSetSimplifyToolParameters(
  CATICGMHybProject *iProjection,
  double iTolerance,
  CATLONG32 iNewSmoothing,
  CATLONG32 iOutputWire3DCleaning);

#endif /* CATPGMToolForProjection_h_ */
