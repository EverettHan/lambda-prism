/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// Jul 09   Creation                                    AAD  
// Sep 10   Optimization WriteDoubleWithRefC            PR
//=============================================================================
#ifndef CATDoubleCompactor_H
#define CATDoubleCompactor_H

#include "CATMathStreamBits.h"
#include "CATFixedPoint64.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "ExportedByCATMathStream.h"
#include "CATMathInline.h"

//#ifdef NurbsCompactOptimPR
#include "CATArithTypes.h"
//#endif

class CATMathStreamImpl;

class ExportedByCATMathStream CATDoubleCompactor
{
public: 

CATDoubleCompactor(CATMathStreamImpl * ioStream, CATMathStreamBits::FlowType iFlowType);
~CATDoubleCompactor();


void EndWrite();
void WriteDoubleStandard(double iDouble, unsigned int iDebugType);
double ReadDoubleStandard();
//void SetCheckMode(int iNbDouble);
//void SetNbTypeDebug(unsigned int iNbType);
//void WriteDoubleWithRef_Full(double* iDouble, CATFixedPoint64::Number* iReference, unsigned int iNbCells,  double iThreshold , unsigned int iDebugType);
void WriteDoubleWithRef(double* iDouble, CATFixedPoint64::Number* iReference, unsigned int iNbCells,  int ThresholdExponent, unsigned int iDebugType);

//#ifdef NurbsCompactOptimPR
void WriteDoubleWithRefC
  (double* iDouble, CATFixedPoint64::Number* iReference,
   int iNbCells, int ThresholdExponent, int DeltaI);
//#endif

//void ReadDoubleWithRef_Full(CATFixedPoint64::Number* iReference,  unsigned int iNbCells, double iThreshold , double* oReadDouble);
void ReadDoubleWithRef(CATFixedPoint64::Number* iReference,  unsigned int iNbCells, int ThresholdExponent, double* oReadDouble);

private:
	struct Stat
	{
		unsigned int NbType;
		int NbDoubleForObject;
		int * NbDoubleForObjectByType;
		int StorageSizeForObject;
		int * StorageSizeForObjectByType;
		int	Trace;
		int NbFailure;
	};

	struct Debug
	{
		int NbDouble;
		double * Double;
		CATBoolean * IsWithReference;
		double * DoubleReference;
    int * Threshold;
		char * Char;
		int DoubleIndex;
		int CharIndex;
	};

	struct Buffer
	{
		unsigned char Byte;
		short Index;//[0..8] = nb bits written or read
	};

	union DoubleAsByte
	{
		double DoubleValue;
		unsigned char Byte[8];
	};
	union DoubleBigEndian
	{
		unsigned char Byte[8];//Big Endian 
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

  union DoubleAsInteger
  {
    double     Real;
    CATULONG64 Integer;
  };

  union ULONG64AsByte
  {
    CATULONG64 ulong64;
    unsigned char Byte[8];
  };

	Stat * _Stat;
	Debug * _Debug;
  CATMathStreamBits  _BitsStream;
	CATMathStreamBits::FlowType _FlowType;

  // code for debug

	///*void InitStat();
	//void SetDebugMode(int iNbDouble);
	//void InitDebug(int iNbDouble);
	//CATBoolean SkipForDebug();
	//void PrintStat();
	//void CountDouble(int iStorageSize, CATBoolean iFinal, unsigned int iDebugType);
	//void IncrementCounterDebug();
	//void RegisterDoubleDebug(double iDouble, double iDoubleReference, int iThreshold, CATBoolean IsWithReference);
	//DoubleBigEndian GetDoubleAsBigEndian(double iDoubleValue);
	//double GetDouble(DoubleBigEndian iDBE);
	//CATDoubleCompactor::UShortBigEndian GetBigEndian(unsigned short iShort);
	//unsigned short GetShort(UShortBigEndian iSBE);
	//unsigned short GetExponent(double iDoubleValue);
	//unsigned short GetExponent(DoubleBigEndian iDBE);
	//void SetExponent(unsigned short iExponent, DoubleBigEndian & ioDBE);

	//void Dump(unsigned char iByte);
	//void DumpAsChar(double iDouble);
	//void Check();
	//void RegisterFailure(double iOriginalDouble, double iReference, CATBoolean iIsWithReference, double iRecoveredDouble);*/

  INLINE void GetLeadingZerosCount(const CATULONG64& iNumber, unsigned short& oCount);
  INLINE void ConvertToInteger(double iDouble, DoubleAsInteger& oDoubleAsInteger);


	CATDoubleCompactor();
	CATDoubleCompactor(const CATDoubleCompactor &);
	void operator = (const CATDoubleCompactor &);
};

//#ifdef NurbsCompactOptimPR
extern "C" ExportedByCATMathStream usla CATWriteDoubleWithRefA
  (Buffer64A& iBuf, double* iDouble, CATFixedPoint64::Number* iReference,
   int iNbCells, int ThresholdExponent, int DeltaI);
//#endif

INLINE void CATDoubleCompactor::ConvertToInteger(double iDouble, DoubleAsInteger& oDoubleAsInteger)
{
  oDoubleAsInteger.Real = iDouble;
}

INLINE void CATDoubleCompactor::GetLeadingZerosCount(const CATULONG64& iNumber, unsigned short& oCount)
{
  ULONG64AsByte UAB;
  UAB.ulong64 = iNumber;
  
#if ! defined (_ENDIAN_LITTLE)
  unsigned char TempoByte;
  TempoByte = UAB.Byte[7];
  UAB.Byte[7] = UAB.Byte[0];
  UAB.Byte[0] = TempoByte;
  TempoByte = UAB.Byte[6];
  UAB.Byte[6] = UAB.Byte[1];
  UAB.Byte[1] = TempoByte;
  TempoByte = UAB.Byte[5];
  UAB.Byte[5] = UAB.Byte[2];
  UAB.Byte[2] = TempoByte;
  TempoByte = UAB.Byte[4];
  UAB.Byte[4] = UAB.Byte[3];
  UAB.Byte[3] = TempoByte;
#endif

  int idx = 7;
  for(idx = 7; idx >= 0; idx--)
  {         
   if(UAB.Byte[idx]|0x00)
     break;
  } 
  oCount = 8*(8-idx);

  if(idx >= 0)
  {
    unsigned char tmp = UAB.Byte[idx];
    do
    {
      oCount--;
      tmp = tmp >> 1;
    }
    while(tmp != 0);   
  }
}

#endif
