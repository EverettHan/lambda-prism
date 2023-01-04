#ifndef CATCGMCreateInclusionPtSur_h_
#define CATCGMCreateInclusionPtSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATICGMInclusionPtSur;
class CATMathPoint;
class CATPoint;
class CATSoftwareConfiguration;
class CATSurface;

/**
 * Creates an operator for testing the inclusion of a CATMathPoint in a CATSurface.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The point.
 * @param iSur
 * The pointer to the surface.
 * @param iTol
 * The tolerance used to decide the inclusion.
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
ExportedByCATGMModelInterfaces CATICGMInclusionPtSur *CATCGMCreateInclusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *Config,
  const CATMathPoint &iPt,
  const CATSurface *Sur,
  const double &iTol,
  const CATBoolean iSearchOnBoundary = TRUE,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for testing the inclusion of a CATPoint in a CATSurface.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPt
 * The pointer to the point.
 * @param iSur
 * The pointer to the surface.
 * @param iTol
 * The tolerance used to decide the inclusion.
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
 * The pointer to the created operator.To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMInclusionPtSur *CATCGMCreateInclusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *Config,
  const CATPoint *iPt,
  const CATSurface *iSur,
  const double &iTol,
  const CATBoolean iSearchOnBoundary = TRUE,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateInclusionPtSur_h_ */
