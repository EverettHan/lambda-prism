#ifndef CATCGAMeasureClearance_H
#define CATCGAMeasureClearance_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    For general solution concerning GM diagnostic inside an applicative product
*       with some major PCS criteria as memory (working set , virtual size)
* 
*    This Multiple purpose analysis can be extended,
*      this support is tightly linked with some reccurent CoreDump incident
*         misunderstood concerning  origin of memory consumption
*         badly managed when request of allocations begin to fail
* 
*    Meaningfull report avec provided with activation of following environement variable
*         CATCGAMeasure=Home=E:\tmp,PCS   (Cache option should be omitted)
*/
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATCGMKernel.h"
#include "CATCGAMeasureDefine.h" 
#include "CATCGATimer.h" 
#include "CATCGAMeasureValue.h" 

// Stack Node
class ExportedByCATCGMKernel CATCGAMeasureClearance
{
public :

  CATUnicodeString       _Framework;  
  CATUnicodeString       _TestCases;  

  CATUnicodeString       _DataURL;  
  int                    _NumberOfURL;  
  CATULONG64             _DataURLMaxSize;  
  CATULONG64             _DataURLSumSize;  

  CATULONG32             _GMBSF;
  CATULONG64             _NbErrors;

	CATCGAMeasureValue     _Values; 
 
  static CATLONG64             _CurWorkingSetPEAK;
  static CATLONG64             _HeapPEAK[CATCGAMeasureHeap_NbCriteria];
	static CATCGATimer           _SessionTimer;


  INLINE CATCGAMeasureClearance() 
  { 
    _NumberOfURL = 0;
	  _DataURLMaxSize = 0;
	  _DataURLSumSize = 0;

	  _GMBSF = 0;
		_NbErrors = 0;

	}

  INLINE ~CATCGAMeasureClearance()
  { 
    _NumberOfURL = 0;
	  _DataURLMaxSize = 0;
	  _DataURLSumSize = 0;

	  _GMBSF = 0;
		_NbErrors = 0;
  }

  INLINE void Reset()
  { 
    _NumberOfURL = 0;
	  _DataURLMaxSize = 0;
		_DataURLSumSize = 0;

		_GMBSF = 0;
		_NbErrors = 0;
		_Values.Reset();

  	_Framework = CATUnicodeString();
  	_TestCases = CATUnicodeString();
  	_DataURL = CATUnicodeString();
  }

  INLINE CATCGAMeasureClearance(const CATCGAMeasureClearance &iCopy);
  INLINE CATCGAMeasureClearance& operator=(const CATCGAMeasureClearance &iCopy);
 
};
 
/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATCGAMeasureClearance::CATCGAMeasureClearance(const CATCGAMeasureClearance &iOther) 
{
  _NumberOfURL = iOther._NumberOfURL;
  _DataURLMaxSize = iOther._DataURLMaxSize;
  _DataURLSumSize = iOther._DataURLSumSize;

  _GMBSF = iOther._GMBSF;
	_NbErrors = iOther._NbErrors;
	_Values = iOther._Values;

	_Framework = iOther._Framework;
	_TestCases = iOther._TestCases;
	_DataURL = iOther._DataURL;
}
 
/** --------------------------------------------------------------------------------
* Constructor by Copie
* -------------------------------------------------------------------------------- **/
INLINE CATCGAMeasureClearance& CATCGAMeasureClearance::operator=(const CATCGAMeasureClearance &iOther)
{
  if (&iOther == this)  return *this;

  _NumberOfURL = iOther._NumberOfURL;
  _DataURLMaxSize = iOther._DataURLMaxSize;
  _DataURLSumSize = iOther._DataURLSumSize;

  _GMBSF = iOther._GMBSF;
	_NbErrors = iOther._NbErrors;
	_Values = iOther._Values;

  _Framework = iOther._Framework;
  _TestCases = iOther._TestCases;
  _DataURL = iOther._DataURL;

  return *this;
}
 

#endif
