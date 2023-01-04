
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATReportEdgeCrvSur :
// Class for reporting a point on a PCURVE onto a point to another
// PCURVE in the same EDGECURVE intersected with a given surface.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Mar.  98 PSH Creation                                             X. Gourdon
// 14/09/21 NLD Detabulation, Mise au propre, Smart indent
//=============================================================================

#ifndef CATReportEdgeCrvSur_H 
#define CATReportEdgeCrvSur_H 

#include "Y30C3XGG.h"

#include "CATIntersectionEdgeCrvSur.h"
#include "CATSurParam.h"
#include "CATCreateReportEdgeCrvSur.h"

class CATSurface;
class CATPCurve;
class CATEdgeCurve;
class CATGeometricProfile;
class CATGeoFactory;

class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATReportEdgeCrvSur : public CATIntersectionEdgeCrvSur
{
  public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
   CATReportEdgeCrvSur (      CATGeoFactory            * iFactory  ,
                              CATSoftwareConfiguration * iConfig   ,
                              CATEdgeCurve             * iECrv     ,
                        const CATPointOnEdgeCurve      * iPOECStart,
                        const CATPointOnEdgeCurve      * iPOECEnd  ,
                              CATPCurve                * iPCrv0    ,
                              CATPCurve                * iPCrv1    ,
                              CATSurface               * iSurf     ,
                              CATPointOnEdgeCurve      * ioPOEC0   ,
                              CATSurParam              & iSurParam0,
                       const double                      iTolerance);

  ~CATReportEdgeCrvSur  ();


  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  void                  Run ();

  // No MergedCurve creation
  void                  SetNoMergedCurveCreation();

  // Inhibit any new spec addition to the provided POEC
  void                  SetNoAddSpecOnPOEC();

  // Return 1 if a solution exists, else return 0
  CATBoolean            IsSolution();

  // Position on iSurf of the reported intersection
  void                  GetSurParam(CATSurParam & oSurParam) const;
  // signature of the reported intersection
  CATIntersectionSign   GetSignature() const;

  
  // Return true if the report results in an isolated solution. In this case,
  // ioPOEC0 is modified and contains a new spec on iPCrv1.
  CATBoolean            IsIsolatedSolution() const;

  // If IsIsolatedSolution is false, the use of the following methods is allowed.
  CATMergedCurve      * GetMergedCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd);

  // If SetNoMergedCurveCreation() has been called, this method permits to have the output POEC
  CATPointOnEdgeCurve * GetOuputPointOnEdgeCurve();

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private:
  CATPointOnEdgeCurve * _ioPOEC,
                      * _OutputPOEC;
  double                _Tol;
  CATSurParam           _SurParam0,
                        _SolParam;
  CATLONG32             _IsSolution; // = 0 if no solution, = 1 if POEC solution, = -1 if merged curve solution
  CATBoolean            _MergedCurveCreation;
  CATBoolean            _AddSpecOnPOEC; // defines whether it's ok to add a spec to the provided POEC
};
#endif
