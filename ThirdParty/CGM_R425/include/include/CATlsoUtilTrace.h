/* -*-C++-*- */

#ifndef CATlsoUtilTrace_H
#define CATlsoUtilTrace_H
/*  
=============================================================================

RESPONSABLE  : L Marini

DESCRIPTION  : class to debug trace on Live Shape Operator
               
=============================================================================
*/
// --------------------------------------------------------
// Level 1   -> Trace for beginning of Construtor and end of Destructor
// Level 2   -> Constructeur, Run et Destructeur des operateur GMLiveShape
// Level 3   -> Les Set des operateurs GMLiveShape
// Level 4   -> Les grands etapes des operateurs GMLiveShape
// Level 5   -> Resultat des operateurs CGM
// Level 6   -> Pour le debug comlpexe
// ..
// Level -1  -> Pour le debug temporaire et specifique 
// --------------------------------------------------------

// --------------------------------------------------------
//  SAMPLE OF VARIABLES SET
// --------------------------------------------------------
//
//  Sample 1 - All traces with level lower than 2
//  --------------------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_MaxLevelTrace=2
//
//  Sample 2 - All Traces with level 3
//  ----------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_MaxLevelTrace=3
//  set CATGMLiveShapeOperator_MinLevelTrace=3
//
//  Sample 3 - All Traces with level between 4 and 5
//  -------------------------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_MaxLevelTrace=5
//  set CATGMLiveShapeOperator_MinLevelTrace=4
//
//  Sample 4 - All Traces with level -1
//  -----------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_MinLevelTrace=-1
//
//  Sample 5 - All traces with level lower than 2 in a file E:\tmp\lsoTrace.txt
//  ---------------------------------------------------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_PathNameTrace=E:\tmp\lsoTrace.txt
//  set CATGMLiveShapeOperator_MaxLevelTrace=2
// 
//  Sample 6 - Activate the CPUTime trace
//  -----------------------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_MaxLevelTrace=2;
//  set CATGMLiveShapeOperator_CPUTimeTrace=1
//
//  Sample 7 - Activate the beep for special debug
//  -----------------------------------------------
//  set CATDevelopmentStage=TRUE
//  set CATGMLiveShapeOperator_BeepTrace=1
//
// --------------------------------------------------------

// --------------------------------------------------------
//  SAMPLE OF CODE
// --------------------------------------------------------
//
// Sample 1 - for levle 1 and 2
// -----------------------------
//   LSOTraceLevel1or2(CATlsoUtilTrace_MANIFOLDEDITOR,CATlsoUtilTrace::DESTRUCTOR_BEGINNING);
//
// Sample 2 - for level N
// ----------------------
//    LSOTraceLevelN(5,CATlsoUtilTrace_THICKNESSFACE,"Thickness KO");
//
// Sample 3 - for level N
// -----------------------
//    LSOTraceLevelN(5,CATlsoUtilTrace_THICKNESSFACE,"Thickness",hr);  // hr is a HReswult
//
// Sample 4 - for level N
// -----------------------
//    CATCGMOutput * dbgoutput = GetLSOTraceOuput(6,CATlsoUtilTrace_ERASEFACE);
//    if (dbgoutput)
//    {
//      LSOTraceLevelN(6,CATlsoUtilTrace::ERASEFACE,"RemoveFaceInShell Journal Dump"); 
//      LSOTraceRestoreCgmoutForNoSpam();
//      ErsaeJournal -> Dump(*dbgoutput);
//      *dbgoutput << "End of Dump" << cgmendl;
//      LSOTraceDisableCgmoutForNoSpam();
//    }
//
//  Sample 5 - Make a Beep
//  -----------------------
//    LSOTraceBeep();
//
// --------------------------------------------------------

#include "PersistentCell.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "IUnknown.h"
#include "CATCGMOutput.h"
#include "CATlsoUtilTraceDef.h"

// Include for CATTimerId
#include "CATLib.h"
#include "CATUnicodeString.h"
#include "CATCX_NCGM.h"

class CATTopOperator;
class CATIPGMTopOperator;
class CATAdvancedExtTopOperator;
class CATBody;
class CATICGMTopOperator;
class CATUnicodeString;


//--------------------------------------------------------------------------
// LSO_MACRO
// ----------------------------------------------------------------------------
// @nocgmitf
#define LSOMACRO_LSOTraceMessage1Run(iCharMessage)  const char * pCharLSOMessage          = iCharMessage;\
                                                    CATULONG32   beginCPUTimerLSOMessage  = LSOTraceMessage1Run(pCharLSOMessage);

// @nocgmitf
#define LSOMACRO_LSOTraceMessage2Result(iOK, ipBody) LSOTraceMessage2Result(pCharLSOMessage, !!iOK, ipBody, beginCPUTimerLSOMessage);

//--------------------------------------------------------------------------
// @nocgmitf
class CATlsoUtilTrace
{

public:

  // ------------------
  // ConfigurationType
  // ------------------
  enum ResultType { NOTHING=-1,
                    RESULT_KO=0,
                    RESULT_OK,
                    RUN
  };

  //-----------------------------------------------------------------------------
  // DisplayTrace
  //-----------------------------------------------------------------------------
  static CATBoolean DisplayTrace(CATLONG32                    iLevel,
                                 CATlsoUtilTrace_OperatorName iOpName);

  //-----------------------------------------------------------------------------
  // SetFirstOutputPathName 
  //-----------------------------------------------------------------------------
  static char * SetFirstOutputPathName();

  //-----------------------------------------------------------------------------
  // CreateOutputStream 
  //-----------------------------------------------------------------------------
  static void CreateOutputStream();

  //-----------------------------------------------------------------------------
  // CreateNewTimerId
  //-----------------------------------------------------------------------------
  static void ResetTimer();
  static void DisplayTimer();

  static void DisableCgmoutForNoSpam();
  static void RestoreCgmoutForNoSpam();

  static void TimeOutOfRunDisplay(const CATULONG32 & iCPUTimeBeforeRun,
                                                   const CATULONG32 & iCPUTimeAfterRun,
                                                   const CATLONG32  & iRunLevel);

  static CATULONG32 DisplayLocalTimeAndDeltaTime(double iDeltaTime);
  static void DisplayResultColumn(CATlsoUtilTrace::ResultType iResultType);

  static void LSOTraceInterruptLastMessage();

  static CATULONG32 LSOTraceMessage(const char                  * iName,
                                    CATlsoUtilTrace::ResultType   iResultType=CATlsoUtilTrace::NOTHING,
                                    CATBody                     * iBody=NULL,
                                    CATULONG32                    iCPUTimerFirstMessage=0);

  static int LoadOperatorDisplayVariable();

  // ------------------
  // ImageNameType
  // ------------------
  enum ImageNameType { IMAGENAME_BODYTAG_ONLY=0,
                       IMAGENAME_BODYTAG_THEN_NAME,
                       IMAGENAME_BODYTAG_THEN_FREE_TEXT,
  };

  static void CreateBodyPhoto(CATBody & iBody, CATUnicodeString iDebugLabel="LSOPhoto", int iTailleDesiree=460);
  static void PrintHTMLPhoto(CATBody & iBody);
  static void CreateBodyPhotoWithBodyTagThenName(CATBody & iBody, CATUnicodeString & iFullName, int iTailleDesiree=460);
  static void CreateBodyPhotoWithBodyTagFreeText(CATBody & iBody, CATUnicodeString & iFullName, CATUnicodeString * iFreeText, int iTailleDesiree=460);

private:

  static void SaveBodyInNCGM(const CATCX_NCGM       & iDebugcgm,
                             CATBody                & iBody,
                             const CATUnicodeString & iBodyName,
                             CATUnicodeString       & oFullPathNCGM);

  static void LoadNCGMAndSaveImage(const CATUnicodeString & iFullPathNCGM,
                                   const CATUnicodeString & iFullPathPhoto,
                                   int iTailleDesiree=460);
};

//-----------------------------------------------------------------------------
// OpName 
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceRestoreCgmoutForNoSpam();
ExportedByPersistentCell void LSOTraceDisableCgmoutForNoSpam();

//-----------------------------------------------------------------------------
// OpName 
//-----------------------------------------------------------------------------
ExportedByPersistentCell const char * GetLSOTraceOpName(CATlsoUtilTrace_OperatorName iOpName);

//-----------------------------------------------------------------------------
// Get and Set OperatorDisplayStatus 
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean GetLSOTraceOperatorDisplayStatus(CATlsoUtilTrace_OperatorName iOpName);
ExportedByPersistentCell void       SetLSOTraceOperatorDisplayStatus(CATlsoUtilTrace_OperatorName iOpName,CATBoolean iDisplay);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceMaxLevel
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATLONG32 GetLSOTraceMaxLevel();
ExportedByPersistentCell void      SetLSOTraceMaxLevel(CATLONG32 iLevel);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceMinLevel
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATLONG32 GetLSOTraceMinLevel();
ExportedByPersistentCell void      SetLSOTraceMinLevel(CATLONG32 iLevel);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceBeep
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean GetLSOTraceBeep();
ExportedByPersistentCell void       SetLSOTraceBeep(CATBoolean iBeep);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceCPUTime
// Display CPU time in each trace 
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_CPUTimeTrace=1;
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean GetLSOTraceCPUTime();
ExportedByPersistentCell void       SetLSOTraceCPUTime(CATBoolean iCPUTimeOn);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceNoSpam
// Display CPU time in each trace 
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_NoSpam=1;
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean GetLSOTraceNoSpam();
ExportedByPersistentCell void       SetLSOTraceNoSpam(CATBoolean iNoSpamOn);

//-----------------------------------------------------------------------------
// Get and Set LSOTracePathName
//-----------------------------------------------------------------------------
ExportedByPersistentCell const char * GetLSOTracePathName();
ExportedByPersistentCell void         SetLSOTracePathName(const char * iName);

//-----------------------------------------------------------------------------
// Dump  Level1 or 2 Traces : (Constructeur, Run , Destructor) * (Beginning, End)
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_MaxLevelTrace=1   (ou plus) 
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceLevel1or2(CATlsoUtilTrace_OperatorName iOpName,
                                                CATlsoUtilTrace_Level1Prefix iPrefix,
                                                CATBoolean iWithLineBreak = TRUE);

//-----------------------------------------------------------------------------
// Dump  Level N Traces 
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_MaxLevelTrace=5   ( si N=5 ou moins de 5) 
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceLevelN(CATLONG32                      iLevel,
                                             CATlsoUtilTrace_OperatorName  iOpName,
                                             const char                   * iText,
                                             HRESULT                      * iHResult=0,
                                             CATBoolean iWithLineBreak = TRUE);


//-----------------------------------------------------------------------------
//
// Return CATCGMOutput * corresponding to &cgmout or a file path
// Retrun NULL if the trace isn't allowed to be displayed
//
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_OutputTrace=console
//  or
// SET CATGMLiveShapeOperator_OutputTrace=E:\tmp\LSOTrace.txt  (or any other file path name)
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATCGMOutput * GetLSOTraceOuput(CATLONG32                       iLevel,
                                                         CATlsoUtilTrace_OperatorName   iOpName);

//-----------------------------------------------------------------------------
// Make a beep : Use it only for very complex debugging
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_BeepTrace=1  
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceBeep();

//-----------------------------------------------------------------------------
// LSOTraceIsFirstOperator : To Indicate the first operator
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean LSOTraceIsFirstOperator(const CATAdvancedExtTopOperator *iExtTopOpe);

//-----------------------------------------------------------------------------
// LSOTraceFollowRunOfFirstOperator : To Indicate the first operator
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceFollowRunOfFirstOperator(const CATAdvancedExtTopOperator *iExtTopOpe,  CATBoolean iOK=TRUE);

//-----------------------------------------------------------------------------
// LSOTraceBeforeRun : Indicate the the run will be call 
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceBeforeRun(CATTopOperator     *iTopOpe, const char * iOpeName=NULL, CATBody * ipInputBody=NULL);
ExportedByPersistentCell void LSOTraceBeforeRun(CATIPGMTopOperator *iIPGMTopOpe);
ExportedByPersistentCell void LSOTraceBeforeRun(CATICGMTopOperator *iICGMTopOpe);
ExportedByPersistentCell void LSOTraceBeforeRun(const char * iOpeName);

//-----------------------------------------------------------------------------
// LSOTraceAfterRun : Indicate the run result
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceAfterRun(CATTopOperator *iTopOpe, CATBoolean iOK, const char * iOpeName=NULL, CATBody * ipInputBody=NULL,  CATBody * ipResultBody=NULL );
ExportedByPersistentCell void LSOTraceAfterRun(CATIPGMTopOperator *iTopOpe, CATBoolean iOK);
ExportedByPersistentCell void LSOTraceAfterRun(CATICGMTopOperator *iICGMTopOpe, CATBoolean iOK);
ExportedByPersistentCell void LSOTraceAfterRun(const char * iOpeName, CATBoolean iOK);

//-----------------------------------------------------------------------------
// LSOTraceMessage 1Run then 2Result
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATULONG32 LSOTraceMessage1Run(const char                  * iName);
ExportedByPersistentCell void       LSOTraceMessage2Result(const char                  * iName,
                                                           CATBoolean                    iResultOk,
                                                           CATBody                     * iBody,
                                                           CATULONG32                    iCPUTimerFirstMessage);

//-----------------------------------------------------------------------------
// LSOTraceInterruptMessage
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceInterruptMessage();

//-----------------------------------------------------------------------------
// Get and Set LSOTraceRunResult
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_RunResult=1  
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean GetLSOTraceRunResult();
ExportedByPersistentCell void       SetLSOTraceRunResult(CATBoolean iRunResult);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceRunResultFileMode
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_RunResult=1  
// SET CATGMLiveShapeOperator_RunResultFileMode=1
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATBoolean GetLSOTraceRunResultFileMode();
ExportedByPersistentCell void       SetLSOTraceRunResultFileMode(CATBoolean iRunResultFileMode);

//-----------------------------------------------------------------------------
// Get and Set LSOTraceRunLevelFilter
//
// SET CATDevelopmentStage=TRUE
// SET CATGMLiveShapeOperator_RunResult=1
// SET CATGMLiveShapeOperator_RunLevelFilter=3
//-----------------------------------------------------------------------------
ExportedByPersistentCell CATLONG32 GetLSOTraceRunLevelFilter();
ExportedByPersistentCell void      SetLSOTraceRunLevelFilter(CATLONG32 iRunLevelFilter);


//-----------------------------------------------------------------------------
// WaitOnlyForDebug
//-----------------------------------------------------------------------------
ExportedByPersistentCell void WaitOnlyForDebug(CATULONG32 iNbMilliSecond);

//-----------------------------------------------------------------------------
// GetTmpAddressForDebug ,  Need to call delete[].
//-----------------------------------------------------------------------------
ExportedByPersistentCell  const char * GetLSOTmpAddressForDebug();

//-----------------------------------------------------------------------------
// LSOTraceCreateBodyPhoto
//-----------------------------------------------------------------------------
ExportedByPersistentCell void LSOTraceCreateBodyPhoto(CATBody                        & iBody,
                                                      CATUnicodeString                 iDebugLabel,
                                                      CATlsoUtilTrace::ImageNameType   iImageNameType=CATlsoUtilTrace::IMAGENAME_BODYTAG_ONLY,
                                                      CATUnicodeString               * iFreeText=NULL,
                                                      int                              iTailleDesiree=460);

#endif
