#ifndef CATPGMlsoUtilTrace_h_
#define CATPGMlsoUtilTrace_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMModelInterfaces.h"
#include "CATlsoUtilTraceDef.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATErrorDef.h"

//--------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Dump  Level1 or 2 Traces : (Constructeur, Run , Destructor) * (Beginning, End)
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_MaxLevelTrace=1   (ou plus) 
//-----------------------------------------------------------------------------
ExportedByCATGMModelInterfaces void CATPGMLSOTraceLevel1or2(
  CATlsoUtilTrace_OperatorName iOpName,
  CATlsoUtilTrace_Level1Prefix iPrefix,
  CATBoolean iWithLineBreak = TRUE);

//-----------------------------------------------------------------------------
// Dump  Level N Traces 
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_MaxLevelTrace=5   ( si N=5 ou moins de 5) 
//-----------------------------------------------------------------------------
ExportedByCATGMModelInterfaces void CATPGMLSOTraceLevelN(
  CATLONG32 iLevel,
  CATlsoUtilTrace_OperatorName iOpName,
  const char *iText,
  HRESULT *iHResult = 0,
  CATBoolean iWithLineBreak = TRUE);

#endif /* CATPGMlsoUtilTrace_h_ */
