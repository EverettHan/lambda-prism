#ifndef CATICGMObjectCATHTAB_H
#define CATICGMObjectCATHTAB_H

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
//
// CATICGMObjectCATHTAB:
// Base class for HashTable of CATICGMObjects
//
//=============================================================================
// Mar. 04 Creation                                                       HCN
//=============================================================================
#include "YP0LOGRP.h"

class CATICGMObject;

#include "CATHTAB_Clean.h"
#define CATHTAB_Insert
#define CATHTAB_Locate
#define CATHTAB_Next
#define CATHTAB_KeyLocate
#define	CATHTAB_NextPosition
#define CATHTAB_Remove
#define CATHTAB_RemoveAll

#include "CATHTAB_Declare.h"
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYP0LOGRP
CATHTAB_DECLARE( CATICGMObject )

ExportedByYP0LOGRP unsigned int HashKeyCATCGMObject(CATICGMObject* ipICGMObject);
ExportedByYP0LOGRP int CompareCATCGMObject(CATICGMObject* ipICGMObject1, CATICGMObject* ipICGMObject2);                                    


#endif
