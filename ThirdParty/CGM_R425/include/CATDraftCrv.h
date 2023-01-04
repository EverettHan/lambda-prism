//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATDraftCrv:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Dec. 97      Creation                                       S. Royer
//-----------------------------------------------------------------------------
// 25/03/21 S9L Changes under macro for draft surface streaming to include cylinder
//=============================================================================

#ifndef CATDraftCrv_h
#define CATDraftCrv_h

#include "CATMathDef.h"
#include "CreateDraftCrv.h"
#include "CATCreateDraftCrv.h"
#include "Connect.h"
#include "CATGeoOperator.h"

#define CATDraftCrvNoTwist  1
#define CATDraftCrvTwist    2
#define CATDraftCrvConeUp   3
#define CATDraftCrvConeDown 4
#define CATDraftTwistUp     5
#define CATDraftTwistDown   6

class CATDraftSurface;
class CATCrvParam;
class CATCrvLimits;
class CATPCurve;

// S9L : Draft Untwist Enhancement : Start
const double SPLIT_OFFSET  = 0.01; // @NumValidated
// S9L : Draft Untwist Enhancement : End

class ExportedByConnect CATDraftCrv : public CATGeoOperator
{    
 public:

	CATDraftCrv(CATGeoFactory* factory);

  virtual ~CATDraftCrv();

  virtual CATLONG32 GetMaxLength(double & oLength1,
                            double & oLength2) const=0;
  virtual CATLONG32 GetNumberOfValidAreas() const=0;
  virtual void GetValidArea(CATLONG32 iAreaIndex,
                            CATCrvParam &oStartParam,
                            CATCrvParam &oEndParam,
                            CATBoolean *oLeftZoneIsValid = 0,
                            CATBoolean *oRightZoneIsValid = 0,
                            double * oMinLength = 0,
                            double * oMaxLength = 0) const=0;
  virtual void SetLimits(const CATCrvLimits & iLimits) =0;
  virtual void SetLength(double iStartLength,double iEndLength) =0;
  virtual void GetLength(double &oStartLength,double &oEndLength) =0;
  virtual CATLONG32 IsDraftCanonic() =0;

  // Default is YesNo==1:
  // Only the heights at the valid area limits are evaluated
  // If YesNo=0:
  // The heights are evaluated everywhere inside (and on the border of)
  // the necessary limits intervall (or else inside the Start-EndParam
  // intervall).
  virtual void SetDiagnosticOnlyDraftableAreas(CATLONG32 YesNo) =0;

  // Define parameter intervall (INSIDE the specified
  // Start-End parameters) that needs to be conserved
  // (the necessary limits MUST define a draft-able area!)
  //
  // Always use SetNecessaryLimits in conjunction with
  // SetDiagnosticOnlyDraftableAreas(0)!!!
  virtual void SetNecessaryLimits(const CATCrvLimits &NecessaryLimits) =0;

  // Update the raw heights that were provided in CreateDraftCrv()
  // with respect to the Curve and the Draft angle (this has to be
  // done before Run())
  virtual void UpdateHeightsWithAngle() =0;

  // To specify if the draft is a ReflectLine type.
  // Used to enhance performance.
  virtual void SetDraftReflectLineType();

  // Only available for SquareDraft, not for ConeDraft (default = 1).
  // 0 -> No check.
  // 1 -> Allow you to specify if you want the operator to split on normal
  //      of draft surface inversion with respect to the pulling directiorn.
  // 2 -> Allow to specify which will remain in the end result, thus making
  //      it possible to define inversion points where the volume convexity
  //      along the neutral curve (between Draft surface and iKeptSurface)
  //      changes (please note that the iPCurveOnKeptSurface is mandatory and
  //      only used for this option, and that the provided EdgeCurve must contain
  //      iPCurveOnKeptSurface)
  virtual void SetCriticalPointOption(CATLONG32 iActivate=0,const CATPCurve * iPCurveOnKeptSurface=NULL);

	// S9L : Draft Untwist Enhancement : Start
	virtual void SetSplitAroundTwistZone();
	virtual void SetDraftProfileSampling(CATMathSetOfPointsND * ipCrvParams);
	virtual void GetDraftCrvTwistedZones(CATMathSetOfPointsND *& ipTwistedZones);
	virtual void SetTwistDetectMode(CATLONG32 iTwistDetectMode);
	static const int DraftCrv_DyadicSamplingFactor = 3;
	// S9L : Draft Untwist Enhancement : End
};

#endif
