#ifndef CATIPGMPConicsComputation_h_
#define CATIPGMPConicsComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATGeoFactory;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathVector2D;
class CATMathDirection2D;
class CATMathPoint2D;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMPConicsComputation;

//-------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMPConicsComputation: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPConicsComputation();

  /**
   * Compute PConics with 3 points (iExtremityPoints[0], iExtremityPoints[1], iPointOnConic)
   * and two tangents(iExtremityTangents[i] : Tangent of the PConic at iExtremityPoints[i])
   */
  virtual void SetPConicsDefinition(
    const CATMathPoint2D iExtremityPoints[2], 
    const CATMathDirection2D iExtremityTangents[2],
    const CATMathPoint2D &iPointOnConic) = 0;

  /**
   * Compute PConics with 3 points (iExtremityPoints[0], iExtremityPoints[2], iPointOnConic)  
   * and another point (iExtremityPoints[1] : intersection of the tangents computed at 
   * iExtremityPoint[0] and iExtremityPoints[2] )
   */
  virtual void SetPConicsDefinition(
    const CATMathPoint2D iExtremityPoints[3],
    const CATMathPoint2D &iPointOnConic) = 0;

  /**
   * Compute PConics with 2 points (iExtremityPoint[0], iExtremityPoint[2]) and a ratio (0<Ratio<1)
   * and another point (iExtremityPoints[1] : intersection of the tangents computed at 
   * iExtremityPoint[0] and iExtremityPoints[2] )
   */
  virtual void SetPConicsDefinition(
    const CATMathPoint2D iExtremityPoints[3],
    const double &Ratio) = 0;

  /** Compute PConics from 4 points and one tangent, the tangent corresponding to
   *  point index iTgtOfPtIndex (0<= iTgtOfPtIndex < 4)
   */
  virtual void SetPConicsDefinition(
    const CATMathPoint2D iPoints[4],
    const CATMathVector2D &iTangent,
    CATLONG32 iTgtOfPtIndex) = 0;

  /** Compute PConics from 5 points
   */
  virtual void SetPConicsDefinition(const CATMathPoint2D iPoints[5]) = 0;

  /**
   * Set Surface
   */
  virtual void SetSurface(CATSurface *iSurface) = 0;

  /**
   * Set tolerance (default is the resolution)
   */
  virtual void SetTolerance(double iTolerance) = 0;

  /**
   * Set the mode where a relimitation is required.
   * In this mode, the relimitation will occur between the first and last points given to
   * the operator using one of the SetPConicsDefinition methods.
   */
  virtual void SetRelimitation(CATBoolean iRelimit = 1) = 0;

  /**
   * In SetRelimitation mode, specifies that an additional check must be performed,
   * ensuring that all other points will be located between the first and last given
   * to the operator. If it is not the case, a null pointer will be returned as result.
   */
  virtual void SetCheckRelimitation(CATBoolean iCheck = 1) = 0;

  /**
   * Get the created PConics.
   * In degenerated cases, a NULL pointer will be returned.
   */
  virtual CATPCurve *GetPConic() = 0;

  /**
   * Get the orientation (+1 or -1)
   * with respect to the inputdata (in the Relimit mode only)
   */
  virtual int GetOrientation() = 0;

  /**
  * 
  */
  virtual void SetParabolaFirst(CATBoolean iParabolaFirst = TRUE) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPConicsComputation(); // -> delete can't be called
};

/**
 * Creates an operator for computing a PConics
 * Use ALWAYS  : 
 *     the Set methods of the CATIPGMPConicsComputation class to specify how to define the PConics
 *     the Run method of the CATIPGMPConicsComputation class to run the operator
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPConicsComputation *CATPGMCreatePConicsComputation(
  CATGeoFactory *iWhere,
  CATSurface *iSurface);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPConicsComputation *CATPGMCreatePConicsComputation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface);

#endif /* CATIPGMPConicsComputation_h_ */
