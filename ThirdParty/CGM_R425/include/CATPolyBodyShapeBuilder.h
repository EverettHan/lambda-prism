// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyShapeBuilder.h
//
//===================================================================
// April 2015  Creation: JXO
//===================================================================
#pragma once

#include "PolyBodyTools.h"

// Poly
class CATPolyBody;
class CATIPolyMesh;

// Math
#include "CATBoolean.h"
class CATMathPoint;
class CATMathVector;


namespace Poly
{
  /**
   * Make a solid CATPolyBody representing a hexahedron.
   * The CATPolyBody returned should be released by the caller.
   * 
   * @param iPoints
   *   The eight points defining the six faces of the hexahedron:
   *     * Face 1: 0, 1, 2, 3
   *     * Face 2: 1, 5, 3, 7
   *     * Face 3: 5, 4, 7, 6
   *     * Face 4: 4, 0, 6, 2
   *     * Face 5: 2, 3, 6, 7
   *     * Face 6: 4, 5, 0, 1
   * 
   *    If the geometry of the face is planar, the hexadron becomes a parallelepiped
   *    as follows:
   * 
   *     4------5
   *    /|     /|
   *   0 ---- 1 |
   *   | |    | |
   *   | 6  - | 7
   *   |/     |/
   *   2------3
   */
  ExportedByPolyBodyTools CATPolyBody* NewHexahedron (const CATMathPoint iPoints[8]);

}


class ExportedByPolyBodyTools CATPolyBodyShapeBuilder
{
public:
  /**
   *
   *     4------5
   *    /|     /|
   *   0 ---- 1 |
   *   | |    | |
   *   | 6  - | 7
   *   |/     |/
   *   2------3
   *
   * To be released by caller
   */
  static CATPolyBody * BuildCuboid(const CATMathPoint iPoints[8], CATBoolean isSolid = TRUE); 
  /**
   * @param iAngle
   *        Angle (in degrees) between two vertices on the sphere. Rounded to have clean division of the 360 degrees.
   *        Default is 10 degrees.
   * To be released by caller
   */
  static CATPolyBody * BuildEllipsoid(const CATMathPoint & iCenter, const CATMathVector iAxis[3], CATBoolean isSolid, double iAngle, CATBoolean iCylindricProjection); 
  /**
   *   
   *        ^
   *     3--|---2
   *    /   |  /
   *   0------1
   *
   * To be released by caller
   */
  static CATPolyBody * BuildQuad(const CATMathPoint iPoints[4]);

  /**
   *
   *     4------5
   *    /|     /|
   *   0 ---- 1 |
   *   | |    | |
   *   | 6  - | 7
   *   |/     |/
   *   2------3
   *
   * Construct an editable (CATPolyMeshImpl) cuboid.
   * To be released by caller
   */
  static CATIPolyMesh * BuildCuboidMesh(const CATMathPoint iPoints[8]);

  /**
   * NOT IMPLEMENTED YET
   * @param iAngle
   *        Angle (in degrees) between two vertices on the sphere. Rounded to have clean division of the 360 degrees.
   *        Default is 10 degrees.
   *
   * To be released by caller
   */
  static CATPolyBody * BuildCylinder(const CATMathPoint iPoints[2], double iRadius1, double iRadius2, CATBoolean isSolid, double iAngle);


protected:
  CATPolyBodyShapeBuilder(){}
  ~CATPolyBodyShapeBuilder(){}
};

