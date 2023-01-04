#ifndef CATPGMCreateFrFCompositeCurveMapping_h_
#define CATPGMCreateFrFCompositeCurveMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATFrFCompositeCurve;
class CATFrFCompositeCurveMapping;

//
ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurveMapping *CATPGMCreatePreciseCompositeCurveMapping(
  const CATFrFCompositeCurve *iCompositeCurve);

//
ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurveMapping *CATPGMCreateDeprecatedUnpreciseCompositeCurveMapping(
  const CATFrFCompositeCurve *iCompositeCurve);

//
ExportedByCATGMOperatorsInterfaces void Remove(CATFrFCompositeCurveMapping *&ioCompositeCurveMapping);

#endif /* CATPGMCreateFrFCompositeCurveMapping_h_ */
