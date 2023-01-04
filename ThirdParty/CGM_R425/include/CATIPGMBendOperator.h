#ifndef CATIPGMBendOperator_h_
#define CATIPGMBendOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATBendDefines.h"

class CATCurve;
class CATGeoFactory;
class CATMathSetOfPointsNDWithVectors;
class CATSoftwareConfiguration;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMBendOperator;

class ExportedByCATGMModelInterfaces CATIPGMBendOperator: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBendOperator();

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------
  /**
 * Provides a global diagnosis for the computation.
 * -1 : No run done (no run, irrelevant input data, minimum bend radius smaller than resolution, etc.).
 *  0 : Run done with success.
 *  1 : Failure.
 */
  virtual CATLONG32 GetDiagnostic() = 0;

  /**
 * If the Run diagnosis is 'Failure' (see upper GetDiagnostic method), this method returns the first index
 * in the global input set of passing points and vectors on which the solving algorithm failed.
 * The method returns :
 * -1 : Irrelevant index (no Run done, or Run has succeeded).
 * Else, a positive index in [0,Size-1], where Size denotes the number of points of input set.
 *
 * oDiag : optional return value used to store a detailed failure diagnosis.    
 */
  virtual CATLONG32 GetFailureIndex(CATBendDiagnostic *oDiag = NULL) = 0;

  /**
 * Returns the number of sub-element curves (circle arcs and line segments) resulting of the
 * global computation of the center line.
 */
  virtual CATLONG32 GetNumberOfCurves() const = 0;

  /**
 * Initializes the iterator of the solution curves.
 */
  virtual void BeginningCurve() = 0;

  /**
 * Skips to the next solution curve. It returns :
 *  TRUE  : if there is a solution curve.
 *  FALSE : if there is no more solution curve (end of the center line).
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * Creates the sub-element curve that corresponds to current iterator position.
 * The methods returns the pointer to the created curve. A new curve is created each time this method is called.
 * The caller must call the Remove method of CATICGMContainer if he decides not to keep the curve.
 */
  virtual CATCurve *GetCurve() = 0;

  /**
 * Returns the usefull limits of the solution curve that corresponds to current iterator position.
 * BE CAREFUL: to obtain relevant limits, the caller must have called previously GetCurve () method.
 */
  virtual void GetCurveLimits(CATCrvLimits &oLimits) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBendOperator(); // -> delete can't be called
};

/**
 * Creates an instance of a CATIPGMBendOperator.
 *
 * iPassingPtsAndVectors : a global ordered set of 3D passing points with associated cinematically oriented tangents (imposed directions)
 *                         that define the center line to be computed.
 *                         The set must be of size equal of greater than 2. It is not required to normalize vectors.
 * iMinBendRadius        : the minimum bend radius of the center line to be computed.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMBendOperator *CATPGMCreateBendOperator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMathSetOfPointsNDWithVectors *iPassingPtsAndTgts,
  double iMinBendRadius);
#endif /* CATIPGMBendOperator_h_ */
