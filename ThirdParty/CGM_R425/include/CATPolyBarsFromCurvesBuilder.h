// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsFromCurvesBuilder.h
// Header definition of CATPolyBarsFromCurvesBuilder
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2008 Creation: ndo
//===================================================================
#ifndef CATPolyBarsFromCurvesBuilder_H
#define CATPolyBarsFromCurvesBuilder_H

#include "PolyBodyTools.h"

#include "CATErrorDef.h"  // Definition of HRESULT

#include "CATPolyCurveList.h"

class CATIPolyMesh;
class CATPolyBars;
class CATPolyBarsBarSupportLayer;
class CATMapOfPtrToInt;
class CAT3DRep;


class ExportedByPolyBodyTools CATPolyBarsFromCurvesBuilder
{

public:

  //
  // Converter of a list of CATIPolyCurve's into a CATPolyBars object.
  //

  /*
     Build PolyBars from a list of CATPolyCurve's.
     @param iCurveList
       The list of CATPolyCurve's.
     @param iVizContainer
       The container of GP's.
     @param iMapFromPolyCurveToVizKey
       The mapping of a CATIPolyCurve to its key of its GP support in the viz container.
     @param ioPolyBars
       The CATPolyBars object that is filled in with the curve data.
     @param ioBarsVizLayer
       An optional layer for the keys of the viz support.
   */
  static HRESULT Build (const CATPolyCurveList& iCurveList,
                        const CATMapOfPtrToInt& iMapFromPolyCurveToVizKey,
                        CATIPolyMesh& ioMesh,
                        CATPolyBars& ioPolyBars, 
                        CATPolyBarsBarSupportLayer* ioBarsVizLayer);

};

#endif
