#ifndef CATIPGMConnectCheckerInterfaceOfSurfaces_h_
#define CATIPGMConnectCheckerInterfaceOfSurfaces_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"

#include "CATIPGMGeoOperator.h" // Q48__ConnectCheckerMigration
///#include "CATIPGMOperator.h"

#include "CATConnectCheckerDef.h"

class CATCrvParam;
class CATCurve;
class CATIPGMDistanceMinPtCrv;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathInterval;
class CATMathVector;
class CATPointOnEdgeCurve;
class CATSurLimits;
class CATMathPoint;
class CATPCurve;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConnectCheckerInterfaceOfSurfaces;

/** 
 * Type to define the command of Connect Checker.
 * @param OptionGaps
 * Evaluation of Gap.
 * @param OptionAngles
 * Evaluation of Angles between normals.
 * @param OptionCurvatures
 * Evaluation of Curvatures.
 * @param OptionOverlaps
 * Search of Overlaps.
 */
class ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfSurfaces: public CATIPGMGeoOperator // Q48__ConnectCheckerMigration
//class ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfSurfaces: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConnectCheckerInterfaceOfSurfaces();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------
  // Post-Run diagnostic on whole computations (TRUE if OK, FALSE otherwise).
  // If FALSE, Get methods could return a throw if they are called 
  virtual CATBoolean IsRunOK() = 0;

  // *** Only to take account of V5R16 new specifications. ***
  //
  // USE EXPLICITLY THIS METHOD BEFORE RUN OPERATOR 
  // TO SWITCH TO V5R16 SPECIFICATIONS.
  //
  virtual void SetNewSpecs(short iSetNewSpecs = 1) = 0;

  /////////////////////////////////////////////////////////////
  // MANDATORY SET METHODS
  /////////////////////////////////////////////////////////////
  // Choose the computation type
  // ex.: Gaps + Curvatures : SetTypeOfEvalutation(CATGap | CATCurvature)
  //
  // CATConnectCheckerGap              1
  // CATConnectCheckerAngle            2
  // CATConnectCheckerCurvature        4
  // CATConnectCheckerOverLaps         8
  // CATConnectCheckerTgtAndNormGap    16
  // CATConnectCheckerCurvatureComb    32
  virtual void SetTypeOfEvaluation(CATCommandOption iCommand) = 0;

  //
  // STANDARD DISCRETIZATION MODE
  //
  // Choose the type of discretization (pre-defined values)
  //
  // iType = 0 : Standard = Nb of Points =  5
  // iType = 1 : Coarse   = Nb of Points = 15
  // iType = 2 : Medium   = Nb of Points = 30
  // iType = 3 : Fine     = Nb of Points = 45
  virtual void SetTypeOfDiscretization(int iType) = 0;

  //
  // THESE MODES ARE ALTERNATIVES TO STANDARD DISCRETIZATION
  //
  // *** Available with V5R16 new specifications. ***
  //
  // Exact G1 reconvergence of Min/Max gap G1 in [0,PI]
  // (call with iEnable = TRUE to activate this mode)
  //
  // iSideOnFace is optionnal (it allows internally to compute G1 values
  // with true sign, in [-PI,PI])
  // 
  // Output results are obtained by calling GetMinMaxAngle method.
  //
  virtual void SetExactG1MinMaxMode(CATBoolean iEnable, int iSideOnFace = 1) = 0;

  //
  //
  //
  // OptimalSampling Mode : an optimal discretization is performed
  //                        according to the complexity of input
  //                        geometries
  //
  virtual void SetOptimalSamplingMode() = 0;

  //
  // OpenSampling Mode : the caller is free to choose the discretization
  //                     sampling value.
  //
  // NB. : iSamplingValue must be higher than 3
  virtual void SetOpenSamplingMode(const CATLONG32 iSamplingValue = 5) = 0;

  /////////////////////////////////////////////////////////////
  // SET METHODS IN ACCORDANCE WITH LIGHT CONSTRUCTOR
  /////////////////////////////////////////////////////////////
  //void SetBoxFace(const CATMathBox * iBoxFace1, const CATMathBox * iBoxFace2,);
  //void SetSurfaceLimits(const CATSurLimits & iLimitSurf1, const CATSurLimits & iLimitSurf2);
  //void SetOrientationSurfFace(const int iOriPCrv1VsSurf1, const int iOriPCrv2VsSurf2);
  //Modif du type de l'edge
  // 1 = mort, 0 = vive sinon CATThrow
  virtual void SetEdgeType(int iIsSmooth) = 0;

  // To stop the angle evaluations as soon as an angle higher, in absolute value, than the given tolerance
  virtual void SetStopOnAngleTolerance(double iAngleMax) = 0;

  // Only for New Specs : define the interval of valid curvatures for your scope
  // By default : iMinCurvature corresponds to the largest radius that can be created in CATIA. At scale 1 the maximum radius for a circle is 10+7, so iMinCurvature is 10-7.
  virtual void SetCurvatureTolerances(double iMinCurvature, double iMaxCurvature) = 0;

  /////////////////////////////////////////////////////////////
  // GET METHODS
  /////////////////////////////////////////////////////////////
  // Returns the number of points used for discreete computations.
  virtual int GetNumberOfPoints() = 0;

  // NB: for all methods flaged by * MD * THE CALLER MUST MANAGE DEALLOCATION ONLY
  ////////////////////
  // G0 get methods //
  ////////////////////
  //
  // Returns [ _MinGap , _MaxGap ] (with respect to the input poecs) and associated points if needed
  virtual CATMathInterval GetMinMaxGap(
    CATMathPoint oPointMin[2] = NULL,
    CATMathPoint oPointMax[2] = NULL) = 0;

  // Returns all discretized couple of points (P1,P2) (with respect to the input poecs)
  // and respected gaps ||P1-P2|| (the method allocates memory)
  //
  // * MD *
  virtual void GetAllPoints(double *&oGaps, CATMathPoint *&oPoint1, CATMathPoint *&oPoint2) = 0;

  ////////////////////
  // G1 get methods //
  ////////////////////
  //
  // Returns [ min(_Angles) , max(_Angles) ] (in radians) and associated points if needed
  //
  // NB1 : the operator should be initialized with the constructor and
  //       the two Curves (iPCrv1 and iPCrv2) must be some PCurves.
  // NB2 : the angles returned are between 0 and PI radians
  virtual CATMathInterval GetMinMaxAngle(
    CATMathPoint oPoint1MinMax[2] = NULL,
    CATMathVector oNormal1MinMax[2] = NULL) = 0;

  // Returns all G1 angles defaults (with respect to the input poecs) and discretized points and normals
  // on first curve (the method allocates memory)
  //
  // * MD *
  virtual void GetAllTangency(
    double *&oAngles,
    CATMathPoint *&oPoint1,
    CATMathVector *&oNormal1) = 0;

  // to get the sharpness if the "StopOnTolerance" mode has been activated
  virtual CATBoolean GetStopOnAngleTolerance() = 0;

  ////////////////////
  // G2 get methods //
  ////////////////////
  //
  // Returns [ min(_Curvatures) , max(_Curvatures) ] in percent and associated points if needed
  virtual CATMathInterval GetMinMaxCurvature(
    CATMathPoint oPoint1MinMax[2] = NULL,
    CATMathVector oNormal1MinMax[2] = NULL) = 0;

  // Returns all G2 curvatures defaults (with respect to the input poecs) and discretized points and normals
  // on first curve (the method allocates memory)
  //
  // * MD *
  virtual void GetAllCurvature(
    double *&oCurvature,
    CATMathPoint *&oPoint1,
    CATMathVector *&oNormal1) = 0;

  // *** Available with V5R16 new specifications. ***
  //
  // * MD *
  //
  // Returns all G2 curvatures defaults (with respect to the input poecs), same convexity booleans, and
  // discretized points and normals on first curve (the method allocates memory)
  virtual void GetAllCurvatureAndConvexities(
    double *&oCurvature,
    CATBoolean *&oSameConvexities,
    CATMathPoint *&oPoint1,
    CATMathVector *&oNormal1) = 0;

  ////////////////////
  // G3 get methods //
  ////////////////////
  //
  // *** Available with V5R16 new specifications. ***
  //
  // * MD *
  //
  // Returns all G3 angle defaults in radians (with respect to the input poecs) of normal section
  // curvature comb between the two surfaces, and discretized points and normals on first curve
  // (the method allocates memory)
  virtual void GetAllCurvatureCombAngles(
    double *&oCurvatureCombAngles,
    CATMathPoint *&oPoint1,
    CATMathVector *&oNormal1) = 0;

  // Returns [ min(CurvCombAngle) , max(CurvCombAngle) ] in radians and associated points and normals if needed
  virtual CATMathInterval GetMinMaxCurvatureCombAngles(
    CATMathPoint oPoint1MinMax[2] = NULL,
    CATMathVector oNormal1MinMax[2] = NULL) = 0;

  // Overlap and healing get methods
  //
  // Returns all overlaps boolean diagnostics for each couple of points (P1,P2) discretized
  // (the method allocates memory)
  //
  // * MD *
  virtual CATBoolean *GetOverlap() = 0;

  // Get dans le cas mort, on retourne les gaps calculés p/r
  // la moyenne des deux normales.
  // TgGap<0 => overlaps, TgGap>0 => pas d'overlaps
  virtual double GetMaxTgtGap() = 0;

  virtual double GetMinTgtGap() = 0;

  virtual double GetMaxNoGap() = 0;

  // Get dans le cas vif, on retourne les gaps calcules p/r
  // a une des normales.
  // TgGap<0 => overlaps, TgGap>0 => pas d'overlaps
  virtual double GetMaxTgtGap(CATPCurve *iPCrvRef) = 0;

  virtual double GetMinTgtGap(CATPCurve *iPCrvRef) = 0;

  virtual double GetMaxNoGap(CATPCurve *iPCrvRef) = 0;

  // DANGER = si le mauvais get est appelé (mode vif ou mort) on sort en Throw!!!
  //Retourne les valeurs des snapping au debut et a la fin de l'edge
  virtual void GetSnapping(double &oSnapStart, double &oSnapEnd) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConnectCheckerInterfaceOfSurfaces(); // -> delete can't be called
};

#endif /* CATIPGMConnectCheckerInterfaceOfSurfaces_h_ */
