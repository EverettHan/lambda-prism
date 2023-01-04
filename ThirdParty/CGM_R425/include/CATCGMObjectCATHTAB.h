/* -*-c++-*- */
#ifndef CATCGMObjectCATHTAB_H
#define CATCGMObjectCATHTAB_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMObjectCATHTAB:
// Base class for HashTable of CATCGMObject
//
//=============================================================================
// Usage notes:
//
// this is an implementation of the CATGeoFactory which uses
// internal container facilities for performances reasons.
//
// Every Object able to create CXR2 geometric objects should inherit from me.
//=============================================================================
// Mar. 97   Creation                                     R. Rorato
//=============================================================================
#include "ExportedByCATCGMFusion.h"

class CATCGMObject;

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
#define CATCOLLEC_ExportedBy ExportedByCATCGMFusion
CATHTAB_DECLARE( CATCGMObject )

ExportedByCATCGMFusion unsigned int HashKeyCATCGMObject(CATCGMObject* inew);
ExportedByCATCGMFusion int CompareCATCGMObject(CATCGMObject* i1, CATCGMObject *i2);                                    


#endif
