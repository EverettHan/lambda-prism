#ifndef CATPGMCreateTopologicalDeviation_h_
#define CATPGMCreateTopologicalDeviation_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATGeoFactory;
class CATPGMTopologicalDeviation;

//========================================================================
//
//========================================================================   
ExportedByCATGMOperatorsInterfaces CATPGMTopologicalDeviation *CATPGMCreateTopologicalDeviation(
  CATGeoFactory *iFactory,
  const CATBody *iBodySupport1,
  const CATBody *iBodySupport2,
  const CATDomain *iDomainSupport1 = 0,
  const CATDomain *iDomainSupport2 = 0,
  CATSkillValue iMode = BASIC);

//
ExportedByCATGMOperatorsInterfaces void CATPGMRemove(CATPGMTopologicalDeviation *&iTopologicalDeviation);

#endif /* CATPGMCreateTopologicalDeviation_h_ */
