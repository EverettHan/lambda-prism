/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//=============================================================================
/**
 * Interface defining class used for  memory management.
 */

//=============================================================================
// Jul. 02 Portage 64 bits : suppression warnings                         HCN
// Sep. 03 Portage 64 bits : remplacement des CATULONG32  par des CATULONG32
//         pour compatibilite Intex/Unix                                  HCN
// Apr. 05 Arguments iopListOfCGMPOOLxxx pour GetCurrentWorkingSet(...)   HCN
//=============================================================================

#ifndef CATCGMPageAllocator_H
#define CATCGMPageAllocator_H

#include <stddef.h>
#include "CATMathematics.h"
#include "CATBooleanDef.h"

#include "CATCGMemoryPOOL.h"

#include "CATDataType.h"

#ifdef _WINDOWS_SOURCE 
#include <Windows.h>
#endif

struct CATCGAMEMStats;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif



#if defined ( PLATEFORME_DS64 )

  //    MAXPageAllocator_NumberOfPages =  1  <<    (_PageAllocator_BlobBits -12)        :  2048 =  1 <<  11  in 64 bits
  //    MAXPageAllocator_MaxKbits      =  1  <<  ( (_PageAllocator_BlobBits -12) - 5 )  :    64 =  1 <<   6  in 64 bits

#define MAXPageAllocator_MaxKbits         64
#define MAXPageAllocator_NumberOfPages  2048

#else

  //    MAXPageAllocator_NumberOfPages =  1  <<    (_PageAllocator_BlobBits -12)        :  128  =  1 <<  7  in 32 bits
  //    MAXPageAllocator_MaxKbits      =  1  <<  ( (_PageAllocator_BlobBits -12) - 5 )  :    4  =  1 <<  2  in 32 bits

#define MAXPageAllocator_MaxKbits         4
#define MAXPageAllocator_NumberOfPages  128

#endif




 
#define NoCorruptExpected               0xACE0BEEF


class CATCGMemoryPOOL;
class CATCGAMEM;
class CATMathDebugCGM;
class CATMathODT;
class CATMathODTCGM;


class ExportedByCATMathematics CATCGMPageAllocator 
{
public  :

  static double *NeedPage(int size, CATCGMemoryPOOL  *POOL);
  void           FreeThePage(int numpage, int size);


  static void    optimize(CATCGMemoryPOOL  *POOL);   // desallocation bloc inutilise

  static void    DeleteAllObjects(CATCGMemoryPOOL  *POOL);   // supression de Tous les POOLS

  static void    ResetAllObjects(CATCGMemoryPOOL  *POOL);   // reinitialisation de Tous les POOLS

  static CATCGMPageAllocator *SearchAllocator(CATCGMemoryPOOL  *POOL, const void *obj,   int &numpage, int &NbDoublesForControl);

  int GetNumberOfLockedPage();

  int HasOnlyFreePages();

  static void    DeleteAllocator(CATCGMPageAllocator *alloc, int numAllocator, CATCGMemoryPOOL  *POOL);  // desallocation
  
  //-----------------------------------------------------------------------
  // Utilitaire de Debug
  //-----------------------------------------------------------------------
 
  static const void* CheckAddress(const void* pointer);
  
  static void GetCurrentWorkingSet( size_t&       ioAllocatedBytes,
                                    size_t&       ioUsedBytes,
                                    CATListPV*    iopListOfCGMPOOLNames = NULL,
                                    CATListOfInt* iopListOfCGMPOOLPageNbs = NULL,
                                    CATListOfInt* iopListOfCGMPOOLUsedPageNbs = NULL,
                                    CATListOfInt* iopListOfCGMPOOLSizes = NULL,
                                    CATListOfInt* iopListOfCGMPOOLUsedSizes = NULL);
  
  //---------------------------------------------------------------------------
  // Gestion d'une eventuelle table associative pour les allocations de 512 Ko
  // Mais on peut garantir que cet acces direct reussi, d'ailleurs il y a en general
  //    - INSERT  : deux cases possibles ou inserer un Allocator
  //    - QUERY   : trois cases eventuelles ou on recherchera un Allocator
  //                 a partir de l'adresse d'un Objet
  // Toutefois ce codage permets dans le cas standard
  //    un access direct O(1) plutot qu'en O(n)
  //---------------------------------------------------------------------------


private :

  
  static CATCGMPageAllocator *SortSearchAllocator(CATCGMemoryPOOL  *POOL, const void *obj,  int &numpage, int &NbDoublesForControl);
  static CATCGMPageAllocator *PoorSearchAllocator(CATCGMemoryPOOL  *POOL, const void *obj,  int &numpage, int &NbDoublesForControl);
  static CATCGMPageAllocator *UnfoundAllocator();
  static CATCGMPageAllocator *InconsistentAllocator();

  double *ReserveOnePage(int size); 

  static CATCGMPageAllocator *newAllocator(double *bigBloc, size_t numberOfBytes, CATCGMemoryPOOL  *POOL, CATCGMemoryProvider  CurProvider);

  // detection ecrasement memoire
  CATULONG32          _CorruptDetect;

  CATCGMMutex       * _mutex;
  CATCGMemoryPOOL   * _MEModeler;

  CATCGMemoryProvider  _Provider;    

  // reference de la premiere et derniere page
  double            * _firstpage;
  char              * _endValidpage;

  // reference de la premiere page
  double            * _allocationAddress;
  size_t              _allocationBytes;
  

  // indirection gestionnaire global de la famille d'object
  //    CATCGMNewMetaBloc::..IdxSize[] 
  size_t             _NumberOfPages;
  size_t             _MaxKbits;

  // Etat d'occupation d'une Page :  0 libre, 1 : occupe  ( 32 pages par bitspage )
  //     4*32 = 128 bits = CATCGMPagePerAllocator

  //
  //    MAXPageAllocator_NumberOfPages =  1  <<    (_PageAllocator_BlobBits -12)        :  2048 =  1 <<  11  in 64 bits
  //    MAXPageAllocator_MaxKbits      =  1  <<  ( (_PageAllocator_BlobBits -12) - 5 )  :    64 =  1 <<   6  in 64 bits
  //

  CATULONG32         _bitsPage          [ MAXPageAllocator_MaxKbits ];      
  CATULONG32         _bitsForbiddenPage [ MAXPageAllocator_MaxKbits ];        
  short              _SizeInPage        [ MAXPageAllocator_NumberOfPages ]; // Toujours laisser en dernier ...


  friend class CATCGMemoryPOOL;
  friend class CATCGAMEM;
  friend class CATMathDebugCGM;
  friend class CATMathODT;
  friend class CATMathODTCGM;
};


#endif

//automate:31/08/01:suppression include de CATCGMNewMetaBloc.h
