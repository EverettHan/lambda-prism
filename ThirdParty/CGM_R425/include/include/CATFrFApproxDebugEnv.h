//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// Variables de DEBUG de l'approx
//=============================================================================

#ifndef CATFrFApproxDebugEnv_H
#define CATFrFApproxDebugEnv_H

//extern int _CATApproxChebychevApproximation;
//extern int _CATApproxDoubleInsertionV2;
//extern int _CATApproxDiscontinuityFiltering;
//extern int _CATApproxNewCutChoice;
//extern int _CATApproxIsoparSwap;
extern int _CATApproxDebug;                 // 1 2 3 : display 3 levels of traces (with the prefix "FCX> ")
extern int _CATApproxDebugCheckQuality;     // Check max deviation (on 50*50 points), if KO displays "FCX> CheckQualityKO"
extern int _CATApproxDebugTol1Res;               // Force the approx tolerance to 1*resolution
extern int _CATApproxDebugSegmentsOnBorder;      // Optimize patches creation near borders of the surface
extern int _CATApproxDebugCutOnDiscontinuities;  // Insert cuts on discontinuities (instead of creating regularization patches around discontinuities) 
extern int _CATApproxDebugCheapInterpol;         // CheapInterpol method used in CATFrFSimpleApprox Perform
extern int _CATApproxDebugNbGaussPointsChange;   // Reduce the number of points or reffine around the discontinuities
extern int _CATApproxDebugCleanArcs;             // Arcs cleaner post-treatment
extern int _CATApproxDebugComputeNbIsopares;     // Optimize the number of isopares for the second approx
extern int _CATApproxDebugChooseSecondIsopar;    // To choose the isoparam of second approx more efficiently
//extern int _CATApproxOldMode;               // Approx old mode
//extern int _CATApproxNewMode;               // Approx new mode
extern int _CATApproxDebugVersion;               // Approx version
extern int _CATApproxDebugCleanRegulArcs;        // Regularization arcs can be merged by the cleaner
extern int _CATApproxDebugMoreGaussPoints;       // 20 Gauss point instead of 10
extern int _CATApproxDebugPlotLaw;                     // ajoute aux traces les valeurs de la loi relle et de la loi approchee


void ApproxSetEnvMode();

#endif
