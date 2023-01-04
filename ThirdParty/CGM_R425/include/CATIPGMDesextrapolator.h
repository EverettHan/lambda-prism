#ifndef CATIPGMDesextrapolator_h_
#define CATIPGMDesextrapolator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATGeometry;
class CATSurLimits;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMDesextrapolator;

/**
 * Class defining a geometric operator that desextrapol a CATGeometrie.
 * A CATDesextrapolator operator is created with the <tt>@href CATCreateDesextrapolator </tt> global method
 * and must be directly released with the <tt>Release</tt> method after use.
 * It is is not streamable.
 */
class ExportedByCATGMModelInterfaces CATIPGMDesextrapolator: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDesextrapolator();

  /**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 */
  //virtual int Run() =0;
  /**
 * Returns the Desextrapolated CATNurbsSurface, CATNurbsCurve or CATPNurbs.
 */
  virtual CATGeometry *GetResult() = 0;

  /**
 * Allow the user to give as input topological limits instead of exact geometric
 * limits. In this case, limits will be reframed on the nearest limits corresponding
 * to an extrapolation step and containing the input limits. This implie that
 * original limits of the surface will be  kept.
 */
  virtual void SetNecessaryLimitsOption() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDesextrapolator(); // -> delete can't be called
};

//-----------------------------------------------------------------------------
// Create a Curve Desextrapolator - Do not use
//-----------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
  CATGeoFactory *iFactory,
  CATCurve *iCurve,
  const CATCrvLimits *iCrvLimits,
  CATBoolean iDuplicate = FALSE,
  CATSkillValue iMode = BASIC);

//-----------------------------------------------------------------------------
// Create a Surface Desextrapolator - Do not use
//-----------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
  CATGeoFactory *iFactory,
  CATSurface *iSurface,
  const CATSurLimits *iSurLimits,
  CATBoolean iDuplicate = FALSE,
  CATSkillValue iMode = BASIC);

//-----------------------------------------------------------------------------
// Create a Curve Desextrapolator
//-----------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve,
  const CATCrvLimits *iCrvLimits,
  CATBoolean iDuplicate = FALSE,
  CATSkillValue iMode = BASIC);

//-----------------------------------------------------------------------------
// Create a Surface Desextrapolator
//-----------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDesextrapolator *CATPGMCreateDesextrapolator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  const CATSurLimits *iSurLimits,
  CATBoolean iDuplicate = FALSE,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMDesextrapolator_h_ */
