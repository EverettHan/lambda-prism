// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathGeoUtil.h
//
//===================================================================
// Jul 2007 Creation: ndo
//===================================================================
#ifndef CATPolyMathGeoUtil_h
#define CATPolyMathGeoUtil_h

#include "PolyMathUtils.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATIAV5Level.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATTolerance.h"
class CATMathDirection;
class CATMathBox2D;
class CATMathBox;


/**
* Miscellaneous geometric services.
* @see CATPolyGeoServices
*/
class ExportedByPolyMathUtils CATPolyMathGeoUtil
{

public :

  static double ComputeCosineOfAngleBetweenVectors (const CATMathDirection& v1, const CATMathDirection& v2);
  static double ComputeCosineOfAngleBetweenVectors (const CATMathDirection& v1, const CATMathVector& v2);
  static double ComputeCosineOfAngleBetweenVectors (const CATMathVector& v1, const CATMathVector& v2);

public:

  // Compute the squared distance between P and the line defined by SE.
  static double ComputeSquareDistance (const CATMathPoint& S, const CATMathPoint& E, 
                                       const CATMathPoint& P);

  // Compute the squared distance between P and the plane defined by ABC.
  static double ComputeSquareDistance (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C, 
                                       const CATMathPoint& P);

public:

  /**
   * @see CATPolyGetMaximumCoordinate
   */
  static HRESULT GetMaximumCoordinate (const CATMathBox2D& iMBox, double& oMaxCoordinate);

  /**
   * @see CATPolyGetMaximumCoordinate
   */
  static HRESULT GetMaximumCoordinate (const CATMathBox& iMBox, double& oMaxCoordinate);

public:

  /** Determines if two triangle A and B are in contact according to a
   *  tolerance, and if they are, computes the distance between the two
   *  triangles (the minimal distance between two points on the
   *  triangles) and the points on each triangle that realize this
   *  distance. If triangles intersect each others and bComputeIntersectionCurves
   *  is TRUE, the given points define the segment as the intersection
   *  between the two triangles.
   *  Two triangles are in contact if their squared minimal distance is
   *  strictly smaller than the given squared tolerance.
   *@param iA: array of the three A triangle vertices.
   *@param iB: array of the three B triangle vertices.
   *@param iTolerance: the squared tolerance for contact.
   *@param oDistance: the squared distance between the two triangles.
   *@param oA: the point on the triangle A realizing the minimal
   *distance with a point of B, one extremity of the intersection
   *segment in case of a clash.
   *@param oB: the point on the triangle B realizing the minimal
   *distance with a point of A, one extremity of the intersection
   *segment in case of a clash.
   *@param epsilon should be a scale-compliant large epsg for length tests
   *@return TRUE if the triangles are in contact, FALSE otherwise.
   */
  static CATBoolean TriangleToTriangleContact(const CATMathPoint iA[3], const CATMathPoint iB[3], double iTolerance,
         double & oDistance, CATMathPoint & oA, CATMathPoint & oB, CATBoolean bComputeIntersectionCurves, const double epsilon);

class ExportedByPolyMathUtils FastTriangleContactAccelerator
{
public:
  inline FastTriangleContactAccelerator(const CATTolerance & iTol)
  {
    _nA2 = 0.;
    _nB2 = 0.;
    _epsilon = iTol.EpsgForLengthTest();
    _largeepsilon = iTol.LargeEpsgForLengthTest();
    _eps2 = _epsilon * _epsilon;
    _infinity = iTol.Infinite();
  }
  ~FastTriangleContactAccelerator()
  {
  }


  CATBoolean FastTestPlaneContact(const CATMathPoint iA[3],
                                  const CATMathPoint iB[3],
                                  double iTolerance,
                                  double & oDistance, CATMathPoint & oA, CATMathPoint & oB);

public:
  CATMathVector _AB[3][3];
  CATMathVector _da[3];
  CATMathVector _db[3];
  CATMathVector _Ib[3];
  CATMathVector _dbXda[3][3];
  CATMathVector _nA;
  CATMathVector _nB;
  // Temporary data to avoid calling the constructor
  CATMathPoint _closestPoint1;
  CATMathPoint _closestPoint2;
  CATMathPoint _Ori;
  CATMathPoint _Dest;
  CATMathVector _Ia;

  double _RB[3], _RA[3];
  double _nA2;
  double _nB2;
  double _epsilon;
  double _largeepsilon;
  double _eps2;
  double _infinity;
  CATBoolean _ComputeIntersectionCurves;
};

  static CATBoolean FastTriangleToTriangleContact(const CATMathPoint iA[3], const CATMathPoint iB[3], double iTolerance,
                                                  double & oDistance, CATMathPoint & oA, CATMathPoint & oB,
                                                  FastTriangleContactAccelerator & ta);
};



#endif
