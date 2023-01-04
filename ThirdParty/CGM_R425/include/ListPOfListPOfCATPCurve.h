// COPYRIGHT DASSAULT SYSTEMES  2000
// EDS

#ifndef __ListPOfListPOfCATPCurve_h__
#define __ListPOfListPOfCATPCurve_h__

#include "CATCGMLISTPP_Declare.h"
#include "ExportedByGeometricObjects.h"
#include "CATListOfCATPCurves.h"

// Should be in CATLsitOfCATPCurve.h, but that's a public interface, so put it here to avoid changing 
// that.
typedef CATLISTP(CATPCurve) ListPOfCATPCurve;

/** 
 * @collection CATLISTP(ListPOfCATPCurve)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
CATCGMLISTPP_DECLARE(ListPOfCATPCurve);

typedef CATLISTP(ListPOfCATPCurve) ListPOfListPOfCATPCurve;

/* Output does not currently build.
 * #include "CATCGMOutput.h"
 * class CATCGMOutput;
 * @nodoc
 * Writes the tags of all the PCurves of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
//ExportedByGeoemtricObjects CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATPCurve& iToWrite);

#endif
