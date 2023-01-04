/* -*-c++-*- */
#ifndef CATCGMParallelComputing_h
#define CATCGMParallelComputing_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2009
//-----------------------------------------------------------------------------
//  Static class to manage activation of parallel computing methods in CGM code
//-----------------------------------------------------------------------------
#include "YN000MAT.h"
#include "CATBoolean.h"

class ExportedByYN000MAT CATCGMParallelComputing
{
  public:
	static void SetEnabled(CATBoolean iEnabled); // does not supersede environment variable
	static CATBoolean GetEnabled();// Forced to TRUE if (set CATCGMParallelComputing=1) and FALSE if (set CATCGMParallelComputing=0)
  static void ForceEnabled(CATBoolean iEnabled); // supersedes environment variable
  
  //------------------------------------------------------------------------------------
  // Enable the debugging aid MonoProcMode
  //------------------------------------------------------------------------------------
  static void EnableMonoProcMode();

  //------------------------------------------------------------------------------------
  // Determine the state of MonoProcMode,  
  //  with consideration of the CATCGMParallelComputing_MonoProc environment variable.
  //------------------------------------------------------------------------------------
  static CATBoolean IsMonoProcModeActive();
	
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
  //    future executions until the next use of SetNbAvailableProcessors.
  //
  // 3) If the value iNbAvailableProcessors is 1 the method disables the parallel
  //     computing mode, but if it's stricly greater than 1, it activates the parallel
  //     computing mode
  //
  // 4) iNbAvailableProcessors must be greater than or equal to 1 (otherwise the
  //    method assumes that only one processor is available)
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

  //------------------------------------------------------------------------------------
  // Check for number of simulated processors
  //------------------------------------------------------------------------------------
  static unsigned int ReadNumberOfSimulatedProcessors();

  //------------------------------------------------------------------------------------
  // Lock/unlock parallel computing (used to inhibit nested parallelism)
  //------------------------------------------------------------------------------------
  static void Lock();
  static void Unlock();
  static CATBoolean IsLocked();

  static CATBoolean   InitStaticData();

  //------------------------------------------------------------------------------------
  // Returns the total number of logical cores on the machine
  //------------------------------------------------------------------------------------
  static unsigned int GetNbLogicalCores();

  //------------------------------------------------------------------------------------
  // Returns the total number of physical cores(CPU) on the machine 
  // (will not take into account the hyperthreading)
  //------------------------------------------------------------------------------------
  static unsigned int GetNbPhysicalCores();

  private:
	static CATBoolean   _Enabled;
	static CATBoolean   _EnvEnabled;
	static CATBoolean   _EnvDisabled;
  static CATBoolean   _EnvVariableRead;
  static CATBoolean   _MonoProcMode;
  static CATBoolean   _MonoProcModeVariableRead;
  static unsigned int _NbAllProcessors;
  static unsigned int _NbAvailableProcessors;
  static CATBoolean   _SingleCoreSimulActiveFlagRead;
  static CATBoolean   _SingleCoreSimulActive;
  static CATBoolean   _NumberOfSimulatedProcessorsFlagRead;
  static unsigned int _NumberOfSimulatedProcessors;
  static unsigned int _NbLocks;

  static CATBoolean   _InitDone;
};
#endif
