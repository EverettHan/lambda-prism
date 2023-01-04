// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// ListPOfGMEquation.h
//
//===================================================================
//
// Declaration of CATLISTP(CATGMEquation)
//
//===================================================================
//
//  Nov 2012  Creation:  CN8

//===================================================================
#ifndef ListPOfGMEquation_H
#define ListPOfGMEquation_H

// Enable pointers lists
#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"
#include "CATCDMBaseInterfaces.h" // export

class CATGMEquation;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCDMBaseInterfaces


CATLISTP_DECLARE( CATGMEquation )
typedef CATLISTP(CATGMEquation) CATListPtrCATGMEquation;

//------------------------------------------------------------------

#endif
