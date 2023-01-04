#ifndef CATCreateDistanceMinPtSur_H
#define CATCreateDistanceMinPtSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATSurLimits.h"

class CATGeoFactory;
class CATPoint;
class CATSurface;
class CATDistanceMinPtSur;
class CATMathPoint;
class CATSoftwareConfiguration;

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
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATDistanceMinPtSur * CATCreateDistanceMinLim(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
								                                      const CATPoint * iPt, 
								                                      const CATSurface *iSur,
                                                              const CATSurLimits * iSurLim,
                                                              CATBoolean iSearchOnBoundary = TRUE,
								                                      CATSkillValue iMode = BASIC); 
/** 
* @deprecated V5R20 
* Use the signature with <tt>CATSurLimits</tt> as parameter.
* This signature has to be used with a <tt>SetLimits<tt>.
*/
ExportedByY300IINT CATDistanceMinPtSur * CATCreateDistanceMin(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
								                                      const CATPoint * iPt, 
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
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATDistanceMinPtSur * CATCreateDistanceMinLim(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
                                                              const CATMathPoint & iPt, 
                                                              const CATSurface *iSur,
                                                              const CATSurLimits * iSurLim,
                                                              CATBoolean iSearchOnBoundary = TRUE,
                                                              CATSkillValue iMode = BASIC);
/** 
* @deprecated V5R20 
* Use the signature with <tt>CATSurLimits</tt> as parameter.
* This signature has to be used with a <tt>SetLimits<tt>.
*/
ExportedByY300IINT CATDistanceMinPtSur * CATCreateDistanceMin(CATGeoFactory * iWhere,
                                                              CATSoftwareConfiguration *Config,
                                                              const CATMathPoint & iPt, 
                                                              const CATSurface *iSur,
                                                              CATBoolean iSearchOnBoundary = TRUE,
                                                              CATSkillValue iMode = BASIC); 


#endif
