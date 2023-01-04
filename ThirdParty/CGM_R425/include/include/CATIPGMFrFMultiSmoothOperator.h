#ifndef CATIPGMFrFMultiSmoothOperator_h_
#define CATIPGMFrFMultiSmoothOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"

class CATIPGMFrFMultiSmoothOperator;
class CATSoftwareConfiguration;
class CATTolerance;
class CATMathSetOfPointsND;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFMultiSmoothOperator;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMFrFMultiSmoothOperator: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFMultiSmoothOperator();

  //
  virtual void SetDegree(int iDegree = 3) = 0;

  /**
  * Defines the Tolerance of the resulting curve.
  * @param iRankCurve
  * The Rank of the curve ( in case of Multicurve ), 1 <= iRankCurve <= iNbreCrv
  * @param iTol3d
  * The Tolerance value for each curve.
  */
  virtual void SetTolerance(double iTolerance) = 0;

  //
  virtual void SetNumberOfSubdivIterations(int iIter = 5) = 0;

  //
  virtual void SetMaxNumberOfArcs(
    int iMaxNumberOfArcs = 64,
    int iInternalContinuity = 2) = 0;

  //
  virtual int Run() = 0;

  //
  virtual void GetResult(CATMathSetOfPointsND **&oresultCtrlPts) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFMultiSmoothOperator(); // -> delete can't be called
};

/**
* Creates the operator that smoothes a set of points to create a Set of curves.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iConfig
* The pointer to configuration defining the level of code to replay.
* @param iPoints
* The pointer to the set of points (Its dimension=3).
* @return
* The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
* @see CATIPGMFrFSmoothingOper
*/
ExportedByCATGMOperatorsInterfaces CATIPGMFrFMultiSmoothOperator *CATPGMFrFCreateFMultiSmoothingOper(
  CATSoftwareConfiguration *iConfig,
  const CATTolerance *ipTolObject,
  int iNb_scans_to_smooth,
  CATMathSetOfPointsND **itab_of_scans);

#endif /* CATIPGMFrFMultiSmoothOperator_h_ */
