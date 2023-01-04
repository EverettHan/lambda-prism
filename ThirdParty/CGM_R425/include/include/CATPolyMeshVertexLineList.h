// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshVertexLineList.h
// Header definition of CATPolyMeshVertexLineList
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// January 2008  Creation: NDO
//===================================================================
#ifndef CATPolyMeshVertexLineList_H
#define CATPolyMeshVertexLineList_H

#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"

#include "PolyMeshImpl.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyMeshImpl

class CATPolyMeshVertexLine;

CATLISTP_DECLARE(CATPolyMeshVertexLine);

typedef CATLISTP(CATPolyMeshVertexLine) CATPolyMeshVertexLineList;

#endif
