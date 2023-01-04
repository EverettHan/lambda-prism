#ifndef CATPGMCreateFillSurface_h_
#define CATPGMCreateFillSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"
#include "CATDataType.h"

class CATCrvLimits;
class CATCurve;
class CATFillSurface;
class CATFrFNurbsMultiForm;
class CATGeoFactory;

ExportedByCATGMOperatorsInterfaces CATFillSurface *CATPGMCreateFillSurface(
  CATGeoFactory *ifactory,
  const CATLONG32 inumberofcurves,
  const CATCurve **itabofcurve,
  CATCrvLimits *itabofcrvlimits,
  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces CATFillSurface *CATPGMCreateFillSurface(
  CATGeoFactory *ifactory,
  const CATLONG32 inumberofcurves,
  const CATCurve **itabofcurve,
  CATCrvLimits *itabofcrvlimits,
  CATLONG32 iNbOfMultiForms,
  const CATFrFNurbsMultiForm **iMultiForm,
  CATLONG32 *iTransitioncontMultiForm,
  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces
void Remove( CATFillSurface *&ioFillSurface );

#endif /* CATPGMCreateFillSurface_h_ */
