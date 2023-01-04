#ifndef CATFrFImproveFilletSurfaces_h
#define CATFrFImproveFilletSurfaces_h

//=============================================================================
// Copyright Dassault Systemes Provence 2012-2013, all rights reserved
//=============================================================================
//
// CATFrFImproveFilletSurfaces: virtual class to plugging a fillet continuity improvement
//
//
//=============================================================================
// Usage notes:
//=============================================================================
// 28/06/13 : HLN ; Add iNextFilletPCurve argument in SetInitData 
// 25/01/13 : HLN ; Add iNextConnectionToBeFixed argument in SetInitData
// 23/04/12 : HLN ; Add SetPrevFilletBorderIsoparValue method
// 12-09-11 HLN ; Add typedef CATFrFImproveFilletSurfaces* (*CATFrFImproveFilletSurfacesCreate)
// 05-05-11 MWE ; Creation 
//=============================================================================

#include "Connect.h"
#include "CATCGMVirtual.h"
#include "CATIsoParameter.h"
class CATGeometry;
class CATSurface;
class CATPCurve;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATSurParam;

class ExportedByConnect CATFrFImproveFilletSurfaces : public CATCGMVirtual
{
public :

  virtual ~CATFrFImproveFilletSurfaces();

  virtual void SetInitData(
    // iSupport1 : 1st supporting surface the current fillet has to be adjusted to (along contact trace)
    CATSurface *iSupport1,
    // iSupport2 : The other side, ie 2nd supporting surface the current fillet has to be adjusted to (along contact trace)   
    CATSurface *iSupport2,
    // iResultFilletSurface : Current fillet surface to adjust (by deformation)
    CATSurface *iResultFilletSurface,
    // iResultOrientation : Kind of isoparameter of the section/arc of the current fillet surface
    CATIsoParameter iResultOrientation,
    // optionally : The current fillet surface has to be adjusted to iPreviousFilletGeometry (surface or mergedcurve
    //              build with one previous pcurve and one current pcurve) at a continuity level given through
    //              SetConnectionContinuity method.
    //              . if surface, adjustment is made along a iResultOrientation isopar type. By default, the isopar
    //                value is chosen on the previous surface as its max limit value, the corresponding isopar on
    //                the current surface being then deduced by distance. Otherwise, the isopar value is still
    //                considered on the previous surface and given through the SetPrevFilletBorderIsoparValue method.
    //              . if mergedcurve, adjustment is made along it.
    CATGeometry *iPreviousFilletGeometry = NULL,
    // optionally : -1 : adjustment : Default value, process is done as described above with iPreviousFilletGeometry
    //              0, 1 : fixity : The current fillet surface remains fixed (no deformation) at
    //                     iPrevConnectionToBeFixed continuity level along the considered isopar/pcurve
    int iPrevConnectionToBeFixed = -1,
    // optionally : The current fillet surface has to be fixed along iNextFilletPCurve at a continuity level given
    //              by iNextConnectionToBeFixed below.
    //              . if NULL, fixity is made along a iResultOrientation isopar type. The isopar value is the max
    //                limit value on the current surface.
    //              . if pcurve, fixity is made along it.
    CATPCurve *iNextFilletPCurve = NULL,
    // optionally : -1 : freedom : Default value, no constraints, thus deformation is any
    //              0, 1 : fixity : The current fillet surface remains fixed (no deformation) at
    //                     iNextConnectionToBeFixed continuity level along the considered isopar/pcurve
    int iNextConnectionToBeFixed = -1
    ) = 0; 
  //
  // set the user's required level continuity on each side
  // [0] on iBody1
  // [1] on iBody2
  // [2] on iPreviousFilletGeometry
  //
  //Default value: 1 = G1
  //
  virtual void SetConnectionContinuity(int iContTrace1, int iContTrace2, int iContInterFilletFaces)=0;
  //
  // set user's tolerances to be reached according to the required level continuities
  //
  virtual void SetTolerances(double iG0Tol, double iG1Tol, double iG2Tol, double iG3Tol)=0;
  //
  // set user's parameters to be reached 
  //
  virtual void SetParameters(int iMaxOrderU, int iMaxOrderV, int iMaxSegmentsU, int iMaxSegmentsV, int iFixMode=0)=0;
  //
  // set traces on the surface supports for constraints if they are different to the boundaries of iResultFilletSurface
  // by default the constraints are on the projected boundaries of iResultFilletSurface
  //
  virtual void SetTraces(CATPCurve *iTrace1, CATPCurve *iTrace2)=0;
  //
  // set param value of previous fillet isoparameter as border to be constraint
  // NB : if iResultOrientation is an isoU take the V parameter value, else if isoV take the U parameter value
  //
  virtual void SetPrevFilletBorderIsoparValue(const CATSurParam &iPrevIsopar)=0;
  //
  // set the ratio Length isoU/Length isoV (3D)
  virtual void SetRatioIsosBords(double iRatio)=0;
  //
  // allow to define the constraints an MapX instead of 3D curve
  // 0 Without MapX Default
  // 1 With MapX
  //
  virtual void SetMapXConstraint(int iWithMapX)=0;
  //
  //                  Returns : 1 OK, 0 KO no result
  virtual int Run()=0;

  virtual void GetResult(CATSurface *&oNewFilletSurface)=0;
};

// 
typedef CATFrFImproveFilletSurfaces* (*CATFrFImproveFilletSurfacesCreate) (CATGeoFactory *iFactory, CATSoftwareConfiguration *iSoftwareConfiguration);    

#endif
