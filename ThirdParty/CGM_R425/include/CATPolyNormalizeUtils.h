// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyNormalizeUtils.h
//
//===================================================================
// April 2006 Creation: NDO
//===================================================================
#ifndef CATPolyNormalizeUtils_H
#define CATPolyNormalizeUtils_H

#include "PolyMathArithmetic.h"
#include "CATErrorDef.h"

class CATPolyExactArithmetic;
class CATMathPoint2D;
class CATMathPoint;
class CATMathBox2D;
class CATMathBox;


/*
Utilities to construct an instance of exact arithmetic and normalize points and bounding box prior
to doing exact arithmetic.
*/
class ExportedByPolyMathArithmetic CATPolyNormalizeUtils
{

public :

  CATPolyNormalizeUtils () {}
  ~CATPolyNormalizeUtils () {}

public:

  /**
   * For use of exact arithmetic in the gridded mode (integer arithmetic), aligns the input bounding box
   * with the grid.
   */
  static HRESULT Normalize (const CATPolyExactArithmetic& iExactArithmetic, CATMathBox2D& bbox);

  /**
   * For use of exact arithmetic in the gridded mode (integer arithmetic), aligns the input bounding box
   * with the grid.
   */
  static HRESULT Normalize (const CATPolyExactArithmetic& iExactArithmetic, CATMathBox& bbox);

public:

  /**
   * Creates an instance of exact arithmetic for use with gridded coordinates (integer arithmetic.)
   * The bounding box is aligned with the grid after creation of the instance of exact arithmetic.
   * @deprecated
   * @see CATPolyNormalizeUtils::Normalize
   */
  static HRESULT NormalizeBoundingBox (CATMathBox2D& ioBoundingBox, CATPolyExactArithmetic*& oExactArithmetic);

  /**
   * Creates an instance of exact arithmetic for use with gridded coordinates (integer arithmetic.)
   * The bounding box is aligned with the grid after creation of the instance of exact arithmetic.
   * @deprecated
   * @see CATPolyNormalizeUtils::Normalize
   */
  static HRESULT NormalizeBoundingBox (CATMathBox& ioBoundingBox, CATPolyExactArithmetic*& oExactArithmetic);

public:

  // Normalize the points and return their bounding box after normalization and a definition of a new instance
  // of exact arithmetic.
  static HRESULT NormalizePoints (CATMathPoint2D* ioPoints, const int iNbPoints, 
                                  CATMathBox2D& oBoundingBox, 
                                  CATPolyExactArithmetic*& ioExactArithmetic);

  // Normalize the points and return their bounding box after normalization and a definition of a new instance
  // of exact arithmetic.
  static HRESULT NormalizePoints (CATMathPoint* ioPoints, const int iNbPoints, 
                                  CATMathBox& oBoundingBox, 
                                  CATPolyExactArithmetic*& ioExactArithmetic);

};

#endif

