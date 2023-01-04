/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//  Controls a memory address of an object already allocated
//    in the Heap with new/delete overloading
//
//
//  --> These tests are only activated in debug mode (ODT or CATDevelopmentStage)
//      In ODT mode, a problem due to an invalid access memory -> code 117
//      In CATDevelopmentStage mode, throws an exception
//
//==========================================================================
/**
 * For Testing validity of the area pointed by the given argument
 * For Robustness
 */
#ifndef CATCGAMEMCheck_H
#define CATCGAMEMCheck_H

#include "CATMathematics.h"

ExportedByCATMathematics void  CATCGAMEMCheck(const void* pointeur);

#endif

