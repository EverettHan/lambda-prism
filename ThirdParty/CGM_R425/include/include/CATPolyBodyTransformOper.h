// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyTransformOper.h
//
//===================================================================
// September 2014  Creation: JXO
//===================================================================
#ifndef CATPolyBodyTransformOper_H
#define CATPolyBodyTransformOper_H

#include "PolyBodyTools.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATPolyBody;
class CATMathTransformation;
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;
class CATIPolySurfaceVertexCellConstLayer;

/**
 * Operator that applies a CATMathTransformation to a CATPolyBody, in place.
 * Input poly body must be editable. If not, operation fails.
 */
class ExportedByPolyBodyTools CATPolyBodyTransformOper
{

public:

  /**
   * Constructor of CATPolyBodyTransformOper
   */
  CATPolyBodyTransformOper();

  ~CATPolyBodyTransformOper();

public:

  /**
   * Transforms the CATPolyBody.
   * @param ioPolyBody
   *   The input CATPolyBody. Needs to be editable because it will be transformed in place. If you want a copy, use CATPolyBodyCopier.
   * @param iPosition
   *   The input CATMathTransformation to apply.
   */
  HRESULT Transform(CATPolyBody& ioPolyBody,
                    const CATMathTransformation & iPosition) const;

  /**
   * Transforms the CATIPolySurface.
   * @param ioSurface
   *   The input CATIPolySurface. Needs to be editable because it will be transformed in place. If you want a copy, use CATPolyMeshCopier.
   *   Note about the edges: Boundary edges, as they may be part of other surfaces, should not be transformed.
   *   For a full transformation, first transform the vertices, then transform the edges, then the surface.
   * @param iPosition
   *   The input CATMathTransformation to apply.
   * @param iCellLayer
   *   Layer used to get the edges and vertices. If not set, everything is transformed, even on free bars.
   */
  HRESULT Transform(CATIPolySurface& ioSurface,
                    const CATMathTransformation & iPosition,
                    CATIPolySurfaceVertexCellConstLayer * iCellLayer = 0) const;

  /**
   * Transforms the CATIPolyCurve.
   * @param ioCurve
   *   The input CATIPolyCurve. Needs to be editable because it will be transformed in place.
   *   Note about the start and end vertices: Vertices, as they may be part of other curves, won't be transformed.
   *   For a full transformation, first transform the vertices, then transform the curve.
   * @param iPosition
   *   The input CATMathTransformation to apply.
   * @param iDoNotExcludeExtremities
   *   If set to TRUE, transforms also the start and end points.
   */
  HRESULT Transform(CATIPolyCurve& ioCurve,
                    const CATMathTransformation & iPosition,
                    CATBoolean iDoNotExcludeExtremities = FALSE) const;

  /**
   * Transforms the CATIPolyPoint.
   * @param ioPoint
   *   The input CATIPolyPoint. Needs to be editable because it will be transformed in place.
   * @param iPosition
   *   The input CATMathTransformation to apply.
   */
  HRESULT Transform(CATIPolyPoint& ioPoint,
                    const CATMathTransformation & iPosition) const;

};


#endif // !CATPolyBodyCopier_H
