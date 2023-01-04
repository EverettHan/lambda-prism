//===================================================================
// COPYRIGHT Dassault Systemes 2017/02/22
//===================================================================
// CATCivilCurveDef.h
//===================================================================
//
// Usage notes: Defines useful for civil curve operator input.
//
//===================================================================
// Historic:
// 22/02/17 F1Z : Creation
// 30/07/18 KJD : Addition of the new element CATCivilCurve_Catenary in the enum CATCivilCurveType
//                Addition of the new enums CATCivilTransitionType, CATCivilTransitionInfoType
// 13/03/20 F4E : Add new enums CATCivilInput_ClockOrientation and CATCivilCurve_CircleCircleTransition
// 17/04/20 F4E : Add new enum CATCivilRunStatus
//                Change CATCivilCurve_CircleCircleTransition field names for generalization
// 16/10/20 Q48 : Move CATCivilRunStatus to namespace (avoid clash with Draft enum)
// 15/01/21 Q48 : Add to CATCivilCurveType enum for new transition types
// 27/05/21 Q48 : Add UNKNOWN to orientation
//===================================================================

#ifndef CATCivilCurveDef_H
#define CATCivilCurveDef_H

namespace CATCivilCurveDef
{
  typedef enum CATCivilRunStatus { OK                 = 0,
                                   ComputationIssue   = 1,
                                   BadInput           = 2,
                                   InputConsistence   = 3,
                                   OptionNotRespected = 4,
                                   ReducedToAPoint    = 5} CATCivilRunStatus;

  //jsx 05/01/2021 erreur compil freestyleresources
#ifdef LENGTH
#define REDO_LENGTH
#undef LENGTH
#endif

  typedef enum ParamType
  {
    UNDEF    = -1,
    A2       =  0,
    RADIUS   =  1,
    LENGTH   =  2,//jsx 05/01/2021 erreur compil freestyleresources
    ANGLE    =  3,
    SHIFTING =  4,
    DOM      =  5
  } ParamType;

#ifdef REDO_LENGTH
#define LENGTH
#endif
};

// Do not insert new entries in the list - this data
// is streamed in CGMReplay. Please only append (before
// the MaxTypeIndex entry)
enum CATCivilCurveType
{
   CATCivilCurve_Unknown          = -1,
   CATCivilCurve_Parabola_2  , // =  0
   CATCivilCurve_Parabola_3  , // =  1
   CATCivilCurve_Clothoide   , // =  2
   CATCivilCurve_Bloss       , // =  3
   CATCivilCurve_Cosinusoidal, // =  4
   CATCivilCurve_Sinusoidal,   // =  5
   CATCivilCurve_Catenary,     // =  6

   CATCivilCurve_SineHalfWavelengthDiminishingTangent, // = 7  (15/01/21 Q48: added)
   CATCivilCurve_ParabolaJP_3,                         // = 8  (15/01/21 Q48: added)
   CATCivilCurve_ParabolsNSW_3,                        // = 9  (15/01/21 Q48: added)
   CATCivilCurve_Quadratic,                            // = 10 (15/01/21 Q48: added)
   CATCivilCurve_BiQuadratic,                          // = 11 (08/11/21 Q48: not to be used)
   CATCivilCurve_Lemniscate,                           // = 12 (15/01/21 Q48: added)
   CATCivilCurve_Viennesebend,                         // = 13 (15/01/21 Q48: added)
   CATCivilCurve_Helmert,                              // = 14 (08/11/21 Q48: added)

   CATCivilCurve_MaxTypeIndex
};

/**
* Defines input curve orientation (e.g. needed for curve creation in between two circles)
*/
enum CATCivilInput_ClockOrientation 
{
  CATCivil_UNKNOWN_ORIENTATION = -1,
  CATCivil_CLOCKWISE,
  CATCivil_ANTI_CLOCKWISE
};


/**
* Defines the transition type in between two circles
*/
enum CATCivilCurve_CircleCircleTransition
{
  CATCivil_INCLUDED_CIRCLES,
  CATCivil_EXTERNAL_CIRCLES
};


enum CATCivilCurveRecognizerMode
{
   CATCivilCurveRecognizer_Internal    = 0,
   CATCivilCurveRecognizer_External // = 1
};

enum CATCivilTransitionType
{
   CATCivilTransition_None       = 0,
   CATCivilTransition_LineLine      ,// = 1
   CATCivilTransition_LineCircleLine // = 2
};

enum CATCivilTransitionInfoType
{
   CATCivilTransitionInfo_NoType   = 0,
   CATCivilTransitionInfo_R           , // = 1
   CATCivilTransitionInfo_L1          , // = 2
   CATCivilTransitionInfo_L2          , // = 3
   CATCivilTransitionInfo_CurvilinearL, // = 4
   CATCivilTransitionInfo_Chord       , // = 5
   CATCivilTransitionInfo_HorizontalL , // = 6
   CATCivilTransitionInfo_K             // = 7
};

#endif

