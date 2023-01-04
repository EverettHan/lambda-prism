//===================================================================
// COPYRIGHT Dassault Systemes 2017/02/21
//===================================================================
// CATExtractCivilCurveProperties.h
// Header definition of class CATExtractCivilCurveProperties
//===================================================================
//
// Usage notes: Civil Curve Extration methods
//
//===================================================================
// Historic:
// 14/03/17 F1Z : Creation.
// 13/04/17 F1Z : for parabola_2
// 28/11/17 F1Z : from end information
// 17/01/20 F4E : Add catenary properties extraction method
// 21/02/20 F4E : add of catenary coef as output of CATExtractCivilCatenaryProperties for CGMReplay and Debug
// 13/03/20 F4E : separate in distinct file
// 17/04/20 F4E : Migration CATClothoideParam -> CATCivilHorizParam + CATCivilHorizCurveData
//                Add of output param in ExtractCivilCurveProperties
//                Remove useless exports
// 10/09/21 Q48 : Remove (or move) unused (or single useage) global functions
// DD/MM/YY
//===================================================================
#ifndef CATExtractCivilCurveProperties_H
#define CATExtractCivilCurveProperties_H

// ExportedBy
#include "GeoAdvCurves.h"

// System 
#include "CATErrorDef.h"
#include "CATBoolean.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"

class CATSoftwareConfiguration;
class CATTolerance;
class CAT2DCurveEvaluator;
class CATMathPoint2D;         
class CATMathVector2D;
class CATMathInterval;
class CATCivilHorizCurveData;

// ============================================================================================================================= //
//                                            CIVIL CURVE EVALUTOR EXTRACTION METHODS                                            //
// ============================================================================================================================= //

///**
//* Extract the civil curve properties
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing a 2D parabola of degree 2.
//* @param oApex
//* The position of the parabola apex.
//* @param oDir
//* The tangent of the parabola at the apex.
//* @param oFocalDistance
//* The signed distance from the focal point to the apex.
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//ExportedByGeoAdvCurves HRESULT CATExtractParabolaConicProperties(      CATSoftwareConfiguration * iConfig       ,
//                                                                 const CATTolerance             & iTolerance    ,
//                                                                 const CAT2DCurveEvaluator      & iEvaluator    ,
//                                                                       CATMathPoint2D           & oApex         ,
//                                                                       CATMathVector2D          & oDir          ,
//                                                                       double                   & oFocalDistance);


///**
//* Extract the starting civil curve geometric information
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing the civil curve.
//* @param oPt
//* The characteristic point (inflexion, summit, ...)
//* @param oDir
//* The direction at characteristic point
//* @param
//* The direction of the civil curve center of curvature at characteristic point
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//HRESULT CATExtractCivilCurveCharactPoint(      CATSoftwareConfiguration * iConfig    ,
//                                         const CATTolerance             & iTolerance ,
//                                         const CAT2DCurveEvaluator      & iEvaluator ,
//                                               CATMathPoint2D           & oPt        ,
//                                               CATMathVector2D          & oDir       ,
//                                               CATMathVector2D          & oDirOrtho  );

///**
//* Extract the civil curve type
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing the civil curve.
//* @param oCivilType
//* The civil type of iEvaluator
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//HRESULT CATExtractCivilCurveType         (      CATSoftwareConfiguration * iConfig    ,
//                                      const CATTolerance             & iTolerance ,
//                                      const CAT2DCurveEvaluator      & iEvaluator ,
//                                            CATCivilCurveType        & oCivilType );

///**
//* Extract the civil curve properties
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing the civil curve.
//* @Param iAccurate
//* TRUE if the properties extracted should be accurate or the approximation version (similar to CATCreateCivilCurveEvaluator iAccurate parameter).
//* @param oMinLengthParam, oMaxLengthParam
//* The civil curve curvilinear min and max 
//* @param oRadius
//* The civil curve radius at end point.
//* @param oFinalAngle
//* The civil curve final angle (angle between orthoDir and final normal)
//* @param oShifting
//* The civil curve shifting (distance curvature circle to starting line)
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//HRESULT CATExtractCivilCurveProperties   (      CATSoftwareConfiguration * iConfig     ,
//                                      const CATTolerance             & iTolerance      ,
//                                      const CAT2DCurveEvaluator      & iEvaluator      ,
//                                      const CATBoolean                 iAccurate       ,
//                                            double                   & oMinLengthParam ,
//                                            double                   & oMaxLengthParam ,
//                                            double                   & oRadius         ,
//                                            double                   & oFinalAngle     ,
//                                            double                   & oShifting       );
//
///**
//* Extract the civil curve properties. The properties returned are the same the one used to build the evaluator.
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing the civil curve.
//* @param oMinLengthParam, oMaxLengthParam
//* The civil curve curvilinear min and max (the difference gives the length).
//* @param oRadius
//* The civil curve radius at end point.
//* @param oFinalAngle
//* The civil curve final angle (angle between orthoDir and final normal)
//* @param oShifting
//* The civil curve shifting (distance curvature circle to starting line)
//* @Param iAccurate
//* TRUE if the properties extracted are accurate or the approximation version (similar to CATCreateCivilCurveEvaluator iAccurate parameter).
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//ExportedByGeoAdvCurves HRESULT CATExtractCivilCurveProperties   (      CATSoftwareConfiguration * iConfig            ,
//                                                                 const CATTolerance             & iTolerance         ,
//                                                                 const CAT2DCurveEvaluator      & iEvaluator         ,
//                                                                       double                   & oMinLengthParam    ,
//                                                                       double                   & oMaxLengthParam    ,
//                                                                       double                   & oRadius            ,
//                                                                       double                   & oFinalAngle        ,
//                                                                       double                   & oShifting          ,
//                                                                       CATBoolean               & oAccurate          );


///**
//* Extract the civil curve properties. The properties returned are the same the one used to build the evaluator.
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing the civil curve.
//* @param oCivilData
//* The civil curve data.
//* N.B. The memory has to be handle by the caller, no delete are performed in this method.
//* @Param iAccurate
//* TRUE if the properties extracted are accurate or the approximation version (similar to CATCreateCivilCurveEvaluator iAccurate parameter).
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//ExportedByGeoAdvCurves HRESULT CATExtractCivilCurveProperties   (      CATSoftwareConfiguration * iConfig    ,
//                                      const CATTolerance             & iTolerance     ,
//                                      const CAT2DCurveEvaluator      & iEvaluator     ,
//                                            CATCivilHorizCurveData  *& oCivilData     ,
//                                            CATBoolean               & oAccurate      );






///**
//* Extract the CATENARY civil curve properties
//* @param iEvaluator
//* The CAT2DCurveEvaluator describing a catenary
//* @param oStartPoint
//* The starting point of the catenary
//* @param oEndPoint
//* The ending point of the catenary
//* @param oLength
//* The length of the catenary
//* @param oCatenaryCoef
//* The catenary's shape coefficient 
//* @return
//* <br>E_FAIL  If there was an issue during the extraction.
//* <br>S_FALSE If the extraction did not succeed because of the inputs & option given
//*             are not consistent.
//* <br>S_OK    If the extraction has not encountered any issue.
//*/
//HRESULT CATExtractCivilCatenaryProperties(      CATSoftwareConfiguration * iConfig      ,
//                                         const CATTolerance             & iTolerance    ,
//                                         const CAT2DCurveEvaluator      & iEvaluator    ,
//                                               CATMathPoint2D           & oStartPoint   ,
//                                               CATMathPoint2D           & oEndPoint     ,
//                                               double                   & oLength       ,
//                                               double                   & oCatenaryCoef
//                                               );


////-----------------------------------------------------------------------------
//// CATExtractLength
////-----------------------------------------------------------------------------
//ExportedByGeoAdvCurves HRESULT CATExtractLength(const CATTolerance             & iTolerance,
//                                                      CATSoftwareConfiguration * iConfig,
//                                                const CAT2DCurveEvaluator      & iEvaluator,
//                                                      double                   & oLength);

//-----------------------------------------------------------------------------
// Extract polynomial degree
//-----------------------------------------------------------------------------
HRESULT CATExtractPolynomialDegree(const CAT2DCurveEvaluator   & iEvaluator,
                                         int                   & oDegreeU  ,
                                         int                   & oDegreeV  );


//-----------------------------------------------------------------------------
// Extract polynomial coef
//-----------------------------------------------------------------------------
HRESULT CATExtractPolynomialCoef(const CAT2DCurveEvaluator   & iEvaluator,
                                       double              * & oCoefU    ,
                                       int                   & oDegreeU  ,
                                       double              * & oCoefV    ,
                                       int                   & oDegreeV  );

//-----------------------------------------------------------------------------
// Extract control points
//-----------------------------------------------------------------------------
HRESULT CATExtractControlPoints (const CAT2DCurveEvaluator   & iEvaluator,
                                 const CATMathInterval       & iLimits   ,
                                       double              * & oCPts     ,
                                       int                   & oNbCPts   );


#endif



