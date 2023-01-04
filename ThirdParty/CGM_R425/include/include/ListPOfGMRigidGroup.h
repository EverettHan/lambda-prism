// COPYRIGHT Dassault Systemes 2010
//===================================================================
//
// ListPOfGMRigidGroup.h
//
//===================================================================
//
// Declaration of CATLISTP(CATGMRigidGroup)
//
//===================================================================
//
//  Oct 2010  Creation:  CHU

//===================================================================
#ifndef ListPOfGMRigidGroup_H
#define ListPOfGMRigidGroup_H

// Enable pointers lists
#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"
#include "CATCDMBaseInterfaces.h" // export

class CATGMRigidGroup;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCDMBaseInterfaces

// #include "CATGMRigidGroup.h"

CATLISTP_DECLARE( CATGMRigidGroup )
typedef CATLISTP(CATGMRigidGroup) CATListPtrCATGMRigidGroup;

//------------------------------------------------------------------

#endif
