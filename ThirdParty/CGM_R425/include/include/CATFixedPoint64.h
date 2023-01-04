// Sep 10   Optimization with CATAddV3A and CATAddV3Array                 PR

#ifndef CATFixedPoint64_H
#define CATFixedPoint64_H

#include "CATDataType.h"
#include "CATBoolean.h"
#include "ExportedByCATMathStream.h"
#include "CATMathStreamImpl.h"
#include "CATMathInline.h"
#include "BigLittle.h"
#include "CATNullPointerThrow.h"
 
//#define CATFixedPoint64_V2_Inline


class ExportedByCATMathStream CATFixedPoint64
{
public:

  //if (Exponent > ExponentZero): Value = (-1)^Sign * 2^(Exponent - 63) * Mantissa	
  //if (Exponent <= ExponentZero) && (Mantissa == 0): Value = 0 
  struct Number
  {
    CATULONG64   Mantissa;//MSB is always 1 (ie. no hidden bit); Value in [2^63 .. 2^64 - 1]*/
    CATLONG32    Exponent;//Unbiased exponent; no denormalized number
    CATULONG32   Sign;//0x00: positive; 0x01: negative
  };

  //if (Exponent > ExponentZero): Value = (-1)^Sign * 2^(Exponent - 63) * (Mantissa << 2)	
  //if (Exponent <= ExponentZero) && (Mantissa == 0): Value = 0 
  struct NumberRShift
  {
    CATULONG64   Mantissa;//MSB is always 001 (ie. no hidden bit); Value in [2^61 .. 2^62 - 1]*/
    CATLONG32    Exponent;//Unbiased exponent; no denormalized number
    CATULONG32   Sign;//0x00: positive; 0x01: negative
  };

  static void Copy(Number  iA, Number  & oB);
  static void Add(Number  iA, Number  iB, unsigned int iSignB, Number & oC);
  static void AddV3(NumberRShift iA, NumberRShift iB, NumberRShift iC, Number & oD);


//#if defined ( CATFixedPoint64_V2_Inline )

  static INLINE void ConvertFromDouble(double iDouble, Number & oA);
  static INLINE void ConvertIntoDouble(Number & iA, double & oDouble);

	static INLINE void ConvertFromFloat(float iFloat, Number & oA);
  static INLINE void ConvertIntoFloat(Number & iA, float & oFloat);

  static INLINE void Multiply(Number & iA, Number & iB, Number & oC);
  static INLINE void Divide(Number & iA, Number & iB, Number & oC);

	static INLINE void Multiply_Float(Number & iA, Number & iB, Number & oC);
	static INLINE void Divide_Float(Number & iA, Number & iB, Number & oC);
 
  static INLINE void Normalize(Number & ioA);
  static INLINE void Normalize_Full(Number & ioA);

  static INLINE void ConvertDoubleIntoInteger(Number  iA, CATULONG64& oInteger);
  static INLINE void ConvertFromDoubleRShift(double iDouble, NumberRShift & oA);

	static INLINE void ConvertFloatIntoInteger(Number  iA, CATULONG32& oInteger);
  static INLINE void ConvertFromFloatRShift(float iFloat, NumberRShift & oA);

//  static INLINE void ConvertIntoDoubleRShift(Number  iA, double & oDouble);

//#else
//
//  static void Multiply(Number & iA, Number & iB, Number & oC);
//  static void ConvertIntoDouble(Number & iA, double & oDouble);
//  static void ConvertFromDouble(double iDouble, Number & oA);
//  static void Divide(Number & iA, Number & iB, Number & oC);
//
// 
//  static void Normalize(Number & ioA);
//
//#endif

private:
  union ULONG64AsByte
  {
    CATULONG64 Ulong64;
    unsigned char Byte[8];
  };
};





//#if defined ( CATFixedPoint64_V2_Inline )


union  CATIeee_754_DoublePrecision
{

  struct  
  {
#if ! defined ( _ENDIAN_LITTLE )

    unsigned int   sign          :  1;  
    unsigned int   exponent      : 11;  
    unsigned int   mantissaH     : 20;  
    unsigned int   mantissaL     : 32;  

#else

    unsigned int   mantissaL     : 32;  
    unsigned int   mantissaH     : 20;  
    unsigned int   exponent      : 11;  
    unsigned int   sign          :  1;  

#endif

  } ieee754;

  double Double;

};



union  CATIeee_754_FloatPrecision
{

  struct  
  {
#if ! defined ( _ENDIAN_LITTLE )

    unsigned int   sign          :  1;  
    unsigned int   exponent      :  8;  
    unsigned int   mantissa      : 23;   

#else

    unsigned int   mantissa      : 23;   
    unsigned int   exponent      :  8;  
    unsigned int   sign          :  1;  

#endif

  } ieee754_float;

  float Float;

};



INLINE void CATFixedPoint64::ConvertFromDouble(double iDouble, Number & oA)
{
  CATIeee_754_DoublePrecision ieee;
  ieee.Double = iDouble;

  oA.Sign     = ieee.ieee754.sign ? 1 : 0; 
  oA.Exponent = ieee.ieee754.exponent -1023; 
	if (oA.Exponent == -1023)
     oA.Mantissa = 0;
  else
     oA.Mantissa = 0x8000000000000000ULL | (CATULONG64(ieee.ieee754.mantissaH) << 43 )  
                                       | (CATULONG64(ieee.ieee754.mantissaL) << 11 ); 
}

INLINE  void CATFixedPoint64::ConvertIntoDouble(Number & iA, double & oDouble)
{
  CATIeee_754_DoublePrecision ieee;
  ieee.Double = 0.0;
  if (iA.Exponent > -1023)
  {
    ieee.ieee754.sign     = iA.Sign ? 1 : 0; 
    ieee.ieee754.exponent = 1023 + iA.Exponent;
    CATULONG64 RoundedMantissa = iA.Mantissa;
    CATULONG64 Residual = RoundedMantissa & 0x00000000000007FFULL; // 11 bits LSB
    //Rounding according to default mode (IEEE-754)
    if ( (Residual        > 0x0000000000000400ULL) ||//Round to nearest
       ( (Residual       == 0x0000000000000400ULL) 
      && (RoundedMantissa & 0x0000000000000800ULL)))//Tie to even
    {
      if((RoundedMantissa & 0xFFFFFFFFFFFFF800ULL) == 0xFFFFFFFFFFFFF800ULL) // carry
      {
        RoundedMantissa   = 0x8000000000000000ULL;
        ieee.ieee754.exponent++;
      }
      else
        RoundedMantissa  += 0x0000000000000800ULL;
    }
 
    ieee.ieee754.mantissaL = RoundedMantissa >> 11; // 32 bits
    ieee.ieee754.mantissaH = RoundedMantissa >> 43; // 20 bits
 
  }

  oDouble = ieee.Double;
}

INLINE void CATFixedPoint64::ConvertDoubleIntoInteger(Number  iA, CATULONG64& oInteger)
{
  oInteger = CATULONG64(iA.Sign) << 63;  
  /*
  //Rounding according to default mode (IEEE-754)
  CATULONG64 Residual = iA.Mantissa & 0x00000000000007FFULL;
  if ( (Residual        > 0x0000000000000400ULL) ||//Round to nearest
    ( (Residual       == 0x0000000000000400ULL) 
    && (iA.Mantissa & 0x0000000000000800ULL)))//Tie to even
  {
    if((iA.Mantissa & 0xFFFFFFFFFFFFF800ULL) == 0xFFFFFFFFFFFFF800ULL) // carry
    {
      iA.Mantissa   = 0x8000000000000000ULL;
      iA.Exponent++; 
    }
    else
      iA.Mantissa  += 0x0000000000000800ULL;
  }
*/
  oInteger |= CATULONG64(iA.Exponent + 1023) << 52;
  oInteger |= ((iA.Mantissa) << 1) >> 12;
}

INLINE void CATFixedPoint64::ConvertFromFloat(float iFloat, Number & oA)
{
	CATIeee_754_FloatPrecision ieee;
  ieee.Float = iFloat;

  oA.Sign     = ieee.ieee754_float.sign ? 1 : 0; 
  oA.Exponent = ieee.ieee754_float.exponent -127; 
	if (oA.Exponent == -127)
     oA.Mantissa = 0;
  else
     oA.Mantissa = 0x8000000000000000ULL | (CATULONG64(ieee.ieee754_float.mantissa) << 40 ); 
}

INLINE void CATFixedPoint64::ConvertIntoFloat(Number & iA, float & oFloat)
{
	CATIeee_754_FloatPrecision ieee;
  ieee.Float = 0.0;
  if (iA.Exponent > -127)
  {
    ieee.ieee754_float.sign     = iA.Sign ? 1 : 0; 
    ieee.ieee754_float.exponent = 127 + iA.Exponent;
    CATULONG64 RoundedMantissa = iA.Mantissa;
    CATULONG64 Residual = RoundedMantissa & 0x000000FFFFFFFFFFULL; // 8 bits LSB
    //Rounding according to default mode (IEEE-754)
    if ( (Residual        > 0x0000008000000000ULL) ||//Round to nearest
       ( (Residual       == 0x0000008000000000ULL) 
      && (RoundedMantissa & 0x0000010000000000ULL)))//Tie to even
    {
      if((RoundedMantissa & 0xFFFFFF0000000000ULL) == 0xFFFFFF0000000000ULL) // carry
      {
        RoundedMantissa   = 0x8000000000000000ULL;
        ieee.ieee754_float.exponent++;
      }
      else
        RoundedMantissa  += 0x0000010000000000ULL;
    }
 
    ieee.ieee754_float.mantissa = RoundedMantissa >> 40; // 32 bits
 
  }

  oFloat = ieee.Float;
}

INLINE void CATFixedPoint64::ConvertFloatIntoInteger(Number  iA, CATULONG32& oInteger)
{
	oInteger = CATULONG64(iA.Sign) << 31;  
  oInteger |= CATULONG64(iA.Exponent + 127) << 23;
  oInteger |= ((iA.Mantissa) << 1) >> 41;
}



INLINE void CATFixedPoint64::Multiply(Number & iA, Number & iB, Number & oC)
{
  CATLONG32 SumExponents = iA.Exponent + iB.Exponent;
  if ((iA.Exponent <= -1023) || (iB.Exponent <= -1023) || (SumExponents <= -1023))
  { oC.Exponent = -1023; oC.Mantissa = 0; return; } // zero

  union 
  {
    struct  
    {
#if ! defined ( _ENDIAN_LITTLE )
      CATULONG32 High;
      CATULONG32 Low;
#else
      CATULONG32 Low;
      CATULONG32 High;
#endif
    } Simple;

    CATULONG64 Double;
  } A,B,C,D;

  A.Double = iA.Mantissa ;
  B.Double = iB.Mantissa ;

  C.Double = CATULONG64(A.Simple.High)* CATULONG64(B.Simple.Low);
  D.Double = CATULONG64(A.Simple.Low) * CATULONG64(B.Simple.High);

  oC.Sign     = iA.Sign ^ iB.Sign;
  oC.Mantissa = CATULONG64(A.Simple.High) * CATULONG64(B.Simple.High) 
              + CATULONG64(C.Simple.High) + CATULONG64(D.Simple.High);
  oC.Exponent = SumExponents;

  if ( oC.Mantissa & 0x8000000000000000ULL ) // Offset
    oC.Exponent++;
  else // No Offset
    oC.Mantissa = oC.Mantissa << 1 ;

  if (oC.Exponent <= -1023)
  {
    oC.Exponent = -1023;
    oC.Mantissa = 0;
  }
}

INLINE void CATFixedPoint64::Multiply_Float(Number & iA, Number & iB, Number & oC)
{
 CATLONG32 SumExponents = iA.Exponent + iB.Exponent;
  if ((iA.Exponent <= -127) || (iB.Exponent <= -127) || (SumExponents <= -127))
  { oC.Exponent = -127; oC.Mantissa = 0; return; } // zero

  union 
  {
    struct  
    {
#if ! defined ( _ENDIAN_LITTLE )
      CATULONG32 High;
      CATULONG32 Low;
#else
      CATULONG32 Low;
      CATULONG32 High;
#endif
    } Simple;

    CATULONG64 Double;
  } A,B,C,D;

  A.Double = iA.Mantissa ;
  B.Double = iB.Mantissa ;

  C.Double = CATULONG64(A.Simple.High)* CATULONG64(B.Simple.Low);
  D.Double = CATULONG64(A.Simple.Low) * CATULONG64(B.Simple.High);

  oC.Sign     = iA.Sign ^ iB.Sign;
  oC.Mantissa = CATULONG64(A.Simple.High) * CATULONG64(B.Simple.High) 
              + CATULONG64(C.Simple.High) + CATULONG64(D.Simple.High);
  oC.Exponent = SumExponents;

  if ( oC.Mantissa & 0x8000000000000000ULL ) // Offset
    oC.Exponent++;
  else // No Offset
    oC.Mantissa = oC.Mantissa << 1 ;

  if (oC.Exponent <= -127)
  {
    oC.Exponent = -127;
    oC.Mantissa = 0;
  }
}


INLINE void CATFixedPoint64::Divide(Number & iDividend, Number & iDivisor, Number & oC)
{
  if (iDividend.Exponent <= -1023) /* NULL dividend */
  { oC.Exponent = -1023;  oC.Mantissa = 0; return;  }

  if (iDivisor.Exponent <= -1023) /* NULL divisor */
  { oC.Exponent = 1024; /*Infinite*/ oC.Mantissa = 0; return; }

  oC.Sign = iDividend.Sign ^ iDivisor.Sign;
  CATULONG64 DivisorHigh  = iDivisor.Mantissa >> 32;
  CATULONG64 QuotientHigh = iDividend.Mantissa / DivisorHigh;
  CATULONG64 Remainder    = iDividend.Mantissa - QuotientHigh * DivisorHigh;
  CATULONG64 Quidam       = (iDivisor.Mantissa << 32) / DivisorHigh;
  CATULONG64 QuotientLow  = (Remainder << 32) / DivisorHigh;
  CATULONG64 Quotient     = (QuotientHigh << 31) + (QuotientLow >> 1);//(A/DivisorHigh)*2^31
  oC.Mantissa = Quotient - ( ((Quotient >> 32) * (Quidam >> 1) ) >> 31 );
  oC.Exponent = iDividend.Exponent - iDivisor.Exponent;

  if ( ! (oC.Mantissa & 0x8000000000000000ULL) ) // No Offset, normalize
  { oC.Exponent--;  oC.Mantissa = oC.Mantissa <<  1 ; }

  if (iDividend.Exponent <= -1023) // normalize
  { oC.Exponent = -1023;  oC.Mantissa = 0;  }

}

INLINE void CATFixedPoint64::Divide_Float(Number & iDividend, Number & iDivisor, Number & oC)
{
  if (iDividend.Exponent <= -127) /* NULL dividend */
  { oC.Exponent = -127;  oC.Mantissa = 0; return;  }

  if (iDivisor.Exponent <= -127) /* NULL divisor */
  { oC.Exponent = 128; /*Infinite*/ oC.Mantissa = 0; return; }

  oC.Sign = iDividend.Sign ^ iDivisor.Sign;
  CATULONG64 DivisorHigh  = iDivisor.Mantissa >> 32;
  CATULONG64 QuotientHigh = iDividend.Mantissa / DivisorHigh;
  CATULONG64 Remainder    = iDividend.Mantissa - QuotientHigh * DivisorHigh;
  CATULONG64 Quidam       = (iDivisor.Mantissa << 32) / DivisorHigh;
  CATULONG64 QuotientLow  = (Remainder << 32) / DivisorHigh;
  CATULONG64 Quotient     = (QuotientHigh << 31) + (QuotientLow >> 1);//(A/DivisorHigh)*2^31
  oC.Mantissa = Quotient - ( ((Quotient >> 32) * (Quidam >> 1) ) >> 31 );
  oC.Exponent = iDividend.Exponent - iDivisor.Exponent;

  if ( ! (oC.Mantissa & 0x8000000000000000ULL) ) // No Offset, normalize
  { oC.Exponent--;  oC.Mantissa = oC.Mantissa <<  1 ; }

  if (iDividend.Exponent <= -127) // normalize
  { oC.Exponent = -127;  oC.Mantissa = 0;  }

}

// for Mantissa, the first two bits are 0
INLINE void CATFixedPoint64::Normalize(Number & ioA)
{
	if (ioA.Mantissa & 0x8000000000000000ULL)
	{
		ioA.Exponent += 2;
	}
	else if (ioA.Mantissa & 0x4000000000000000ULL)
	{
		ioA.Exponent += 1;
		ioA.Mantissa <<= 1;
	}
	else if (ioA.Mantissa & 0x2000000000000000ULL)
	{
		ioA.Mantissa <<= 2;
	}
	else if (ioA.Mantissa & 0x1000000000000000ULL)
	{
		ioA.Exponent -= 1;
		ioA.Mantissa <<= 3;
		if (ioA.Exponent <= -1023)
		{
			ioA.Exponent = -1023;
			ioA.Mantissa = 0;
		}
	}
	else
	{
		CATULONG64 Mask  = 0x0800000000000000ULL;
		for (int numbit = 2; numbit < 51; numbit++, Mask >>= 1)
		{
			if (ioA.Mantissa & Mask) 
			{
				ioA.Exponent -= numbit;
				if (ioA.Exponent > -1023)
				{
					ioA.Mantissa <<= (numbit + 2);
					return;
				}
				else
				{ 
					break;
				}
			}
		}
		ioA.Exponent = -1023; 
		ioA.Mantissa = 0; 
	}
}

INLINE void CATFixedPoint64::Normalize_Full(Number & ioA)
{
	if (ioA.Mantissa & 0x8000000000000000ULL)
		return;

	CATULONG64 Mask  = 0x4000000000000000ULL;
	for (int numbit = 1; Mask;   numbit++, Mask = Mask >> 1)
	{
    if ( ioA.Mantissa & Mask  ) 
    {
      ioA.Exponent = (ioA.Exponent - numbit);

      if (ioA.Exponent > -1023)
        ioA.Mantissa = ioA.Mantissa << numbit;
      else
      { ioA.Exponent = -1023; ioA.Mantissa  = 0; }

      return;
    }
 	}
	ioA.Exponent = -1023;
  ioA.Mantissa = 0;
  return;
}

//#endif



INLINE void CATFixedPoint64::ConvertFromDoubleRShift(double iDouble, NumberRShift & oA)
{
  CATIeee_754_DoublePrecision ieee;
  ieee.Double = iDouble;

  oA.Sign     = ieee.ieee754.sign ? 1 : 0; 
  oA.Exponent = ieee.ieee754.exponent -1023; 
	if (oA.Exponent == -1023)
     oA.Mantissa = 0;
  else
     oA.Mantissa = 0x2000000000000000ULL | (CATULONG64(ieee.ieee754.mantissaH) << 41 )  
                                       | (CATULONG64(ieee.ieee754.mantissaL) << 9 ); 
}

INLINE void CATFixedPoint64::ConvertFromFloatRShift(float iFloat, NumberRShift & oA)
{
	CATIeee_754_FloatPrecision ieee;
  ieee.Float = iFloat;

  oA.Sign     = ieee.ieee754_float.sign ? 1 : 0; 
  oA.Exponent = ieee.ieee754_float.exponent -127; 
	if (oA.Exponent == -127)
     oA.Mantissa = 0;
  else
     oA.Mantissa = 0x2000000000000000ULL | (CATULONG64(ieee.ieee754_float.mantissa) << 38 ); 
}


/*
INLINE void CATFixedPoint64::ConvertIntoDoubleRShift(Number  iA, double & oDouble)
{
  CATIeee_754_DoublePrecision ieee;
  ieee.Double = 0.0;
  if (iA.Exponent > -1023)
  {
    ieee.ieee754.sign     = iA.Sign ? 1 : 0; 
    ieee.ieee754.exponent = 1023 + iA.Exponent;
    CATULONG64 RoundedMantissa = (iA.Mantissa) << 2;
    CATULONG64 Residual = RoundedMantissa & 0x00000000000007FFULL; // 11 bits LSB
    //Rounding according to default mode (IEEE-754)
    if ( (Residual        > 0x0000000000000400ULL) ||//Round to nearest
       ( (Residual       == 0x0000000000000400ULL) 
      && (RoundedMantissa & 0x0000000000000800ULL)))//Tie to even
    {
      if((RoundedMantissa & 0xFFFFFFFFFFFFF800ULL) == 0xFFFFFFFFFFFFF800ULL) // carry
      {
        RoundedMantissa   = 0x8000000000000000ULL;
        ieee.ieee754.exponent++;
      }
      else
        RoundedMantissa  += 0x0000000000000800ULL;
    }
 
    ieee.ieee754.mantissaL = RoundedMantissa >> 11; // 32 bits
    ieee.ieee754.mantissaH = RoundedMantissa >> 43; // 20 bits
 
  }

  oDouble = ieee.Double;
}
*/

//#ifdef NurbsCompactOptimPR
extern "C" void CATAddV3A
  ( CATFixedPoint64::NumberRShift &iA, CATFixedPoint64::NumberRShift &iB,
    CATFixedPoint64::NumberRShift &iC, CATFixedPoint64::Number &oD );

extern "C" void CATAddV3Array
  ( CATFixedPoint64::NumberRShift *iA, CATFixedPoint64::Number *oD,
    int iMCnt, int iLCnt );
#endif  //NurbsCompactOptimPR

//#endif
