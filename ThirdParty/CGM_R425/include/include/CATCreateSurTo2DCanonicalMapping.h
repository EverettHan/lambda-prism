#ifndef CATCreateCATSurTo2DCanonicalMapping_H 
#define CATCreateCATSurTo2DCanonicalMapping_H 

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */

#include "Connect.h" 
#include "CreateSurTo2DCanonicalMapping.h"

class CATGeoFactory;
class CATMathAxis;  
class CATSurTo2DGlobalPlanarMapping;
class CATSoftwareConfiguration;
/**
* Creates an object defining a global mapping between a plane and a 2D space.
* <br>The mapping corresponds to a projection onto a plane. This object is used
* by the @href CATTopDevelop operator to define the input and output mappings. You
* have to <tt>delete</tt> this object after use.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iAxis
* The axis defining the plane. 
* @return
* The pointer to the created operator. To delete with the usual C++ delete operator after use.
*/
ExportedByConnect
CATSurTo2DGlobalPlanarMapping * CATCreatePlanarMapping( CATGeoFactory *iFactory,
                                                    CATSoftwareConfiguration *iConfig,
                                                    const CATMathAxis& iAxis );

#endif


