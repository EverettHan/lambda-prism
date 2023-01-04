#ifndef CATPGMDoSmooth_h_
#define CATPGMDoSmooth_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATPointOnCurve;
class CATSoftwareConfiguration;
class CATTopData;

ExportedByCATGMOperatorsInterfaces void CATPGMDoSmoothTgts(
  CATGeoFactory *Builder,
  CATTopData *iData,
  CATBody *TangentBody,
  CATBody *Support1,
  CATBody *PtCrv1,
  CATBody *Support2,
  CATBody *PtCrv2,
  CATBody *&SmoothBody,
  CATLONG32 iTrimFirst = 1,
  CATLONG32 iTrimLast = 1);

#endif /* CATPGMDoSmooth_h_ */
