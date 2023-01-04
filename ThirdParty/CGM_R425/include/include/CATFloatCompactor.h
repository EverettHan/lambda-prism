
#ifndef CATFloatCompactor_H
#define CATFloatCompactor_H

#include "CATDataType.h"
#include "CATBoolean.h"
#include "ExportedByCATMathStream.h"
#include "CATMathStreamBits.h"
#include "CATMathInline.h"
#include "CATFixedPoint64.h"

class CATMathStreamImpl;

class ExportedByCATMathStream CATFloatCompactor
{
public: 
CATFloatCompactor(CATMathStreamImpl * ioStream, CATMathStreamBits::FlowType iFlowType);
~CATFloatCompactor();

void WriteFloat(float* iFloat, unsigned int iNbCells, unsigned int iDebugType);
void EndWrite();
void ReadFloat(float*  oFloatList, unsigned int iNbCells);
//void SetNbTypeDebug(unsigned int iNbType);
void WriteFloatStandard(float iFloat, unsigned int iDebugType);
void WriteFloatWithRef2(float* iFloat, float* iReference, unsigned int iNbCells,  float iThreshold , unsigned int iDebugType);
void ReadFloatWithRef2(float* iReference,  unsigned int iNbCells, float iThreshold , float* oReadFloat);
float ReadFloatStandard();


// with CATFixedPoint64
void WriteFloatWithRef(float* iFloat, CATFixedPoint64::Number* iReference, unsigned int iNbCells, int ThresholdExponent, unsigned int iDebugType);
void ReadFloatWithRef(CATFixedPoint64::Number* iReference, unsigned int iNbCells, int ThresholdExponent, float* oReadFloat);

private:
	struct Stat
	{
		unsigned int NbType;
		int NbFloatForObject;
		int * NbFloatForObjectByType;
		int StorageSizeForObject;
		int * StorageSizeForObjectByType;
		int	Trace;
		int NbFailure;
	};

	struct Debug
	{
		int NbFloat;
		float * Float;
		CATBoolean * IsWithReference;
		float * FloatReference;
    float * Threshold;
		char * Char;
		int FloatIndex;
		int CharIndex;
	};

	struct Buffer
	{
		unsigned char Byte;
		short Index;//[0..4] = nb bits written or read
	};

	union FloatAsByte
	{
		float FloatValue;
		unsigned char Byte[4];
	};
	union FloatBigEndian
	{
		unsigned char Byte[4];//Big Endian 
	};  
	union UShortBigEndian
	{
		unsigned char Byte[2];//Big Endian 
	};  
	union UShortAsByte
	{
		unsigned short ShortValue;
		unsigned char Byte[2];
	};

  union FloatAsInteger
  {
    float     Real;
    CATULONG32 Integer;
  };

  union ULONG32AsByte
  {
    CATULONG32 ulong32;
    unsigned char Byte[4];
  };

	Stat * _Stat;
	Debug * _Debug;
  CATMathStreamBits  _BitsStream;
	CATMathStreamBits::FlowType _FlowType;

	//void InitStat();
	//void SetDebugMode(int iNbFloat);
	//void InitDebug(int iNbFloat);
	//CATBoolean SkipForDebug();
	//void PrintStat();
	//void CountFloat(int iStorageSize, CATBoolean iFinal, unsigned int iDebugType);
	//void IncrementCounterDebug();
	//void RegisterFloatDebug(float iFloat, float iFloatReference, float iThreshold, CATBoolean IsWithReference);

	//FloatBigEndian GetFloatAsBigEndian(float iFloatValue);
	//float GetFloat(FloatBigEndian iFBE);
	//CATFloatCompactor::UShortBigEndian GetBigEndian(unsigned short iShort);
	//unsigned short GetShort(UShortBigEndian iSBE);

 // unsigned char GetExponent(float iFloatValue);
 // unsigned char GetExponent(FloatBigEndian iFBE);
 // void SetExponent(unsigned char iExponent, FloatBigEndian & ioFBE);


	//

	//void WriteFloatInternal(float iFloat, unsigned int iDebugType);

	////void WriteFloatStandard(FloatBigEndian iDBE, unsigned int iDebugType);
	//
	//void Dump(unsigned char iByte);
	//void DumpAsChar(float iFloat);
	//void Check();
	//void RegisterFailure(float iOriginalfloat, float iReference, CATBoolean iIsWithReference, float iRecoveredFloat);

  INLINE void GetLeadingZerosCount(const ULONG32AsByte& iNumber, unsigned short& oCount);
	INLINE void GetLeadingZerosCount2(const CATULONG32& iNumber, unsigned short& oCount);
  INLINE void ConvertToInteger(float iFloat, FloatAsInteger& oFloatAsInteger);


	CATFloatCompactor();
	CATFloatCompactor(const CATFloatCompactor &);
	void operator = (const CATFloatCompactor &);
};

INLINE void CATFloatCompactor::ConvertToInteger(float iFloat, FloatAsInteger& oFloatAsInteger)
{
  oFloatAsInteger.Real = iFloat;
}

INLINE void CATFloatCompactor::GetLeadingZerosCount(const ULONG32AsByte& iNumber, unsigned short& oCount)
{

ULONG32AsByte Num;
Num.ulong32 = iNumber.ulong32;

#if ! defined (_ENDIAN_LITTLE)

  unsigned char TempoByte;
  TempoByte = Num.Byte[3];
  Num.Byte[3] = Num.Byte[0];
  Num.Byte[0] = TempoByte;
  TempoByte = Num.Byte[2];
  Num.Byte[2] = Num.Byte[1];
  Num.Byte[1] = TempoByte;

#endif

  int idx = 3;
  for(idx = 3; idx >= 0; idx--)
  { 
   oCount += 8;     
   if((Num.Byte[idx] | 0x00) != 0)
     break;
  } 
  if(idx >= 0)
  {
    unsigned char tmp = Num.Byte[idx];
    do
    {
      oCount--;
      tmp = tmp >> 1;
    }
    while(tmp != 0);
   
  }
}

INLINE void CATFloatCompactor::GetLeadingZerosCount2(const CATULONG32& iNumber, unsigned short& oCount)
{

	ULONG32AsByte Num;
	Num.ulong32 = iNumber;

#if ! defined (_ENDIAN_LITTLE)

	unsigned char TempoByte;
	TempoByte = Num.Byte[3];
	Num.Byte[3] = Num.Byte[0];
	Num.Byte[0] = TempoByte;
	TempoByte = Num.Byte[2];
	Num.Byte[2] = Num.Byte[1];
	Num.Byte[1] = TempoByte;

#endif

	int idx = 3;
	for(idx = 3; idx >= 0; idx--)
	{ 
		oCount += 8;     
		if((Num.Byte[idx] | 0x00) != 0)
			break;
	} 
	if(idx >= 0)
	{
		unsigned char tmp = Num.Byte[idx];
		do
		{
			oCount--;
			tmp = tmp >> 1;
		}
		while(tmp != 0);

	}
}

#endif
