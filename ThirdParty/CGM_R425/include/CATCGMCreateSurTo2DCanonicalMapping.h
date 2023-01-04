#ifndef CATCGMCreateSurTo2DCanonicalMapping_h_
#define CATCGMCreateSurTo2DCanonicalMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"

class CATGeoFactory;
class CATMathAxis;
class CATSoftwareConfiguration;
class CATICGMSurTo2DGlobalPlanarMapping;

/**
* Creates an object defining a global mapping between a plane and a 2D space.
* <br>The mapping corresponds to a projection onto a plane. This object is used
* by the @href CATICGMTopDevelop operator to define the input and output mappings. You
* have to <tt>Release</tt> this object after use.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iAxis
* The axis defining the plane. 
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMSurTo2DGlobalPlanarMapping *CATCGMCreatePlanarMapping(
  CATGeoFactory *iFactory,
  const CATMathAxis &iAxis);

/**
* Creates an object defining a global mapping between a plane and a 2D space.
* <br>The mapping corresponds to a projection onto a plane. This object is used
* by the @href CATTopDevelop operator to define the input and output mappings. You
* have to <tt>Release</tt> this object after use.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iAxis
* The axis defining the plane. 
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMSurTo2DGlobalPlanarMapping *CATCGMCreatePlanarMapping(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathAxis &iAxis);

#endif /* CATCGMCreateSurTo2DCanonicalMapping_h_ */
