#ifndef CreateCATSurTo2DCanonicalMapping_H 
#define CreateCATSurTo2DCanonicalMapping_H 

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */

#include "Connect.h"
#include "CATIACGMLevel.h"

class CATGeoFactory;
class CATMathAxis;  
class CATSurTo2DGlobalPlanarMapping;
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
CATSurTo2DGlobalPlanarMapping * CreatePlanarMapping( CATGeoFactory *iFactory,
#ifdef CATIACGMR217CAA
											  const CATMathAxis & iAxis );
#else
											  const CATMathAxis iAxis );
#endif

/** @nodoc*/
ExportedByConnect
void RemoveMapping(CATSurTo2DGlobalPlanarMapping *&iMappingToRemove); 

#endif


