// COPYRIGHT Dassault Systemes 2015
//===================================================================
//
// ListPOfCDMBaseServices.h
//
//===================================================================
//
// Declaration of CATLISTP(CDMBaseServices)
//
//===================================================================
//
//  Aor 2015  Creation:  CN8

//===================================================================
#ifndef ListPOfCDMBaseServices_H
#define ListPOfCDMBaseServices_H

// Enable pointers lists
#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"
#include "CATCDMBaseInterfaces.h" // export

class CATCDMBaseServices;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCDMBaseInterfaces

CATLISTP_DECLARE( CATCDMBaseServices )
typedef CATLISTP(CATCDMBaseServices) CATListPtrCATCDMBaseServices;

//------------------------------------------------------------------

#endif
