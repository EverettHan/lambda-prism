#ifndef ListPOfCATDRepSeed_h
#define ListPOfCATDRepSeed_h

// COPYRIGHT DASSAULT SYSTEMES  2011

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATDRepSeed;

/** 
 * @collection CATLISTP(CATDRepSeed)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATDRepSeed);

typedef CATLISTP(CATDRepSeed) ListPOfCATDRepSeed;

#endif
