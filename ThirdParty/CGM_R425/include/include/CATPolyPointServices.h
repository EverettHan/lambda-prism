// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointServices.h
//
//===================================================================
// January 2011  Creation: NDO
//===================================================================
#ifndef CATPolyPointServices_H
#define CATPolyPointServices_H

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

/** @file 
 * Global services about CATIPolyPoint.
 *
 * @see CATPolyServices.h
 * @see CATPolyCGMServices.h
*/

class CATIPolyPoint;

/** @file */


/** @name Miscellaneous Services
    @{ */

/**
 * Retrieves the CGM ID of a CATIPolyPoint.
 * @param iPolyPoint
 *   The point.
 * @param oID
 *   The returned ID of the point.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the ID is set,
 *   <li> <tt>S_FALSE</tt> if the point does not have an ID, or
 *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetID (const CATIPolyPoint& iPolyPoint, unsigned int& oID);

/**
 * Returns the size in bytes of the CATIPolyPoint and its layers.
 * The size of the dependent objects is not included.
 * @param iPolyPoint
 *   The input point.
 */
ExportedByPolyhedralUtilities unsigned int CATPolySizeOf (const CATIPolyPoint& iPolyPoint);

/**
 * Returns <tt>TRUE</tt> if the CATIPolyPoint shares its data with another CATIPolyPoint.
 * @param iPolyPoint1
 *   The first CATIPolyPoint.
 * @param iPolyPoint2
 *   The second CATIPolyPoint.
 */
ExportedByPolyhedralUtilities CATBoolean CATPolyShareDataWith (const CATIPolyPoint& iPolyPoint1, const CATIPolyPoint& iPolyPoint2);

/** @} */

#endif // !CATPolyPointServices_H
