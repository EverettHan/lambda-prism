
/* -*-C++-*- */


#ifndef CATReflectCurveProtected_H
#define CATReflectCurveProtected_H


/* -*-C++-*- */

//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//
// CATReflectCurveProtected - 
//
// Class for customizing settings of CATReflectCurve for other FWs
// without changing public interfaces
//
//===================================================================

//===================================================================
//
// Usage notes:
//
// To be only instantiated using new operaor on derived classes
//
//===================================================================

//===================================================================
// Feb 2019    Creation                         S9L
//===================================================================

#include "CATReflectCurve.h"

#include "CATListOfCATPCurves.h"

#include "CATMathPlane.h"

class CATMathIntervalND;
class CATMathSetOfPointsND;

/**
* Class to access implementation of CATReflectCurve outside the parent framework
* CATReflectCurve is the operator to compute the reflect curves on a surface.
* <br>The reflect curves are the set of points of a surface such that the surface normal
* at these points and a direction defines a constant angle.
*<ul>
*<li>The CATReflectCurveProtected operator currently is not streamed.
*<li> Serivces arealmost the same as that of CATReflectCurve except for some additional settings
*</ul>
*/
class ExportedByY30C3XGG CATReflectCurveProtected : public CATReflectCurve
{
public:
  //-----------------------------------------------------------------------
  //- constructor & destructor
  //-----------------------------------------------------------------------
  // cylinderical reflect
  CATReflectCurveProtected(CATGeoFactory             *   ipFactory,
                           CATSoftwareConfiguration  *   ipConfig,
                           CATSurface                *   ipSurface,
                           CATMathDirection          &   iDirection,
                           CATAngle                      iAngle);
  // conical reflect
  CATReflectCurveProtected(CATGeoFactory             *   ipFactory,
                           CATSoftwareConfiguration  *   ipConfig,
                           CATSurface                *   ipSurface,
                           CATPoint                  *   ipPoint,
                           CATAngle                      iAngle);
  // destructor
  ~CATReflectCurveProtected();

  /**
  * Modifies the surface domain to take into account for <tt>this</tt> CATReflectCurve
  * operator (<tt>ADVANCED</tt> mode).
  *<br> It does not change the current surface
  * limitations.
  * @param iLimits
  * The new limitations of the surface, <tt>NULL</tt> to take the current limitations.
  */
  virtual void SetLimits(CATSurLimits  * ipLimits);

#if (defined(CATIACGMV5R21))
  /** @nodoc */
  // @nocgmitf
  virtual void EnableBorderSolutionFilter();
#endif

  /**
  * Sets the boundary PCurves to define limits of reflect curve solutions
  */
  /** @nodoc */
  // @nocgmitf 
  virtual void SetBoundaryPCurves(CATLISTP(CATPCurve) & iBoundaryPCurves);

  /**
  * Sets the polylines corresponsing to the boundary PCurves to limit of solution points
  *
  * 4D Point: (t,x,y,z) : t - curve param, (x, y, z) - 3D point on curve
  */
  /** @nodoc */
  // @nocgmitf 
  virtual void SetBoundaryPolylines(CATLISTP(CATMathSetOfPointsND) & iBoundaryPolylines);

  /**
  * Sets the closed boundary UV polyline for the given face borders
  *
  * 2D Point: (u, v) - surface param along face border
  */
  /** @nodoc */
  // @nocgmitf 
  virtual void SetClosedUVBoundary(CATMathSetOfPointsND * ipClosedUVBoundary);

  /**
  * Check if surface solution is possible
  */
  /** @nodoc */
  // @nocgmitf 
  virtual CATBoolean IsSurfaceSolution();

  /**
  * Check if surface solution is needed
  */
  /** @nodoc */
  // @nocgmitf 
  void EnableSurfaceSolutions();

  /**
  * Check if the solution is on the boundary curves
  */
  /** @nodoc */
  // @nocgmitf 
  virtual CATBoolean IsOnBorder() = 0;

  /**
  * Compute the contours around the possible surface solutions
  */
  /** @nodoc */
  // @nocgmitf 
  virtual void ComputeSurfacicSolutions() = 0;

  /**
  * Initializes the iterator of the solution curves of <tt>this</tt>
  * CATProjectionCrvSur operator.
  *<br>By default, the initialization is performed once the operator runs,
  * and this is therefore only used to read the solutions again.
  */
  virtual void BeginningCurve() = 0;

  /**
  * Skips to the next solution curve of <tt>this</tt> CATReflectCurve operator.
  *<br>After <tt>BeginningCurve</tt>, it skips to the first curve.
  * @return
  * The existence of the next solution.
  * <br><b>Legal values</b>:
  *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
  *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
  */
  virtual CATBoolean NextCurve() = 0;

  /**
  * Creates the next solution curve as a curve on surface.
  * @return
  * The pointer to the created curve on surface. A new curve is created each time this method is called.
  * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
  */
  virtual CATPCurve * GetPCurve() = 0;

  /**
  * Creates the next solution curve.
  * @return
  * The pointer to the created curve. A new curve is created each time this method is called.
  * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
  */
  virtual CATCurve * GetCurve() = 0;

  /** @nodoc */
  virtual CATReflectCurveSign GetSignatureOn() const = 0;

  /**
  * Returns the number of solution curves.
  * @return
  * The number of curves.
  */
  virtual CATLONG32 GetNumberOfPCurves()            const = 0;

  /** @nodoc */
  virtual void BeginningSurface() = 0;
  /** @nodoc */
  virtual CATBoolean NextSurface() = 0;
  /** @nodoc */
  virtual void GetExtremitiesIndex(CATLONG32 & oStartIndex, CATLONG32 & oEndIndex) = 0;
  /** @nodoc */
  virtual CATReflectCurveSign GetIntrinsicSignatureOn() const = 0;

#ifdef CATIACGMR214CAA
  /** @nodoc */
  // @nocgmitf
  virtual void ManageStrongCurvatures(CATBoolean iManage) = 0;
#endif

#ifdef CATIACGMR215CAA
  /** @nodoc */
  // @nocgmitf
  virtual void ExtractIsoCurves() = 0;
#endif

protected:
  void CleanBoundaryData();
  void RetrieveBoundaryData();

  CATSoftwareConfiguration       *   _SoftwareConfiguration;
  CATSurface                     *   _Surface;
  CATPoint                       *   _OriginCATPt;
  CATAngle                           _Angle;
  CATMathDirection                   _Dir;
                                 
  CATSurLimits                       _SurLimits;
  CATSurLimits                   *   _ExactSurLimits;

  CATBoolean                         _FilterBorderSolution;
  CATBoolean                         _EnableSurfaceSolutions;

  CATMathPlane                       _ViewingPlane;

  CATLONG32                          _nBoundaryCurves;
  CATLISTP(CATPCurve)                _BoundaryPCurves; 
  CATLISTP(CATMathSetOfPointsND)     _BoundaryPolylines;

  CATBoolean                         _IsSurfacicPosibility;

  CATMathSetOfPointsNDWithVectors  **_pBoundaryParamsWithTangents; // Boundary UV params with 2D tangents
  CATMathSetOfPointsND             **_pProjectedBoundaries; // Boundary projected on viewing plane
  CATMathIntervalND                **_pBoundaryUIntervals; // V intervals on Iso-U curve
  CATMathIntervalND                **_pBoundaryVIntervals; // U intervals on Iso-V curve
  CATMathSetOfPointsND              *_pClosedUVBoundary; // Closed boundary of UV params
  CATMathSetOfPointsND              *_pBoundaryUParams; // U Param for Iso-U curve
  CATMathSetOfPointsND              *_pBoundaryVParams; // V Param for Iso-V curve
  CATMathSetOfPointsND              *_pSurfaceUParams; // U Param for Iso-U curve
  CATMathSetOfPointsND              *_pSurfaceVParams; // V Param for Iso-V curve
};                                   

#endif

/* -*-C++-*- */
