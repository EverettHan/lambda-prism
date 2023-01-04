#ifndef ListPOfCATTopObject_h
#define ListPOfCATTopObject_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

class CATTopObject;
/** 
 * @collection CATLISTP(CATTopObject)
 * Collection class for pointers to topological objects.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"
//
// generate interface of collection class
// (functions declarations)
#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
/** @nodoc */
CATLISTPP_DECLARE_TS(CATTopObject, 10)
/** @nodoc */
typedef CATLISTP(CATTopObject) ListPOfCATTopObject;

#endif
