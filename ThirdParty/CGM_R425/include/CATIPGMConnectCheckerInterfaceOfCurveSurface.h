#ifndef CATIPGMConnectCheckerInterfaceOfCurveSurface_h_
#define CATIPGMConnectCheckerInterfaceOfCurveSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATConnectCheckerDef.h"

class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConnectCheckerInterfaceOfCurveSurface;

class ExportedByCATGMModelInterfaces CATIPGMConnectCheckerInterfaceOfCurveSurface: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConnectCheckerInterfaceOfCurveSurface();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  // Post-Run diagnostic on whole computations (TRUE if OK, FALSE otherwise).
  // If FALSE, Get methods could return a throw if they are called 
  virtual CATBoolean IsRunOK() = 0;

  ////////////////////////////////////////////////////////////
  // Set methods
  ////////////////////////////////////////////////////////////
  // Select the computation type (necessary)
  //
  // Example : Gaps + Curvatures : ... -> SetTypeOfEvalutation(CATConnectCheckerGap | CATConnectCheckerCurvature)
  //
  // CATConnectCheckerGap              1
  // CATConnectCheckerAngle            2
  // CATConnectCheckerCurvature        4
  virtual void SetTypeOfEvaluation(CATCommandOption iCommande) = 0;

  // Only for New Specs : define the interval of valid curvatures for your scope
  // By default : iMinCurvature corresponds to the largest radius that can be created in CATIA.
  // At scale 1 the maximum radius for a circle is 10+7, so iMinCurvature is 10-7.
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
  virtual double GetAngle() = 0;

  // Returns the result of the G2 measure in percent
  // (NO; ERROR, ratio in [0, 1]; CAUTION, see below)
  // and a boolean
  // which indicates if we have the same convexity on curve and surface.
  // The result is an adimensional rate between 0. and 100 %.
  // The boolean is TRUE if same convexity has been found, FALSE otherwise.
  //
  // Default tolerance = G2 TOL = 5 percent
  // An rate inferior to G2 TOL and same convexity ensure G2 continuity.

  // CAUTION: to be fixed ???
  // as of historical version, (from the beginning)
  // and despite of documentation above,
  // ioCurvatureRate is a ratio in [0., 1.]
  // and NOT a percent in [0., 100.]
  //   NLD270522
  // PLEASE USE GetCurvatureDeviation()
  virtual void GetCurvatureAndConvexity(
    double &ioCurvatureRate,
    CATBoolean &ioSameConvexity) = 0;

  // Returns the result of the G2 measure in percent and a boolean
  // which indicates if we have the same convexity on curve and surface.
  // The result is an adimensional rate between 0. and 100 %.
  // The boolean is TRUE if same convexity has been found, FALSE otherwise.
  //
  // Default tolerance = G2 TOL = 5 percent
  // An rate inferior to G2 TOL and same convexity ensure G2 continuity.

  // REPLACES GetCurvatureAndConvexity()
  //   NLD100622
  virtual void GetCurvatureDeviation(double     & ioCurvaturePercentRate,
                                     CATBoolean & ioSameConvexity) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConnectCheckerInterfaceOfCurveSurface(); // -> delete can't be called
};

#endif /* CATIPGMConnectCheckerInterfaceOfCurveSurface_h_ */
