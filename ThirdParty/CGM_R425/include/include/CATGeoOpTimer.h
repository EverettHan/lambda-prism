// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
//
// CATGeoOpTimer :
// Class used as a timer to measure time spend and count number of calls
// in various places of the code
// (internal use)
//
//==========================================================================

#ifndef CATGeoOpTimer_h
#define CATGeoOpTimer_h

#include "CATGMModelInterfaces.h"

#include "CATBoolean.h"
#include "CATString.h"
#include "CATLib.h"
#include "CATDataType.h"

class CATCGMOutput;

class ExportedByCATGMModelInterfaces CATGeoOpTimer {
public:
	CATGeoOpTimer(const CATString * iName);
  CATGeoOpTimer(const char * iName);
	~CATGeoOpTimer();
  // Reset the total timing of all the measure to 0
	void ResetTimer();
  // Start a new measure
	void StartTimer();
  // Stop the current measure
	void StopTimer();
  // Write the name and value of the timer
	void WriteTimer(CATCGMOutput& ioStream);
  // Return 1 if the timer has been added to AllTimers
  CATBoolean IsUsed();
  // 
  void SetUsed(CATBoolean iIsUsed=1);

  // Read timer values
  void ReadTimer(CATULONG32  & TotalCPU, CATULONG32  & TotalElapsed, 
                 CATULONG32  & LocalCPU, CATULONG32  & LocalElapsed,
                 CATLONG32 & Counter);
  
  CATULONG32 GetTime_TotalCPU() const;

private:

  CATTimerId _SolveTime;
	CATString  _Name;
  CATLONG32 _Counter;
	CATULONG32  _TotalCPU, _TotalElapsed;
  CATULONG32  _StartCPU, _StartElapsed;
  CATULONG32  _LocalCPU, _LocalElapsed;

  CATBoolean _Used;
};

#endif
