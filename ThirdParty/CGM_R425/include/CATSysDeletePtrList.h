#ifndef __CATSysDeletePtrList
#define __CATSysDeletePtrList
// COPYRIGHT DASSAULT SYSTEMES 2012

/**
* Macro used to delete or release objects in a list
*/
#include "CATSysMacros.h"

#define CATSysDeletePtrList(PtrList) { { for ( int PtrListIndex=(PtrList).Size(); PtrListIndex>0; PtrListIndex-- ) CATSysDeletePtr((PtrList)[PtrListIndex]);}; (PtrList).RemoveAll(); }
#define CATSysReleasePtrList(PtrList) { { for ( int PtrListIndex=(PtrList).Size(); PtrListIndex>0; PtrListIndex-- ) CATSysReleasePtr((PtrList)[PtrListIndex]);}; (PtrList).RemoveAll(); }

#endif
