#ifndef CATMathMinimizeXYParams_H
#define CATMathMinimizeXYParams_H

// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// External and internal parameters description for CATMathFunctionXY minimizers
//
//=============================================================================
// 21/07/11 NLD Création
//              - les options internes additives pour CATMathMinimizeXY et ses classes derivées
//                proviennent de l'implémentation de cette classe
//              - la liste des attributs et de leur utilisation
//                provient des implémentations de CATMathFunctionXY CATMathMinimizeXY et CATMathDirectMinimizeXY
//=============================================================================

// Additive option for minimizing (internal use: reserved for this class and its super classes)
// ------------------------------
//   **** A renommer et prefixer par CATMathMinimizeXY_     NLD200711
//    absolute minimum              0
//    all minima                   +1 (actif par défaut dans CATMathMinimizeXY, pas dans CATMathDirectMinimizerXY)
//    interior minima              +2
//    image lower than M           +4
//    interval method              +8
#define CATMathALLEXTREMA       1
#define CATMathINTERIOREXT      2
#define CATMathIMAGECOMPAREDEXT 4
#define CATMathINTERVALMETHOD   8
#define CATMathRELENTLESSLY    16

//-------------------------------------------------------------------
// gestion des attributs du Minimize de CATMathFunctionXY: (bilan au 21/07/11) NLD
//-------------------------------------------------------------------
#define CATMathMinimizeXYParams_ISwearToAlwaysKeepConsistencyWithDoc(subscriber) // tous les abonnés doivent maintenir cette documentation
//
// 1) attributs geres par CATMathFunctionXY::Minimize()
//    -------------------------------------------------
//    directement:
// "CATMathAttrTolObject" "CATMathAttrScaleOption"  "DirectMethod"
//    et indirectement via CATMathFunctionXY_DirtyAttributeScaling
// "TolForCst"  "AbsoluteTolerance"  "Tolerance"  "LimitValue"  "EpsRoot"

// 2) attributs geres par CATMathMinimizeXY::Minimize()
//    -------------------------------------------------
// "AbsoluteExtremum"  "InteriorExtremum"  "LimitValue"  "TolForCst"  "IntervalMethod"  "Relentlessly"
// "LocalMin_BugCorrected" "SpecialPoints"  "Tolerance"  "CATMathAttrScaleOption"
// "SamplingPointsX"  "SamplingPointsY"  "GridGlobalOptimum"  "GridLocalOptimum"

// 3) attributs geres par CATMathDirectMinimizeXY::Minimize()
//    -------------------------------------------------------
// "LimitValue"  "TolForCst"  "SamplingPointsX"  "SamplingPointsY"  "CATMathAttrTolObject"
// "CATMathAttrScaleOption"
// "AllExtrema" (new 21/07/11)
// (utilisés en interne mais non lus "AbsoluteExtremum" "BrentMethod" "BrentMethodTrueSampling" "SamplingPoints")
//
// 4) synthèse des utilisations (X si utilisation, O sinon)
//    -------------------------
//
//                              CATMathFunctionXY
//                              ! CATMathMinimizeXY
//                              ! ! CATMathDirectMinimizeXY
//                              ! ! !
// "CATMathAttrTolObject"       X O X (CATTolerance recu en argument par CATMathMinimizeXY)
//                                    (CATTolerance recu en argument par CATMathDirectMinimizerXY
//                                     dont l'interrogation de l'attribut "CATMathAttrTolObject" ne vient qu'en
//                                     supplément (historique) redefinir le cas échéant l'objet CATTolerance)
//                                    (cependant revoir certains constructeurs de classes derivées) ********
// "CATMathAttrScaleOption"     X X X (CATMathFunctionXY fait un rescaling d'apres cet attribut
//                                     CATMathMinimizeXY et CATMathDirectMinimizeXY interrogent seulement
//                                     le champ _OKReviewed)
// "DirectMethod"               X O O (CATMathFunctionXY active le switch vers CATMathDirectMinimizeXY)
// "TolForCst"                  X X X
// "Tolerance"                  X X O
// "LimitValue"                 X X X
// "AbsoluteExtremum"           O X O
// "InteriorExtremum"           O X O
// "IntervalMethod"             O X O
// "LocalMin_BugCorrected"      O X O (pertinent seulement pour CATMathMinimizeXY: bug spécifique)
// "SpecialPoints"              O X O (N.B voir leur re-scaling?)
// "SamplingPointsX"            O X X
// "SamplingPointsY"            O X X
// "GridGlobalOptimum"          O X O
// "GridLocalOptimum"           O X O
// "Relentlessly"               O X O (déclenche un rattrapage surdiscretisé en l'absence de solution)
//                                    (incompatible avec "GridGlobalOptimum" et "GridLocalOptimum")
// "AllExtrema"                 O O X (CATMathMinimizeXY:       non necessaire car c'est le défaut)
//                                    (CATMathDirectMinimizeXY: necessaire car le défaut utilise la meilleure init seulement) 
// non pertinents
// "EpsRoot"                    X O O (non utilise par les minimiseurs)
// "AbsoluteTolerance"          X O O (non utilise par les minimiseurs)
// "BrentMethod"                O O O
// "BrentMethodTrueSampling"    O O O
// "SamplingPoints              O O O
//
// 5) remarques:
//    ---------
//  Ensemble de paramètres incompatibles et priorités de ces paramètres:
//  A) 1) "GridGlobalOptimum" 2) "GridLocalOptimum" 3) "Relentlessly"

#endif
