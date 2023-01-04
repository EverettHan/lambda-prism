#ifndef CATSysElapseTime_H
#define  CATSysElapseTime_H

#include "JS0MT.h"

#ifdef _WINDOWS_SOURCE
#include  <windows.h>
#define CATSysElaTimerUnit_t LARGE_INTEGER

#else

#ifdef _MACOSX_SOURCE
#include <mach/clock.h>
#include <mach/mach.h>
#define CATSysElaTimerUnit_t mach_timespec_t

#else

#include <time.h>
#include <sys/time.h>
#define CATSysElaTimerUnit_t struct timespec

#endif //_MACOSX_SOURCE
#endif //_WINDOWS_SOURCE

#include "CATDataType.h"

class ExportedByJS0MT  CATSysElapseTime
{
#ifdef _WINDOWS_SOURCE
	static CATSysElaTimerUnit_t S_Frequency;
	static int      S_Init;
#else
#ifdef _MACOSX_SOURCE // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t m_cclock;
#endif
#endif
	CATSysElaTimerUnit_t		m_StartTime;

public :
	/***
	 constructor
	 initialises the start time (calls reset)
     ***/
	CATSysElapseTime();

	/***
	 copy  constructor
	 ***/
	CATSysElapseTime(CATSysElapseTime&);

	/***
	 destructor
		to close port on MacOS
     ***/
	~CATSysElapseTime();
	
	/***
	 Reset the start time for the object
	 GetElapse gives the number of microseconds since the last call to Reset 

	 RETURN VALUES
	 0  : OK
	 -1 : fine timers not supported on this host machine
	 -2 : fine timers not supported on this operating systeme
	 ***/
	int Reset();

	/***
	 GetElapse gives the number of microseconds since the last call to Reset with type double

	 ARGUMENTS
	 oNbMicroSeconds : output / double : number of microseconds since the last call to Reset
	 RETURN VALUES
	 0  : OK
	 -1 : fine timers not supported on this host machine
	 -2 : fine timers not supported on this operating systeme
	 ***/
	int GetElapse(double &oNbMicroSeconds);

	/***
	 GetElapse gives the number of nanoseconds since the last call to Reset with type double
	 
	 ARGUMENTS
	 oNbMicroSeconds : output / double : number of nanoseconds since the last call to Reset
	 RETURN VALUES
	 0  : OK
	 -1 : fine timers not supported on this host machine
	 -2 : fine timers not supported on this operating systeme
	 ***/
	int GetElapseNano(double &oNbNanoSeconds);
	
	/***
	 GetElapse gives the number of microseconds since the last call to Reset with type CATULONG64

	 ARGUMENTS
	 oNbMicroSeconds : output / CATULONG64 : number of microseconds since the last call to Reset   

	 RETURN VALUES
	 0  : OK
	 -1 : fine timers not supported on this host machine
	 -2 : fine timers not supported on this operating systeme
	 ***/
	int GetElapse(CATULONG64 &oNbMicroSeconds);

	/***
	 GetElapseNano gives the number of nanoseconds since the last call to Reset with type CATULONG64
	 
	 ARGUMENTS
	 oNbMicroSeconds : output / CATULONG64 : number of nanoseconds since the last call to Reset   
	 
	 RETURN VALUES
	 0  : OK
	 -1 : fine timers not supported on this host machine
	 -2 : fine timers not supported on this operating systeme
	 ***/
	int GetElapseNano(CATULONG64 &oNbNanoSeconds);
};
#endif
