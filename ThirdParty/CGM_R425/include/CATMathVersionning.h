//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2021
//=============================================================================
// Utilities for Mathematics framework versionning (framework architcture bypass)
//
// Allow easy versionning resolution at call
//
// (versionning values transmission from framework having access to versionning
//  software (GetCGMLevel()) and variables)
//
// For each versionning action
// (this stands for an external objet using a matheùatical object, assuming it belongs to a framework or module having access
//  to software configuration variables and tools (GetCGMLevel())
// - add an dedicated integer data member in CATYYYY.h
//   example
//   int _ActiveVers1;
//   int _ActiveVers2;
// - add the corresponding argument in the constructor or in a Set method
//   CATYYYY(previousargumentlist,
//           int iActiveVers1,
//           int iActiveVers2);
// - define a macro calling CATMathVersionningActive() macro with the software configuration and the real versionning variable
//   (CGM_Versionning_XXXX1)
//   example:
//   #define CATYYYYActiveVers1(iConfig)                       \
//    CATMathVersionningActive(iConfig, CGM_Versionning_XXXX1) //
//   #define CATYYYYActiveVers2(iConfig)                       \
//    CATMathVersionningActive(iConfig, CGM_Versionning_XXXX2) //
//
// - each calling program must define the argument value through this macro
//   example:
//   CATYYYY YYYY(previousargumentlist,
//                CATYYYYActiveVers1(Config),
//                CATYYYYActiveVers2(Config));
//
//  see sample of recommended use in CATMathLocalConnectChecker.h
//
//=============================================================================
// 21/12/21 NLD Creation
//              Non non non non MacLochard n'est pas mort car il frappe encore
// 14/01/22 NLD Documentation plus complète et adhésion à LesBonnesRecettesDuPereLochard
//=============================================================================

#ifndef CATMathVersionning_H
#define CATMathVersionning_H

#define CATMathVersionningActive(iConfig, Variable) ( (GetCGMLevel(iConfig, "") >= Variable) ? 1 : 0 )

#include "LesBonnesRecettesDuPereLochard.h"
LesBonnesRecettesDuPereLochard(CATMathVersionningActiveMacro, "Using CATMathVersionningActive macro for external versionning in Mathematics");
// see above in header definition

#endif
