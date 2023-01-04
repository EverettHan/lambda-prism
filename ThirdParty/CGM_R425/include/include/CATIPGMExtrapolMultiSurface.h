#ifndef CATIPGMExtrapolMultiSurface_h_
#define CATIPGMExtrapolMultiSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATGeoFactory;
class CATMultiSurface;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMExtrapolMultiSurface;

/**
 * Class defining the operator for extrapolating a multi-surface from its
 * current global limits to specified required global limits.
 *<ul>
 *<li>The CATIPGMExtrapolMultiSurface is created with the @href
 * CATPGMCreateExtrapolation method and directly <tt>delete</tt>d. 
 *<li>The operation is automatically done at the operator creation. 
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMExtrapolMultiSurface: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolMultiSurface();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  /**
   * Indicates whether the multi-surface has been extrapolated for <tt>this</tt>
   * CATIPGMExtrapolMultiSurface operator.
   * @return
   * Indicates whether the multi-surface has been extrapolated.
   * <br><b>Legal values</b>: <tt>TRUE</tt> if the multi-surface has been
   * extrapolated; <tt>FALSE</tt>, otherwise.
   */
  virtual CATBoolean MultiSurfaceIsExtrapolated() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolMultiSurface(); // -> delete can't be called
};

/**
 * Creates an operator for extrapolating a multi-surface from its current
 * global limits to specified required global limits.
 * <br>
 * @param iFactory
 * A pointer to the factory of the geometry.
 * The first surface.
 * @param iConfig
 * The software configuration.
 * @param iMultiSurfaceToExtrapolate
 * A pointer to the multi-surface that is to be extrapolated.
 * @param iRequiredGlobalLimits
 * An array of four values for the required global limits of the 
 * multi-surface.
 * The order for the values is the minimum U-parameter value, the minimum
 * V-parameter value, the maximum U-parameter value, and the maximum
 * V-parameter value.
 * @param iAllowMultipleExtrapolation
 * Indicates whether extrapolation is permitted on multi-surfaces that
 * consist of more than one surface
 * @param iAllowOffsetNurbsExtrapolation
 * Indicates whether extrapolation is permitted on multi-surfaces that
 * consist of offset surfaces whose reference surface is of type NURBS
 * <br><b>Legal values</b>: <tt>TRUE</tt> if multiple extrapolation is
 * permitted; <tt>FALSE</tt>, otherwise.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. 
 */
ExportedByCATGMModelInterfaces CATIPGMExtrapolMultiSurface *CATPGMCreateExtrapolation(
  CATGeoFactory * const iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMultiSurface * const iMultiSurfaceToExtrapolate,
  const double * const iRequiredGlobalLimits,
  const CATBoolean iAllowMultipleExtrapolation,
  const CATBoolean iAllowOffsetNurbsExtrapolation = FALSE);

#endif /* CATIPGMExtrapolMultiSurface_h_ */
