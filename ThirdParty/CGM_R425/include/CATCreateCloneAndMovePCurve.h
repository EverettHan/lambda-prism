#ifndef CATCreateCloneAndMovePCurve_H 
#define CATCreateCloneAndMovePCurve_H 

#include "CATGMModelInterfaces.h"

class CATCloneAndMovePCurve;
class CATSoftwareConfiguration;
class CATPCurve;
class CATCrvLimits;
class CATSurface;
class CATGeoFactory;

/**
 * @nodoc
 * @param iSoftwareConfiguration
 * @param iPCurve
 * The original PCurve
 * @param iLimits
 * The limits on iPCurve to take into account to create the new PCurve.
 * @param iNewSupport
 * The surface on which the new PCurve will be created
 * @param iTolerance
 * If an approximation is needed, it will be performed at this tolerance. 
 * By default iTolerance is specified as a 2D tolerance;
 * To specify it as a 3D tolerance, call the method: SetDeviationComputationIn3D
 */

ExportedByCATGMModelInterfaces
CATCloneAndMovePCurve * CATCreateCloneAndMovePCurve(CATSoftwareConfiguration * iSoftwareConfiguration, 
											                              CATPCurve * iPCurve,
                                                    const CATCrvLimits & iLimits,
											                              CATSurface * iNewSupport,
                                                    double iTolerance);

/**
 * @nodoc
 * @param iFactory
 * @param iSoftwareConfiguration
 * @param iPCurve
 * The original PCurve
 * @param iLimits
 * The limits on iPCurve to take into account to create the new PCurve.
 * @param iNewSupport
 * The surface on which the new PCurve will be created
 * @param iTolerance
 * If an approximation is needed, it will be performed at this tolerance. 
 * By default iTolerance is specified as a 2D tolerance;
 * To specify it as a 3D tolerance, call the method: SetDeviationComputationIn3D
 */
ExportedByCATGMModelInterfaces
CATCloneAndMovePCurve * CATCreateCloneAndMovePCurve(CATGeoFactory * iFactory, 
													                          CATSoftwareConfiguration * iSoftwareConfiguration, 
											                              CATPCurve * iPCurve,
                                                    const CATCrvLimits & iLimits,
											                              CATSurface * iNewSupport,
                                                    double iTolerance);


#endif


