// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATSurfaceToCanonic :
//  Operator to replace a given surface by a canonical approximation (plane,
//  cylinder, ...). When it's possible a Bilinear mapping between the surface
//  and it's approximation is given.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jan.  00 PSH Creation                                               P. Sebah
// Oct.  01 STY Modification
// Dec.  03 KLX Geometric Detection Modes
// 11/08/08 NLD Ajout _LinearMappingSpec pour distinguer la spec et le resultat
// 02/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 23/03/11 NLD Suppression CreateCurveToCanonic(). 1ere phase. nodoc nocgmitf
// 06/04/11 NLD Suppression CreateCurveToCanonic(). 2eme phase. suppression
// 31/03/16 KJD (IR429492) Plane Detection in case of procoffset 
// 16/11/16 JSX Dump de la matrice 
//              Passage en static de StaticComputeLimitedPlane et StaticRunOnNURBS
//              Reorganisation annuelle
// 24/03/21 S9L API to activate GeometricDetection to combine all detection algorithms (IR-819887)
// 19/04/21 NLD Smart indent
//=============================================================================

#ifndef CATSurfaceToCanonic_H
#define CATSurfaceToCanonic_H 

#include "Y30UIUTI.h"

#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATIsoParameter.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATGeoOperator.h"
#include "CATCGMOperatorDebug.h"
#include "CATCreateSurfaceToCanonic.h"
#include "CATSurLimits.h"
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATSurLimits.h"

class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATPoint;
class CATCrvParam;
class CATMathPoint;
class CATMathVector;
class CATMathDirection;
class CATMathTransformation2D;
class CATMathPlane;

class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATSurfaceToCanonic : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATSurfaceToCanonic);
  public :

  //-----------------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------------

  // Do not use. Use the CATCreateSurfaceToCanonic function to create such an operator.
   CATSurfaceToCanonic (CATGeoFactory            * iFactory          ,
                        CATSoftwareConfiguration * iConfig           ,
                        CATSurface               * iSurfaceToApproxim,
                        double                     iTolApprox        );

  // Do not use. Use the CATCreateSurfaceToCanonic function to create such an operator.
   CATSurfaceToCanonic (CATGeoFactory            * iFactory          ,
                        CATSurface               * iSurfaceToApproxim,
                        double                     iTolApprox        );

   // Do not use. 
   CATSurfaceToCanonic (CATGeoFactory            * iFactory          ,
                        CATSoftwareConfiguration * iConfig           ,
                        CATLISTP(CATSurface)     * iSurList          ,
                        double                     iTolApprox        );

  // Do not use. Use the Remove function to delete such an operator.
  ~CATSurfaceToCanonic ();


  //-----------------------------------------------------------------------
  //- Settings
  //-----------------------------------------------------------------------

  // Take into account the given limits on the surface.
  // The default value is the max limits of the surface.
  void SetLimits       (CATSurLimits           & iLimits);
  
  void SetListOfLimits (CATLISTP(CATSurLimits) & iLimits);

  //-----------------------------------------------------------------------
  //- Options for the classical way of detection
  //-----------------------------------------------------------------------

  // Find the canonic surface only if a bilinear mapping is defined between the
  // original surface and the canonical surface (default value : no bilinear 
  // mapping is required).
  void SetBilinearMapping ();

  // Find the canonic surface (cylinder) when the original surface is a 
  // revolution surface(nurbs).
  void SetCylinderRecognition ();

  // Activate GeometricDetection mode to combine all detection algorithms
  // NOT supposed to be used with SetBilinearMapping and SetCylinderRecognition
  void SetGeometricRecognition();
  
  //-----------------------------------------------------------------------
  //- Options for the most up to date way of detection
  //-----------------------------------------------------------------------

  // These methods activate GeometricDetection mode, which is the most up to date.
  // They are NOT supposed to be used with SetBilinearMapping and SetCylinderRecognition.
  // You can combine them to activate several detection algorithms.
  // They will search, taking the input tolerance into account, if the input surface is ... :

  // ...a cylinder modulo a bilinear mapping on the parametrization :
  void SearchIsoCylinder ();

  // ...a cone modulo a bilinear mapping on the parametrization :
  void SearchIsoCone ();

  // ...a plane modulo a bilinear mapping on the parametrization :
  void SearchIsoPlane ();

  // ...a sphere modulo a bilinear mapping on the parametrization :
  // (only on RevolutionSurface for the moment)
  void SearchIsoSphere ();

  // ...a plane even if there is no mapping between the parametrizations :
  void SearchPlane ();

  // ...a cylinder with no mapping between the parametrizations :
  // (only on GenericFillet for the moment)
  void SearchNoIsoCylinder ();

  // ...a tore with no mapping between the parametrizations :
  // (only on GenericFillet for the moment)
  void SearchNoIsoTore ();

  // ...a cylinder even if there is no mapping between the parametrizations :
  void SearchCylinder ();

  // ...a Torus even if there is no mapping between the parametrizations :
  void SearchTorus ();

  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------
  /** @nodoc @nocgmitf */
  CATCGMOperatorDebugDeclareRun(CATSurfaceToCanonic,CATGeoOperator);
  // Do not use.
  // Use the Run function from the mother class to launch such an operator.
  /** @nodoc @nocgmitf */
  int RunOperator ();


  //-----------------------------------------------------------------------
  //- Get result
  //-----------------------------------------------------------------------

  // Returns canonical equivalent surface (or return 0 if no canonical equivalent
  // surface has been found), together with the surface limits.
  CATSurface * GetSurface  (CATSurLimits & oLimits);

  // Retrieve the bilinear mapping between the original surface and the canonical
  // surface. (Ucan, Vcan) = oMappingUV * (uSurf, vSurf). The return value is true
  // if a mapping is found.
  CATBoolean GetBilinearMappingToCanonic (CATMathTransformation2D & oMappingUV);

  //-----------------------------------------------------------------------
  //- Miscellanous Services
  //-----------------------------------------------------------------------

  // Do not use. Use GetRuleDirection service

  // Static method designed to check if the input surface is a ruled surface,
  // modulo a tolerance and a bilinear mapping on the parametrization.

  //Inputs:
  //iSurface : the input surface
  //iSurLimits: Surface portion which needs to be checked
  //iTolerance: tolerance for geometric check
  //Output = CATIsoParNoDir if the surface portion is not ruled
  //       = CATIsoParamU if the surface portion is ruled in V (iso-U) direction
  //       = CATIsoParamV if the surface portion is ruled in U (iso-V) direction
  //       = CATIsoParBothDir if the surface portion is ruled in both U & V directions
  static CATIsoParameter IsRuledSurface (const CATSurface   * iSurface   ,
                                         const CATSurLimits & iSurLimits ,
                                               double         iTolerance );

  
  // Start : SUH : 2004:2:9
  
  // Returns whether the input surface to the operator is a ruled surface.
  // Expect useful return value ONLY if SearchRuleDirection(int) is called with a non-zero argument.
  // One can specify the tolerance for geometric check at operator creation and limits of surface to examine via SetLimits.
  
  // To be used after operator Run

  // Output = CATIsoParNoDir if the surface portion is not ruled
  //        = CATIsoParamU if the surface portion is ruled in V (iso-U) direction
  //        = CATIsoParamV if the surface portion is ruled in U (iso-V) direction
  //        = CATIsoParBothDir if the surface portion is ruled in both U & V directions
  CATIsoParameter GetRuleDirection();

  // To set if information about Rule Direction of input surface is required
  // Input:
  // iRuleDirOption = 0  => No search for Rule Direction of input surface is made.
  // iRuleDirOption = 1  => Search for Rule Direction. To get it, use GetRuleDirection().
  // iRuleDirOption = 2  => NO CANONIC RESULT is computed, only search for Rule Direction is made. To get it, use GetRuleDirection().

  // Output = 1 if successful
  //        = 0 otherwise
  // 
  int       SearchRuleDirection(int iRuleDirOption = 1);

  // End : SUH : 2004:2:9

  // For debug only : Checks the result.
  // Return values are 1 in case of success, 0 otherwise.
  // Also returns the maximum computed gap.
  CATLONG32 CheckResult (double & maxgap);

  // For debug only : Checks the result.
  // Return values are 1 in case of success, 0 otherwise.
  // Print traces to cgmout.
  CATLONG32 CheckResult ();

  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;

  //
  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
  //
  private :

  CATSurfaceToCanonic(const CATSurfaceToCanonic&);
  void    operator = (const CATSurfaceToCanonic&);

  int  RunOneSurface      ();
  int  RunMultipleSurfaces();
  void RunOnNURBS         ();
  void RunOnProcOffset    ();
  void RunOnRevolution    ();
  void RevolToSphere      ();
  void RunNoIsoCylinder   ();
  void RunNoIsoTore       ();
  void InitializeCommon   ();
  
  // ajout jsx 121116
  static CATLONG32 StaticComputeLimitedPlane (      CATSoftwareConfiguration * iConfig ,
                                              const CATTolerance             & iTolFact,
                                                    double                     itol    ,
                                                    CATLONG32                  iNbPoint,
                                                    CATLONG32                  iNu     ,
                                                    CATLONG32                  iNv     ,
                                                    CATMathPoint             * iCloud  ,
                                                    CATMathPoint             & oO      ,
                                                    CATMathVector            & oI      ,
                                                    CATMathVector            & oJ      ,
                                                    double                   & oUmin   ,
                                                    double                   & oVmin   ,
                                                    double                   & oUmax   ,
                                                    double                   & oVmax   );

  void RunGeometricDetection   ();
  void RunIsoSurface           ();
  void RunPlane                ();

  CATLONG32 DetectLine         (CATCurve         * iCurve    ,
                                CATCrvLimits     & iLimits   ,
                                double             iTol      ,
                                CATMathDirection & oDirection,
                                double           & oScale    );

  CATLONG32 DetectCircle       (CATCurve         * iCurve    ,
                                CATCrvLimits     & iLimits   ,
                                double             iTol      ,
                                CATMathPlane     & oPlane    ,
                                double           & oRadius   ,
                                CATMathPoint     & oCenter   ,
                                double           & oScale    ,
                                double           & oAngle1   ,
                                double           & oAngle2   );

  CATLONG32 Parallel           (double             iRefDistance,
                                CATMathVector    & v1          ,
                                CATMathVector    & v2          ,
                                CATMathVector   *  oCross      = NULL,
                                double          *  AngErrScale = NULL);

  CATLONG32 Orthogonal         (double iRefDistance, CATMathVector & v1, CATMathVector & v2);

  void      ExtractIsopar      (CATIsoParameter & iDir   ,
                                double            iMin   ,
                                double            iMax   ,
                                CATSurParam     & iParam ,
                                CATCurve       *& oIsopar,
                                CATPoint       *& oPoint ,
                                CATCrvLimits    & oLimits);

  void      UpdateMapping      (CATLONG32 UVSwapped    ,
                                CATLONG32 PointingStart,
                                CATLONG32 PointingEnd  );

  void      NumericalErrorScale(CATMathPoint & Location     ,
                                double       & oDistErrScale,
                                double       & oAngErrScale );

  // kjd 31Mar16 (IR429492) : Detection on the Offset of NURBS surfaces : plane
  // oBox={umin, vmin, umax, vmax}
  // oMapping ={a11,a22,b1,b2}
  // jsx 12/11/16 aout static
  // pkc 29/06/21 c'est bête de ne pas avoir mis un mapping complet en sortie
  // économie de bouts de chandelles?
  // je modifie la signature
  // oMapping = {a11, a12, a21, a22, b1, b2}
  static HRESULT StaticRunOnNURBS (      CATSoftwareConfiguration * iConfig    ,
                                   const CATTolerance             & iTolFact   ,
                                         double                     itol       ,
                                   const CATSurface               * ipSurface  ,
                                         CATMathPlane             & oPlane     ,
                                         double                     oBox    [4],
                                         double                     oMapping[6],
                                         CATLONG32                & oLinearMapping );

   //
  //-----------------------------------------------------------------------
  //- Data
  //-----------------------------------------------------------------------
  //
private :
   // in
   double                     _tol;

   CATSurface               * _SurfaceIn;
   CATSurLimits               _Limits;
   CATLISTP(CATSurface)     * _SurListIn;
   CATLISTP(CATSurLimits)     _LimitsList;
   const CATSurface         * _SurfaceInRep;

   CATLONG32                  _GeometricDetection;
   CATLONG32                  _CylinderRecognition;
   CATLONG32                  _LinearMappingSpec ;
   int                        _SearchRuleDirection; //SUH : 2004:2:9  0 => no search for _RuleDir unless needed. 
                                                    // 1 => search for _RuleDir even if not needed for Canonic result computation. 
                                                    // 2 => search for _RuleDir only, no need to compute Canonic result


   // out
   CATSurface               * _SurfaceOut; 
   CATLONG32                  _LinearMapping;  // voir plus loin *LinearMapping* NLD110808
   double                     _a11, _a22, _a12, _a21, _b1, _b2; // matrix of mapping

   // internal
   CATLONG32                  _Size;
   CATLONG32                  _EraseSurface;


   CATSoftwareConfiguration * _Config;

   CATIsoParameter            _RuleDir; // Rule Direction of input surface found within _Limits
 
  
//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString            _OperatorId;
  static CATGeoOpTimer        _Timer;

public:
  
  /** @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  /** @nodoc @nocgmitf */
  virtual CATExtCGMReplay *IsRecordable  (short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void             WriteInput    (CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void             WriteOutput   (CATCGMStream & os);
  /** @nodoc @nocgmitf */
  virtual CATBoolean       ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void             Dump          (CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void             DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void             DumpOutput    (CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  //virtual void ReadInput(CATCGMStream  & ioStream);
};



//
// Create and remove 
//
ExportedByY30UIUTI CATSurfaceToCanonic * CreateSurfaceToCanonic (CATGeoFactory * iFactory  ,
                                                                 CATSurface    * iSurface  ,
                                                                 double          iTolApprox,
                                                                 CATSkillValue   iMode     = BASIC);

ExportedByY30UIUTI void Remove (CATSurfaceToCanonic * iCanonicOper);
//
// DePrecated 
//
/** @nodoc @nocgmitf */
// Test NLD230311. si on ajoute nocgmitf, l'interface de ce service debile disparaitra-t-elle?
// auquel cas, ensuite on pourra enlever la methode
/*
ExportedByY30UIUTI CATSurfaceToCanonic * CreateCurveToCanonic (CATGeoFactory * i1,
                                                               CATSurface    * i2,
                                                               double          i3,
                                                               CATSkillValue   iMode=BASIC);
*/
#endif







