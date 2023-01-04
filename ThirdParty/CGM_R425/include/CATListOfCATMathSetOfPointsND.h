#ifndef CATListOfCATMathSetOfPointsND_h
#define CATListOfCATMathSetOfPointsND_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/** 
 * @collection CATLISTP(CATMathSetOfPointsND)
 * Collection class for pointers to sets of N-dimensional mathematical points.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "YP00IMPL.h"


#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

#define  CATLISTPP_Append


//class CATMathSetOfPointsND;
#include "CATMathSetOfPointsND.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYP00IMPL

CATLISTPP_DECLARE_TS( CATMathSetOfPointsND, 10 )


#endif

