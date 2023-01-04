#ifndef CATPGMFrFTopologicalSweepR12Adapter_h_
#define CATPGMFrFTopologicalSweepR12Adapter_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

#include <CATDataType.h>
#include <ListPOfCATVertex.h>
#include <CATListOfDouble.h>
// Advanced topological operators
#include <CATICGMFrFTopologicalSweep.h>
#include "CATCGMWarning.h"
#include "CATTopLimit.h"
#include "CATTopLimitType.h"
#include "CATMathDef.h"
#include "CATTopPropagationType.h"
#include "CATCollec.h"
#include "CATTopBooleanType.h"

//=============================================================================
class CATCGMOutput;
class CATGeometry;
class CATICGMFrFTopologicalSweep;
class CATLaw;
class CATMathPlane;
class CATCell;
class CATLISTP(CATDomain);

class ExportedByCATGMOperatorsInterfaces CATPGMFrFTopologicalSweepR12Adapter
{
public:
  /**
   * Constructor
   */
  CATPGMFrFTopologicalSweepR12Adapter();

  /**
   * Destructor
   */
  virtual ~CATPGMFrFTopologicalSweepR12Adapter();

//=============================================================================
// R24 only CAA  Methods adaption
//=============================================================================
/**
 * (temporary and restricted use).
 * Manages motion axis twist with a variable (local) viewing direction.
 * To be used only with following conditions;
 * <ul>
 * <li>Standard moving frame type (CATFrFTopologicalSweepMF_Ortho).
 * <li>Unspec sweep (with profile)
 * <li>Spine with a complex 3D curve
 * </ul>
 */
   virtual void        ForceVariableViewingDirMode()                                                                             = 0;

  //=============================================================================
  // R23 only CAA  Methods adaption
  //=============================================================================
/**
 * Upgrade default operator settings.
 * (for historical and compatibility reasons old fashioned default settings are still active without this call).
 * Must be called immediatly after operator creation.
 * Level 1 default setting changes:
 * <ul>
 * <li>Twist detection is activated.
 * <li>Wrap detection is activated.
 * <li>All angles are defined in degree including int Circular Sweep case.
 * <li>In case of profile or guide support, internal laydown will be done.
 * </ul>
 */
  virtual void         SetUpgradedDefaultSettings(     int                     iSettingsLevel                   = 1)             = 0;

  //=============================================================================
  // R22 only CAA  Methods adaption
  //=============================================================================
  // Angular laws definition
  // Angles must be given in degree, including in circular sweep case)
  virtual void         SetAngularLawsInDegree   (      CATLaw               ** iLaws                            ,
                                                       int                     iNbLaws                          )                = 0;

  //=============================================================================
  // R21 only CAA  Methods adaption
  // (**** Not necessarily already published in CATFrFTopologicalSweep.h *****)
  //=============================================================================
 /**
 * Defines the type of limitation of each extremity along the extrusion (center curve) direction.
 * <br>To be called for each extremity, if you do not want to keep
 * the default options of the global creation function.
 * @param iId
 * The first or last extremity.
 * @param iType
 * The type of limit on the extremity.
 * @param iIsAxisReverted
 * The orientation.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for the same orientation as the direction defined at the operator
 * creation, <tt>FALSE</tt> for an opposite orientation. In general, use <tt>TRUE</tt> for the start limit,
 * and <tt>FALSE</tt> for the end limit.
 * @param iOffset
 * The value of the offset if <tt>iType</tt> has the value <tt>CatLimOffsetFromProfile</tt>.
 * @param iLimit
 * The pointer to the geometry or the topology that stops the extrusion.
 * @param iPropagationBody
 * The pointer to the body which contains <tt>iLimit</tt>, thus allowing the
 * propagation of the trimming specification. To use if <tt>iType = CatLimUntil</tt> and
 * <tt>iPropagationFlag = CatPropagClosing</tt>  or if <tt>iType = CatLimNextAlongAxis</tt>
 * or <tt>iType = CatLimLastAlongAxis</tt>
 * @param iPropagationFlag
 * The management of the propagation.
 * @param iThickness
 * defines the value of any thickness which must be applied to the considering relimitation
 */
  virtual void         SetExtrudeLimit          (      CATTopLimit             iId                              ,
                                                       CATTopLimitType         iType                            ,
                                                       CATBoolean              iIsAxisReverted                  ,
                                                       CATLength               iOffset                          ,
                                                       CATGeometry           * iLimit                           ,
                                                       CATBody               * iPropagationBody                 ,
                                                       CATTopPropagationType   iPropagType                      ,
                                                       CATLength               iThickness                       )                = 0;

  // Thin solid mode definition
  virtual void         SetThinSolidMode         (const CATBoolean              iThinSolidMode                   ,
                                                 const CATBoolean              iIsNeutralFiber                  ,
                                                 const double                  iThinSolidThickness[2]           ,
                                                       CATLISTP(CATDomain)   * iWireListWithReverseThinSolidSide)                = 0;

  // Trimming body definition
  virtual void         SetTrim                  (      CATBody               * iTrimBody                        )                = 0;

  // Boolean operation definition
  virtual void         SetOperation             (      CATTopBooleanType       iBooleanType                     )                = 0;

  // Extrapolation and profile trim on trimming body (defined by SetTrim())
  virtual void         SetProfileClosure        () = 0;

  // Reference plane definition (for extrusion/relimitation)
  virtual void         SetRefPlane              (      CATMathPlane          & iRefPlane                        )                = 0;

  // Unset topological twist check
  virtual void         UnsetCheckTopoTwist      (      CATBoolean              iUnsetCheckTopoTwist             = CATBoolean(1)) = 0;

  // Boolean relimitation mode (SetRelimitationMode() on CATIPGMSweep2 operator)
  // (la connaissance des modes de SetRelimitationMode() sur CATSweep/CATSweep2/CATIPGMSweep2,
  //  et donc de cette methode
  //  semble etre reservee a une secte secrete dans laquelle on entre par cooptation;
 //   je ne peux pas documenter ici ce que mes fournisseurs ne daignent toujours pas documenter)
  virtual void        SetBooleanRelimitationMode(      short                   iMode                            ,
                                                       short                   iAutomaticDirectionInversion     = 1)             = 0;

  virtual void         SetVirtualBoolean        () = 0;

  virtual void         SetBothResult            () = 0;

  virtual void         SetReversePolarity       (      CATBoolean              iPolarity                        )                = 0;

  // (SetTwistReduction() on CATIPGMSweep2 operator)
  virtual void         SetBooleanTwistReduction(       CATBoolean              iTwistReduction                  )                = 0;

  virtual void         SetOldShapeRequested     ()                                                                               = 0;

  virtual CATBody    * GetBooleanResult         ()                                                                               = 0;

  virtual CATBoolean   IsInvariantResult        ()                                                                               = 0;

  // Direction de balayage, a comportement quasi continu, permettant le franchissement des sommets C0
  virtual void         GetSmoothSweepingDir     (      double                  iLambda                          ,
                                                       CATMathPoint          & oOrigin                          ,
                                                       CATMathDirection      & oDir                             )                = 0;

  //=============================================================================
  // R18 only CAA  Methods adaption
  //=============================================================================
  //-------------------------------------------------------------------------
  // Recuperation des zones remplies et des indicateurs de remplissage
  // (0 pour zones avec echec de remplissage)
  //-------------------------------------------------------------------------
  virtual void         GetFilledAreas           (      CATListOfDouble       & oFillBegin                       ,
                                                       CATListOfDouble       & oFillEnd                         ,
                                                       CATListOfInt          & oFillOk                          )                = 0;

  //=============================================================================
  // R15 only CAA  Methods adaption
  //=============================================================================
  // SetAreaLaw()
  // SetLayDownRequest()
  // GetProfileArea()

  //=============================================================================
  // R14 only CAA  Methods adaption
  //=============================================================================

  //=============================================================================
  // R13 only CAA  Methods adaption
  //=============================================================================

  //=============================================================================
  // R12 only CAA  Methods adaption
  //=============================================================================

  //=============================================================================
  // others R12 only CAA  Methods adaption
  //=============================================================================
  //-------------------------------------------------------------------------
  // Activation/Desactivation du detwistage
  // Mode 1: Calcul des zones de twist
  // Mode 2: Calcul et retrait des zones de twist
  // Mode 3: Calcul et conservation des zones de twist seulement
  // Mode 4 : calcul et retrait des zones twistees avec controle de non twist du residu (19/06/05)
  //-------------------------------------------------------------------------
  virtual void         SetUntwistMode           (      int                     iUntwistMode                     ,
                                                       double                  iRecoilDistance                  = 0.0,
                                                       int                     iRecoilSubIntervalsNumber        = 0)             = 0;

  //=============================================================================
  // R11 only CAA Methods adaption
  //=============================================================================

  //=============================================================================
  // Internal methods adaption
  //=============================================================================
  //-------------------------------------------------------------------------
  // Operator dump
  //-------------------------------------------------------------------------
  virtual void         Dump                     (      CATCGMOutput          & os                               )                = 0;

  //-------------------------------------------------------------------------
  // Definition du niveau de modeleur CGM pour le calcul de spine implicite
  //-------------------------------------------------------------------------
  virtual void         SetCGMLevelForImplicitSpine(    int                     iCGMLevelForImplicitSpine        )                = 0;

  //-------------------------------------------------------------------------
  // Activation/Desactivation du mode assemblage pour l'aide au diagnostic
  //-------------------------------------------------------------------------
  virtual void         SetAssemblyForDiagnosis  (      int                     iActiveAssembly                  = 1)             = 0;

  //-------------------------------------------------------------------------
  // Imposition de condition de continuite generalisee sur les guides
  // (cas loft et cas sweep conique)
  // Ceci est mis en public pour le blend qui utilise un angle de 180
  // pour jouer sur les orientations
  //-------------------------------------------------------------------------
  virtual void         SetGeneralizedGuideContinuityCondition(
                                                       int                     iGuideNumber                     ,
                                                       CATGeometry           * iReferenceElement                ,
                                                       CATLaw                * iAngleLaw                        ,
                                                       CATFrFTopologicalSweepContinuity_Type
                                                                               iContinuityCondition             )                = 0;

  //-------------------------------------------------------------------------
  // Simulation de découpe non C2: parametres imposés par l'appelant
  //-------------------------------------------------------------------------
  virtual void         AddSimuNonC2Parameters   (      int                     iNbValues                        ,
                                                       double                * iValues                          )                = 0;

  //-------------------------------------------------------------------------
  // Desactivation de la deformation des peignes aux vertex C0
  // (seulement pour les sweeps segment)(usage privé, réduit à SweepExtrapol)
  //-------------------------------------------------------------------------
  virtual void         SetNoCombDeformationOnC0Vertex()                                                                          = 0;

  //-------------------------------------------------------------------------
  // Definition d'une tolerance de maillage minimum (methode utilisee en test seulement)
  //-------------------------------------------------------------------------
  virtual void         SetMinimumMeshTolerance  (      double                  iMinimumMeshTolerance            )                = 0;

  //-------------------------------------------------------------------------
  // Cas d'un blend sans spine avec couplage en abscisse curviligne
  //-------------------------------------------------------------------------
  virtual void         SetNoSpineBlend          (      int                     iOption                          = 1)             = 0;

  //-------------------------------------------------------------------------
  // Definition du mode de calcul des directions en extremite pour le blend
  // 0 : perpendiculaire (à la guide)
  // 1 : tangent         (mode par défaut)
  //-------------------------------------------------------------------------
  virtual void         SetBlendBorderMode       (      int                     iNumGuide                        ,
                                                       int                     iStartMode                       ,
                                                       int                     iEndMode                         )                = 0;

  //-------------------------------------------------------------------------
  // Definition de l'option develop (blend)
  // nouveau mode:
  // iDevelopOption = 0 : inactive
  //                = 1 : Develop
  //                = 2 : NoTwist
  // iActiveRelimitation = 0 : pas de relim
  //                     = 1 : relimitation active
  // ancien mode:
  // iDevelopOption = 0 : inactive
  //                = 1 : active
  //                = 2 : active avec relimitation
  //
  // iDevelopClearance  : valeur du parametre Clearance
  // si option develop active avec relimitation:
  // iRelimitationMode[2] & iRelimitingGuideNumber[2]:
  //  On each extremity(0/1):
  //    iRelimitationMode[i]=0 : until extremity vertices on all guides
  //                          =1 : Until extremity vertex of guide number iRelimitingGuideNumber[i]
  //                          =2 : Best solution (Automatic selection of the limiting guide)
  //    iRelimitingGuideNumber[i] : guide number whose extremity vertex will relimit coupling
  virtual void         SetBlendDevelopOption    (      int                     iDevelopOption                   ,
                                                       double                  iDevelopClearance                ,
                                                       int                     iActiveRelimitation              = 0,
                                                       int                   * iRelimitationMode                = 0,
                                                       int                   * iRelimitingGuideNumber           = 0)             = 0;

  //-------------------------------------------------------------------------
  // Proto Sweep unspec non manifold
  //-------------------------------------------------------------------------
  virtual void         SetNonManifoldUnspecProto(      int                     iOption                          = 1)             = 0;

  //-------------------------------------------------------------------------
  // Activation/Desactivation du mode remplissage des zones twistees
  // iFillTwistMode
  // 0 : inactif
  // 1 : actif avec tangence
  // 2 : actif sans tangence (a discuter)
  // 3 : actif avec tangence selon guide obligatoire et autres finesses speciales extrapolation de skin
  //      (USAGE STRICTEMENT RESERVE)
  //      N.B liste des modes à enrichir mais sans changement car stream sous CGMReplay
  // iFillTwistDefaultOption: option de remplissage par défaut
  // (memes valeurs possibles que pour l'argument iFillOptions de SetAreasToEliminate)
  //-------------------------------------------------------------------------
  virtual void         SetFillTwistProto        (      int                     iFillTwistMode                   = 1)             = 0;

  virtual void         SetFillTwistProto        (      int                     iFillTwistMode                   ,
                                                       int                     iFillTwistDefaultOption          )                = 0;

  //-------------------------------------------------------------------------
  // Force le mode viewing dir multiple
  //-------------------------------------------------------------------------
  virtual void         ForceMultipleViewingDirMode()                                                                             = 0;

  //-------------------------------------------------------------------------
  // Definition des vertex limites de zones à eliminer
  // en l'absence de liste iFillOptions on remplit chaque zone eliminée si
  // le remplissage a été demandé par SetFillTwistProto()
  // sinon pour chaque zone l'indicateur doit valoir 1 si la zone doit etre remplie
  //-------------------------------------------------------------------------
  virtual void         SetAreasToEliminate      (      CATLISTP(CATVertex)   & iStartVertices                   ,
                                                       CATLISTP(CATVertex)   & iEndVertices                     ,
                                                       CATListOfInt          & iFillOptions                     )                = 0;

  //-------------------------------------------------------------------------
  // Force suivi reduit du clean/posage pour perfos GenericNaming
  //-------------------------------------------------------------------------
  virtual void         ForceGenericNamingPourLesNULs(  int                     iForceGenericNamingPourLesNULs   = 1)             = 0;

  //-------------------------------------------------------------------------
  // Force le mode warning
  //-------------------------------------------------------------------------
  virtual void         SetWarningMode           (      CATCGMWarning           iMode                            )                = 0;

  //-------------------------------------------------------------------------
  // Closure mode with profiles underlying surfaces if any (restricted use)
  //-------------------------------------------------------------------------
  virtual void         SetAdvancedClosureModeWithSurfaces()                                                                      = 0;

  //-------------------------------------------------------------------------
  // Compute point on master guide from sweeping ratio
  // CATMathPoint is the origin of the moving frame computed on the master guide
  // returns 0 if OK
  //-------------------------------------------------------------------------
  virtual int          ComputePointFromSweepingRatio
                                                (      double                  iRatio                           ,
                                                       CATMathPoint          & oPoint                           )                = 0;

  //-------------------------------------------------------------------------
  // Compute sweeping ratio from point on master guide
  // point can be either on the master guide (edition initialization)
  //                     or in the 3D (manipulation)
  // returns 0 if OK
  //-------------------------------------------------------------------------
  virtual int          ComputeSweepingRatioFromPoint
                                                (const CATMathPoint          & iPoint                           ,
                                                       double                & oRatio                           )                = 0;

  //-------------------------------------------------------------------------
  // Recoil parameters definition around twisted areas of pseudo-twisted areas
  //-------------------------------------------------------------------------
  virtual void         SetRecoilParameters      (      double                  iRecoilDistance                  ,
                                                       int                     iRecoilSubIntervalsNumber        )                = 0;

  //-------------------------------------------------------------------------
  // Activate pseudo untwist mode for C0 vertices in error
  //-------------------------------------------------------------------------
  virtual void         SetPseudoUntwistModeForC0VerticesInError
                                               (       int                     iAutomaticRecoil                 = 0)             = 0;

  //-------------------------------------------------------------------------
  // Define final body freeze mode
  //-------------------------------------------------------------------------
  // Special call for setting freeze mode on CATSweep2 operator
  // CAUTION: inconsistent behaviour for GetFreezeMode(); NLD250918
  virtual void         SetFreezeMode           (       CATBoolean              iFreezeMode                      )                = 0;

  //-------------------------------------------------------------------------
  // Ridge mode for segment profile sweep
  //-------------------------------------------------------------------------
  virtual void         SetRidgeOption          ()                                                                                = 0;

  //-------------------------------------------------------------------------
  // Scaling law for unspec sweep                                      010617
  //-------------------------------------------------------------------------
  virtual void         SetScalingLaw           (       CATLaw                * iLaw                             )                = 0;

  virtual void         SetRadiusLaws           (       CATLaw               ** iLaws                            ,
                                                       int                     iNbLaws                          )                = 0;

  //-------------------------------------------------------------------------
  // RoadWidth mode for segment profile sweep                          080617
  //-------------------------------------------------------------------------
  virtual void         SetRoadWidthOption      ()                                                                                = 0;

  //-------------------------------------------------------------------------
  // Prototype d'extraction de frontiere sur un sweep segment (cote 1 ou 2)
  // (+ generalisation a d'autres types de sweep)                      190917
  //-------------------------------------------------------------------------
  virtual CATBody*     ExtractBoundary         (      int                      iSide                            )                = 0;

  //-------------------------------------------------------------------------
  // Prototype d'extraction de middle curve sur un sweep road crown (à deux segments)
  //-------------------------------------------------------------------------
  virtual CATBody*     ExtractMidCurve         ()                                                                                = 0;

  //-------------------------------------------------------------------------
  // Prototype d'extraction de parallèle, generalisé (usage reservé à CivilEngineering)
  //-------------------------------------------------------------------------
  // Extraction de parallèle depuis un vertex du profil
  // le vertex est imposé soit par ses deux edges adjacentes
  // soit directement
  //-------------------------------------------------------------------------
  virtual CATBody*     ExtractParallel         (      CATCell                * iImposedProfileCell1             ,
                                                      CATCell                * iImposedProfileCell2             ,
                                                      CATCGMJournalList      * OutputReport                     )                = 0;


  //-------------------------------------------------------------------------
  // Mode de relimitation du journal
  // (voir CATSweep.h sans documentation aucune de la méthode)
  // en revanche on trouve dans CATTopExtrude la documentation de SetJournalMode():
  // @nodoc
  // Sets journal behaviour. If set to 1, the profile face will be added as a parent of faces involved in 
  // contextual limits. Also, CATCGMJournalInfoItem data will be added for faces for the start and end limits.
  // @param iJournalMode
  // New value of the journal mode
  //-------------------------------------------------------------------------
  virtual void         SetRelimJournalMode     (      short                    iRelimJournalMode                )                = 0;

};

// Access to Sweep R12 Adapter. This object belongs to CATIPGMFrFTopologicalSweep operator and must
// neither be deleted by caller, nor used after CATIPGMFrFTopologicalSweep operator deletion
ExportedByCATGMOperatorsInterfaces
CATPGMFrFTopologicalSweepR12Adapter *CATPGMGetTopologicalSweepR12Adapter(CATICGMFrFTopologicalSweep *iSweepOperator);

#endif /* CATPGMFrFTopologicalSweepR12Adapter_h_ */
