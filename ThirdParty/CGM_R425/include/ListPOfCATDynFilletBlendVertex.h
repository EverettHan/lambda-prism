// COPYRIGHT DASSAULT SYSTEMES 2003
#ifndef CATListPOfDynFilletBlendVertex_h_
#define CATListPOfDynFilletBlendVertex_h_
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
/** 
 * @collection CATLISTP(CATDynFilletBlendVertex)
 * Collection class for pointers to the radius definition in a ribbon.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

#include "CATGMOperatorsInterfaces.h"

class CATDynFilletBlendVertex;

#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynFilletBlendVertex )


#endif
