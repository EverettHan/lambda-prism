/* -*-C++-*-*/
#ifndef CATCGAMEMStats_H
#define CATCGAMEMStats_H
//
// COPYRIGHT DASSAULT SYSTEMES 1998
//
//==========================================================================
/**
 * Class used for memory management.
 */

//=============================================================================
// Jul. 02 Portage 64 bits                                                HCN
// Sep. 03 CATCGAMEMStats_GetCATCGMemBook(...)                            HCN
// Apr. 05 Arguments iopListOfCGMPOOLxxx pour
//            CATCGAMEMStats_GetCurrentWorkingSet(...)                    HCN
//=============================================================================
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATCollec.h"

#include "CATCGM_LightSession.h"

class CATCGMOutput;

#include "YN000MAT.h"
ExportedByYN000MAT void CATCGAMEMPrintStats(CATCGMOutput&);

//=============================================================================
struct CATCGAMEMStats
{
  const char*       ClassName;
        CATULONG32  ClassSize;
        CATULONG32  NbBlocs;
        CATULONG32  BlocSize;
        CATULONG32  AllocInstancesNumber;
        CATULONG32  AliveInstancesNumber;
        CATULONG32  FreeInstancesNumber;
        double      ClassUsage;
};

ExportedByYN000MAT void CATCGAMEMGetStats(CATULONG32     & NbStats   ,
                                          CATCGAMEMStats*& TabStats  ,
                                          size_t         & TotalUsed ,
                                          size_t         & TotalAlloc,
                                          double         & UsedPercentage );

//   The return value is very important for CATCGAMEM_AtExit
//  because it defines the value of an ::exit .
// 


ExportedByYN000MAT void CATCGAMEM_AtExit           ( CATCGAMEM_Exit fct );
ExportedByYN000MAT void CATCGAMEM_AtExit_Remove    ( CATCGAMEM_Exit fct );

ExportedByYN000MAT void CATCGAMEM_BeforeExit       ( CATCGAMEM_Exit fct );
ExportedByYN000MAT void CATCGAMEM_BeforeExit_Remove( CATCGAMEM_Exit fct );
//  
//       Retrieves the global values of the memory management
//   Allocated & Used Bytes in Heap dedicated for CGM Management
// 
ExportedByYN000MAT void CATCGAMEMStats_GetCurrentWorkingSet( size_t&       ioAllocatedBytes            ,
                                                             size_t&       ioUsedBytes                 ,
                                                             CATListPV*    iopListOfCGMPOOLNames       = NULL,
                                                             CATListOfInt* iopListOfCGMPOOLPageNbs     = NULL,
                                                             CATListOfInt* iopListOfCGMPOOLUsedPageNbs = NULL,
                                                             CATListOfInt* iopListOfCGMPOOLSizes       = NULL,
                                                             CATListOfInt* iopListOfCGMPOOLUsedSizes   = NULL);

// Stat figures far CATCGMemBook / CATCGMemClear calls
ExportedByYN000MAT void CATCGAMEMStats_GetCATCGMemBook(size_t &ioCurrentNbBook,
                                                       size_t &ioTotalNbBook,
                                                       size_t &ioCumulatedBytes,
                                                       size_t &ioRealCumulatedBytes, 
                                                       size_t &ioRealCumulatedFreedBytes);

#endif

