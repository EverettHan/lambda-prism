#ifndef CATCGMemoryProvider_H
#define CATCGMemoryProvider_H
/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  HEADER IMPLEMENTATION : INTERDICTION D'INCLURE DANS HEADER CAA
//
// Fonctions d allocation memoire CGM dans une Heap privee
//=============================================================================

typedef unsigned char CATCGMemoryProvider;
#define CATCGMemoryProvider_BestSoFar 'x'
#define CATCGMemoryProvider_malloc    'm'
#define CATCGMemoryProvider_new       'n'
#define CATCGMemoryProvider_Heap      'h'
#define CATCGMemoryProvider_Virtual   'v'
#define CATCGMemoryProvider_SysAlloc  's'
#define CATCGMemoryProvider_AMAS      'a'


#endif

