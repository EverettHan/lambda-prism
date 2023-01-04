#ifndef UpgradeCheckDiagnostic_h
#define UpgradeCheckDiagnostic_h

#include <YP00IMPL.h>
#include "CATCGMOperator.h"

/*
* UpgradeCheckDiagnostic
*
* Replace ioDiagnostic by iOther if the latter represents a more serious diagnosis.
* Example:
*    UpgradeCheckDiagnostic(A, B);
* The value of A is replaced by the value of B if:
* A == CheckOK && B == CheckWarning
* or A == CheckOK && B == CheckError
* or A == CheckWarning && B == CheckError
*/
ExportedByYP00IMPL void UpgradeCheckDiagnostic(CATCGMOperator::CATCheckDiagnostic & ioDiagnostic, CATCGMOperator::CATCheckDiagnostic iOther);


#endif
