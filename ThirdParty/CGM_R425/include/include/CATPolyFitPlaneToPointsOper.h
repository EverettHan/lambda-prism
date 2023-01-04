// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyFitPlaneToPointsOper.h
// Header definition of CATPolyFitPlaneToPointsOper
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// April 2006 Creation: ndo
//===================================================================
#ifndef CATPolyFitPlaneToPointsOper_H
#define CATPolyFitPlaneToPointsOper_H

#include "PolyMathUtils.h"
#include "CATBoolean.h"
#include "CATMathPlane.h"
#include "CATErrorDef.h" // Definition of HRESULT.


class ExportedByPolyMathUtils CATPolyFitPlaneToPointsOper
{

public:

   CATPolyFitPlaneToPointsOper (); 
   ~CATPolyFitPlaneToPointsOper ();

 	static HRESULT Fit (const CATMathPoint* iPoints, const int iNbPoints, CATMathPlane& oPlane);

};

#endif
