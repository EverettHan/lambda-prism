/* -*-c++-*- */
#ifndef CATechHandle_h
#define CATechHandle_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  accessing manager of Extract/Redo infrastructure
//-------------------------------------------------------------------------------------------------

#include "ExportedByCATTechTools.h"
#include "CATechDefine.h"

#include "CATErrorDef.h"
#include "CATError.h"

#include "CATDataType.h"
#include "CATBooleanDef.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfInt.h"


 
class CATString;
class CATError;
class CATMathBox;
class CATHashDico;

class CATechBehavior;
class CATechChannel;
class CATechExt;
class CATechMonitor;

class CATechCheckPoint;

class CATechAttribute;


/**
* Interface to manage Simple Extract Redo    Monitor 
*/
class ExportedByCATTechTools CATechHandle 
{
public :  

  
  /** 
  * IsPhoenixAble : Detect if small Extract/Redo or CheckPoint/Inspector is available
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */
  static INLINE  HRESULT  IsPhoenixAble() ;  

  /** 
  * IsMonitoringEnabled : This method is used for checking if phoenix capture/replay mechanism is enabled 
  *
  *  @param iLateType    : SuffixName for LateType of Core Operator 
  * @param iBehavior    : Kind of phoenix behavior(capture/replay/redo etc.)
  * @return
  *      S_OK if phoenix capture is enabled <br>
  *      E_FAIL if request failed <br>
  */
  static /*INLINE*/  HRESULT  IsMonitoringEnabled(const CATString   & iLateType,
                                             const CATechBehaviorType iBehavior) ;
  
  /** 
  * IsUnderTransaction : The method checks if a transaction corresponding to the passed behavior exists or not
  *
  * @param iBehavior   : Kind of phoenix behavior(capture/replay/redo etc.)
  * @return
  *      S_OK if transaction with the passed iBehavior exists <br>
  *      E_FAIL if request failed <br>
  */
  static INLINE  HRESULT  IsUnderTransaction(const CATechBehaviorType & iBehaviorType ) ;
 

  //---------------------------------------------------------------------------------------- 
  // Engine Integration  :  Open architecture  : ManageBehavior
  //---------------------------------------------------------------------------------------- 

  /** 
  * ManageBehavior              : One shot of behavior. The method is used for performing phoenix related
  *                               capture for before/after/redo behaviors when running a particular operator
  *
  *  @param iLateType    : SuffixName for LateType of Core Operator 
  *                              used in context of dedicated Phoenix dictionnary (see CNext\Phoenix\*
  *                              with explit triple values given { iLateType,  EntryName, SharedLibName }
  *                              according to function signature :  CATechChannelCreator
  *  @param iBehaviorType : Kind of behavior.
  *  @param iOperation    : Context of operator understandable only in context of the Late Type 
  * @param iOperationExtension  : May be NULL in initially at the time of capture. 
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT ManageBehavior( const CATString          & iLateType, 
                                 const CATechBehaviorType & iBehaviorType, 
                                 void                     * iOperation,
                                 CATechExt            * iOperationExtension,
								 CATechAttribute	  *piAttributeToFill = NULL);
 
  /** 
  * IsWithPreview : Is Preview Enabled.
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */
  static HRESULT  IsWithPreview() ;

  //---------------------------------------------------------------------------------------- 
  //  Incubate/Reborn/Growth
  //---------------------------------------------------------------------------------------- 
      
  /**
   * Incubate                   : This method is used for initiating phoenix capture
   *
   * @param iOperationExtension : Operator extension instance, mandatory. 
   * @param oOutputFile         : Path for the output file for this phoenix transaction.
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static  HRESULT Incubate(CATechBehavior         * iOperationExtension ,  CATUnicodeString   * oOutputFile = NULL)  ;
      
  /**
   * Reborn                     : The method is used to replay the captured phoenix file which is passed as input
   *
   * @param inputFile           : Input phoenix.xml file path. 
   * @param iOperationExtension : Operator extension instance which can be NULL 
   *                              initially, is valuated if successfull. 
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static  HRESULT Reborn( const CATUnicodeString  &  inputFile,  CATechBehavior *  & iOperationExtension )  ;

  /**
   * RequestForWebFile        : The method is used for calculating the file path to the current phoenix 
   *                            transaction/extension output directory for a file whose name is passed as 
   *                            the iSuffixFile and type(extension) as the iFileType
   *
   * @param iBehaviorContext  : Current phoenix behavior 
   * @param oWebFile          : File name for the requested file 
   * @param iSuffixFile       : Prefix for the requested file
   *  @param iFileType         : Classical type of file for automatic (default) application association
   *  @param iHiddenForHistory    : dedicated to history index
   *                                   enable/disable (if file is indirectly acceded by a master one)
   *
   *  @param iShortNameForHistory : dedicated to history index  
   *                                   more convenient name presentation
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static HRESULT RequestForWebFile(const CATechBehaviorType & iBehaviorContext
                                   , CATUnicodeString        &  oWebFile
                                   , const char                 iSuffixFile[] = ""
                                   , const char                 iFileType[]   = "html"
                                   , const CATBoolean           iHiddenForHistory = FALSE
                                   , const char               * iShortNameForHistory = NULL )    ;
 
        
  /**
   * RequestOfCacheMainStyleSheet : The method get the name for the .css file for phoenix history HTML. It also copies the 
   *                                file to the current phoenix directory from the run time view
   *
   * @param oMainStyleSheet       : Name for the style sheet 
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static HRESULT RequestOfCacheMainStyleSheet(CATUnicodeString   &  oMainStyleSheet ) ;
        
  /**
   * RequestOfCacheRessource : The method get the name for the resource files(bitmap files etc.) for phoenix history HTML. 
   *                           It also copies the file to the current phoenix directory from the run time view
   *
   * @param iPhoenixFileName :  Name for the resource file 
   *  @param oExactFileName   :  Duplicated ressource in welcome page
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static HRESULT RequestOfCacheRessource( const CATUnicodeString  &  iPhoenixFileName, 
                                          CATUnicodeString        &  oExactFileName   ) ;

 
  //---------------------------------------------------------------------------------------- 
  //  SetUp
  //---------------------------------------------------------------------------------------- 

   /**
   * SetUpOutputDirectory       : The method sets the ouput directory in the CATechMonitor and creates it if needed. 
   *                              Can be used by clients to set the output directory from code directly instead 
   *                              of specifying it in “CATech” variable
   *
   * @param iOutputDirectory    : Output directory path 
   * @param iForceCreate        : Explicitly creates the directory if the option is true
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static   HRESULT SetUpOutputDirectory(const CATUnicodeString  &  iOutputDirectory,
                                        const CATBoolean           iForceCreate  )   ;

   /**
   * GetOutputDirectory         : Gets the output directory path for current phoenix session
   *
   * @param oOutputDirectory    : Output Directory path. 
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static   HRESULT GetOutputDirectory(CATUnicodeString  &  oOutputDirectory  )   ;


  //---------------------------------------------------------------------------------------- 
  //  Explicit Phoenix Monitoring Enabler
  //---------------------------------------------------------------------------------------- 

  /** 
  * BootPhoenix : Enables phoenix if the variable CATech has been set.
  *               If already available, returns the existing monitor.
  *
  * @iLateType : Late type name for the phoenix monitor
  * @iBootPrms : This input string has two different goals :
  *              - if it is exactly "Phoenix", then Phoenix will be enabled even if the variable CATech was not set. (Replaces previous use of keyvalue {Phoenix,""})
  *              - if it is a string of the same format as the variable CATech, it will be parsed instead of CATech.
  *
  * Every call to BootPhoenix using a different string than "Phoenix" MUST BE FOLLOWED by a call to DisablePhoenix.
  * When such a string is used, the existing monitor is not returned. A new monitor is created instead which will have
  * to be released when not used anymore so as to restore the previous monitor.
  *
  * @return
  *      Returns the CATechMonitor instance
  */
  static CATechMonitor*  BootPhoenix(const CATString   & iLateType, const char* iBootPrms = NULL);

  /** 
  *  EnablePhoenix : The method Creates the CATechMonitor and performs the necessary initialization for enabling phoenix
  *                  It also saves the created monitor on a stack in case a new, customized monitor is required later on.
  *
  * @param iKeyValue : Hashtable with key value pairs created by reading the CATech variable
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */
  static HRESULT  EnablePhoenix(const CATHashDico &iKeyValue);

  /** 
  * DisablePhoenix : Disable the last phoenix capture that was enabled either with BootPhoenix or EnablePhoenix.
  *                  Restores the previous phoenix capture if there was one.
  *
  * @return
  *      S_OK always
  */
  static HRESULT  DisablePhoenix();

  /** 
  * SetWithExtractRedo : 
  *
  */
  static HRESULT SetWithExtractRedo(CATBoolean iWithExtractRedo);

  /** 
  * ReInitStaticData : 
  *
  */
  static HRESULT ReInitStaticData();

   /**
   * SetPreview
   *
   *  @param iPreview          : Force Preview   . 
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static HRESULT SetPreview(const CATBoolean iPreview = TRUE) ;

  //---------------------------------------------------------------------------------------- 
  // Management
  //---------------------------------------------------------------------------------------- 


  /** 
  * HResultHandling : Helpers for debugging a returned FAILED HRESULT.
  *  while under dedicated Phoenix management
  *       Good Practise :  use CATechHandle::HResultHandling(rc,,) before return or CATThrow;
  *       Bad Practice  :  CATThrowForNullPointerReturnValue(E_FAIL);
  *
  *  @param iHResult  : Value of synthetic HRESULT. 
  *  @param iSeverity : Severity of anomalie. 
  *                        CATErrorTypeCritical    : 
  *                        CATErrorTypeFatal       : 
  *                        CATErrorTypeWarning     : 
  *                        CATErrorTypeInformation : 
  * @param iMessage  : Error Message
  * @return
  *      same as given input argument<br>
  */
  static HRESULT  HResultHandling(HRESULT iHResult, CATErrorType iSeverity = CATErrorTypeCritical, CATError *iMessage = NULL) ;
 
  
  /** 
  * GetLastPhoenixTypeRecorded : Gets the Late type name for the last phoenix recorded
  *
  *  @param oLateType : LateType.
  *
  * @return
  *      S_OK as long as a valid monitor is available
  */
  static INLINE HRESULT  GetLastPhoenixTypeRecorded(CATString   & oLateType) ;

  /** 
  * Set_UnderControlOfPlayBack : Set the information that Phoenix monitoring is under control of PlayBack
  *
  *  @param iOptionValue : Value .
  *
  */
  static /*INLINE*/ void Set_UnderControlOfPlayBack(short iOptionValue);

  /** 
  * Set_UnderControlOfPlayBack : Set the information that Phoenix monitoring is under control of PlayBack
  *
  *  @return the Value.
  *
  */
  static /*INLINE*/ short IsUnderControlOfPlayBack();

   /** 
  * Set_UnderUnstreamOfPlayBackFile : Set the information that Phoenix monitoring is under control of PlayBack
  *
  *  @param iOptionValue : Value .
  *
  */
  static /*INLINE*/ void Set_UnderUnstreamOfPlayBackFile(short iOptionValue);

  /** 
  * Is_UnderUnstreamOfPlayBackFile : Set the information that Phoenix monitoring is under control of PlayBack
  *
  *  @return the Value.
  *
  */
  static /*INLINE*/ short Is_UnderUnstreamOfPlayBackFile();

  /** 
  * UseLocalSubDirectory : Acivate or Inactivate the use of SubLocalDirectory to save Phoenix files
  */
  static /*INLINE*/ void UseLocalSubDirectory(CATBoolean iEnableSubLocalSubDir);

  //---------------------------------------------------------------------------------------- 
  //  BLA BLA 
  //---------------------------------------------------------------------------------------- 

  /** 
  * Constructor.
  */
  INLINE CATechHandle();

  /** 
  * Destructor.
  */
  INLINE ~CATechHandle();

  /**
  * To be called from ~CATechHandle
  */
  void Destruction();

  /** 
  * TheRa.
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static CATechHandle  TheRa; 

 
 
  /** 
  * GetMonitor.
  *
  * @return
  *      CATechMonitor* if request succeeded <br>
  */
  static CATechMonitor*  GetMonitor();

  /** 
  * Is_PhoenixInfra_PlayBack_Stream_Disabled.
  *
  * @return
  *      
  */
  static CATBoolean  Is_PhoenixInfra_PlayBack_Stream_Disabled();

  /** 
  * Is_PhoenixInfra_PlayBack_Unstream_Disabled.
  *
  * @return
  *      
  */
  static CATBoolean  Is_PhoenixInfra_PlayBack_UnStream_Disabled();

  /** 
  * Is_PhoenixInfra_PlayBack_Unstream_Disabled.
  *
  * @return
  *      
  */
  static CATBoolean  Is_PhoenixInfra_PlayBack_UnStream_Enhancement_Disabled();
 
  /** 
  * Default <br>
  */
  static const CATString       _PhoenixMonitor;

private:

  static  CATechMonitor   *  _IsPhoenixAble() ;  

  /** 
  * Variable _Handler<br>
  */
  static   CATechMonitor   * _Handler;

  /** 
  * Invalid<br>
  */
  static   CATBoolean           _Invalid;

  /** 
  * UnderControlOfPlayBack<br>
  */
  static   short           _UnderUnstreamOfPlayBackFile;

  /** 
  * UnderControlOfPlayBack<br>
  */
  static   short           _UnderControlOfPlayBack;

  /** 
  * UnderUnstreamOfPlayBackFile<br>
  */
  static   CATListOfInt           _StackOfUnderUnstreamOfPlayBackFile;

  /**
  * Stack of handlers
  */
  static   CATListPV       * _StackOfHandlers;

  /** 
  * UnderControlOfPlayBack<br>
  */
  static   CATListOfInt           _StackOfUnderControlOfPlayBack;
  
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATechHandle(const CATechHandle &iCopy);
  CATechHandle& operator=(const CATechHandle &iCopy);

  friend class CATechCheckPoint;
};
 
#include "CATechMonitor.h"

#endif
