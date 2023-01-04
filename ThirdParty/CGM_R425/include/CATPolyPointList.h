// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointList.h
//
//===================================================================
// February 2010  Creation: NDO
//===================================================================
#ifndef CATPolyPointList_H
#define CATPolyPointList_H

class CATIPolyPoint;

#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"

#include "PolyhedralModel.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyhedralModel


CATLISTP_DECLARE (CATIPolyPoint);

typedef CATLISTP(CATIPolyPoint) CATPolyPointList;


#endif // !CATPolyPointList
