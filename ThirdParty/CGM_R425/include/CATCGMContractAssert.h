#ifndef CATCGMContractAssert_h
#define CATCGMContractAssert_h

#include "CATMathematics.h"
#include "CATBoolean.h"

// use this method to turn on contracts
extern ExportedByCATMathematics void CATCGMContractSetChecks(CATBoolean iCheckState);

// Flag to indicate if contract checks are on.
extern ExportedByCATMathematics CATBoolean CATCGMContractChecksOn;
// Swap the line above with the line below to check for improper (non-const) uses of CGMContractChecksOn
// We can't declare it const in production code because the compiler notices it's const and doesn't assign any memory.
//extern ExportedByCATGMModelCmpInterfaces CATBoolean const CATCGMContractChecksOn;

// CGMContractBegin/CGMContractEnd
// allows developers to put extra validation code in that will not be executed 
// unless the global CATCGMContractChecksOn is set.
#define CATCGMContractBegin if ( CATCGMContractChecksOn ){
#define CATCGMContractEnd   }

void ExportedByCATMathematics CATCGMAssertForContractChecks( CATBoolean condition, const char* message, const char* filename, int linenumber );

// these only throw if the environment variable is set.
// no guarantee the message is printed anywhere.
#define CATCGMContractAssert( __condition ) if ( CATCGMContractChecksOn ){ CATCGMAssertForContractChecks( __condition, NULL, __FILE__,__LINE__); }
#define CATCGMContractAssertMessage( __condition,__message ) if ( CATCGMContractChecksOn ){ CATCGMAssertForContractChecks( __condition, __message, __FILE__,__LINE__); }

#endif
