// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathBasicTools.h
//
//===================================================================
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathBasicTools_H
#define CATPolyMathBasicTools_H

#include "PolyMathUtils.h"
#include "CATErrorDef.h"

class CATMathPoint;
class CATMathVector;
class CATMathTransformation;


class ExportedByPolyMathUtils CATPolyMathBasicTools
{

public:

  /**
   * Returns the sign of the determinant of the matrix from the CATMathTransformation.
   */
  static int GetSignOfDeterminant (const CATMathTransformation& iMT);

  /**
   * @deprecated
   * See CATPolyTriangleServices.h.
   * @see CATPolyComputeTriangleNormal
   */
  static HRESULT ComputeTriangleNormal (const CATMathPoint iPoints[], CATMathVector& oNormal);

public:

  static void ApplyToleranceToCoordinates (CATMathVector& ioVector, const double iTolerance = 0);

  static void  VectorNormalize(float* iopVector);
  static void  VectorApplyCoordTol(float* iopVector, float iCoordTol);
  static int   TestSameFloatsFromRatio(float ifloat1, float ifloat2, float iRatioTol);
  static void  ComputeTriangleNormal(float* ipP1, float* ipP2, float* ipP3, float* ipN1, float iopTriangleNormal[]);
  static float GetTriangleMaxSideLength(float* ipP1, float* ipP2, float* ipP3, int* iopMaxSide);

};

#endif // !CATPolyMathBasicTools
