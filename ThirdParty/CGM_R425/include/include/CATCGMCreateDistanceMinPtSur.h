#ifndef CATCGMCreateDistanceMinPtSur_h_
#define CATCGMCreateDistanceMinPtSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATSkillValue.h"

class CATICGMDistanceMinPtSur;
class CATGeoFactory;
class CATMathPoint;
class CATPoint;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurLimits;

/**
 * Creates an operator for computing the minimum distance between a CATPoint
 * and a CATSurface.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iSur
 * The pointer to the surface.
 * @param iSurLim
 * The limits of the surface.
 * @param iSearchOnBoundary
 *<dl><dt><tt>TRUE</tt><dd> the operator operates on the whole surface, including
 * its boundary.
 *    <dt><tt>FALSE</tt><dd> the operator does not operate on the CATSurface
 * boundary.</dl>
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMDistanceMinPtSur *CATCGMCreateDistanceMinLim(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATPoint *iPt,
  const CATSurface *iSur,
  const CATSurLimits *iSurLim,
  CATBoolean iSearchOnBoundary = TRUE,
  CATSkillValue iMode = BASIC);

/**
* Use the signature with <tt>CATSurLimits</tt> as parameter.
* This signature has to be used with a <tt>SetLimits<tt>.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMDistanceMinPtSur *CATCGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATPoint *iPt,
  const CATSurface *iSur,
  CATBoolean iSearchOnBoundary = TRUE,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for computing the minimum distance between a CATMathPoint
 * and a CATSurface.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iSur
 * The pointer to the surface.
 * @param iSurLim
 * The limits of the surface.
 * @param iSearchOnBoundary
 *<dl><dt><tt>TRUE</tt><dd> the operator operates on the whole surface, including
 * its boundary.
 *    <dt><tt>FALSE</tt><dd> the operator does not operate on the CATSurface
 * boundary.</dl>
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMDistanceMinPtSur *CATCGMCreateDistanceMinLim(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATMathPoint &iPt,
  const CATSurface *iSur,
  const CATSurLimits *iSurLim,
  CATBoolean iSearchOnBoundary = TRUE,
  CATSkillValue iMode = BASIC);

/** 
* Use the signature with <tt>CATSurLimits</tt> as parameter.
* This signature has to be used with a <tt>SetLimits<tt>.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMDistanceMinPtSur *CATCGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  const CATMathPoint &iPt,
  const CATSurface *iSur,
  CATBoolean iSearchOnBoundary = TRUE,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateDistanceMinPtSur_h_ */
