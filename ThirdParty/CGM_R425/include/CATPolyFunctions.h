// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyFunctions.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// September 2005 Creation: ndo
//===================================================================
#ifndef CATPolyFunctions_h
#define CATPolyFunctions_h

#include "PolyFunctions.h"
#include "CATErrorDef.h" // Definition of HRESULT

class CAT3DBagRep;
class CATRep;


//
// DEPRECATED METHODS.
// DO NOT USE! SEE INSTEAD CATPolyVisuIntersectOper IN PolyhedralVisuOperators.
//


/*
 * Global boolean function (intersection) that operates directly on rep for use in R16SP2 without
 * changing dependencies of frameworks. Normals are automatically handled, and custom-reps that
 * may appear within the input bag-reps are not handled
 * @param iRepOperand1
 *   The rep representing the first operand.
 * @param iRepOperand2
 *   The rep representing the second operand.
 * @param oResultRep
 *   The result rep.
 */
extern "C" ExportedByPolyFunctions HRESULT RepIntersectionFunction 
(
   CAT3DBagRep* iRepOperand1,
   CAT3DBagRep* iRepOperand2,
   CATRep*& oResultRep
);


/*
 * Global boolean function (intersection) that operates directly on rep for use in R16SP2 without
 * changing dependencies of frameworks. Handling normal vectors and filtering out custom-reps
 * is customizable (1=enable, 0=disable)
 * @param iRepOperand1
 *   The rep representing the first operand.
 * @param iRepOperand2
 *   The rep representing the second operand.
 * @param iDisregardSurfaceVolumeFlag
 *   A flag to disregard whether the rep represents a surface or a volume.
 * @param iTakeCustomReps
 *   A flag to take into account custom reps.
 * @param iTakeNormals,
 *   A flag to take into account normals.
 * @param oResultRep
 *   The result rep.
 * @param oNbDomains
 *   The number of domains found from the intersection result.
 * @param oErrorID
 *   The error ID returned when the operator failed (see CATPolyBoolean::BooleanError for definition
 *   of the various errors.)  The NLS message associated to the error can be retrieved with the
 *   class CATPolyBooleanError.
 */
extern "C" ExportedByPolyFunctions HRESULT RepIntersectionCustomFunction 
(
   CAT3DBagRep* iRepOperand1,
   CAT3DBagRep* iRepOperand2,
   const int iDisregardSurfaceVolumeFlag,
   const int iTakeCustomReps,
   const int iTakeNormals,
   CATRep*& oResultRep,
   int& oNbDomains,
   int& oErrorID
);

#endif

