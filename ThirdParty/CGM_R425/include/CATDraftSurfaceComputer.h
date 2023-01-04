//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATDraftSurfaceComputer:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Aug. 99     Creation                                       NDN
//-----------------------------------------------------------------------------
// 25/03/21 S9L Changes under macro for draft surface streaming to include cylinder
//=============================================================================

#ifndef CATDraftSurfaceComputer_h
#define CATDraftSurfaceComputer_h

class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATDraftSurface;
class CATMathDirection;
class CATMathPoint;
class CATMathVector;
class CATMathSetOfPointsND;
class CATCrvLimits;
class CATLaw;
class CATSoftwareConfiguration;
class CATSurface;
#include "CATListOfCATCrvParams.h"
#include "Connect.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"
#include "CATCGMVirtual.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"


//=============================================================================
enum CATKindOfDiagnostic {NotDoneYet                   = -1,
                          OK                           ,
                          Intersection                 ,
                          IntersectionWithExtrapolation,
                          Deformation,KODeformation    ,
                          KOWithInitialLength          ,
                          KO
                         };
enum CATKindOfDraft      {NeutralDraft                 = 0,
                          ReflectLineDraft             ,
                          VariableDraft
                         };


class ExportedByConnect CATDraftSurfaceComputer : public CATCGMVirtual
{    
 public:

  virtual ~CATDraftSurfaceComputer() {};

  //These Get methods can be called when you want i.e. you don't have to make a Run.  
  virtual CATLONG32           GetMaxLength         (double      & oMaxStartLength,
                                                    double      & oMaxEndLength  ) const = 0;

  virtual CATLONG32           GetNumberOfValidAreas() const = 0;

  virtual void                GetValidArea         (CATLONG32      iAreaIndex        ,
                                                    CATCrvParam &  oStartParam       ,
                                                    CATCrvParam &  oEndParam         ,
                                                    CATBoolean   * oLeftZoneIsValid  = NULL,
                                                    CATBoolean   * oRightZoneIsValid = NULL,
                                                    double       * oStartLength      = NULL,
                                                    double       * oEndLength        = NULL) const = 0;

  // The tangent vector to the Draft surface's rule line is ALWAYS defined by DV!!!!
  // DV is ALWAYS opposite to the Draft pulling direction
  // DU is ALWAYS tangent to the Neutral curve
  virtual void                EvalDraftSurfaceOnTheNeutral(const CATCrvParam   & iParam,
                                                                 CATMathPoint  & Pt    ,
                                                                 CATMathVector & DU    ,
                                                                 CATMathVector & DV    ) const = 0;

  // argument iSoftwareConfig a supprimer
  // - le seul appelant CATDrftRib passe BIEN SUR le meme pointeur que dans le Create ou CATCreate. NLD040716
  virtual void                GetHeightAdjustment         (      double       *  height,
                                                                 CATSoftwareConfiguration* iSoftwareConfig) = 0;


  //oDelta is an array of four double : oDelta[0]=UMin , oDelta[1]=VMin , oDelta[2]=UMax , oDelta[3]=VMax.
  //The result is a positive parametric distance value.
  virtual void                ExtendSurLimits(const CATCrvParam          & ParamOnNeutral ,
                                              const CATMathPoint         & PointToBeInside,
                                              const CATDraftSurface      * Surface        ,
                                              const CATMathSetOfPointsND * Mapping,
                                                    double                 oDelta       [],
                                                    double                 oSpec        []=NULL) const = 0;

  //
  //Any Set method change the resulting DraftSurface.
  //
  virtual void                SetPreviousDraftSurfaceComputer(CATDraftSurfaceComputer * iPrevious,
                                                              CATCrvParam &iParamOnPrevious,CATCrvParam &iParamOnCurrent) = 0;

  virtual void                SetLimits     (const CATCrvLimits          & iLimits     ) = 0;

  virtual void                SetInnerParams(const CATLISTP(CATCrvParam) * iInnerParams) = 0;

  virtual void                SetLength     (      double                  iStartLength,
                                                   double                  iEndLength  ) = 0;

  virtual void                GetLength     (      double                & oStartLength,
                                                   double                & oEndLength  ) = 0;

  //The Run is mandatory in order to call the GetDraftSurface method.
  virtual void                Run           ()                                           = 0;

  //You should have called the Run method just before calling this method.
  //When you call this method, you're in charge of deleting the oMapping.
  virtual CATDraftSurface   * GetDraftSurface     (CATMathSetOfPointsND *& oMapping    ) = 0;

  // To be called only when resulting draft surface is cone or cylinder
  virtual CATDraftSurface   * GetDraftSurfaceCanonic(CATMathSetOfPointsND *& oMapping,
                                                     double                  iStartLimit,
                                                     double                  iEndLimit ) = 0;
  virtual CATDraftSurface   * GetCanonicMapping(CATMathSetOfPointsND *& oMapping)        = 0;

  //You should have called the Run method just before calling this method.
  //To get the limits used on the NeutralCurve for the DraftSurface computation.
  virtual void                GetLimitsOnNeutral  (CATCrvLimits          & oLim        ) = 0;


  //Begin=0 End=1. The beginning is between current and previous, end is between current and next CATDraftSurfaceComputer.
  //If there is no previous or next CATDraftSurfaceComputer, the result is OK at both end.
  virtual CATKindOfDiagnostic GetDiagnostic       (CATLONG32               BeginOrEnd  ) = 0;

  //Set Maximum gap
  virtual void                SetMaxGapC0         (double                  MaxGapC0    ) = 0;

  virtual void                SetMaxGapC1         (double                  MaxGapC1    ) = 0;

  //Set kind of draft : Neutral or ReflectLine draft.
  virtual void                SetKindOfDraft      (CATKindOfDraft          iKindOfDraft) = 0;

  //Just for diagnostic with no call to GetDraftSurface method (light run)
  virtual void                SetOnlyDiagnostic   ()                                     = 0;

  //Default is No -> YesNo=0, else put YesNo to 1
  virtual void                SetKeepCanonicity        (CATLONG32 YesNo)                 = 0;

  //If the diagnostic is Intersection whithin the maxlimits of the curve , the operator can change itself the
  //limits of the NeutralCurve. Default  is Yes -> YesNo=1, else put YesNo to 0
  virtual void                SetExtrapolUntilMaxLimits(CATLONG32 YesNo)                 = 0;

  //If the diagnostic is Intersection whit extrapolation of the curve , the operator can extrapol itself the
  //NeutralCurve. Default  is Yes -> YesNo=1, else put YesNo to 0
  virtual void                SetExtrapol              (CATLONG32 YesNo)                 = 0;

  // Update the raw heights that were provided in CreateDraftCrv()
  // with respect to the Curve and the Draft angle (this has to be
  // done before Run())
  virtual void                UpdateHeightsWithAngle   ()                                = 0;

  //The argument DraftSurface is the result of the GetDraftSurface Method
  virtual void                GetDraftSurParam         (const CATCrvParam      & iParamOnNeutral,
                                                              CATSurParam      & oParamOnDraft  ,
                                                        const CATDraftSurface *  DraftSurface   ) const =0 ;

  // You should have called the Run method just before calling this method.
  // The input DraftSurface should be the returned surface from the GetDraftSurface
  // method corresponding to this CATDrafturfaceComputer.
  // Creates the CATPCurve corresponding to the rule line passing through the
  // low limitation of the generating Neutral curve.
  // NB: The rule line is ALWAYS opposite to the Draft pulling direction
  virtual CATPCurve * CreateStartRuleLine    (const CATDraftSurface * iSurf) const= 0;

  // You should have called the Run method just before calling this method.
  // The input DraftSurface should be the returned surface from the GetDraftSurface
  // method corresponding to this CATDrafturfaceComputer.
  // Creates the CATPCurve corresponding to the rule line passing through the
  // high limitation of the generating Neutral curve.
  // NB: The rule line is ALWAYS opposite to the Draft pulling direction
  virtual CATPCurve * CreateEndRuleLine      (const CATDraftSurface * iSurf) const= 0;

  // Creates the CATPCurve corresponding to the rule line passing through the
  // paramater 
  // NB: The rule line is ALWAYS opposite to the Draft pulling direction
  virtual CATPCurve * CreateInnerRuleLine    (const CATDraftSurface * iSurf, const CATSurParam &iParmOnSur) const= 0;
  virtual void        UseProfileClosure      () = 0;
  virtual CATBoolean  IsCone                 () = 0;
  virtual void        SetTwistLength         (double iStartLength  , double iEndLength ) = 0;
  virtual void        GetTwistLength         (double &oStartLength , double &oEndLength) = 0;
  // S9L : Draft Untwist Enhancement : Start
  virtual void        SetSplitAroundTwistZone() = 0;
  // S9L : Draft Untwist Enhancement : End
  static CATBoolean   AreMaxLimitsOfConeFixed();
  

};

//Create pour draft par enveloppe de cone.
// iStartLength & iEndLength can be either
// - rough values along the Draft direction (in which case they need to be
//   updated with the UpdateHeightsWithAngle() method), or
// - up to date values (that do not need to be submitted to the
//   UpdateHeightsWithAngle() method)
ExportedByConnect 
CATDraftSurfaceComputer * CreateDraftSurfaceComputer   (      CATGeoFactory           * iFactory        ,
                                                              CATCurve                * iNeutralCurve   ,
                                                              CATLONG32                 iOrientation    ,
                                                        const CATMathDirection        & iDirection      ,
                                                              CATAngle                  iAngle          ,
                                                              double                    iStartLength    ,
                                                              double                    iEndLength      ,
                                                        const CATCrvLimits            * iLimitsOnNeutralCurve = 0,
                                                        const CATLISTP(CATCrvParam)   * iInnerParams    = 0,
                                                              CATSkillValue             iMode           = BASIC,
                                                              CATSoftwareConfiguration* iSoftwareConfig = 0);


//Create pour Draft variable/equerre.
// iStartLength & iEndLength can be either
// - rough values along the Draft direction (in which case they need to be
//   updated with the UpdateHeightsWithAngle() method), or
// - up to date values (that do not need to be submitted to the
//   UpdateHeightsWithAngle() method)
// - if iSupportOrn=FALSE then the inverse of the normal on the surface to be drafted
//   will be used for computation.
// - iMapping is a law defined on iLimitsOnNeutralCurve. It is used to get
//   the corresponding angle to a param on the curve.
ExportedByConnect 
CATDraftSurfaceComputer * CATCreateVarDraftSurfaceComputer(      CATGeoFactory           * iFactory        ,
                                                                 CATCurve                * iNeutralCurve   ,
                                                                 CATLONG32                 iOrientation    ,
                                                           const CATCrvLimits            & iLimitsOnNeutralCurve,
                                                                 CATPCurve               * iPCrvOnSTBD     ,//SurfaceToBeDrafted
                                                                 CATEdgeCurve            * iEC             ,
                                                           const CATMathDirection        & iDirection      ,
                                                           const CATLaw                  * iAngleLaw       ,
                                                           const CATLaw                  * iMapping        ,
                                                                 double                    ilength1        ,
                                                                 double                    ilength2        ,
                                                                 CATBoolean                iSupportOrn     ,
                                                           const CATLISTP(CATCrvParam)   * iInnerParams    = 0,
                                                                 CATSkillValue             iMode           = BASIC,
                                                                 CATSoftwareConfiguration* iSoftwareConfig = 0);

ExportedByConnect
void Remove(CATDraftSurfaceComputer *& ToDelete);

#endif
