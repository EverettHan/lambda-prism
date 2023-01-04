/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1998
//
//=============================================================================
// May   03 HCN _ExitForODTOnBadNewSpecial
// Sep.  03 HCN _Book_RealCumulatedBytes, _Book_RealCumulatedFreedBytes
// Apr.  04 HCN _CATCGMemBookStats
// Jan.  05 FDN Ajout de la variable d'environnement InactiveCGMPool pour vrai 
//              malloc/free
// Apr.  05 BOM Ajout de l'information _CurrentODTName pour Authorized
//              migration checkODT OOMV
// 28/10/08 NLD Ajout _TraceMode et declaratif CATCGMemoryPoolTrace
//=============================================================================

#ifndef CATCGMemoryPOOL_H
#define CATCGMemoryPOOL_H

#include "CATMathematics.h"

#include "CATCGAMEM.h"
#include "CATCGAMEMStats.h"
#include "CATCGMaxLong.h"
#include "CATCGMNewManagement.h"
#include "CATCGMemory.h"
#include "CATCGMManageMemory.h"

#include "CATDataType.h"
#include "CATErrorDef.h"

//=============================================================================
#define  CATCGMNewDoublePerPage 512
//=============================================================================


/** 
* Manages the OS that do not align the allocation of doubles
*/
#if defined (_LINUX_SOURCE) || defined (_DARWIN_SOURCE)
#undef  CATdoubleAllocationIsAligned
#else
#define CATdoubleAllocationIsAligned
#endif


class CATCGMArrayPool;
class CATError;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATCGMemoryPOOL;
class CATCGMPageAllocator;
class CATCGAMeasure;
class CATCGAMeasureGlobal;
class CATCGMemoryPOOL_Session;
class PDQFrmDialog;

typedef void * CATSysPoolPtr;

//#include "CATCGM_LightSession.h"

#include "CATCGMemoryPOOL_Session.h"


//-----------------------------------------------------------------------
// CATCGMemoryPOOL : gestionnaire par POOL
//-----------------------------------------------------------------------
class ExportedByCATMathematics  CATCGMemoryPOOL  : public CATCGAMEM
{
public :

  virtual                      ~CATCGMemoryPOOL     ();



  static void                   memorychecker       (const char iMsg[]="");

  //-----------------------------------------------------------------------
  // Methodes virtuelles 
  //-----------------------------------------------------------------------
         void                   FreeUnusedAllocation();   // deallocates the unused blocks
         void                   CheckConsistency    ();

         void                 * newSpecial          (CATCGMNewMetaBloc *myClass, size_t Size);
         int                    deleteSpecial       (CATCGMNewMetaBloc *myClass, void* result);


  //-----------------------------------------------------------------------
  // Manages under session the allocated blocks:
  //    exits to definitively clean the memory
  //-----------------------------------------------------------------------
  static void                   cleanBeforeExit    ();  // final treament of cleaning
    
  static void                   DumpProvider       (ostream &logstat, CATCGMemoryProvider provider);

  //----------------------------------------------------------------------
  // Statistical file for memory (ODTNAME.CATCX_MEMORY)
  //-----------------------------------------------------------------------
  static const char            * GetAvailableLog   (CATCGMEventGarbage iEvent = CatCGMEndingExecution);  //  controled access to the CATCX_MEMORY log
  
  
#ifdef _WINDOWS_SOURCE 
         HANDLE                 _PrivateHeap;            // Gestion Heap privee
         CATBoolean             _PrivateHeapInitialized; // Gestion Heap privee
         CATBoolean             GetPrivateHeap();
  
  static HANDLE                 GetCATCGMemoryHeap();
  static CATBoolean             DestroyCATCGMemoryHeap();

#endif

  
  static CATSysPoolPtr          GetCATCGSysPool();
  static CATBoolean             DestroyCATCGSysPool();

  //-----------------------------------------------------------------------
  // Define allocation memory CATCX_QUOTA during a ODT
  // Statistics on the WorkingSet for the POOL
  //-----------------------------------------------------------------------
         CATCGMaxLong           _BytesCumulated;
         CATCGMaxLong           _WorkingSet_CURRENT;  // in number of DW (8 bytes)
         CATCGMaxLong           _WorkingSet_PEAK;     // in number of DW (8 bytes)


         CATCGMemoryProvider    _MemoryProvider;      // memory provider

       struct CATCGMemField
       {
        // petits attributs persistents
         unsigned char          _IsFlushable                  : 1;  // can we flush all objects
         unsigned char          _RetainLastBlock              : 1;  // keep last block (for temporary)
         unsigned char          _NoIntermediateDesallocation  : 1;  // ...
         unsigned char          _SortedPageAllocators         : 1;  // ...

       } MemField;

 

  virtual CATBoolean            AskNoIntermediateDesallocation(CATBoolean NoDesallocate);

          char                  _Name[5];             // Name of the POOL

  // taille en octets d'un bloc de pages (environ 500 ko)
          size_t                _DefaultBytesPerPageAllocator;

  //-----------------------------------------------------------------------
  // Detection of a data corruption in memory allocation
  //-----------------------------------------------------------------------
  static void                   Invalidity();

  //-----------------------------------------------------------------------
  // Detection d'un Multi-Threaded 
  //-----------------------------------------------------------------------
         CATCGMMutex          * MultiThreaded();
  static CATBoolean             QueryMultiThreadEnable();

  //----------------------------------------------------------------------------
  // LE POOL DE GESTION PAR DEFAULT 
  //---------------------------------------------------------------------------- 
  static CATCGMemoryPOOL      * SearchPOOL(const char IdentityPOOL[5]);   // deallocates the unused blocks
  static CATCGMemoryPOOL      * CreatePOOL(const char IdentityPOOL[5]);   // deallocates the unused blocks
  
  
  //----------------------------------------------------------------------------
  // Creation de l'allocateur de Tableau 
  //---------------------------------------------------------------------------- 
         CATCGMArrayPool      * CreateForArrays();

  static CATCGMArrayPool      * GetDefaultForArrays();

  static CATCGMArrayPool      * GetTemporaryForArrays();


  //----------------------------------------------------------------------------
  // Pour gestion des allocations temporaires
  //----------------------------------------------------------------------------
         CATCGMArrayPool      * _ForArrays;

  //----------------------------------------------------------------------------
  // Chainage Global des POOLS
  //---------------------------------------------------------------------------- 
         CATCGMemoryPOOL      * _NextMEModeler;



private :

  static void                   Boot();


  //------------------------------------------------------------------------------------
  // Chainages des CLASSES gere par ce POOL
  //------------------------------------------------------------------------------------
         CATCGMNewMetaBloc    * _FirstClass;     // chain the class allocated during the session
         CATCGMMutex          * _PoolMutex;

  //-----------------------------------------------------------------------
  // A global POOL MANAGER is given to the Debug
  //-----------------------------------------------------------------------
  CATCGMemoryPOOL(const char IdentityPOOL[5]);

  //-----------------------------------------------------------------------
  // SOME OTHER DEDICATED METHODS
  //-----------------------------------------------------------------------
         void                   optimizeArrayByClassNotPaged();   // deallocation of unused blocks  
         void                   DeleteAllObjects();

  //----------------------------------------------------------------------------
  //   PAGE ALLOCATION DEDICATED : 
  //       Famille = les objects de la meme taille memoire (au sens cga
  //       + Array of page allocators 
  //------------------------------------------------------------------------ 
         CATCGMNewManagement    _IdxSize[CATCGMNewDoublePerPage]; 


         int                    _MaxPageAllocators;
         int                    _HighestUsedPageAllocators;
 
   const int                    _NumberPageAllocators;
         CATCGMPageAllocator ** _PageAllocators;

         CATCGMPageAllocator  * _StaticPageAllocators;
  
  //----------------------------------------------------------------------------
  // SynchronousDelete DEDICATED :
  //----------------------------------------------------------------------------
         double              ** _ChainAllAllocations;

  //---------------------------------------------------------------------------------
 // service dedie a l'initialisation
  //----------------------------------------------------------------------------------
  static void                   InitializeUnderODT(const char *pOdtName);  


  static int                    CATCGM_exit_System(int rc);
  static void                   CATCGM_exit_atexit();

  friend class CATCGMPageAllocator;
  friend class CATCGMBreakPoint;
  friend class CATCGMNewMetaBloc;
  friend class CATCGAMEM;
  friend class CATMathDebugCGM;
  friend class CATMathODT;
  friend class CATMathODTCGM;
  friend class CGMDebugLife;
  friend class CATCGMThreadManager;

  friend class CATCGAMeasure;
  friend class CATCGAMeasureGlobal;
  friend class CATCGMemoryPOOL_Session;
  friend class PDQFrmDialog;

};


#endif
