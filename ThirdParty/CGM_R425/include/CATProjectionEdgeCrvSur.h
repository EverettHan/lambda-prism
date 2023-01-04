#ifdef _Coverage_GOO
// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATProjectionEdgeCrvSur:
//  class used to project an EdgeCurve on a surface when it is close to the
//  surface.
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Jul. 98   Creation                                   X. Gourdon
//=============================================================================

#ifndef CATProjectionEdgeCrvSur_H
#define CATProjectionEdgeCrvSur_H

#include "Y30E3PMG.h"
#include "CATSkillValue.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

class CATCrvLimits;
class CATSurLimits;
class CATGeoFactory;
class CATEdgeCurve;
class CATCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCurve;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------------
class ExportedByY30E3PMG CATProjectionEdgeCrvSur : public CATCGMVirtual
{
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  CATProjectionEdgeCrvSur (CATGeoFactory *iFactory,
                           CATSoftwareConfiguration *iConfig,
                           CATEdgeCurve  *iEdgeCurve,
                           const CATPointOnEdgeCurve * iPOECStart,
                           const CATPointOnEdgeCurve * iPOECEnd,
                           CATSurface    *iSurface);

  ~CATProjectionEdgeCrvSur();
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  
  //
  // Setting methods
  //
  // Precise which representant of the EdgeCurve should be projected on iSurface
  void SetCurveToProject(CATCurve * iCrv);
  // Gives the initial parameter of the projection on iSurface
  void SetInitSurParam(const CATSurParam & iInitParam);
  // Precise on which SurLimits we should work for iSurface
  void SetLimits(const CATSurLimits & iSurLimits);
  // specify an array of incidents EdgeCurves. In that way, the solution of the
  // problem is first search in this array of EdgeCurve and it avoid to create
  // a new EdgeCurve if one of these is solution.
  void SetIncidentEdgeCurves(CATEdgeCurve ** iTabECrv, const CATLONG32 iNbECrv);

  //
  // Getting methods 
  //
  // The returned EdgeCurve can be 0 if no solution was found
  // It can be equal to one of the EdgeCurves specified in the incident edgecurves
  CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve * & oPOECStart, 
                              CATPointOnEdgeCurve * & oPOECEnd);
  

  // Returns the orientation of the created EdgeCurve with respect to ECrv
  CATLONG32 GetOrientation();
  

  // Running the operator
  void Run();
private:
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration *_Config;
  const CATSurface * _Surf;
  CATSurParam _StartSurf, _EndSurf;

  CATEdgeCurve * _ECrv;
  const CATPointOnEdgeCurve * _StartECrv, * _EndECrv;

  CATCurve * _Crv; // Representant of _Ecrv to project
  CATBoolean _IsInitSurParamKnown;
  CATSurParam _InitSurParam;

  CATEdgeCurve ** _TabECrv;
  CATLONG32 _NbECrv;

  CATEdgeCurve * _OutputECrv;
  CATPointOnEdgeCurve * _StartOutputECrv, * _EndOutputECrv;
  CATLONG32 _Orientation;
};

ExportedByY30E3PMG CATProjectionEdgeCrvSur * 
CreateProjection (CATGeoFactory *iFactory,
                  CATEdgeCurve  *iEdgeCurve,
                  const CATPointOnEdgeCurve * iPOECStart,
                  const CATPointOnEdgeCurve * iPOECEnd,
                  CATSurface    *iSurface,
                  CATSkillValue  mode=BASIC);


ExportedByY30E3PMG void Remove(CATProjectionEdgeCrvSur * Oper);

#endif
#endif

