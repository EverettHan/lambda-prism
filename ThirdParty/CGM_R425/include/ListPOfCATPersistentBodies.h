/* -*-c++-*- */
#ifndef ListPOfCATPersistentBodies_h
#define ListPOfCATPersistentBodies_h

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATPersistentBody;

/** 
 * @collection CATLISTP(CATPersistentBody)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATPersistentBody);

typedef CATLISTP(CATPersistentBody) ListPOfCATPersistentBodies;

#endif


