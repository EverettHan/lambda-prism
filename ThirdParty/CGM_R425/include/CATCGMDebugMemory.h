/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 2001
// Pour Debug synchrone des allocations/desallocations effectuees a CGM
// 
//
//==========================================================================
// Jui 02   Portage 64 bits                   HCN
//==========================================================================

#ifndef CATCGMDebugMemory_H
#define CATCGMDebugMemory_H

#include "CATMathematics.h"

//============================================================================================
// A inserer dans le code ou l'on soupconne les plus grosses allocations/desallocations
//============================================================================================

ExportedByCATMathematics extern short CATCGMIsDebuggingMemory;

ExportedByCATMathematics void CATCGMDebugMemoryMalloc(const size_t numberOfBytes, const char Message[]);

ExportedByCATMathematics void CATCGMDebugMemoryFree(const size_t numberOfBytes, const char Message[]);


/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

ExportedByCATMathematics ostream & CATCGMDebugMemoryLOG(ostream &);

ExportedByCATMathematics void      CATCGMDebugMemoryGlobalDump(const char Message[]);

//==========================================================================
// Pour un debug Interactif (dedie a la commande c:cgamem)
//==========================================================================

typedef void (*CATCGMDebugMemoryFeedBack)(const short IsAllocating, const size_t numberOfBytes, const char Message[]) ;

ExportedByCATMathematics void CATCGMDebugMemoryUI(CATCGMDebugMemoryFeedBack fonction);


#endif

