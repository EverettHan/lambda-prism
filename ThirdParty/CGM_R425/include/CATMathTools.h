#ifndef CATMathTools_H
#define CATMathTools_H

//
//   Mathematical Basic or Complementary  Services
//
//
//   09/11/2008     Creation                     KJD
//   05/06/2018     KJD addition of the API RandPerm


#include "YN000MAT.h"
#include "CATMathAxis.h"
#include "CATMathTransformation.h"
#include "CATMathDirectionf.h"

class ExportedByYN000MAT CATMathTools
{
public:

  /**
  * Random generator (generates ramdom numbers between 0 and 1).
  * @param ioSeed     Seed to generate random numbers.
  * @param iN         Number of random figures wanted.
  * @param oX         Tab which contains random figures.
  * Notice that if ioSeed=0, forall i 0 < oX[i] <= 1 otherwise 0 < oX[i] <1
  */
  static void Rand (CATLONG32 &ioSeed, CATULONG32 iN, double *oX);
  static void Rand (CATLONG32 &ioSeed,                double *oX);

  /**
  * Random generator (generates ramdom numbers between 0 and INT32_MAX(2^31=2147483647)).
  * @param ioSeed     Seed to generate random numbers.
  * @param oX         Contains random figures.
  * Notice that if ioSeed=0, X = INT32_MAX 
  */
  static void Rand (CATLONG32 &ioSeed, int *oX);

  /**
  * Random generator (generates  iSize ramdom integers between 0 and iSize).
  * @param iSize     Size of the array
  * @param oX        Contains random figures.
  */
  static void RandPerm(CATLONG32 & ioSeed, CATLONG32 iSize, int * oX);


  /**
   * Return the exponent of a double in base 10.
   * @param  iDouble     The number to get the exponent in base 10.
   * @param  oPowerOfTen Fill, if provided, the double with 10^exponent.
   * @return             The exponent of iDouble in base 10.
   */
  static int GetExponentOfTen  (double   iDouble           ,
                                double * oPowerOfTen = NULL);

  /**
   * Round a double at the digit associated with 10^iExponentOfTen
   * @param  iDouble        The number to round.
   * @param  iExponentOfTen The power of ten.
   * @return                The rounded number.
   * @example
   * CATRoundBaseOfTen(1928.3746,  4) =    0
   * CATRoundBaseOfTen(1928.3746,  3) = 2000
   * CATRoundBaseOfTen(1928.3746,  2) = 1900
   * CATRoundBaseOfTen(1928.3746,  1) = 1930
   * CATRoundBaseOfTen(1928.3746,  0) = 1928
   * CATRoundBaseOfTen(1928.3746, -1) = 1928.4
   * CATRoundBaseOfTen(1928.3746, -2) = 1928.37
   * CATRoundBaseOfTen(1928.3746, -3) = 1928.375
   * CATRoundBaseOfTen(1928.3746, -4) = 1928.3746
   * CATRoundBaseOfTen(1928.3746, -5) = 1928.3746
   */
  static double RoundBaseOfTen(double   iDouble           ,
                               int      iExponentOfTen    );


  /**
  *  Utilities for the axes.
  */

  //Reorthonormalize very precisely an axis system 
  static HRESULT AxisReorthonormalization(const CATMathAxis & iAxis,CATMathAxis & oAxis);

  //Initializes a CATMathAxis already orthogonalized according to the construction rules of the CATMathAxis class
  static HRESULT SetOrthogonalizedAxis(const CATMathPoint & P, const CATMathVector & I, const CATMathVector & J, const CATMathVector & K, CATMathAxis & oAxis);

  //Initializes a CATMathAxis already orthonormalized according to the construction rules of the CATMathAxis class
  static void SetOrthonormalizedAxis(const CATMathPoint & P, const CATMathVector & I, const CATMathVector & J, const CATMathVector & K, CATMathAxis & oAxis);

  //Constructs a CATMathDirectionf without an internal normalization.
  static void SetNormalizedDirectionf(const float iFirstCoord,const float iSecondCoord, const float iThirdCoord,CATMathDirectionf & oDir);

 
  /**
  *  Utilities for the transformations.
  *  DEPRECATED METHODS : Use the APIs of the CATMathTransfoTools class
  */

   /* Constructs a transformation of axis systems.
  This transformation transforms, in the global axis system CATMathOIJK, the coordinates of a point <tt>M</tt> into the coordinates of the point TM such that:
  ---> M and TM have the same coordinate values in the axis <tt>iFromAxis</tt> and <tt>iToAxis</tt>. 
  WARNING : It is supposed that the used CATMathAxis are previously orthonormalized. No reorthonormalization is done !!!
  */  
  static void ComputeTransfoWithoutOrthoNormalization(const CATMathAxis & iFromAxis, const CATMathAxis & iToAxis, CATMathTransformation & oTransfo);

private:
   static void RandTools (CATLONG32 &ioSeed, double & orm);
  CATMathTools();
  CATMathTools(const CATMathTools &);//Necessary to prevent unwanted automatic creation by compiler
  void operator = (const CATMathTools &);
};

#endif

