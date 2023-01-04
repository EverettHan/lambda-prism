#ifndef CATEdgeExtremityForFastRun_h
#define CATEdgeExtremityForFastRun_h
/*-*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATVertex.h"
#include "CATTopDefine.h"
#include "CATEdgeCurve.h"
class CATEdge;


class ExportedByCATTopologicalObjects CATEdgeExtremityForFastRun
{

public:

   CATEdgeExtremityForFastRun(CATEdge * iEdge, CATVertex * iVertex);
   ~CATEdgeExtremityForFastRun();


  CATBoolean operator== (CATEdgeExtremityForFastRun iExtr);
  CATEdgeExtremityForFastRun * GetCommonExtremity(CATEdge * iEdge1, CATEdge * iEdge2);

  CATVertex     * GetVertex();
  CATOrientation  GetOrientation();
  CATEdgeCurve  * GetEdgeCurve();


private:

  CATVertex     * _Vertex;
  CATOrientation  _Orientation;
  CATEdgeCurve  * _EdgeCurve;

};
#endif
