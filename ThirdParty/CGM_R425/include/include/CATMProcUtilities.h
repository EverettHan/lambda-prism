

// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// Jun. 09  Creation                                                    ASE
//=============================================================================



#ifndef CATMProcUtilities_H
#define CATMProcUtilities_H

#include "CATBoolean.h"
#include "MPROCTools.h"


//**
//for compilation on unix based platforms

#ifndef NULL
#define NULL 0
#endif

#include "IUnknown.h"
#ifndef _WINDOWS_SOURCE
#include "string.h"
#include "stdio.h"
#endif

// Debug output
// #define DEBUG_MPROC
#ifdef DEBUG_MPROC
ExportedByMPROCTools void MProcAssert( int iCond, const char* iMsg, const char* iFile, int iLine);
# define MPROCASSERT(cond) MProcAssert( !!(cond), #cond, __FILE__, __LINE__ )
#else
# define MPROCASSERT(cond)
#endif

//**

//-----------------------------------------------------------------------------------
//Class managing Multiprocess utilities.
//-----------------------------------------------------------------------------------
/*
//-----------------------------------------------------------------------------------
Typical Usage Scenarios
//-----------------------------------------------------------------------------------

1. For a process flow through steps A, D to Time a block between A & D , use ResetMProcTime at A and ReadMProcTime at D
2. For a process flow through steps A, B, C, D to time blocks AD and BC, use ResetMProcTime at A, B and ReadMProcTime at C, D
The time dumped at C coressponds to BC block, and time dumped at D coressponds to AD block ( inclusive of BC )
3. For a process flow through steps A,B1,C1,B2,C2,D to time blocks B1C1 & B2C2 use ResetMProcTime at B1, B2 and ReadMProcTime at C1, C2
To get total time B1C1 + B2C2, use ResetTotalMProcTime at A and ReadTotalMProcTime at D
Time dumped at D will not contain AB1 & C2D times, but only B1C1+B2C2
4. For a process flow through steps A, B, C, D, with multiple passages through BC, to find cumulative time spent in BC use
InitMProcTimeBlock(id) at A where id is integer which identifies the block BC
BeginMProcTimeBlock(id) at B
EndMProcTimeBlock(id) at C
ReadMProcTimeBlock(id) at D 
The time dumped at D will be cumulative time consumed in BC, across multiple passes through it
//-----------------------------------------------------------------------------------
Notes: 
//-----------------------------------------------------------------------------------
1. To enable dump of times in traces, one must activate dump using set CGMTest_MProcPerfoActive=1
2. Can be used in single process mode as well.
3. Time dumped are elapsed times unless specifically mentioned
*/
//-----------------------------------------------------------------------------------
class ExportedByMPROCTools CATMProcUtilities
{
  public:
  // Stream optimization active (e.g. already sent geometries are not re-sent)
  static CATBoolean IsStreamOptimizationActive();

  // Number of processes set b environment variable
  static unsigned int ReadNumberOfProcesses();

  // Performance statistics
  static CATBoolean IsPerfoTestActive();
  static CATBoolean IsPerfoDumpActive();
  static void       ResetMProcTime();
  // Read time elapsed since last ResetMProcTime
  static double     ReadMProcTime(unsigned int *oNbTasksOfCurrentTransaction = 0);
  static void       ResetTotalMProcTime();
  // Read total time elapsed in all MProc activity since last ResetTotalMProcTime
  static double     ReadTotalMProcTime(unsigned int *oNbMProcTransactions = 0,
                                       unsigned int *oTotalNbTasks        = 0);

  static void       InitMProcTimeBlock(int id);
  static void       BeginMProcTimeBlock(int id);
  static void       EndMProcTimeBlock(int id);
  static double     ReadMProcTimeBlock(int id);

  static void       IncrementNbTasksOfCurrentTransaction();

  // MProc execution detection: at least one task has been sent from master to slave(s)
  static CATBoolean IsMProcExecutionDetectionActive();
  static void       SetMProcExecutionDetected();

  //------------------------------------------------------------------------------------
  // Get the total number of processors (i.e. maximum physical capacity)
  //------------------------------------------------------------------------------------
  static unsigned int GetNbAllProcessors();

  //------------------------------------------------------------------------------------
  // Set the number of AVAILABLE processors (regardless of any OPTIMAL number(s) of
  // processes to be used, those can be specified otherwise - see below)
  //
  // Please note:
  //
  // 1) This is used to keep part of the CPU resources free for other usage (at a code
  //    level, that is sufficiently high, so that resource sharing decisions can/must
  //    be made)
  //
  // 2) This setting remains valid until another one is made, i.e. it will affect ALL
  //    future MProc executions until the next use of SetNbAvailableProcessors.
  //
  // 3) The methods SetMinNbProcessesToUse and SetMaxNbProcessesToUse that are defined
  //    in the CATMProcAppliManager class have neither the same meaning nor the same
  //    scope.
  //    They define the OPTIMAL number(s) of processes to use (see CATMProcAppliManager.h
  //    for more details).
  //
  // 4) If, for instance, only 3 processes are AVAILABLE, and even if the OPTIMAL number
  //    of processes to use is 7, only 3 processes will be used.
  //    Conversely, if, for example, 8 processes are AVAILABLE but the OPTIMAL number
  //    is 5, only 5 processes will be used.
  //------------------------------------------------------------------------------------
  static void SetNbAvailableProcessors(unsigned int iNbAvailableProcessors);

  //------------------------------------------------------------------------------------
  // Get the number of available processors (per default this is equal to the
  // total number of processors, but can be less if SetNbAvailableProcessors
  // has been used)
  //------------------------------------------------------------------------------------
  static unsigned int GetNbAvailableProcessors();

  //------------------------------------------------------------------------------------
  // Check if single core simulation is activated
  // (i.e. the total number of processors is reduced to 1)
  //------------------------------------------------------------------------------------
  static CATBoolean IsSingleCoreSimulActive();

  static CATBoolean   IsGeoStreamOptimEvalActive();

  static CATBoolean   InitStaticData();

private :
  static CATBoolean   _StreamOptimizationActiveFlagRead;
  static CATBoolean   _StreamOptimizationActive;
  static CATBoolean   _NumberOfProcessesFlagRead;
  static unsigned int _NumberOfProcesses;
  static CATBoolean   _PerfoTestActiveFlagRead;
  static CATBoolean   _PerfoTestActive;
  static CATBoolean   _PerfoDumpActiveFlagRead;
  static CATBoolean   _PerfoDumpActive;
  static double       _TotalMProcTime;
  //static CATTimerId  *_TimerId;
  static CATBoolean   _MProcExecutionDetectionActiveFlagRead;
  static CATBoolean   _MProcExecutionDetectionActive;
  static CATBoolean   _MProcExecutionDetected;
  static CATBoolean   _GeoStreamOptimEvalActiveFlagRead;
  static CATBoolean   _GeoStreamOptimEvalActive;

  static unsigned int _NbMProcTransactions;
  static unsigned int _NbTasksOfCurrentTransaction;
  static unsigned int _TotalNbTasks;

  static CATBoolean   _InitDone;

  CATMProcUtilities();
};
#endif

