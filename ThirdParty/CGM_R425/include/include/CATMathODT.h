/* -*-c++-*- */
#ifndef CATMathODT_H_
#define CATMathODT_H_
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2002
/*
* @COPYRIGHT DASSAULT SYSTEMES 2002
* ----------------------------------------------------------------------------------------------------------------------
*
*   Origin              : Detect as soon as possible inappropriate deviations in software behavior
*                              when engineering change occured (or in context of implement and control are made asynchronous).
*                         Target is the "one-shot perfect delivery" without iterations   
*                             by satisfying all quality check-list criteria 
*                             or anticipating the major pro/cons debate when bigger changes occured.
*                         (Some well-known antagonist : Quality vs Performance, Openess Vs Controlled, ....)
*
*                         Ideally, each domain should provide dedicated build-in tests
*                                   and practise these validations before any delivery shared with others impacted category.
*                                  this methodology should reduce considerably unpreditected entropy.
*                         Software quality is something very complex with specific criteria depending on
*                            each applied domain, proposal here is about an small attempts to reduce delay or entropy
*                           (which may implied high cost of analysis) in some of the specific fields :
*                           A/ With official Code quality CleanUp indicators
*                                 (for instance prevent embedded memory leaks detection automatically with ODT replay
*                                  problematic with official Code-CleanUp is about :
*                                         1/ delay  2/ high cost analysis to find the appropriate correction
*                                         in the AddRef()/Release() problematic, etc ...
*                           B/ Between very high interconnected sofware category
*                                 (Data checker aka topological check-up at each Body completion
*                                  serving as a measure of applied modeler's quality  between operation's execution)
*
*
*   Software's Category : TINY infrastructure services dedicated to enhanced CGM infrastructure tests
*
*                            it should help sofware convergence with intermediate higher control than usual
*                            targetting unit tests framework associated to that design.
*                                  (for instance , the CGMxxx.tst frameworks)
*
*   Similar C++ class of services :  CATCGMIsAuthorized.h ,  CATCGMExitForODT.h,  CATCGMIsUnderODT.h
*
*   About the enhanced (more severe) controls : they are ignited by specific files found/delivered in InputData.
*     The contents of these files is the initial condition for more severe anomalies detection.
*     It is specified in a very simple format with two columns :
*          first column  : Name
*          second column : Integer
*
*   Furthermore, you may find in Output, some report files of the same kind of suffix when a Test is replayed 
*  Here is a brief some input files used by CGM Infrastructure tests :
*
*
*  General Purpose
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  InputData/File                   | Category        | RC  | Comments
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  autorised.CATCX_MEMORY           | Memory Leaks    | 77  |  Embedded CGM memory leaks detection at exit
*      |                                   |                 |     |    (thanks to the popular memory manager override)
*      |                                   |                 |     |  The detection of inputdata file implied
*      |                                   |                 |     |    automatic control for all ODT of framework
*      |                                   |                 |     |  Content of inputdata file allows CGM leaks
*      |                                   |                 |     |    with ODTNAME allowed cardinality of CGM objets leaked
*      +-----------------------------------+-----------------+-----+------------------------------------------------------
*      |  Authorized.CATCX_CGM_CHECK_CLEAN | Data Checker    |     | Check if the failure ODT/Case is "Authorized" to pass!
*      |                                   |                 |     | Do we consider check "authorization"?
*      |                                   |                 |     |   Following file would need to be present if we need to consider check "authorization" tables (entries of ODT/Case)
*      |                                   |                 |     |   FWName/FunctionTests/InputData/"Authorized.CATCX_CGM_CHECK_CLEAN"
*      |                                   |                 |     | Create the "authorized" table name:
*      |                                   |                 |     |   e.g. For rule PCE_1:  following file would have "authorized" ODT/Case entries
*      |                                   |                 |     |   FWName/FunctionTests/InputData/Authorized/"PCE_1.txt"
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  Authorized.CATCX_CHECKUP         | Topo CheckUp    | 66  | Topological Check-Up behave with higher severity
*      |                                   |                 |     |   about intermediate severity so-called "PotDeVin"
*      |                                   |                 |     | The input
*      |                                   |                 |     |
*      +-----------------------------------+-----------------+-----+-----------------------------------------
*
*  Specific Purpose
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  InputData/File                   | Category        | RC  | Comments
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  Authorized.CATGeoControl         | Optimized Data  |     | Control of extrapolation impact over geometry bytes size,
*      |                                   |                 |     |    stability is controlled thanks to these measures.
*      |                                   |                 |     | Originated with a problematic on amount of geometrical data
*      |                                   |                 |     |   (see CATDUA integration with FAT_**  data optimizer)
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  Authorized.CATCX_FREEZE          | Behavior Check  |     | Levee d'exeption sur changement de definition
*      |                                   |                 |     |  sur une modelisation dite "Frozen"
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*      |  Authorized.Tolerances            |                 |     |
*      |                                   |                 |     |
*      +-----------------------------------+-----------------+-----+-----------------------------------------------------
*
* 
* ----------------------------------------------------------------------------------------------------------------------
*/

#include <stddef.h>
#include <stdlib.h>

#include "CATMathematics.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATCGMemoryPOOL;
class CATCGMNewMetaBloc;
class CATCGMOutput;
class CATCGMMutex;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ifstream;
#endif

#include "CATMathAuthODTStatus.h"
#include "CATMathInline.h"
#include "CATCGMemoryProvider.h"
#include "CATLib.h"
#include "CATechSetup_Domain.h"


class CATCGMLibraryInformation;
class CATHashTabCATCGMLibraryInformation;
class CATUnicodeString;
class CATCGMOperator;
class CATechSetOfChar;
class CATCGAMeasure;
class CATMathODTCGM;

typedef unsigned int CATMathODT_DumpMemoryManagement;

#define CATMathODT_DumpMemoryManagement_Global        0x00000001
#define CATMathODT_DumpMemoryManagement_Class         0x00000002
#define CATMathODT_DumpMemoryManagement_Leaks         0x00000004
#define CATMathODT_DumpMemoryManagement_Ressources    0x00000008
#define CATMathODT_DumpMemoryManagement_FormatMeasure 0x00000010


/**
 *  Small tool-kit helpers for enhanced CGM validation build-in tests.
 */
class ExportedByCATMathematics CATMathODT
{
public:

  /**
   * IsAvailable : detect correct availability of service
   *
   *   loadable CATMathStream shared-lib
   *   && (     ODT   (Exeption PerformanceCapacityScalability ODT, PerfOnly_ exeption if CATCX_MEMORY set)  )
   *        ||  Debug (EnvironnementVariable CATDevelopmentStage=TRUE && Packaging loadable CATCgmDebugMath) )
   *
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  INLINE static short IsAvailable();

    /**
   * GetScenario :  
   *
   * @param oScenarioName
   *   Get current scenario name.
   *
   * @return
   *      TRUE   if scenario defined<br>
   *      FALSE  if scenario undefined<br>
   */
  INLINE static CATBoolean GetScenario(CATUnicodeString & oScenarioName);
 
  /**
   * SetScenario :  
   *
   * @param iScenarioName
   *   set current scenario name.
    *
   * @return
   *      TRUE   if scenario defined<br>
   *      FALSE  if scenario undefined<br>
  */
  INLINE static CATBoolean SetScenario(const CATUnicodeString & iScenarioName);

 

  /**
   * GetCurrentScenarioNumber : Gets current scenario number
   *
   * @return
   *      current scenario number
   */
  INLINE static int GetCurrentScenarioNumber(); 



  /**
   * See @href CATCGMIsAuthorized#HardTreatment
   */
  INLINE static CATBoolean HardTreatment(const char       *suffix,
                                         const CATBoolean  DefaultMeansHard,
                                         size_t           *pMaximalValue = NULL,
                                         const CATBoolean  iWithScenarioName = FALSE,
                                         const CATBoolean  iAsDirectory = FALSE);

  /**
   * This methods looks for a line in the file TstFw/InputData/Authorized.xxx or TstFw/InputData/Authorized/xxx
   * that matches the ODT name and it returns the associated value.
   * @param suffix
   *   Suffix for the file name (xxx).
   * @param oValue
   *   The value read in the file.
   * @param iWithScenarioName
   *   TRUE  -> the line in the file must contain <ODT>/<Scenario>
   *   FALSE -> the line in the file must contain <ODT>
   * @param iAsDirectory
   *   TRUE  -> the file is TstFw/InputData/Authorized/xxx
   *   FALSE -> the file is TstFw/InputData/Authorized.xxx
   * @return
   *   See @href CATMathAuthODTStatus
   */
  INLINE static CATMathAuthODTStatus ODTIsAuthorized(
    const char *suffix,
    double &oValue,
    CATBoolean iWithScenarioName = FALSE,
    CATBoolean iAsDirectory = FALSE);

  /**
   * See @href CATCGMIsAuthorized#FrameworkWithHardTreatment
   */
  INLINE static CATBoolean FrameworkWithHardTreatment(const char        *iSuffix,
                                                      ifstream          *pInputData = NULL,
                                                      const CATBoolean   iAsDirectory = FALSE );

  /**
   * ExitForODT : request for abnormal exit return code
   *
   *   See CATCGMExitForODT
   *
   * @param iStatus
   *   Value of exepected returned Code
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static void ExitForODT( const int iStatus);


  /**
   * DumpRessources :
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static void DumpRessources(const char       iMessageDelta[],
                             ostream         &iosDump,
                             const CATBoolean iDumpAnalysis,
                             const CATBoolean iManageDelta  = TRUE,
                             const CATBoolean iForConsole = FALSE);
  /**
   * DumpGMemory :
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  static void DumpGMemory(const char       iMessageDelta[],
                             CATechSetOfChar         &iosDump,
                             const CATBoolean iDumpAnalysis,
                             const CATBoolean iManageDelta  = TRUE,
                             const CATBoolean iForConsole = FALSE);
 

  //---------------------------------------------------------------------------
  // DumpLoadedLibraries
  //---------------------------------------------------------------------------
  //
  // iSelectedLibraries = 0 : all
  //                      1 : only DS
  //                      2 : only CGM
  //                      etc...
  //
  //       iSortingMode = 0 : by path/name
  //                      1 : by name
  //                      2 : by size
  //                      3 : by address
  //
  // iLibraryDetailFLAG = Bit 0 : no details
  //                      Bit 1 : library header
  //                      Bit 2 : library import section : library list
  //                      Bit 3 : library import section : symbol table
  //                      ...
  //
  static void DumpLoadedLibraries(ostream& iosDump, int iSelectedLibraries = 0, int iSortingMode = 0,
                                  unsigned char iLibraryDetailFLAG = 0, CATBoolean iDumpAddr = TRUE);
  static void DumpLinkedLibraries(ostream&                            iosDump,
                                  CATCGMLibraryInformation*           ipLibraryInfo,
                                  CATHashTabCATCGMLibraryInformation& iHashTabAllLibInfos,
                                  int                                 iSelectedLibraries = 0,
                                  CATBoolean                          iDumpSymbols = FALSE,
                                  CATBoolean                          iDumpAddr = TRUE);
  static void DumpLibraryDetails(ostream& iosDump, CATCGMLibraryInformation* ipLibraryInfo, unsigned char iLibraryDetailFLAG = 0);

  //---------------------------------------------------------------------------
  // DumpMemory
  //---------------------------------------------------------------------------
  INLINE static ostream & DumpMemory(ostream &logstat, const CATMathODT_DumpMemoryManagement iManage );
  static void      DumpGMCXMemory(CATechSetOfChar  &iDump, const CATMathODT_DumpMemoryManagement iManage );

  //---------------------------------------------------------------------------
  // MayBeHelpFull
  //---------------------------------------------------------------------------
  INLINE static ostream * MayBeHelpFull();
  INLINE static void  SetStatusMode(short on_or_off);
  INLINE static ostream * HelpFullConvert(CATCGMOutput& os);
  INLINE static const char *Get_CATCX_MEMORY_Log();

    //---------------------------------------------------------------------------
  // CATCGMemoryPOOL (internal)
  //---------------------------------------------------------------------------
  INLINE static void lognew(CATCGMemoryPOOL *iPool, double *current, CATCGMNewMetaBloc *myClass);
  INLINE static void logdel(CATCGMemoryPOOL *iPool, double *current, CATCGMNewMetaBloc *myClass);


  //---------------------------------------------------------------------------
  // CATCGMMutex
  //---------------------------------------------------------------------------
  INLINE static CATCGMMutex *NewMutex();
  INLINE static void DelMutex(CATCGMMutex *&iMutex);
  INLINE static void Lock(CATCGMMutex *iMutex);
  INLINE static void Unlock(CATCGMMutex *iMutex);

  INLINE static short IsAlreadyAvailable();
  //---------------------------------------------------------------------------
  // IsForceDebug
  //---------------------------------------------------------------------------
  INLINE static short IsForceDebug();

  /**
  * @deprecated  
  */
  INLINE static const char *GetCurrentScenario(size_t *pLgrScenario = NULL);

  /**
  * @deprecated  
  */
  INLINE static void SetCurrentScenario(const char *iCurrentScenario);

  /**
  * @nodoc  
  */
  INLINE static void FlushCGMtkJournaling();

  // catcgmmultirun 

  /**
  * @nodoc  
  */
  INLINE static void Pop_catcgmmultirun(const CATUnicodeString & iNameId, CATCGMOperator *iOp, const int  iNumberOfRun);   

  /**
  * @nodoc  
  */
  INLINE static void Flush_catcgmmultirun();

  /**
  * @nodoc  
  */
  //-----------------------------------------------------------------------------
  // Retourne le numero d'une variable de versionning en fonction de son nom.
  // Retourne 0 si la variable donnée n'existe pas.
  //-----------------------------------------------------------------------------
  INLINE static short Get_CGMVersionNumber(const char* versionString);
  INLINE static char *Get_CGMVersionString(const short versionNumber);

  /**
  * @nodoc  
  */
  INLINE static CATBoolean IsJournalingActivated(CATechSetup_Domain iDomain = CATechSetup_Factory);


  //---------------------------------------------------------------------------
  // nbmaxAutorised
  //---------------------------------------------------------------------------
  static int nbmaxAutorised();


protected :
  //---------------------------------------------------------------------------------
  // Pour gestion interne
  //---------------------------------------------------------------------------------
  CATMathODT();
  virtual ~CATMathODT();

  static  void       DumpProvider(CATechSetOfChar  &iDump,  CATCGMemoryProvider provider);

  //---------------------------------------------------------------------------
  // CATCGMemoryPOOL (internal)
  //---------------------------------------------------------------------------
  static void FinalExit( const int RequestedRC );

  static void SortieFinale(int &ioRequestedRC);

 
  //-----------------------------------------------------------
  // Management of the log of CATCGMError
  //-----------------------------------------------------------
  INLINE static void ThreadManager_End();

  /**
   * See @href CATCGMIsAuthorized#HardTreatment
   */
  virtual CATBoolean _HardTreatment(const char       *suffix,
                                    const CATBoolean  DefaultMeansHard,
                                    size_t           *pMaximalValue = NULL,
                                    const CATBoolean  iWithScenarioName = FALSE,
                                                      const CATBoolean  iAsDirectory = FALSE) = 0;

  /**
   * See @href CATMathODT#ODTIsAuthorized
   */
  virtual CATMathAuthODTStatus _ODTIsAuthorized(
    const char *suffix,
    double &oValue,
    CATBoolean iWithScenarioName = FALSE,
    CATBoolean iAsDirectory = FALSE) = 0;

  /**
   * See @href CATCGMIsAuthorized#FrameworkWithHardTreatment
   */
  virtual CATBoolean _FrameworkWithHardTreatment(const char  *suffix, ifstream *pInputData = NULL,
                                                      const CATBoolean  iAsDirectory = FALSE ) = 0;
 
  //---------------------------------------------------------------------------
  // CATCGMemoryPOOL
  //---------------------------------------------------------------------------
  virtual void _lognew(CATCGMemoryPOOL *iPool, double *current, CATCGMNewMetaBloc *myClass)= 0;
  virtual void _logdel(CATCGMemoryPOOL *iPool, double *current, CATCGMNewMetaBloc *myClass)= 0;

  //---------------------------------------------------------------------------
  // DumpMemory
  //---------------------------------------------------------------------------
  virtual ostream & _DumpMemory(ostream &logstat, const CATMathODT_DumpMemoryManagement iManage ) = 0;

  //---------------------------------------------------------------------------
  // MayBeHelpFull
  //---------------------------------------------------------------------------
  virtual ostream * _MayBeHelpFull()= 0;
  virtual void      _SetStatusMode(short on_or_off)= 0;
  virtual ostream * _HelpFullConvert(CATCGMOutput& os) = 0;
  virtual const char *_Get_CATCX_MEMORY_Log() = 0;

  //---------------------------------------------------------------------------
  // CATCGMMutex
  //---------------------------------------------------------------------------
  virtual CATCGMMutex *_NewMutex() = 0;
  virtual void _DelMutex(CATCGMMutex *&iMutex) = 0;
  virtual void _Lock(CATCGMMutex *iMutex) = 0;
  virtual void _Unlock(CATCGMMutex *iMutex) = 0;
  virtual void _ThreadManager_End() = 0;

  virtual void _FlushCGMtkJournaling()= 0;

  virtual void _Flush_catcgmmultirun()= 0;
  virtual void _Pop_catcgmmultirun(const CATUnicodeString & iNameId, CATCGMOperator *iOp, const int  iNumberOfRun) = 0;
 
  /**
  * @nodoc  
  */
  virtual CATBoolean _IsJournalingActivated(CATechSetup_Domain iDomain)= 0;



  /**
  * @nodoc  
  */
  //-----------------------------------------------------------------------------
  // Retourne le numero d'une variable de versionning en fonction de son nom.
  // Retourne 0 si la variable donnée n'existe pas.
  //-----------------------------------------------------------------------------
  virtual  short _Get_CGMVersionNumber(const char* versionString) = 0;
  virtual  char *_Get_CGMVersionString(const short versionNumber) = 0;

  static short       _ForceDebug;



private :

  /**
   * DumpGMemoryForConsole :
   */
  static void DumpGMemoryForConsole(const char       iMessageDelta[], CATechSetOfChar         &iosDump,
     const CATBoolean iDumpAnalysis,  const CATBoolean iManageDelta  = TRUE, const CATBoolean iForConsole = FALSE);



  //---------------------------------------------------------------------------
  // Acces a l'init
  //---------------------------------------------------------------------------
  static CATMathODT *GetMathODT();

  static CATMathODT *_Debug;
  static short       _Once;

  static CATUnicodeString  _ScenarioName;
  static CATBoolean        _ScenarioValid;

  static int         _ScenarioNumber;

  friend class CATCGMemoryPOOL;
  friend class CATCGAMeasure;
  friend class CATMathODTCGM;
  
};

//-----------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------
INLINE short CATMathODT::IsAvailable()
{
  return ( (_Once || GetMathODT()) && _Debug ) ? 1 : 0;
}

INLINE short CATMathODT::IsAlreadyAvailable()
{
  return _Debug ? 1 : 0;
}


/**
* GetScenario :  
*
* @param oScenarioName
*   Get current scenario name.
*
* @return
*      TRUE   if scenario defined<br>
*      FALSE  if scenario undefined<br>
*/
INLINE CATBoolean CATMathODT::GetScenario(CATUnicodeString & oScenarioName)   
{
  if ( _ScenarioValid )
    oScenarioName = _ScenarioName;
  else
    oScenarioName = CATUnicodeString();
  return _ScenarioValid;
}

/**
* SetScenario :  
*
* @param iScenarioName
*   set current scenario name.
*
* @return
*      TRUE   if scenario defined<br>
*      FALSE  if scenario undefined<br>
*/
INLINE CATBoolean CATMathODT::SetScenario(const CATUnicodeString & iScenarioName) 
{
  if ( iScenarioName.GetLengthInChar() > 0 )
  {
    _ScenarioValid = TRUE;
    _ScenarioName = iScenarioName;
    _ScenarioNumber++;
  }
  else
  {
    _ScenarioValid = FALSE;
    _ScenarioName = CATUnicodeString();
  }
  return _ScenarioValid;
}



//---------------------------------------------------------------------------
// Current scenario number
//---------------------------------------------------------------------------
INLINE  int CATMathODT::GetCurrentScenarioNumber()
{
 return  _ScenarioNumber;
}



//---------------------------------------------------------------------------
// Gestion des ODTS CGM et de la transaction d'un scenario
//---------------------------------------------------------------------------
INLINE const char *CATMathODT::GetCurrentScenario(size_t *pLgrScenario)
{
  if ( _ScenarioValid )
  {
    const char * pName   = _ScenarioName.ConvertToChar() ;
    size_t       lgrName = _ScenarioName.GetLengthInByte();
    if ( lgrName > 255 ) lgrName = 255;

    static char LocalName[256];
    strncpy(LocalName,pName,lgrName);
    LocalName[lgrName] = '\0'; 

    if  (pLgrScenario) (*pLgrScenario) = lgrName;
    return LocalName;
  }

  if  (pLgrScenario) (*pLgrScenario) = 0;
  return NULL;
}

//---------------------------------------------------------------------------
// Reserved for Internal Use (CGMTestToolkit.tst)
//---------------------------------------------------------------------------
INLINE void CATMathODT::SetCurrentScenario(const char *CurrentScenario)
{
  if ( CurrentScenario )
  {
    _ScenarioValid = TRUE;
    _ScenarioName = CATUnicodeString(CurrentScenario);
    CATMathODT::_ScenarioNumber++;
  }
  else
  {
    _ScenarioValid = FALSE;
    _ScenarioName = CATUnicodeString();
  }
}


 
//-----------------------------------------------------------
// CATCGMIsAuthorized
//-----------------------------------------------------------
INLINE CATBoolean CATMathODT::HardTreatment(const char       *suffix,
                                            const CATBoolean  DefaultMeansHard,
                                            size_t           *pMaximalValue,
                                            const CATBoolean  iWithScenarioName,
                                            const CATBoolean  iAsDirectory)
{
  if (pMaximalValue) (*pMaximalValue) = 0x7FFFFFFF;
  if ( (_Once || GetMathODT()) && _Debug )
     return _Debug->_HardTreatment(suffix,DefaultMeansHard,pMaximalValue,iWithScenarioName,iAsDirectory);
  return DefaultMeansHard;
}

INLINE CATMathAuthODTStatus CATMathODT::ODTIsAuthorized(
  const char *suffix,
  double &oValue,
  CATBoolean iWithScenarioName,
  CATBoolean iAsDirectory)
{
  if ( (_Once || GetMathODT()) && _Debug )
     return _Debug->_ODTIsAuthorized(suffix, oValue, iWithScenarioName, iAsDirectory);
  return CATMathAuthODTStatusNotFound;
}

INLINE CATBoolean CATMathODT::FrameworkWithHardTreatment(const char  *suffix,
                                                         ifstream *pInputData,
                                                         const CATBoolean  iAsDirectory)
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_FrameworkWithHardTreatment(suffix,pInputData,iAsDirectory);
  return FALSE;
}


//---------------------------------------------------------------------------
// CATCGMemoryPOOL
//---------------------------------------------------------------------------

INLINE void CATMathODT::lognew(CATCGMemoryPOOL *iPool, double *current, CATCGMNewMetaBloc *myClass)
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_lognew(iPool,current,myClass);

}
INLINE void CATMathODT::logdel(CATCGMemoryPOOL *iPool, double *current, CATCGMNewMetaBloc *myClass)
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_logdel(iPool,current,myClass);
}

//---------------------------------------------------------------------------
// CATCGMPageAllocator
//---------------------------------------------------------------------------
INLINE ostream & CATMathODT::DumpMemory(ostream &logstat, const CATMathODT_DumpMemoryManagement iManage)
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_DumpMemory(logstat,iManage);
  return logstat;
}
 


//---------------------------------------------------------------------------
// MayBeHelpFull
//---------------------------------------------------------------------------
INLINE ostream * CATMathODT::MayBeHelpFull()
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_MayBeHelpFull();
  return NULL;
}

//---------------------------------------------------------------------------
// IsJournalingActivated
//---------------------------------------------------------------------------
INLINE CATBoolean CATMathODT::IsJournalingActivated(CATechSetup_Domain iDomain)
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_IsJournalingActivated(iDomain);
  return FALSE;
}

 
//---------------------------------------------------------------------------
// HelpFullConvert
//---------------------------------------------------------------------------
INLINE ostream * CATMathODT::HelpFullConvert(CATCGMOutput& os)
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_HelpFullConvert(os);
  return NULL;
}

//---------------------------------------------------------------------------
// SetStatusMode
//---------------------------------------------------------------------------
INLINE void CATMathODT::SetStatusMode(short on_or_off)
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_SetStatusMode(on_or_off);
}

//---------------------------------------------------------------------------
// Get_CATCX_MEMORY_Log
//---------------------------------------------------------------------------
INLINE const char * CATMathODT::Get_CATCX_MEMORY_Log()
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_Get_CATCX_MEMORY_Log();
  return NULL;
}

INLINE short CATMathODT::Get_CGMVersionNumber(const char* versionString)
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_Get_CGMVersionNumber(versionString);
  return 0;
}

INLINE char * CATMathODT::Get_CGMVersionString(const short versionNumber)
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_Get_CGMVersionString(versionNumber);
  return NULL;
}
 

//---------------------------------------------------------------------------
// CATCGMMutex
//---------------------------------------------------------------------------
INLINE CATCGMMutex* CATMathODT::NewMutex()
{
  if ( (_Once || GetMathODT()) && _Debug ) return _Debug->_NewMutex();
  return NULL;
}

INLINE void CATMathODT::DelMutex(CATCGMMutex *&iMutex)
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_DelMutex(iMutex);
}

INLINE void CATMathODT::Lock(CATCGMMutex *iMutex)
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_Lock(iMutex);
}

INLINE void CATMathODT::Unlock(CATCGMMutex *iMutex)
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_Unlock(iMutex);
}

INLINE void CATMathODT::ThreadManager_End()
{
  if ( (_Once || GetMathODT()) && _Debug ) _Debug->_ThreadManager_End();
}

INLINE void CATMathODT::FlushCGMtkJournaling()
{
  if ( (_Once || GetMathODT()) && _Debug )  _Debug->_FlushCGMtkJournaling();
}

INLINE void CATMathODT::Flush_catcgmmultirun()
{
  if ( (_Once || GetMathODT()) && _Debug )  _Debug->_Flush_catcgmmultirun();
}

INLINE void CATMathODT::Pop_catcgmmultirun(const CATUnicodeString & iNameId, CATCGMOperator *iOp, const int  iNumberOfRun)
{
  if ( (_Once || GetMathODT()) && _Debug )  _Debug->_Pop_catcgmmultirun(iNameId,iOp,iNumberOfRun);
}
 

//---------------------------------------------------------------------------
// IsForceDebug
//---------------------------------------------------------------------------
INLINE short CATMathODT::IsForceDebug()
{
  return _ForceDebug;
}


#endif
