/* -*-c++-*- */
#ifndef CATExtCGMReplay_h
#define CATExtCGMReplay_h
//=============================================================================
//
//  COPYRIGHT DASSAULT SYSTEMES 1999
//
//      Internal persistency management of a CATGeoFactory's Operator
//
//=============================================================================
// 07/06/22 NLD _ArrayToDelete split into _CrvParamArrayToDelete and _CGMObjectArrayToDelete
//=============================================================================
#include "CATGeometricObjects.h"
#include "CATICGMStreamFactory.h"
#include "CATBaseUnknown.h"

#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATListPV.h"
#include "CATListOfCATUnicodeString.h"

#include "CATListOfCATGeoFactories.h"
#include "CATListOfCATCGMJournals.h"

#include "CATCGMOperator.h"
#include "CATCrvLimits.h"
#include "CATErrorDefs.h"
#include "CATCGMReplayLiveAttrInitMode.h"
#include "CATMathInline.h"
#include "CATCGMStreamVersion.h"
#include "CATListOfCATCGMIndex.h"
 
#include "CATHashDico.h"

class CATMathStream;
class CATCGMStream;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCGMJournal;
class CATError;
class CATCGMOutput;
class CATTopologicalOperator;
class CATCGMStreamImpl;
class CATGeoDebug;
class CATCGMIndex;
struct CATCGMVoBTool;
class CATechAttribute;

class CATCGMOperator;
class CATError;
class CATechSet;
class CATechAttribute;
class CATPGMDRepBehavior;
class CATCGMUnknown;


typedef enum
{
  CATExtCGMReplay_ValidateOutputOK              = 0,
  CATExtCGMReplay_ValidateOutputKOBodiesMapping ,
  CATExtCGMReplay_ValidateOutputKOJournalMapping,
  CATExtCGMReplay_ValidateOutputKO              ,
  CATExtCGMReplay_ValidateOutputKORunOkSavedKo
}
  CATExtCGMReplay_ValidateOutputDiagType;


/**
*  PCS Asynchronous (Replay) Control Steps (Validity and Stability) under  CheckInput CheckOutput ValidateOutput
*/
#define CATExtCGMReplayAsynchronous_CheckInput_Factory               0x0000000000000001ULL
#define CATExtCGMReplayAsynchronous_CheckOutput_Journal              0x0000000000000002ULL
#define CATExtCGMReplayAsynchronous_CheckOutput_LiveBody             0x0000000000000004ULL
#define CATExtCGMReplayAsynchronous_CheckOutput_Factory              0x0000000000000008ULL

#define CATExtCGMReplayAsynchronous_CheckOutput_CellTrackerData      0x0000000000000010ULL
#define CATExtCGMReplayAsynchronous_CheckOutput_Extension            0x0000000000000020ULL
#define CATExtCGMReplayAsynchronous_CheckOutput_Persistency          0x0000000000000040ULL
#define CATExtCGMReplayAsynchronous_ValidateOutput_BodiesMapping     0x0000000000000080ULL

#define CATExtCGMReplayAsynchronous_ValidateOutput_JournalMapping    0x0000000000000100ULL
#define CATExtCGMReplayAsynchronous_ValidateOutput_RecyclingRate     0x0000000000000200ULL
#define CATExtCGMReplayAsynchronous_ValidateOutput_CheckFastUpdate   0x0000000000000400ULL
#define CATExtCGMReplayAsynchronous_ValidateOutput_CheckVoB          0x0000000000000800ULL

#define CATExtCGMReplayAsynchronous_ValidateOutput_CellTrackerData   0x0000000000001000ULL
 
 
//---------------------------------------------------------------------------
// Utility class for mono or multi-run sharp cumulated measures
// (measure taken before and after each run) NLD230221
//---------------------------------------------------------------------------
class ExportedByCATGeometricObjects CATExtCGMReplayRunMeasure
{
     public:
     virtual void Start() = 0;
     virtual void End  () = 0;
};
 

/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
class ExportedByCATGeometricObjects CATExtCGMReplay : public CATICGMStreamFactory
{
  CATDeclareClass;

public:


  //---------------------------------------------------------------------------
  //  Save Load Run Close
  //---------------------------------------------------------------------------


  /**
    * Save
    */
         HRESULT           CATSaveCGMReplay(          CATCGMOperator       *  iOperator          ,
                                                      CATCGMStream          & iStr               ,
                                                      CATCGMStreamVersion     iForceVersion      = CatCGMStream_UnknownVersion ,
                                                      short                   iHowMany           = 1,
                                                      CATBoolean              iDedicatedToReplay = FALSE,
                                                      CATechAttribute      *  iRFUOptionsForCompositeManagement = NULL );



  /**
   * Load
   */
  static CATExtCGMReplay * CATLoadCGMReplay          (CATCGMStream          & iStr          ,
                                                      CATechAttribute      *  iRFUOptionsForCompositeManagement = NULL );
 

  /**
   * Run   For ODT Commodities ..
   */
          HRESULT          RunReplay                 (CATCGMOutput              & os           ,
                                                      CATBoolean                  iOnlyOneStep ,
                                                      CATExtCGMReplayRunMeasure*  iMeasureTool , // NLD230221
                                                      int                       & rc           ,
                                                      CATErrorId               *  oErrorId     );

          HRESULT          Run                       (CATCGMOutput              & os           ,
                                                      int                       & rc           ,
                                                      CATErrorId               *  oErrorId     = 0,
                                                      CATBoolean                  iOnlyOneStep = FALSE);


  /**
    * Close
    */
  virtual HRESULT          Close                     ();



  //---------------------------------------------------------------------------
  //  Commoditities
  //---------------------------------------------------------------------------

  /**
    * CATCGMReplayToOperator
    */
  static void              CATCGMReplayToOperatorName(     CATCGMStream            & iStr         ,
                                                           CATUnicodeString        & oOperatorName);

  /**
    * GetCATExtCGMReplay
    */
  static CATExtCGMReplay * GetCATExtCGMReplay        (     CATCGMOperator         *  iOperator);

 

  /**
    * DuplicateCGMOperator
    */
  static CATExtCGMReplay * DuplicateCGMOperator     (      CATCGMOperator         *  iOperator);

  /**
    * Rebind on Load
    */
  static CATExtCGMReplay  * CATRebindOnLoadCGMReplay(      CATGeoFactory          *  iFactory ,
                                                           CATCGMStream            & iStr     );



  //----------------------------------------------------------------------------------------
  //  PCS control over Asynchronous Steps     
  //     Steps are enumerated 
  //           by String   inside   CATCGMDb_Common.h   CATCGMDb_CGMReplayExtended.h 
  //           by Flags    here by  CATExtCGMReplayAsynchronous_XXXX
  //     Services are explicitly Controled  (filtering) Query  Reporting
  //----------------------------------------------------------------------------------------

  // External (enhanced Replay Engine or customized applications ..)

         void               AsynchronousFilter      (const CATULONG64           iCATExtCGMReplayAsynchronous);

         void               Asynchronous_ToFilter   (const CATUnicodeString   & iStep      );

  static CATULONG64         CATCGMReplay_filtering  ();


  // Internal Filter (Operator and Replay integration)

         int            Asynchronous_AvailableStep(const CATUnicodeString   & iStep      ,
                                                         CATCGMOutput       & osDump     );

  static void               AsynchronousLOG       (const CATUnicodeString   & iKeyWord   ,
                                                   const CATUnicodeString   & iDirectory ,
                                                   const CATUnicodeString   & iOperatorId,
                                                   const CATUnicodeString   & iMessage   ,
                                                   const CATUnicodeString   & HeadODT    )  ;

  //---------------------------------------------------------------------------
  //  GetFeedbackSteps 
  //    enhanced diagnostic on asynchronous Replay 
  //---------------------------------------------------------------------------

  INLINE CATechAttribute  * GetFeedbackSteps      ();
 

  //---------------------------------------------------------------------------
  //  GetCATCGMReplay : Getting GUI context indicator
  //---------------------------------------------------------------------------
  INLINE  CATBaseUnknown  * GetCATCGMReplay       ();
          void              SetCATCGMReplay       (      CATBaseUnknown    *  iReplay );
 

  //---------------------------------------------------------------------------
  // CATICGMStreamable
  //---------------------------------------------------------------------------

  /**
   *  Naming (Default Basic CATExtCGMReplay implementation)
   */
  virtual const char* const GetOperatorString     (      void *  object    ) ;

   /**
   *  TO OVERLOAD (1) : Naming to physical implementation
   */
  virtual void              GetSharedlibOfOperator(const char *  operatorId,
                                                         char *& sharedlib ) = 0 ;

  /**
   *   TO OVERLOAD (2) : For Avalaible Operator Identificators
   */
  virtual HRESULT           GetAvailableOperators(CATListOfCATString &OpIds)= 0 ;


  /**
   *  Write Operator
   */
          HRESULT           WriteOperator        (void                 * object        ,
                                                  CATMathStream        & Str           ,
                                                  CATCGMStreamVersion    iForceVersion = CatCGMStream_UnknownVersion ,
                                                  short                  iHowMany      = 1)  ;


  /**
    * Read Operator
    */
          HRESULT           ReadOperator         (CATMathStream        & Str           ,
                                                  void                *& object        ) ;


   /**
   *  GetCGMExtension
   */
  INLINE CATExtCGMReplay  * GetCGMExtension      ()
  {
      return this;
  } ;
  


  //---------------------------------------------------------------------------
  // .... CATCGMOperator->WriteInput(CATMathStream&  ioStream)
  //---------------------------------------------------------------------------
  
  /**
   * Makes the operator.<br> CATOprStreamFactory overload
   * By default, this method calls @href #GetSharedlibOfOperator and it calls the function
   * <tt>"CATLoad" + OperatorId</tt> in the shared library whose name was returned.<br>
   * You can over override this method in order to create the operator with another mean (ObjectModeler...).
   */
  virtual CATCGMOperator                    * MakeOperator        (const char         * iOperatorId     ,
                                                                         CATCGMStream & iStr            ,
                                                                         short          iLevelOfRuntime ,
                                                                         short          iVersionOfStream);

  //---------------------------------------------------------------------------
  // ....
  //---------------------------------------------------------------------------
 
   /**
    * Read / Write
    */

  virtual HRESULT                             Write               (void         * object  ,
                                                                   CATMathStream& Str     ) ;

  virtual HRESULT                             Read                (CATMathStream& Str     ,
                                                                   void         * &object ) ;


  // NLD180105 transitoire pour correction de l'identificateur en souplesse
  //#ifndef GetAvalaibleOperators
  //#define GetAvalaibleOperators GetAvailableOperators
  //#endif

  /**
   *  TO OVERLOAD (3) : If a pure  factory of geometrical operators
   */
  virtual CATBoolean                          IsTopological();


  /**
  * GetShortName  
  */
  virtual HRESULT                             GetShortName(CATUnicodeString & oValue) const  ;

          void                                SetShortName(CATCGMOperator   * iOperator);
 

  //===================================================================================
  // Meta description for Recording Replaying
  //    for common Replay-PlayBack-Phoenix integration
  //       same descriptive infrastructure available
  //       with CGMReplay as Proof Of Concept (2012Spring)
  //===================================================================================

  /**
  * GetRecording (generate if necessary (and before Run())
  */
  virtual CATechAttribute                   * GetRecording(CATechSet      **  iContext = NULL) const   ;

  /**
  * SetRecording 
  */
  virtual HRESULT                             SetRecording(CATechAttribute *  iReplaying,
                                                           CATechSet       *  iContext  )   ;

  /**
  * GetReplaying 
  */
  virtual CATechAttribute                   * GetReplaying(CATechSet      **  iContext  = NULL) const   ;

  /**
  * SetReplaying 
  */
  virtual HRESULT                             SetReplaying(CATechAttribute *  iReplaying,
                                                           CATechSet       *  iContext  )   ;


  //===================================================================================
  //  OTHER 
  //===================================================================================


  /**
   *  For ODT Commodities ..
   */
          CATCGMOperator::CATCheckDiagnostic  CheckInput(CATCGMOutput &os );

  /**
   *  For ODT Commodities ..
   */
          CATCGMOperator::CATCheckDiagnostic  CheckOutput(CATCGMOutput &os );

  /**
   *  For ODT Commodities ..
   */
          HRESULT                             ValidateOutput(CATCGMOutput & os,
                                                             CATExtCGMReplay_ValidateOutputDiagType* oDiag = 0);




  /**
   *  For ODT Commodities ..
   */
          void                                Dump( CATCGMOutput& os ) ;

  /**
   *  For ODT Commodities ..
   */
          void                                DumpResult( CATCGMOutput& os ) ;

  /**
   *  For ODT Commodities ..
   */
          void                                DumpReference( CATCGMOutput& os ) ;





  /**
   *  For very specific ODT Replay commodity
   */
          HRESULT                             GetReplayDefinition  (CATCGMOperator      *& ioOperator    ,
                                                                    CATGeoFactory       *& ioInputFactory);

  /**
   *  For very specific ODT Replay commodity
   */
          HRESULT                             GetValidateDefinition (CATBoolean          & ioHasReference,
                                                                     CATTopCheckJournal *& iEquivalent   );



  /**
   *  INTERNAL ONLY : For memory management at Replay (with extra CATGeoFactory)
   */
          void                                AddFactoryToClose     (CATGeoFactory     *  iFactory);

  /**
  *  INTERNAL ONLY : For memory management at Replay (with extra CATGeoFactory)
  */
          void                                AddFactoryToNotClose  (CATGeoFactory     *  iFactory);

  /**
   *  INTERNAL ONLY : For memory management at Replay (with extra CATGeoFactory)
   */
          void                                AddCATCGMIndexToClose (CATCGMIndex       *  iIndex);


  /**
   *  INTERNAL ONLY : For memory management at Replay (with extra CATCGMJournal)
   */
          void                                AddJournalToDelete    (CATCGMJournal     *  iJournal);

  /**
   *  INTERNAL ONLY : For memory management at Replay (with extra CATSoftwareConfiguration)
   */
          void                                AddSoftwareConfigToRelease(CATSoftwareConfiguration *  iSoftConfig);

  /**
   *  INTERNAL ONLY : For memory management at Replay (with extra CATSoftwareConfiguration)
   */

          void                                AddToolsToDelete(CATCGMVirtual  *  iTool);
          void                                AddToolsToDelete(CATBaseUnknown *  iTObj);
          void                                AddToolsToDelete(CATCrvLimits   *  iTool); // expects an array of CATCrvLimits; LD030522
          void                                AddToolsToDelete(double         *  iTool);
          void                                AddToolsToDelete(CATCGMUnknown  *  iTObj);
  // pkc 26/09/2005 contre MLK
          void                                AddToolsToDelete(CATLONG32      *  iTool);
          void                                AddArrayToDelete(CATCrvParam    *  iToolCrv);
  // pkc 06/10/2015 contre MLK
          void                                AddArrayToDelete(CATICGMObject **  iArray);
  
  /**
  *  INTERNAL ONLY : Set/Get the CGMReplay "document" that contains this
  *                  (known only by CATGem)
  */
          void                                SetCGMReplayDoc (CATBaseUnknown *  iCGMReplayDoc); // input = CATCGMReplay
          CATBaseUnknown                    * GetCGMReplayDoc ();                                // rend un CATCGMReplay
 
  /**
  * @nodoc @nocgmitf
  */
          short                               GetOpenConfig();

  /**
  * @nodoc @nocgmitf
  */
          unsigned char                       GetOpenConfigInChar();
   
  /**
  * @nodoc @nocgmitf
  */
          void                                SetOpenConfig(short iOpenConfig);

  /**
  * @nodoc @nocgmitf
  */
          CATBoolean                          IsLevelVersActivated(char *piLevelVers);

  /**
  * @nodoc @nocgmitf
  */
          char                              * GetInfLevelLimit();
  
  /**
  * @nodoc @nocgmitf
  */
          char                              * GetSupLevelLimit();
  
  /**
  * @nodoc @nocgmitf
  */
          char                              * GetLevelVers();
  
  /**
  * @nodoc @nocgmitf
  */
          char                              * GetFreeText();

  //---------------------------------------------------------------------------
  // Gestion de la configuration
  //---------------------------------------------------------------------------
  static void                                 StreamConfig       (CATSoftwareConfiguration *  iConfig,
                                                                  CATCGMStream              & Str    );

  //---------------------------------------------------------------------------
  // Utilites to allow Math Dirty CGMVersioning to work in:
  //    CheckInput / CheckOutput / ValidateOutput / DumpInput / DumpOutput
  //---------------------------------------------------------------------------

         void                                 GetConfigMailData  (int                      & oMailIdent,
                                                                  void                    *& oMailFrom ,
                                                                  void                    *& oMailTo   ) const;
         void                                 SendConfigMail     ()                                      const;
         void                                 UnSendConfigMail   ()                                      const;

  //---------------------------------------------------------------------------
  // Regeneration configuration
  // Si ce service est utilise sous le contexte d'un CATCGMReplay
  //   alors la Config alloue est automatiquement enregistree en nettoyage
  //   par le service AddSoftwareConfigToRelease
  //---------------------------------------------------------------------------
  static  void                                UnStreamConfig     (CATCGMStream             & Str     ,
                                                                  CATSoftwareConfiguration * &iConfig);

  static  CATTopologicalOperator            * GetLastTopologicalOperatorLoadedFromReplay() ;

  // ne pas enlever :
  //   rien de special par rapport au CATBaseUnknown
  //   mais permet de mettre un point d'arret pour traquer les AddRef en trop
  virtual ULONG                     __stdcall AddRef             ();
  virtual ULONG                     __stdcall Release            ();

  //
  INLINE CATGeoFactory                      * GetInFactory       ()
  {
     return _InFactory;
  }

  INLINE void                                 SetInFactory       (CATGeoFactory    *  pInFactory)
  {
     _InFactory = pInFactory;
  }

  INLINE void                                 AllowDistinctInput_CreationAndLoadedFactory()
  {
     _AllowDistinctInput_CreationAndLoadedFactory = TRUE;
  }

   
/*
 * For integration of global ODT Treatment in CATCGMReplay 
 */
    
  /** ODT extension to CATCGMreplay : To be Defined */
  virtual void                                DumpDefinition          (CATCGMOperator   *  iOperator,
                                                                       CATCGMOutput      & os       );


  /** ODT extension to CATCGMreplay : To be Defined */
  virtual void                                DumpResultAfterRun      (CATCGMOperator   *  iOperator,
                                                                       CATCGMOutput      & os       );



  /** ODT extension to CATCGMreplay : To be Defined */
  virtual CATCGMOperator::CATCheckDiagnostic  CheckInputBeforeRun     (CATCGMOperator   *  iOperator,
                                                                       CATCGMOutput      & os       );


  /** ODT extension to CATCGMreplay : To be Defined */
  virtual CATCGMOperator::CATCheckDiagnostic  CheckOutputAfterRun     (CATCGMOperator   *  iOperator,
                                                                       CATCGMOutput      & os       );




  /** ODT extension to CATCGMreplay : To be Defined */
  virtual void                               DumpReference            (CATCGMOperator  *  iOperator,
                                                                       CATCGMOutput     & os       );

  /** ODT extension to CATCGMreplay : To be Defined */
  virtual CATBoolean                         ValidateReference        (CATCGMOperator  *  iOperator,
                                                                       CATCGMOutput     & os       );

 

  INLINE CATCGMOperator                    * GetCGMOperator           ()
  {
     return _CurOp;
  } ;
         void                                GetSummaryMessage        (CATUnicodeString & SummaryMessage);

  //=============================================================================
  // 09/03/09 KY1 Integration CATCellTrackingData
  //=============================================================================
  INLINE CATCGMVirtual                    * GetCATCellTrackingData    ()
  {
     return _CATCellTrackingData;
  } ;

         void                               SetCATCellTrackingData    (CATCGMVirtual *iCellTrackingData);
  //
  INLINE CATBoolean                         GetEnableCellTracker      ()
  {
     return _EnableCellTracker;
  } ;

         void                               SetEnableCellTracker      (CATBoolean iEnableCellTracker);

  //=============================================================================
  // 22/06/11 JHN Integration VoBTool
  //=============================================================================
         CATCGMVoBTool                    * GetAndNullifyCATCGMVoBTool() ;
         void                               SetCATCGMVoBTool          (CATCGMVoBTool *iVoB);
         CATBoolean                         IsVoBSaved                ();
         void                               SetVoBSaved               ();

  //=============================================================================
  // 16/07/13 YL3 Integration Warning mode
  //=============================================================================
         void                               SetOperatorTransactionMode(CATBoolean iTransactionMode);
         CATBoolean                         GetOperatorTransactionMode();
         void                               SetWarningMode            (CATCGMWarning iWarningMode);
         CATCGMWarning                      GetWarningMode            ();

  //=============================================================================
  // 07/02/13 LD2 Integration Failsafe
  //=============================================================================
         void                               SetFailsafeMode           (CATBoolean iFailsafeMode);
         CATBoolean                         GetFailsafeMode           ();

  //=============================================================================
  // 08/02/2013  QF2 Integration DRepBehavior
  //=============================================================================
         CATPGMDRepBehavior               * GetDRepBehaviorPointer    ();
         void                               SetDRepBehaviorPointer    (CATPGMDRepBehavior *iDRepBehaviorPtr);

  // WQO Nov 10 Pour moteur FourRunForOneFast
  INLINE CATBoolean                         GetRefError               ()
  {
     return _RefError;
  } ;

  //=============================================================================
  // 18/11/10 KY1 : Added To test if the Scenario is to be squeezed or not
  //=============================================================================
         CATBoolean                         IsCGMReplayToFilter       ();

  /** 
  *  Interrupt History  (saved with refential).
  */
  INLINE CATLONG32                          GetInterruptHistory       ();

  /** 
  *  Warning Referential.
  */
  INLINE CATBoolean                         GetRefWarningResult       ()
  {
     return _RefWarningResult;
  } ;


  //---------------------------------------------------------------------------
  // dedicated PlayBack
  //---------------------------------------------------------------------------
  /**
   *  Composite Write Operator
   */
         HRESULT                            CompositeWriteAfter(CATCGMStream       & iStr         ,
                                                                CATCGMStreamImpl   * cgmStreamImpl,
                                                                CATCGMOperator     * iOperator    ,
                                                                CATError           * iErr         ,
                                                                CATBoolean         & TheGoodWriteAfter )  ;


   /**
   * Composite Read Operator
   */
         HRESULT                            CompositeReadAfter(CATCGMStream          & iStr                    ,
                                                               CATCGMStreamImpl      * pCGMImpl                ,
                                                               CATCGMOperator        * iOperator               ,
                                                               CATBoolean              iWithStochasticAfterRun ,
                                                               CATBoolean              iWithReferenceAfterRun )  ;


  //---------------------------------------------------------------------------
   //  ExcludeAnomaly  Save && Load
   //---------------------------------------------------------------------------

  static int                                Asynchronous_Add(const CATUnicodeString         iKeyWord       ,
                                                                   CATCGMOperator         * iOperator      ,
                                                                   CATCGMOutput           & osDump         );

         HRESULT                            CATCGMReplay_Run_Throw(CATBoolean               ExpectInterrupt,
                                                                   CATError               * error          ,
                                                                   CATCGMOutput           & osDump         ) ;


   //-----------------------------------------------------------------------------
   // Ajout des differentes Factory associees a la Gestion du CATCGMReplay
   // Set et get du "document" CATCGMReplay associe a this
   //-----------------------------------------------------------------------------
   INLINE  int                               GetVersionOfStream()
   {
      return _VersionOfStream;
   }

   /** @nodoc @nocgmitf */
   INLINE  int                               GetUnStreamHeaderLevel()
   {
      return _UnStreamHeaderLevel;
   }

   /** @nodoc @nocgmitf */
   INLINE  int                               GetStreamHeaderLevel()
   {
      return _StreamHeaderLevel;
   }

   /** @nodoc @nocgmitf */
   static CATExtCGMReplay                   * IsRecordableOperator(CATCGMOperator            *  iOperator      ,
                                                 short                      & LevelOfRuntime ,
                                                 short                      & VersionOfStream);

   //---------------------------------------------------------------------------
   // To Transfer Data unstreamed from CGMReplay Header to the Factory :
   //    - Emulate setting done on Factory by Applications (CATIA, CGMComponent, ...etc)
   //---------------------------------------------------------------------------
   /** @nodoc @nocgmitf */
          void                               TransferDataToFactory(CATGeoFactory            *  piGeoFactory);

   /** @nodoc @nocgmitf */
          void                               ForceSupLevelLimit   (CATSoftwareConfiguration *  piSoftConfig);

protected:

   //---------------------------------------------------------------------------
  // Ctor-Dtor
  //---------------------------------------------------------------------------
                                             CATExtCGMReplay();
                                            ~CATExtCGMReplay();

          void                               _Close();





private:

  static  void                               DumpOperator             (CATCGMOperator *  iOperator,
                                                                       CATCGMOutput    & os       );

  static  void                               DumpOutputOperator       (CATCGMOperator *  iOperator,
                                                                       CATCGMOutput    & os       );

  static  void                               WriteInputOperator       (CATCGMOperator *  iOperator,
                                                                       CATCGMStream    & Str      );

  static  void                               WriteTopOutputOperator   (CATCGMOperator *  iOperator,
                                                                       CATCGMStream    & Str      );

  static  CATTopCheckJournal               * ReadTopOutputOperator    (CATCGMOperator *  iOperator,
                                                                       CATCGMStream    & Str      );

  static  CATBoolean                         ValidateTopOutputOperator(CATCGMOperator *  iOperator,
                                                                       CATTopCheckJournal* iEquivalent,
                                                                       CATCGMOutput    & os);

  static  void                               DumpTopOutputOperator    (CATCGMOperator *  iOperator,
                                                                       CATTopCheckJournal* iEquivalent,
                                                                       CATCGMOutput    & os);

  static  CATCGMOperator::CATCheckDiagnostic CheckInputOperator       (CATCGMOperator *  iOperator,
                                                                       CATCGMOutput    & os       );

  static  CATCGMOperator::CATCheckDiagnostic CheckOutputOperator      (CATCGMOperator *  iOperator,
                                                                       CATCGMOutput    & os       );

  static  void                               WriteOutputOperator      (CATCGMOperator *  iOperator,
                                                                       CATCGMStream    & ioStream);

  static  void                               DumpOutputOperator       (CATCGMOperator *  iOperator     ,
                                                                       CATCGMStream    & ioStream      ,
                                                                       CATCGMOutput    & os            ,
                                                                       int               VersionNumber = 1);

  static  CATBoolean                         ValidateOutputOperator   (CATCGMOperator *  iOperator     ,
                                                                       CATCGMStream    & ioStream      ,
                                                                       CATCGMOutput    & os            ,
                                                                       int               VersionNumber = 1);

    /**
   *  For ODT Commodities ..
   */
          void                               DumpError                (const char        Context[]     ,
                                                                       CATError       *  err           ,
                                                                       CATCGMOutput    & os            );

  /**
   *  For ODT Commodities ..
   */
          HRESULT                            GetCopyOfOuput            (CATCGMStream  & ioStream      );




          void                               WriteBeforeRun            (CATCGMOperator * iOperator,
                                                                        CATCGMStream   & ioStream);

          void                               ReadBeforeRun             (CATCGMOperator * iOperator  ,
                                                                        CATCGMStream   & ioStream   ,
                                                                        short            HeaderLevel,
                                                                        CATULONG32       CGMBuildVersionRead );

          void                               ReadAfterRun              (CATCGMStream  & ioStream               ,
                                                                        CATBoolean      iWithStochasticAfterRun,
                                                                        CATBoolean      iWithReferenceAfterRun );


  /**
   *  Write Operator
   */
          void                               WriteAfter                (CATCGMOperator * iOperator,
                                                                        CATCGMStream   & stream   ,
                                                                        CATError       * iErr     = NULL)  ;

  //---------------------------------------------------------------------------
  // StochasticAfterRun  / ReferenceAfterRun 
  //---------------------------------------------------------------------------

          void                               WriteStochasticAfterRun   (CATCGMOperator *iOperator, CATCGMStream & ioStream, CATError *iErr);

          void                               OldWriteStochasticAfterRun(CATCGMOperator *iOperator, CATCGMStream & ioStream, CATError *iErr);

          void                               ReadStochasticAfterRun    (CATCGMOperator *iOperator, CATCGMStream& ioStream);

          void                               OldReadStochasticAfterRun (CATCGMOperator *iOperator, CATCGMStream& ioStream);


          void                               WriteReferenceAfterRun    (CATCGMOperator *iOperator, CATCGMStream & ioStream);

          void                               ReadReferenceAfterRun     (CATCGMOperator *iOperator, CATCGMStream& ioStream);

 
          HRESULT                            Asynchronous_Save         (CATCGMOperator       * iOperator,
                                                                        CATCGMStream         & iStr,
                                                                        CATCGMStreamVersion    iForceVersion   = CatCGMStream_UnknownVersion ,
                                                                        short                  iHowMany         = 1,
                                                                        CATBoolean             iDedicatedToReplay = FALSE,
                                                                        CATechAttribute      * iRFUOptionsForCompositeManagement = NULL );
 
          HRESULT                            Asynchronous_Load       (  CATCGMStream         & iStr  );



          void                               CompositeError         (  CATCGMOperator       * iOperator,
                                                                       CATError             * iErr     ,
                                                                       CATechSet            * iCompositeManagement,
                                                                       CATechAttribute      * iBootAttribute);


   // XXXX_Global

          int                                CheckInput_Global                (CATCGMOutput & osDump);
          int                                CheckOutput_Global               (CATCGMOutput & osDump);
          int                                ValidateOutput_Global            (CATCGMOutput & osDump);

          int                                _ValidateOutput_ValidateTopOutput(CATCGMOutput & osDump);
          int                                _ValidateOutput_ValidateOutput   (CATCGMOutput & osDump);
          int                                _ValidateOutput_ErrorReferential (CATCGMOutput & osDump);
          int                                _ValidateOutput_Global           (CATCGMOutput & osDump);




  static  int                               _Asynchronous_Add           (const CATUnicodeString   iKeyWord ,
                                                                               CATCGMOperator  *  iOperator,
                                                                               CATCGMOutput     & osDump   );
    
 
  /**
   *  Uniquement pour nettoyage des donnees generees au Read
   */
  CATCGMOperator              * _CurOp;                // associated loaded operator (replay dedicated step)
   
  CATHashDico                   _Asynchronous;         // Gestion delayed asynchronous steps (associated to default textual zip step=level )
                                                       //  Step -> HashDico (Field=Value)  *  ,  levelCGM=open=* 

  CATCGMOperator              * _RefValidate;          // associated referential loaded operator (CATTopCheckJournal_

  CATCGMStream                * _RefOutput;            // extracted referential outputs 
  CATBoolean                    _HasBeenRead;          // control flag , validated loaded operator (replay dedicated step)
  CATBoolean                    _HasReferenceResult;
  CATBoolean                    _HasBeenClosed;        // control flag, closing only one time

  CATGeoFactory               * _InFactory;            // associated default generative data factory (doublon avec Factory)
  CATBoolean                    _AllowDistinctInput_CreationAndLoadedFactory;

  CATLISTP(CATGeoFactory)       _ToCLose;              // AddFactoryToClose     (replay dedicated step),
  CATLISTP(CATGeoFactory)       _ToNotCLose;           // AddFactoryToNotClose     (replay dedicated step),
  CATLISTP(CATCGMIndex)         _IndexToClose;         // AddCATCGMIndexToClose
  CATLISTP(CATCGMJournal)       _JournalToDelete;      // AddJournalToDelete
  CATListPV                     _ConfigToRelease;      // AddSoftwareConfigToRelease
  CATListPV                     _OperatorToRelease;    // AddToolsToDelete
  CATListPV                     _TabObjToRelease;      // AddToolsToDelete
  CATListPV                     _PointerToRelease;     // AddToolsToDelete
  CATListPV                     _TableToRelease;       // AddToolsToDelete
  CATListPV                     _CGMObjTabToRelease;   // AddToolsToDelete 
  CATListPV                     _TableOfLongToRelease; // AddToolsToDelete
//CATListPV                     _ArrayToDelete;        // AddArrayToDelete
  CATListPV                     _CrvParamArrayToDelete;
  CATListPV                     _CGMObjectArrayToDelete;

  CATBoolean                    _OpenConfig;           //  Cf ReplayEngine (rla)   :  si le level n'est pas actif on joue le CGMReplay 
                                                       //                             en configuration ouverte
                                                       //  0 : Closed Config,
                                                       //  1 : Open Config without Hist,
                                                       //  2 : Open Config as caught from customer scenario (KY1)
//CATBoolean                    _UnstreamedConfigStatus;//  The status of the Unstreamed scenario softconfig :
                                                       //  0 : Closed Config,
                                                       //  1 : Open Config without Hist,
                                                       //  2 : Open Config as caught from customer scenario (KY1)
  char                        * _InfLevelLimit;
  char                        * _SupLevelLimit;
  //rlad
  char                        * _LevelVers;
  //rlaf
  char                        * _FreeText;

  CATBoolean                    _RefError;
  short                         _RefErrorId;
  const char                  * _RefErrorMsgCatalog;
  const char                  * _RefErrorMsgId;

  short                         _ResultErrorId;
  char                        * _ResultErrorMsgCatalog;
  char                        * _ResultErrorMsgId;

  CATUnicodeString              _SummaryMessage; // fin de la ligne Summary dans le fichier .status

  CATLONG32                     _InterruptHistory;
  CATLONG32                     _InterruptCounter;
  char                        * _InterruptHistoryLabel;

  CATBoolean                    _RefWarningResult;

  //=============================================================================
  // 09/03/09 KY1 Integration CATCellTrackingData
  //=============================================================================
  CATCGMVirtual              *  _CATCellTrackingData;
  CATBoolean                    _EnableCellTracker;
  CATCGMVoBTool              *  _VoBTool;
  CATBoolean                    _VoBSaved;
  CATPGMDRepBehavior         *  _DRepBehavior;
  CATBoolean                    _FailsafeMode;

  //=============================================================================
  // 15/07/13 YL3 Integration Warning mode
  //=============================================================================
  CATBoolean                    _OperatorTransactionMode;
  CATCGMWarning                 _WarningMode;

  int                           _VersionOfStream;
  CATBaseUnknown             *  _CGMReplayDoc;

  CATCGMReplayLiveAttrInitMode  _LiveAttrInitMode;

  //=============================================================================
  // Generic Data to manage behavior og the loaded operator
  //=============================================================================
  short                         _CGMComponentInUse;

  //=============================================================================
  // Generic Data to CGMReplay version
  //=============================================================================
  short                         _StreamHeaderLevel;
  short                         _UnStreamHeaderLevel;


  //===================================================================================
  // Meta description for Recording Replaying
  //    for common Replay-PlayBack-Phoenix integration
  //       same descriptive infrastructure available
  //       with CGMReplay as Proof Of Concept (2012Spring) 
  //===================================================================================
  CATUnicodeString              _ShortName;
  CATBoolean                    _ShortNameBoolean;
  CATechSet                  *  _RootSetForReplaying;
  CATechSet                  *  _RootSetForRecording;
  CATechAttribute            *  _RootForReplaying;
  CATechAttribute            *  _RootForRecording;

  CATechSet                  *  _LifeCycleLock;

  //---------------------------------------------------------------------------
  //  GetFeedbackSteps   enhanced diagnostic on asynchronous Replay 
  //---------------------------------------------------------------------------
  CATechAttribute             * _FeedbackSteps;
  friend class CATGeoDebug;


  //---------------------------------------------------------------------------
  // Old CATCGMReplay document GUI integration 
  //---------------------------------------------------------------------------
  CATBaseUnknown   * const      _CATCGMReplay;


  //------------------------------------------------------------
  // Static DATA 
  //------------------------------------------------------------
  static  void                Asynchronous_ComputeDicos();
  static  int                 Asynchronous_AtExit();
  static  CATHashDico        _Asynchronous_Dico;
  static  CATBoolean         _Asynchronous_Init;

  static  CATExtCGMReplay  * _LastLoadedTopologicalCCGMReplay ;
  static  CATLONG32          _CounterOfOperators;

   /**
   *  Forbidden ..
   */
   CATExtCGMReplay             (const CATExtCGMReplay &);
   CATExtCGMReplay& operator = (const CATExtCGMReplay &);

};

 
 INLINE  CATLONG32          CATExtCGMReplay::GetInterruptHistory()
 {
    return _InterruptHistory;
 }


 INLINE  CATechAttribute *  CATExtCGMReplay::GetFeedbackSteps()
 {
     return _FeedbackSteps;
 }



  INLINE  CATBaseUnknown *  CATExtCGMReplay::GetCATCGMReplay()
  {
     return _CATCGMReplay;
  }

 


// petit utilitaire pour communication de la version du dernier replay en unstream
// iWrite=1 pour ecrire, 0 pour lire
// ioVersion doit etre vu comme une version des donnees CGM, voir voir Mathematics\CATMathStream.m\src\DataVersion.cpp
ExportedByCATGeometricObjects
          void              CATExtCGMReplayForceUnstreamVersion (int  iWrite   ,
                                                                 int& ioVersion) ;



#endif



