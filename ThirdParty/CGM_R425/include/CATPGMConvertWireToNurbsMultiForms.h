#ifndef CATPGMConvertWireToNurbsMultiForms_h_
#define CATPGMConvertWireToNurbsMultiForms_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

class CATBody;
class CATFrFNurbsMultiForm;
class CATTopData;

ExportedByCATGMOperatorsInterfaces CATFrFNurbsMultiForm **CATPGMConvertWireToNurbsMultiForms(
  CATTopData *iTopData,
  const CATBody *iWire,
  CATFrFNurbsMultiForm **iRefMults,
  CATLONG32 iNbRefMults);

#endif /* CATPGMConvertWireToNurbsMultiForms_h_ */
