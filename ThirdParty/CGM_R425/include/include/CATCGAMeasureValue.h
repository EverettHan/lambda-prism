#ifndef CATCGAMeasureValue_H
#define CATCGAMeasureValue_H

#include "CATDataType.h"
#include "CATMathematics.h"
#include "CATMathInline.h"
#include "CATCGMNewArray.h"
#include "CATCGAMeasureDefine.h" 
#include "CATBoolean.h" 
  
// Gestion des CATCGAMeasureValue
class ExportedByCATMathematics CATCGAMeasureValue
{
public :

  INLINE CATCGAMeasureValue(double iCpu, double iElapsed, CATULONG64 iTicks, CATULONG64 iDiskBytes, CATULONG64 iNbErrors, CATULONG64 iDLLs )  
    : _Cpu(iCpu), _Elapsed(iElapsed), _Ticks(iTicks), _DiskBytes(iDiskBytes), _NbErrors(iNbErrors), _DLLs(iDLLs), _WorkingSet(0)
  {
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap] =  _HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] =  _HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]  = 0;
    _NbObjects[0] = _NbObjects[1] = 0;
  }

  INLINE CATCGAMeasureValue()  
    : _Cpu(0.0), _Elapsed(0.0),  _Ticks(0),  _DiskBytes(0), _NbErrors(0), _DLLs(0), _WorkingSet(0) 
  {
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap] =  _HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] =  _HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]  = 0;
    _NbObjects[0] = _NbObjects[1] = 0;
	}

	INLINE CATCGAMeasureValue(const CATCGAMeasureValue &iCopy)  
		: _Cpu(iCopy._Cpu), _Elapsed(iCopy._Elapsed), _Ticks(iCopy._Ticks), _DiskBytes(iCopy._DiskBytes), _NbErrors(iCopy._NbErrors), _DLLs(iCopy._DLLs), _WorkingSet(iCopy._WorkingSet)
	{
		_HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]       = iCopy._HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap];
		_HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] = iCopy._HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes];
		_HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]     = iCopy._HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks];
		_NbObjects[0] = iCopy._NbObjects[0];
		_NbObjects[1] = iCopy._NbObjects[1];
	}


	INLINE CATCGAMeasureValue& operator=(const CATCGAMeasureValue &iOther)
	{
		_Cpu        =  iOther._Cpu;
		_Elapsed    =  iOther._Elapsed;
		_Ticks      =  iOther._Ticks;
		_DiskBytes  =  iOther._DiskBytes;
		_NbErrors   =  iOther._NbErrors;
		_DLLs       =  iOther._DLLs;
		_WorkingSet =  iOther._WorkingSet;
		_HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]       =  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]; 
		_HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] =  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes]; 
		_HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]     =  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]; 
		_NbObjects[0] = iOther._NbObjects[0];
		_NbObjects[1] = iOther._NbObjects[1];
		return *this;
	}

	INLINE void Reset() 
	{
    _Cpu=0.0;  _Elapsed=0.0;  _WorkingSet=0;  _DiskBytes=0;  _Ticks=0; _NbErrors=0; _DLLs=0;   
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap] =  _HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] =  _HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]  = 0;
    _NbObjects[0] = _NbObjects[1] = 0;
	}

	INLINE void Substract(const CATCGAMeasureValue &iOther)  
  {
    _Cpu        = ( iOther._Cpu       > _Cpu       ) ? 0.0 : (_Cpu       - iOther._Cpu); 
    _Elapsed    = ( iOther._Elapsed   > _Elapsed   ) ? 0.0 : (_Elapsed   - iOther._Elapsed); 
    _Ticks      = ( iOther._Ticks     > _Ticks     ) ?   0 : (_Ticks     - iOther._Ticks); 
    _DLLs       = ( iOther._DLLs      > _DLLs      ) ?   0 : (_DLLs - iOther._DLLs); 
    _WorkingSet                                       -=  iOther._WorkingSet;
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]       -=  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]; 
    _HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] -=  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes]; 
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]     -=  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]; 
		// Inappropriate By default, To Be customized   unchanged _NbObjects[0] -= iOther._NbObjects[0];  
		// Inappropriate By default, To Be customized   unchanged _NbObjects[1] -= iOther._NbObjects[1];  
    //   concerning _DiskBytes _NbErrors should be identical 
    _DiskBytes  = ( iOther._DiskBytes > _DiskBytes ) ?   0 : (_DiskBytes - iOther._DiskBytes); 
    _NbErrors   = ( iOther._NbErrors  > _NbErrors  ) ?   0 : (_NbErrors  - iOther._NbErrors); 
  }
 

	INLINE void Accumulate(const CATCGAMeasureValue &iOther)  
  {
    _Cpu        += iOther._Cpu; 
    _Elapsed    += iOther._Elapsed; 
    _Ticks      += iOther._Ticks; 
    _DiskBytes  += iOther._DiskBytes; 
    _NbErrors   += iOther._NbErrors; 
    _DLLs       += iOther._DLLs; 
    _WorkingSet                                       +=  iOther._WorkingSet;
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]       +=  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_NbHeap]; 
    _HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes] +=  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_VirtualBytes]; 
    _HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]     +=  iOther._HeapsCriteria[CATCGAMeasureHeapIdx_NbBlocks]; 
		_NbObjects[0] += iOther._NbObjects[0];
		_NbObjects[1] += iOther._NbObjects[1];
  }

  void GetMeasure(CATBoolean iCATCGAMeasure = TRUE);

  double               _Cpu;
  double               _Elapsed;
  CATULONG64           _Ticks;

	CATLONG64            _WorkingSet;
	CATLONG64            _HeapsCriteria[CATCGAMeasureHeap_NbCriteria];
  CATULONG64           _DLLs;

  CATULONG64           _DiskBytes;
  CATULONG64           _NbErrors;
  CATLONG64            _NbObjects[2];

};
 
 

 
#endif
