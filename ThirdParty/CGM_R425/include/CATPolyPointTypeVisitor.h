// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointTypeVisitor.h
//
//===================================================================
// April 2016  Creation: NDO
//===================================================================
#ifndef CATPolyPointTypeVisitor_H
#define CATPolyPointTypeVisitor_H

#include "PolyMeshTools.h"
#include "CATErrorDef.h"

class CATIPolyPoint;


/**
 * Returns the PolyhedralObjects type of the CATIPolyPoint.  
 */
class ExportedByPolyMeshTools CATPolyPointTypeVisitor
{

public:

  CATPolyPointTypeVisitor () {}
  ~CATPolyPointTypeVisitor () {}

  enum PointType
  {
    /** Unknown point */                      eUnknownPoint                 = -1,
    /** CATPolyPoint */                       ePolyPoint                    = 0,
    /** CATPolyPointConst */                  ePolyPointConst               = 1,
    /** CATPolyCurvePoint */                  ePolyCurvePoint               = 2,
    /** CATPolyCurvePointConst */             ePolyCurvePointConst          = 3,
    /** CATPolyMeshPoint */                   ePolyMeshPoint                = 4,
    /** CATPolyMeshPointConst */              ePolyMeshPointConst           = 5,
    /** CATPolyCurveVertex */                 ePolyCurveVertex              = 6,
    /** CATPolyCurveVertexConst */            ePolyCurveVertexConst         = 7,
    /** CATPolySurfaceVertex */               ePolySurfaceVertex            = 8,
    /** CATPolySurfaceVertexConst */          ePolySurfaceVertexConst       = 9
  };

public:

  /**
   * Returns the PolyhedralObjects type of the CATIPolyPoint.
   * @param oType
   *   The type of the CATIPolyPoint.
   *   <ul>
   *     <li> ePolyPoint
   *     <li> ePolyPointConst
   *     <li> ePolyCurvePoint
   *     <li> ePolyCurvePointConst
   *     <li> ePolyMeshPoint
   *     <li> ePolyMeshPointConst
   *     <li> ePolyCurveVertex
   *     <li> ePolyCurveVertexConst
   *     <li> ePolySurfaceVertex         
   *     <li> ePolySurfaceVertexConst         
   *   </ul>
   */
  static PointType Type (const CATIPolyPoint& iPoint);

public: 

  /**
   * See static Type () method.
   */
  HRESULT GetType (const CATIPolyPoint& iPoint, PointType& oType);

};

#endif
