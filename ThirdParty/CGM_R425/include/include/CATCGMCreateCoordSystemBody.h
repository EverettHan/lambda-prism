#ifndef CATCGMCreateCoordSystemBody_h
#define CATCGMCreateCoordSystemBody_h

// COPYRIGHT DASSAULT SYSTEMES 2017

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"

class CATGeoFactory;
class CATBody;
class CATMathAxis;
class CATTopData;

/**
 * Creates a body representing a coordinate system.
 * <br> This body is made of a shell, composed of 3 quater-infinite planes.
 * @param iFactory
 * The factory where the body is created.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iData</tt> 
 * is never filled.
 * @param iAxis
 * The mathematical definition of the axis.
 * @return 
 * The pointer to the created body. To be removed if needed by the <tt>remove</tt> method of the CATICGMContainer.
 */
ExportedByCATGMOperatorsInterfaces
CATBody *  CATCGMCreateCoordSystemBody(CATGeoFactory * iFactory, CATTopData * iData, CATMathAxis & iAxis);

#endif
