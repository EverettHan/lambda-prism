#ifndef CATVectorUtilities_h
#define CATVectorUtilities_h

/**
* Vector utilities by LD2.
*/

#include "ExportedByCATTopologicalObjects.h"

class CATListValCATMathVector;
class CATMathVector;
class CATCGMOutput;

#ifndef NULL
#define NULL 0
#endif

#define GetCooordinates(COORD)  (COORD).GetX(), (COORD).GetY(), (COORD).GetZ()

class ExportedByCATTopologicalObjects CATVectorUtilities
{
public:

  /** @nodoc @nocgmitf */
  static void AccurateDump(
    CATCGMOutput & ioOutput,
    CATMathVector & iVector);

  /** @nodoc @nocgmitf
  * Given a list of vectors, create a base that:
  * - doesn't depend on the order of input vectors
  * - is as stable as possible towards rotations
  */
  static void ComputeStableBase(
    double iTolerance,
    CATListValCATMathVector & iListOfVectors,
    CATMathVector & oOrigin,
    CATMathVector & oVector1,
    CATMathVector & oVector2,
    CATMathVector & oVector3,
    CATCGMOutput * ioOutput = NULL);

  /** @nodoc @nocgmitf */
  static void RotoTranslateVector(
    CATMathVector & iInput,
    CATMathVector & iNewOrigin,
    CATMathVector & iNewBaseX,
    CATMathVector & iNewBaseY,
    CATMathVector & iNewBaseZ,
    CATMathVector & oResult);

  /** @nodoc @nocgmitf */
  static void RotoTranslateAllVectorsInList(
    CATListValCATMathVector & ioListOfVectors,
    CATMathVector & iNewOrigin,
    CATMathVector & iNewBaseX,
    CATMathVector & iNewBaseY,
    CATMathVector & iNewBaseZ);

  /** @nodoc @nocgmitf */
  static void NormalizeAllVectorsInList(
    CATListValCATMathVector & ioListOfVectors);

  /** @nodoc @nocgmitf */
  static double GetCoord(
    short iWhichOne, //0->X, 1->Y, 2->Z
    CATMathVector & iVector);

  /** @nodoc @nocgmitf */
  static int VectorComparison_ScaleIndependent(
    CATMathVector & iVector1,
    CATMathVector & iVector2);

  /** @nodoc @nocgmitf */
  static void CreateOrthonormalBase(
    double iEpsilon,
    CATMathVector & iVector1,
    CATMathVector & iVector2,
    CATMathVector & oBaseX,
    CATMathVector & oBaseY,
    CATMathVector & oBaseZ);

  /** @nodoc @nocgmitf */
  static void DumpSupport(
    CATCGMOutput & ioOutput,
    CATMathVector & iOrigin,
    CATMathVector & iVector1,
    CATMathVector & iVector2,
    CATMathVector & iVector3);

  /** @nodoc @nocgmitf */
  static void DumpVectors(
    CATListValCATMathVector & iList,
    CATCGMOutput & ioOutput);
};

#endif
