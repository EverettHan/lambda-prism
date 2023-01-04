#ifndef CATIPGMDistanceCrvSur_h_
#define CATIPGMDistanceCrvSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATMathDef.h"
#include "CATDistanceType.h"
#include "CATMathDiagnostic.h"

class CATCartesianPoint;
class CATCurve;
class CATGeometry;
class CATPointOnCurve;
class CATPointOnSurface;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATCrvParam;
class CATSurParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMDistanceCrvSur;

class ExportedByCATGMModelInterfaces CATIPGMDistanceCrvSur: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceCrvSur();

  // Initializes the iterator for the solutions 
  virtual void BeginningPoint() = 0;

  // returns 1 if there exists an other solution
  // and 0 if not
  virtual CATBoolean NextPoint() = 0;

  // GetPointOnCurve
  // Returns for each distance solution, the point on curve solution 
  virtual CATPointOnCurve *GetPointOnCurve() const = 0;

  // GetPointOnSurface
  // Returns the point solution on surface
  virtual CATPointOnSurface *GetPointOnSurface() const = 0;

  // Returns the point 3D solution on the curve or the surface
  virtual CATCartesianPoint *GetCartesianPoint(CATGeometry *iGeometry) const = 0;

  // GetDistance
  // Returns a distance (minimum or maximum) between a curve and a surface
  virtual CATLength GetDistance() = 0;

  // In the case of SetPointAndInit usage, the algorithm is limited to a maximum number of iterations.
  // If a maximum number of iterations is reached, the returned point is not fully reconverged but
  // can be used as a new init, using the SetPointAndInit method.
  // @return
  // The diagnostic (CATMathOK or CATMathMaxIteration)
  virtual CATMathDiagnostic GetDiagnostic() const = 0;

  // SetDistanceType
  // if iDistanceType = CATAbsoluteMinDist : absolute minimum distance
  //                    CATLocalMinDist    : all local minima
  // (****DO NOT USE**** CATAbsoluteMaxDist : absolute maximum distance)
  // (****DO NOT USE**** CATLocalMaxDist    : all local maxima)
  virtual void SetDistanceType(CATDistanceType iDistanceType) = 0;

  // SetCurveLimits
  // modifies the limits of the curve 
  virtual void SetCurveLimits(const CATCrvLimits& iLimits) = 0;

  // SetSurfaceLimits
  // modifies the limits of the surface 
  virtual void SetSurfaceLimits(const CATSurLimits& iLimits) = 0;

  // SetCurve
  // modifies the curve 
  virtual void SetCurve(CATCurve *iNewCurve) = 0;

  //SetInit
  //Gives an init
  virtual void SetInit(double * iInit[3], int iNum) = 0;

  /**
	* @nodoc
	* return the minimum value of the local minimum distances.
	* @return
	* The Absolute Minimum Distance
	*/
  virtual double GetAbsoluteMinDistance() const = 0;

  /**
	* @nodoc
	* Defines the maximum value the distance can't exceed (<tt>ADVANCED</tt> mode). 
	* @param iMaxDistance
	* The Maximum Value of DistanceMin.
	*/
  virtual void SetMaximumValue(double iMaxDistance) = 0;

  /**
	* @nodoc
	* Defines whether the boundaries are taken into account or not (<tt>ADVANCED</tt> mode). 
	* @param iSearchMode
	* The type of search.
	* <br><b>Legal values</b>:
	*  <dl><dt><tt>FALSE</tt><dd> the operator is equivalent to an orthogonal
	* projection which realizes the minimum distance.
	*<dt><tt>TRUE</tt><dd> the operator always return a solution realizing minimum
	* distance even if it is not a projection.</dl> 
	*/
  virtual void SetSearchOnBoundary(CATBoolean iSearchOnBoundary) = 0;

  /**
	* @nodoc
  */
  virtual CATCrvParam GetCrvParam() const = 0;

  /**
	* @nodoc
  */
  virtual CATSurParam GetSurParam() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceCrvSur(); // -> delete can't be called
};

#endif /* CATIPGMDistanceCrvSur_h_ */
