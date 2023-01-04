#ifndef CATGeometricOperatorsDebugEnv_H
#define CATGeometricOperatorsDebugEnv_H

#include "CATGeometricOperators.h"

extern int  _CATConnectDecoupe;
extern ExportedByCATGeometricOperators int  _CATConnectC1;
extern int  _CATDiscontinuitiesUncheck;
extern int  _CATCheckHomotopy;

extern int  _CATProjMarchingDebug;

extern ExportedByCATGeometricOperators int  _CATConnectMarchingDebug   ;
extern ExportedByCATGeometricOperators int  _CATConnectInterpolDebug   ;
extern ExportedByCATGeometricOperators int  _CATConnectConstraintDebug ;
extern int  _CATIntersectionMarchingDebug ;
extern int _CATSurSurOptimizeArcs;
extern int  _CATIsoparInitDebug  ;
extern int  _CATEdgeCurveDebug   ;

extern int  _CATDebugReflectSign     ;
extern int  _CATDebugReflectMarching ;

extern int  _CATLayDownCrvSurDebug      ;
extern int  _CATLayDownCrvSurCheckInput ;

extern int _CATConnectOldCGMReplay ;

extern ExportedByCATGeometricOperators int _CATRollbackGeoOp_KLX;
extern ExportedByCATGeometricOperators int _CATFilletOptimizeArcs;

// sdp
extern int _CATExtrapolCurve_LinearMapping;
extern ExportedByCATGeometricOperators int _CATHomotopy_Extrapol;
extern ExportedByCATGeometricOperators int _CATSurSurTg_Debug;
extern ExportedByCATGeometricOperators int _CATSurSurWithInits_Canonical; // sdp 13feb04

extern int _CATRollback_ProjPtSurGen;

// FCX-PKC Approx : moved to CATFrFApproxDebugEnv.h

// FCX VariableFilletG1
extern ExportedByCATGeometricOperators int _CATConnectShowCenterCurve;
extern ExportedByCATGeometricOperators int _CATConnectShowMarchingPoints;

//CWM Interpolation explicite de la surface pour VariableFilletG1
extern ExportedByCATGeometricOperators int _CATFilletG1ExplicitInterpol;
extern ExportedByCATGeometricOperators int _CATFilletG1SmoothPlaneDir;

#endif
