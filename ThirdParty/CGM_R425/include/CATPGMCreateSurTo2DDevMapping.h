#ifndef CATPGMCreateSurTo2DDevMapping_h_
#define CATPGMCreateSurTo2DDevMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATBody;
class CATGeoFactory;
class CATMathAxis;
class CATMathLine;
class CATSoftwareConfiguration;
class CATIPGMSurTo2DGlobalDevDevMapping;
class CATIPGMSurTo2DGlobalDevProjMapping;
class CATVertex;



/**
* Retrieves theIvariant Point Working axis  
* Do not depend on Mapping Mode. 
*/
ExportedByCATGMOperatorsInterfaces void CATPGMGetSurTo2DDevProjAxis(
  CATVertex *iInvariantPoint,
  const CATMathLine &iRevolAxis,
  CATMathAxis &oAxisOnSupport,
  CATSoftwareConfiguration *iConfig = 0);

/**
* Creates DevProj mapping according to an axis 
* =>All surfaces witin the shell  must be revolution surfaces or equivalent with iRevolAxis 
* => Invariant Point => X=0, Y=0
* => Y will be angle coordinate ( steching =0 at radius invariantPoint)
* => X will transfered according to curve coordinate on a circle of radius iRADIUS and then projected normally to the circle on surface.
* => If RADIUS= 0. then the distance fron Invariant Point to RevolAxis is taken
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMSurTo2DGlobalDevProjMapping *CATPGMCreateDevProjMapping(
  CATGeoFactory *iFactory,
  const CATBoolean iImplicitMapping,
  CATVertex *iInvariantPoint,
  const CATMathLine &iRevolAxis,
  const double &iRadius = 0.,
  CATSoftwareConfiguration *iConfig = 0);

/**
* Retrieves the Invariant Point Working axis  according to the Mapping Mode.
* =>According to Shell orientation if iImplicitMapping=0 
* =>According to exterior evaluation if iImplicitMapping=1  
*/
ExportedByCATGMOperatorsInterfaces void CATPGMGetSurTo2DDevDevAxis(
  CATGeoFactory *iFactory,
  CATBody *SupportShell,
  const CATBoolean iImplicitMapping,
  CATVertex *iInvariantPoint,
  const CATMathLine &iRevolAxis,
  CATMathAxis &oAxisOnSupport,
  CATLONG32 &oAxisInversionSuggestion,
  double &oSkinAxisOrientation,
  CATSoftwareConfiguration *iConfig = 0);

/**
* Creates DevDev mapping according to an axis .
* =>All surfaces witin the shell  must be revolution surfaces or equivalent with iRevolAxis 
* => Invariant Point => X=0, Y=0
* => Y will be angle coordinate ( steching =0 at radius invariantPoint)
* => X will be generatrice direction according to curve coordinate 
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMSurTo2DGlobalDevDevMapping *CATPGMCreateDevDevMapping(
  CATGeoFactory *iFactory,
  CATBody *SupportShell,
  const CATBoolean iImplicitMapping,
  CATVertex *iInvariantPoint,
  const CATMathLine &iRevolAxis,
  CATSoftwareConfiguration *iConfig = 0);

#endif /* CATPGMCreateSurTo2DDevMapping_h_ */
