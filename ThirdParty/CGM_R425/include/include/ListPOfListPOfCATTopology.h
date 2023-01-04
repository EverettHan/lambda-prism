// COPYRIGHT DASSAULT SYSTEMES  2021
// EDS

#ifndef __ListPOfListPOfCATTopology_h__
#define __ListPOfListPOfCATTopology_h__

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATTopology.h"

/**
 * @collection CATLISTP(ListPOfCATTopology)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia.
 */

CATCGMLISTPP_DECLARE(ListPOfCATTopology);

typedef CATLISTP(ListPOfCATTopology) ListPOfListPOfCATTopology;

#endif
