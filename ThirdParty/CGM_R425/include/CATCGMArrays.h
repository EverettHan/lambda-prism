/* -*-c++-*- */
#ifndef CATCGMArrays_h
#define CATCGMArrays_h
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
// Nov  05  Perfos                                                      PR
//===========================================================================

#include "CATMathematics.h"
#include "CATCGMaxLong.h"
#include "CATDataType.h"
#include "CATCGMVirtual.h"

/**
 * Allocating and Freeing a array of pointer
 */

ExportedByCATMathematics  void **CATCGMArrayPtrsNew(const size_t iNumberOfPointer);
ExportedByCATMathematics  void **CATCGMArrayPtrsResize(void **iOldPacked,
                                                       const size_t iOldNumberOfPointer,
                                                       const size_t iNewNumberOfPointer);
ExportedByCATMathematics  void   CATCGMArrayPtrsDel(void **iPacked,const size_t iNumberOfPointer);

/**
 * Allocating and Freeing a array of CATULONGPTR and unsigned char
 * The unsigned char Array is found with    unsigned char * TabUChar =  (unsigned char *) (result+Number);;
 */
ExportedByCATMathematics  CATULONGPTR *CATCGMArrayUPtrsUCharNew(const size_t iNumber);
ExportedByCATMathematics  CATULONGPTR *CATCGMArrayUPtrsUCharResize(CATULONGPTR *iOldPacked,
                                                                   const size_t iOldNumber,
                                                                   const size_t iNewNumber);
ExportedByCATMathematics  void         CATCGMArrayUPtrsUCharDel(CATULONGPTR *iPacked, const size_t iNumber);


/**
 * Allocating and Freeing a array of double
 */
ExportedByCATMathematics  double *CATCGMArrayDoubleNew(const size_t iNumberOfDouble);
ExportedByCATMathematics  double *CATCGMArrayDoubleResize(double *iOldPacked,
                                                          const size_t iOldNumberOfDouble,
                                                          const size_t iNewNumberOfDouble);
ExportedByCATMathematics  void    CATCGMArrayDoubleDel(double *iPacked,const size_t iNumberOfDouble);

// Array of 0x10_aligned doubles, for Intel & AMD SSE2 processor architecture

ExportedByCATMathematics  double *CATCGMAlignedDoubleNew
  (const size_t iNumberOfDouble);
ExportedByCATMathematics  void    CATCGMAlignedDoubleDel
  (double *iPacked,const size_t iNumberOfDouble);

/**
 * Allocating and Freeing a array of double an short
 */
ExportedByCATMathematics  double *CATCGMArrayDoubleShortNew(const size_t iNumber, short * &iTabShort);
ExportedByCATMathematics  void    CATCGMArrayDoubleShortDel(double *iPacked, const size_t iNumbershort, short *iTabShort);


/**
 * Allocating and Freeing a array of float
 */
ExportedByCATMathematics  float  *CATCGMArrayFloatNew(const size_t iNumberOfFloat);
ExportedByCATMathematics  float  *CATCGMArrayFloatResize(float *iOldPacked,
                                                         const size_t iOldNumberOfFloat,
                                                         const size_t iNewNumberOfFloat);
ExportedByCATMathematics  void    CATCGMArrayFloatDel(float *iPacked,const size_t iNumberOfFloat);


/**
 * Allocating and Freeing a bag of Bytes
 */
ExportedByCATMathematics  void   *CATCGMArrayBytesNew(const size_t iNumberOfBytes);
ExportedByCATMathematics  void   *CATCGMArrayBytesResize(void  *iOldPacked,
                                                         const size_t iOldNumberOfBytes,
                                                         const size_t iNewNumberOfBytes);
ExportedByCATMathematics  void    CATCGMArrayBytesDel(void *iPacked,const size_t iNumberOfBytes);


/**
 * Allocating and Freeing a bag of Bytes
 */
ExportedByCATMathematics  void  CATCGMArrayStatsOutside(CATCGMaxLong &ioNumberOfAlloc,
                                                        CATCGMaxLong &ioSumBytesAtMax,
                                                        CATCGMaxLong &ioSumBytesCumulated);

#endif

