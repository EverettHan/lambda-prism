#ifndef ListPOfCATIPGMTopOperator_h
#define ListPOfCATIPGMTopOperator_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATIPGMTopOperator;

/** 
 * @collection CATLISTP(CATIPGMTopOperator)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATIPGMTopOperator);

typedef CATLISTP(CATIPGMTopOperator) ListPOfCATIPGMTopOperator;

#endif
