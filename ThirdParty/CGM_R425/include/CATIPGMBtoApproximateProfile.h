#ifndef CATIPGMBtoApproximateProfile_h_
#define CATIPGMBtoApproximateProfile_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCldScan;
class CATGeoFactory;
class CATMathSetOfPointsND;
class CATMathVector;
class CATSoftwareConfiguration;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBtoApproximateProfile;

/**
* Class defining a operator that smooth a set of points to create a decomposition into arcs and segments(and Bezier!).
* <br>The CATIPGMBtoApproximateProfile operator follows the global frame of the geometric operators:
*<ul>
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.
*<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMBtoApproximateProfile: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBtoApproximateProfile();

  /**
  * Defines the maximum number of arcs of the created curve.
  * @param iMaxNumberOfArcs
  * The maximum number of arcs of each created curve
  * @param iInternalContinuity
  * The Internal continuity of each created curve, iInternalContinuity = 2, 3, 4.
  */
  virtual void SetMaxNumberOfArcs(
    int iMaxNumberOfArcs = 64,
    int iInternalContinuity = 3) = 0;

  /**
  * Defines the Smoothing Tolerance.
  * @param iTol
  * the Smoothing Tolerance ( it is used also for canonical recognition ).
  * @param iRmin, iRmax
  * The minimum and maximum Radius of Circle ( else the result will be a segment de droite or Bezier Curve)
  */
  virtual void SetParams(double iTol, double iRmin, double iRmax) = 0;

  /**
  * Defines Support Plane.
  * @param iPlane
  * If we are in 2D, the result will be in 2D (particularly PCircle and PLine). 
  */
  virtual void SetPlane(CATMathPlane *iPlane = NULL) = 0;

  //
  virtual void CleanInputs(double iMinEdge = 0., double iCuttingAngle = 45.) = 0;

  /**
  * Runs <tt>this</tt> operator .
  */
  virtual int Run() = 0;

  //
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBtoApproximateProfile(); // -> delete can't be called
};

/**
* Creates the operator that smoothes a set of points to create a Set of curves.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iTopData
* The pointer to TopData containing configuration And Journal defining the level of code to replay.
* @param iPoints
* The pointer to the set of points (Its dimension=3).
* @return
* The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
* @see CATIPGMFrFSmoothingOper
*/
ExportedByCATGMOperatorsInterfaces CATIPGMBtoApproximateProfile *CATPGMBtoCreateApproximateProfile(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATMathSetOfPointsND *iPoints);

/**
* Creates the operator that smoothes a set of points to create a Set of curves.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iTopData
* The pointer to TopData containing configuration And Journal defining the level of code to replay.
* @param iScan
* The pointer to the CATCldScan corresponding to an ordered set of points (Its dimension=3).
* @return
* The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
* @see CATIPGMFrFSmoothingOper
*/
ExportedByCATGMOperatorsInterfaces CATIPGMBtoApproximateProfile *CATPGMBtoCreateApproximateProfile(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATCldScan *iScan);

#endif /* CATIPGMBtoApproximateProfile_h_ */
