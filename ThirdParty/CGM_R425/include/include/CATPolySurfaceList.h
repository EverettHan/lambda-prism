// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceList.h
//
//===================================================================
//
// December 2009  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceList_H
#define CATPolySurfaceList_H

class CATIPolySurface;

//
#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"

//
#include "CATLISTP_Declare.h"

//
#include "PolyhedralModel.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyhedralModel

//
CATLISTP_DECLARE(CATIPolySurface);

typedef CATLISTP(CATIPolySurface) CATPolySurfaceList;

#endif // !CATPolySurfaceList
