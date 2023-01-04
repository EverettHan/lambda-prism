#ifndef CATMATHFP_H
#define CATMATHFP_H

// COPYRIGHT DASSAULT SYSTEMES  2005

/**
 * Definition of useful functions. 
 *<ul>
 *<li>CATDivision(A,B)   : returns the result of division by two double
 *<li>CATCeil(A)         : returns the result of a Ceil as an int value
 *<li>CATFloor(A)        : returns the result of a Floor as an int value
 *<li>CATRound(A)        : returns the closest int of a double
 *</ul>
*/
#include "CATMathematics.h"

#include "CATMathLimits.h"
#include "CATMath.h"
#include <limits.h>
#include <math.h>
#include "CATAssert.h"
#include "CATDataType.h"
#include "CATTolerance.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include <string.h> /* memset */

//-----------------------------------------------------------------------------
// Basic numerical constants : a mattre a terme dans CATMathLimits.h
//-----------------------------------------------------------------------------
// Min double.
#ifdef DBL_MIN
#define CATdoubleMin DBL_MIN
#else
#define CATdoubleMin 2.2250738585072014E-308
#endif

INLINE double CATSafeDivision(double iValueA, double iValueB, int *oDiag=0)
{
  if (oDiag)
    *oDiag = 0;

  // Cas d'overflow (i.e resultat de la division > CATdoubleMax) : on n'effectue pas la division 
  // et l'on rend +/- CATdoubleMax comme resultat de la division.
  // a) si diagnostic demande (i.e oDiag<>0), on rend *oDiag=1 et +/- CATDoubleMax comme resultat de la division
  // b) si diagnostic non demande, on fait un CATAssert
  //-------------------------------------------------------------------------------------------------------------
  if (CATFabs(iValueB) < 1. && (CATFabs(iValueA) > CATFabs(iValueB) * CATdoubleMax))
  {
    if (oDiag)
    {
      *oDiag = 1;
    }
    else
    {
      CATAssert(0);
    }
    int signA = *((int *)&iValueA)>>(sizeof(double)-1);
    int signB = *((int *)&iValueB)>>(sizeof(double)-1);
    if (signA*signB < 0)
      return -CATdoubleMax;
    else
      return  CATdoubleMax;

  }

  // Cas d'underflow (i.e resultat de la division < CATDoubleMin) : on n'effectue pas la division
  // et l'on rend 0.0 comme resultat de la division.
  // Cas particulier ou iValueA=0.0 ET iValueB=0.0, on rend egalement 0.0 comme resultat de la division (convention),
  // mais on rend en outre 
  // a) le diagnostic *oDiag=2 si diagnostic demande l'utilisateur
  // b) CATAssert sinon
  //-----------------------------------------------------------------------------------------------------------------
  else
    if ((CATFabs(iValueB) > 1. && (CATFabs(iValueA) < CATFabs(iValueB) * CATdoubleMin)) || CATFabs(iValueA) == 0.0)
    {
      if (CATFabs(iValueB) == 0.0)
      {
        if (oDiag)
        {
          *oDiag=2;
        }
        else
        {
          CATAssert(0);
        }
      }
      return 0.0;
    }
  
  // Dans tous les autres cas, on effectue la division
  //--------------------------------------------------
  return iValueA / iValueB;
}

/**
 * Returns ceil of double with the type int.
 */
INLINE int CATCeil (double iValue);
/**
 * Returns floor of double with the type int.
 */
INLINE int CATFloor (double iValue);
/**
 * Returns the int closest to the double in input.
 */
INLINE int CATRound (double iValue);
/**
 * Returns ceil of float with the type int.
 */
INLINE int CATCeil (float iValue);
/**
 * Returns floor of float with the type int.
 */
INLINE int CATFloor (float iValue);
/**
 * Returns the int closest to the float in input.
 */
INLINE int CATRound (float iValue);


//-----------------------------------------------------------------------------
// IEEE 754 Standard compliance (CATMathIsAGoodNumber :  isnan _isnan)
// floating-point control exeptions 
//-----------------------------------------------------------------------------
/**
 * Control validity of a floating points
 *    Do not abuse otherwise performance may decrease 
 * specific ODT behavior, under floating point replay (CATFPExceptions=TRUE) Fatal Error occurs   
 *    so if invalid floating point is expected, you may have to disable in shell CATFPExceptions
 * Returns the Validity of input double.
 *     1 = valid double according to IEEE 754 (!nan and ! infinite)
 *     0 = invalid double (nan and infinite)
 */
ExportedByCATMathematics  int CATMathIsAGoodNumber(double iValue, CATBoolean isSignalError = FALSE );

/**
 * Control validity of a floating points
 *    Check if a floating points is not NaN either infinite/-infinite
 * Returns the Validity of input double.
 *     1 = valid double according to IEEE 754 
 *     0 = invalid double (nan , infinite, -infinite)
 */
ExportedByCATMathematics  int CATMathIsAGoodFP(double iValue);

/**
 * Control validity of a floating points
 *    Do not abuse otherwise performance may decrease 
 * specific ODT behavior, under floating point replay (CATFPExceptions=TRUE) Fatal Error occurs   
 *    so if invalid floating point is expected, you may have to disable in shell CATFPExceptions
 * Returns the Validity of input double.
 *     1 = valid double according to IEEE 754 (!nan and ! infinite)
 *     0 = invalid double (nan and infinite)
 */
ExportedByCATMathematics  int CATMathIsAGoodNumber(float iValue, CATBoolean isSignalError = FALSE );
ExportedByCATMathematics  CATLONG64 CATMathIsAGoodNumberOfCheck();
ExportedByCATMathematics  CATLONG64 CATMathNumberOfBadCheck();

/**
 * Returns the floating point control.
 *     1 = is under Floating point control (set CATFPExceptions=TRUE).
 *     0 = otherwise.
 */
ExportedByCATMathematics  int CATMathIsUnderFPExceptions();

//
//------------------------------------------------------------------------------------------------
// Comparison between two doubles at a given tolerance iEpsilon
// The two doubles iValueA and iValueB are considered as equal if :
//     |iValueA - iValueB| < Eps
//     with Eps = iEpsilon + EpsgForRelativeTest * max(|iValueA|, |iValueB|) 
//     and EpsgForRelativeTest = 1.e-12 (documented in CATTolerance.h)
// 
// The method returns an int type which takes the following values :
//     0 : means "iValueA = iValueB"  ( |iValueA - iValueB| < Eps  )
//    -1 : means "iValueA < iValueB"  ( iValueA < iValueB - Eps)
//     1 : means "iValueA > iValueB"  ( iValueA > iValueB + Eps  )
//
// Comment :
// ---------
// * The comparison becomes completely relative for big numbers :
// if |iValueA|<<1. and |iValueB|<<1., the tests becomes |iValueA - iValueB| / max(|iValueA|, |iValueB|) < EpsgForRelativeTest.
// * The comparison becomes completely absolute for very small numbers 
// if |iValueA|<<1. and |iValueB|<<1., the tests becomes |iValueA - iValueB| < iEpsilon.
// 
// Recommendations :
// ---------------- 
// 
// *The value for iEpsilon must be compliant with EXTREME SCALE.
//  1/It means that, if you compare two doubles homogeneous to LENGTH values, you must use a scaled tolerance 
//  iEpsilon = CATGetTolerance(iFactory).EpsgForLengthTest()
//  Ex : for scale = 1000, iEpsilon = 1000 * 1.e-12 = 1.e-9  (rather than 1.e-12)
//
//  2/For test between values that are independant from the scale (ex : angle, adimensional values), 
//  you can let the internal default tolerance with is the same for all the scale and is equal to 1.e-12
//  by using the CATCompare(double iValueA, double iValueB ) signature
//  In this cas, the value for internal used for iEpsilon is 
//  iEpsilon = CATGetDefaultTolerance().EpsgForRelativeTest() which is equal to 1.e-12  
//
// *Generally, the doubles to compare are results of combinations and accumulations 
//  of several arithmetic operations. In order to absorb the cumulative rounding errors, we 
//  prefer to use EpsgForRelativeTest tolerance (1.e-12) (default value) 
//  rather than EpsilonForRelativeTest (1.e-15)
//
// *There is no generic rules on how to select the tolerance.
//  The choice of tolerance value depends on domain or problem specific knowledge.
//  For instance, if you know that your doubles come from Sqrt, you should use a bigger
//  tolerance such as LargeEpsgForLengthTest = 1.e-6 rather than EpsgForLengthTest = 1.e-12
//
//---------------------------------------------------------------------------------------
INLINE int CATCompare(double iValueA, double iValueB , double iEpsilonAbs, double iEpsilonRel);
INLINE int CATCompare(double iValueA, double iValueB , double iEpsilon);
INLINE int CATCompare(double iValueA, double iValueB );


//-----------------------------------------------------------------------------
// Not geometrical, Only for enabling stability control of computer data persistency
// (Cf NegativeZero, IEEE 754, ... )
//     0 : means "iValueA" computer data is strictly equal to "iValueB"  
//     1 : otherwise
//-----------------------------------------------------------------------------
INLINE int CATCompareComputerData(double iValueA, double iValueB);



//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE int CATCeil(double iValue) {
  return (int) ceil(iValue);}    //@FDTOI

INLINE int CATFloor(double iValue) {
  return (int) floor(iValue);}   //@FDTOI

INLINE int CATRound(double iValue) {
  return (int) floor(iValue+0.5);}   //@FDTOI

INLINE int CATCeil(float iValue) {
  return (int) ceil(iValue);}    //@FSTOI

INLINE int CATFloor(float iValue) {
  return (int) floor(iValue);}   //@FSTOI

INLINE int CATRound(float iValue) {
  return (int) floor(iValue+0.5);}   //@FSTOI

INLINE int CATCompare(double iValueA, double iValueB , double iEpsilonAbs, double iEpsilonRel)
{
  double Eps = iEpsilonAbs + iEpsilonRel * CATMax( CATFabs(iValueA), CATFabs(iValueB) ) ;
  double Diff = iValueA-iValueB;
  int Result = 0;
  
  if (Diff < -Eps) Result = -1;
  else if (Diff > Eps) Result = 1;

  return Result;
}

INLINE int CATCompare(double iValueA, double iValueB, double iEpsilon)
{
  double Eps = iEpsilon + CATGetDefaultTolerance().EpsgForRelativeTest() * CATMax( CATFabs(iValueA), CATFabs(iValueB) ) ;
  double Diff = iValueA-iValueB;
  int Result = 0;
  
  if (Diff < -Eps) Result = -1;
  else if (Diff > Eps) Result = 1;

  return Result;
}
// EB++  split the signature to increase performances for checks onto adimensional values and make them XScale Compliant 
INLINE int CATCompare(double iValueA, double iValueB) 
{
  double Eps = CATGetDefaultTolerance().EpsgForRelativeTest()*( 1. + CATMax( CATFabs(iValueA), CATFabs(iValueB) ));
  double Diff = iValueA-iValueB;
  int Result = 0;
  if (Diff < -Eps) Result = -1;
  else if (Diff > Eps) Result = 1;
  return Result;
}

//-----------------------------------------------------------------------------
// Not geometrical, Only for enabling stability control of computer data persistency
// (Cf NegativeZero, IEEE 754, ... )
//     0 : means "iValueA" computer data is strictly equal to "iValueB"  
//     1 : otherwise
//-----------------------------------------------------------------------------
INLINE int CATCompareComputerData(double iValueA, double iValueB)
{ return ( *((CATULONG64 *)(&iValueA)) == *((CATULONG64 *)(&iValueB)) ) ? 0 : 1; }

//-----------------------------------------------------------------------------
// Init all double array elements with 0.
//-----------------------------------------------------------------------------
#define CATInitDoubleArray(DoubleArray) memset(DoubleArray, 0, sizeof(DoubleArray))

#endif
