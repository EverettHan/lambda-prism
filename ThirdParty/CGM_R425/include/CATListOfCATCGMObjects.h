#ifndef CATListOfCATCGMObjects_h
#define CATListOfCATCGMObjects_h

#include "ExportedByCATCGMFusion.h"

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
// Dec. 03 CATCGMObjectTagCompareFunction                                 HCN
//=============================================================================

#include "CATCGMLISTPP_Declare.h"

class CATCGMObject;

CATCGMLISTPP_DECLARE(CATCGMObject);

ExportedByCATCGMFusion int CATCGMObjectTagCompareFunction(CATCGMObject* ipCGMObject1, CATCGMObject* ipCGMObject2);


#endif

