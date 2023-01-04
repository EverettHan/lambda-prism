#ifndef CATMATH_H
#define CATMATH_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Definition of useful functions. The name are overloaded for int, CATLONG32, 
 * CATINTPTR, float
 * and double, such that the compilator can choose the appropriate function 
 *( except CATFabs that is changed to CATAbs for int and CATLONG32).
 *<ul>
 *<li>CATMin(A,B)   : returns the min of two numbers
 *<li>CATMin(A,B,C) : returns the min of three numbers
 *<li>CATMax(A,B)   : returns the max of two numbers
 *<li>CATMax(A,B,C) : returns the max of three numbers
 *<li>CATSign       : return -1 0 or 1 according to the sign of the entry
 *<li>CATIsign(I,J) : transfers the sign of J to the CATLONG32 or int |I|
 *<li>CATDsign(A,B) : transfers the sign of B to the double or float |A| 
 *<li>CATMsign(A,B) : multiply the sign of B to the double or float A 
 *<li>CATIdim(I,J)  : returns the positive difference I-J, else zero 
 *<li>CATSquare     : returns the square of an number 
 *<li>CATPower3     : returns the cube of an number 
 *<li>CATSqrt       : returns the squareroot of an number 
 *<li>CATFabs       : return the absolute value of a float or double 
 *<li>CATAbs        : return the absolute value of an int or CATLONG32 
 *<li>CATCos        : returns the cosinus of an number 
 *<li>CATSin        : returns the sinus of an number 
 *<li>CATLog        : returns the logarithm of an number 
 *<li>CATTan        : returns the tangent of an number
 *<li>CATAcos       : returns the arccosine of a number
 *<li>CATAtan       : returns the arctangent of an number. If there are two arguments,
 *                      behaves as atan2 and resolve the angle in the interval -Pi, Pi
 *<li>CATSwap(A,B)  : swaps two values of the same type (double, float, int or
 *                    CATLONG32)
 *</ul>
*/

#if (defined(_MSC_VER) && (_MSC_VER >= 1900))
#include <cmath>
#else
#include <math.h>
#endif
#include "CATDataType.h"
#include "CATMathInline.h"

//=============================================================================
// WARNING !!!
//   if this define is inactive, there is no more allowed assembly code
//   inside the full C++ source code
//=============================================================================

#define _ASM_ALLOWED

//=============================================================================
// INTERFACES OF the FUNCTIONS
//=============================================================================

//--------------------------------------------------------------
// Max and Min are defined for CATINTPTR, int, float and double,
// for two or three values
//--------------------------------------------------------------

#ifdef PLATEFORME_DS64
/**
 * Returns the minimum of two ints/longs.
 */
INLINE CATINTPTR CATMin(CATINTPTR iValueA, CATINTPTR iValueB) ;
/**
 * Returns the minimum of two ints/longs.
 */
INLINE CATINTPTR CATMin(CATINTPTR iValueA, CATINT32  iValueB) ;
/**
 * Returns the minimum of two ints/longs.
 */
INLINE CATINTPTR CATMin(CATINT32  iValueA, CATINTPTR iValueB) ;
/**
 * Returns the minimum of three ints/longs.
 */ 
INLINE CATINTPTR CATMin(CATINTPTR iValueA, CATINTPTR iValueB, CATINTPTR iValueC) ;
#else
/**
 * Returns the minimum of two longs.
 */
INLINE CATLONG32 CATMin(CATLONG32 iValueA, CATLONG32 iValueB) ;
/**
 * Returns the minimum of three longs.
 */ 
INLINE CATLONG32 CATMin(CATLONG32 iValueA, CATLONG32 iValueB, CATLONG32 iValueC) ;
#endif

/**
 * Returns the minimum of two ints.
 */ 
INLINE int    CATMin(int    iValueA, int    iValueB) ; 
/**
 * Returns the minimum of three ints.
 */
INLINE int    CATMin(int    iValueA, int    iValueB, int    iValueC) ; 
/**
 * @nodoc
 */
INLINE float  CATMin(float  iValueA, float  iValueB) ;
/**
 * @nodoc
 */ 
INLINE float  CATMin(float  iValueA, float  iValueB, float  iValueC) ; 
/**
 * Returns the minimum of two doubles.
 */
INLINE double CATMin(double iValueA, double iValueB) ; 
/**
 * Returns the minimum of three doubles.
 */
INLINE double CATMin(double iValueA, double iValueB, double iValueC) ; 

#ifdef PLATEFORME_DS64
/**
 * Returns the maximum of two ints/longs.
 */
INLINE CATINTPTR CATMax(CATINTPTR iValueA, CATINTPTR iValueB) ; 
/**
 * Returns the maximum of two ints/longs.
 */
INLINE CATINTPTR CATMax(CATINTPTR iValueA, CATINT32  iValueB) ; 
/**
 * Returns the maximum of two ints/longs.
 */
INLINE CATINTPTR CATMax(CATINT32  iValueA, CATINTPTR iValueB) ; 
/**
 * Returns the maximum of three ints/longs.
 */
INLINE CATINTPTR CATMax(CATINTPTR iValueA, CATINTPTR iValueB, CATINTPTR iValueC) ;
#else
/**
 * Returns the maximum of two longs.
 */
INLINE CATLONG32 CATMax(CATLONG32 iValueA, CATLONG32 iValueB) ; 
/**
 * Returns the maximum of three longs.
 */
INLINE CATLONG32 CATMax(CATLONG32 iValueA, CATLONG32 iValueB, CATLONG32 iValueC) ;
#endif

/**
 * Returns the maximum of two ints.
 */ 
INLINE int    CATMax(int    iValueA, int    iValueB) ; 
/**
 * Returns the maximum of three ints.
 */
INLINE int    CATMax(int    iValueA, int    iValueB, int    iValueC) ; 
/**
 * @nodoc
 */
INLINE float  CATMax(float  iValueA, float  iValueB) ;
/**
 * @nodoc
 */ 
INLINE float  CATMax(float  iValueA, float  iValueB, float  iValueC) ;
/**
 * Returns the maximum of two doubles.
 */ 
INLINE double CATMax(double iValueA, double iValueB) ; 
/**
 * Returns the maximum of three doubles.
 */
INLINE double CATMax(double iValueA, double iValueB, double iValueC) ; 

//-----------------------------------------------------------------
// Return the square and cube of an CATINTPTR, int, float or double
//-----------------------------------------------------------------

#ifdef PLATEFORME_DS64
/**
 * Returns the square of a CATINTPTR/int.
 */
INLINE CATINTPTR CATSquare(CATINTPTR iValue) ;
#else
/**
 * Returns the square of a CATLONG32.
 */
INLINE CATLONG32 CATSquare(CATLONG32 iValue) ;
#endif

/**
 * Returns the square of an int.
 */ 
INLINE int    CATSquare(int    iValue) ; 
/**
 * @nodoc
 */
INLINE float  CATSquare(float  iValue) ;
/**
 * Returns the square of a double.
 */  
INLINE double CATSquare(double iValue) ; 

#ifdef PLATEFORME_DS64
/**
 * Returns the cube of a CATINTPTR/int.
 */ 
INLINE CATINTPTR CATPower3(CATINTPTR iValue) ; 
#else
/**
 * Returns the cube of a CATLONG32.
 */ 
INLINE CATLONG32 CATPower3(CATLONG32 iValue) ; 
#endif

/**
 * Returns the cube of an int.
 */ 
INLINE int    CATPower3(int    iValue) ; 
/**
 * @nodoc
 */
INLINE float  CATPower3(float  iValue) ; 
/**
 * Returns the cube of a double.
 */ 
INLINE double CATPower3(double iValue) ; 

//------------------------------------------------------------
// Returns the sign of the argument (-1, 0 or 1)
// Note that there is no tolerance for 0
//------------------------------------------------------------

#ifdef PLATEFORME_DS64
/**
 * Returns the sign of a CATINTPTR.
 * @return
 * The sign.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>-1</tt></dt><dd> for a negative value
 * <dt><tt>1</tt></dt><dd> for a positive value
 * <dt><tt>0</tt></dt><dd> for a null value
 * </dl>
 */
INLINE CATINTPTR CATSign(CATINTPTR  iValue) ; 
/**
 * Returns the sign of an int.
 * @return
 * The sign.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>-1</tt></dt><dd> for a negative value
 * <dt><tt>1</tt></dt><dd> for a positive value
 * <dt><tt>0</tt></dt><dd> for a null value
 * </dl>
 */
INLINE int CATSign(int iValue) ;
/**
 * @nodoc
 */ 
INLINE CATINTPTR CATSign(float   iValue) ;
/**
 * Returns the sign of a double.
 * <br>There is no tolerance for the null value.
 * @return
 * The sign.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>-1</tt></dt><dd> for a negative value
 * <dt><tt>1</tt></dt><dd> for a positive value
 * <dt><tt>0</tt></dt><dd> for a null value
 * </dl>
 */ 
INLINE CATINTPTR CATSign(double  iValue) ; 
#else
/**
 * Returns the sign of a CATLONG32.
 * @return
 * The sign.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>-1</tt></dt><dd> for a negative value
 * <dt><tt>1</tt></dt><dd> for a positive value
 * <dt><tt>0</tt></dt><dd> for a null value
 * </dl>
 */
INLINE CATLONG32 CATSign(CATLONG32  iValue) ; 
/**
 * Returns the sign of an int.
 * @return
 * The sign.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>-1</tt></dt><dd> for a negative value
 * <dt><tt>1</tt></dt><dd> for a positive value
 * <dt><tt>0</tt></dt><dd> for a null value
 * </dl>
 */
INLINE CATLONG32 CATSign(int     iValue) ;
/**
 * @nodoc
 */ 
INLINE CATLONG32 CATSign(float   iValue) ;
/**
 * Returns the sign of a double.
 * <br>There is no tolerance for the null value.
 * @return
 * The sign.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>-1</tt></dt><dd> for a negative value
 * <dt><tt>1</tt></dt><dd> for a positive value
 * <dt><tt>0</tt></dt><dd> for a null value
 * </dl>
 */ 
INLINE CATLONG32 CATSign(double  iValue) ; 
#endif

#ifdef PLATEFORME_DS64
/**
 * Transfers the sign of <tt>iValueJ</tt> to the CATINTPTR <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE CATINTPTR CATIsign(CATINTPTR iValueI, CATINTPTR iValueJ) ;
/**
 * Transfers the sign of <tt>iValueJ</tt> to the CATINTPTR <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE CATINTPTR CATIsign(CATINTPTR iValueI, int    iValueJ) ;
/**
 * Transfers the sign of <tt>iValueJ</tt> to the int <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE CATINTPTR CATIsign(int    iValueI, CATINTPTR iValueJ) ;
#else
/**
 * Transfers the sign of <tt>iValueJ</tt> to the CATLONG32 <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE CATLONG32 CATIsign(CATLONG32 iValueI, CATLONG32 iValueJ) ;
/**
 * Transfers the sign of <tt>iValueJ</tt> to the CATLONG32 <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE CATLONG32 CATIsign(CATLONG32 iValueI, int  iValueJ) ;
/**
 * Transfers the sign of <tt>iValueJ</tt> to the int <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE CATLONG32 CATIsign(int  iValueI, CATLONG32 iValueJ) ;
#endif

/**
 * Transfers the sign of <tt>iValueJ</tt> to the int <tt>|iValueI|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueI)</tt> if <tt>iValueJ<0</tt>, <tt>CATAbs(iValueI)</tt> otherwise.
 */
INLINE int    CATIsign(int    iValueI, int    iValueJ) ;
/**
 * Transfers the sign of <tt>iValueB</tt> to the double <tt>|iValueA|</tt>.
 * @return
 * The value: <tt>-CATAbs(iValueA)</tt> if <tt>iValueB<0</tt>, <tt>CATAbs(iValueA)</tt> otherwise.
 */
INLINE double CATDsign(double iValueA, double iValueB) ;
/**
 * @nodoc
 */
INLINE float  CATDsign(float  iValueA, float  iValueB) ;
/**
 * Multiplies the sign of <tt>iValueB</tt> by the double <tt>iValueA</tt>.
 */
INLINE double CATMsign(double iValueA, double iValueB) ;
/**
 * @nodoc
 */
INLINE float  CATMsign(float  iValueA, float  iValueB) ;

#ifdef PLATEFORME_DS64
/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE CATINTPTR CATIdim(CATINTPTR  iValueI, CATINTPTR iValueJ) ;
/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE CATINTPTR CATIdim(CATINTPTR  iValueI, int  iValueJ) ;
/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE CATINTPTR CATIdim(int iValueI, CATINTPTR iValueJ) ;
#else
/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE CATLONG32 CATIdim(CATLONG32  iValueI, CATLONG32 iValueJ) ;
/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE CATLONG32 CATIdim(CATLONG32  iValueI, int  iValueJ) ;
/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE CATLONG32 CATIdim(int iValueI, CATLONG32 iValueJ) ;
#endif

/**
 * Returns the positive difference <tt>iValueI-iValueJ</tt>, else zero.
 */
INLINE int    CATIdim(int     iValueI, int    iValueJ) ;


//------------------------------------------------------------
// Mathematical functions that have been defined
//------------------------------------------------------------
#ifdef __Only_to_show_the_interfaces

/**
 * Returns the arc-tangent of a value (expressed in radian).
 */
double CATAtan(double iTangent) ; 

/**
 * Returns the angle corresponding two the given sinus and cosinus
 * (expressed in radian).
 */
double CATAtan(double iY, double iX) ; 

/**
 * Returns the absolute value.
 */
double CATFabs(double iValue) ; 
/**
 * @nodoc
 */
float  CATFabs(float  iValue) ; 

#ifdef PLATEFORME_DS64
/**
 * Returns the absolute value.
 */
CATINTPTR CATAbs (CATINTPTR iValue) ;
#else
/**
 * Returns the absolute value.
 */
CATLONG32 CATAbs (CATLONG32 iValue) ;
#endif

/**
 * Returns the absolute value.
 */ 
int    CATAbs (int    iValue) ; 

// Classical sinus and cosinus and tangent with angles in radians
/**
 * Returns the sine of an angle expressed in radian.
 */
double CATSin(double iAngle);
/**
 * Returns the cosine of an angle expressed in radian.
 */
double CATCos(double iAngle);
/**
 * @nodoc
 */
void CATSincos(double iANGLE, double ioSINUS, double ioCOSINUS);
/**
 * Returns the tangent of an angle expressed in radian.
 */
double CATTan(double iAngle);
/**
 * Returns the arccosine of an angle expressed in radian.
 */
double CATAcos(double iValue);

/**
 * Returns the neperian logarithm.
 */
double CATLog(double iValue);

/**
 * Returns the exponential.
 */
double CATExp(double iValue);

/**
 * Returns the square root.
 */
double CATSqrt(double iValue);

#endif

//------------------------------------------------------------
// Swapping two values contained in variables
//------------------------------------------------------------

#ifdef PLATEFORME_DS64
/**
 * Swaps two CATINTPTR values.
 * <br><tt>ioValueA</tt> becomes <tt>ioValueB</tt> and the converse.
 */
INLINE void CATSwap(CATINTPTR &ioValueA, CATINTPTR &ioValueB) ; 
#else
/**
 * Swaps two CATLONG32 values.
 * <br><tt>ioValueA</tt> becomes <tt>ioValueB</tt> and the converse.
 */
INLINE void CATSwap(CATLONG32 &ioValueA, CATLONG32 &ioValueB) ; 
#endif

/**
 * Swaps two int values.
 * <br><tt>ioValueA</tt> becomes <tt>ioValueB</tt> and the converse.
 */
INLINE void CATSwap(int    &ioValueA, int    &ioValueB) ; 
/**
 * @nodoc
 */
INLINE void CATSwap(float  &ioValueA, float  &ioValueB) ;
/**
 * Swaps two double values.
 * <br><tt>ioValueA</tt> becomes <tt>ioValueB</tt> and the converse.
 */ 
INLINE void CATSwap(double &ioValueA, double &ioValueB) ; 


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================


#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATMin(CATINTPTR iValueA, CATINTPTR iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE CATINTPTR CATMin(CATINTPTR iValueA, CATINT32  iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE CATINTPTR CATMin(CATINT32  iValueA, CATINTPTR iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE CATINTPTR CATMin(CATINTPTR iValueA, CATINTPTR iValueB, CATINTPTR iValueC)
{
  return (iValueA > iValueB) ? ( (iValueB > iValueC) ? iValueC : iValueB)
    : (( iValueA > iValueC) ? iValueC : iValueA);
};
#else
INLINE CATLONG32 CATMin(CATLONG32 iValueA, CATLONG32 iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE CATLONG32 CATMin(CATLONG32 iValueA, CATLONG32 iValueB, CATLONG32 iValueC)
{
  return (iValueA > iValueB) ? ( (iValueB > iValueC) ? iValueC : iValueB)
    : (( iValueA > iValueC) ? iValueC : iValueA);
};
#endif

INLINE int CATMin(int iValueA, int iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE int CATMin(int iValueA, int iValueB, int iValueC)
{
  return (iValueA > iValueB) ? ( (iValueB > iValueC) ? iValueC : iValueB)
    : (( iValueA > iValueC) ? iValueC : iValueA);
};

INLINE float CATMin(float iValueA, float iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE float CATMin(float iValueA, float iValueB, float iValueC)
{
  return (iValueA > iValueB) ? ( (iValueB > iValueC) ? iValueC : iValueB)
    : (( iValueA > iValueC) ? iValueC : iValueA);
};

INLINE double CATMin(double iValueA, double iValueB)
{
  return (iValueA > iValueB) ? iValueB : iValueA;
};

INLINE double CATMin(double iValueA, double  iValueB, double iValueC)
{
  return (iValueA > iValueB) ? ( (iValueB > iValueC) ? iValueC : iValueB)
    : (( iValueA > iValueC) ? iValueC : iValueA);
};

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATMax(CATINTPTR iValueA, CATINTPTR iValueB)
{
  return (iValueA < iValueB) ? iValueB : iValueA;
};

INLINE CATINTPTR CATMax(CATINTPTR iValueA, CATINT32  iValueB)
{
  return (iValueA < iValueB) ? iValueB : iValueA;
};

INLINE CATINTPTR CATMax(CATINT32  iValueA, CATINTPTR iValueB)
{
  return (iValueA < iValueB) ? iValueB : iValueA;
};

INLINE CATINTPTR CATMax(CATINTPTR iValueA, CATINTPTR iValueB, CATINTPTR iValueC)
{
  return (iValueA > iValueB) ? ( (iValueA > iValueC) ? iValueA : iValueC)
    : (( iValueB > iValueC) ? iValueB : iValueC);
};
#else
INLINE CATLONG32 CATMax(CATLONG32 iValueA, CATLONG32 iValueB)
{
  return (iValueA < iValueB) ? iValueB : iValueA;
};

INLINE CATLONG32 CATMax(CATLONG32 iValueA, CATLONG32 iValueB, CATLONG32 iValueC)
{
  return (iValueA > iValueB) ? ( (iValueA > iValueC) ? iValueA : iValueC)
    : (( iValueB > iValueC) ? iValueB : iValueC);
};
#endif

INLINE int CATMax(int iValueA, int iValueB)
{
  return ((iValueA < iValueB) ? iValueB : iValueA);
};

INLINE int CATMax(int iValueA, int iValueB, int iValueC)
{
  return (iValueA > iValueB) ? ( (iValueA > iValueC) ? iValueA : iValueC)
    : (( iValueB > iValueC) ? iValueB : iValueC);
};

INLINE float CATMax(float iValueA, float iValueB)
{
  return (iValueA < iValueB) ? iValueB : iValueA;
};

INLINE float CATMax(float iValueA, float iValueB, float iValueC)
{
  return (iValueA > iValueB) ? ( (iValueA > iValueC) ? iValueA : iValueC)
    : (( iValueB > iValueC) ? iValueB : iValueC);
};

INLINE double CATMax(double iValueA, double iValueB)
{
  return (iValueA < iValueB) ? iValueB : iValueA;
};

INLINE double CATMax(double iValueA, double iValueB, double iValueC)
{
  return (iValueA > iValueB) ? ( (iValueA > iValueC) ? iValueA : iValueC)
    : (( iValueB > iValueC) ? iValueB : iValueC);
};

//=============================================================================
// Return the square and cube of an CATLONG32, int, float or double
//=============================================================================

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATSquare(CATINTPTR iValue)
{
  return iValue*iValue;
};
#else
INLINE CATLONG32 CATSquare(CATLONG32 iValue)
{
  return iValue*iValue;
};
#endif

INLINE int CATSquare(int iValue)
{
  return iValue*iValue;
};

INLINE float CATSquare(float iValue)
{
  return iValue*iValue;
};

INLINE double CATSquare(double iValue)
{
  return iValue*iValue;
};

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATPower3(CATINTPTR iValue)
{
  return iValue*iValue*iValue;
};
#else
INLINE CATLONG32 CATPower3(CATLONG32 iValue)
{
  return iValue*iValue*iValue;
};
#endif

INLINE int CATPower3(int iValue)
{
  return iValue*iValue*iValue;
};

INLINE float CATPower3(float iValue)
{
  return iValue*iValue*iValue;
};

INLINE double CATPower3(double iValue)
{
  return iValue*iValue*iValue;
};

//=============================================================================
// Return the sign of the Value ( 1 if positive, -1 if negative
// 0 if equal to 0 )
//=============================================================================

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATSign(CATINTPTR  iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};

INLINE int CATSign(int iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};

INLINE CATINTPTR CATSign(float   iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};

INLINE CATINTPTR CATSign(double  iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};
#else
INLINE CATLONG32 CATSign(CATLONG32 iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};

INLINE CATLONG32 CATSign(int iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};

INLINE CATLONG32 CATSign(float iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};

INLINE CATLONG32 CATSign(double iValue)
{
  return (iValue > 0) ? 1 : ( (iValue < 0) ? -1 : 0 );
};
#endif

//=============================================================================
// Returns the sinus, the cosinus, the logarithm, tangent, arctangent and
// the squareroot
//=============================================================================
#define CATSin sin

#define CATCos cos

#include "CATMathSincos.h"        // simultaneous

#define CATLog log

#define CATTan tan

#define CATAcos acos

#define CATSqrt sqrt 

#define CATExp exp

INLINE double CATAtan(double iValue)
{
  return atan(iValue);
};

INLINE double CATAtan(double iSinus, double iCosinus)
{
  return atan2(iSinus, iCosinus);
}


// Returns the absolute value
INLINE double CATFabs(double iValue)
{
#if defined(_WINDOWS_SOURCE)
  return (fabs(iValue));
#else
  return (iValue >= 0.) ? iValue : -iValue;
#endif
};

INLINE float CATFabs(float iValue)
{
  return (iValue >= 0.f) ? iValue : -iValue;
};

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATAbs (CATINTPTR iValue)
{
  return (iValue >= 0) ? iValue : -iValue;
};
#else
INLINE CATLONG32 CATAbs(CATLONG32 iValue)
{
  return (iValue >= 0) ? iValue : -iValue;
};
#endif

INLINE int CATAbs(int iValue)
{
  return (iValue >= 0) ? iValue : -iValue;
};

//=============================================================================
// Swaps two values (double, float or CATLONG32)
//=============================================================================

#ifdef PLATEFORME_DS64
INLINE void CATSwap(CATINTPTR &ioValueA, CATINTPTR &ioValueB)
{
  CATINTPTR C=ioValueA;
  ioValueA=ioValueB;
  ioValueB=C;
};
#else
INLINE void CATSwap(CATLONG32 &ioValueA, CATLONG32 &ioValueB)
{
  CATLONG32 C=ioValueA;
  ioValueA=ioValueB;
  ioValueB=C;
};
#endif

INLINE void CATSwap(int &ioValueA, int &ioValueB)
{
  int C=ioValueA;
  ioValueA=ioValueB;
  ioValueB=C;
};

INLINE void CATSwap(float &ioValueA, float &ioValueB)
{
  float C=ioValueA;
  ioValueA=ioValueB;
  ioValueB=C;
};

INLINE void CATSwap(double &ioValueA, double &ioValueB)
{
  double C=ioValueA;
  ioValueA=ioValueB;
  ioValueB=C;
};

//=============================================================================
// Compound sign and positive difference
//=============================================================================

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATIsign(CATINTPTR iValueI, CATINTPTR iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}

INLINE CATINTPTR CATIsign(CATINTPTR iValueI, int    iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}

INLINE CATINTPTR CATIsign(int    iValueI, CATINTPTR iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}
#else
INLINE CATLONG32 CATIsign(CATLONG32 iValueI, CATLONG32 iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}

INLINE CATLONG32 CATIsign(CATLONG32 iValueI, int iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}

INLINE CATLONG32 CATIsign(int iValueI, CATLONG32 iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}
#endif

INLINE int CATIsign(int iValueI, int iValueJ)
{
  return iValueJ < 0   ?   - CATAbs ( iValueI )   :   CATAbs ( iValueI );
}

INLINE double CATDsign(double iValueA, double iValueB)
{
  return iValueB < 0.   ?   - fabs ( iValueA )   :   fabs ( iValueA );
}

INLINE float CATDsign(float iValueA, float iValueB)
{
  return iValueB < 0.f   ?   - CATFabs ( iValueA )   :   CATFabs ( iValueA );
}

INLINE double CATMsign(double iValueA, double iValueB)
{
  return iValueB < 0.   ?   - iValueA   :   iValueA;
}

INLINE float CATMsign(float iValueA, float iValueB)
{
  return iValueB < 0.f   ?   - iValueA   :   iValueA;
}

#ifdef PLATEFORME_DS64
INLINE CATINTPTR CATIdim(CATINTPTR  iValueI, CATINTPTR iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}

INLINE CATINTPTR CATIdim(CATINTPTR  iValueI, int  iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}

INLINE CATINTPTR CATIdim(int iValueI, CATINTPTR iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}
#else
INLINE CATLONG32 CATIdim(CATLONG32 iValueI, CATLONG32 iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}

INLINE CATLONG32 CATIdim(CATLONG32 iValueI, int iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}

INLINE CATLONG32 CATIdim(int iValueI, CATLONG32 iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}
#endif

INLINE int CATIdim(int iValueI, int iValueJ)
{
  return iValueJ < iValueI   ?   iValueI - iValueJ   :   0;
}

#endif
