#ifndef CATCreateCoordSystemBody_H
#define CATCreateCoordSystemBody_H

// COPYRIGHT DASSAULT SYSTEMES  1999
#include <stdlib.h>
class CATGeoFactory;
class CATBody;
class CATMathAxis;
class CATCGMJournalList;
class CATTopData;
#include "CATGMOperatorsInterfaces.h"

/**
 * Creates a body representing a coordinate system.
 * <br> This body is made of a shell, composed of 3 quater-infinite planes. It points to a CATCGMAttribute
 * <tt>UAIDName(CATCGMCoordSystemBodyAttr)</tt>.
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
CATBody *  CATCreateCoordSystemBody(CATGeoFactory * iFactory, CATTopData* iData,CATMathAxis & iAxis);

/**
 * Deprecated. Use the signature with CATTopData.
 */
ExportedByCATGMOperatorsInterfaces
CATBody *  CATCreateCoordSystemBody(CATGeoFactory * iFactory, CATMathAxis & iAxis);

#endif
