#ifndef CATIPGMConnectCheckerInterfaceOfCurves_h_
#define CATIPGMConnectCheckerInterfaceOfCurves_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATConnectCheckerDef.h"

class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATMathVector;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConnectCheckerInterfaceOfCurves;

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
class ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfCurves: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConnectCheckerInterfaceOfCurves();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  // Post-Run diagnostic on whole computations (TRUE if OK, FALSE otherwise).
  // If FALSE, Get methods could return a throw if they are called 
  virtual CATBoolean IsRunOK() = 0;

  ////////////////////////////////////////////////////////////
  // Set methods
  ////////////////////////////////////////////////////////////
  // *** Only to take account of V5R16 new specifications. ***
  //
  // USE EXPLICITLY THESE METHOD BEFORE RUN OPERATOR 
  // TO SWITCH TO V5R16 SPECIFICATIONS.
  //
  virtual void SetNewSpecs(short iSetNewSpecs = 1) = 0;

  // Select the computation type (necessary)
  //
  // Example : Gaps + Curvatures : ... -> SetTypeOfEvalutation(CATConnectCheckerGap | CATConnectCheckerCurvature)
  //
  // CATConnectCheckerGap              1
  // CATConnectCheckerAngle            2
  // CATConnectCheckerCurvature        4
  // CATConnectCheckerOverLaps         8
  // CATConnectCheckerCurvatureComb    32
  virtual void SetTypeOfEvaluation(CATCommandOption iCommande) = 0;

  // Only for New Specs : define the interval of valid curvatures for your scope
  // By default : iMinCurvature corresponds to the largest radius that can be created in CATIA. At scale 1 the maximum radius for a circle is 10+7, so iMinCurvature is 10-7.
  virtual void SetCurvatureTolerances(double iMinCurvature, double iMaxCurvature) = 0;

  ////////////////////////////////////////////////////////////
  // Get methods
  ////////////////////////////////////////////////////////////
  // Returns the result of the G0 measure 
  // The result is a distance (positive quantity).
  //
  // Default tolerance = G0 TOL = 0.001 mm
  // A distance inferior to G0 TOL ensures G0 continuity.
  virtual double GetDistance() = 0;

  // Returns the result of the G1 measure in radians
  // The result is an angle between 0. and 0.5*PI radians.
  //
  // Default tolerance = G1 TOL = 0.5 degree
  // An angle inferior to G1 TOL ensures G1 continuity.
  // NB.: the angle depends of input orientations
  virtual double GetAngle() = 0;

  // Returns the result of the G2 measure in percent
  // The result is an adimensional rate between 0. and 200 %.
  //
  // Default tolerance = G2 TOL = 0.05 (5 percent)
  // A rate inferior to (100 * G2 TOL) ensures G2 continuity.
  virtual double GetCurvature() = 0;

  // Returns TRUE if an overlap exists between curve and surface, FALSE otherwise
  virtual CATBoolean GetOverlap() = 0;

  // Returns the normal on the curve 1
  virtual void GetNormal(CATMathVector &oNormal) = 0;

  // *** V5R16 new specifications methods  ***
  // Returns the result of the G2 measure in percent and a double
  // which indicates the angle made between the osculator planes of each curves.
  // The result is an adimensional rate between 0. and 100 %.
  // The boolean is TRUE if same convexity has been found, FALSE otherwise.
  //
  // Default tolerance = G2 TOL = 0.05 (5 percent)
  // An rate inferior to (100 * G2 TOL) and an angle inferior to G1 TOL ensures G2 continuity.
  virtual void GetCurvatureAndAngle(double &oCurvatureRate, double &oAngle) = 0;

  // Returns the result of the G2 measure in only one ratio thanks to
  // following alternative representation:
  //
  // Let R1 and R2 be respectively the curvature vectors of input curves 1 and 2. Then:
  //
  // oCurvatureDelta = ||R1-R2|| / ( max( ||R1|| , ||R2|| ) ) which lies in [0,1]
  //
  // ( oCurvatureError = 1 / ( 1 + oCurvatureDelta ) is optionnal )
  //
  // A value of oCurvatureDelta inferior to G2 TOL ensures G2 continuity.
  virtual void GetCurvatureErrorAndDelta(
    double &oCurvatureDelta,
    double *oCurvatureError = NULL) = 0;

  // Returns the result of the G3 measure in radians
  //
  // oCurvCombAngle = Angle( dR1/ds1 , dR2/ds2 ) in [0,PI] , where dR1/ds1 and dR2/ds2 denote the radius of curvature
  //                                                         vector first derivatives of curve 1 and 2 associated to
  //                                                         arc length s.
  //
  // A value of oPhi inferior to G3 TOL ensures G3 continuity.
  virtual void GetCurvatureCombAngle(double &oCurvCombAngle) = 0;

  // This method allows to retrieve a singularity diagnosis.
  // It returns TRUE if curve's first derivative is singular (ie. the tangent to the curve is defined by a derivative higher than one), FALSE otherwise.
  // iIndexCurve is 0 for iEdgeCurve1 (or iCurve1), 1 for iEdgeCurve2 (or iCurve2).
  //
  // NB.: this method is relevant if the type of evaluation contains CATConnectCheckerAngle or higher (Curvature, OverLaps or CurvatureComb).
  virtual CATBoolean IsSingular(int iIndexCurve) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConnectCheckerInterfaceOfCurves(); // -> delete can't be called
};

#endif /* CATIPGMConnectCheckerInterfaceOfCurves_h_ */
