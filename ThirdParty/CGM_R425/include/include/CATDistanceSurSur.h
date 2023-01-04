//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATDistanceSurSur:
//
//=============================================================================
// Usage Notes:
//
// This is an abstract class to handle implementation by ObjectOriented way
//
//=============================================================================
#ifndef CATDistanceSurSur_h
#define CATDistanceSurSur_h

#include "Y30A3HGG.h"
#include "CATMathDef.h"
#include "CATGeoOperator.h"
#include "CATCrvLimits.h"
#include "CATDistanceType.h"
#include "CATCreateDistanceSurSur.h"

class CATPointOnSurface;
class CATSurface;
class CATCartesianPoint;
class CATGeometry;
class CATPCurve;

class ExportedByY30A3HGG CATDistanceSurSur : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATDistanceSurSur);
public:
	//  Destructor.
	virtual ~CATDistanceSurSur() ;
	// Constructor.
	CATDistanceSurSur(CATGeoFactory * factory) ;
	
	// BeginningPoint
	// Initializes the iterator of solutions
	virtual void                BeginningPoint() = 0;
	
	// NextPoint
	// Returns 1 if there exists an other solution 
	// and updates the iterator
	virtual CATBoolean          NextPoint() = 0; 
	
	// GetPointOnSurface
	// returns the point on iSurface solution
	virtual CATPointOnSurface * GetPointOnSurface(CATSurface *iSurface) const = 0;
	
	// GetCartesianPoint
	// returns the 3D point solution on iSurface
	virtual CATCartesianPoint * GetCartesianPoint(CATSurface *iSurface) const = 0;
	
	// GetDistance
	// returns the distance solution
	virtual CATLength           GetDistance() = 0;
	virtual CATLength           GetCurveDistance() = 0;

  // Donne la dimension de la solution :
  // 0 = point isole
  // 1 = courbe (degenere)
  // 2 = surface (degenere)
  virtual CATLONG32 GetSolutionDimension() = 0;
	
	// SetDistanceType
	// if iDistanceType = CATAbsoluteMinDist : absolute minimum distance
	//                    CATLocalMinDist    : all local minima
	// (****DO NOT USE**** CATAbsoluteMaxDist : absolute maximum distance)
	// (****DO NOT USE**** CATLocalMaxDist    : all local maxima)
	virtual void SetDistanceType(CATDistanceType iDistanceType) =0;
	
	// SetSurfaceLimits
	// modifies the limits of iSurface
	virtual void SetSurfaceLimits(CATSurface* iSurface, const CATSurLimits& iLimits) = 0;
	
	// SetSurface
	// modifies the surfaces or one surface
	virtual void SetSurface(CATSurface* iNewSurface1, CATSurface* iNewSurface2) = 0;
	
	virtual void                BeginningCurve() = 0;
	virtual CATBoolean          NextCurve() = 0; 
	virtual CATPCurve         * GetPCurve(CATSurface*) const =0;
	
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
	
};

#include "CreateDistanceSurSur.h"

#endif
