//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006
//=============================================================================
//
// CATBendDefines :
//   Contains all constants and diagnosis required by CATBendOperator.
//
//=============================================================================
// March 06 Creation												                               CQI
//=============================================================================

#ifndef CATBendDefines_H 
#define CATBendDefines_H 

#include "CATDataType.h"

typedef  CATLONG32 CATBendDiagnostic;

#define   CATBendUndefined                    -1 // Undefined failure.
#define   CATBendOK                            0 // Success.
#define   CATBendInvalidInput                  1 // Failure because of invalid inputs.
#define   CATBendSolverFailure                 2 // Solver reconvergence failure (ill conditionned, no solution, etc.).
#define   CATBendNoSolution1                   4 // Parallel lines with same directions and distance strictly inferior to 4 radius.
#define   CATBendNoSolution2                   8 // Confused lines with opposite directions.
#define   CATBendNoSolution3                  16 // Parallel lines with opposite directions far from less than 2 radius.

//
// TO BE FILLED OUT IF NEEDED
//

#endif

