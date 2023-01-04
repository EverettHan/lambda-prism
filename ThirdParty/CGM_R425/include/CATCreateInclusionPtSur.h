#ifndef CATCreateInclusionPtSur_H
#define CATCreateInclusionPtSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"
#include "CreateInclusionPtSur.h"

class CATGeoFactory;
class CATPoint;
class CATSurface;
class CATInclusionPtSur;
class CATMathPoint;
class CATSoftwareConfiguration;

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
 * @return
 * The pointer to the created operator.To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATInclusionPtSur * CATCreateInclusion(CATGeoFactory * iFactory,
                                                          CATSoftwareConfiguration *Config,
                                                          const CATPoint * iPt, 
                                                          const CATSurface *iSur, 
                                                          const double & iTol,
                                                          const CATBoolean iSearchOnBoundary = TRUE,
                                                          CATSkillValue iMode = BASIC);
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
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByY300IINT CATInclusionPtSur * CATCreateInclusion(CATGeoFactory * iFactory,
                                                          CATSoftwareConfiguration *Config,
                                                          const CATMathPoint & iPt, 
                                                          const CATSurface *Sur, 
                                                          const double & iTol,
                                                          const CATBoolean iSearchOnBoundary = TRUE,
                                                          CATSkillValue iMode = BASIC);


#endif




