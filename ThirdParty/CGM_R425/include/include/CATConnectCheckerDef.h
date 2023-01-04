//=============================================================================
// CATConnectCheckerDef
//=============================================================================

#ifndef CATConnectCheckerDef_h
#define CATConnectCheckerDef_h

#include "CATDataType.h"

//////////////////////////////////////////////////////
// ConnectChecker generic commmands
//////////////////////////////////////////////////////

typedef CATLONG32 CATCommandOption;
#define CATConnectCheckerGap              1    // G0
#define CATConnectCheckerAngle            2    // G1
#define CATConnectCheckerCurvature        4    // G2
#define CATConnectCheckerOverLaps         8    // Overlap
#define CATConnectCheckerTgtAndNormGap    16   // G0 decomposition
#define CATConnectCheckerCurvatureComb    32   // G3

#define CONNECTCHECKERCRVSUR_UPTOG2       7
#define CONNECTCHECKERCRVCRV_UPTOG3       47
#define CONNECTCHECKERSURSUR_UPTOG3       63
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// ConnectChecker tolerances
//////////////////////////////////////////////////////
// DAD: Week 25/2007: Hard Tol Migration: Tolerances have been
// migrated to PrivateInterfaces\CATConnectCheckerTol.h
//const double CATConnectCheckerG0Tol       = 0.001;
//const double CATConnectCheckerG1Tol       = 8.72664626e-3; // 0.5 deg
//const double CATConnectCheckerG2Tol       = 0.05;          // 5 %

// DAD: Week 25/2007: Hard Tol Migration : !!! CAUTION !!! to be scaled case by case  before used
//const double CATConnectCheckerCRBMin      = 1.e-7; //@NumValidated  // old value: 8.e-9;
// DAD: Week 25/2007: Hard Tol Migration : !!! CAUTION !!! to be scaled case by case  before used
//const double CATConnectCheckerCRBMax      = 1.e+7; //@NumValidated // old value: 1.e+9;
// DAD: Week 25/2007: Hard Tol Migration : !!! CAUTION !!! to be scaled case by case before used
//const double CATConnectCheckerNullTangent = 1.e-9; //@NumValidated 

// First order finite differences steps
const double CATConnectCheckerStep = 1.e-4; //@NumValidated ( scaled when used )
const double CATConnectCheckerInvStep = 1.e+4; //@NumValidated ( scaled when used )
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
// ConnectChecker CrvUtilities options
//////////////////////////////////////////////////////
typedef CATLONG32 CATCrvUtilitiesOption;
#define CATCrvUtilitiesFirstDeriv              1
#define CATCrvUtilitiesSecondDeriv             2
#define CATCrvUtilitiesThirdDeriv              4

#define CRVUTILS_ALL_OPTIONS 7 // a incrementer lors du rajout d'options

// Max order of derivation
#define CATCrvUtilitiesMaxDeriv           4
//////////////////////////////////////////////////////

// Temporary: to be removed. Use only for debug (allows to activate V5R16 new specifications
// of Connect Checker Crv/Crv and Sur/Sur
#include "CATMathDebug.h"
static int CCNEWSPECS = (CATMathDebug::integerGetEnv("CCNEWSPECS") == 1) ? 1 : 0;


#endif
