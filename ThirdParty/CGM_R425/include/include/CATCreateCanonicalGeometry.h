/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

/* -*-C++-*- */

#ifndef __CATCreateCanonicalGeometry_H__ 
#define __CATCreateCanonicalGeometry_H__ 

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// CATCreateCanonicalGeometry
//
// Author : HCN
//
// Description: 
//  Attempts to create a canonical geometry matching the supports of a list of cells.
//
//===========================================================================
// Dec. 04 Creation                                                     HCN
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"

#include "CATGeometryType.h"
#include "CATListOfCATCells.h"

class CATGeometry;
class CATTopData;

/**
* Attempts to create a canonical geometry matching the supports of a list of cells.
* @param ipTopData
* A pointer to the topological data for versionning informations.
* @param iListInputCells
* A list with pointers to all the cells which geometry must be analysed.
* @param iRequestedType
* A requested geometric type for the result.
* <dl><dt><tt>CATGeometryType</tt></dt><dd> The computed geometry may be of any supported type (see below).
*     <dt><tt>CATLineType</tt></dt><dd> Attempts to compute a geometry which provide a CATLine interface.
*     <dt><tt>CATCircleType</tt></dt><dd> Attempts to compute a geometry which provide a CATCircle interface.
*     <dt><tt>CATPlaneType</tt></dt><dd> Not supported yet
*</dl>
* @return
* A pointer to the canonical support if such a geometry could be calculated from the input cells.
* NULL otherwise.
* The returned CATGeometry provides an interface to one of the supported type (see iRequestedType parameter).
* But NO assumptions should be made to the real implementation type of the geometry.
*
* If not NULL, the returned geometry MUST be deleted by the caller using CATICGMCOntainer::Remove(...) method.
*/

ExportedByCATTopologicalObjects CATGeometry* CATCreateCanonicalGeometry(CATTopData*              ipTopData,
                                                                        const CATLISTP(CATCell)& iListInputCells,
                                                                        CATGeometricType         iRequestedType);
#endif






