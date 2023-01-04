//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
//=============================================================================
//
// CATExtrapolMultiSurface:
//   Header file for the CATExtrapolMultiSurface class,
//   which is used to extrapolate a multi-surface from its current global
//   limits to specified required global limits.
//
//   Currently, the only surfaces of a multi-surface that can be extrapolated
//   are (a) those of type NURBS and (b) those of type offset whose reference
//   surface is of type NURBS, provided that the appropriate option is set.
//=============================================================================
// Usage notes:
//=============================================================================
// 26/11/15 R1Y  Creation
// 22/08/16 R1Y  Added a flag to allow extrapolation of non-NURBS surfaces.
// 21/09/20 LJL2 Add SetExtensionModeOn()
//=============================================================================

#ifndef CATExtrapolMultiSurface_H
#define CATExtrapolMultiSurface_H

#include "Y30C3XGG.h"
#include "CATGeoOperator.h"
#include "CATBoolean.h"

class CATMultiSurface;
class CATGeoFactory;
class CATSoftwareConfiguration;

/**
 * Class defining the operator for extrapolating a multi-surface from its
 * current global limits to specified required global limits.
 *<ul>
 *<li>The CATExtrapolMultiSurface is created with the @href
 * CreateExtrapolation method and directly <tt>delete</tt>d. 
 *<li>The operation is automatically done at the operator creation. 
 *</ul>
 */
class ExportedByY30C3XGG CATExtrapolMultiSurface : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATExtrapolMultiSurface);

protected:

  /** @nodoc */
  // Do not use the constructor directly; instead, use CreateExtrapolation().
  CATExtrapolMultiSurface();

  /** @nodoc */
  // Do not use the constructor directly; instead, use CreateExtrapolation().
  CATExtrapolMultiSurface(CATGeoFactory * iFactory);

private:

  /** @nodoc */
  // Forbidden (declared, but not defined): Construction by copying or using the assignment operator.
  CATExtrapolMultiSurface(const CATExtrapolMultiSurface & iExtrapolMultiSurface);
  CATExtrapolMultiSurface & operator=(const CATExtrapolMultiSurface & iExtrapolMultiSurface);

public :

  /** @nodoc */
  // Destructor.
  virtual ~CATExtrapolMultiSurface();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  /**
   * Indicates whether the multi-surface has been extrapolated for <tt>this</tt>
   * CATExtrapolMultiSurface operator.
   * @return
   * Indicates whether the multi-surface has been extrapolated.
   * <br><b>Legal values</b>: <tt>TRUE</tt> if the multi-surface has been
   * extrapolated; <tt>FALSE</tt>, otherwise.
   */
  virtual CATBoolean MultiSurfaceIsExtrapolated() const = 0;

  /**
   * Gets the extrapolated multi-surface for <tt>this</tt>
   * CATExtrapolMultiSurface operator.
   * @return
   * A pointer to the multi-surface (the pointer can be null if the multi-surface
   * has not been extrapolated).
   */
  virtual const CATMultiSurface * const GetResult() const = 0;

   /**
    * Allow the extension (but not the extrapolation) of the MultiSurface
    */
  virtual void SetExtensionModeOn() = 0;
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
 * @return
 * The pointer to the created operator. 
 */
ExportedByY30C3XGG CATExtrapolMultiSurface * CreateExtrapolation(      CATGeoFactory            * const iFactory,
                                                                       CATSoftwareConfiguration *       iConfig,
                                                                       CATMultiSurface          * const iMultiSurfaceToExtrapolate,
                                                                 const double                   * const iRequiredGlobalLimits,
                                                                 const CATBoolean                       iAllowMultipleExtrapolation,
                                                                 const CATBoolean                       iAllowOffsetNurbsExtrapolation);

 /**
  * Removes a CATExtrapolMultiSurface operator.
  * @param ioExtrapolOper
  * The CATExtrapolMultiSurface operator that is to be removed.
  */
ExportedByY30C3XGG void Remove(CATExtrapolMultiSurface *& ioExtrapolOper);

#endif
