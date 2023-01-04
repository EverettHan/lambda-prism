/* -*-c++-*- */
#ifndef CATGeoClnIDs_H_
#define CATGeoClnIDs_H_
//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//============================================================================
//
//    - Definition of all available CGM cleaner check rules.
//    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//    NE JAMAIS INSTANCIER CETTE CLASSE !!!!!!!!!!!!!!!!!!!!!!!
//    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//
//============================================================================
// Mar. 02  Creation                                                     HCN
// Jul. 02  Unextrapolation rule                                         HCN
// Aug. 02  Fat vertices rule for factory                                HCN
// Oct. 02  Fat vertices rule for body                                   HCN
// Dec. 02  TAB_GEOCLEAN_RULE_DEFS et methodes dediees
//          regle EdgePOECDifferentCurve EPC_1,
//          regles FEX_1 et FEX_2 (a la place de UEX_1 et UEX_2)         HCN
// Jan. 03  Reordonnancement de FEX_? et FVX_?
//          regles FGM_1 et FGM_2,
//          CATCGMRuleDEF::_RuleDomain                                   HCN
// Feb. 03  CylinderSurfaceOverLimits                                    HCN
// May. 03  SurfaceClosureError                                          HCN
// Jun. 03  PCurveOutSideSupport                                         RHA
// Jun. 03  POECCurveNotInEdgeCurve                                      AJM
// Jul. 03  CATGeoClnPOECSpecParamOutsideSpecCurve                       AJD
// Jul. 03  CheckTabDefIsOK(...) and _CheckTabDefIsOKDone                HCN
// Jul. 03  FatEdgesForFactory, FatEdgesForBody                          HCN
// Sep. 03  CurveParamOutsideLimits                                      AJM
// Sep. 03  IntCurveGapExceedingResolution                               AJM
// Oct. 03  CheckC1Continuity                                            PKC
// Nov. 03  CheckSetOfPointsMappingLimits                                AJM
// Dec. 03  MacroPointInternalGap                                        FDN
// Dec. 03  FATEdgeForBodyCompleted                                      FDN
// Jan. 04  CurveLimitsUsefulOutsideMax                                  AJM
// Mar. 04  Unification de CATCGMRuleDef et CATCGMRuleDEF                FDN
// Mar. 04  Numerotation stable et figee des RuleID                      FDN  
// Apr. 04  Check Geometry Continuity is Valid for V5                    RHA/PKC
// Apr. 04  _CheckTabDefIsOKDone, _pRankToId                             HCN
// Dec. 04  CheckEdgeCurveIdenticalPCurves                               BQJ 
// May. 05  CATGeoClnCheckEdgeCurveGap100R                               BQJ
// Jun. 05  CATGeoClnINFCheckMathRepSurfaceInMI                          BQJ
// Autumn 18 Disable CGMCleaner rules not CAA exposed                    F4Z
//============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"
#include "CATMapVoidToVoid.h"

#ifndef NULL
  #define NULL 0
#endif

class CATCGMRuleDef;

class ExportedByGeometricObjects CATGeoClnIDs
{
public:


  enum RuleID
  { 
    // Warning : The purpose of those numbers is only to identify the rules.
    //           It is NOT used to define the order of the rules tables.
    //           NEVER CHANGE THOSE VALUES
    // REQUIRED : Range of the numbers is [ 0 , 32767 ]

    UndefinedRule = 0,

    // Topological rules (id 1 to 499)
    //================================
    ResidualTouchedCells            =  10, // TRE_1, CATGeoClnTouchedResiduels
    AmbiguousEdgeSharpness          =  20, // ESH_1, CATGeoClnEdgeSharpness
    //VertexLyingOnCorruption         =  30, // LYO_1, CATGeoClnVertexLyingOn
    //EdgeLyingOnCorruption           =  31, // LYO_2, CATGeoClnEdgeLyingOn
    //BadStoredBodyBoundingBox        =  40, // BOB_2, CATGeoClnBodyBoundingBox
    FaceAutoIntersection            =  50, // FAI_1, CATGeoClnFaceAutoIntersection
    VertexConfusionOnGeometry       =  60, // CFG_1, CATGeoClnVertexConfusionOnGeometry
    EdgeConfusionOnGeometry         =  61, // CFG_2, CATGeoClnEdgeConfusionOnGeometry

    // Check FAT...
    FatGeometriesForFactory         = 100, // FGM_1, CATGeoClnFatGeometries
    FatGeometriesForBody            = 101, // FGM_2, CATGeoClnFatGeometries

    FatVerticesForFactory           = 110, // FVX_1, CATGeoClnFatVertex
    FatVerticesForBody              = 111, // FVX_2, CATGeoClnFatVertex

    FatEdgesForFactory              = 120, // FED_1, CATGeoClnFatEdge
    FatEdgesForBody                 = 121, // FED_2, CATGeoClnFatEdge
    FatEdgesForBodyCompleted        = 122, // FED_3, CATGeoClnFatEdgeCompleted

    FatExtrapolForFactory           = 130, // FEX_1, CATGeoClnFatExtrapol
    FatExtrapolForBody              = 131, // FEX_2, CATGeoClnFatExtrapol

    //EdgePOECDifferentCurve          = 200, // EPC_0,
    //CylinderSurfaceOverLimits       = 210, // CSL_0,
    SurfaceClosureError             = 220, // SCE_0, CATGeoClnSurfaceClosure
    ClosedWireFewerEdges            = 230, // CWE_1, CATGeoClnClosedWireFewerEdges
    //INFCheckBodyInModelSize         = 240, // INF_3, CATGeoClnINFCheckBodyInModelSize
    //CheckTopologicalEdgeLength      = 250, // TEL_1, CATGeoClnCheckTopologicalEdgeLength
    //OnlyOneEdgeInFullLoop           = 260, // EFL_0, CATGeoClnOnlyOneEdgeInFullLoop


    // Geometrical rules (id >= 500)
    //==============================
    //BadStoredBoundingBox            = 500, // BOB_1, CATGeoClnBoundingBox
    PCurveOutSideSupport0           = 510, // PSS_0, CATGeoClnPCurveOutSideSupport
    PCurveOutSideSupport1           = 511, // PSS_1, CATGeoClnPCurveOutSideSupport
    POECCurveNotInEdgeCurve         = 520, // PCE_1, CATGeoClnPOECCurveInEC
    POECSpecParamOutsideSpecCurve   = 530, // PPO_1, CATGeoClnPOECSpecParamOutsideSpecCurve
    CurveParamOutsideLimits         = 540, // CPO_1, CATGeoClnCurveParamOutsideLimits
    IntCurveGapExceedingResolution  = 550, // ICG_1, CATGeoClnIntCurveGapExceedingResolution
    CheckC1ContinuityCurve          = 560, // CCC_0, CATGeoClnCheckC1ContinuityCurve 
    CheckC1ContinuitySurface        = 561, // CCC_1, CATGeoClnCheckC1ContinuitySurface 
    CheckSetOfPointsMappingLimits   = 570, // SPM_1, CATGeoClnCheckSetOfPointsMappingLimits
    MacroPointInternalGap           = 580, // MPG_1, CATGeoClnMacroPointInternalGap
    CurveLimitsUsefulOutsideMax     = 590, // ULO_1, CATGeoClnCurveLimitsUsefulOutsideMax
    CheckGeometryContinuityCurve    = 600, // CGC_0, CATGeoClnCheckGeometryContinuityCurve 
    CheckGeometryContinuitySurface  = 601, // CGC_1, CATGeoClnCheckGeometryContinuitySurface 
    INFCheckOriginInModelSize1      = 610, // INF_1, CATGeoClnINFCheckOriginInModelSize
    INFCheckOriginInModelSize2      = 611, // INF_1, CATGeoClnINFCheckOriginInModelSize
    INFCheckMathRepInModelInfinite1 = 612, // INF_2, CATGeoClnINFCheckMathRepInModelInfinite
    INFCheckMathRepInModelInfinite2 = 613, // INF_2, CATGeoClnINFCheckMathRepInModelInfinite
    //CheckEdgeCurveGap               = 620, // ECG_1, CATGeoClnCheckEdgeCurveGap
    //CheckEdgeCurveGap100R           = 621, // ECG_2, CATGeoClnCheckEdgeCurveGap100R
    //CheckSmallGeometryCurve         = 630, // CSG_1, CATGeoClnCheckSmallGeometryCurve
    //CheckSmallGeometrySurface       = 631, // CSG_2, CATGeoClnCheckSmallGeometrySurface
    CheckEdgeCurveIdenticalPCurves  = 640, // EIP_1, CATGeoClnCheckEdgeCurveIdenticalPCurves
    //INFCheckElemSurfaceInMI1        = 650, // INF_5, CATGeoClnINFCheckElemSurfaceInMI
    //INFCheckElemSurfaceInMI2        = 651, // INF_5, CATGeoClnINFCheckElemSurfaceInMI
    //INFCheckElemSurfaceInMI3        = 652, // INF_5, CATGeoClnINFCheckElemSurfaceInMI
    //INFCheckElemSurfaceInMI4        = 653 // INF_5, CATGeoClnINFCheckElemSurfaceInMI
    // Never greater than           32767 !!!!!!!!!!!!!!
  };

  // Constructor and destructor
  CATGeoClnIDs(); // Ne jamais instancier
  CATGeoClnIDs(CATBoolean Attention); // Ne jamais instancier
  ~CATGeoClnIDs();

  static void CheckTabDefIsOK();

  // UndefinedRule is not taken in account
  static int GetNbRules(CATBoolean iWithCheck = TRUE);

  // GetRule(0) = UndefinedRule
  // GetRule(1) = ResidualTouchedCells
  // ...
  static CATGeoClnIDs::RuleID GetRule(int iRank, CATBoolean iWithCheck = TRUE);

  static int GetRankInTab(CATGeoClnIDs::RuleID iRule);

  static CATCGMRuleDef* GetRuleDefinition(CATGeoClnIDs::RuleID iRule);

  static CATCGMRuleDef* GetRuleDefinitionInTab(int iRank, CATBoolean iWithCheck = TRUE);

  static void InitOneRule(CATCGMRuleDef * iRule);

  static char* GetCode(CATGeoClnIDs::RuleID iRule);

  static char* GetCheckupCode(CATGeoClnIDs::RuleID iRule);

  static CATGeoClnIDs::RuleID GetRule(const char* ipCode);

  static char* GetDescription(CATGeoClnIDs::RuleID iRule);

  static CATGeometricType GetTargetType(CATGeoClnIDs::RuleID iRule);

  static CATGeoClnIDs::RuleID GetPreviousRule(CATGeoClnIDs::RuleID iRule);

  static char* GetRuleDomainName(CATGeoClnIDs::RuleID iRule);

  static CATBoolean    _CleanMyselfCleanerTable; // nettoyage du tableau statique des regles cleaner par this (TRUE) ou CATCGMCleaner (FALSE)

  static CATBoolean        _CheckTabDefIsOKDone;
  static CATMapVoidToVoid* _pRankToId;
  static int               _CleanAtExit();
  static short             _0Init_1AtExit_2Done;


  static CATCGMRuleDef ** GetTAB_GEOCLEAN_RULE_DEFS(short iWithCleanOrNew, int * ioNbRules = 0);
};

#endif
