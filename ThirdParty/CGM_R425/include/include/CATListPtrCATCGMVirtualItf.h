#ifndef CATListPtrCATCGMVirtualItf_h_
#define CATListPtrCATCGMVirtualItf_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

/** 
 * @collection CATLISTP(CATCGMVirtualItf)
 * Collection class for pointers to fillet ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATMathematics.h"

class CATCGMVirtualItf;

#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATMathematics
CATLISTP_DECLARE( CATCGMVirtualItf )

#endif /* CATListPtrCATCGMVirtualItf_h_ */
