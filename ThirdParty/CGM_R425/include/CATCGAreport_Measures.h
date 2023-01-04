#ifndef CATCGAreport_Measures_H
#define CATCGAreport_Measures_H

#include "CATDataType.h"
#include "CATMathematics.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATCGMNewArray.h"

#include "CATCGAMeasureContext.h"
#include "CATCGAMeasureDefine.h" 
#include "CATCGAMeasureValue.h" 

#define report_PCS_Cpu                            0
#define report_PCS_Elapsed                        1
#define report_PCS_WorkingSetDelta                2
#define report_PCS_DiskBytes                      3
#define report_PCS_Ticks                          4
#define report_PCS_Errors                         5
#define report_PCS_DLLsDelta                      6
#define report_PCS_NbMeasures                     7
 


class CATCGMItfName;

class ExportedByCATMathematics CATCGAreport_Measures
{
public :
  CATCGMNewClassArrayDeclare;  

  INLINE CATCGAreport_Measures(const CATCGAMeasureContext &iCopy)  
    : _NbMeasures(0) , _Context(iCopy)  , _Overall() , _Inclusive()
  {}

  INLINE CATCGAreport_Measures() 
    : _NbMeasures(0) , _Context()  , _Overall() , _Inclusive()
  {}

  // Cf CATCGAMeasure
  INLINE CATCGAreport_Measures(const char * iOperation, const char * iOperationDomain , CATCGMItfName    *  iWorkingFeature)  
    : _NbMeasures(0) , _Context(iOperation,iOperationDomain, iWorkingFeature)  , _Overall() , _Inclusive()
  {}
 
 
  INLINE ~CATCGAreport_Measures()
  {}

  INLINE void Reset() 
  { 
    _Overall.Reset();
    _Inclusive.Reset();
    _NbMeasures = 0;
  }

  INLINE void Substract(const CATCGAreport_Measures &iCumulatedInclusive)  
  {
		_Overall.Substract(iCumulatedInclusive._Overall);
  }


  INLINE void Accumulate(const CATCGAreport_Measures &iCumulatedInclusive)  
  {
		_Overall.Accumulate(iCumulatedInclusive._Overall);
		_Inclusive.Accumulate(iCumulatedInclusive._Inclusive);
    ++_NbMeasures;
  }

  // Measures
	CATCGAMeasureValue   _Overall;
	CATCGAMeasureValue   _Inclusive;

  // Context
	CATULONG64             _NbMeasures;
  CATCGAMeasureContext   _Context;

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGAreport_Measures(const CATCGAreport_Measures &iCopy);
  CATCGAreport_Measures& operator=(const CATCGAreport_Measures &iCopy);
};
 

 
#endif
