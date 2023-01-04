// COPYRIGHT Dassault Systemes 2011
//===================================================================
//
// ListPOfGMConstraint.h
//
//===================================================================
//
// Declaration of CATLISTP(CATGMConstraint)
//
//===================================================================
//
//  May 2011  Creation:  CHU

//===================================================================
#ifndef ListPOfGMConstraint_H
#define ListPOfGMConstraint_H

// Enable pointers lists
#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"
#include "CATCDMBaseInterfaces.h" // export

class CATGMConstraint;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCDMBaseInterfaces

// #include "CATGMConstraint.h"

CATLISTP_DECLARE( CATGMConstraint )
typedef CATLISTP(CATGMConstraint) CATListPtrCATGMConstraint;

//------------------------------------------------------------------

#endif
