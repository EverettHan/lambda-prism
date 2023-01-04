/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 2001
// Pour Debug synchrone des allocations/desallocations effectuees a CGM
// 
//
//=============================================================================
// * @quickReview 666 13:04:01  2013 Week15 / Assembly Design Scalability / Functions =(Product Filtering-Import CCP)  / Customer = Toyota + Exchanges / Modeler CGM
//=============================================================================

#ifndef CATCGMDebugMemoryLocal_H
#define CATCGMDebugMemoryLocal_H

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ofstream;
#endif
#include "CATMathematics.h"
#include "CATCGMaxLong.h"
#include "CATDataType.h"

extern ExportedByCATMathematics ostream*  CATCGMDebugMemoryOutput;   // sortie des traces

extern ExportedByCATMathematics ofstream* CATCGMDebugMemoryDedicatedOutput;   // sortie des traces

extern ExportedByCATMathematics size_t    CATCGMDebugMemoryPeak;    // Autorisation d'un Peak maximal (working set)

extern ExportedByCATMathematics size_t    CATCGMDebugMemoryQuota;    // Autorisation d'un Peak maximal

extern ExportedByCATMathematics size_t    CATMathStreamSizeMultipleBuffer;    // taille minimale Reallocation File/Save

extern ExportedByCATMathematics CATLONG32      CATCXIO_NUMBER;    // Nombre d'operations I/O provoque dans le code CGM

extern ExportedByCATMathematics CATLONG64      CATCXTOPO_ACTIVATE;    // Complexite d'objets affectes par Body->Activate

extern ExportedByCATMathematics CATLONG64      CATCGM_InitTransactionBit;    

extern ExportedByCATMathematics CATLONG32      CATCX_HeapDestroy;    // Nombre d'operations HeapDestroy dans le code CGM

extern ExportedByCATMathematics CATLONG64      CATCXListMembers_Containers;    // istMembers

extern ExportedByCATMathematics CATLONG64      CATCXListMembers_Objects;    //  


#endif

