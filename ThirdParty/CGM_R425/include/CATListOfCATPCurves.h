#ifndef CATListOfCATPCurves_h
#define CATListOfCATPCurves_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/** 
 * @collection CATLISTP(CATPCurve)
 * Collection class for pointers to curves defined on the space of a surface.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "YP00IMPL.h"


#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"


class CATPCurve;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYP00IMPL

CATLISTPP_DECLARE_TS( CATPCurve , 10)


#endif

