/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1998
//
//=============================================================================
// Jul. 02  Portage 64 bits                                              HCN
// May  03  SetExitForODTOnBadNewSpecial                                 HCN
//=============================================================================

#ifndef CATCGAMEM_H
#define CATCGAMEM_H

#include <stddef.h>
#include "CATMathematics.h"
#include "CATBooleanDef.h"
#include "CATCGMemoryProvider.h"
#include "CATDataType.h"

class  CATCGMMutex;
class  CATCGMNewMetaBloc;
class  CATCGMPageAllocator;
struct CATCGAMEMStats;
class  CATCGMOutput;
class  CATICGMUnknown;

/**
* Class used for  memory management.
*/
class ExportedByCATMathematics CATCGAMEM
{
public :
/**
* Defines the parameterization of the CGM memory allocation.
* The choice is done only once at the initialization of the CGM session.
  */
  enum CATMemoryStrategy { ArrayByClass      = +13,
                           SynchronousDelete = +23,
                           ArrayByPage       = +44 };
  
  virtual             ~CATCGAMEM            ();

  //-----------------------------------------------------------------------
  // BE CAREFUL : DEDICATED TO TRANSACTIONAL OBJECT
  //   Tessellation ...
  //-----------------------------------------------------------------------
  static  void         DeleteAllObjects     (const char                IdentityPOOL[5]);
  
  //-----------------------------------------------------------------------
  //    optimizes to free the free blocks
  //-----------------------------------------------------------------------
  static  void         EmptyRecycleBin      ();   // deallocates the unused blocks
  
   
  //-----------------------------------------------------------------------
  // Encapsulates the memory allocation stategy
  //-----------------------------------------------------------------------
  static  void         initMutex            (      CATCGAMEM        *  pool            ,
                                                   CATCGMMutex     **  mutex           );
  
  static  int          init                 (      CATCGMNewMetaBloc*& ioLocalMngt     ,
                                                   size_t              iSize           ,
                                             const int                 iNBOBJ          ,
                                             const char             *  iClassname      ,
                                             const char                iIdentityPOOL[5],
                                                   CATCGAMEM        *  pool            );

  
  //-----------------------------------------------------------------------
  // Prints the current statistics on the current memory management
  //-----------------------------------------------------------------------
  static  void         stats                ();

  //-----------------------------------------------------------------------
  // detetion of an ODT replay in Purify mode
  //-----------------------------------------------------------------------
  static  CATBoolean   IsExecutedUnderPurify(); 
  
  //-----------------------------------------------------------------------
  // For Debug use
  //-----------------------------------------------------------------------
  static  void         CheckAddress         (const void             *  pointer         ,
                                                   CATCGMNewMetaBloc*  cganew          );
  
  //-----------------------------------------------------------------------
  // GeometricObjects\ProtectedInterfaces\CATCGMValidObject.h
  //-----------------------------------------------------------------------
  static  CATBoolean   IsInsideMemoryPool   (      CATICGMUnknown   *  iUnknown        );
  
  //-----------------------------------------------------------------------
  // Controls the consistency of the informations of memory management
  //-----------------------------------------------------------------------
  virtual void         CheckConsistency     () = 0;
  
  //-----------------------------------------------------------------------
  // data of the memory management associated to a MODELER
  //-----------------------------------------------------------------------
  CATMemoryStrategy  _Strategy;  // allocation Perfo, Debug, Purify

  //-----------------------------------------------------------------------
  // Array management in the same POOL as one Objects
  //-----------------------------------------------------------------------
  static  void       * NewArray             (      CATCGAMEM        *  iPool           ,
                                                   size_t              iNumberOfBytes  );

  static  void         DelArray             (      CATCGAMEM        *  iPool           ,
                                                   size_t              iNumberOfBytes  ,
                                                   void             *  iResult         );

  static  CATCGAMEM  * Query                (const char                IdentityPOOL [5]);

  //-----------------------------------------------------------------------
  // Pour l'implementation des operateurs new/delete
  //-----------------------------------------------------------------------
  static  double     * allocate             (      CATCGAMEM        *  pool            ,
                                                   CATCGMNewMetaBloc*  bloc            );

  static  void         desallocate          (      CATCGAMEM        *  pool            ,
                                                   CATCGMNewMetaBloc*  cganew          ,
                                                   double           *  area            );

  virtual void       * newSpecial           (      CATCGMNewMetaBloc*  myClass         ,
                                                   size_t              Size            ) = 0;
  virtual int          deleteSpecial        (      CATCGMNewMetaBloc*  myClass         ,
                                                   void             *  result          ) = 0;
  
  //------------------------------------------------------------------------ 
  // Pour DEBUG : INTERNAL ONLY
  //------------------------------------------------------------------------ 
  static  void         PrintStats           (      CATCGMOutput      &                 );
  static  void         GetStats             (      CATULONG32        & NbStats         ,
                                                   CATCGAMEMStats   *& TabStats        ,
                                                   size_t            & TotalUsed       ,
                                                   size_t            & TotalAlloc      ,
                                                   double            & UsedPercentage  );
  
  //------------------------------------------------------------------------ 
  // Pour Gestion Multi-Thread
  //------------------------------------------------------------------------ 
  static  CATCGMMutex* GlobalMultiThreaded  ();
  static  int          GetThreadManagerMode ();


  //-----------------------------------------------------------------------
  // BE CAREFUL : DEDICATED TO RESTRICTED AND INTERNAL USE ...
  //    returned value gives the old management
  //
  // 1) EmptyRecycleBin() does not take into account this status
  // 2) Control is done under ODT to ensure that this query is made under a short transaction .....
  // 3) Useless memory allocation will be desallocated coming back 
  //     to NoDesallocate = FALSE ....
  //-----------------------------------------------------------------------
  static  void AskNoIntermediateDesallocation(const char               IdentityPOOL [5],
                                                    CATBoolean         NoDesallocate   ,
                                                    CATBoolean       & ioPoolFound     ,
                                                    CATBoolean       & ioOldValueNoDesallocate);

  
  static CATCGAMEM::CATMemoryStrategy  GetPool_Default_Strategy();

  static void          SetExitForODTOnBadNewSpecial(CATBoolean iActive = TRUE);


protected :


  virtual CATBoolean AskNoIntermediateDesallocation(CATBoolean NoDesallocate) = 0;
  virtual void         FreeUnusedAllocation          () = 0;   // deallocates the unused blocks


  friend class CATCGMPageAllocator;
  friend class CGMDebugLife;
  friend class CATCGMNewMetaBloc;
  friend class CATCGMemoryPOOL;
  friend class CATMathDebugCGM;
  friend class CATMathODTCGM;
  friend class CATCGMThreadManager;
};



#endif

