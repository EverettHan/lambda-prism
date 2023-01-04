// COPYRIGHT DASSAULT SYSTEMES 1999
//===================================================================
//
// CATPositionVsSurfaceBorder

// Class containing only static methods to tell whether a point or
// a pcurve lies on a border (max limit), or corner (for a point)
// of a given surface, and say which border(s) are involved.

// No operator object has to be constructed, static methods must be
// called instead, since no advanced mode is available (saves bytes)

// Usage = detecting and handling closure pcurves, anticipating need
// for extrapolation...
 
//===================================================================
// Jan. 99    Creation (migrating code from Top.Ope.)     A.Deleglise
//===================================================================

#ifndef CATPositionVsSurfaceBorder_H
#define CATPositionVsSurfaceBorder_H

#include "Y30UIUTI.h"
#include "CATIsoParameter.h"
#include "CATCGMVirtual.h"

class CATSurface;
class CATSurLimits;
class CATPCurve;
class CATEdgeCurve;
class CATSurParam;
class CATCrvParam;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATPositionVsSurfaceBorder  : public CATCGMVirtual
{

public:

  // Definition of a function type that returns a binary "closed surface" information 
  // (1=closed, 0=no), intended for handling non periodic closed surfaces (closed sweeps ...)
  // iUorV=0 <=> "U-closed" <=> iso-V (e.g. U axis) are cycles and there exists 2 identical
  //              iso-U <=> same result as method IsClosedU() if the surface is periodic
  // iUorV=1 <=> "V-closed" <=> iso-U (e.g. V axis) are cycles and there exists 2 identical
  //              iso-V <=> same result as method IsClosedV() if the surface is periodic
  // iContext can be used to provide contextual information to the function itself
  // If oMinClosedParm or oMinClosedParm is not null as input, it will point towards 
  // the minimum (or maximum) value taken by the closed parameter (ex: MinU and MaxU if iUorV=0)
  typedef short (*InvestigateClosedSurf)(CATSurface * iSurf, short iUorV, void * iContext,
    double * oMinClosedParm, double * oMaxClosedParm);

  //---------------------------------------------------------------------------
  // Tells whether a surparam or poec is on the border of a surface
  // (in case of a poec, one of its pcurve must be provided to set the surface)

  // Output data oBdList[k] = 1 if border "k" contains the point, otherwise 0
  // with k = 0 -> Umin / 1 -> Umax / 2 -> Vmin / 3 -> Vmax
  // Multiple "1" can be returned if the point is in a corner
  // Returned (short) value is the number of borders answering yes

  // The underlying surface and / or its max or closed limits can be provided to save time,
  // in case of a surparam, one of the two (surface or box) must be provided
  // A parametric tolerance can be input, default = resolution
  static short IsBorder(CATPointOnEdgeCurve * iPoec, CATPCurve * iPCrv, 
                        short * oBdlist, CATSurface * iSurf=0,
                        CATSurLimits * iMaxOrClosedBox=0);

  static short IsBorder(CATSurParam & iSurp, short * oBdlist,
                        CATSurface * iSurf, CATSurLimits * iMaxOrClosedBox=0,
                        double * iSurpTol = 0);

  //---------------------------------------------------------------------------
  // Tells whether a pcurve lies on a border of a surface (not necessarily closed)
  // max or closed limits (iMaxOrClosedBox) can be provided to save time

  // Output data oBdList[k] = +/-1 if border "k" contains the point, otherwise 0
  // with k = 0 -> Umin / 1 -> Umax / 2 -> Vmin / 3 -> Vmax
  // oBdList = +1 if the pcurve runs positively with respect to the isoparametric
  // -1 otherwise (pcurve called anti-isoparametric)
  // 1 non zero answer is expected at most for the four borders.

  // oDetSign is the sign of det(TgPCrv,NormSurf,NormIntPCrv), where TgPCrv
  // is the tangent to the pcurve, NormSurf is the normal to the surface, and
  // NormIntPCrv is normal to this pcurve, tangent to the surface inwards (pointing
  // to the surface interior)
  static short IsBorder( const CATPCurve          * iPCrv,
                         CATSurface               * iSurf,
                         short                    * oBdList,
                         short                    & oDetSign,
                         CATSurLimits             * iMaxOrClosedBox = NULL,
                         CATSoftwareConfiguration * iConfig = NULL,
                         double                   * iTolerance = NULL );

  //---------------------------------------------------------------------------
  // Tells whether an edge-curve lies on a border of a surface
  // Output data oBdList[k] = related pcurve if any, otherwise zero
  // with k = 0 -> Umin / 1 -> Umax / 2 -> Vmin / 3 -> Vmax

  // Multiple pcurves can be returned if the surface is closed, their number is
  // the returned (short) value.
  static short IsBorder( CATEdgeCurve             *  iEdgCrv,
                         CATSurface               *  iSurf, 
                         CATPCurve                ** oBdPCrvList,
                         CATSurLimits             *  iMaxOrClosedBox = NULL,
                         CATSoftwareConfiguration *  iConfig = NULL,
                         double                   *  iTolerance = NULL );

  //---------------------------------------------------------------------------
  // Tells whether a pcurve lies on a closure (opposite borders coincident in
  // 3d space) of a closed surface. Returns zero if the surface is not closed
  // or if the pcurve does not lie on the closure (nor any of them in case of
  // a torus). A degenerate border (pole of sphere) is not a closure.

  // Otherwise returns the closure number (1 or 2), that is intrinsic to the
  // surface. Numbering convention for surfaces with UV parametrization is "1"
  // if the pcurve is equivalent to an "iso-u" closure and "2" for "iso-v".

  // If position versus closure is needed, oOriVersusNaturalClosure = 1 if the
  // pcurve has the same orientation than the natural closure involved (that
  // is, positive iso-U or iso-V) and oDetSign gives the sign of determinant
  // det<NormSurf, TgNaturalClosure, TgSideOfPCurve> where NormSurf is the
  // normal to the surface, the second vector points towards the intrinsic
  // orientation of the closure (tangent to a positive U or V isoparametric on
  // the closure), and the third one is perpendicular to the first two, and
  // points towards the side of the current pcurve with respect to the closure
  // itself.

  // These definitions are designed to fit all closed surfaces regardless
  // of any UV parametrization (eg. algebraic surfaces), provided they have
  // stable numbering convention for closures, intrinsic normal and intrinsic
  // closure orientations.
  // If an "InvestigateClosedSurf" function is provided, it will be used rather
  // than IsClosedU and IsClosedV (which do not handle non periodic closed surfaces)

  static short GetClosureNumber(CATPCurve                * iPCrv,
                                short                    * oOriVersusNaturalClosure=0,
                                short                    * oDetSign = 0,
                                InvestigateClosedSurf      iClosedSurfFunction = NULL,
                                void                     * iClosedSurfContext = NULL,
                                CATSoftwareConfiguration * iConfig = NULL,
                                double                   * iTolerance = NULL );

  //---------------------------------------------------------------------------
  // Tells whether a point on edge-curve lies on a given closure (iCloNum) of a
  // given closed surface, and returns the position of the poec by the sign of
  // determinant det<NormSurf, TgNaturalClosure, TgSideOfPoec> where SideOfPoec
  // is normal to the first two vectors and points towards the side of the poec
  // (i.e. the side of its point-on-pcurve lying on the given surface) with 
  // repect to the closure itself.
  // Closure Number (iCloNum) is 1 if closure line is iso-U and 2 if iso-V
  // If an "InvestigateClosedSurf" function is provided, it will be used rather
  // than IsClosedU and IsClosedV (which do not handle non periodic closed surfaces)

  static short GetPosVsClosure(CATPointOnEdgeCurve * iPoec,
                               CATSurface * iSurf,
                               short iCloNum,
                               InvestigateClosedSurf iClosedSurfFunction = 0,
                               void * iClosedSurfContext = 0);

  //---------------------------------------------------------------------------
  // Scans the points-on-pcurves of a given point on edge-curve that are lying
  // on the closure line of a closed surface. The corresponding pcurves are
  // returned one by one, zero after the last one, or zero at first call (first
  // call means iLastPCurve = null pointer, or is omitted) if no closure line
  // is involved in the given poec.

  // Note that if the poec has no spec on a pcurve lying on a closed surface,
  // though the pcurve is agregated by the owning edge-curve, then no closure
  // will ever be found on this surface even though it might be relevant.

  // Optional output are : position of poec vs closure, as defined hereabove
  // *oPosVsClo = det<NormSurf, TgNaturalClosure, TgSideOfPoec>, and closure
  // number *oNumClo = 1 if involved closure line is iso-U and 2 if iso-V

  // If an "InvestigateClosedSurf" function is provided, it will be used rather
  // than IsClosedU and IsClosedV (which do not handle non periodic closed surfaces)

  static CATPCurve * NextClosure(CATPointOnEdgeCurve * iPoec,
                                 CATPCurve * iLastPCurve,
                                 short * oPosVsClo = 0,
                                 short * oNumClo = 0,
                                 InvestigateClosedSurf iClosedSurfFunction = 0,
                                 void * iClosedSurfContext = 0);

  //---------------------------------------------------------------------------
  // Tells whether an edge-curve has isoparametric pcurve(s) on a given surface,
  // what kind of isoparametrics, and the constant parameter value(s).
  // The short value returned by the method is the number of constant parameters
  // found (one in general, two at most when the edge-curve is a closure line)
  // If the edge-curve proves to be iso-parametric, its orientation versus the
  // surface's non constant parameter is optionnally returned (in *oOrientation)
  static short IsIsoParametric(CATEdgeCurve * iECrv, CATSurface * iSurf,
                               CATIsoParameter & oIsop, double * oParm,
                               short * oOrientation = 0);

  //---------------------------------------------------------------------------
  // Tells whether a pcurve is an isoparametric, of what kind, gives the constant
  // parameter value (oParm) and optionnally the pcurve orientation versus the
  // surface's non-constant parameter. The short value returned is zero if the
  // pcurve is not an iso-parametric, 1 if it is.
  static short IsIsoParametric(const CATPCurve * iPCrv, CATIsoParameter & oIsop,
                               double & oParm, short * oIsopDir = 0);

private:

  // Utility designed to compute all closure information on a surface
  static void GetClosedSurfInfo(CATSurface * iSurf, short oIsClosed[2],
    InvestigateClosedSurf iClosedSurfFunction = 0, void * ClosedSurfContext = 0,
    CATSurLimits * oClosedBoxIfAny = 0);

};
#endif
