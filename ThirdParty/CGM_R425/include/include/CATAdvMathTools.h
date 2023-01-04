// Usage notes:
//=============================================================================
// 15/01/2020 : SMT1 : Distance method was misnamed and used to compute SquareDistance. Now there are two methods.
//=============================================================================

#ifndef CATAdvMathTools_H
#define CATAdvMathTools_H

#include "CATDataType.h"
#include "CATOptTypes.h"
#include "YN000FUN.h"


class ExportedByYN000FUN CATAdvMathTools
{
public:

  /*
  * Generation of 2 normally distributed samples with the Box-Muller process from 2 uniform distributed samples, mean=0, standard-deviation=1
  * @param iN     Size of the samples 
  * @param ioX1   Input parameters which contains the first uniform sample. Output parameters which contains the  first normally distributed sample
  * @param ioX2   Input parameters which contains the second uniform sample. Output parameters which contains the  second normally distributed sample 
  */
  static void  NormalfromUniformDistribution(CATULONG32 iN, CATOptReal *ioX1, CATOptReal *ioX2 );


  /**
  * Calculates the distance between two points.
  * @param iX1      First point.
  * @param iX2      Second point
  * @param iN       Space dimension
  */
  static CATOptReal  Distance (CATOptReal const *, CATOptReal const *, CATULONG32);

   /**
  * Calculates the squared distance between two points.
  * @param iX1      First point.
  * @param iX2      Second point
  * @param iN       Space dimension
  */
  static CATOptReal  SquareDistance (CATOptReal const *, CATOptReal const *, CATULONG32);

  /*
  * Evaluate the norm of a vector
  * @param iN           Input size of vector
  * @param iArray       Input vector
  */
  static CATOptReal  Norm(CATULONG32 iN, CATOptReal*  iArray);

  /**
  * Function sorting a table. The result table contains the index 
  * @param iN       Number of elements to sort.
  * @param ioA      Array of length iN ; in : data to be sorted out          : Sorted array ( min to max)
  * @param oIndex       Array of length iN. oA[i] index of the initial value ; ioA(before)[oIndex[i]] = ioA(after)[i]
  */
  static void  ShellSort (CATULONG32 iN, CATOptReal *iA, CATULONG32 *oIndex);

  // iA is not modified
  // MinValue (iA[oIndex[0]   )
  // MaxValue (iA[oIndex[iN-1])
  static void  ShellSort2 (CATULONG32 iN, CATOptReal *iA, CATULONG32 *oIndex);

  // Using Merge Algorithm 
  // iA not modified
  static void MergeSort (CATULONG32 iN, CATOptReal *iA, CATULONG32 *oA);

  /**
  * Initializes points positions with the LHS method. http://en.wikipedia.org/wiki/Latin_hypercube_sampling
  * @param iN               Number of points.
  * @param iDimension       Space size.
  * @param iXMin            Vector of space size dimension which contains the lower bounds of the domain.
  * @param iXMax            Vector of space size dimension which contains the upper bounds of the domain.
  * @param iRandomTable     Table of iN random numbers between 0 and 1. 
  * @param iNGiven          Number of points already positionned (with no need of being initialized with the LHS method).
  * @param oPositions       Output coordinates of the iN points. First we find the iDimension coordinates of the first point, then the iDimension coordinates of the second point, ... The memory has to be allocated by the user (size iN*iDimension).
  */
  static void  InitializePositionsWithLHS (CATULONG32, CATULONG32, CATOptReal *, CATOptReal *, CATOptReal *, CATULONG32, CATOptReal *);

private:
  CATAdvMathTools();
  CATAdvMathTools(const CATAdvMathTools &);//Necessary to prevent unwanted automatic creation by compiler
  void operator = (const CATAdvMathTools &);
};

#endif
