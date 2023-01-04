#ifndef CATAdvancedMathematicsDebugEnv_H
#define CATAdvancedMathematicsDebugEnv_H

#include "CATAdvancedMathematics.h"

extern int _CATCGMInterpolDebug       ; 
extern int _CATCGMInterpolPrecision   ; 
extern int _CATCGMInterpolClean       ; 
extern int _CATCGMInterpolC1          ; 
extern int _CATCGMInterpolCheck       ; 
extern int _CATMarchingRollback ;
extern int _CATMarchingImprovements ;
extern ExportedByCATAdvancedMathematics int _CATMarchingDebug ; //jsx 04/2015 ajout exported by pour usage dans geo
extern int _CATRollback_SolverPerfo; // sdp 03jul03
extern  ExportedByCATAdvancedMathematics int _CATNewThirdDeriv ;
extern ExportedByCATAdvancedMathematics int _CATRollback_System3x3s; // sdp 21oct03
extern ExportedByCATAdvancedMathematics int _CATCGM_Math2GeoDebugInfo; //jsx 04042019 pour enregistrer a la demande depuis les maths

#endif
