#ifndef CATechSetup_h
#define CATechSetup_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    GMTk journaling idea is to record and collect an history of operations 
*        as data meaningfull for a GM support in either one zip auto-described file or either in one dedicated directory of files.
*        those previous data are able to be replay the initial in an equivalent manner.
*     Remarks 1) not all GM operations have yet implemented an integration in GMTkJournaling mecanisms (with underlining CGMReplay file).
*     Remarks 2) GMTkJournaling is also gathering information about scenarios
*                   (some statistics on I/O operations, or intermediate operation data (CATCX_NCGM))
* 
*   About some known limitations : structure of zip (or directory) may changed at any software iteration.
*       -each type of file has its own data compatibility management (NCGM,CGMReplay)
*       -CSV file has no defined compatibility management 
* 

1)	What is CGMTkJournaling technology ?
       CGMTkJournaling is a collaboration tool aims to ease support 
               between an application software and prerequisite GM functionalities with developers ready to provide answers.
       CGMTkJournaling main purpose is to enable partial replay of scenario  
              by a set of stand-alone (generally one shot run) GM operations.
       CGMTkJournaling is technics based on data exchange (self described zip file suffixed *.CATechSet.zip)
              rather than software sample extractions,
               this is a result of complex objects and algorithms underlining the running operations.

2)	What is old about CGMTkJournaling technology  ?
       CGMTkJournaling incorporates traces of previous technological tools
            "CATCX_NCGM" (1998) for some services (3D Boolean CutBodies for instance)
            "CGMReplay" (2000) for CGM operators
            "CATPhoenix" (2008) for some mesh operations (but with very partial restrictive reuse)

      CGMTkJournaling address data which can be attached documents in maintenance, but does not address at all
            internal debugging introspection (checkpoint, textual or graphical representations)
            internal delivery process (ODT referential, checking inputs and outputs, …) 

3)	What is new about CGMTkJournaling technology ?

     Functionnality is provided through A.P.I (small S.D.K, see chapter 5) 
         -> no more any environnement variable.
         -> for internal GM, interactive functionnality is demonstated through c:cgm\S.O.S 
          
     CGMTkJournaling captures as all-in-one set  the heterogeneous history of events/operations
          -> conceptual interfaces has been developed to capture the generalization to make it simple to use.

     CGMTkJournaling runs from commercial packaging 
         -> it induces some limitations:
              as legacy Debug NCGM,CGMReplay workbench unavailable
              as Visualisation A.P.I are not available to make a presentation of result
              as XML parser is under debate 

4)	What are provided materials ?
              
     CGMtkJournalingWriter.cpp :  it shows simply how journaling is start/stop/save/empty from an in-process management
           (Data_Site.tst\CATCGMtkJournalingWriter.m\src\CGMtkJournalingWriter.cpp)

     CGMtkJournalingReader.cpp :  it shows how stored journaling is recovered and replayed again
           (TopologicalOperators\CATCGMtkJournalingReader.m\src\CGMtkJournalingReader.cpp)

5)	zip and directory 

   
    A  small (as seamless as possible) PlayBack physical representation is expected  in Friday CGMOFF/CGMPRJ collect (so week 13 of 2011 for developers)
        In fact for synchronous recording, the directory of files will be default representation rather than the zip file. 
        It should have no direct impact on A.P.I usage.

     This evolution was motivated by Performance criteria of synchronous recording 
             (less working set footprint and less I/O operations at each synchronous save)


     the zip self contained file is preferred for error-prone manipulation (file transfer),
       whereas the directory of files is more efficient for synchronous recording (differential I/O and less working set).

     the suffix of zip or directory containing GM Playback is normalized according to the following rules :
              JohnDoe.PlayBack.zip : filename of PlayBack
              JohnDoe.PlayBack     : directory of files associated to one 

     However no matter the physical representations (zip of directory) for Playback
     
        the PlayBack S.D.K and Open/Save A.P.I treats in the same way the two representations,
          you just have to specify the extended filename "...JohnDoe" without suffix,
          it is automatically normalized and in case of ambiguity, the zip file is first searched before directory.
 
           
        zip file and directory of files representation can be very easily converted in each other,
        as for instance with the 7-Zip file archiver 
            "C:\Program Files\7-Zip\7z.exe" a JohnDoe.PlayBack.zip JohnDoe.PlayBack\*
            "C:\Program Files\7-Zip\7z.exe" e JohnDoe.PlayBack.zip -oJohnDoe.PlayBack

  

*/
//-------------------------------------------------------------------------------------------------
//   Event (and optionnally Data) GM's Collector 
//-------------------------------------------------------------------------------------------------
#include "ExportedByCATTechTools.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATechMeta.h"
#include "CATMathInline.h"
#include "CATechGet.h"
#include "CATHashDico.h"
#include "CATLISTV_CATechGet.h"
 
class CATMathODTCGM;
class CATechExt;
class CATechSet;
class CATechAttribute;
#define CATechSetup_ApplicativeStack 64



/** 
*  Utility for collecting GM events and data during an unspecified interval of times
*  Monitor  CGMTk Journaling usage .
*/

class  ExportedByCATTechTools CATechSetup
{ 
public :
 

  //-------------------------------------------------------------------------------------------------
  // Public A.P.I for GMtk journaling
  //-------------------------------------------------------------------------------------------------


  /** 
   * Activates "asynchronous" GMtk journaling recording of forecoming GM events/operations.
	 * Previous current list of events/Operations is emptied if this list exits.
	 * recording is kept in memory and requires an explicit save.
  */           
  static void   ActivateJournaling(const char *pOutputZip = NULL) ;

  /** 
    * Activates "synchronous" recording of forecoming GM events/operations.
    * @param iOutputZipFileName
    *  filename of record which is overwrite for each event. 
	  *  recording is kept in a current list in memory  .
  */           
  static void   ActivateSynchronousJournaling(const CATUnicodeString & iOutputZipFileName) ;


  /** 
  *  Stops recording of events/operations.
	 * @param iEmptyBuffer
	 *    if <tt>TRUE</tt> previous current list of events/Operations is emptied  .
  */           
  static void   StopJournaling(CATBoolean iEmptyBuffer) ;

  /** 
  *  Access current list events/operations associated to the recording mode.  
  *   if recording is activated and list not yet initialized, the list is created.
	*   Returns the <tt>CATechSet</tt> which owns list of events/Operations.
  */           
  static CATechSet *GetPlackBackForRecording() ;


  /** 
  * Empty from memory the current list of events/Operations.
  */ 
  static HRESULT  EmptyJournaling( );

 
  /** 
   * Save on OutputZip current buffer 
   *
	 * @param iOutputZipFileName
	 *    if <tt>TRUE</tt> previous current list of events/Operations is emptied  .
   *
   * @return
   *      S_OK   if request succeeded <br>
   *      E_FAIL if request failed <br>
   */           
  INLINE static HRESULT  SaveOutputZip( const CATUnicodeString & iOutputZipFileName );


  /** 
   *  Access current list events/operations   
   *   if recording is activated and list not yet initialized, the list remains null.
   *   if replayind mode .
  */           
  static CATechSet *GetCurrentJournaling() ;

 
  /** 
  * NormalizeSuffix 
   *
	 * @param iOutputZipFileName
	 *    filename to be normalized with PlayBack suffix.
   *
   *
	 * @param oOutputZipFileName
	 *    filename normalized with PlayBack suffix.
   *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  static HRESULT NormalizeSuffix( const CATUnicodeString & iOutputZipFileName, CATUnicodeString & oOutputZipFileName );


  /** 
   * OpenZip
   *
	 * @param iOutputZipFileName
	 *    filename containing a recorded list of events/operations.
   *
	 * @param iSetAsCurrentJournaling
	 *    if <tt>TRUE</tt> previous current list of events/Operations is emptied  .
   *
	*   Returns the <tt>CATechSet</tt> which owns list of events/Operations.
  */ 
  static CATechSet *  OpenZip( const CATUnicodeString & iOutputZipFileName , const CATBoolean iSetAsCurrentJournaling = TRUE );


  /** 
   * OpenZip
   *
	 * @param iInputZipFileName
	 *    filename containing a recorded list of events/operations.
   *
	 * @param oResult
	 *    List of <tt>CATechSet</tt> which owns list of events/Operations .
   *
	*   Returns  .
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT      OpenZip( const CATUnicodeString & iInputZipFileName , CATLISTV(CATechGet_var) & oResult);


  /** 
   * OpenZip
   *
	 * @param iOutputZipFileName
	 *    filename containing a recorded list of events/operations.
   *
	 * @param iSetAsCurrentJournaling
	 *    if <tt>TRUE</tt> previous current list of events/Operations is emptied  .
   *
	*   Returns the <tt>CATechSet</tt> which owns list of events/Operations.
  */ 
  static CATechSet *  OpenZipWithOpenConfigurations( const CATUnicodeString & iOutputZipFileName , const CATBoolean iSetAsCurrentJournaling = TRUE );

  /** 
   * OpenZipWithOpenConfigurations
   *
	 * @param iInputZipFileName
	 *    filename containing a recorded list of events/operations.
   *
	 * @param oResult
	 *    List of <tt>CATechSet</tt> which owns list of events/Operations .
   *
	 * @param ifOnlyOneSetAsCurrentJournaling
	 *    if <tt>TRUE</tt> previous current list of events/Operations is emptied  .
   *
   *   Returns  .
   *      S_OK   if request succeeded <br>
   *      E_FAIL if request failed <br>
  */ 
  static HRESULT      OpenZipWithOpenConfigurations( const CATUnicodeString  & iInputZipFileName , 
                                                     CATLISTV(CATechGet_var) & oResult ,
                                                     const CATBoolean          ifOnlyOneSetAsCurrentJournaling = TRUE );

 

  /** 
   * Predefines a filename for the playback file (used for implicit asynchronous and save operations).
   *
	 * @param iOutputZipFileName
	 *    predefined filename for saving the current list of recording mode.
   *
 */ 
  static void  SetOutputZip( const CATUnicodeString & iOutputZipFileName );

 /** 
   * Access current  filename for the playback file (used for implicit asynchronous and save operations).
   *
	 * @param oOutputZipFileName
	 *    predefined filename for saving the current list of recording mode.
  *
  * @return
  *      S_OK   if oOutputZipFileName has been defined  <br>
  *      E_FAIL otherwise <br>
  */           
  INLINE static HRESULT GetCurrentOutputZip(  CATUnicodeString & oOutputZipFileName );


 /** 
   * Access current  filter of contents by id when recording playback file .
   *
	 * @param oKeepName
	 *    predefined filename for saving the current list of recording mode.
  *
  * @return
  *      S_OK   if oKeepName has been defined  <br>
  *      E_FAIL otherwise <br>
  */       
  INLINE  static HRESULT WithKeepName(  CATUnicodeString & oKeepName ) ;


  /** 
  * Save Current list of events/operations in filename  
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  Save( );
 

  /** 
  *  Empty current list of events/operations 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  UnsetCurrentJournaling( );



  //-------------------------------------------------------------------------------------------------
  // Intermediate (reserved for futur Usage)  A.P.I for GMtk journaling
  //-------------------------------------------------------------------------------------------------


  /** 
  * @nodoc 
   *
 *  activates explicitly GM events collecting  
  *
  * @param iOptions.
  *          Define domains which are activated for debug purpose
 */           
  static void   ActivateJournaling(CATechAttribute  *iOptions) ;


  /** 
  * @nodoc 
   *
  *   check if GM events collecting is activated
  * @param iDomain.
  *          Define domains which are activated for debug purpose
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  INLINE static HRESULT  IsJournalingActivated(CATechSetup_Domain iDomain) ;

  /** 
  * @nodoc 
 */           
  static CATechAttribute  *  GetCurrentApplicativeStack();

 
  /** 
  *  Convert from  OperatorId to InterfaceId
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed (same Id) <br>
  */           
  static HRESULT  GetInterfaceId( const CATUnicodeString & iOperatorId, CATUnicodeString & oInterfaceId);

  
  /** 
  *  Transient Logging Convergence HasBeenIdentifiedAsUncomplete
  *
  * @return
  *      S_OK   if Has Been Identified As Uncomplete <br>
  *      E_FAIL if request failed (same Id) <br>
  */           
  static CATBoolean  HasBeenIdentifiedAsUncomplete( const CATUnicodeString & iOperatorId);
 
    
  /** 
  *  Filtering type of operators
  *
  * @return
  *      TRUE   Filtered (Explicit) <br>
  *      FALSE    <br>
  */           
  static CATBoolean  ExplicitFiltering( const char *iOperatorName);

  /** 
  *  CATMathODTCGM_Folder
  */           
  static void  CATMathODTCGM_Folder( const CATUnicodeString & iOperatorId, const CATUnicodeString & iFolder );
  
  /** 
  *  Recording_Error
  */           
  static void  Recording_Error( const CATUnicodeString & iOperatorId, CATBoolean iRecording );
 
  //-------------------------------------------------------------------------------------------------
  // Internal management of GMtk journaling
  //-------------------------------------------------------------------------------------------------

  /** 
  *  CATCGMReplay_WithPushPop
  */           
  static CATBoolean  CATCGMReplay_WithPushPop( );
  /** 
  *  CATCGMReplay_Push (return TRUE if already push as TRUE
  */           
  static CATBoolean  CATCGMReplay_Push( const CATUnicodeString & iOperatorId,  const CATBoolean iWithPreliminary );
 
  /** 
  *  CATCGMReplay_Push
  */           
  static void  CATCGMReplay_Pop( );

  //-------------------------------------------------------------------------------------------------
  // Internal management of GMtk journaling
  //-------------------------------------------------------------------------------------------------

  /** 
  * @nodoc 
  */ 
  static HRESULT  SynchronousFromDirectoryToZip( );

  /** 
  * @nodoc 
  */ 
  static HRESULT  SynchronousUpdateFromDirectoryToZip( );

  /** 
  * @nodoc 
  */
  static HRESULT CreateSetUpDirectory(CATUnicodeString &pioCATechSetup_Directory);

  /** 
  * @nodoc 
  Externals for GMtk 
  */ 
  INLINE static const CATechMeta & CGMOperator();   
  INLINE static const CATechMeta & PolyOperator();   
  INLINE static const CATechMeta & CDSComponent();   

  INLINE static const CATechMeta & OutputZip();  // Output Directory
  INLINE static const CATechMeta & MinimalWithoutOutputs();  // Output Directory
  
  INLINE static const CATechMeta & Completion(); 
  INLINE static const CATechMeta & Factory();  
  INLINE static const CATechMeta & ExtCGMOperator();   

  INLINE static const CATechMeta & Exclude();   


  INLINE static const CATechMeta & WithDataLink();  
  INLINE static const CATechMeta & KeepName();  // Output Directory
  INLINE static const CATechMeta & AvoidSameName(); 
  INLINE static const CATechMeta & CATCX_NCGM(); 
  INLINE static const CATechMeta & KeyOne(); 
  INLINE static const CATechMeta & KeyTwo(); 
  INLINE static const CATechMeta & KeyThree(); 
  INLINE static const CATechMeta & MappingResult(); 
  INLINE static const CATechMeta & NestedEvent(); 
 
  INLINE static const CATechMeta & IndexValue(); 
  INLINE static const CATechMeta & Dummy_NoValue(); 

 
  /** 
  * @nodoc 
  Internals for GM developpers
  */ 
  INLINE static const CATechMeta &  Domain(); // 

  INLINE static const CATechMeta &  GeoSessionIdOutput(); // Factory output
  INLINE static const CATechMeta &  OperatorId(); // 
  INLINE static const CATechMeta &  MultiRun(); // 


  INLINE static const CATechMeta &  FeatureName(); // 
  INLINE static const CATechMeta &  ResultName(); // 

  INLINE static const CATechMeta &  OperatorType(); // string 
  INLINE static const CATechMeta &  SoftLevel();
  INLINE static const CATechMeta &  OpenConfig();
 
  INLINE static const CATechMeta &  Ticks();
  INLINE static const CATechMeta &  WorkingSet();
  INLINE static const CATechMeta &  CreatedEntities();

  INLINE static const CATechMeta &  WithError();

  INLINE static const CATechMeta &  PhoenixType();
  INLINE static const CATechMeta &  PhoenixDataDir();
  INLINE static const CATechMeta &  PhoenixRootDir();
  INLINE static const CATechMeta &  PhoenixXML();

  INLINE static const CATechMeta &  InputCopy(); //  ...
  INLINE static const CATechMeta &  InputNoCopy();
  INLINE static const CATechMeta &  InputNeutral();
  INLINE static const CATechMeta &  Output();

  INLINE static const CATechMeta &  DumpInput();
  INLINE static const CATechMeta &  DumpOutput();
  INLINE static const CATechMeta &  DumpHtml();
 
  INLINE static const CATechMeta &  ModusOperandi();
  INLINE static const CATechMeta &  DataVersion();
  INLINE static const CATechMeta &  DiskSize();


  INLINE static const CATechMeta &  Option_BeforeOnly();
  INLINE static const CATechMeta &  Recording_Error();
  INLINE static const CATechMeta &  Recording_NoReplay();

  INLINE static const CATechMeta &  ErrorId();
  INLINE static const CATechMeta &  ErrorMsgCatalog();
  INLINE static const CATechMeta &  ErrorMsgId();
 

  INLINE static const CATechMeta & Patch_CATPGMTessBody(); 

  INLINE static const CATechMeta & DeltaCgmthrow(); 

 
  /** 
  * @nodoc 
  2012Spring
  */ 
  INLINE static const CATechMeta &  CompositeManagement(); // 


  INLINE static CATBoolean IsAutomaticByEnvironnementVariable();
  INLINE static CATLONG32  PopAvoidSameNameCounter();

  INLINE static CATBoolean IsSynchronous();
  INLINE static CATBoolean IsMinimalWithoutOutputs();


  /** 
  * @nodoc 
  */ 
  static CATechSet *  OpenZipWithMutations( const CATUnicodeString & iOutputZipFileName ,
                                            CATechAttribute  *iOptions ,
                                             const CATBoolean iSetAsCurrentJournaling = TRUE);

  /** 
  * @nodoc 
  */ 
  static HRESULT      OpenZipWithMutations( const CATUnicodeString & iInputZipFileName ,
                                            CATLISTV(CATechGet_var) & oResult,
                                            CATechAttribute  *iOptions ,
                                            const CATBoolean          ifOnlyOneSetAsCurrentJournaling = TRUE);
  /** 
  * @nodoc 
  */ 
  static  void              ComputeDicos();

  /** 
  * @nodoc 
  */
  INLINE static void               Initialize();

  /** 
  * @nodoc 
  */
  static HRESULT			_BootPhoenixForJournaling();

  /** 
  * @nodoc 
  */

  static HRESULT			_BootPhoenixForReading();
  /** 
  * @nodoc 
  */
  static HRESULT			_DisablePhoenixForJournaling();

protected :
  /** 
   * @nodoc 
  *  _Initialize
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  static void               _Initialize(CATechAttribute  *iOptions = NULL);
  static CATBoolean         _IsInitialized;

  static CATBoolean			_IsPhoenixInitialized;
  static CATBoolean         _IsPlayBackActivated;
  static CATBoolean         _IsAutomaticByEnvironnementVariable;
  static CATBoolean         _IsSynchronous;
  static CATBoolean         _MinimalWithoutOutputs;

  static CATechSetup_Domain  _Domains;
  static CATUnicodeString   _OutputZip;
  static CATUnicodeString   _CATechSetup_Directory;
  static CATUnicodeString   _CATechSetup_OldZip;
  static CATBoolean         _OutputZipIsDefined;
  static  CATLONG32         _AvoidSameNameCounter;  
  static CATUnicodeString   _KeepName;
  static CATBoolean         _KeepNameIsDefined;
  static CATBoolean         _IsZipFileCreated;
  static CATBoolean         _IsZipPathFileNameOK;

  static CATechAttribute  *_GetOptions(const char * pCATGMayday);

  // _ApplicativeStack
  static  CATLONG32         _ApplicativeStackIndex;  
  static  CATechAttribute * _ApplicativeStackAttributes[CATechSetup_ApplicativeStack];    
  static  CATULONG64        _ApplicativeStackTicks[CATechSetup_ApplicativeStack]; //  = __rdtsc();
  static  CATLONG64         _ApplicativeStackWorkingSet[CATechSetup_ApplicativeStack]; //  = __rdtsc();
  static  int               _ApplicativeStack_NumberOfThrow[CATechSetup_ApplicativeStack]; //  = __rdtsc();
 
  static  CATLONG32         _ApplicativeStackPushPopIndex;  
  static  CATBoolean        _ApplicativeStackPushPop[CATechSetup_ApplicativeStack]; //  = __rdtsc();
  static  CATUnicodeString  (*_ApplicativeStackPushPopName) [CATechSetup_ApplicativeStack]; //  = __rdtsc();

   // Buffer Set
  static  CATechSet       * _BufferSet;    

  static  CATLONG64         _CumulatedTicks; //  = __rdtsc();
  static  CATLONG64         _CumulatedToolsTicks; //  = __rdtsc();
  
  // OpId_Itf
  static  CATHashDico       _OpId_Itf_Dico;  
  static  CATHashDico       _OpId_HasBeenIdentifiedAsUncomplete;  
  static  int               AtExit();
  static CATBoolean        _ComputeDicos;

  static void				Setup_PolyOperator_Catched(CATBoolean iIs_PolyOperator_Catched);
  static CATBoolean			_Is_PolyOperator_Catched;
  static CATUnicodeString _CATechSetup_PhoenixDirectory;

private :
  static void   SetPlayBackActivated();
  static CATUnicodeString GetDataType(CATUnicodeString &iFileName,CATUnicodeString &iExt);

  /** 
  * SaveAsXXX
  */ 
  static HRESULT      SaveAsDirectory();
  static HRESULT      SaveAsZip();
  static HRESULT      OpenAsZip( const CATUnicodeString & iOutputZipFileName , CATLISTV(CATechGet_var) & oResult, CATechAttribute  *iOptions );
  static CATechSet *  OpenAsDirectory( const CATUnicodeString & iOutputZipFileName);
  static void  OpenAsDirectory( const CATUnicodeString & iOutputDirectoryName, CATHashDico *&ioDataLinks);

  friend class CATMathODTCGM;
};

//-------------------------------------------------------------------------------------------------
// Initialize
//-------------------------------------------------------------------------------------------------
INLINE void  CATechSetup::Initialize()
{
	if ( ! _IsInitialized ) CATechSetup::_Initialize(); 
}

//-------------------------------------------------------------------------------------------------
// IsActivated
//-------------------------------------------------------------------------------------------------
INLINE   HRESULT  CATechSetup::IsJournalingActivated(CATechSetup_Domain iDomain)  
{ 
  if ( ! _IsInitialized ) CATechSetup::_Initialize();  
  if ( ! _IsPlayBackActivated || ! ( iDomain & _Domains ) ) return E_FAIL;
  //if ( ! _IsPhoenixInitialized  && (iDomain & CATechSetup_PolyOperator) ) return _BootPhoenixForJournaling();
  return S_OK;
}

//-------------------------------------------------------------------------------------------------
// SaveOutputZip
//-------------------------------------------------------------------------------------------------           
INLINE HRESULT  CATechSetup::SaveOutputZip( const CATUnicodeString & iOutputZipFileName )
{
  CATechSetup::SetOutputZip(iOutputZipFileName);
  return CATechSetup::Save( );
}


INLINE  HRESULT CATechSetup::GetCurrentOutputZip(  CATUnicodeString & oOutputZipFileName ) 
{
  if ( ! _IsInitialized ) CATechSetup::_Initialize();  
  oOutputZipFileName = _OutputZip;
  return _OutputZipIsDefined ? S_OK : E_FAIL ;
} 

INLINE  HRESULT CATechSetup::WithKeepName(  CATUnicodeString & oKeepName ) 
{
  if ( ! _IsInitialized ) CATechSetup::_Initialize();  
  oKeepName = _KeepName;
  return _KeepNameIsDefined ? S_OK : E_FAIL ;
}

//-------------------------------------------------------------------------------------------------
// Options customisation for GMtk developper
//-------------------------------------------------------------------------------------------------

INLINE const CATechMeta & CATechSetup::CompositeManagement()  { static const CATechMeta _Dummy("CompositeManagement",CATechFormat_NoValue);  return _Dummy;}


INLINE const CATechMeta & CATechSetup::CGMOperator()              { static const CATechMeta _Dummy("CGMOperator",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::PolyOperator()             { static const CATechMeta _Dummy("PolyOperator",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::MinimalWithoutOutputs()    { static const CATechMeta _Dummy("MinimalWithoutOutputs",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::CDSComponent()             { static const CATechMeta _Dummy("CDSComponent",CATechFormat_NoValue);  return _Dummy;}


INLINE const CATechMeta & CATechSetup::Completion()      { static const CATechMeta _Dummy("Completion",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::Factory()         { static const CATechMeta _Dummy("Factory",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::WithDataLink()    { static const CATechMeta _Dummy("WithDataLink",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::ExtCGMOperator()  { static const CATechMeta _Dummy("ExtCGMOperator",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::OutputZip()       { static const CATechMeta _Dummy("OutputZip",CATechFormat_CATUnicode);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::KeepName()        { static const CATechMeta _Dummy("KeepName",CATechFormat_CATUnicode);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::AvoidSameName()   { static const CATechMeta _Dummy("AvoidSameName",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::KeyOne()          { static const CATechMeta _Dummy("1",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::KeyTwo()          { static const CATechMeta _Dummy("2",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::KeyThree()        { static const CATechMeta _Dummy("3",CATechFormat_NoValue);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::CATCX_NCGM()      { static const CATechMeta _Dummy("CATCX_NCGM",CATechFormat_NoValue);  return _Dummy;}
 
INLINE const CATechMeta & CATechSetup::PhoenixType()     { static const CATechMeta _Dummy("PhoenixType",CATechFormat_CATUnicode);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::PhoenixDataDir()      { static const CATechMeta _Dummy("PhoenixDataDir",CATechFormat_CATUnicode);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::PhoenixXML()      { static const CATechMeta _Dummy("PhoenixXML",CATechFormat_CATechDataLink);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::PhoenixRootDir()  { static const CATechMeta _Dummy("PhoenixRootDir",CATechFormat_CATUnicode);  return _Dummy;}

INLINE const CATechMeta & CATechSetup::IndexValue()      { static const CATechMeta _Dummy("IndexValue",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATechSetup::MappingResult()   { static const CATechMeta _Dummy("MappingResult",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATechSetup::NestedEvent()     { static const CATechMeta _Dummy("NestedEvent",CATechFormat_Int32); return _Dummy;}
 
INLINE const CATechMeta & CATechSetup::Dummy_NoValue()   { static const CATechMeta _Dummy("Dummy_NoValue",CATechFormat_NoValue); return _Dummy;}

INLINE const CATechMeta & CATechSetup::ErrorId()           { static const CATechMeta _Dummy("ErrorId",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATechSetup::ErrorMsgCatalog()   { static const CATechMeta _Dummy("ErrorMsgCatalog",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::ErrorMsgId()        { static const CATechMeta _Dummy("ErrorMsgId",CATechFormat_CATUnicode); return _Dummy;}

INLINE const CATechMeta & CATechSetup::DeltaCgmthrow()  { static const CATechMeta _Dummy("DeltaCgmthrow",CATechFormat_Int32); return _Dummy;}
 

//-------------------------------------------------------------------------------------------------
// Internals value for GM developper
//-------------------------------------------------------------------------------------------------

INLINE const CATechMeta & CATechSetup::Domain()             { static const CATechMeta _Dummy("Domain",CATechFormat_Int32); return _Dummy;}

INLINE const CATechMeta & CATechSetup::GeoSessionIdOutput() { static const CATechMeta _Dummy("GeoId",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATechSetup::OperatorId()         { static const CATechMeta _Dummy("OpId",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATechSetup::MultiRun()           { static const CATechMeta _Dummy("MultiRun",CATechFormat_Int32); return _Dummy;}

INLINE const CATechMeta & CATechSetup::OperatorType()       { static const CATechMeta _Dummy("Type",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::SoftLevel()          { static const CATechMeta _Dummy("SoftLevel",CATechFormat_Int32); return _Dummy;}
INLINE const CATechMeta & CATechSetup::OpenConfig()         { static const CATechMeta _Dummy("OpenConfig",CATechFormat_NoValue); return _Dummy;}

INLINE const CATechMeta & CATechSetup::FeatureName()        { static const CATechMeta _Dummy("FeatureName",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::ResultName()         { static const CATechMeta _Dummy("ResultName",CATechFormat_CATUnicode); return _Dummy;}
  

INLINE const CATechMeta & CATechSetup::Ticks()             { static const CATechMeta _Dummy("Ticks",CATechFormat_Int64); return _Dummy;}
INLINE const CATechMeta & CATechSetup::WorkingSet()        { static const CATechMeta _Dummy("WorkingSet",CATechFormat_Int64); return _Dummy;}
INLINE const CATechMeta & CATechSetup::CreatedEntities()   { static const CATechMeta _Dummy("Created",CATechFormat_Int32); return _Dummy;}

INLINE const CATechMeta & CATechSetup::WithError()         { static const CATechMeta _Dummy("WithError",CATechFormat_NoValue);  return _Dummy;}

INLINE const CATechMeta & CATechSetup::InputCopy()         { static const CATechMeta _Dummy("InputCopy",CATechFormat_CATICGMObject);  return _Dummy;}
INLINE const CATechMeta & CATechSetup::InputNoCopy()       { static const CATechMeta _Dummy("InputNoCopy",CATechFormat_CATICGMObject); return _Dummy;}
INLINE const CATechMeta & CATechSetup::InputNeutral()      { static const CATechMeta _Dummy("InputNeutral",CATechFormat_CATICGMObject); return _Dummy;}
INLINE const CATechMeta & CATechSetup::Output()            { static const CATechMeta _Dummy("Output",CATechFormat_CATICGMObject); return _Dummy;}
 
INLINE const CATechMeta & CATechSetup::Option_BeforeOnly()  { static const CATechMeta _Dummy("Before",CATechFormat_NoValue); return _Dummy;}
INLINE const CATechMeta & CATechSetup::Recording_NoReplay() { static const CATechMeta _Dummy("Recording_NoReplay",CATechFormat_NoValue); return _Dummy;}
INLINE const CATechMeta & CATechSetup::Recording_Error()    { static const CATechMeta _Dummy("Recording_Error",CATechFormat_CATUnicode); return _Dummy;}

INLINE const CATechMeta & CATechSetup::Patch_CATPGMTessBody()    { static const CATechMeta _Dummy("Patch_CATPGMTessBody",CATechFormat_CATCGMRefCounted); return _Dummy;}


 
  // OpenSave
INLINE const CATechMeta & CATechSetup::ModusOperandi()     { static const CATechMeta _Dummy("ModusOperandi",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::DataVersion()       { static const CATechMeta _Dummy("DataVersion",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::DiskSize()          { static const CATechMeta _Dummy("DiskSize",CATechFormat_Int64); return _Dummy;}

INLINE   CATBoolean      CATechSetup::IsAutomaticByEnvironnementVariable() 
{
  if ( ! _IsInitialized ) CATechSetup::_Initialize();  
  return _IsAutomaticByEnvironnementVariable; 
}


INLINE   CATBoolean      CATechSetup::IsSynchronous()
{
  if ( ! _IsInitialized ) CATechSetup::_Initialize();  
  return _IsSynchronous; 
}


INLINE   CATBoolean      CATechSetup::IsMinimalWithoutOutputs()
{
  if ( ! _IsInitialized ) CATechSetup::_Initialize();  
  return _MinimalWithoutOutputs; 
}
 

INLINE   CATLONG32       CATechSetup::PopAvoidSameNameCounter() { return ++_AvoidSameNameCounter; }
 
INLINE const CATechMeta & CATechSetup::DumpInput()   { static const CATechMeta _Dummy("DumpInput",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::DumpOutput()  { static const CATechMeta _Dummy("DumpOutput",CATechFormat_CATUnicode); return _Dummy;}
INLINE const CATechMeta & CATechSetup::DumpHtml()    { static const CATechMeta _Dummy("DumpHtml",CATechFormat_CATUnicode); return _Dummy;}

#endif
