#ifndef CATExtGeoOperator_h_
#define CATExtGeoOperator_h_
//====================================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//  CAUTION
//  1) This geometric operator extent stands for general  CATCGMOperator extension
//     and not                               for specific CATGeoOperator extension
//  2) Any extension of a topological operator also derivates from this extension
//  (as far as I understand the code. NLD111219)
//
//====================================================================================================================
// Jan.  04 HCN _SessionRun
// Jul.  05 HCN Statistiques parcours UpDown :
//              _pUpDownStatEntry
// Aug.  05 HCN _Has_CATCGMOperator_Run
// Oct.  08 FDS Static method for performance analysis
// 03/11/08 NLD CATCGMOperator_TraceTimer_Start() renommee CATCGMOperator_Timer_Start()
//              (+ ajout argument iForceTraceMode)
//              CATCGMOperator_TraceTimer_Stop() renommee CATCGMOperator_Timer_Stop()
// 04/11/08 NLD Ajout arguments oCpuAll, oElapsedAll a CATCGMOperator_Timer_Stop()
// 05/11/08 NLD Ajout argument optionnel iOkRun a AfterRun()
// 14/11/08 NLD Ajout _DummyAllocForLevel1CGMOperator et ___AllocationForRemainingLevel1CGMOperator___()
//              (pour identification dans replay purify
//              des operateurs de niveau 1 non desalloues)
// 20/11/08 LAP Ajout de la methode AllowMultiRun
//              pour la protection des operateurs monorun lors de l'activation de CATCGMReplay_NbRun.
// 04/03/09 JSX Ajout de _SummaryMessage (info de BodiesMapping) 
//              pas de friend class CATTopOperator car on utilise CATExtTopOperator pour ecrire depuis un op topo
// 11/06/14 Q48 Add ScaleManager and ReplayFactory for X-scale
//                  - see tag "Q48 (06/2014): X-scale"
// 11/10/16 KY1 Management of Error raised by the operator inside CGM Operator 
//              interface/ CGMReplay Infra:
//              - Stream and Unstream the Error in CGMRepaly delegated 
//                to the CGM Operator. 
//              - Deep mapping of the Result and Reference Error during 
//                Validation Output Step (Nested Errors are mapped and Bodies 
//                referenced by errors are also mapped) 
// 21/03/17 NLD Ajouts arguments a ___AllocationForRemainingLevel1CGMOperator___()
//              pour distinction sortie d'operateur standard/exception
//              Detabulation et mise au propre
// 24/03/17 KY1 Correction of "MultiRun CGMReplay Infra" VersionStream (of specific operator data)
//              must be communicated to the specific operator through the generic Unstream services
//              towards the overloaded unstream service under specific operator resp.
// 20/06/18 KY1 Introduction of InputFactory Data member and its corresponding Get service
// 11/12/19 NLD Deflaggage
//              Mise au propre (2/2); reindentation
//              Separation methodes/données
//              Documentation
//              _Has_CATCGMOperator_Run passe de public en protected ce qui est largement suffisant
// 14/10/20 Q48 Store whether config has been set --> improved warning messages
// 14/04/21 NLD friend class CATGeoODTScaleManager for special tooling
// 18/06/21 NLD friend class CATCGMOperatorRun     for special architecture
//====================================================================================================================
#include "CATIACGMLevel.h"

#include "ExportedByGeometricObjects.h"
#include "CATCGMOperator.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATString.h"
#include "CATListPV.h"
#include "CATBaseUnknown.h"
#include "CATMathInline.h"
#include "CATCGMReplayLiveAttrInitMode.h"
#include "CATCGMUnknown.h"
#include "CATCGMStreamControl.h"
#include "CATCGMStreamVersion.h"
#include "CATThrowForNullPointer.h"

#include "CATCGMWarning.h"
#include "CATCGMWarningAdvanced.h"

#include "CATCGMStreamExtendedReplay.h" 
#include "CATListOfCATUnicodeString.h"
#include "CATCGMProgressBar.h"
//#include "CATGMErrorInfo.h"

class CATUnicodeString;
class CATechAttribute;
struct CATCGMOptUDStatEntry;
class CATCGMProgressBar;
class CATCGMInputError;
class CATGeoDebug;
class CATCGMStreamImpl;
class CATCX_AuthorizedAnomaliesForCGMOperator;
class CATGMErrorInfo;


class CATGeoODTScaleManager;    // Q48 (06/2014): X-scale
class CATSoftwareConfiguration; // Q48 (03/2020): GetSoftwareConfig
class CATCGMOperatorRun;

// October 08 Static method for performance analysis FDS
// It gives the cumul of cpu and elapsed time of CGM level one operator 
// Rectricted and limited usage for temporary performance analysis
ExportedByGeometricObjects void CATCGMOperator_Timer_Start(int iForceTraceMode=0);
ExportedByGeometricObjects void CATCGMOperator_Timer_Stop ( double & oCpuCGM, CATLONG32 & oElapsedCGM,
                                                            double & oCpuAll, CATLONG32 & oElapsedAll   );



/**
  * -------------------------------------------------------------------------------------------------------
  * Extension of operators.
  * -------------------------------------------------------------------------------------------------------
*/


class ExportedByGeometricObjects CATExtGeoOperator : public CATCGMUnknown
{

  //=======================================================================================================
  // M E T H O D S
  //=======================================================================================================

public:

  //-------------------------------------------------------------------------------------------------------
  // Constructeur
  //   iOperateur peut etre NULL,  mais ca doit etre reserver au cas tres particuliers sous constructeur
  //   il faut dans ce cas s'empresser de retablir la definition avec la methode SetOperator
  //-------------------------------------------------------------------------------------------------------
                                             CATExtGeoOperator (CATCGMOperator *iOperateur);
          void                               SetOperator       (CATCGMOperator *iOperateur);

  INLINE  CATCGMOperator                   * GetGMOperator() const;
  
protected :

  //------------------------------------------------------
  // CGMReplay
  //------------------------------------------------------
  // Dedicated to CATCGMreplay : Save definition ..  Open is done by static CATLoadOperatorId(...) */
  virtual void                               WriteInput(CATCGMStream  & ioStream);
  // Dedicated to CATCGMreplay : Dump current definition */
  virtual void                               Dump      (CATCGMOutput  & os      ) ;


public:

  /*
   * A MINIMA EXTENDED RUN integration 
   * <br>Refer to  GeometricObjects\ProtectedInterfaces\CATCGMStreamExtendedReplay.h for  explanations
   */
                  //===================================================================
                  //      MINIMAL TO BE OVERLOADED AND IMPLEMENTED BY OPERATOR
                  //===================================================================

  // Reserved for Operator mandatory implement for integration of variational parameters 
  //    with one line of code : SetMultipleRun(); return TRUE;
  virtual CATBoolean                         IsMultipleRun(); 

  // For common static method about Update after loaded
  virtual CATCGMOperator                   * CreateOrUpdate(CATCGMStream &Str,const short LevelOfRuntime, const short VersionOfStream);

  // For common static method about Update after loaded
  virtual void                               DumpMultipleRun( CATCGMStream &iStream, CATCGMOutput& os );


                  //----------------------------------------------- 
                  //  FOR ENHANCED IMPLEMEMTATION 
                  //----------------------------------------------- 

  // Reserved for Operator mandatory implement for integration of variational parameters 
  virtual void                               WriteInputMultipleRun(CATCGMStream &iStream, CATCGMPad * ioPad = NULL ); 

  // Reserved for Operator mandatory implement for integration of variational parameters 
  virtual void                               ReadInputMultipleRun(CATCGMStream &iStream, const short iVersionOfStream, CATCGMPad  * ioPad = NULL ); 

  /** @nodoc */
  virtual void                               DumpInputMultipleRun( CATCGMStream &iStream, CATCGMPad * ioPad, CATCGMOutput& os );


                  //----------------------------------------------- 
                  //  For Cache Management After each Run()
                  //----------------------------------------------- 
 
  // Boolean RC : if AfterRun() should be called  
  virtual CATBoolean                         BeforeRun(int iDepth,  int iDepthForChain);

  //  iOkRun : Value 1=Okay  0=Error
  //  iDepth : Depth of Operator
  virtual void                               AfterRun (int iOkRun, int iDepth,  int iDepthForChain);


                  //------------------------------------- 
                  //  TO BE USED  BY OPERATOR
                  //------------------------------------- 

  // Dedicated for Operator implement of IsMultipleRun 
  INLINE void                                SetMultipleRun();

  // Dedicated for Operator implement in case of out of control management (getting back to Full Record/Replay)
  INLINE void                                ResetMultipleRun();


                  //------------------------------------- 
                  //  TO BE USED  BY CGMReplay ENGINE 
                  //------------------------------------- 

  // INTERNAL Dedicated for CGMReplay integration  (ENGINE Replay)
  //   return the number of necessary variation ....
         CATULONG32                          GetNumberOfRemaingMultipleRun();

  //   return TRUE if ! dummy variation
         CATBoolean                          NextRemaingMultipleRun(const short iVersionOfStream); 

  // INTERNAL Dedicated for CGMReplay integration  (ENGINE Replay)
         CATULONG32                          GetGlobalNumberOfStepsToReplay();

                  //------------------------------------- 
                  //  TO BE USED  BY CGMReplay Integration 
                  //------------------------------------- 

  // Dedicated for CGMReplay integration  
  INLINE CATBoolean                          IsUnderMultipleRunRecord(); 

  // INTERNAL Dedicated for CGMReplay integration  (RECORD)
         void                                CacheInputMultipleRun(CATCGMStream  & iStream, CATExtCGMReplay* iReplay); 




  //-------------------------------------------------------------------------------------------------------
  // Destructeur
  //   Nettoyage dedie en interne au nettoyage CATCGMOperator
  //-------------------------------------------------------------------------------------------------------
  static void                                Clear(CATExtGeoOperator * iExtension);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  //------------------------------------------------------
  // Identificateur de Session pour le Debug
  //------------------------------------------------------
  INLINE CATULONG32                          GetSessionIdentifier() const ;

  //------------------------------------------------------
  // Nommage pour classification de l'Operateur
  //------------------------------------------------------
  virtual const CATString                  * GetOperatorId() const;
          void                               SetOperatorId (const CATString & iOperatorName);

  //------------------------------------------------------
  // Mode Warning (Reserve DUC ou ulterieur)
  //------------------------------------------------------
          CATCGMWarning                      GetWarningMode        () const;
  INLINE  void                               SetWarningMode        (CATCGMWarning         iMode );
  
          CATCGMWarningAdvanced              GetWarningAdvancedMode(CATCGMWarningAdvanced iMode) const;
  INLINE  void                               AddWarningAdvancedMode(CATCGMWarningAdvanced iMode );

  //------------------------------------------------------
  // Parametrage d'une sorte de gestioon Freeze Mode
  //------------------------------------------------------
  INLINE  void                               GetResultStatus(       short & ioValidation,       short & ioModifiable ) const;
  INLINE  void                               SetResultStatus( const short   iValidation , const short   iModifiable );

  //------------------------------------------------------
  // Nombre d'execution CATCGMReplay
  //------------------------------------------------------
  INLINE  short                              GetNumberOfReplay() const;

  //------------------------------------------------------
  // Autorise le MultiRun (en mode CATCGMReplay)
  //------------------------------------------------------
  virtual CATBoolean                         AllowMultiRun() const;

  //------------------------------------------------------
  // Run
  //------------------------------------------------------
  virtual int                                RunOperator();

#ifdef CATIACGMR419CAA
  //------------------------------------------------------
  // Run Exact Operator 
  //------------------------------------------------------
  virtual int                                RunExactOperator();

  //------------------------------------------------------
  // Run Poly Operator 
  //------------------------------------------------------
  virtual int                                RunPolyOperator();
#endif

  //------------------------------------------------------
  // Factory
  //------------------------------------------------------

  // Output Factory i.e Working Factory 
  virtual void                               SetFactory             (CATGeoFactory* iFactory);
  INLINE  CATGeoFactory                    * GetFactory             () const;
  // Input Factory : It is deduced and not an input arg. of the op. like the Working Factory
  virtual CATGeoFactory                    * GetInputFactory        (); 
  INLINE void                                SetInputFactory        (CATGeoFactory* iFactory);

  //------------------------------------------------------
  // Statut CGMReplay pendant le Run()
  //------------------------------------------------------
  INLINE  void                               SetCGMReplayIsRecording(CATBoolean     iIsRecording);
  INLINE  CATBoolean                         CGMReplayIsRecording   () const;
  INLINE  void                               SetCGMReplayIsPlaying  (CATBoolean     iIsPlaying, CATCGMReplayLiveAttrInitMode iLiveAttrInitMode);
  INLINE  CATBoolean                         CGMReplayIsPlaying     (CATCGMReplayLiveAttrInitMode *opLiveAttrInitMode) const;

  virtual CATBoolean                         WithFastRunContext     ();

  INLINE  CATBoolean                         IsRunDone              ();
  INLINE  void                               SetRunIsDone           (CATBoolean iIsRunDone);

 #ifdef CATIACGMR419CAA
  //------------------------------------------------------
  // Is Poly Operator 
  //------------------------------------------------------
  virtual CATBoolean                         IsPolyOperator();
#endif

  //------------------------------------------------------------------------------
  // Denying CompositeManagement
  //------------------------------------------------------------------------------
          CATBoolean                         IsDenyingCompositeManagement() const;
  INLINE  void                               DenyCompositeManagement(CATBoolean iDeny);


  //------------------------------------------------------
  // Spatial.Open.Solution
  //------------------------------------------------------
  virtual void                               Mayday_Decorate(int i0Before_1After, CATechAttribute * ioAttribute);

  //------------------------------------------------------
  // Error Management
  //------------------------------------------------------
  //      void                               SetResErrorInfo(CATGMErrorInfo *iResErrorInfo);
          CATGMErrorInfo                   * GetResErrorInfo();
  //      void                               SetRefErrorInfo(CATGMErrorInfo *iRefErrorInfo);
          CATGMErrorInfo                   * GetRefErrorInfo();
  virtual void                               CreateErrorInfo(CATError *piError, CATBoolean iRemoveObj);

  /** 
  *  Trigger : simulation of interruption thrown.
  */
  INLINE  void                               ActivateTrigger(CATLONG32 iTrigger, const char *  iStaticConstLabel, CATBoolean ToDeleteConstLabel);
  INLINE  CATLONG32                          GetTrigger     (const char *  iStaticConstLabel);
  INLINE  void                               ResetTrigger   ();
  INLINE  CATBoolean                         HasTrigger     ();

  
  /** 
  *  HistoryKey
  */
  INLINE  void                               ResetHistoryKey();
  INLINE  CATBoolean                         HasHistoryKey();
  INLINE  void                               SetHistoryKey();


  /** 
  *  UnderControlOfLoadedReplay
  */
  INLINE  CATExtCGMReplay                  * UnderControlOfLoadedReplay() const;
          void                               SetUnderControlOfLoadedReplay( CATExtCGMReplay * iReplay) ;

  /** 
  *  Progress bar.
  */
  virtual CATCGMProgressBar                * GetProgressBar();

    //-----------------------------------------------------------------
  //  Gestion des interuptions
  //-----------------------------------------------------------------

  //------------------------------------------------------
  // Method to provide the "progress bar display and interrupt query" function
  // (Creates automatically the current progress bar if undefined)
  //------------------------------------------------------
          void                               SetProgressBarFunction(CATCGMInterruptFunction ipInterruptFunction);

  // Set the "parent progress bar" to progress bar of this operator
  // (Creates automatically the current progress bar if undefined)
  // iParentProgressBar : Parent progress bar
  // iStartPercentage, iEndPercentage : Start and End percentages of the current progress bar inside parent progress bar range
  // Sample : If the current operator will go from 20% to 80% of the total range of the parent operator,
  //          set iStartPercentage = 20.0 and iEndPercentage = 80.0
          void                               SetParentProgressBar(      CATCGMProgressBar* iParentProgressBar,
                                                                  const double             iStartPercentage = 0.0,
                                                                  const double             iEndPercentage = 100.0);

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
  virtual CATBoolean                         SetProgress(const double       iValue              =   0.0 ,
                                                         const double       iTotalValue         = 100.0 ,
                                                               CATBoolean   iThrowIfInterrupted = FALSE ,
                                                         const char*        iStaticConstLabel   = NULL);


          CATCGMProgressBar                * GetProgressBarNoCreation();

  // DEPRECATED - DEPRECATED -DEPRECATED -DEPRECATED
  // DEPRECATED : Sort en erreur si on doit interrompre : MathInterruptedOperator_ERR_110
  virtual void                               MustInterruptExecution(int iProgressValue = 0, int iProgressRange = 0);
  // DEPRECATED : Methode statique pour les operateurs qui NE derivent PAS de CATExtGeoOperator
  // Sort en erreur si on doit interrompre : MathInterruptedOperator_ERR_110
  // Ne gere absolument pas l'empilement des ProgressBar. Si vous voulez gérer cet empilement, migrez sur
  // la classe CATCGMProgressBar
  static  void                               S_MustInterruptExecution(int iProgressValue = 0, int iProgressRange = 0);

  /** 
  *  Simulate CGMWarning if Warning_On and Flush Result.
  */
  virtual CATCGMInputError                 * GetCATCGMWarning();

  /** 
  *  To Update settings of the Operator from parameters stored in Ext of CGMReplay
  */
  virtual void                               UpdateSettingsFromExtCGMReplay(CATExtCGMReplay *piExtCGMReplay);

  /** 
  *  For Dynamic Filtering of PotDeVins of CGM Operators
  */
  virtual void                               GetParametersForDynFilteringOfAnomalies
                                                                        (CATCX_AuthorizedAnomaliesForCGMOperator *piAuthorizedAnomaliesForCGMOperator);

  
  //------------------------------------------------------
  // CATCGMReplay_GetAsynchronous
  //------------------------------------------------------
  virtual void                               CATCGMReplay_GetAsynchronous(CATListOfCATUnicodeString & oAnomalyManagement);


  //------------------------------------------------------

  //------------------------------------------------------
  // CGMReplay - Xscale management
  //------------------------------------------------------

          // Q48 (06/2014): X-scale -->
          void                               SetDataForScaleManager(CATGeoODTScaleManager* iScaleManager, CATGeoFactory* iFactory);
          CATGeoODTScaleManager            * GetODTScaleManager() const;
          CATGeoFactory                    * GetInFactory() const;
          // Q48 (06/2014): X-scale <--

  //------------------------------------------------------
  // CATSoftwareConfiguration management
  //------------------------------------------------------

  // Store the config in this class for use in CATCGMOperator
  // Please note:
  //    - most (all?) operators store their own CATSoftwareConfiguration
  //    - some operators implement GetSoftwareConfiguration
  //         --> CATCGMOperator implementation not called
  //    - some operators do not implement GetSoftwareConfiguration
  //         --> CATCGMOperator implementation is called --> this mechanism is used

  static void SetConfig(      CATCGMOperator           * iOp, 
                              CATSoftwareConfiguration * iConfig,
                        const short                      iCGMLevel);

  void SetIsAGeoOperator();
  CATBoolean IsAGeoOperator() const;

  // The only access to the stored config should be through the
  // CGM operator class
  private:
    friend CATSoftwareConfiguration* CATCGMOperator::GetSoftwareConfiguration() const;
    CATSoftwareConfiguration * GetConfig(const CATCGMOperator* iOp) const;
  
  class SoftwareConfigurationStore
  {
  public:
    SoftwareConfigurationStore();
    ~SoftwareConfigurationStore();

  private:
    friend CATSoftwareConfiguration* CATExtGeoOperator::GetConfig(const CATCGMOperator* iOp) const;
    friend void CATExtGeoOperator::SetConfig(CATCGMOperator*, CATSoftwareConfiguration*, const short);
    
    CATSoftwareConfiguration * _Config;
    CATBoolean                 _ConfigSet;
  };

private:

  SoftwareConfigurationStore _ConfigStore;
  CATBoolean                 _IsGeo; // derived from CATGeoOperator (or CATCGMOperator)

public:

  //------------------------------------------------------
  // Check Legacy of CGM Operator Inputs Definition 
  //------------------------------------------------------
  virtual void                               CheckInputDefinitionCompliance();

protected :
  
  
  //------------------------------------------------------
  //Following methods can be overloaded to implement CGMReplay functionalities.
  //Warning: you can decide to overload equivalent methods of CATCGMOperator instead of these ones,
  //but it is important not to overload both.
  //Please refer to http://wikigm/mediawiki/index.php/CGMReplay for further information.
  virtual CATExtCGMReplay                  * IsRecordableExt              (short             & LevelOfRuntime, short &VersionOfStream);
  virtual void                               DumpExt                      (CATCGMOutput      & os);
  virtual void                               DumpOutputExt                (CATCGMOutput      & os);
  virtual void                               WriteInputExt                (CATCGMStream      & Str);
  virtual void                               WriteTopOutputExt            (CATCGMStream      & Str);
  virtual CATTopCheckJournal               * ReadTopOutputExt             (CATCGMStream      & Str);
  virtual CATBoolean                         ValidateTopOutputExt         (CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  virtual void                               DumpTopOutputExt             (CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  virtual CATCGMOperator::CATCheckDiagnostic CheckInputExt                (CATCGMOutput      & os);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutputExt               (CATCGMOutput      & os);
  virtual void                               WriteOutputExt               (CATCGMStream      & ioStream);
  virtual void                               DumpOutputExt                (CATCGMStream      & ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATBoolean                         ValidateOutputExt            (CATCGMStream      & ioStream, CATCGMOutput & os,int VersionNumber=1);

   // Manage Stream/Unstream of Error reaised by the Operator
          void                               ReadStochasticAfterRun       (CATCGMStream      & iStream);
          void                               WriteStochasticAfterRun      (CATCGMStream      & ioStream, CATError *piError);
  virtual void                               ReadTopOpStochasticAfterRun  (CATCGMStream      & iStream);
  virtual void                               WriteTopOpStochasticAfterRun (CATCGMStream      & ioStream);

  //end of CGMReplay methods

  typedef enum {Level1Allocation_StandardExit = 1,
                Level1Allocation_ErrorExit    = 2
               }Level1Allocation_Type;
          void                               ___AllocationForRemainingLevel1CGMOperator___
                                                                          (Level1Allocation_Type iType    = Level1Allocation_StandardExit,
                                                                           int                   iReplace = 0) ;

  virtual                                   ~CATExtGeoOperator();

  INLINE const CATString                  * _GetOperatorId();

private :

                                             CATExtGeoOperator         (const CATExtGeoOperator &iCopy);
          CATExtGeoOperator& operator =                                (const CATExtGeoOperator &iCopy);

          void                               CopyGeoExtDataPreRunFrom  (CATExtGeoOperator  const* ipSource);
          void                               CopyGeoExtDataPostRunFrom (CATExtGeoOperator  const* ipSource);

  //=======================================================================================================
  // D A T A
  //=======================================================================================================
public:

protected :

  CATBoolean                         _Has_CATCGMOperator_Run; // deplacée de public en protected; accès externe par CATCGMOperator qui est friend; NLD111219

  //------------------------------------------------------
  //   
  //------------------------------------------------------

  CATString                        * _OperatorId;             // the name of the operator
  CATUnicodeString                 * _SummaryMessage;         // fin de la ligne Summary dans le fichier .status
  CATCGMOperator                   * _Operateur;

  //------------------------------------------------------
  // Error Management (Dedicated CGMReplay)
  //------------------------------------------------------
  CATGMErrorInfo                   * _ResErrorInfo;
  CATGMErrorInfo                   * _RefErrorInfo;
  // Dedicated Interrupt mechanism
  CATLONG32                          _InterruptHistory;
  CATLONG32                          _InterruptCounter;
  char                             * _InterruptHistoryLabel;

private :
 

  CATGeoFactory                    * _Factory;                // the factory in the operator (can be scaled by _GeoODTScaleManager)
  CATGeoFactory                    * _InputFactory;           // the input factory : the one that input objects of the Op/. belong to 

  CATCGMProgressBar                * _ProgressBar;

  // Q48 (06/2014): X-scale -->
  CATGeoODTScaleManager            * _GeoODTScaleManager;     // store the scale manager
  CATGeoFactory                    * _ReplayInFactory;        // the original factory in the replay file
  // Q48 (06/2014): X-scale <--

  struct CATCGMDbgOp
  {
          unsigned SessionId                  : 32;


          unsigned NumberOfReplay             :  5;
          unsigned ForceCaptureMode           :  1;
          unsigned ForceCheckMode             :  1;
          unsigned IsRunning                  :  1;
          unsigned InvalidResult              :  1;
          unsigned FrozenResult               :  1;
          unsigned IsRecording                :  1;
          unsigned IsPlaying                  :  1;
            signed LiveInit                   :  3;
          unsigned IsRunDone                  :  1;
          unsigned TriggerToDeleteConstLabel  :  1;
          unsigned IsMultipleRun              :  1;
          unsigned UnderMultipleRunRecord     :  1;
          unsigned WarningMode                :  2; // 0:Warning_Off // 1:Warning_On // 2:Warning_Advanced 
          unsigned WarningModeAdvanced        :  1; // 1: Warning_Advanced_ModelSizeExceeded 
    
          unsigned DenyingCompositeManagement :  1;

          unsigned _WithHistoryKey            :  1;



          CATCGMExplicitParameters * _ManyVariations;
          CATExtCGMReplay          * _UnderControlOfLoadedReplay;

          CATLONG32                  _Trigger;                // Interrupt management with CGMReplay
    const char                     * _TriggerStaticConstLabel;

          int                      * _DummyAllocForLevel1CGMOperator ; // small allocation (in memorycheck mode) remaining if operator leak


  }
  Debog;

  //------------------------------------------------------
  // Nombre de CATExtGeoOperators crees = environ nombre de CATCGMOperators crees
  // Nombre de CATExtGeoOperators executes < nombre de CATCGMOperators executes
  //------------------------------------------------------

  static CATULONG32                  _SessionBorn ;
  static CATULONG32                  _SessionRun ;

  friend class CATCGMOperator;
  friend class CATExtCGMReplay;
  friend class CATCGMReplayRecord;
  friend class CATCXFactoryTransaction;
  friend class CATGeoDebug;
  friend class CATCGMStreamImpl;
  friend class CATGeoODTScaleManager;
  friend class CATCGMOperatorRun;
};

  //=======================================================================================================
  // I N L I N E    M E T H O D S
  //=======================================================================================================

//-------------------------------------------------------------------------------------------------------------
//  GetSessionIdentifier
//-------------------------------------------------------------------------------------------------------------
INLINE CATULONG32  CATExtGeoOperator::GetSessionIdentifier() const
{
  return (CATULONG32 ) Debog.SessionId;
}


//-------------------------------------------------------------------------------------------------------------
//  GetOperatorId
//-------------------------------------------------------------------------------------------------------------
INLINE const CATString * CATExtGeoOperator::_GetOperatorId()
{
  return  _OperatorId ? _OperatorId : GetOperatorId();
}


//-------------------------------------------------------------------------------------------------------------
//  GetResultStatus
//-------------------------------------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::GetResultStatus( short & ioValidation, short & ioModifiable ) const
{
  ioValidation =  Debog.InvalidResult ? 0 : 1;
  ioModifiable =  Debog.FrozenResult  ? 0 : 1;
}

//-------------------------------------------------------------------------------------------------------------
//  SetResultStatus
//-------------------------------------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::SetResultStatus( const short iValidation, const short iModifiable )
{
  Debog.InvalidResult = iValidation ? 0 : 1;
  Debog.FrozenResult  = iModifiable ? 0 : 1;
}


//-------------------------------------------------------------------------------------------------------------
//  GetNumberOfReplay
//-------------------------------------------------------------------------------------------------------------
INLINE short CATExtGeoOperator::GetNumberOfReplay() const
{
  return (short) Debog.NumberOfReplay;
}

//-------------------------------------------------------------------------------------------------------------
//  SetWarningMode
//-------------------------------------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::SetWarningMode(CATCGMWarning iMode )
{
  switch ( iMode )
  {
    case  Warning_Off     : Debog.WarningMode = 0;                                break;
    case  Warning_On      : Debog.WarningMode = 1;                                break;
    case  Warning_Advanced: Debog.WarningMode = 2; Debog.WarningModeAdvanced = 0; break;
    default               : CATThrowForNullPointer(); // New Value
  }
}

//-------------------------------------------------------------------------------------------------------------
//  SetWarningMode
//-------------------------------------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::AddWarningAdvancedMode(CATCGMWarningAdvanced iMode )
{
  if (Debog.WarningMode == 2)
    Debog.WarningModeAdvanced = (CATCGMWarningAdvanced)((CATCGMWarningAdvanced)Debog.WarningModeAdvanced | iMode);
}

//------------------------------------------------------------------------------
// GetGMOperator
//------------------------------------------------------------------------------
INLINE CATCGMOperator* CATExtGeoOperator::GetGMOperator() const
{
  return _Operateur;
}


//------------------------------------------------------------------------------
// RunIsDone
//------------------------------------------------------------------------------

INLINE CATBoolean CATExtGeoOperator::IsRunDone()
{
 return Debog.IsRunDone  ? TRUE : FALSE;
}

//------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::SetRunIsDone(CATBoolean iIsRunDone)
{
 Debog.IsRunDone =  iIsRunDone ? TRUE : FALSE;
}


//------------------------------------------------------------------------------
// Denying CompositeManagement
//------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::DenyCompositeManagement(CATBoolean iDeny)
{
 Debog.DenyingCompositeManagement =  iDeny ? 1 : 0;
}


//------------------------------------------------------
// Statut CGMReplay pendant le Replay()
//------------------------------------------------------
INLINE CATExtCGMReplay *  CATExtGeoOperator::UnderControlOfLoadedReplay() const
{
 return Debog._UnderControlOfLoadedReplay; 
}

//------------------------------------------------------
// Statut CGMReplay pendant le Run() / Record
//------------------------------------------------------
INLINE void CATExtGeoOperator::SetCGMReplayIsRecording(CATBoolean iIsRecording)
{
 Debog.IsRecording =  iIsRecording ? 1 : 0;
}

//------------------------------------------------------
INLINE CATBoolean CATExtGeoOperator::CGMReplayIsRecording() const
{
 return Debog.IsRecording  ? TRUE : FALSE; 
}

//------------------------------------------------------
INLINE void CATExtGeoOperator::SetCGMReplayIsPlaying(CATBoolean iIsPlaying, CATCGMReplayLiveAttrInitMode iLiveAttrInitMode)
{
  Debog.IsPlaying = iIsPlaying ? 1 : 0;
  Debog.LiveInit  = iIsPlaying ? (signed int)iLiveAttrInitMode :  (signed int)CATCGMReplayLiveAttrInit_None;
}

//----------------------------------------------------------------------------------
INLINE CATBoolean CATExtGeoOperator::CGMReplayIsPlaying(CATCGMReplayLiveAttrInitMode *opLiveAttrInitMode) const
{
  if (opLiveAttrInitMode != NULL)
    *opLiveAttrInitMode = (CATCGMReplayLiveAttrInitMode)Debog.LiveInit;
  return Debog.IsPlaying  ? TRUE : FALSE; 
}

//----------------------------------------------------------------------------------
INLINE CATBoolean  CATExtGeoOperator::IsUnderMultipleRunRecord()  
{
  return ( Debog.IsMultipleRun && Debog.UnderMultipleRunRecord )  ? TRUE : FALSE; 
}

//----------------------------------------------------------------------------------
INLINE void        CATExtGeoOperator::ResetMultipleRun() 
{
  Debog.UnderMultipleRunRecord = 0; 
}

//----------------------------------------------------------------------------------
INLINE void        CATExtGeoOperator::SetMultipleRun() 
{
  Debog.IsMultipleRun = 1; 
}

 
//----------------------------------------------------------------------------------
// HistoryKey  :   Has  ; Reset 
//----------------------------------------------------------------------------------

CATBoolean  CATExtGeoOperator::HasHistoryKey()
{
  return Debog._WithHistoryKey  ? TRUE : FALSE;
}

//------------------------------------------------------
void       CATExtGeoOperator::ResetHistoryKey()
{
  Debog._WithHistoryKey = 0;
}

//------------------------------------------------------
void       CATExtGeoOperator::SetHistoryKey()
{
  Debog._WithHistoryKey = 1;
}


//----------------------------------------------------------------------------------
// GetFactory
//----------------------------------------------------------------------------------
INLINE CATGeoFactory* CATExtGeoOperator::GetFactory() const
{
  return _Factory;
}

//----------------------------------------------------------------------------------
// SetInputFactory
//----------------------------------------------------------------------------------
INLINE void CATExtGeoOperator::SetInputFactory(CATGeoFactory *piGeoFactory)
{
   if (!_InputFactory)
   {
      _InputFactory = piGeoFactory;
   }
}


//----------------------------------------------------------------------------------
/** 
*  Trigger : simulation of interruption thrown.
*/
void       CATExtGeoOperator::ActivateTrigger(CATLONG32 iTrigger, const char *  iStaticConstLabel, CATBoolean ToDeleteConstLabel)
{ 
  Debog._Trigger                  = iTrigger; 
  Debog._TriggerStaticConstLabel  = iStaticConstLabel;
  Debog.TriggerToDeleteConstLabel = ToDeleteConstLabel ? 1 : 0;
}

//----------------------------------------------------------------------------------
CATBoolean  CATExtGeoOperator::HasTrigger()
{
  if ( ! Debog._Trigger )  return FALSE;
  return TRUE;
}

//----------------------------------------------------------------------------------
CATLONG32  CATExtGeoOperator::GetTrigger(const char *  iStaticConstLabel)
{
  if ( ! Debog._Trigger )
    return 0;

  // Identity des valeurs de Const char Label
  if ( iStaticConstLabel && (*iStaticConstLabel != '\0') )
  {
    if ( ! Debog._TriggerStaticConstLabel )
      return 0;

    int idx = 0; 
    for ( ;Debog._TriggerStaticConstLabel[idx] && (Debog._TriggerStaticConstLabel[idx] == iStaticConstLabel[idx]); idx++ )
      ;

    if (  Debog._TriggerStaticConstLabel[idx] || iStaticConstLabel[idx] )
      return 0;
  }
  else
  {
    if ( Debog._TriggerStaticConstLabel && (*(Debog._TriggerStaticConstLabel) != '\0') )
      return 0;
  }

 // Valid
  return Debog._Trigger; 
}

//----------------------------------------------------------------------------------
void       CATExtGeoOperator::ResetTrigger()
{ 
  Debog._Trigger = 0; 
  if ( Debog._TriggerStaticConstLabel )
  { if ( Debog.TriggerToDeleteConstLabel ) { delete [] (char *)Debog._TriggerStaticConstLabel; }  Debog._TriggerStaticConstLabel = 0;  }
  Debog.TriggerToDeleteConstLabel = 0;
}


#endif
