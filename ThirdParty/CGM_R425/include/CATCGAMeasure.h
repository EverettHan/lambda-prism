#ifndef CATCGAMeasure_H
#define CATCGAMeasure_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/*--------------------------------------------------------------------------------------------------------------*/
/*  ELUCIDATION EMBEDDED INSIDE Report, for INTEGRATION OF INTERACTIVE CORE MODELING RELEASES                   */
/*     middleware integration for potential heavy commands                                                      */
/*        filling a gap between preliminary local functionnal components based testings                         */
/*        and manual industrial integration such as data management of http://pcs/                              */
/*     targetted to be available on any workstation and any runtimeview configuration (even commercial)         */
/*        for some more collaborative experience feedbacks based upon neutral integrative measure               */
/*  Tutorial, Documentation, and Project of this genuine toolkit are gathered inside following page             */
/*           http://wikigm/wiki/index.php/Category:Architecture                                                 */
/*  Those Kernel Experience set of services are physically implemented in this added value framework            */
/*       coexistant V5-V6 availability with Light Core FootPrint compliant with Cold Start requirement          */
/*       The only prerequisite is the System framework and VisualisationFoundation already prereq it.           */
/*--------------------------------------------------------------------------------------------------------------*/
/**
* @level Private
* @usage U1
*---------------------------------------------------------------------------------------- 
*
*   Rationale :  Applied Clearance Reporting  (Capacity, Scalability and Performance)
*                  Used primary for quick and clearer integration of heterogenous piecewise sofware components 
*                  used inside commercial products and solutions, for easier support of innovations and openness.
*
*   Purpose: Generic clarification of the contents of a scenario targetting any commands which need to be more collaborative
*                in terms of readiness requests
*                with minimal footprint (on demand activation) according to following dicreasing priorities and orders  
*        
*      Purpose #0 : Functionnal Naming, identify by explicit names (domain, operation)  major computation nodes
*                         associated to the configuration of a end-user digital scenario performance
*                         enabling an enhanced collaborations between underlying multiple components or services .
*
*      Purpose #1 : Reliability helpers, enable to collect if needed , in context of previous explicit Nodes (computation, I/O, ...)
*                      some meaningfull intermediate extensions and indicators with minimal footprint on demands.
*
*      Purpose #2 : derivated PCS Indicators Collect (and applied domains contexts),
*                     enable to collect some computer sciences indicators (elapsed times, working set)
*                        to be compared with human physiology (human cognitive process  heart rate of 1s - 0.5s and threshold pcs of 15 ms)
*                     but which may be usefull if compared or interpreted in context of applied domains
*                        depending from scalability of data or nature and of mathematicals foundations of treatments (solver, ..)
*
*   Mandatory Input conditions as A.P.I entry-point :
*
*      minimal threshold  criteria is currently subjectively choosen  
*          such as 50 % of elapsed time usage of command,operator/services is superior 15 ms (66 Hz  ~ electrical frequency) 
*
*   Limitations :
*
*        This service is designed as  simpliest A.P.I and  implemented only with System as Kernel prerequisite framework 
*             so usable for the maximum range of deployment of applications (initialised coexistent V5/V6 and single system image)  
*       this helper does not replace at all general purpose profiler such as internal MipMip tracking  (http://pcs/index.php)
*          it rather collect some modeling architecture complexity indicators mixed 
*             with external user experience (interactivity and real times needs), 
*          it should explicit help to explicitly integrate as integrated build-in knowledge of some recurrent opened architectural protocols
*             generating on demand a controlled automatic quick and dirty clearance reporting directly more readable
*     
*   RoadMaps :
*
*    For V6R2014x General Availability  (2013.Week 47 in published CGMOFF-CGMPRJ)
*      Tier 0, environnement variable                                         (10/2013)
*      Tier 1, automatic customised ODT report excluding dedicated pcs (3 %)  (11/2013)  ${ODT_LOG_NAME}.CATCGAMeasure.csv   http://webtechno/
*
*    For co-existent V5-6R2014 = V6R2014x (2013.Week 47 in published CGMOFF-CGMPRJ)
*      Tier 2, On demand generated report outside testauto (manual)           (12/2013)
*      Tier 3, dedicated small GUI                                            (2014.Q1)
*
*
*   Limitations :
*
*      From experience return, this approach was very helpfull
*         to superses some old legacy (with sometimes unsafe numerous exit management associated to leaks managements)
*      preferring to provide only scalable report with sections on demands 
*         letting  delayed appreciation of measures in context  of some more global integration of heterogenous innovations
*      Do not confuse with some local software local generic quality report and support
*         This middleware approach has nothing todo with memorycheck indicators which should primary
*         used for reliability convergence of errors
*
*   Confidential Usage :
*
*    This A.P.I and any attachments are intended solely for the use of the individual or entity to whom it is addressed
*      and may be confidential and/or privileged. 
*      If you are not one of the named recipients or have received this email in error, 
*        (i) you should not read, disclose, or copy it, 
*       (ii) please notify sender of your receipt by reply email and delete this email and all attachments, 
*      (iii) Dassault Systemes does not accept or assume any liability or responsibility for any use of or reliance on this email. 
*   
*   Out of scope :
*
*     The possible back-office administration of generated report is out of commercial considerations
*     (too far from high end-user added values),
*     and should purely used as usual for any ProtectedInterfaces as some internal helpers
*     to ease technical communication among different organisations.      
*
*   History :
*    
*     In review of Packaged 3D experience CATIA.media V6R2104x the 15 August 2013 (under microsoft Seven windows 64 bits )
*        Cold start on Blank Page with zero degree of freedoom in user intents capture
*          666 shared-lib  (10 % of the full runtimeview = ~6 K shared-lib) were initially loaded in the main interactive process 
*          (not taking into account other running processus)
*     Among those 666, without any CATGeoFactory instanciated, in September concerning the geometrical domain (expected later lazzy loading)
*        he comes some initial loaded dependant from applied open interactive customisations  
*          CATMathematics CATGMGeometricInterfaces CATAdvancedMathematics CATMathStream
*        in that area, this helper service was provide a clearer diagnosis
*           and reportdata towards best organisations which are more appropriate concerning Cold start optimisations and readiness.
*
*     Concening versatility of diagnosis, the 11 November 2013 demonstrate      
*
*      1) Reporting on reuse of  Forced Upgrade Update
*
*          a) Controle
*               set CATCGAMeasure=depth=Name,domain=Feat
*          b) Execute 
*               set TEST_INDUS_PERFO=1
*               mkodt -s BMW_EK_V5R7SP4_Adapter_091001.sh -F zzIndusPartShapeOpenUpdate.tst
*          c) Single_Report
*               automatically generated File inside Output in form ${ODT_LOG_NAME}.CATCGAMeasure.csv with multiple sections @xxx
*          d) Optional synthesis of numerous single reports 
*               extraction de la section @CSI en synthese 
*
*---------------------------------------------------------------------------------------- 
*
*  HOW Internally explicilty collaborate on meaningfull computations (or treatments)
*
*---------------------------------------------------------------------------------------- 

#include "CATCGAMeasure.h"

  static CATCGAMeasureNode  MeasureNode("COLLAB",CATCGAMeasureDomain_Command,0);

  CATCGAMeasure::StartPush(MeasureNode);
  CATTry  
  {
       ....
  } 
  CATCatch (CATError, err)
  {
    CATCGAMeasure::EndPop(MeasureNode);
    CATRethrow;
  }
  CATEndTry ; 
  CATCGAMeasure::EndPop(MeasureNode);

*---------------------------------------------------------------------------------------- 
*
*  HOW to activate and customized on-demand report
*
*---------------------------------------------------------------------------------------- 
*
*    A general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    Meaningfull report avec provided with activation of following environement variable
*
*      Core generic computer science indicators (and some human real times mapping)
*
*         CATCGAMeasure=                  Minimal statistics at Exit 
*         CATCGAMeasure=Home=E:\tmp       Minimal statistics at Exit, generated files on specified directory
*
*         CATCGAMeasure=depth=Root|Type|Name                   (Simple, basic reporting in CSV about main GeoFactory
*                                                               (Create,Save,Load,Close,..)
*         CATCGAMeasure=domain=Command|Feat|GM|Part|DataIO          (Filtering resulton specific domain
*         CATCGAMeasure=criteria=ELS+CPU+DLL+Ticks+MEM+DISK         (multiple criteria reserved for future use)
*                                                                      ELS   : temps ecoule
*                                                                      CPU   : temps cpu
*                                                                      MEM   : WorkingSet Peak (Global) + Delta GM Objects
*                                                                      DISK  : Poids disque d un Feature
*                                                                      DLL   : Delta # DLL (Cost intensive)
*                                                                      Ticks : temps ecoule
*         CATCGAMeasure=domitf=Command|Feat|GM|Part|DataIO          (restraint domain Filtering on first level)
*
*         CATCGAMeasure=log               Workspace\LOG\CaseStudy sub-directory
*         CATCGAMeasure=dll               report loaded dll at end of report
*
*         CATCGAMeasure=cockpit           (callee-operatorid-caller-knowledgedatabase-preparing-immersive-tool  )
*                                           CATCGAMeasure=cockpit=gmtype (extension with GMTypes
*
*      Core control management
*
*         CATCGAMeasure=NULL              Avoid control of all previous options
*         CATCGAMeasure=FILE=XXX          Indirect declarative by textual file
*
*         For Smoother Middleware software architecture configuration 
*
*            CATCGAMeasure=Exclude=Type.Domain   Exclude list (Default management on integrated ...)
*            CATCGAMeasure=Include=Type.Domain   Include list (On first declarative node, restricted management is switched
*                                                              on this restrictive mode)
*              (for instance of nodes :  GMCheckUp.GeoFactory , .... )
*
*         CATCGAMeasure=mipmips=TypeName  generate CATMakeStartPoint/CATMakeStopPoint on fly when criteria of Type or Name is Okay
*                                             with  CATMonitoredObject=CATCGAMeasure
*                                         Assuming CSI is active with something like,  CATCGAMeasure=domain=CommandFeat,depth=Name,mipmips=XXX
*
*      3D modeling generic capabilities and Feature Naming conventions
*
*         CATCGAMeasure=history           (Simple, basic reporting in CSV about main GeoFactory (Create,Save,Load,Close,..)
*         CATCGAMeasure=cache              (Simple, NCGM extracted on each I/O)
*         CATCGAMeasure=cachebrep          (Advanced with NCGM extracted on each BRep Reference)
*
*         CATCGAMeasure=name=RectPattern.7 (capture dedicated to Part->Update and anti-regressions mechanisms)
*         CATCGAMeasure=type=RectPattern   (capture dedicated to Part->Update and anti-regressions mechanisms)
*         CATCGAMeasure=playback           (generic capture of root CATCGMReplays as PlayBack...)
*
*         CATCGAMeasure=PCS=50            (WorkingSet reporting, tuning set based upon value of MegaBytes  )
*         CATCGAMeasure=PCS=50,PCSCache   (WorkingSet Avanced with CGMReplay extracted when meaningfull)
*
*         CATCGAMeasure=Option=XXX|||     Extended Options
*         CATCGAMeasure=nobox              (NoBox management at persistency management)
*
*      3D modeling generic capabilities and Feature Naming conventions
*
*         CATCGAMeasure=featype                                                     Feature Type collect          (When running) 
*         CATCGAMeasure=featatclose                                                 Feature at close              (Debug, N1 Support) 
*                                                                         ->> CGMV5SpecsQuery\CATCGMV5Part.m\src\CATCGMV5PartFeatureMonitor.cpp
*
*         CATCGAMeasure=gmerrors                                                    with message of gm errors collected
*         CATCGAMeasure=gmtype                                                      with CATGeoFactory tracability  
*         CATCGAMeasure=featlevel                                                   Option with Feature Reporting (When Collecting) 
*
*         CATCGAMeasure=trace                                                       Internal                      (Debug, Not Supported) 
*         CATCGAMeasure=lowlevel                                                    Low levl memory               (Debug, N1 Support) 
*         CATCGAMeasure=gmlevelupgrade=#                                            RFU
*
*         CATCGAMeasure=gmpoolreport                                                On exit of ODT, generate old CATCX_MEMORY report at exit
*
*
*      Prototype evaluations
*
*         CATCGAMeasure=force=FeatPurge|PartialLoad|CleanLoad|...                   (Debug, Not Supported) 
*                                                                                          force=FeatPurge -> Add featype reporting
*         CATCGAMeasureUserExit=CATIfWePurgeNonPersistent.CATGeometricObjects       (DEPRECATED, Purge Lean Data Manufacturing
*                                                                                   (Debug, Not Supported) 
*
*----------------------------------------------------------------------------------------------------------- 
* Currently integrated Software experience
*
*  Elucidation Adminstrative Project (V6R2015) lead for heavy and middleware modelers integrations 
*
*      As primer for standalone and do-it-yourself experience follow-up 
*          based on internal generic common infrastructure 
*      For cleaning previous unsafe miscallaneous reports attempt on exit
*          leading sometimes to confusing analysis with mail-chain on complex conflicting solver
*      For promoting safer two cycles from automatic scenario and experiences 
*         1/ optimal functionnal foreground and 2/ background knowledge report management 
*      For upgrading some internal implicit dedicated work station
*         based on external technologies with uncertain evolution costs (such as 2013 mks removal)
*         
*    -> Synthetic report  ${ODT_LOG_NAME}.CATCGAMeasure.csv 
*          generated at exit carefully and safetelly and incrementally driven a a kernal Framework  
*          which is managed exclusively under Direction of Capacity and Scalabality responsability
*
*  Optional Customer extensions ..
*
*     The rich set of Options can also be locally combined and activated by extension
*         by Software development made under SCM workspace
*     However No warranty and support will be provided when introducing such customisation 
*        ${FW}\CNext\code\CATCGAMeasureWorkspace\CATCGAMeasure.${ADL_WS}.txt
*
*    For instance , Old fashion report of specific *.CATCX_MEMORY files can be regenerated 
*      with "gmpoolreport" keyword includes in that declarative file CATCGAMeasure.${ADL_WS}.txt
*
*    This kind of unsecured extensions requires at least the minimal administrative validation 
*        with  associated to a prelimiary framework managed by Elucidation Project
* 
*----------------------------------------------------------------------------------------------------------- 
 
    Boot

    Operator() 

    Mechanical() 
       Update()
       Close()

    ManageMemory 
       NoMore_Product
       NoMore_FactoryV5

    CGMContainer
       afterCreate 
       GMClosing()
       CleanNewerUnused() = Tass
       GMSave()
       GMLoad()

    Tessellation()

    PageAllocator 
        new del Delete 

    CATCX_CHECKUP_GeoFactory
    CATCX_CHECKUP_Object
    CheckupExplicit

*---------------------------------------------------------------------------------------- 
* Post scriptum
*---------------------------------------------------------------------------------------- 
*
*    Helpers anti-regression mechanisms Applied forced upgrade update  
*       suggested for new 3D Experience GUI of V6R2104, V6R2014x helper switched at beginning of 2013
*         (on initial long sequence of Cold Start with zero degree of freedom which is not manually automatised)
*       legacy usefull for Legacy Lean Manufacturing of GM Optimised Data
*          also tighly linked with some recurrent CoreDump incident
*          misunderstood concerning  origin of memory consumption  badly managed when request of allocations begin to fail
*
*   Citations  (William Shakespeare 1564-1616, Rabelais 1483-1553, Heisenberg 1901-1976):
*       To Be or Not To Be
*          (Be.        3DViaShape freely downalable started in  3 s with    authoring Brep )
*          (Not To Be, Initial 3D Experience Cold Start     in 40 s without GM Modeling DLLS implementation)
*      "science sans conscience était ruine de l’âme" 
*      "on ne peut pas connaître simultanément sa position et sa vitesse"
*
*----------------------------------------------------------------------------------------
*/
//---------------------------------------------------------------------------------------
#include "CATMathematics.h"

#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"

#include "IUnknown.h"
#include "CATMathInline.h"

// #include "CATCGM_LightSession.h"
#include "CATCGMCockpitTable.h"

#include "CATCGAMeasureNode.h"
#include "CATCGAMeasureTimer.h"
#include "CATCGAMeasureContext.h"
#include "CATCGAMeasureGlobal.h"
#include "CATCGAMeasureDefine.h"
#include "CATCGAMeasureValue.h"
#include "CATCGAreport_Measures.h"

#include "CATGMIfWePurgeNonPersistent.h"


#define CATCGAMeasure_MAXSTACKDEPTH 512


class CATCGAMeasure;
class CATCGAMeasure_IMPL;
class CATCGMContainer;
class CATCGMExtensionsForPart;
class CATCGMManageMemory;
class CATCGMOperator;
class CATCGMOperatorRun;
class CATCGMPageAllocator;
class CATCGMTopoCXMODEL;
class CATCGM_STREAM;
class CATCGMemoryPOOL;
class CATCXDebug;
class CATCGMV5PartFeatureMonitor;
class CATCXTopology;
class CATExtCGMReplay;
class CATMakePoint;
class CATMathODT;
class CATMfMechanicalFeature;
class CATMfPartExt;
class CATOGM_STREAM;
class CATOGM_STREAM;
class CATechSetOfChar;
class CATCGAMeasureStackLevel;
class CATCGAMeasureNode;
class CATCGMObject;
class CATCGMItfName;
class CATExtCGMObject;
class CATError;
class CATCGMIsUnderODT;
class CATCGAMeasureGlobal;
class CATTechGemFrmDialog;

typedef unsigned int CATCGMItfNameFLAGS;

 
//------------------------------------------------------------ 
/**
* Essential services to manage the replay of running objects  .
*/

class ExportedByCATMathematics CATCGAMeasure
{
public :


 /** 
   * Declare a secure (before and after must be securize by catch/rethrow)
   *    explicit monitored measure (rather than an external samplings or interrruptions)
   *    to see if it is meaningfull for further analysis .
   *
   * @return
   *      TRUE   if significant variation has occured since last previous measure <br>
   *      FALSE  otherwise <br>
  */           
  INLINE static CATBoolean StartPush( CATCGAMeasureNode & ioNodeContext );

  INLINE static CATBoolean Direct( CATCGAMeasureNode & iNodeContext );

  INLINE static CATBoolean EndPop( CATCGAMeasureNode & iNodeContext  );





  //-----------------------------------------------------------------------
  // Monitoring
  //-----------------------------------------------------------------------

 /** 
   * nodoc 
  */           
  INLINE static CATBoolean IsActive();

 /** 
   * Activate monitoring
  */           
  static void Activate(const double iCurrentWorkingSetDelta =0.0, CATCGMCockpitTable * iTypes = 0 );


 /** 
   * Inactivate
  */           
  static void Inactivate();

  
 /** 
   * Temporary Management
  */           
  INLINE static void TemporaryManagement(const CATBoolean iTrueActivate_FalseDesactive);


  /**
  * HasHomeDirectory .
  */
  static CATBoolean HasHomeDirectory(CATUnicodeString & oHomeCache)   ;

  /**
  * HasStatFile .
  */
  static CATBoolean HasStatFile(CATUnicodeString & oStatFile)   ;
 
  /** 
  * @nodoc  MakeSureInitDone
  */ 
  static void MakeSureInitDone();

  /** 
  * @nodoc  EndMeasures
  */ 
  INLINE static CATBoolean EndMeasures( CATCGAMeasureNode & iNodeContext );

  //-----------------------------------------------------------------------
  //  Option query
  //-----------------------------------------------------------------------

  /** 
  * @nodoc  GetGlobalSession
  */ 
  static const CATCGAMeasureGlobal *  GetGlobalSession();

  /** 
  * @nodoc  AskIfOption
  */ 
  static CATBoolean AskIfOption( const CATUnicodeString & iFlushFileName  );


  /** 
  * @nodoc  WithExtract (optional extract on Type)
  */ 
  static CATBoolean WithExtract( CATUnicodeString & oExtract , int & oExtractDone );


  /** 
  * @nodoc  WithBestSoFarSnapShotOfResults
  */ 
  static CATBoolean WithBestSoFarSnapShotOfResults();


  /** 
  * @nodoc  _UserExit
  */ 
  static CATCGAMeasureUserExit  _UserExit();


   /** 
  * @nodoc  NoGathering
  */ 
  static CATBoolean  NoGathering();

  
 /** 
   * Get CurrentCockpit
  */           
  INLINE static CATCGMCockpitTable * GetCurrentCockpit();

  //-----------------------------------------------------------------------
  // Internal Management
  //-----------------------------------------------------------------------


  /** 
  * @nodoc  Data URL
  */ 
  static void AddDataURL( const CATUnicodeString & iDataURL, CATULONG64 iPartSize );
  static int  GetDataURL( CATUnicodeString & oDataURL );

 
  /** 
  * @nodoc  GetReporting
  */ 
  static int GetReporting( CATCGMCockpitTable * iCumulativeCallerCallee,   const CATUnicodeString & iInputFileName );

  /** 
  * @nodoc  GetCockpitReporting
  */ 
  static int GetCockpitReporting( CATCGMCockpitTable * iCumulativeCallerCallee,  const CATLISTV(CATUnicodeString) & iLines );

  /** 
  * @nodoc  SetReporting
  */ 
  static void SetReporting( CATCGMCockpitTable * iCumulativeCallerCallee,  CATechSetOfChar  &ioDump  );



  //-----------------------------------------------------------------------
  // GM Data Integration
  //-----------------------------------------------------------------------

  /** 
  * Counter Of GMObject Creations
  */
 INLINE static void GMObjectCreations(const char * iCGMTypeName);

  /** 
  * Counter Of GMObject Deletions
  */           
  INLINE static  void GMObjectDeletions(const char * iCGMTypeName);

  /** 
  * Counter Of GMObject LeanPurge
  */
  INLINE static void GMObjectLeanPurge(const CATGMIfWePurgeNonPersistent & iGlobalStats);

   //----------------------------------------------------------------------
  // Statistical file for CGM Error thrown (ODTNAME.CATCGMError)
  //-----------------------------------------------------------------------
  static void LogCATCGMError(CATError *iError);  
  
 
   /** 
  * @nodoc  NoGathering
  */ 
  static void  Reset_CATCGAMeasure_Computed();

 
  /** 
  * @nodoc  EndOfProcess
  */ 
  static void  EndOfProcess();

 
  /** 
  * @nodoc  CATCGAMeasure_ODT
  */ 
  static const char *CATCGAMeasure_ODT();


  /** 
  * @nodoc  PrefetchCSI
  */ 
  static CATBoolean  PrefetchCSI( CATCGAMeasureNode & ioNodeContext  );


  
  //----------------------------------------------------------------------
  // Restricted integrated 
  //-----------------------------------------------------------------------

  /** 
  * @nodoc  FlushCurrentReporting   
  */ 
  static CATBoolean FlushCurrentReporting();

  /** 
  * @nodoc  RestrictedIntegration   
  */ 
  static void RestrictedIntegration(const char *ipCATCGAMeasure);



protected :

  void InitByDecodeOptions(const char *ipCATCGAMeasure);
  void EndOfInit();

  CATCGAMeasure();
  ~CATCGAMeasure();

  void Init(const CATULONG64 iWorkingSetDelta, const  CATBoolean iWithCockpit = FALSE ) ;


  /** 
  * @nodoc  GetFeatypeDirectory   
  */ 
  static CATBoolean GetFeatypeDirectory( CATUnicodeString & oFeatype );

  /** 
  * @nodoc  GetFlushFileName   
  */ 
  static CATBoolean GetFlushFileName( CATUnicodeString & oFlushFileName  );

  /** 
  * The Capture
  */ 
  void Capture(CATCGMItfName    *  iWorkingFeature);

  

private :

  /** 
  * @nodoc 
  */ 
  CATBoolean Gathering( CATCGAMeasureNode & ioNodeContext  );

  /** 
  * @nodoc  PrefetchCSI
  */ 
  CATBoolean _PrefetchCSI( CATCGAMeasureNode & ioNodeContext  );

  static CATCGAMeasure  * GetSingleton();
  static void             UnsafeExit();

  static void             FlushReporting();

  void    _FlushReporting();




  static void   FlushGMLeaks(CATechSetOfChar  &ioDump );
 

  static CATCGAMeasure * _Monitored;
 

private :

         // Parameters
         CATCGAMeasureGlobal   _Session;
  static CATBoolean            _CATCGAMeasure_Computed;


         // Stack Of Computing
         CATCGAMeasureNode     _Stack            [CATCGAMeasure_MAXSTACKDEPTH];
 
         // Stack Of preliminary Collect (Meta-Data)
         CATCGAMeasureContext  _StackContext     [CATCGAMeasure_MAXSTACKDEPTH];

         // Stack Of Data Collect : Computer Science Indicator 
         CATCGAMeasureTimer    _StackCSI         [CATCGAMeasure_MAXSTACKDEPTH];
         CATCGAMeasureValue    _StackExclusiveCSI[CATCGAMeasure_MAXSTACKDEPTH];

         // Stack Of Data Collect : Working Statistics (IFWe Purge)
         CATCGAMeasureGMData   _StackGMData      [CATCGAMeasure_MAXSTACKDEPTH];



private :

  /** 
  * Counter Of GMObject
  */           
 void _GMObjectCreations(const char * iCGMTypeName);

  /** 
  * Counter Of GMObject
  */           
  void _GMObjectDeletions(const char * iCGMTypeName);

  /** 
  * Counter Of GMObject
  */
  void _GMObjectLeanPurge(const CATGMIfWePurgeNonPersistent & iGlobalStats);
 

  void  ComputerScienceIndicators(      unsigned int        iCurrentDomain,
                                        CATCGAMeasureNode & iNodeContext,
                                        CATBoolean        & MeaningFull ,
                                  const int                 iBeforeOneShotAfter,
                                  const char              * iKindOfOperation,
                                  const char              * iDataDomain,
                                        void              * iObject,
                                        CATCGMItfName     *  iWorkingFeature );

  void  Performance              (      CATCGAMeasureNode & iNodeContext,
                                        CATBoolean        & MeaningFull ,
                                  const int                 iBeforeOneShotAfter,
                                  const char              * iKindOfOperation,
                                  const char              * iDataDomain,
                                        void              * iObject );

  void  Cockpit                  (      CATCGAMeasureNode & iNodeContext,
                                        CATBoolean        & MeaningFull ,
                                  const int                 iBeforeOneShotAfter,
                                  const char              * iKindOfOperation,
                                  const char              * iDataDomain,
                                        void              * iObject );


  


  static void        AddInPlayBack    (       CATBoolean              WithPlayBackExtraction ,
                                        const int                     iBeforeOneShotAfter    ,
                                              CATCGAMeasureNode     & ioNodeContext          );

  static void        UserExits         (      CATCGAMeasureUserExit   iUserExits             ,
                                        const int                     iBeforeOneShotAfter    ,
                                        const char                  * iKindOfOperation       ,
                                        const char                  * iDataDomain            ,
                                              void                  * iObject                );

  static void        NameAutoCompletion(       CATCGMItfName        * AlreadyFound );

  static CATBoolean  OpenMainCSV       (       CATBoolean           & oFirstLineTime,
                                               unsigned int         & oCSVReport);

  static void        OpenCSV           (       CATBoolean           & oFirstLineTime,
                                               CATBoolean           & oWithLineReport,
                                               unsigned int         & oCSVLineReport);


  // exclusive consummer 
  friend class CATCGAMeasure_IMPL;
  friend class CATCGMContainer;
  friend class CATCGMExtensionsForPart;
  friend class CATCGMManageMemory;
  friend class CATCGMOperator;
  friend class CATCGMOperatorRun;
  friend class CATCGMPageAllocator;
  friend class CATCGMTopoCXMODEL;
  friend class CATCGM_STREAM;
  friend class CATCGMemoryPOOL;
  friend class CATCXDebug;
  friend class CATCGMV5PartFeatureMonitor;
  friend class CATCXTopology;
  friend class CATExtCGMReplay;
  friend class CATMakePoint;
  friend class CATMathODT;
  friend class CATMfMechanicalFeature;
  friend class CATMfPartExt;
  friend class CATOGM_STREAM;
  friend class CATCGAMeasureStackLevel;
  friend class CATCGAMeasureNode;
  friend class CATCGMObject;
  friend class CATCGMItfName;
  friend class CATExtCGMObject;
  friend class CATCGMIsUnderODT;
  friend class CATCGAMeasureContext;

  friend class CATCGAMeasureGlobal;
  friend class CATTechGemFrmDialog;
 
private :


  CATCGAMeasure           (const CATCGAMeasure &iCopy);
  CATCGAMeasure& operator=(const CATCGAMeasure &iCopy);

 
};
 

//---------------------------------------------------------------------------------------
INLINE   CATBoolean  CATCGAMeasure::StartPush(CATCGAMeasureNode & ioNodeContext )
{ 
   if ( ! _CATCGAMeasure_Computed ) CATCGAMeasure::MakeSureInitDone();
   if (_Monitored && ! _Monitored->_Session._Flags.TemporaryDesactivation )
   { ioNodeContext._SelfBeforeOneShotAfter = +1; _Monitored->Gathering(ioNodeContext); }
   return FALSE; 
}

//---------------------------------------------------------------------------------------
INLINE   CATBoolean  CATCGAMeasure::Direct(  CATCGAMeasureNode & ioNodeContext )
{
   if ( ! _CATCGAMeasure_Computed ) CATCGAMeasure::MakeSureInitDone();
   if (_Monitored && ! _Monitored->_Session._Flags.TemporaryDesactivation )
   { ioNodeContext._SelfBeforeOneShotAfter = 0; _Monitored->Gathering(ioNodeContext); }
   return FALSE; 
}

//---------------------------------------------------------------------------------------
INLINE   CATBoolean  CATCGAMeasure::EndPop(CATCGAMeasureNode & ioNodeContext )
{
   if (_Monitored && ! _Monitored->_Session._Flags.TemporaryDesactivation )
   { ioNodeContext._SelfBeforeOneShotAfter = -1; _Monitored->Gathering(ioNodeContext); }
   return FALSE; 
}

//---------------------------------------------------------------------------------------
INLINE   CATBoolean  CATCGAMeasure::EndMeasures(  CATCGAMeasureNode & ioNodeContext )
{ 
   if (_Monitored && ! _Monitored->_Session._Flags.TemporaryDesactivation )
   { ioNodeContext._SelfBeforeOneShotAfter = -2; _Monitored->Gathering(ioNodeContext); }
   return FALSE; 
}


//---------------------------------------------------------------------------------------
INLINE  void CATCGAMeasure::TemporaryManagement(const CATBoolean iTrueActivate_FalseDesactive)
{
   if ( _Monitored ) _Monitored->_Session._Flags.TemporaryDesactivation = iTrueActivate_FalseDesactive ? 0 : 1; 
}

//---------------------------------------------------------------------------------------
/** 
* @nodoc 
*/ 
//---------------------------------------------------------------------------------------
INLINE   CATBoolean  CATCGAMeasure::IsActive()
{
   return (_Monitored && ! _Monitored->_Session._Flags.TemporaryDesactivation ) ? TRUE : FALSE; 
}


//---------------------------------------------------------------------------------------
/** 
* @nodoc 
*/ 
//---------------------------------------------------------------------------------------
INLINE   void  CATCGAMeasure::GMObjectCreations(const char * iCGMTypeName)
{
   if (_Monitored && _Monitored->_Session._Flags.CollectGMData && ! _Monitored->_Session._Flags.TemporaryDesactivation )
      _Monitored->_GMObjectCreations(iCGMTypeName); 
}

//---------------------------------------------------------------------------------------
INLINE   void  CATCGAMeasure::GMObjectDeletions(const char * iCGMTypeName)
{
   if (_Monitored && _Monitored->_Session._Flags.CollectGMData && ! _Monitored->_Session._Flags.TemporaryDesactivation )
      _Monitored->_GMObjectDeletions(iCGMTypeName); 
}

//---------------------------------------------------------------------------------------
INLINE   void  CATCGAMeasure::GMObjectLeanPurge(const CATGMIfWePurgeNonPersistent & iGlobalStats)
{
   if (_Monitored && _Monitored->_Session._Flags.CollectGMData && ! _Monitored->_Session._Flags.TemporaryDesactivation )
      _Monitored->_GMObjectLeanPurge(iGlobalStats); 
}
 

//---------------------------------------------------------------------------------------
/**
* WithBestSoFarSnapShotOfResults .
*/
//---------------------------------------------------------------------------------------
INLINE CATBoolean CATCGAMeasure::WithBestSoFarSnapShotOfResults()
{
    return (     _Monitored
            && ! _Monitored->_Session._Flags.TemporaryDesactivation
            && ! NoGathering()                                    ) ? (_Monitored->_Session._Flags.WithBestSoFarSnapShotOfResults ? TRUE
                                                                                                                                  : FALSE)
                                                                    : FALSE;
 }

//---------------------------------------------------------------------------------------
/** 
* Get CurrentCockpit
*/
//---------------------------------------------------------------------------------------
INLINE  CATCGMCockpitTable * CATCGAMeasure::GetCurrentCockpit()
{
   return (_Monitored && ! _Monitored->_Session._Flags.TemporaryDesactivation ) ? _Monitored->_Session._TheCockpitGraph : NULL; }
 

/** 
* Get CurrentCockpit
*/   

extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_DataIO;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_Command;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_Feat;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_Polyhedral;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_GeoFactory;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_Part;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_Replay;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_CGMGeom;
extern ExportedByCATMathematics const char *  CATCGAMeasureDomain_Afr;



extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_Boot;

extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_Tessellation;
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_HLRComputer;
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_CleanNewerUnused; 


extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMSave;
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMLoad;
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMCheckUp;
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMCreate;
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMClose;

extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMOpGeo; 
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMOpTopo; 
extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_GMOpAppli; 

extern ExportedByCATMathematics const char *  CATCGAMeasureOperation_Update; 


#endif
