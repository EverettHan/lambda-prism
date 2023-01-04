#ifndef CATCGMemory_H
#define CATCGMemory_H
/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  HEADER IMPLEMENTATION : INTERDICTION D'INCLURE DANS HEADER CAA
//
// Fonctions d allocation memoire CGM dans une Heap privee
//=============================================================================

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "CATMathematics.h"
#include "CATDataType.h"
#include "CATCGMemoryProvider.h"

//----------------------------------------------------------------------------------------------
// Si vous n'avez aucune attente  sur l'allocateur memoire (malloc/Heap/Virtual/new ..) 
// Afin d'eviter soi-meme a la main les allocations de facon plus optimale, 
// voici un enrobage securise plus approprie pour les allocations a CGM
//----------------------------------------------------------------------------------------------

ExportedByCATMathematics void * CATCGMemBook   (size_t iWantedBytes, 
                                                CATCGMemoryProvider iForceProvider = CATCGMemoryProvider_BestSoFar); 

ExportedByCATMathematics void   CATCGMemClear  (void * iAllocated,   
                                                CATCGMemoryProvider iForceProvider = CATCGMemoryProvider_BestSoFar); 

ExportedByCATMathematics void * CATCGMemExtend (size_t iOldUsedBytes,
                                                void * iOldAllocated,  
                                                size_t iWantedBytes, 
                                                CATCGMemoryProvider iForceProvider = CATCGMemoryProvider_BestSoFar); 

/*
   double *CATCGMemDoubleBook (const size_t    iNumberOfDouble)
   void    CATCGMemDoubleClear(double        * iAllocated) 
*/
#define CATCGMemDoubleBook(iNumberOfDouble)    (double *)CATCGMemBook( (iNumberOfDouble) << 3 ,CATCGMemoryProvider_BestSoFar)
#define CATCGMemDoubleClear(iAllocated)                  CATCGMemClear((void *)iAllocated     ,CATCGMemoryProvider_BestSoFar)



/*
   void * *catcxPtrNew (const size_t    iNumberOfPointer)
   void    catcxPtrFree(void  *       * iAllocated)
*/
#ifdef PLATEFORME_DS64
#define catcxPtrNew(iNumberOfPointer) (void **) CATCGMemBook( (iNumberOfPointer) << 3 ,CATCGMemoryProvider_BestSoFar)
#define catcxPtrFree(iAllocated)                CATCGMemClear((void *)iAllocated      ,CATCGMemoryProvider_BestSoFar)
#else
#define catcxPtrNew(iNumberOfPointer) (void **) CATCGMemBook( (iNumberOfPointer) << 2 ,CATCGMemoryProvider_BestSoFar)
#define catcxPtrFree(iAllocated)                CATCGMemClear((void *)iAllocated      ,CATCGMemoryProvider_BestSoFar)
#endif

/*
   double *catcxDoubleNew (const size_t    iNumberOfDouble)
   void    catcxDoubleFree(double        * iAllocated)
*/
#define catcxDoubleNew(iNumberOfDouble)    (double *)CATCGMemBook( (iNumberOfDouble) << 3 ,CATCGMemoryProvider_BestSoFar)
#define catcxDoubleFree(iAllocated)                  CATCGMemClear((void *)iAllocated     ,CATCGMemoryProvider_BestSoFar)



/*
   float  *catcxFloatNew (const size_t    iNumberOfFloat)
   void    catcxFloatFree(float         * iAllocated) 
*/
#define catcxFloatNew(iNumberOfFloat)    (float *)CATCGMemBook( (iNumberOfFloat) << 2 ,CATCGMemoryProvider_BestSoFar)
#define catcxFloatFree(iAllocated)                CATCGMemClear((void *)iAllocated    ,CATCGMemoryProvider_BestSoFar)



/*
   short  *catcxShortNew (const size_t     iNumberOfShort)
   void    catcxShortFree(short          * iAllocated)
*/
#define catcxShortNew(iNumberOfShort)    (short *)CATCGMemBook( (iNumberOfShort) << 1  ,CATCGMemoryProvider_BestSoFar)
#define catcxShortFree(iAllocated)                CATCGMemClear((void *)iAllocated     ,CATCGMemoryProvider_BestSoFar)



#endif

