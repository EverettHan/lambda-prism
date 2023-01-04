#ifndef CATechMonitor_H
#define CATechMonitor_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
* @level Private
* @usage U1
*/
//-------------------------------------------------------------------------------------------------
//  Interface for implementation of manager of Extract/Redo infrastructure
//    manipulated through CATechHandle 
//-------------------------------------------------------------------------------------------------

#include "ExportedByCATTechTools.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include <stddef.h>
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATBoolean.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATechMonitor;
#else
extern "C" const IID IID_CATechMonitor ;
#endif


#include "CATechHandle.h"

class CATechExt;
class CATechCheckPoint;
class CATechInspector;
class CATHashDico;
class CATCGMTransaction;
class CATCGMOperator;



/** -------------------------------------------------------------------------------------
* Dynamic invokation of Build-In But Debug Only Software .
-------------------------------------------------------------------------------------  */
class ExportedByCATTechTools CATechMonitor : public CATBaseUnknown
{
    CATDeclareInterface;

public:

    /** 
    * IsMonitoringEnabled : Based on the input Latetype name and the behavior it determines if 
    *                       Phoenix capture is enabled or not and is thus called from operator::Run() 
    *                       for checking if phoenix capture is enabled.
    * @param iLateType : LateType name for phoenix
    * @param iBehavior : Behavior for we check if phoenix capture is enabled
    * @return
    *   Returns S_OK when phoenix capture is enabled
    */
    virtual HRESULT  IsMonitoringEnabled(const CATString          & iLateType,
                                         const CATechBehaviorType   iBehavior) = 0;


    /** 
    * IsUnderTransaction : Checks if the transaction for the passed iBehaviorType is currently active
    * @param iBehaviorType : The behavior which is to be compared
    * @return
    *   Returns S_OK if transaction for the passed iBehaviorType is currently active
    */
    virtual HRESULT  IsUnderTransaction( const CATechBehaviorType & iBehaviorType ) = 0;

    /** 
    * EnablePhoenix : Method checks if phoenix capture/redo is enabled or not.
    * @param KeyValues : Created after parsing the CATech environment variable
    * @return
    *    Returns S_OK if phoenix capture/redo is enabled
    */
    virtual HRESULT  EnablePhoenix(const CATHashDico &iKeyValue) = 0;

    //---------------------------------------------------------------------------------------- 
    // BeginPhoenixTransaction/EndPhoenixTransaction
    //    ressources are transient to a transaction monitored by this way
    //---------------------------------------------------------------------------------------- 

    /** 
    * BeginTransaction : To be called when phoenix is enabled(IsMonitoringEnabled() returns S_OK), 
    *                    used to begin a particular phoenix transaction
    * @param iLateType : Late type name for phoenix
    * @param iBehaviorType : Behavior corresponding to which the transaction is to
    *                        be created.
    * @param iOperation : Reference to the Operator. It can be NULL as in case
    *                     of replay(ie. CATechBehaviorTypeRedo)
    * @param iOperationExtension : Reference to the operator CATechExt extension
    *                              instance. It can be NULL as in case
    *                              of replay(ie. CATechBehaviorTypeRedo)
    */ 
    virtual HRESULT  BeginPhoenixTransaction(const CATString          & iLateType, 
                                             const CATechBehaviorType & iBehaviorType, 
                                             void                     * iOperation,
                                             CATechExt                * iOperationExtension ,
                                             const CATechCheckPoint   * iBreakPoint = NULL,
											 CATechAttribute	  *iAttributeToFill = NULL)  = 0;

    /** 
    * EndTransaction : To be matched exactly for each pending BeginTransaction (no cross Transaction).
    *                  It is to be called at the end of a particular phoenix transaction so as to 
    *                  perform clean up activities once phoenix capture is done like:
    * @param iLateType : Late type name for phoenix
    * @param iBehaviorType : Behavior corresponding to which the transaction is to be ended.
    * @param iOperation : Reference to the Operator. It can be NULL as in case
    *                     of replay(ie. CATechBehaviorTypeRedo)
    * @param iOperationExtension : Reference to the operator CATechExt extension instance. It can be 
    *                              NULL as in case of replay(ie. CATechBehaviorTypeRedo)
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */ 
    virtual HRESULT  EndPhoenixTransaction(const CATString          & iLateType, 
                                           const CATechBehaviorType & iBehaviorType, 
                                           void                     * iOperation,
                                           CATechExt                * iOperationExtension,
										   CATechAttribute	  *iAttributeToFill = NULL)  = 0;



    /** 
    * IsCurrentPhoenixTransactionAbout : The method checks if the current transaction behavior type 
    *                                    and extension instance matches with the input behavior and extension. 
    * @param iBehaviorType : Behavior which is to be compared
    * @param iOperationExtension : The operator extension to be compared
    * @return
    *   Returns S_OK if the behavior and extension match for the current transaction
    */ 
    virtual HRESULT IsCurrentPhoenixTransactionAbout(const CATechBehaviorType & iBehaviorType, 
                                                     CATechExt                * iOperationExtension )  = 0;


    /** 
    * IsTransactionAbout : Detect if a particulart kind of transaction is currently engaged
    *
    *  @param iTransactionType : Kind of transaction.
    *
    * @return
    *   Returns S_OK if a transaction of passed iTransactionType is currently active
    */ 
    virtual HRESULT IsTransactionAbout(const CATechBehaviorType & iTransactionType  )  = 0;


    /** 
    * BeforeBreakPointContext : Integration event (BreakPoint/Inspector) for history management of phoenix transactions
    * @param iBreakPoint : CATechCheckPoint to be set
    * @param iInspector : CATechInspector to be set, currently is unused
    * @param iInspectorName : Inspector name to be set 
    * @return
    Returns S_OK if the request succeeds without any issues
    */ 
    virtual HRESULT  BeforeBreakPointContext(const CATechCheckPoint & iBreakPoint,
                                             CATechInspector        * iInspector ,
                                             const CATUnicodeString & iInspectorName  )  = 0;

    /** 
    * AfterBreakPointContext : Integration event (BreakPoint/Inspector) for history management of phoenix transactions
    * @param iBreakPoint : CATechCheckPoint to be set
    * @param iInspector : CATechInspector to be set, currently is unused
    * @param iInspectorName : Inspector name to be set 
    * @return
    Returns S_OK if the request succeeds without any issues
    */ 
    virtual HRESULT  AfterBreakPointContext(const CATechCheckPoint & iBreakPoint,
                                            CATechInspector        * iInspector ,
                                            const CATUnicodeString & iInspectorName  )  = 0;


    /** 
    *   BreakPointContext : Integration event (for history management
    *
    * @param iBreakPoint.
    *
    * @param i0Before_1After
    *
    *
    * @return
    *      S_OK   if request succeeded <br>
    *      E_FAIL if request failed <br>
    */ 
    virtual HRESULT  BreakPointContext(const CATechCheckPoint & iBreakPoint,
                                       const CATBoolean         i0Before_1After)  = 0;


    /** 
    *   PublishTransactionContext  
    *
    * @param iTransaction.
    *
    * @param i0Before_1After
    *
    *
    * @return
    *      S_OK   if request succeeded <br>
    *      E_FAIL if request failed <br>
    */ 
    virtual HRESULT  PublishTransactionContext(const CATBoolean          i0Before_1After,
                                               const CATCGMTransaction * iTransaction,  
                                               CATCGMOperator          * iOperator) = 0;



    /** 
    *   IsBreakpointFiltered  
    *
    *
    * @return
    *      TRUE   if to be Filtered <br>
    *      FALSE  otherwisw <br>
    */ 
    virtual CATBoolean IsBreakpointFiltered() = 0;


    //---------------------------------------------------------------------------------------- 
    //  Filtering Context under runtime 
    //     helpers for focus on a particular 3D area
    //---------------------------------------------------------------------------------------- 

    /**
    * IsToBeFilteredByBox3D : The method is used to check if a filter in the form of a CATMathBox 
    *                         which specifies the important area has been applied so that too many 
    *                         traces are not generated.
    * @param oBox3DFilter : CATMathBox which is used for filtering
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    */
    virtual  HRESULT IsToBeFilteredByBox3D(CATMathBox * oBox3DFilter = NULL)  = 0;

    /**
    * SetBox3DFilter: The method is used to apply such a filter so that too many traces are not 
    *                 generated in case of a very complex scenario. The filter is applied in the 
    *                 form of a CATMathBox. 
    * @param iBox3DFilter : CATMathBox representing the spatial area to be
    *                       Considered when generating traces.
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual  HRESULT SetBox3DFilter(CATMathBox & iBox3DFilter)  = 0;


    //---------------------------------------------------------------------------------------- 
    //    ressources are transient to a transaction monitored by this way
    //                Incubate/Reborn/Growth
    //---------------------------------------------------------------------------------------- 

    /**
    * Incubate : The method is used for initiating phoenix capture.
    * @param iOperationExtension : Operator extension for phoenix.
    * @param oOutputFile : Output file path for phoenix.xml corresponding 
    *                      to the current phoenix transaction.
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT Incubate(CATechBehavior   *  iOperationExtension ,
                             CATUnicodeString *  oOutputFile = NULL)   = 0;

    /**
    * Reborn : The method is used for replaying a captured phoenix scenario
    * @param inputFile : File path for the Phoenix.xml which has all the data
    *                    related to all transactions in a particular session.
    * @param oOutputResult : Pointer to implementation of CATechBehavior
    *                        interface
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    */
    virtual  HRESULT Reborn(const CATUnicodeString  &  inputFile,
                            CATechBehavior         *& iOperationExtension )  = 0;


    /**
    * Growth : Transient management under Reborn global operation
    * @param iFatherContext : CATechExt derived extension instance
    * @param iPhoenixType : LateType name for phoenix
    * @return
    *   S_OK if the request succeeds without any issues
    */
    virtual  HRESULT Growth(CATechChannel   * iFatherContext,
                            const CATString & iPhoenixType     )  = 0;



    /**
    * RequestForWebFile : The method is used for calculating the file path to the current 
    *                     phoenix transaction/extension output directory for a file whose name 
    *                     is passed as the iSuffixFile and type(extension) as the iFileType. 
    * @param iBehaviorContext  : Current phoenix behavior
    * @param oWebFile          : File name for the requested file
    * @param iSuffixFile       : Prefix for the requested file
    * @param iFileType         : Classical type of file for automatic (default)
    *                            application association 
    * @param iHiddenForHistory : dedicated to history index enable/disable 
    *                            (if file is indirectly acceded by a master one)
    *  @param iShortNameForHistory : dedicated to history index  
    *                                   more convenient name presentation
    *
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT RequestForWebFile(const CATechBehaviorType & iBehaviorContext,
                                      CATUnicodeString         & oWebFile,
                                      const char                 iSuffixFile[] = "",
                                      const char                 iFileType[]   = "html",
                                      const CATBoolean           iHiddenForHistory = FALSE,
                                      const char               * iShortNameForHistory = NULL) = 0;


    /**
    * RequestOfCacheMainStyleSheet : The method is used for copying the phoenix associated .css files 
    *                                into current phoenix directory. 
    * @param iBehaviorContext  : Current phoenix behavior
    * @param oMainStyleSheet : Name for the CSS file
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT  RequestOfCacheMainStyleSheet(const CATechBehaviorType & iBehaviorContext,
                                                  CATUnicodeString   &  oMainStyleSheet )  = 0;

    /**
    * RequestOfCacheRessource : The method is used for copying file with the passed name into 
    *                           the current phoenix directory. 
    * @param iBehaviorContext  : Current phoenix behavior
    * @param oMainStyleSheet : Name pattern of the resource file
    * @param oMainStyleSheet : Actual name of the resource file
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT RequestOfCacheRessource(const CATUnicodeString   & iPhoenixFileName,
                                            const CATechBehaviorType & iBehaviorContext,
                                            CATUnicodeString         & oCacheRessource) = 0;

    //---------------------------------------------------------------------------------------- 
    //  SetUp and Options
    //---------------------------------------------------------------------------------------- 

    /**
    * SetUpOutputDirectory : The method is used to set the output directory specified in the “CATech” 
    *                        variable as he output directory at the time of enabling phoenix(EnablePhoenix()). 
    *                        Creates the same always if iForceCreate option is true
    * @param iOutputDirectory : The directory path to be set
    * @param iForceCreate : Specifies if we need to create the directory
    *                       Corresponding to the passed path
    * @return
    *   Returns S_OK if directory is accessible/its creation succeeds.
    */
    virtual HRESULT SetUpOutputDirectory(const CATUnicodeString  &  iOutputDirectory,
                                         const CATBoolean           iForceCreate = TRUE)   = 0;

    /**
    * GetOutputDirectory : Gets the output directory for phoenix
    * @param  oOutputDirectory  : The output directory path
    * @return
    *   Returns S_OK if output directory is properly set
    */
    virtual HRESULT GetOutputDirectory(CATUnicodeString  &  oOutputDirectory)   = 0;

    /**
    * SetPreview : Sets the preview. We query for this value at a later time
    * @param iPreview : Boolean value to be set.
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT SetPreview(const CATBoolean iPreview = TRUE)   = 0;

    /**
    * IsWithPreview : Is Preview Enabled.
    *
    *
    * @return
    *   Returns S_OK if preview was set
    */
    virtual HRESULT IsWithPreview()   = 0;


    /** 
    * GetLastPhoenixTypeRecorded : Gets the late type name of the last phoenix transaction.
    * @param oLateType : Late type name corresponding to the phoenix transaction
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT  GetLastPhoenixTypeRecorded(CATString   & oLateType)   = 0;


    //---------------------------------------------------------------------------------------- 
    // Miscellaneous Management
    //---------------------------------------------------------------------------------------- 

    /** 
    * HResultHandling : Method adds additional traces based on the iSeverity parameter 
    *                   for FAILED HRESULT. Also logs the message corresponding to passed iMessage
    * @param iHResult : The failed HRESULT value.
    * @param iSeverity : type of error for logging the appropriate message.
    * @param iMessage : Error associated with the failure for printing the correct message.
    * @return
    *   same as the given input argument
    */
    virtual HRESULT  HResultHandling(HRESULT iHResult, CATErrorType iSeverity  , CATError *iMessage  )   = 0;


    /**
    * InitHistoryMasterFile : The method is used for creating and initializing phoenix 
    *                         history  related files
    * @param iExtractRedo : Is true if extract redo is enabled
    * @param iCheckPoint : Is true if with history break points is enabled 
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT  InitHistoryMasterFile(const CATBoolean iExtractRedo, const CATBoolean iCheckPoint)   = 0;

    /**
    * SetVerboseExtractRedo : Sets as to whether more verbose information is to added to the history 
    *                         files (HistoryExtractRedo.html, History.html) for the phoenix scenario.
    * @param iExtractRedoVerbose : Boolean value to be set
    * @return
    *   Returns S_OK if the request succeeds without any issues
    */
    virtual HRESULT  SetVerboseExtractRedo(const CATBoolean iExtractRedoVerbose)   = 0;

    /**
    * IsVerboseExtractRedo : Returns true if for the current phoenix scenario, 
    *                        the option for verbose history was set.
    */
    virtual  CATBoolean IsVerboseExtractRedo()= 0;

	/** 
	* UseLocalSubDirectory : Acivate or Inactivate the use of SubLocalDirectory to save Phoenix files
	*/
	virtual void UseLocalSubDirectory(CATBoolean iEnableSubLocalSubDir)		= 0;

  /**
  * ReInitStaticData
  * 
  */
  virtual void ReInitStaticData() = 0;

  /** 
  * SetWithExtractRedo : 
  *
  */
  virtual void SetWithExtractRedo(CATBoolean iWithExtractRedo) = 0;

};

#include "CATechHandle_inline.h"



#endif
