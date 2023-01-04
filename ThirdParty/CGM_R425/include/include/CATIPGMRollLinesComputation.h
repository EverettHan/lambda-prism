#ifndef CATIPGMRollLinesComputation_h_
#define CATIPGMRollLinesComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATMathDiagnostic.h"

class CATMathVector2D;

class CATMathPoint2D;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMRollLinesComputation;

//-------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMRollLinesComputation: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMRollLinesComputation();

  /**
   * AddPointData : should be called n times to specify n points, before calling the Run()
   * Specify one by one the points to add. The data (L,M,N) represents the second fundamental form
    * (in the way returned by the CATIPGMLocalAnalysis2D class), Point2D represents the image of the
   * 3D point in the flat view (expressed in the plane coordinates), DU2D and DV2D the images
   * on the 3D vectors DU and DV in the flat view (expressed in the plane coordinates)
   */
  virtual void AddPointData(
    double L,
    double M,
    double N,
    const CATMathPoint2D &Point2D,
    const CATMathVector2D &DU2D,
    const CATMathVector2D &DV2D,
    CATBoolean *Valid = NULL) = 0;

  /*
   * Specify the number of rolllines to be computed. Should be called before the Run()
   */
  virtual void SetNumberOfRollLines(int iNumberOfRollLines) = 0;

  /*
   * Specify energy type to be minimized to find RollLines.
   * iEnergyType=0 means that energy is minimization of twists along rolllines
   * iEnergyType=1 means that energy is minimization of curvature 
   *   (twists+longitudinal curvature) along rolllines
   * Default value is iEnergyType=0
   */
  virtual void SetEnergyType(int iEnergyType) = 0;

  /**
   * Return TRUE in case of success, FALSE otherwise. Should be called after the Run()
    * NEW ! Optional Argument oPreciseDiag give Info 
    * = CATMathOK : no problem
    * = CATMathConstantFunction : Too Smal Energie: Check that input is not on a plane. 
    */
  virtual CATBoolean GetDiagnostic(CATMathDiagnostic *oPreciseDiag = NULL) = 0;

  /**
   * Retrieve the rollline of index iRollLineIndex, with 0<= iRollLineIndex < iNumberOfRollLines;
   * Should be called after the Run() call.
   * TransversalCurvature contains the mean value of curvature of the RollLine (a sort of energy).
   * (Important : TransversalCurvature may be positive or negative)
   * RollLineRelativeEnergy is between 0 and 1. It contains the relative "energy" of the RollLine compared
   * to the set of all RollLines.
   */
  virtual void GetRollLine(
    int iRollLineIndex,
    CATMathPoint2D &oStart,
    CATMathPoint2D &oEnd,
    double &TransversalCurvature,
    double &RollLineRelativeEnergy) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMRollLinesComputation(); // -> delete can't be called
};

/**
 * Creates an operator for computing RollLines
 * Use ALWAYS  : 
 *     * Set methods (if needed) of the class to specify optional parameters
 *     * the Run method of the CATIPGMRollLinesComputation class to run the operator
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMRollLinesComputation *CATPGMCreateRollLinesComputation(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig);

#endif /* CATIPGMRollLinesComputation_h_ */
