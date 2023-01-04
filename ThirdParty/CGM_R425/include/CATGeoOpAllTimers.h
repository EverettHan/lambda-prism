// COPYRIGHT DASSAULT SYSTEMES 2000
//==========================================================================
//
// CATGeoOpAllTimers :
// Class used to store all the timers in order to handle them at the same time
// (internal use)
//
//==========================================================================

#ifndef CATGeoOpAllTimers_h
#define CATGeoOpAllTimers_h

#include "Y3DYNOPE.h"
#include "CATDataType.h"
#include "CATCGMVirtual.h"

class CATGeoOpTimer;
class CATCGMOutput;

class ExportedByY3DYNOPE CATGeoOpAllTimers  : public CATCGMVirtual
{
public:
  CATGeoOpAllTimers();
  ~CATGeoOpAllTimers();

	void ResetAllTimers();
	void WriteAllTimers(CATCGMOutput& ioStream);

	void AddTimer(CATGeoOpTimer * iNewTimer);

private:
	CATLONG32 _NbTimers, _NbAllocTimers;
	CATGeoOpTimer ** _Timers;
};

#endif
