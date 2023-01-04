#ifndef CATCGAMeasureGlobal_H
#define CATCGAMeasureGlobal_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATTime.h"
#include "CATListOfCATCGMItfNames.h"
#include "CATechPsApi.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATGetEntryPoint.h"
#include "CATCGMKernel.h"

#include "CATError.h"

#include "CATCGAreport_Measures.h"
#include "CATCGAMeasureGMData.h"
#include "CATCGAMeasureTimer.h"
#include "CATCGAreport_PCS.h"
#include "CATCGAMeasureClearance.h"

#include "CATListOfCATCGAreport_Measures.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfInt.h"
#include "CATListOfCATCGMCockpit.h"
#include "CATCGMHashNames.h"
 
class CATHashDico;
class CATCGMCockOperationTable;
class CATechAttribute;
class CATCGMCockpitTable;

class CATCGAMeasure;
class CATechSetOfChar;
class CATCGMHashNames;

class CATCGMemoryPOOL_Session;
class CATCGMemoryPOOL;

// Ensemble des parametres globaux 
// Stack Node
class ExportedByCATCGMKernel CATCGAMeasureGlobal
{
public :
   
 CATCGAMeasureGlobal();

  ~CATCGAMeasureGlobal();

    // Make sure initialisation DONE 

  struct CATCGAMeasureGlobalFlags
  {
    //
    //  GENERIC CORE MODELING
    //
    unsigned int  MakeSureInitDone         : 1; // only Once
    unsigned int	HomeReporting            : 1;
    unsigned int  WorkspaceLOG             : 1; // Force log reporting (for multiple frameworks replay)
    unsigned int  CollectGMData            : 1;
    unsigned int  CollectCSI               : 1;
    unsigned int  TraceStackLevel          : 1;
    unsigned int  TemporaryDesactivation   : 1;
    unsigned int	WithExplicitHomeReporting : 1;

    unsigned int	csiDomain    :  8; // PCS Synthesis
    unsigned int	csiDepth     :  8;
    unsigned int	csiCriteria  :  8;
    unsigned int	csiDomItf    :  8; // PCS Synthesis
    unsigned int	Forced       :  8; // CATCGAMeasureForce_XXX

    unsigned int  WithHistory          : 1; // Report Extended with historical file
    unsigned int  IsReportingActive    : 1;
    unsigned int  StatFileComputed     : 1; 
    unsigned int  InvalidStatFile      : 1; 
    unsigned int  WithFlush            : 1;
    unsigned int  WithDLL              : 1;
    unsigned int  WithFeatPurgeUI      : 1;

    //
    //  Customised Recycling Rate
    //

    unsigned int  FeatType             : 1; // Report Extended  (Feature Types)
    unsigned int  CollectGMType        : 1; //                  (Geometrical Types)
    unsigned int  WithFeatLevel        : 1; // Report Extended  (Feature Types)

    unsigned int  Cockpit              : 1; //                  (Relationships)
    unsigned int  WithFeatReportAtClose    : 1; // Report Extended  (Features Status When Closing)
    unsigned int  WithGMLowLevelIndicators : 1; // Report Extended  

    unsigned int	IsCacheActive        : 1; // Data Cache
    unsigned int	WithCacheBrep        : 1;
    unsigned int	WithCacheLoadBrep    : 1;

    unsigned int  WithExtractingType   : 1;  // Data-Operator Cache
    unsigned int  WithExtractingName   : 1;
    unsigned int  WithPlayBack         : 1;

    unsigned int	PCS                  : 1;
    unsigned int	PCSCache             : 1;
    unsigned int	NoBox                : 1;

    unsigned int  Hooked               : 1;
    unsigned int  WithOptions          : 1;

    unsigned int  UserExit                         : 1;
    unsigned int  WithBestSoFarSnapShotOfResults   : 1;
    unsigned int  WithCGMErrors   : 1;

    unsigned int  NoGathering_Initialized  : 1;
    unsigned int  NoGathering              : 1;
    unsigned int  GMOperators              : 1;


    unsigned int	WithRecyclingRate : 1; // Obsolete

    unsigned int	FlushReportOnNoMoreFactoryV5 : 1; // Reserved

    unsigned int	FlusGMPoolReportOnExit  : 1; // gmpoolreport

    unsigned int  FeatTypeDirectory  : 1; // Report Extended  (Feature Types)


    unsigned int  withVariableNodes  : 1;

    unsigned int  withLastCATCGAMeasureReport  : 1;
 
    unsigned int  ReportIdentifiedForEachProcessus  : 1; // Id Option (extended for report for each process)

  }
  _Flags;

  // Current Stack of Sampling
  CATLONG64     _CurrentStackLevel; 


  CATUnicodeString _HomeCache;

  CATUnicodeString _FlushFileName;
  CATUnicodeString _LastCATCGAMeasureReport;


  CATUnicodeString _DataURL;
  CATULONG64       _DataURLMaxSize;
  CATULONG64       _DataURLSumSize;
  int              _WithDataURL;


  CATUnicodeString _ExtractFilteredType;
  CATUnicodeString _ExtractFilteredName;

  int              _ExtractDone;

  // Advanced cockpit for Type Usage
  CATHashDico               * _TheOptions;

  CATUnicodeString  _CockpitPathName;

  CATUnicodeString  _UserExitName;

  // Cumulated number of sampling
  CATLONG64      _NumberOfMeaningFullSampling;

  // Current RootLevel Number of Sampling 
  int           _RootLevel;
  CATLONG64     _RootLevelSampleMeaningFull;

  // Cumulated number of sampling
  CATLONG64     _ForceNoMoreMemory;


  // Advanced CATCGAMeasure_IMPL
  CATUnicodeString    _StatFile;
  CATULONG32          _StepCount;
  LibraryHandler      _HookHandle;

  //-----------------------------------------------------------------------
  // Collected DATA 
  //-----------------------------------------------------------------------

  CATCGAreport_PCS      _SessionTransaction;

  CATCGAMeasureGMData   _GMDataOutsideStack;

  CATCGAMeasureGMData   _GMDataGlobal;


  // Collected DATA 
  double                 _CurrentWorkingSetDelta;
  CATCGMCockpitTable *   _TheCockpitGraph;

  // Advanced cockpit for Type Usage
  CATHashDico               * _CockpitGMTypes;
  CATCGMCockOperationTable  * _Types;


  // Collected DATA With CSI
  CATLISTP(CATCGAreport_Measures)  _ComputerScienceIndicators;
  CATCGMCockpitTable *             _TheCockpitReport;


  // In case of best fitted scenario for meaningfull indicators
  //   The list of final geometrical Feature-Based Design with associated resulting status 
  CATLISTP(CATCGMItfNames) _BestSoFarSnapShotOfResults;

  CATCGMItfNames       *  _WorkingInstances;  
  CATCGMItfNames       *  _WorkingFeatures;  


  void SetCurrentAttribute( CATBaseUnknown * iCurrentAttribute );
  CATechAttribute    *const _CurrentAttribute; 

  //-----------------------------------------------------------------------
  //  Failed ReplaySteps 
  //-----------------------------------------------------------------------
  CATLISTV(CATUnicodeString)   _CATCGMErrors;
  CATLISTV(CATUnicodeString)   _CGMReplayAsynchronousLOG;

	
	/** 
	* @nodoc  SetUpdatedStatusReporting
	*/ 
	void AddGMCloseStatistics( int iStatus, CATULONG32 iObjectsCount );
	CATULONG64 _NbGMClose[4];
	CATULONG64 _NbGMCloseLife[4];

  //-----------------------------------------------------------------------
  // FlushReporting() ...
  //-----------------------------------------------------------------------
   void FlushReporting();

  //-----------------------------------------------------------------------
  // FactoryForStackTraces() ...
  //-----------------------------------------------------------------------
   void FactoryForStackTraces(const CATLONG32 icatcxfactory, const int iCreateOrDelete);
   void IObjectForStackTraces(const CATUnicodeString & iShortName, const int iCreateOrDelete);
   void IBRepObjectForStackTraces(const CATUnicodeString & iShortName);
 
  //-----------------------------------------------------------------------
	//
	//  For smoother intermediate control on mixed and heteregenous workspace 
	//    before media are Build 
	//   (with other alternative than MSI or local RunTimeView)
	// 
	//  Associated on CATBoolean CATCGAMeasureNode IsEnable();  deployment 
  //     Exclude=Type.Domain
  //     Include=Type.Domain
	//
  //-----------------------------------------------------------------------
  static CATHashDico *  _ExcludeNodes;
  static CATHashDico *  _IncludeNodes;
  static CATCGMHashNames *  _VariableNodes;

  static CATBoolean                  _WithLeaks;
  static CATLISTV(CATUnicodeString)  _CATCGMLeaks;

  static CATBoolean                  _WithExcludeOs;
  static CATUnicodeString            _ExcludeOs;

  static CATBoolean                  _WithGMTopoFreeze;
  static CATLISTV(CATUnicodeString)  _GMTopoFreezes;

  static CATBoolean                  _WithCATCGAMeasureOptions;
  static CATUnicodeString            _CATCGAMeasureOptions;

  static CATLONG64 _catcxbreakpoints_called;

  //-----------------------------------------------------------------------------
  //  _Session._Flags.WithExtractingType or  _Session._Flags.WithExtractingName
  //-----------------------------------------------------------------------------
  static CATLISTV(CATUnicodeString)  _IFWePurgeHelpers;
  static CATLONG64                   _CATICGMObjectTag;
  static CATLONG64                   _CATGeoFactoryId;


  //-----------------------------------------------------------------------
  //  _CATCGAMeasureVariable 
  //-----------------------------------------------------------------------
  static short                       _WithCATCGAMeasureVariable; // o:Unknown , -1:Unset, +1:Set, 66:NULL
  static CATUnicodeString            _CATCGAMeasureVariable;

  //-----------------------------------------------------------------------
  //  CATCGAMeasure::HasHomeDirectory 
  //-----------------------------------------------------------------------
  static CATUnicodeString  _TheHome;
  static CATBoolean        _OkayHome;
  static CATBoolean        _OnceHome;

  //-----------------------------------------------------------------------
  //  CATCGAMeasure::OpenMainCSV
  //-----------------------------------------------------------------------
  static CATUnicodeString  _PostMotermFileName;
  static CATBoolean        _FirstTimeInSession;
  static CATBoolean        _WithPostMotermFileName;


  //-----------------------------------------------------------------------
  //  CATCGAMeasure::GetFlushFileName
  //-----------------------------------------------------------------------
  static CATBoolean        _GetFlushFileName;


  //-----------------------------------------------------------------------
  // _CurrentError
  //-----------------------------------------------------------------------
  static CATError       * _CurrentError;
  static CATErrorId       _CurrentErrorId;


  //-----------------------------------------------------------------------
  //  CATCGAMeasure::OpenCSV
  //-----------------------------------------------------------------------
  static CATUnicodeString  _LineFileName;
  static CATBoolean        _LineReportInit;
  static CATBoolean        _FirstLineTime;

  //-----------------------------------------------------------------------
  //  CATMakePoint::GetPrimayKEY
  //-----------------------------------------------------------------------
  static char              _uuidChar[CATMakePointMAXPrimayKEY];
  static CATBoolean        _ComputedGetComputerAndMain;
  static CATTime           _tLocalTime;
  static CATBoolean        _ComputedGetPrimayKEY;
  static CATUnicodeString  _TheComputer;
  static CATUnicodeString  _ExeName;

  //-----------------------------------------------------------------------
  // MipMips;
  //-----------------------------------------------------------------------
  static CATBoolean        _WithMipMips;
  static CATUnicodeString  _MipMips;

  //-----------------------------------------------------------------------
  // Reporting managenement;
  //-----------------------------------------------------------------------
  /** 
  * @nodoc  ReportGMLowLevelIndicators
  */ 
  void ReportGMLowLevelIndicators(  CATechSetOfChar  &ioDump   );
 

  /** 
  * @nodoc  SetUpdatedStatusReporting
  */ 
  void SetUpdatedStatusReporting( CATechSetOfChar  &ioDump );

  /** 
  * @nodoc  GetClearance (end of measures)
  */ 
  void GetClearance( CATCGAMeasureClearance & oMeasureClearance  );



private :
 

  //-----------------------------------------------------------------------
  //  Flush various sections ...
  //-----------------------------------------------------------------------
  void          FlushClearance(CATechSetOfChar  &ioDump );
  void          FlushCockpitGraph(CATechSetOfChar  &ioDump );
  void          FlushGMTypes(CATechSetOfChar  &ioDump );
  void          FlushGMErrors(CATechSetOfChar  &ioDump );
  void          FlushLeanRoots(CATechSetOfChar  &ioDump );
  void          FlushStackTraces(CATechSetOfChar  &ioDump );
  void          FlushVariableNodes( CATechSetOfChar  &ioDump );
  void          FlushDLL( CATechSetOfChar  &ioDump );

  void          FlushFeatype();
  void          FlushCSI( CATLISTP(CATCGMCockpit) & TableIndex,   CATCGAreport_PCS & Cumulated, CATechSetOfChar  &ioDump );

  void          SetAsynchronousLOG(CATechSetOfChar  &ioDump );
 
  //-----------------------------------------------------------------------
  //  CATCGAMeasure::_NoMoreThanOneExit
  //-----------------------------------------------------------------------
  static CATBoolean        _NoMoreThanOneExit;
  static CATBoolean        _ForbidExitReportOrRegeneration;

  friend class CATCGAMeasure;
  friend class CATCGMemoryPOOL_Session;
  friend class CATCGMemoryPOOL;

  static CATLISTV(CATUnicodeString)  _StackTraces;
  
};
 
 
#endif
