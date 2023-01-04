#ifndef CATExtTopOperator_h_
#define CATExtTopOperator_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//=============================================================================
// DD/MM/YY XXX
//   /05/04 HCN  MustInterruptExecution(..) et S_MustInterruptExecution(...)
//   /06/04 FDN  MustInterruptExecution(..) et S_MustInterruptExecution(...) ne
//               rendent plus un boolean, MathInterruptedOperator_ERR_110
//   /06/04 FDN  MustInterruptExecution(..) devient publique
//   /03/05 HCN  _NoInputObjects, SetNoInputObjects() et HasNoInputObjects()
//               pour les CGMReplay des operateurs qui n'ont pas d'objects CGM
//               en entree (par exemple CATTopPointOperatorCx3)
//   /11/05 FDN  Integration de CATCGMProgressBar
// 08/08/07 NLD  XScale: Ajouts pour CGMReplay:
//               _CGMODTScaleManager, SetCGMODTScaleManager(), GetCGMODTScaleManager()
// 05/11/08 NLD  Ajout argument optionnel iOkRun a AfterRun()
//   /04/09 JMA  JJ3 JHN WQO
//               Integration du FastUdpate
//   /07/09 KY1  Integration du Hidden Seam Cell Data
//   /10/09 KY1  Integration de la variable HasHiddenSeamCellManagingDone
//   /03/10 KY1  Suppression de l'Integration du Hidden Seam Cell Data car 
//               le BodiesMappping intègre un mappping complet entre attributs 
//               HS des cellules ref et res
//   /06/11 JHN  VoBTool integration
// 14/10/14 NLD  Detabulation. Smart indent.
//               Separation methodes/donnees. Reordonnancements
// 26/03/15 JHN  Methode pour test de fonctionnalite generique sur operateur
// 07/09/15 G5S  Refactoring of this-> ODTGenerateFastRunContextFromFirstRun(), 
//               so it calls a new method, SetAllContextResults(), which 
//               enables Fast Update Stress tests for Extrude operators.
// 11/07/16 G5S  New method ODTFillFastRunContextFromFirstRun to allow for a 
//               fast update test when the input CGMReplay already has a
//               context object.                                             
// 11/10/16 KY1  Management of Error raised by the operator inside CGM Operator 
//               interface/ CGMReplay Infra:
//               - Stream and Unstream the Error in CGMReplay delegated
//                 to the CGM Operator.
//               - Deep mapping of the Result and Reference Error during
//                 Validation Output Step (Nested Errors are mapped and Bodies
//                 referenced by errors are also mapped)
// 21/06/22 PPU7 xGenerativeDesign performances:
//               - add _HasResultBody to avoid unecessary after run operations.
//=============================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATExtGeoOperator.h"
#include "CATTopOperator.h"

#include "CATListPOfCATCGMDiagnoses.h"
#include "CATTopData.h"
#include "CATBodyFreezeMode.h"
#include "CATCGMVoBResult.h"

//#include "CATCGMProgressBar.h"

#include "ListPOfCATFace.h"
#include "ListPOfCATDomain.h"
#include "CATCollec.h"
#include "CATTopDefine.h"
#include "CATCGMJournalList.h"

#include "CATFastRunStatus.h"
#include "CATMathInline.h"
#include "CATIACGMLevel.h"

#include "CATExtCGMReplay.h"
#include "CATTopCGMAttributeLabel.h"

#include "CATCGMVoBOptionControl.h"

#include "CATErrorDef.h"

class     CATTopCheckJournalData;
class     CATString;
class     CATCGMOperatorRunTransaction;
class     CGMODTScaleManager;
class     CATCellManifoldsManager;
//
class     CATCellTrackingData;
class     CATTopMultiResult;
class     CATDRepExtTopOperator;

class     CATContextForFastRun;
class     CATListPtrCATCell;
class     CATListPtrCATDomain;
class     CATCellHashTable;
class     CATCGMHashTable;
class     CATContextForFastRunExt;
class     CATCGMHashTableWithAssoc;
class     CATechGet;
class     CATechAttribute;
struct    CATCGMVoBTool;
struct    CATCGMVoBResult;
class     CATTopVoBOperator;
class     CATOprTopOperatorExt;
class     CATOprTopologicalOperator;
class     CATPGMDRepBehavior;
class     CATError;
class     CATCGMDiagnosis;
class     CATExtTopMultiResult; 

namespace EK 
{
  class Trace;
}


#define ParameterForTestKeepAndDelete

#ifdef CATIACGMR419CAA
/**
* Defines the type inputs operator definition .
* @param CATTopInputDefinitionUnknown
* 
* 
* @param CATTopInputDefinitionUnHandled
*
*
* @param CATTopInputDefinitionExact
*
*
* @param CATTopInputDefinitionPoly
*
*
* @param CATTopInputDefinitionExactAndPoly
*
*
* Do not use.
*/
enum CATTopInputDefinitionType { CATTopInputDefinitionUnknown,
                                 CATTopInputDefinitionUnHandled,
                                 CATTopInputDefinitionExact,
                                 CATTopInputDefinitionPoly,
                                 CATTopInputDefinitionExactAndPoly };
#endif



class ExportedByCATTopologicalObjects CATExtTopOperator : public CATExtGeoOperator
{
public:
  
  //-------------------------------------------------------------------------------------------------------
  // Constructeur 
  //   iOperateur peut etre NULL,  mais cela doit etre reserve aux cas tres particuliers sous constructeur
  //   il faut dans ce cas s'empresser de retablir la definition avec la methode SetOperator
  //-------------------------------------------------------------------------------------------------------
  CATExtTopOperator(CATTopOperator *iOperateur = NULL);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

//virtual INLINE const MethodType              * MethodName                       (const ArgumentType            *& ArgumentName       ) const ; //SampleMethodDeclaration

  //------------------------------------------------------
  // Analyse CATTopData
  //------------------------------------------------------
          INLINE       void                      GetTopData                       (      CATTopData               & ioTopData          ) const;
  virtual              void                      SetTopData                       (const CATTopData               & ioTopData          );

  //------------------------------------------------------
  // Analyse Config
  //------------------------------------------------------
          INLINE       CATSoftwareConfiguration* GetSoftwareConfiguration         ()                                                     const;
          INLINE       void                      SetSoftwareConfiguration         (      CATSoftwareConfiguration*  iConfig            );

  //------------------------------------------------------
  // Freeze mode management
  //------------------------------------------------------
                       CATBodyFreezeMode         GetFreezeMode                    ()                                                     const;
                       void                      SetFreezeMode                    (      CATBodyFreezeMode          iOnOrOff           );

  //------------------------------------------------------
  // Analyse Journal
  //------------------------------------------------------
          INLINE       CATCGMJournalList       * GetJournal                       ()                                                     const;
          INLINE       void                      SetJournal                       (      CATCGMJournalList       *  iJournal           );

  //------------------------------------------------------
  //
  //------------------------------------------------------
  /** @nodoc  CheckJournal / dedicated multiple Output Bodies in one only run .. */
                       void                      SetMultipleOutputBodies          (const CATLISTP(CATBody)        & iOutputs           );

  //------------------------------------------------------
  // Has result body
  //------------------------------------------------------
  /** @nodoc  Default value for _HasResultBody is TRUE */
          INLINE       CATBoolean                GetHasResultBody                 ()                                                     const;
          INLINE       void                      SetHasResultBody                 (      CATBoolean                 iHasResultBody     );

  //------------------------------------------------------
  // Run
  //------------------------------------------------------

  /** Boolean RC : if AfterRun() should be called */
  virtual              CATBoolean                BeforeRun                        (      int                        iDepth             ,
                                                                                         int                        iDepthForChain     );

   
/**
 * @param iOkRun : Value 1=Okay  0=Error
 * @param iDepth : Depth of Operator
 *    . 
 */
  virtual              void                      AfterRun                         (      int                        iOkRun             ,
                                                                                         int                        iDepth             ,
                                                                                         int                        iDepthForChain     );

#ifdef CATIACGMR419CAA
  //------------------------------------------------------------------------
  // Generic Infra for Legacy of Operator Inputs  (Exact/Poly Inputs)
  //------------------------------------------------------------------------

  /**
  * Is Poly Inputs (i.e All Inputs or part of them are polyhedrique 
  * (GMPolyObject)) allowed for this Operator. 
  */
  virtual              CATBoolean                Is_PolyInputs_Allowed();

  /**
  * Is mix of poly inputs (GMPolyObject) and exact inputs allowed for this operator?
  **/
  virtual              CATBoolean                Is_MixedPolyExactInputs_Allowed();
  /**
  * Run this if operator has mix of poly and exact inputs.
  * It will throw if this is not allowed in given context.
  **/
                       void                      Check_MixedPolyExactInputs_Allowed();


  /**
  * Get the category of Inputs Definition 
  */
                       CATTopInputDefinitionType GetInputsDefinitionType();

  /**
  * Check if the Inputs Definition is authorized by this operator
  */
                       void                      CheckInputDefinitionCompliance();

#endif

  /**
  * Retrieve the Input Factory : the one that input objects belong to
  */
                       CATGeoFactory           * GetInputFactory();
  /**
  * Retrieve the Input Factory : the one that input objects belong to
  * INTERNAL SERVICE : DO NOT USE 
  */
                       CATGeoFactory           * RetrieveInputFactory();

  //------------------------------------------------------
  // VoB
  //------------------------------------------------------
/**
 * @param iTool : define 
 *                   A/ type of checking to do
 *                   B/ the background or not for this checking
 *    . 
 */
                       void                      SetVoBTool                       (      CATCGMVoBTool           *  iTool              );

/**
 * @param iTool : define 
 *                   A/ type of checking to do
 *                   B/ the background or not for this checking
 *    . 
 */
                 const CATCGMVoBTool           * GetVoBTool                       ();

 /**
 *  Check if VoB Operator is enable
 */
  virtual              CATBoolean                IsVoBSupported                   ();

 /**
 *  Check if VoB Operator is enable
 */
  virtual              void                      AdaptVoBOptions                  ();

                       void                      AllocateVoBOptionControl         ();
                       CATCGMVoBOptionControl  * GetVoBOperatorOptionControl      ();

 /**
 *  Check if VoB Operator is saved in CGMReplay
 */
                       CATBoolean                IsVoBSaved                       ();
                       void                      SetVoBSaved                      ();

 /**
  * erase current VoBoperator and replace it by the parameter
  * current VoBoperator can be NULL, input parameter can be NULL to. It can be used also to cleanthe VoBoperator
  * @param iVoBOperator : The VoBoperator to apply to check the body result.
  *    . 
  */
                       void                      ReplaceVoBOperator               (      CATTopVoBOperator       *  iVoBOperator       );

 /**
  * Get the current VoBoperator if it exists
  *    . 
  */
                 const CATTopVoBOperator       * GetVoBOperator                   ();

 /**
  * @param iFailureResults : list of failure containing the check and the failing operand(s)
  * @param iBlock : 
  * @param iCompletion : True if ended else false (useful when background option is activated)
  *    . 
  */
                       void                      GetVoBResults                    (      CATLISTP(CATCGMVoBResult)& iFailureResults    ,
                                                                                         CATBoolean                 iBlock             ,
                                                                                         CATBoolean               & iCompletion        );


  //------------------------------------------------------
  // DRep
  //------------------------------------------------------
  /**
  * @param iDRepBehavior : Use CATDeclarativeContext and CATDeclarativeApplication to create this object.
  * 
  */
                       void                      SetDRepBehavior                  (      CATPGMDRepBehavior      *  iDRepBehavior      );

  //------------------------------------------------------
  // Factory
  //------------------------------------------------------
                       void                      SetFactory                       (      CATGeoFactory           *  iFactory           );

  //------------------------------------------------------
  // Analyse CheckJournalData
  //------------------------------------------------------
                       CATTopCheckJournalData  * GetTopCheckJournalData           (      CATBoolean                 iRequired          = TRUE) const;

  //------------------------------------------------------
  // Warnings
  //------------------------------------------------------
                       CATTopOpInError         * GetWarning                       ();
                       void                      AppendWarning                    (      CATCGMDiagnosis         *  iWarning           );
                       void                      RemoveAllWarning                 ();
  /** 
  *  Simulate CGMWarning if Warning_On and Flush Result.
  */
  virtual              CATCGMInputError        * GetCATCGMWarning                 ();

  //
  // Diagnosis: take care using it. Only for data transfer between to CATExtTopOperator. 
                       void                      GetLocalWarningDiagnosis         (      CATLISTP(CATCGMDiagnosis)& ioDiagnosisList    );
  //------------------------------------------------------
  // Diagnosis: do not use it. Only for CGMReplay usage
  //------------------------------------------------------
  private:
                       void                      ReadWarningDiagnosis             (      CATLISTP(CATCGMDiagnosis)& ioDiagnosisList    );
  
  //------------------------------------------------------
  // Acces à l'interface
  //------------------------------------------------------
  public:
                       CATTopOperator          * GetTopOperator                   ()                                                       const; // Safe
    
  /** @nodoc CATTopCheckJournal   */
  virtual              void                      RequireDefinitionOfInputAndOutputObjects();

  // CATTopCheckJournal  
                       void                      SetNoInputObjects                ();

  // acces a l'ensemble des donnees d'output (code commun avec CATTopMultiResult)
  virtual              void                      GetAllResults                    (      CATBody                **& oNewBodies         ,
                                                                                         CATCGMJournalList      **& oNewReports        ,
                                                                                         CATLONG32                & oNBody             );

  //--------------------------------------------------------------------------------------------------------------
  //  GetErrorObjects : private service
  //--------------------------------------------------------------------------------------------------------------
  static               void                      GetErrorObjects                  (      CATError                *  piError            ,
                                                                                         CATLISTP(CATBody)        & ioListOfOutputErrors);

//-----------------------------------------------------------------
//  Gestion des interruptions
//-----------------------------------------------------------------
  
  //------------------------------------------------------
  // Method to provide the "progress bar display and interrupt query" function
  // (Creates automatically the current progress bar if undefined)
  //------------------------------------------------------
  //                   void                      SetProgressBarFunction           (      CATCGMInterruptFunction   ipInterruptFunction );

  // Set the "parent progress bar" to progress bar of this operator
  // (Creates automatically the current progress bar if undefined)
  // iParentProgressBar : Parent progress bar
  // iStartPercentage, iEndPercentage : Start and End percentages of the current progress bar inside parent progress bar range
  // Sample : If the current operator will go from 20% to 80% of the total range of the parent operator,
  //          set iStartPercentage = 20.0 and iEndPercentage = 80.0
  //                   void                      SetParentProgressBar             (      CATCGMProgressBar       * iParentProgressBar  , 
  //                                                                               const double                    iStartPercentage    = 0.0,
  //                                                                               const double                    iEndPercentage      = 100.0);




  /**
  * Sets the progress.
  * <ul>
  * <li>If iValue=0 and iTotal value=0, interrupt function is called to check if "stop" is requested.
  * <li>If iValue is outside progress range, the real progress value won't change.
  * <li>An internal test avoid any progress back if iValue is lesser than current progress value.
  * </ul>
  * @param iValue
  * The value currently reached (between 0 and iTotalValue if iTotalValue>0.)
  * @param iTotalValue
  * The value that is reached when 100% progress is achieved.
  * @param iThrowIfInterrupted
  * Indicates if an error "MathInterruptedOperator_ERR_110" has to be raised in case of interruption
  * @param iStaticConstLabel
  *  Be carefull for labell of stochastic interruption
  * @return
  * A boolean to specify whether computation should continue (TRUE) or stop (FALSE.)
  */
//virtual              CATBoolean                SetProgress                      (const double                     iValue             = 0.0,
  //                                                                ,              const double                     iTotalValue        = 100.0,
  //                                                                                     CATBoolean                 iThrowIfInterrupted= FALSE,
  //                                                                               const char                    *  iStaticConstLabel  = NULL);



//virtual              CATCGMProgressBar       * GetProgressBar                   ();
//                     CATCGMProgressBar       * GetProgressBarNoCreation         ();

  // DEPRECATED - DEPRECATED -DEPRECATED -DEPRECATED
  // DEPRECATED : Sort en erreur si on doit interrompre : MathInterruptedOperator_ERR_110
//virtual              void                      MustInterruptExecution           (      int                        iProgressValue     = 0,
  //                                                                                     int                        iProgressRange     = 0);

  // DEPRECATED : Methode statique pour les operateurs qui NE derivent PAS de CATExtGeoOperator
  // Sort en erreur si on doit interrompre : MathInterruptedOperator_ERR_110
  // Ne gere absolument pas l'empilement des ProgressBar. Si vous voulez gérer cet empilement, migrez sur
  // la classe CATCGMProgressBar
//static               void                      S_MustInterruptExecution         (      int                        iProgressValue     = 0,
  //                                                                                     int                        iProgressRange     = 0);

  // PropagateJournalMustBeCreatedByTopOperator 
  static               void                      PropagateJournalMustBeCreatedByTopOperator
                                                                                  (const CATTopData               & iTopData           ,
                                                                                         CATTopData               & ioTopData          );

  // To Update settings of the Operator from parameters stored in Ext of CGMReplay 
                       void                      UpdateSettingsFromExtCGMReplay   (      CATExtCGMReplay         *  piExtCGMReplay     );

  /** @nodoc */
  virtual              CATCGMCellTracker       * CreateCellTracker                ();

  /** @nodoc */
  virtual              CATBoolean                HasMultiResultBehavior           ();

  /** @nodoc  */
  virtual              CATExtTopMultiResult    * GetMultiResultExtension          ();

  //------------------------------------------------------
  // Failsafe mode
  //------------------------------------------------------

  /** @nodoc @nocgmitf */
                       void                      SetFailsafeMode                  (      CATBoolean                 iFailsafeMode      );

  /** @nodoc @nocgmitf */
                       CATBoolean                GetFailsafeMode                  ();

  /** @nodoc @nocgmitf */
                       void                      GetFailsafeDiagnosis             (      CATLISTP(CATCGMDiagnosis)& oFailsafeDiagnosis );

  /** @nodoc @nocgmitf */
                       void                      AppendFailsafeDiagnosis          (      CATCGMDiagnosis         *  iDiagnosis);

  //------------------------------------------------------
  // Warning check
  //------------------------------------------------------

  /** @nodoc @nocgmitf */
                       CATLISTP(CATCGMDiagnosis)*ReadWarningReference             ();

  /** @nodoc @nocgmitf */
                       void                      AppendWarningReference           (       CATCGMDiagnosis        *  iDiagnosis);

  /** @nodoc @nocgmitf */
                       void                      RemoveAllWarningReference        ();

protected :
  //------------------------------------------------------
  // CheckJournal
  //------------------------------------------------------

  // CheckJournal / pour donner les entrees de l'operateur ... 
                       void                      AddInputBody                     (      CATBody                 *  input              ,
                                                                                         CATTopCheckJournalType     copy_or_not        = CATTopCheckCopy);
   
  // CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... 
                       void                      AddInputObject                   (      CATICGMObject           *  obj                ,
                                                                                         CATTopCheckJournalType     copy_or_not        = CATTopCheckNoCopy);
   
   /** @nodoc  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
                       void                      AddInputObjects                  (const CATLISTP(CATGeometry)    & objs               ,
                                                                                         CATTopCheckJournalType     copy_or_not        = CATTopCheckNoCopy);

  // CATTopCheckJournal
                       CATBoolean                IsFullyDefinedForInputAndOutputObjects();
  
  // CATTopCheckJournal  
                       void                      SetFullyDefinedForInputAndOutputObjects(CATBoolean                 iStatus            );


  // CATTopCheckJournal  
                       CATBoolean                HasNoInputObjects                ();

 // CATTopCheckJournal
                       void                      SetOutputErrors                  (CATLISTP(CATBody)              & ioListOfErrorBodies);
  
  /** @nodoc : CATCGMReplay  / Dump de la definition de l'operateur et son status actuel (Config,Input) + affinite */
  virtual              void                      Dump                             (      CATCGMOutput             & os                 );
  
  /** @nodoc : CATCGMReplay  / Dump du resultat de l'execution l'operateur (Body,Journal) + affinite */
  virtual              void                      DumpOutput                       (      CATCGMOutput             & os                 );

  /** @nodoc */
                       void                      DumpAllResults                   (      CATCGMOutput             & os                 );
  
  /** @nodoc : CATCGMReplay  / Sauvegarde des informations avant execution (Input/Output ,Config, ..) + affinite */
                       void                      WriteInput                       (      CATCGMStream             & ioStream           );
  
  /** @nodoc : CATCGMReplay  */
                       void                      WriteTopOperator                 (      CATGeoFactory           *  iFactory           ,
                                                                                         CATCGMStream             & ioStream           ,
                                                                                         CATBoolean                 iWithSpecifiedInOut,
                                                                                         CATBoolean                 iTrueBefore_FalseAfter_Run);
  /** @nodoc : CATCGMReplay  */
                       void                      WriteTopOpStochasticAfterRun     (      CATCGMStream             & ioStream           );
  
/** @nodoc : CATCGMReplay  */
                       void                      ReadTopOpStochasticAfterRun     (      CATCGMStream             & ioStream           );
                        
  /** @nodoc : CATCGMReplay  / Controle de validite des resultats (TopCheckJournal +..) */
  virtual   CATCGMOperator::CATCheckDiagnostic   CheckOutput                      (      CATCGMOutput             & os                );

public :

  //------------------------------------------------------
  // XScale CGMReplay management
  //------------------------------------------------------
                       void                      SetCGMODTScaleManager            (      CATCGMODTScaleManager   *  iCGMODTScaleManager) ;


                       CATCGMODTScaleManager   * GetCGMODTScaleManager            ();
  
  //------------------------------------------------------
  // CATCGMReplay_GetAsynchronous
  //------------------------------------------------------
  virtual              void                      CATCGMReplay_GetAsynchronous     (     CATListOfCATUnicodeString & oAnomalyManagement );

  //------------------------------------------------------
  // CATCGMReplay_CheckInput_Factory
  //------------------------------------------------------
                       int                       CATCGMReplay_CheckInput_Factory  (         CATCGMOutput          & osDump             ) ; 

                       int                       CATCGMReplay_CheckOutput_Journal (         CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_CheckOutput_LiveBody(         CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_CheckOutput_Factory (         CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_CheckOutput_CellTrackerData(  CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_CheckOutput_Extension(        CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_CheckOutput_Persistency(      CATCGMOutput          & osDump             );

  


                       int                       CATCGMReplay_ValidateOutput_BodiesMapping (CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_ValidateOutput_JournalMapping(CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_ValidateOutput_RecyclingRate (CATCGMOutput          & osDump             );


                       int                       CATCGMReplay_ValidateOutput_CheckFastUpdate(CATCGMOutput         & osDump             );

                       int                       CATCGMReplay_ValidateOutput_CheckVoB      (CATCGMOutput          & osDump             );

                       int                       CATCGMReplay_ValidateOutput_CellTrackerData(CATCGMOutput         & osDump             );

  //------------------------------------------------------
  // Detect_
  //------------------------------------------------------

                       void                      Asynchronous_Detect_CheckFastUpdate(       CATCGMOutput          & osDump             );

                       void                      Asynchronous_Detect_CheckVoB(              CATCGMOutput          & osDump             );

                       void                      Asynchronous_Detect_CellTrackerData(       CATCGMOutput          & osDump             );

                       void                      Asynchronous_Detect_JournalMapping(        CATCGMOutput          & osDump             );

  //------------------------------------------------------

  /**
  * @nodoc  
  */
  virtual              CATOprTopologicalOperator*GetOprTopologicalOperator        ();
  
  /** @nodoc : CATCGMReplay  */
public :


  //------------------------------------------------------
  //------------------------------------------------------
                       void                      SynchroCATTopCheckJournalData    (      CATExtTopOperator       *  iEmitter           ) ;  

  /**
  * Get the current DRepBehavior if it exits or not
  */  
                       CATPGMDRepBehavior      * GetDRepBehavior                  ()                                                      const;

protected :
  //------------------------------------------------------
  virtual                                       ~CATExtTopOperator();
  
                       void                      SetResult                        (      CATBody                 *  iBody              );
  
  
  virtual              CATBody                *  GetResult                        (      CATCGMJournalList       *  iJournal           );
  virtual              CATBody                *  GetResult                        ();

                 const CATTopData              & GetTopData                       ()                                                      const;

#ifdef CATIACGMR419CAA
  //------------------------------------------------------
  // Compute InputsDefinition category
  //------------------------------------------------------
  virtual              void                      DefineInputsType                 ();
#endif

  //------------------------------------------------------
  // Retrieve CheckJournalData
  //------------------------------------------------------
                       CATTopCheckJournalData  * RetrieveTopCheckJournalData      ();

  //------------------------------------------------------
  // Generate Cell Tracking Data (KY1)
  //------------------------------------------------------
  public :
  virtual              void                      GenerateCellTrackingData         ();
          INLINE       CATCellTrackingData     * GetCATCellTrackingData           ();
  virtual              CATCGMJournalList       * GetJournalForCellTracker         () ;
                       void                      SetJournalComplet                (      CATCGMJournalList       *  iJournalComplet    );
                       void                      SetMultiDimensionTracking        (      CATBoolean                 iIsMultiDim        );
                       CATBoolean                IsEnableMultiDimensionTrack      ();
                       CATBoolean                IsJournalComplet                 () ;

  //------------------------------------------------------
  // Hidden Seam Cell Management (KY1)
  //------------------------------------------------------
  //                                anciennement HasCGMAttrinbuteManagingDone     () renommage NLD151014
          INLINE       int                       HasCGMAttributeManagingDone      (      CATTopCGMAttributeLabel    iCGMAttributeLabel );
          INLINE       void                      SetCGMAttributeManagingStatus    (      CATTopCGMAttributeLabel    iCGMAttributeLabel );

  //------------------------------------------------------
  // Info Error Creation (KY1 : Temp Location)
  //------------------------------------------------------
                       void                      CreateErrorInfo(CATError *piError, CATBoolean iRemoveObj);
  //------------------------------------------------------
  // update error (mainly CGMDiagnosis) according to input of operator
  //------------------------------------------------------
                       void                      UpdateError(CATError * iError);
                       void                      CATTopOpUpdateBodyInError(CATTopOpInError * ErrorToUpdate, ListPOfCATBody * iListOfInputBodies, CATCGMJournalList * JournalTillFailure);

private :

//-----------------------------------------------------------------
//  GetTransaction, checking that it has the same factory as this operator 
//-----------------------------------------------------------------
                   CATCGMOperatorRunTransaction* GetRunTransaction                () const;

//-------------------------------------------------------
//  Fonctionnalites FastUpdate
//-------------------------------------------------------
// protected :
// (see below) CATContextForFastRun* _Ctx;
//-------------------------------------------------------

public:
  virtual              CATContextForFastRun    * GetContextForFastRun             ();
  virtual              CATContextForFastRun    * GetOrCreateContextForFastRun     ();
  virtual              CATContextForFastRun    * ODTGenerateFastRunContextFromFirstRun();
  virtual              void                      ODTFillFastRunContextFromFirstRun(CATContextForFastRun * ioContextToFill);
  virtual              void                      Redefinition                     ();

  virtual              void                      SetContextForFastRun             (     CATContextForFastRun     *  ipCtx              );

  virtual              CATFastRunStatus          CheckContextForFastRun           ();
  virtual              CATFastRunStatus          PrepareOrExecuteFastRun          ();
  virtual              int                       FastRun                          ();
  virtual              int                       PartialRun                       (     CATBody                  *  ipFastRunResultBody,
                                                                                        CATCGMJournalList        *  ipFastRunJournal   );

  //===============================================
  // Outils pour Redefine (tests N1 FastRun)
  //===============================================
public:
  virtual              void                      Redefine                         (      CATechGet               *  iNewOption         );
  virtual              void                      GetDefinition                    (      CATechAttribute         *& oAttribute         );

  virtual              CATBoolean                WithFastRunContext               ();

//-------------------------------------------------------
public:
  //===============================================
  // Methods for LiveShape environment
  //===============================================

  // Cast used to protect LiveBody (VB7)
  virtual INLINE       CATDRepExtTopOperator   * CastToCATDRepExtTopOperator      ();

//-------------------------------------------------------

public:
  /** @nodoc CATIA Live Shape  */
  virtual              void                      AddDeclarativeManifoldAgents     (      CATCellManifoldsManager  & iCellManifoldsManager,
                                                                                         ListPOfCATBody           & iListOfInputBodies ,
                                                                                         ListPOfCATBody           & iListOfNoCopyInputBodies,
                                                                                         CATBody                 *  iOutputBody        ,
                                                                                         CATCGMJournalList       *  iTopOpJournal      );
  /** @nodoc CATIA Live Shape  */
  virtual              void                      GetResultAndJournal              (      CATBody                 *& oResultBody        ,
                                                                                         CATCGMJournalList       *& TopOpJournal       );
  /** @nodoc CATIA Live Shape  */
  virtual              void                      ReadInputBodies                  (      ListPOfCATBody           & oListOfCopyInputBodies,
                                                                                         ListPOfCATBody           & oListOfNoCopyInputBodies);

  // Implementation of CATTopOperator::ReadInputBodies accessible from CATIPGMRunnerOperatorImplDefine.h
  static               void                      CATTopOperator_ReadInputBodies   (      CATTopOperator          *  pCurTopOperator    ,
                                                                                         ListPOfCATBody           & oListOfCopyInputBodies  ,
                                                                                         ListPOfCATBody           & oListOfNoCopyInputBodies);

  // VUC:2010-02-08 Must be use between run on the same operator, if you need definitionofinputandoutput
                       void                      CleanDefinedInputAndOutputForMultiRun();

  // Gestion du Journal et du TopaData Local destinés aux opérateurs spécifiques (KY1 : 09/02/2011)
  /**
  * @nodoc  
  */
                       void                      CreateLocalTopData               ();
  /**
  * @nodoc  
  */
                       CATTopData              * GetLocalTopData                  ();
  /**
  * @nodoc  
  */
                       void                      InsertLocalJournalInMasterJournal();
  /**
  * @nodoc  
  */
                       void                      SetInsertLocalJournalInMasterJournal(   CATBoolean                 iOption            );
   
  /**
  * @nodoc  
  */
                       void                      CreateAndManageLifeCycleOfJournal(      CATSoftwareConfiguration*  iSoftConfig        ,
                                                                                         CATCGMJournalList       *& ioJournal          );

   /**
   * @nodoc  
   */
                       CATBoolean                IsSelfReportingActivated         ();

//------------------------------------------------------
// AdvancedWarning OverModelSize check
//------------------------------------------------------
public:
    /** @nodoc AdvancedWarning Rules  */
                       void                      SetBodyForOverModelSizeAdvancedCheck(   CATBody                 *  ipObj              ); 
          INLINE       CATBody                 * GetBodyForOverModelSizeAdvancedCheck()                                                  const ;
                       HRESULT                   AdvancedCheckAndAppendWarning       (   CATCGMWarningAdvanced      iAdvancedWarning   ,
                                                                                         CATBody                 *  ipObj              );

private :

  /* Internal use only 
   * 
   * Give _DRepBehavior elements (DeclarativeContext + DeclarativeApplication ) to CellManifoldsManager
   * -----------------------*/
                       void                      TransfertContextAndApplication   (      CATCellManifoldsManager *  iCellManifoldManager);

                       void                      CopyTopExtDataPreRunFrom         (      CATExtTopOperator  const*  ipSource           );
                       void                      CopyTopExtDataPostRunFrom        (      CATExtTopOperator  const*  ipSource           );

  //------------------------------------------------------
  // Spatial.Open.Solution
  //------------------------------------------------------
  virtual              void                      Mayday_Decorate                  (      int                        i0Before_1After    ,
                                                                                         CATechAttribute         *  ioAttribute        );

  //------------------------------------------------------
  // Before/After run subroutines
  //------------------------------------------------------
                       void                      _BeforeRun_AllowMultiRun         ();
                       void                      _BeforeRun_KY1_UnsmartGeometry   (      int                        iDepth             );
                       void                      _BeforeRun_KY1_CGMAttributePropagation();
                       void                      _BeforeRun_KY1_CheckUpMemorize   ();
                       void                      _BeforeRun_PFV                   ();
                       void                      _BeforeRun_VUC                   (      int                        CATIncrementalStreamLevel );
                       void                      _BeforeRun_TCX                   ();
                       void                      _BeforeRun_Chain                 ();
                       void                      _BeforeRun_Check                 ();
  // starter , but insuffisient-inapppropriate (because non exhaustive operator management , limited scope of "GMTk" public interfaces
  // general purpose footprint, ignition by unsmart topology management , !! too much before-after 
                       void                      _BeforeRun_FootPrint               (      int                        iDepth             );

                       void                      _AfterRun_KY1_UnsmartGeometry      (      int                        iDepth             );
                       void                      _AfterRun_KY1_CGMAttributePropagation();
                       void                      _AfterRun_KY1_CheckUpMemorize      ();
                       void                      _AfterRun_PFV                      ();
                       void                      _AfterRun_VUC                      (      int                        CATIncrementalStreamLevel);
                       void                      _AfterRun_Chain                    ();
                       void                      _AfterRun_Check                    ();
                       void                      _BeforeRun_KY1_JournalOfDomains    ();   
                       void                      _AfterRun_KY1_JournalOfDomains     ();
                       void                      _AfterRun_KY1_ReOrder              ();
  // starter , but insuffisient-inapppropriate (because non exhaustive operator management , limited scope of "GMTk" public interfaces
  // general purpose footprint, ignition by unsmart topology management , !! too much before-after 
                       void                      _AfterRun_FootPrint              (      int                        iOkRun             ,
                                                                                         int                        iDepth             ,
                                                                                         int                        iDepthForChain);
#ifdef ParameterForTestKeepAndDelete
                       void                      _AfterRun_Test                   ( );
                       void                      _BeforeRun_Test                  ( );
#endif
  //------------------------------------------------------
  //------------------------------------------------------
                       void                      SetVoBResultReference            (      CATLISTP(CATCGMVoBResult)* iListOfResults);
                       void                      GetVoBResultReference            (const CATLISTP(CATCGMVoBResult)*&oListOfReferences);
  
  static               void                      ModifyTopData                    (      CATTopData               & ioTopData        );



  //*****************************************************************************
  // UNDER DEVELOPEMENT ! DO NOT USE
  // For imprint project, those methods will be added directly the generic infra after.
  //*****************************************************************************
protected:

  /** @nodoc @nocgmitf*/
  virtual void DumpOutputExt(CATCGMOutput& os);

  /** @nodoc @nocgmitf*/
  virtual void DumpTopOutputExt(CATTopCheckJournal* ipEquivalent, CATCGMOutput& os);

  /** @nodoc @nocgmitf
   * U29@070618
   */
  virtual void DumpOutputExt_Imprint(CATCGMOutput& os);

  /** @nodoc @nocgmitf
  * U29@070618
  */
  virtual void DumpTopOutputExt_Imprint(CATTopCheckJournal* ipEquivalent,
                                        CATCGMOutput& os);

  //------------------------------------------------------
  // Failsafe mode
  //------------------------------------------------------
private:

                       void                      RemoveAllFailsafeDiagnosis();


  //======================================================
  // Data
  //======================================================
private :
  //
  CATLISTP(CATCGMDiagnosis)    _WarningDiagnosisList;
  CATTopData                   _TopData;
  CATTopCheckJournalData     * _TopCheckJournalData;
  CATBody                    * _Result;
  CATCGMVoBTool              * _CheckTool;
  CATTopVoBOperator          * _CheckOperator;
  CATBoolean                   _IsVoBSaved;
  CATPGMDRepBehavior         * _DRepBehavior;
  CATBodyFreezeMode            _FreezeMode;
  CATBoolean                   _DefinedForInputAndOutputObjects;
  CATBoolean                   _NoInputObjects;
  CATBoolean                   _EnableMultiDimensionTrack;
  CATBoolean                   _IsEmptyJournalBeforeRun; 
  CATBoolean                   _HasResultBody;
  //CATCGMProgressBar        * _ProgressBar;

  CATCGMODTScaleManager      * _CGMODTScaleManager;

  static CATCGMOperator      * _FactoryPreviousCurrentOperator;

#ifdef CATIAR424
  EK::Trace                  * _pRunEkTraces;
#endif

#ifdef CATIACGMR419CAA
  CATTopInputDefinitionType _InputDefinitionType;
#endif

protected:

#ifdef CATIAR424
  INLINE EK::Trace * GetRunEkTraces() const { return _pRunEkTraces; }
#endif

  // Data for Cell Tracking Data (KY1)
  CATCellTrackingData        * _CATCellTrackingData; //Le cell tracking data qui contient le résultat de l'execution de l'opérateur    
  // To indicate if internal Cell Tracker has been enabled for H.S or S.G use
  CATBoolean                   _EnableInternalCellTracker;
  // To indicate if Hidden Seam Cell Managing has been done : Propagation or Decoration
  int                          _HasCGMAttributeManagingDone;

  // Gestion du Journal et du TopaData Local destinés aux opérateurs spécifiques (KY1 : 09/02/2011)  
  CATBoolean                   _InsertJournalAttheEndOfRun;
  CATTopData                 * _LocalTopData;
  CATCGMJournalList          * _LocalJournal;
  CATCGMJournalList          * _TassedLocalJournal;
  CATBoolean                   _WithLifeCycleManagement;
  
  CATLISTP(CATCGMVoBResult)  * _ListOfVoBReferences;

  CATCGMVoBOptionControl     * _VoBOperatorOptionControl;

  CATLISTP(CATCGMDiagnosis)    _RefWarningList;

//-------------------------------------------------------
//  Fonctionnalites FastUpdate
//-------------------------------------------------------
protected :
  CATContextForFastRun       * _Ctx;

  // Set both results from iCurOpe in the context from this operator, ioContext.
  virtual void SetAllContextResults(CATContextForFastRun* ioContext, CATTopOperator * iCurOpe);

  
private:

  CATCGMJournalList          * _JournalComplet; // Journal complet

  //------------------------------------------------------
  // Failsafe mode
  //------------------------------------------------------
private:
  // (see above)       void                      RemoveAllFailsafeDiagnosis();
  CATBoolean                   _FailsafeMode;
  CATLISTP(CATCGMDiagnosis)    _FailsafeDiagnosis;

// public :
  // CATCGMReplay_*() methods: see above


//------------------------------------------------------
// AdvancedWarning OverModelSize check
//------------------------------------------------------
private:
  // See above
  // public:
  //                   void                      SetBodyForOverModelSizeAdvancedCheck(   CATBody                 *  ipobj              ); 
  //      INLINE       CATBody                 * GetBodyForOverModelSizeAdvancedCheck()                                                  const ;
  //                   HRESULT                   AdvancedCheckAndAppendWarning       (   CATCGMWarningAdvanced      iAdvancedWarning   ,
  //                                                                                     CATBody                 *  ipObj              );
  CATBody                    * _BodyForOverModelSizeAdvancedCheck;
#ifdef ParameterForTestKeepAndDelete
  int                          _JournalAlreadyFilled;
#endif

  //======================================================
  // Friends
  //======================================================
  friend class CATTopOperator;
  friend class CATTopMultiResult;
};

  //======================================================
  // INLINE implementations
  //======================================================
 
//-----------------------------------------------------------------
// GetTopData 
//-----------------------------------------------------------------
          INLINE       void                      CATExtTopOperator::GetTopData    (      CATTopData               & ioTopData          ) const
{
  ioTopData = _TopData;
}

//------------------------------------------------------
// GetSoftwareConfiguration
//------------------------------------------------------
          INLINE       CATSoftwareConfiguration* CATExtTopOperator::GetSoftwareConfiguration()                                           const
{
  return _TopData._Config;
}

//------------------------------------------------------
// SetSoftwareConfiguration
//------------------------------------------------------
          INLINE       void                      CATExtTopOperator::SetSoftwareConfiguration
                                                                                  (      CATSoftwareConfiguration*  iConfig            )
{
  _TopData.SetSoftwareConfiguration(iConfig);
}

//------------------------------------------------------
// GetJournal
//------------------------------------------------------
          INLINE       CATCGMJournalList       * CATExtTopOperator::GetJournal    () const
{
  return _TopData._Journal;
}

//------------------------------------------------------
// SetJournal
//------------------------------------------------------
                       void                      CATExtTopOperator::SetJournal    (      CATCGMJournalList       *  iJournal           )
{
  //KY1(30/03/2011) : replace a journal by another one 
  //     when self reporting is enabled is forbidden
  //if (_WithLifeCycleManagement && _TopData.GetJournal()) return;
  _TopData.SetJournal(iJournal);
}

//------------------------------------------------------
// GetHasResultBody
//------------------------------------------------------
          INLINE       CATBoolean                CATExtTopOperator::GetHasResultBody 
                                                                                  () const
{
  return _HasResultBody;
}

//------------------------------------------------------
// SetHasResultBody
//------------------------------------------------------
          INLINE       void                      CATExtTopOperator::SetHasResultBody 
                                                                                  (      CATBoolean                 iHasResultBody     )
{
  _HasResultBody = iHasResultBody;
}

//----------------------------------------------------------------------
// Test whether a given CGM Attribute Decoration or Propagation has Been done (KY1)
//----------------------------------------------------------------------
          INLINE       int                       CATExtTopOperator::HasCGMAttributeManagingDone
                                                                                  (      CATTopCGMAttributeLabel    iCGMAttributeLabel )
{ 
 return (_HasCGMAttributeManagingDone ^ iCGMAttributeLabel);
}

//----------------------------------------------------------------------
// Set the the status of a given CGM Attribute Decoration or Propagation (KY1)
//----------------------------------------------------------------------
          INLINE       void                      CATExtTopOperator::SetCGMAttributeManagingStatus
                                                                                  (      CATTopCGMAttributeLabel    iCGMAttributeLabel  )
{
  _HasCGMAttributeManagingDone |= iCGMAttributeLabel;
}

//----------------------------------------------------------------------
// Cast used to protect LiveBody (VB7)
//----------------------------------------------------------------------
          INLINE       CATDRepExtTopOperator   * CATExtTopOperator::CastToCATDRepExtTopOperator   ()
{
  return NULL;
}

//----------------------------------------------------------------------
// AdvancedWarningCheck Object
//----------------------------------------------------------------------
          INLINE       CATBody                 * CATExtTopOperator::GetBodyForOverModelSizeAdvancedCheck () const
{ 
  return _BodyForOverModelSizeAdvancedCheck;
}

//----------------------------------------------------------------------
// GetCATCellTrackingData
//----------------------------------------------------------------------
          INLINE       CATCellTrackingData     * CATExtTopOperator::GetCATCellTrackingData           ()
{
  return _CATCellTrackingData;
}

#endif
