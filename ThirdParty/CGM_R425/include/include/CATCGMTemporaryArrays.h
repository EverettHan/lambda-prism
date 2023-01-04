/* -*-c++-*- */
#ifndef CATCGMTemporaryArrays_h
#define CATCGMTemporaryArrays_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//  
//  1) ** RESERVED FOR DATA MEMBERS OF GEOMETRY/TOPOLOGY MODELISATION ** 
//  2) ** ADAPTED  FOR SMALL ARRAYS ** 
//  3) ** All allocation and freeing muste be done in the same WAY
//  
//  All array described above must be mastered in their Life Cycle
//

//===========================================================================
// Jui  02  Portage 64 bits                                             HCN
//===========================================================================

#include <stddef.h>
#include <stdlib.h>

#include "CATMathematics.h"

class CATCGAMEM;

/**
 * Allocating and Freeing a array of double
 */
ExportedByCATMathematics  double *CATCGMTemporaryArrayDoubleNew(const size_t iNumberOfDouble,
                                                                CATCGAMEM *iPool = NULL);

ExportedByCATMathematics  double *CATCGMTemporaryArrayDoubleResize(double *iOldPacked,
                                                                   const size_t iOldNumberOfDouble,
                                                                   const size_t iNewNumberOfDouble,
                                                                   CATCGAMEM *iPool = NULL);

ExportedByCATMathematics  void    CATCGMTemporaryArrayDoubleDel(double *iPacked,const size_t iNumberOfDouble,
                                                                CATCGAMEM *iPool = NULL);


#endif

