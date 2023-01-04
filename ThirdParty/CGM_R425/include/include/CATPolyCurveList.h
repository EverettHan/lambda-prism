//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyCurveList
//
//=============================================================================
// 2006-12-07   BPG: New
//=============================================================================
#ifndef CATPolyCurveList_H
#define CATPolyCurveList_H

class CATIPolyCurve;

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
CATLISTP_DECLARE(CATIPolyCurve);

typedef CATLISTP(CATIPolyCurve) CATPolyCurveList;

#endif // !CATPolyCurveList
