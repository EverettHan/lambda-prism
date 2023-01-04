#ifndef CATCreateIntersection_h
#define CATCreateIntersection_h

// COPYRIGHT DASSAULT SYSTEMES 2002
/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATMathConstant.h"

class CATGeoFactory;
class CATPointOnCurve; 
class CATPointOnSurface; 
class CATCartesianPoint; 
class CATCurve;
class CATPCurve;
class CATSurface;
class CATPlane;
class CATIntersectionCrvCrv;
class CATIntersectionCrvSur;
class CATIntersectionSurSur;
class CATIntersectionTriSur;
class CATSoftwareConfiguration;

/**
 * Creates an operator intersecting two curves.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iCurve1
 * The pointer to the first curve.
 * @param iCurve2
 * The pointer to the second curve.
 * <br><b>Warning</b><br>:
 * For performance reasons, the operator does not support having twice the same geometry in arguments.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT
CATIntersectionCrvCrv * CATCreateIntersection( CATGeoFactory *iWhere,
                                              CATSoftwareConfiguration * iConfig,
                                      CATCurve *iCurve1, CATCurve *iCurve2,
                                      CATSkillValue iMode=BASIC );


/**
 * Creates an operator intersecting a curve and a surface.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iCurve 
 * The pointer to the curve.
 * @param iSurface
 * The pointer to the surface.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT
CATIntersectionCrvSur * CATCreateIntersection( CATGeoFactory *iWhere,
                                           CATSoftwareConfiguration * iConfig,
				      CATCurve *iCurve, CATSurface *iSurface,
				      CATSkillValue  iMode=BASIC );



/**
 * Creates an operator intersecting two surfaces.
 * @param iWhere
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iSurface1
 * The pointer to the first surface.
 * @param iSurface2
 * The pointer to the second surface.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT
CATIntersectionSurSur * CATCreateIntersection( CATGeoFactory *iWhere,
              CATSoftwareConfiguration * iConfig,
					    CATSurface *iSurface1,
					    CATSurface *iSurface2,
					    CATSkillValue iMode=BASIC);


/**
 * @nodoc
 * Like CreateIntersection but requires a CATSoftwareConfiguration.
 */
ExportedByY300IINT
CATIntersectionSurSur * CATCreateIntersectionWithInits( CATGeoFactory *iWhere,
                                      CATSoftwareConfiguration * iConfig,
                                      CATSurface *iSurface1,
                                      CATSurface *iSurface2,
                                      CATSkillValue iMode=BASIC );


/**
 * @nodoc
 * Like CreateIntersection but requires a CATSoftwareConfiguration.
 */
ExportedByY300IINT
CATIntersectionSurSur * CATCreateIntersectionPlnSur(CATGeoFactory *iWhere,
                                                    CATSoftwareConfiguration * iConfig,
                                                 CATPlane *iPlane,
                                                 CATSurface *iSurface,
                                                 CATSkillValue iMode);
/**
 * @nodoc
 * Like CreateIntersection but requires a CATSoftwareConfiguration.
 */
// sdp 04avr03- j'ajoute l'argument CATSoftwareConfiguration malencontreusement omis
// a la creation de ce header. a priori sans consequence du point de vue CAA car
// c'est une fonction globale en nodoc
ExportedByY300IINT
CATIntersectionTriSur * CATCreateIntersectionTriSur(CATGeoFactory *iWhere,
                                                    CATSoftwareConfiguration * iConfig,
                                                 CATSurface *iSurface1,
                                                 CATSurface *iSurface2,
                                                 CATSurface *iSurface3,
                                                 CATSkillValue iMode=BASIC);


#endif
