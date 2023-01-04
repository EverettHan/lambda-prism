/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATHomotopy3Sur :
// Abstract class for homotopy with three non tangent surfaces. 
// Some indications about how it works ( more details available in paper-documentation)
// Computation of the intersection of three offset surfaces ( defined as  
//  CATOffsetSurfaces or by the support CATSurface and a radius ).
//
//  a- OK : diagnostic given by  GetHomotopyDiag() method is CATHomotopyOK
//    CATSurParam of the intersection are given !!!! on the support surfaces !!!
//    by the GetSurParam(i) method (i=1,2,3 same order as in Create )
//
//  b- Some kind of problem.
//     - b.a. : homotopy impossible. diagnostic given by  GetHomotopyDiag() method
//       CATHomotopyExtrapolation. The point is on the MaxLimits of at least
//       one support surface. GetSurDiag(i) gives for surface i the logical quantity
//      surdiag =  (PointOnMaxLimUMin)+2*(PointOnMaxLimUMax)
//                         +4*(PointOnMaxLimVMin)+8*(PointOnMaxLimVMax)
//     - b.b. : homotopy partially done. diagnostic given by  GetHomotopyDiag() method
//       CATHomotopyStop (+eventually CATHomotopySeamLimimts 
//                        +eventually CATHomotopyFilletLimits )
//       The partial solution is described by GetSurParam(i) methods returning his CATSurParam
//       on the support surfaces. The partial radius (lam*r1wanted, lam*r2wanted, 
//       lam*r3wanted ) are given by GetRadiusStop(i) mehods.
//       if the stop point is located at a seam-boundary (Sur->IsClosed() true )
//       then the diagnostic is CATHomotopyStop + CATHomotopySeamLimits
//       if the stop point is located at a V-boundary of a CATCircularSweep surface
//       then the diagnostic is CATHomotopyStop + CATHomotopyFilletLimits 
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// Aug.  97     Creation                       J. Peter
// Sept. 98     Add SetLimits method           I. Levy
// Fev.  99     Add DetectsPoleOnSurfaceNumber P.Tonnerre
//========================================================================== 

#ifndef CATHomotopy3Sur_H
#define CATHomotopy3Sur_H

#include "Y30C3XGG.h"
#include "CreateHomotopy3Sur.h"
#include "CATCreateHomotopy3Sur.h"
#include "CATGeoOperator.h"
#include "CATHomotopyDef.h"
#include "CATSurLimits.h"
#include "CATSurParam.h"

class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATEdgeCurveTransientExtrapolManager;

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATHomotopy3Sur : public CATGeoOperator
{    
  public:

    virtual ~CATHomotopy3Sur();

    CATHomotopy3Sur(CATGeoFactory * factory);
    
    virtual void GetSurParam( const CATLONG32 i, CATSurParam & oParam ) const = 0;
    
    virtual CATHomotopyDiag GetHomotopyDiag() const = 0;
    
    virtual double GetRadiusStop(const CATLONG32 i) = 0;
    
    virtual CATLONG32   GetSurDiag(const CATLONG32 i) = 0;
    
    /**
    * Sets a new domain for surface i  in <tt>ADVANCED</tt> mode.
    *
    * For surface iSurfNumber, iSide indicates which sides 
    * of the surface between UMin, UMax, VMin, and VMax
    * can be extrapolated.
    * By default, each side can be extrapolated during the 
    * algorithm of homotopy.
    *
    */
    virtual void SetLimits(const CATLONG32           iSurfNumber,
			   const CATSurLimits & iNewLimits,
         CATSideToExtrapolate  iSide =CATNoSide) =0;

    
    /**
     * Detects a pole crossing on the surface whose number is oSurfaceNumber (1<=i<=3),
     * finds the param on the other side of the pole (stored in an array of size oNumberOfSolutions 
     * (1<=size<=2 : size=2 to prevent a boundary of the surface))
     */
    virtual void DetectsPoleOnSurfaceNumber(CATLONG32 &oSurfaceNumber, 
      CATLONG32 &oNumberOfSolutions,
      CATSurParam *oDegenerateParamOnTheOtherSide)=0;


    /* Use this method to specify a reference parametre (=centre of a face's UV box)
     * on each surface as a helper for lower-level routines that require such 
     * contextual (topological) information (specifically GetSurfaceValidMaxBox). 
     */
    virtual void SetRefParam(CATLONG32 iSurfNumber, const CATSurParam & sp) =0;

    
    /* This method is used to provide optional topological context to the operator
     * which can be helpful in lifting off from a singular init (specifically in 
     * the case of smooth-sharp edges at the smooth end).
     * If iSurfNumber = 0, EC is the edge curve between surfaces 1 and 2
     *                  1                                        2     0
     *                  2                                        0     1
     * POECNearTripleInt is the point on the edge curve corresponding to the init of the system.
     * POECExtremity is the other extremity of the edge curve (the two poec define the used edge curve)
     */
    virtual void SetHelperEdgeCurve(CATLONG32 iSurfNumber, 
                                    CATEdgeCurve * EC,
                                    CATPointOnEdgeCurve * POECNearTripleInt,
                                    CATPointOnEdgeCurve * POECExtremity = NULL) =0;

    /* This method is used in addition to 'SetHelperEdgeCurve' method.
     * It allows user to specify to Homotopy3Sur algorithm if he has a mandatory
     * helper EdgeCurve, ie. an EdgeCurve from which he wants to start whatever
     * smooth angle is. If this Set is called, 3Sur algorithm will returned the best
     * solution computed by HomotopyCrvSur technique, except if it failed. In such
     * a case, we will switch on standard 3Sur technique.
     *
     *  (see conventions upper)
     */
    virtual void SetMandatoryHelperEdgeCurve(short iSurfNumber) =0;


    /* Enable a special mode of extrapolation for the edgecurve underlying the
     * bisector surfaces, such that a larger gap than the standard gap
     * is allowed in the extrapolated edge curve. The larger gap used is an
     * internal tolerance associated to the factory.
     */

    virtual void AllowLargeGapInBisectorExtrapolation(CATEdgeCurveTransientExtrapolManager * Manager) =0;
};


#endif
