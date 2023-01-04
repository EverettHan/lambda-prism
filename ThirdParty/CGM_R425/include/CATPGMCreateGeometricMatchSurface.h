#ifndef CATPGMCreateGeometricMatchSurface_h_
#define CATPGMCreateGeometricMatchSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATFrFCompositeCurve;
class CATGeoFactory;
class CATGeometricMatchSurface;
class CATPLine;
class CATSoftwareConfiguration;

// NE PLUS APPELER car pas de config
ExportedByCATGMOperatorsInterfaces CATGeometricMatchSurface *CATPGMCreateGeometricMatchSurface(
  CATGeoFactory *iFactory,
  const CATPLine *iFrontiere,
  const CATFrFCompositeCurve *iCompCurve2,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateGeometricMatchSurface.
 */
inline CATGeometricMatchSurface *CreateGeometricMatchSurface(
  CATGeoFactory *iFactory,
  const CATPLine *iFrontiere,
  const CATFrFCompositeCurve *iCompCurve2,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGeometricMatchSurface(iFactory, iFrontiere, iCompCurve2, iMode);
}

ExportedByCATGMOperatorsInterfaces CATGeometricMatchSurface *CATPGMCreateGeometricMatchSurface(
  CATSoftwareConfiguration *iConfig,
  CATGeoFactory *iFactory,
  const CATPLine *iFrontiere,
  const CATFrFCompositeCurve *iCompCurve2,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateGeometricMatchSurface.
 */
inline CATGeometricMatchSurface *CreateGeometricMatchSurface(
  CATSoftwareConfiguration *iConfig,
  CATGeoFactory *iFactory,
  const CATPLine *iFrontiere,
  const CATFrFCompositeCurve *iCompCurve2,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateGeometricMatchSurface(iConfig, iFactory, iFrontiere, iCompCurve2, iMode);
}

ExportedByCATGMOperatorsInterfaces
void Remove( CATGeometricMatchSurface *&ioGeometricMatchSurface );

#endif /* CATPGMCreateGeometricMatchSurface_h_ */
