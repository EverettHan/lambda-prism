/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATHomotopyCrvSur :
// Abstract class for homotopy with one surface and one edge.
//  ( = one surface and two tangents surfaces ) 
// We also introduce diagnostics which refer to the two support surfaces
//  of the egdecurve. See CreateHomotopyCrvSur.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// Aug.  97     Creation                       J. Peter
// Sept. 98     Add SetLimits methods          I. Levy
//========================================================================== 

#ifndef CATHomotopyCrvSur_H
#define CATHomotopyCrvSur_H

#include "Y30C3XGG.h"
#include "CreateHomotopyCrvSur.h" 
#include "CATHomotopyDef.h"
#include "CATGeoOperator.h"
#include "CATSurLimits.h"
#include "CATSurParam.h"
#include "CATCrvLimits.h"
#include "CATCrvParam.h"

class CATPCurve;
class CATEdgeCurveTransientExtrapolManager;

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATHomotopyCrvSur : public CATGeoOperator
{    
public:
  
  CATHomotopyCrvSur(CATGeoFactory * factory);
  
  virtual ~CATHomotopyCrvSur();
  
  virtual CATSurParam  GetSurParam() const = 0;
  
  virtual CATCrvParam  GetCrvParam() const = 0;
  
  virtual CATHomotopyDiag GetHomotopyDiag() const = 0;
  
  virtual double GetRadiusEdgeStop() const = 0;
  
  virtual double GetRadiusSurStop() const = 0;
  
  virtual CATLONG32  GetEdgeDiag() const = 0;
  
  virtual CATLONG32  GetSurDiag(const CATLONG32 i) const = 0;
  
  
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
  virtual void SetLimits(const CATLONG32 iSurfNumber,
    const CATSurLimits & iNewLimits,
    CATSideToExtrapolate  iSide =CATNoSide) =0;
  
  /**
  * Sets a new domain for surface in <tt>ADVANCED</tt> mode.
  * 
  * Now, use the precedent method with iSurfNumber=2
  */
  virtual void SetSurLimits(const CATSurLimits & iNewLimits, 
    CATSideToExtrapolate  iSide =CATNoSide) =0;
  
  /**
  * Sets a new domain for edgecurve in <tt>ADVANCED</tt> mode.
  */
  virtual void SetCrvLimits(const CATCrvLimits & iNewLimits, 
    CATSideToExtrapolate  iSide =CATNoSide) =0;
  
  /**
  * Detects a pole crossing on the base surface (i.e. not the surface support of the EdgeCurve),
  * finds the param on the other side of the pole (stored in an array of size oNumberOfSolutions 
  * (1<=size<=2 : size=2 to prevent a boundary of the surface))
  */
  virtual void DetectsPoleOnBaseSurface( CATLONG32 &oNumberOfSolutions,
    CATSurParam *oDegenerateParamOnTheOtherSide)=0;
  
  /**
  * Returns ths PCurve used in the system of Homotopy 
  */
  virtual CATPCurve * GetHomotopyPCurve() = 0;

  /* Specify the PCurves corresponding to the surfaces in the edgecurve.
   * (This is necessary because an edgecurve may have more than one member PCurve
   *  lying on a given surface) */

  virtual void SetPCurve(CATLONG32 iSurfNumber, CATPCurve * iPCurve) = 0;

  /* Specify the priviledged PCurve/SupportSurface number (i.e. the PCurve used 
   * to solve the intersection system) 
   * NOT IMPLEMENTED YET - as of today, the reference PCurve/SupportSurface number
   * defaults to zero in all HomotopyCrvSur
   */

  virtual void SetRefPCurve(CATLONG32 iSurfNumber) = 0;

  /* Use this method after a successful run of the operator to
   * get the squared 3d distance between the solution specified on the EdgeCurve
   * found by the operator and the corresponding points on the specified PCurves
   */

  // deprecated, use next method
  virtual double GetGap2() =0;
  
  // the more modern method:
  virtual double GetGapSquared() =0;


  /* Use this method after a successful run of the operator to
   * reconverge the solution found by the operator using the
   * specified PCurve
   * Return values:
   *   0  ok
   *   1  reconvergence failed
   */
  
  virtual CATLONG32 GetSolutionForPCurve(CATLONG32 iSurfNumber, CATCrvParam & cp, CATSurParam & sp) =0;
  
  /* Use this method to specify a reference parametre (=centre of a face's UV box)
   * on each surface as a helper for lower-level routines that require such 
   * contextual (topological) information (specifically GetSurfaceValidMaxBox). 
   */
  
  virtual void SetRefParam(CATLONG32 iSurfNumber, const CATSurParam & sp) =0;

  /* Enable a special mode of extrapolation for the edgecurve of this homotopy,
   * such that a larger gap than the standard gap is allowed in the extrapolated
   * edge curve. The larger gap used is an internal tolerance associated to the
   * factory.
   */

  virtual void AllowLargeGapInECExtrapolation(CATEdgeCurveTransientExtrapolManager * Manager) =0;

  /* Like above but enables the special mode for the edgecurve underlying the
   * surface when it is a bisector surface. */ 

  virtual void AllowLargeGapInBisectorExtrapolation(CATEdgeCurveTransientExtrapolManager * Manager) =0;

  /* Use this method after an unsuccessful Run of the operator with CATHomotopySeamLimits diagnostic.
   * Such diagnostic indicates that homotopy stopped on a curve closure, and should be restarted.
   * Return values:
   *   oCrvParamStop    : the stop parameter reached, ie. the CrvParam returned by GetCrvParam() method.
   *   oCrvParamRestart : the init parameter for the second Run of CATHomotopyCrvSur.
   *
   * WARNING: THIS METHOD IS DEDICATED TO CRV / PLN HOMOTOPY. IRRELEVANT USE WITH CRV / SUR HOMOTOPY. */ 
  virtual void GetCrvParams(CATCrvParam & oCrvParamStop, CATCrvParam & oCrvParamRestart) const =0;
};


#endif
