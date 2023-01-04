#ifndef CATCivilCurveArchiTEMP
#define CATCivilCurveArchiTEMP

// Q48 07/10/20: Small file to easily roll back the interface / export
//               changes in case of build errors. Once all is delivered
//               and built against BSF, we can remove the code and
//               this file

#define Q48_Civil_KeepOldCreate_PtPtDir // Q48 29/01/21: required for CATCDSGMInfra\CDSCurve.m\src\CATCSTransitionCurve2DImp.cpp

#define Q48_RemoveSetDomain
//#define Q48_RemoveGetMaxDomain  // Q48 29/09/21: required for CATCDSGMInfra\CDSCurve.m\src\CATCSTransitionCurve2DImp.cpp
//#define Q48_RemoveGetCurDomain  // Q48 29/09/21: required for CATCivilEngAlignmentModeler\CATCivilEngAlignmentModeler.m\src\CATECegAlignmentSketchFactory.cpp
#define Q48_RemoveAngleOptions

#define Q48_Civil_Keep_FixedParameterCSC
#undef Q48_Civil_Keep_FixedParameterCSC  // Q48 14/09/22 (never completed or used)

//#define Q48_Civil_KeepDeprecatedTSCST
//#undef Q48_Civil_KeepDeprecatedTSCST // Q48 23/12/21

#endif // CATCivilCurveArchiTEMP
