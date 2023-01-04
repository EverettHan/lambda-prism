// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATExtrapolSurface :
// Class for extrapoling a CATSurface.
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Jun. 98  Creation                          L. Alt
// 11/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 04/03/09 RNO Ajout RunOnSubdivSurface
// 25/04/14 R1Y Added Debug_DrawSurfaceLimits().
// 15/02/16 R1Y Added RunOnGenericFillet() (for IR-345191).
// 01/06/16 JSX remove GetSurfaecSide
// 24/02/17 JSX AJout "nocgmitf" pour AllowLargeGapInBisector
//                ajout AllowRunOnGenericFillet(CATBoolean iAllow);
// 20/11/17 R1Y Added GetExtrapolParamLength
// 29/10/18 R1Y Allowed the input extrapolation lengths to be 2d values
// 12/03/20 Q48 Headers etc for math versioning
// 11/05/20 SMT1 RunOnForeignSurface
//=============================================================================

#ifndef CATExtrapolSurface_H
#define CATExtrapolSurface_H 

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSkillValue.h"
#include "CATMathVector2D.h"
#include "CATSurParam.h"
#include "CATSurLimits.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATExtrapolSurfaceSide.h"
#include "CATGeoOpDebug.h"
#include "CATExtrapolVectFormEnum.h"

#include "CATCGMOperatorDebug.h"

class CATSurface;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurveTransientExtrapolManager;
class CATEdgeCurve;
class CATPCurve;

class ExportedByY30C3XGG CATExtrapolSurface : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATExtrapolSurface);
public :  
  //-----------------------------------------------------------------------
  //- Enums for parametric surface sides.
  //-----------------------------------------------------------------------
  enum CATSurfaceSide
  {
    SideUMin = CATExtrapolSurfaceSideUMin,
    SideUMax = CATExtrapolSurfaceSideUMax,
    SideVMin = CATExtrapolSurfaceSideVMin,
    SideVMax = CATExtrapolSurfaceSideVMax,
    SideUMinVMin = CATExtrapolSurfaceSideUMinVMin,
    SideUMaxVMin = CATExtrapolSurfaceSideUMaxVMin,
    SideUMinVMax = CATExtrapolSurfaceSideUMinVMax,
    SideUMaxVMax = CATExtrapolSurfaceSideUMaxVMax,
    SideUMinUmax = CATExtrapolSurfaceSideUMinUmax,
    SideVMinVmax = CATExtrapolSurfaceSideVMinVmax,
    AllSides     = CATExtrapolSurfaceSideUMinUmaxVMinVMax
  };

  //-----------------------------------------------------------------------
  //- Enums for parametric surface sides.
  //-----------------------------------------------------------------------
  enum CATExtrapolVectForm
  {
    Form_Unknown = CATExtrapolVectForm_Unknown,
    Form_2d      = CATExtrapolVectForm_2d,
    Form_3d      = CATExtrapolVectForm_3d
  };

  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------
  //
  //- iSurfaceToExtrapolate est la surface a extrapoler.
  //- iStart est le parametre ou on se trouve lorsqu'on veut extrapoler. Il 
  //  doit etre en Maxlimit sur au moins un des bords de la surface a extra-
  //  poler
  //- iSurfaceSide indique sur quel(s) bord(s) de la surface se trouve le
  //  point iStart (afin d'eviter des tests numeriques en parametres). Con-
  //  vention : 0 = none, 1 = Umin, 2 = Umax, 3 = Vmin, 4 = Vmax (c'est DPS
  //  qui a pris cette convention pour l'homotopie). Il y a les flags pour
  //  les diagonales en plus.
  //- iVectorEstimation is an estimate (in either 2D or 3D, depending on the
  //  value of iVectorEstimationForm) of the extrapolation lengths.
  //  D'autres signatures peuvent etre envisagees.
  //- iAllowSurfaceCreation est un flag qui, si il vaut 0, interdit a l'al-
  //  gorithme de creer une nouvelle surface (l'appelant est suppose savoir
  //  qu'on se trouve dans un tel cas).
  //- iVectorEstimationForm is a flag that indicates the form of the input
  //  values of iVectorEstimation (as either unknown, 2d, or 3d).
  //-----------------------------------------------------------------------
  CATExtrapolSurface(      CATGeoFactory            * iFactory,
                           CATSurface               * iSurfaceToExtrapolate,
                           CATSurParam              * iStart,
                           CATSurfaceSide             iSurfaceSide, 
                     const CATMathVector2D          & iVectorEstimation,
                           short                      iAllowSurfaceCreation = 1,
                           CATSoftwareConfiguration * iConfig = 0,
                     const CATExtrapolVectForm        iVectorEstimationForm = Form_Unknown);

  ~CATExtrapolSurface();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  // Returns extrapolated (or created) surface. Result can be the surface to
  // extrapolate itself (if it was extended, or if it is closed), or a newly
  // created surface.
  // 
  // Also returns parameter that matches iStart on the extrapolated surface.  
  // There are 3 cases :
  //    - surface was extended : then this parameter is the same as iStart in
  //      the constructor (same pointer).
  //    - surface is closed, and the extrapolation passed the closure. Then
  //      this parameter is the match of iStart on the other side of the sur-
  //      face closure
  //    - a new surface was created. Then this parameter is the match of iStart
  //      on the new surface
  // Surface side (0 to 8) are also provided as an output to be more explicit.
  //-----------------------------------------------------------------------
  CATSurface * GetResult(CATSurParam ** oNewParam);

  // enum CATSolutionDiagnostic { NoSolution , SolutionOK, CaseNotTreated };
  // CATSolutionDiagnostic GetSolutionDiagnostic();

  // Triggers the extrapolation
  //-----------------------------------------------------------------------
  /** @nodoc @nocgmitf */
  CATCGMOperatorDebugDeclareRun(CATExtrapolSurface, CATGeoOperator);

  /** @nodoc @nocgmitf */
  int RunOperator();

  // Check for an existing result with the same inputs
  //-----------------------------------------------------------------------
  CATSurface * CheckForExistingResult(CATSurface     * iSurfaceToExtrapolate,
                                      CATSurfaceSide   iSurfaceSide);

  // Stores extrapolated surface as an attribute on the surface itself.
  //-----------------------------------------------------------------------
  void StoreAsExistingResult(CATSurface     * iSurfaceToExtrapolate,
                             CATSurface     * iExtrapolatedSurface,
                             CATSurfaceSide   iSurfaceSide);

  // Static function to obtain the parameter-space value of the extrapolation length in either the U- or V-parameter direction. 
  static double GetExtrapolParamLength(      CATSoftwareConfiguration * const   iConfig,
                                       const CATTolerance                     & iTolObject,
                                       const CATSurface               * const   iSurface,
                                       const CATSurParam                      & iStartParam,
                                       const CATBoolean                         iIsParamDirU,
                                       const double                             iExtrapol3dLength);

  // Different methods for different kinds of surfaces
  //-----------------------------------------------------------------------
  void RunOnPlane();
  void RunOnCylinder();
  void RunOnNurbsSurface();
  void RunOnSweepSurface();
  void RunOnConnect();
  void RunOnGenericFillet();
  void RunOnDraft();
  void RunOnTabCylinder();
  void RunOnRevolSurface();
  void RunOnOffsetSurface();
  void RunOnDirectionalSurface();
  void RunOnSpecSurface();
  void RunOnSubdivSurface();
  void GenerateLongerSurface();
  void GetOtherSurfaceEnd();
  void RunOnOffsetWithRepGenericFillet();
  void RunOnForeignSurface();

//JSX010616  CATSurfaceSide GetSurfaceSide();

  short NeedsExtrapolationOnSide(CATSurfaceSide iSide);

  // ... etc

  // Allows large gap in extrapolation of the edge curve underlying a bisector
  // surface. The larger gap allowed is an internal tolerance of the factory.
  // JSX 24/02/2017 AJout "nocgmitf"
   /** @nodoc @nocgmitf */
  void AllowLargeGapInBisector(CATEdgeCurveTransientExtrapolManager * ECTEMan);
  
private:
   
  // Function to store the 3d extrapolation lengths.
  // If the input extrapolation lengths are 2d then they are converted into 3d lengths and stored; otherwise, the input lengths are just stored.
  void Store3dExtrapolLengths();

  // GenericFillet "alone" are not extrapolated.
  // they should be a REP of a CATFillet or a CATOffset surface
  void AllowRunOnGenericFillet(CATBoolean iAllow);

  void RunOnSpecSurface2();
  CATLONG32 GetSupportMaxLimits_AsOnPC1(CATEdgeCurve * EC,
                                        CATPCurve    * PC1,
                                        CATCrvLimits & SupportMaxLimits_AsOnPC1);

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private :

  // IN
  CATSoftwareConfiguration * _Config;

  CATSurface      * _SurfaceToExtrapolate;
  CATSurParam       _StartParam;
  CATMathVector2D   _InputVectorEstimation;
  CATSurfaceSide    _SurfaceSide;
  short             _AllowSurfaceCreation;
  CATEdgeCurveTransientExtrapolManager * _ECTEMan; 
  CATBoolean        _AllowRunOnGenericFillet;
  CATExtrapolVectForm _VectorEstimationForm;

  // INTERNAL
  CATMathVector2D   _VectorEstimation;  // initialised to _InputVectorEstimation, and modified if _VectorEstimationForm is equal to Form_2d

  // OUT
  CATSurface      * _ExtrapolatedSurface;
  CATSurParam       _NewParam;
  short             _NeedsExtrapolationOnSide[8];

  // internal
  CATSurLimits _InitialMaxLimits;



  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 

  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime,
                                short & VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & ioStream);
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  virtual CATBoolean ValidateOutput(CATCGMStream & ioStream,
                                    CATCGMOutput & os,
                                    int            VersionNumber = 1);
  /** @nodoc @nocgmitf */
  virtual void Dump(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream & ioStream,
                          CATCGMOutput & os,
                          int            VersionNumber = 1);
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  public:
  
  GEOPDEBUG_CMD(static CATUnicodeString StringFromExtrapolSide(const CATSurfaceSide))

  private:
  
  GEOPDEBUG_CMD(void Debug_DrawSurfaceLimits(      CATSurface   * const iSurface,
                                             const CATSurLimits &       iMaxSurLimits))
};


ExportedByY30C3XGG CATExtrapolSurface * CreateExtrapolation(      CATGeoFactory                           * iFactory,
                                                                  CATSurface                              * iSurfaceToExtrapolate,
                                                                  CATSurParam                             * iStart,
                                                                  CATExtrapolSurface::CATSurfaceSide        iSurfaceSide,
                                                            const CATMathVector2D                         & iVectorEstimation,
                                                                  short                                     iAllowSurfaceCreation = 1,
                                                                  CATSkillValue                             iMode = ADVANCED,
                                                                  CATSoftwareConfiguration                * iConfig = 0,
                                                            const CATExtrapolSurface::CATExtrapolVectForm   iVectorEstimationForm = CATExtrapolSurface::Form_Unknown);

ExportedByY30C3XGG void Remove(CATExtrapolSurface *& ExtrapolOper);

#endif
