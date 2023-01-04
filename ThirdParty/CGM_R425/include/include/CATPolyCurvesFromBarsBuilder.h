// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurvesFromBarsBuilder.h
// Header definition of CATPolyCurvesFromBarsBuilder
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// // 2013-04-10    : ANR : Ajout de iLevelTreatmentForClosedPolyCurve
// May 2008 Creation: ndo
//===================================================================
#ifndef CATPolyCurvesFromBarsBuilder_H
#define CATPolyCurvesFromBarsBuilder_H

#include "CATErrorDef.h"  // Definition of HRESULT

#include "CATPolyCurveList.h"
#include "PolyBodyTools.h"


class CATIPolyMesh;
class CATPolyBars;
class CATPolySurfaceFacetSupportLayer;
class CATPolyBarsBarSupportLayer;
class CATMapOfPtrToInt;


class ExportedByPolyBodyTools CATPolyCurvesFromBarsBuilder
{

public:

  //
  // Converter of CATPolyBars's to a list of CATIPolyCurve object.
  //

  /*
     Build CATIPolyCurve's from CATPolyBars.
     @param iMesh
       The mesh containing the vertices.
     @param iPolyBars
       The bars.
     @param iBarVizLayer
       A layer with the key to the viz support.
     @param ioCurveList
       A list to which the curves are appended.
     @param ioMapFromPolyCurveToVizKey
       The mapping from a curve to the viz key.
     @param iLevelTreatmentForClosedPolyCurve
       option of adding a vertex on a closed polycurve
       iLevelTreatmentForClosedPolyCurve = 1 -----> treatment as before
       iLevelTreatmentForClosedPolyCurve = 2 -----> Adding the vertex in the middle of the PolyCurve.
   */
  static HRESULT Build (const CATIPolyMesh& iMesh,
                        const CATPolySurfaceFacetSupportLayer& iFacetSupport,
                        const CATPolyBars& iBars,
                        const CATPolyBarsBarSupportLayer& iBarSupport,
                        CATPolyCurveList& ioCurveList,
                        CATMapOfPtrToInt& ioMapFromPolyCurveToKeySupport,
                        int iLevelTreatmentForClosedPolyCurve = 1);

  static HRESULT Build (const CATIPolyMesh& iMesh,
                        const CATPolySurfaceFacetSupportLayer& iFacetSupport,
                        const CATPolyBars& iBars,
                        const CATPolyBarsBarSupportLayer& iBarSupport1, 
                        const CATPolyBarsBarSupportLayer* iBarSupport2, // Optional (clipping, for example)
                        CATPolyCurveList& ioCurveList,
                        CATMapOfPtrToInt& ioMapFromPolyCurveToKeySupport1,
                        CATMapOfPtrToInt* ioMapFromPolyCurveToOptSupport2,  // If (iOptSupport2).
                        int iLevelTreatmentForClosedPolyCurve = 1);

};

#endif
