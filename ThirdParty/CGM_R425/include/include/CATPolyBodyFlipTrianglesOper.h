// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyFlipTrianglesOper.h
//
//===================================================================
// October 2014  Creation: JXO
//===================================================================
#ifndef CATPolyBodyFlipTrianglesOper_H
#define CATPolyBodyFlipTrianglesOper_H

#include "PolyBodyTools.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATPolyBody;
class CATIPolySurface;

/**
 * Operator that flip all the triangles.
 * (v0, v1, v2) becomes (v0, v2, v1)
 */
class ExportedByPolyBodyTools CATPolyBodyFlipTrianglesOper
{

public:

  /**
   * Constructor of CATPolyBodyFlipTrianglesOper
   */
  CATPolyBodyFlipTrianglesOper();

  ~CATPolyBodyFlipTrianglesOper();

public:

  /**
   * Transforms the CATPolyBody by flipping all the triangles
   * @param ioPolyBody Poly body that must be editable.
   * @param iInvertVerticesNormals If set to TRUE, vertices normals will also be inverted
   */
  HRESULT Run(CATPolyBody& ioPolyBody, CATBoolean iInvertVerticesNormals = FALSE) const;

  /**
   * Transforms the CATIPolySurface by flipping all the triangles
   * @param ioSurface Poly surface that must be editable.
   * @param iInvertVerticesNormals If set to TRUE, vertices normals will also be inverted
   */
  HRESULT Run(CATIPolySurface& ioSurface, CATBoolean iInvertVerticesNormals) const;

};


#endif // !CATPolyBodyCopier_H
