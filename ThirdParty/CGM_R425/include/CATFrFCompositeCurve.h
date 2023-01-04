#ifndef CATFrFCompositeCurve_H
#define CATFrFCompositeCurve_H

#define CATFrFCompositeCurveStream            "en test NLD80214"
#define CATFrFCompositeCurveWithAdvancedBoxes "13/10/09"

// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATFrFCompositeCurve:
// Interface class of Guide Object for the Generalized Sweep Operator.
//
//==========================================================================
//
// Usage notes:
//
//==========================================================================
// November 97  Creation                                    CPL
// February 98  Continuity,Closure,Check,Limit,Replace      ALM
// November 98  DeepClone: Clone Geometry                   CPL
// November 98  IsNotALimit                                 JBX
// November 98  IsSuperior,IsEqualWithResolution,PositionOf JBX - ALM
// December 98  PositionOf(3 arguments)                     ALM
// December 98  GetParametricLength, GetSignedLength        CPL
// December 98  Perfos (inline et void)                     ALM
// December 98  Calcule de la MathBox                       JBX
// January  99  Ajout argument iMode a DeepClone            NLD
// 30/07/99 NLD dizaines de iMode dans DeepClone 
// 30/09/99 DHN iMode dans GetContinuityCvCv
// 28/10/99 ALM IsEqualWithTolerance
// 10/02/00 ALM Correctifs IsNotALimit,IsEqualWithTolerance,
//              GetSignedLength. Nouvelle methode : Compare. ==> #define
// 23/06/00 CPL IsEqual Test si deux Ccvs sont identiques
// 19/01/01 NLD AddRef(), Release()
// 08/03/01 CPL Ajout de IsDegenerateCrv
// 22/05/01 NDN GetParamFromLength
// 31/05/01 CPL Implementation EvalNormalAndDerivOnSupport
//    05/02 MNA Rajout de diverses methodes suite a la mise en place de la nouvelle Ccv (+MC)
// 13/06/02 NLD Ajout Dump()
// 17/12/02 NLD Ajout de tolerance a PositionOf()
// 22/01/03 NLD Ajout de tolerance a IsNotALimit()
// 23/01/03 NLD Ajout de IsALimit(), qui rend la limite exacte
// 22/08/03 MNA Ajout de SetSoftwareConfiguration suite au Versionning de CATMassProperties1D
// 16 06 04 JSX Ajout de IsOneCrvC1Continuous();
// 18/06/04 NLD Ajout ProtectedGetMapping(), ProtectedSetMapping()
//              pour memorisation et calcul d'un seul mapping par CCV
// 22/06/04 NLD Argument iRemoveOld à ProtectedSetMapping()
// 04/01/05 NLD Ajout de SetDomains() et GetDomains()
// 04/10/05 NLD GetEquivalentParamOnPCurve() rend de maniere optionnelle la derivee
//              du changement de parametre
// 13 01 06 JSX GetContinuityCrv Ajout de l'argument icrv permettant de limiter la recherche a une courbe + const
// 13 07 06 NLD DebugOnlySaveAsBody() remonte ici dans la classe mère
// 21 02 07 NLD GetTolerance() remonte ici dans la classe mère
// 09 03 07 NLD Ajout ListPOfCATFrFCompositeCurve
// 07 08 09 NLD Ajout #define SpecialInfiniteContinuityQuery (pour le 1000 en dur)
//              et    #define SpecialMaxDiscontinuityParamsByCrv (pour le 10 en dur)
// 13/10/09 NLD Gestion des CATMathAdvancedBox:
//              Ajout GetAdvancedBoxes()
// 09/12/09 NLD Definition de nomenclature pour les #define partages:
//              SpecialInfiniteContinuityQuery     devient CATFrFCompositeCurve_SpecialInfiniteContinuityQuery
//              SpecialMaxDiscontinuityParamsByCrv devient CATFrFCompositeCurve_SpecialMaxDiscontinuityParamsByCrv
// 19/05/10 JSX Ajout d'une troisieme signature pour GetContinuityCvCv
//              Cette methode utilise GContinuity et est compatible avec le CleanCurve
// 18/02/14 NLD Le stream passe de CATMathStream a CATCGMStream, avant son activation pour CGMReplays
//              Activation du stream
//              Smart indent (1)
// 05/04/17 NLD Smart indent (2) (complet)
//==========================================================================
//
//
#include <CATGMOperatorsInterfaces.h>

#include <CATListOfCATCurves.h>
#include <CATListOfCATPCurves.h>
#include <CATListOfCATEdgeCurves.h>
#include <CATListOfInt.h>

#include <CreateFrFCompositeCurve.h>
#include <CATCGMVirtual.h>

class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATCrvLimits;
class CATCrvParam;
class CATSurParam;
class CATSurface;
class CATMathPoint;
class CATFrFCCvParam;
class CATCrvEvalCommand;
class CATMathVector;
class CATMathDirection;
class CATCloneManager;
class CATGeoFactory;
class CATTolerance;
class CATMathBox;
class CATMathAdvancedBox;
class CATCGMOutput;
class CATFrFCompositeCurveMapping;
class CATMathStream;
class CATCGMStream;
class CATSoftwareConfiguration;
// Je passe par des macros intermédiaires car CATLISTP perturbe l'analyseur de syntaxe de Sniff
//   Nicolas 03/03/03
#define CATFrFCompositeCurve_ListPOfCATCurve     CATLISTP(CATCurve)
#define CATFrFCompositeCurve_ListPOfCATPCurve    CATLISTP(CATPCurve)
#define CATFrFCompositeCurve_ListPOfCATEdgeCurve CATLISTP(CATEdgeCurve)
#define ListPOfCATFrFCompositeCurve              CATLISTP(CATFrFCompositeCurve)

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFCompositeCurve : public CATCGMVirtual
{
 public :

  //-------------
  // Destructor
  //-------------

  virtual                                         ~CATFrFCompositeCurve     ();

  //-------------
  // Evaluators
  //-------------
  virtual void                                     Eval                     (const CATFrFCCvParam    & iCCvPar      ,
                                                                             const CATCrvEvalCommand & iCommand     ,
                                                                                   CATMathPoint     *  oPoint       ,
                                                                                   CATMathVector    *  oFirstDeriv  = NULL,
                                                                                   CATMathVector    *  oSecondDeriv = NULL,
                                                                                   CATMathVector    *  oThirdDeriv  = NULL) const = 0;

  virtual void                                     EvalPoint                (const CATFrFCCvParam    & iCCvPar      ,
                                                                                   CATMathPoint     *  oPoint       ) const = 0;

  virtual void                                     EvalPointUVOnSupport     (const CATFrFCCvParam    & iCCvPar      ,
                                                                                   CATSurParam       & oSurParam    ) const = 0;

  virtual void                                     EvalFirstDeriv           (const CATFrFCCvParam    & iCCvPar      ,
                                                                                   CATMathVector    *  oFirstDeriv  ) const = 0;

  virtual void                                     EvalNormalOnSupport      (const CATFrFCCvParam    & iCCvPar      ,
                                                                                   CATMathDirection  & oNormal      ) const = 0;

  virtual void                                     EvalNormalOnSupport      (const CATFrFCCvParam    & iCCvPar      ,
                                                                                   CATSurface       *& oSurf        ,
                                                                                   CATSurParam       & oSurPar      ,
                                                                                   CATMathDirection  & oNormal      ) const = 0;

  virtual void                                     EvalNormalAndDerivOnSupport
                                                                            (const CATFrFCCvParam    & iCCvPar      , 
                                                                                   CATMathVector     & oNormal      , 
                                                                                   CATMathVector     & odNormal     ) const = 0;

  virtual void                                     EvalNormalCurvatureOnSupportInOneDir
                                                                            (const CATFrFCCvParam    & iCCvPar      ,
                                                                             const CATMathDirection *  iDirection   ,
                                                                                   double            & oCurvature   ) const = 0;

  virtual void                                     FastEval                       (CATLONG32           iCrvInd      ,
                                                                                   double              iGParam      , 
                                                                                   CATMathOption       iOption      ,
                                                                                   double           *  oP           ,
                                                                                   double           *  odP          ,
                                                                                   double           *  od2P         ,
                                                                                   double           *  od3P         ) const = 0;

  virtual void                                     FastEvalPoint                  (CATLONG32           iCrvInd      ,
                                                                                   double              iGParam      ,
                                                                                   double           *  oPoint       ) const = 0;

  virtual void                                     FastEvalPointUV                (CATLONG32           iCrvInd      ,
                                                                                   double              iGParam      ,
                                                                                   double           *  oUV          ) const = 0;

  virtual void                                     FastEvalFirstDeriv             (CATLONG32           iCrvInd      ,
                                                                                   double              iGParam      ,
                                                                                   double           *  oFirstDeriv  ) const = 0;

  virtual void                                     FastEvalNormal                 (CATLONG32           iCrvInd      ,
                                                                                   double           *  iUV          ,
                                                                                   double           *  oNormal      ) = 0;

  virtual void                                     FastEvalNormalCurvatureInOneDir(CATLONG32           iCrvInd      ,
                                                                                   double           *  iUV          ,
                                                                                   double           *  iDirection   ,
                                                                                   double            & oCurvature   ) const = 0;

  //----------------------
  // References management
  //----------------------
  virtual int                                       AddRef                        () = 0;

  virtual int                                       Release                       () = 0;

  //----------------------
  // Set and Get Methods
  //----------------------
  virtual CATLONG32                                 GetNumberOfCurves             ()                                  const = 0;

  virtual CATFrFCompositeCurve_ListPOfCATCurve    * GetCurves                     ()                                  const = 0;

  virtual CATCurve                                * GetOneCurve                   (CATLONG32           iIndex       ) const = 0;

  virtual CATPCurve                               * IsTherePCurveData             (CATLONG32           iIndex       ,
                                                                                   CATLONG32         * ioOrn        = 0   ,
                                                                                   CATCrvLimits      * ioLimits     = NULL) const = 0;

  //Internal Use - Beginning
  virtual CATFrFCompositeCurve_ListPOfCATPCurve   * GetPCurves                    ()                                  const = 0;

  virtual CATPCurve                               * GetOnePCurve                  (CATLONG32           iIndex       ) const = 0;

  virtual CATBoolean                                IsTherePCurveData             ()                                  const = 0;

  virtual CATFrFCompositeCurve_ListPOfCATEdgeCurve* GetMergedCurves               ()                                  const = 0;

  virtual CATEdgeCurve                            * GetOneMergedCurve             (CATLONG32           iIndex       ) const = 0;

  // rend le parametre equivalent, et la derivee de ce parametre par rapport au parameter entré,
  // si demandee (ces parametres etant alors vus en tant que parametre globaux via GetParam())
  virtual void                                      GetEquivalentParamOnPCurve    (CATLONG32           iIndex       ,
                                                                                   CATCrvParam       & iParamRef    ,
                                                                                   CATCrvParam       & iParamOut    ,
                                                                                   double           *  oDeriv       = 0) const = 0;

  virtual CATBoolean                                IsThereMergedCurveData        ()                                     const = 0;
  //Internal Use - End

  // Get Max diagonal size in the sense of bounding boxes
  virtual double                                    GetMaxDiagonalSize            ()                                     const = 0;

  // Get extremities
  virtual void                                      GetExtremities                (CATFrFCCvParam    & oStartCCvParam,
                                                                                   CATFrFCCvParam    & oEndCCvParam  )   const = 0;
  // Get one CrvLimits     0 <= iIndex < nbcurves
  virtual CATCrvLimits                              GetOneCrvLimits               (CATLONG32           iIndex        )   const = 0;

  //
  //GetSoftwareConfiguration()
  //

  virtual CATSoftwareConfiguration                * GetSoftwareConfiguration      ()                                     const = 0;
  
  //
  // SetSoftwareConfiguration()
  //
  virtual void                                      SetSoftwareConfiguration      (CATSoftwareConfiguration *  iSoftwareConfiguration) =0;
  //
  // Set one CrvLimits     0 <= iIndex < nbcurves
  //
  virtual void                                      SetOneCrvLimits               (CATLONG32           iIndex        ,
                                                                                   CATCrvLimits      & iCrvLimits    ) = 0;

  //
  // Get one Crv limit    0 <= iIndex < NbCurves
  //                      0 <= iExtremity <= 1
  // gives the crvparam of the curve iIndex, of the extremity
  // 0 or 1 (start or end) testing the curve orientation.
  // (for example with a iExtremity = 1 and a curve orientation
  // negative the methods gives the StartLimit of the curve).
  virtual CATCrvParam                               GetOneCrvLimit                (CATLONG32           iIndex        ,
                                                                                   CATLONG32           iExtremity    )  const = 0;

  virtual void                                      GetOneCrvLimit                (CATLONG32           iIndex        ,
                                                                                   CATLONG32           iExtremity    ,
                                                                                   CATCrvParam       & oCrvPar       )  const = 0;

  virtual CATMathPoint                              GetOneStartPoint              (CATLONG32           iIndex        )  const = 0;

  virtual CATMathPoint                              GetOneEndPoint                (CATLONG32           iIndex        )  const = 0;

  virtual CATMathVector                             GetOneStartFirstDerivative    (CATLONG32           iIndex        )  const = 0;

  virtual CATMathVector                             GetOneEndFirstDerivative      (CATLONG32           iIndex        )  const = 0;

  //                    Get one Crv Orientation     0 <= iIndex < nbcurves

  virtual CATLONG32                                 GetOneCrvOrientation          (CATLONG32           iIndex        )  const = 0;

  virtual void                                      SetOneCrvOrientation          (CATLONG32           iIndex        ,
                                                                                   CATLONG32           iCrvOrien     )  const = 0;
  // Get one SupportOrientation    0 <= iIndex < nbcurves
  // If the curve is not a PCurve element, SupportOrientation == 0
  virtual CATLONG32                                 GetOneSupportOrientation      (CATLONG32           iIndex        )  const = 0;

  virtual void                                      SetTgtAngle                   (CATAngle            iTgtAngle     )        = 0;

  // Get ContinuityCvCv(double iResolution, CATLONG32 * oCont)  const
  // fills an array of longs between -1 and 2. These longs give the
  // continuity between  the curve Index and the curve Index+1, where
  // 0 <= Index < nbcurves. The last Index value is really tested
  // if the CCv is closed, otherwise the value is set to -1.
  //    The value of the CATLONG32 is
  // -1 if the two curves are not connected,
  //  0 if there is a G0 continuity,
  //  1 if there is a G1 continuity,
  //  2 if there is a G2 continuity.
  //
  //  iMode : mode to get the values of the discontinuities
  //  0 -> no values
  //  1 -> discontinuities in point (DeltaPt : distances)
  //  2 -> discontinuities in point and in tangency (DeltaTg : angles)
  virtual void                                      GetContinuityCvCv             (double              iResolution   ,
                                                                                   CATLONG32        *  oCont         ,
                                                                                   CATLONG32           iMode         = 0   ,
                                                                                   double           *  ioDeltaPt     = NULL,
                                                                                   double           *  ioDeltaTg     = NULL) const = 0;

  virtual void                                      GetContinuityCvCv             (double              iResolution   ,
                                                                                   double              iResAng       ,
                                                                                   CATLONG32        *  oCont         ,
                                                                                   CATLONG32           iMode         = 0,
                                                                                   double           *  ioDeltaPt     = NULL,
                                                                                   double           *  ioDeltaTg     = NULL) const = 0;

  //This Method uses GContinuity operator to measure error. It must be used to obtain the same behavior than
  // the CleanOperator.
  // Note that for G2 continuity, behaviors are:
  // :( ConnectChecker                           : Scalar comparison of curvature
  // :) CCVClenaer                               : Vector comparison (==GContinuity)
  // :( GetContinuityCvCv (the 2 others methods) : Scalar comparison + Check of parallelism of normal vector!
  // 
  // TabResolution : Res For Each Continuity, G0<=>G3 , =-1. to use Factory resolution(except for G2 see CATCurveGContinuity)
  // ioDelta[i] : discontinuities of order i
  virtual void                                      GetContinuityCvCv             (double              TabResolution[4],
                                                                                   CATLONG32         * oCont         ,
                                                                                   CATLONG32           iMode         = 0   ,
                                                                                   double           ** ioDelta       = NULL) const = 0;

  virtual CATBoolean                                IsOneCrvC1Continuous          ()                                               = 0;

  //  Continuity analysis of a curve
  #define CATFrFCompositeCurve_SpecialInfiniteContinuityQuery   1000   /* requete particuliere pour le C-infini        */
  #define CATFrFCompositeCurve_SpecialMaxDiscontinuityParamsByCrv 10   /* limitation provisoire (qui dure) pour perfos */
  virtual CATBoolean                                GetContinuityCrv              (int                 iInfo           ,
                                                                                   int                 iContinuityQuery,
                                                                                   CATListOfInt      * oListIndexCrv   ,
                                                                                   CATListOfDouble   * oListParam      ,
                                                                                   int                 iCrv            = -1)  const =0;

  // Get ContinuitySurSur(double iResolution, CATLONG32 * oCont) const
  // fills an array of longs between -1 and 2. These longs give the
  // continuity between the underlying surface of the curve Index
  // and underlying  surface of the curve Index+1, where
  // 0 <= Index < nbcurves. The last Index value is really tested if
  // the CCv is closed, otherwise the value is set to -1.
  //    The value of the CATLONG32 is
  // -1 if the two surfaces are not connected,
  //  0 if there is a G0 continuity,
  //  1 if there is a G1 continuity,
  //  2 if there is a G2 continuity.
  //  for the moment, only -1, 0 or 1 options are tested.
  //  if G2, output is 1.
  virtual void                                      GetContinuitySurSur           (double              iResolution     ,
                                                                                   CATLONG32        *  oCont           )     const = 0;

  // with an angular resolution ( radian )
  virtual void                                      GetContinuitySurSur           (double              iResolution     ,
                                                                                   double              iResAng         ,
                                                                                   CATLONG32        *  oCont           )     const = 0;

  // Set the Closure of the CCv
  // The value of the Closure is
  // 1 if the CCv is closed
  // 0 if the CCv is not close
  // This method does not check if the
  // input value is compatible with the CCv
  virtual void                                      SetClosure                    (short               iFermeture      )           = 0;

  // Get the Closure of the CCv
  virtual short                                     GetClosure                    ()                                         const = 0;

  virtual void                                      SetFactory                    (CATGeoFactory    *  iFactory        )           = 0;

  // Compare each crv pointers, crv limits and orientation
  // iMode=0: standard
  // iMode=1: ignore all support data (support orientation, merged curve, pcurve)
  virtual CATBoolean                                IsEqual                       (CATFrFCompositeCurve*
                                                                                                       iCcv            ,
                                                                                   int                 iMode           = 0 ) const = 0;

  // Get parameter at iLength from the beginning of this. This method does not
  // manage closure, nor gap between two CATCurve. Tolerance used is 
  // CATGeoFactory->GetResolution() for computation.
  // iLength is negative or superior to this length, return will be 1.
  // 0 else.
  virtual CATLONG32                                 GetParamFromLength            (double               iLength        ,
                                                                                   CATFrFCCvParam     & ioParam        )     const = 0;

  // Get composite curve mapping (property of the composite curve)
  // May compute it if necessary
  // RESTRICTED USE
  virtual CATFrFCompositeCurveMapping             * ProtectedGetMapping           (CATBoolean           iComputeIfNecessary = CATBoolean(1)) = 0 ;

  // Get mapping on composite curve; Computes it if necessary
  // RESTRICTED USE
  virtual void                                      ProtectedSetMapping           (CATFrFCompositeCurveMapping*
                                                                                                        iMapping       ,
                                                                                   CATBoolean           iRemoveOld     = CATBoolean(1)) = 0;

  // Defines curves domains (by default each curve is in domain number 1)
  // First value must be 1 and each value must be equal to preceeding value +0 or +1
  virtual void                                      SetDomains                    (CATListOfInt       & iDomains       )        = 0;

  // Get curves domains (by default each curve is in domain number 1)
  virtual void                                      GetDomains                    (CATListOfInt       & oDomains       )  const = 0;

  //-------------------
  // Checking Methods
  //-------------------

  // Check a CCv
  // Checks the closure and the orientations
  // of a CCv by giving the size of the
  // greatest hole between two following curves
  // of the CCv. The (nbcurves-1)curve - (0)curve
  // hole is tested if the closure is set to 1
  virtual double                                    CheckCCv                      ()                                      const = 0;

  // Compute CCv orientation if make connex ccv is possible.
  // Otherwise return FALSE
  virtual CATBoolean                                ComputeCrvOrientation         (double               iResolution    ) = 0;

  // Compute Support orientation
  virtual void                                      ComputeSupportOrientation     () = 0;

  //--------------------------
  // Methods on the elements
  //--------------------------
  // Replace a curve in the CCv
  virtual CATBoolean                                ReplaceCurve                  (CATCurve          *  iNewCurve           ,
                                                                                   CATLONG32            iIndex              ,
                                                                                   CATLONG32            iCrvOrientation     = 0,
                                                                                   CATCrvLimits      *  iCrvLimit           = 0,
                                                                                   CATLONG32            iSupportOrientation = 0,
                                                                                   CATEdgeCurve      *  iNewMergedCurve     = 0,
                                                                                   CATPCurve         *  iNewPCurve          = 0) = 0;


  //--------------------------------
  // Tests on CCvParams of the CCv
  //--------------------------------
  // Return true if SupParam is not a limit of the CCv, 
  // the comparison is done at the resolution, using CompareWithResolution
  // except if a tolerance is given
  virtual CATBoolean                                IsNotALimit             (const CATFrFCCvParam     & SupParam       ,
                                                                                   double            *  iTolerance     = 0) const = 0 ;

  // Return true if SupParam is a limit of the CCv, 
  // the comparison is done at the resolution, using CompareWithResolution
  // except if a tolerance is given;
  // the exact limit is given in output if SupParam is a limit within Tolerance
  virtual CATBoolean                                IsALimit                (const CATFrFCCvParam     & SupParam       ,
                                                                                   CATFrFCCvParam     & oExactLimit    ,
                                                                                   double            *  iTolerance     = 0) const = 0 ;
  // DO NOT USE (since 100200)
  // DO NOT USE (since 100200)
  // DO NOT USE (since 100200)
  // DO NOT USE (since 100200)
  // Compare two CCvParams of the CCv
  virtual CATBoolean                                IsSuperior              (const CATFrFCCvParam     & SupParam       ,
                                                                             const CATFrFCCvParam     & InfParam       ) const = 0;

  virtual CATBoolean                                IsEqualWithResolution   (const CATFrFCCvParam     & CCvParam1      ,
                                                                             const CATFrFCCvParam     & CCvParam2      ) const = 0;

  virtual CATBoolean                                IsEqualWithTolerance    (const CATFrFCCvParam     & CCvParam1      ,
                                                                             const CATFrFCCvParam     & CCvParam2      ,
                                                                             const double               iTolerance     ) const = 0;
  // Return the relative position of a CCvParam in the CCV
  // the comparison is done at the resolution, using CompareWithResolution.
  // unless a comparison tolerance is given
  // 0 = point is inside the Curve SupParam.GetCrvIndex (not at the limits)
  // 1 = point is on one limit of the Curve, at the beginning.
  // 2 = point is on one limit of the Curve, at the end.
  // 3 = point is outside the CCV

  virtual CATLONG32                                 PositionOf              (const CATFrFCCvParam     & SupParam       ,
                                                                                   double            *  iTolerance     = NULL) const = 0;
  // Return the relative position of a CCvParam compared with two other CCvParams,
  // the comparison is done at the resolution, using CompareWithResolution.
  // unless a comparison tolerance is given
  // 0 = iCCvParam is between iCCvParStart and iCCvParEnd
  // 1 = iCCvParam is near iCCvParStart
  // 2 = iCCvParam is near iCCvParEnd
  // 3 = iCCvParam is out of the [iCCvParStart iCCvParEnd] interval
  virtual CATLONG32                                 PositionOf              (const CATFrFCCvParam     & iCCvParam      ,
                                                                             const CATFrFCCvParam     & iCCvParStart   ,
                                                                             const CATFrFCCvParam     & iCCvParEnd     ,
                                                                                   double            *  iTolerance     = NULL) const = 0;

  // Compare two CATFrFCCvParam :
  // The comparison implies three equality levels :
  // * strictly equal CATFrFCCvParam <==> ((CrvIndex1 == CrvIndex2) &&
  //                                       (CrvParam1 == CrvParam2))
  // * equivalent CATFrFCCvParam : the CCvParam1 can be a the end of one curve
  //                               and the CCvParam2 at the beginning of the following ;
  //                               the degenerated curves are taken into account.
  // * equal with resolution/tolerance : the length between the two CCvParams is smaller 
  //                                     than the resolution/tolerance.
  // The result values are :
  // -3 : CCvParam1 is smaller (even with the resolution/tolerance) than CCvParam2
  // -2 : CCvParam1<CCvParam2 (in the equivalent meaning) but CCvParam1 is 
  //      equal with resolution/tolerance to CCvParam2.
  // -1 : CCvParam1<CCvParam2 (in the strict equality meaning) but CCvParam1 is 
  //      equivalent to CCvParam2.
  //  0 : strict equality
  //  1 : CCvParam1>CCvParam2 (in the strict equality meaning) but CCvParam1 is 
  //      equivalent to CCvParam2.
  //  2 : CCvParam1>CCvParam2 (in the equivalent meaning) but CCvParam1 is 
  //      equal with resolution/tolerance to CCvParam2.
  //  3 : CCvParam2 is smaller (even with the resolution/tolerance) than CCvParam1
  virtual CATLONG32                                 CompareWithTolerance    (      double               iTolerance     ,
                                                                             const CATFrFCCvParam     & iCCvParam1     ,
                                                                             const CATFrFCCvParam     & iCCvParam2     ) const = 0;
  virtual CATLONG32                                 CompareWithResolution   (const CATFrFCCvParam     & iCCvParam1     ,
                                                                             const CATFrFCCvParam     & iCCvParam2     ) const = 0;
  //-----------------------------------------------------
  // Give the distance between two CCvParams of the CCv
  //-----------------------------------------------------
  // Geometrical length between 2 CCv Parameters
  // if CCvParam1 > CCvParam2, result is negative
  // If the CCv is closed and CCvParam1>CCvParam2, the length is not measured 
  // over the closure, the measure will be - GetSignedLength(CCvParam2,CCvParam1)
  virtual double                                    GetSignedLength         (const CATFrFCCvParam     & iCCvParam1     ,
                                                                             const CATFrFCCvParam     & iCCvParam2     ) const = 0;

  virtual double                                    GetParametricLength     (const CATFrFCCvParam     & iCCvParam1     ,
                                                                             const CATFrFCCvParam     & iCCvParam2     ) const = 0;

  //------------------------------------------------------
  // Give the distance between the start and the end of the distance of curve iIndex 
  //------------------------------------------------------
  virtual double                                    GetLength               (      CATLONG32            iIndex         )= 0;

 
  //----------
  // Clonage
  //----------
  // Copy Ccv attributes & Clone Geometry
  //
  // NLD 04 01 98 : ajout argument optionnel iMode
  //   unites de iMode = 0 : standard
  //   unites de iMode = 1 : clone des (n-1) dernieres occurences
  //                          pour une courbe à n occurences dans la CCV
  //   dizaines de iMode = 0 : standard
  //   dizaines de iMode = 1 : creer un clone manager par courbe
  //   la liste des courbes clonees est donnee en sortie si on recoit 
  //   un pointeur de liste non nul

  virtual CATFrFCompositeCurve                    * DeepClone               (      CATCloneManager    & iCloneManager  ,
                                                                                   int                  iMode          = 0,
                                                                                   CATLISTP(CATCurve)*  ioClonedCurves = NULL) = 0;

  virtual void                                      RemoveGeometry          (      CATBoolean           iRmGeometry    )       = 0;

  //------
  // Boxes
  //------
  //
  // Computes the bounding box of a CCv 
  //
  virtual CATMathBox                              * GetBox                  ()                                           const = 0 ;

  //
  // Computes the bounding box of each Curve of the CCv 
  // ioBoxes is allocated by the caller
  virtual void                                      GetBoxes                (       CATMathBox       *  ioBoxes        )       = 0;

  #ifdef CATFrFCompositeCurveWithAdvancedBoxes
  //
  // Computes the advanced bounding box of each Curve of the CCv
  // returns 0 if computation done, or a diagnostic raising from first box curve computation failure
  //
  virtual int                                       GetAdvancedBoxes        (       CATMathAdvancedBox* ioBoxes        )       = 0;
  #endif

  //
  // Return TRUE if the curve length is less than Tolerance
  //
  virtual CATBoolean                                IsDegenerateCrv         (       CATLONG32           iIndex         ) const = 0;

  //----------
  // Utilities
  //----------
  // Dumps composite curve
  // @param iStream
  // A pointer to the output. If <tt>0L</tt>, the method dumps the 
  // coordinates on the <tt>cgmout</tt> output.
  // iTexte : text associated to composite curve
  // iCodeDump: code for type of dump (reserved for future use)
  // example: CCV->Dump("texte") ;
  //          CCV->Dump("texte", &cgmout) ;
  virtual void                                      Dump                    (       char             *  iTexte         = NULL,
                                                                                    CATCGMOutput     *  iStream        = 0L  ,
                                                                                    int                 iCodeDump      = 0   ) const = 0;

  // Save as body; only for test and debug
  virtual CATBody                                 * DebugOnlySaveAsBody     ()                                                 const = 0 ;

  //-----------------------------------------------------------------------------
  // Stream/Unstream only for test and debug
  //-----------------------------------------------------------------------------
#ifdef CATFrFCompositeCurveStream
  virtual void                                      Stream                  (       CATCGMStream      & Str            ,
                                                                             const  char                iLabelReserved[] = "") const = 0;
#endif
  //------------------------------------------------------
  // Give access to current tolerances 
  //------------------------------------------------------
  virtual const CATTolerance                      & GetTolerance            ()                                                 const = 0 ;

//  ============================================================================
//   CES METHODES NE SONT PLUS DISPONIBLES, MAIS ELLES PEUVENT ETRE REMISES
//  ============================================================================
//  
//   Remove a curve from the CCv
//  
//virtual void                                      RemoveCurve             (        short              iSide          )             = 0;

//  
//   Add a curve to the CCv
//  
//virtual void                                      AddCurve                (        short               iSide          ,
//                                                                                   CATCurve         *  iCurve         ,
//                                                                                   CATCrvLimits        iCrvLimits     ,
//                                                                                   CATLONG32           iCrvOrientation,
//                                                                                   CATLONG32           iSupportOrientation = 0)    = 0;

};

//============================================================================
#ifdef CATFrFCompositeCurveStream
// voir CATFrFCompositeCurveCx2
// #include <FrFAdvancedObjects.h>
// extern "C" ExportedByFrFAdvancedObjects
// CATFrFCompositeCurve* CATUnStreamFrFCompositeCurve(CATCGMStream& Str, const char iLabelReserved[]="");
#endif

#endif




