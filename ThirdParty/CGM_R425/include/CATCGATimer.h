#ifndef CATCGATimer_H
#define CATCGATimer_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//  small tools legacy from tessellation utilities
//    offered at lower level for architecture purpose
//  may be enhance package is available from System harware/operating system abstraction
//     so do not forget to contact single system image or PCS actors
//-------------------------------------------------------------------------------------------------
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATTimer : timer that allow to determine the elapsed and CPU time
//
// DESCRIPTION : use the method Start and Stop ( that can be used many time),
// and Reset to set the timer to 0. Times are given in miliseconds.
// 
// Main Methods :
//  
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
//
// History
//
// Jul. 97   Jose CHILLAN (jch)    Creation            
//
//=============================================================================
#include "CATMathematics.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATMathematics.h"
#include "CATMathInline.h"
#include "CATCGAMeasureDefine.h" 
#include "CATCGAMeasureValue.h" 


//---------------------------------------------------------------------------------------------
//  COULD NOT CLEAN, DUE TO
//     CATCompositesLightModel\CATCmoProdSimulation.m\src\CATCoProdSimResultOperator.cpp
//---------------------------------------------------------------------------------------------

#ifndef CATCGATimer_Structure_H
#define CATCGATimer_Structure_H

#ifdef _WINDOWS_SOURCE
#include <time.h>

struct CATCGATimerTIMER
{
  DWORD    startTime;
  FILETIME startKernel;
  FILETIME startUser;
};

#else

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

struct CATCGATimerTIMER
{
  struct timeval startTime;
  clock_t startCpuTicks;
};

#endif

#endif


 
class CATCGAreport_Measures;
class CATCGAreport_PCS;
class CATCGAMeasure;

class ExportedByCATMathematics CATCGATimer
{
public:

//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
// Default constructor
  CATCGATimer(CATBoolean iDedicated = FALSE);
  CATCGATimer(CATBoolean iDedicated , CATBoolean iStart );

  CATCGATimer (const CATCGATimer &);          
  CATCGATimer& operator=(const CATCGATimer&);  
  ~CATCGATimer();          

//=============================================================================
// dedicated CATechTimer 
//=============================================================================
 
// Getting the elapsed time (in miliseconds)
  double _GetElapsed();

// Getting the CPU time
  // CATLONG32 GetCPU();
  double _GetCPU();

  // Getting WorkingSet in bytes
  double _GetWorkingSetDelta();

  // Getting after stop result
  //    oCpu (ms)
  //    oElapsed (ms)
  //    oWorkingSetDelta (bytes)
  void _GetStopped(double & oCpu, double  & oElapsed, double & oWorkingSetDelta);
 

  // Setting stop result
  void _SetStopped(const double iCpu, const double  iElapsed, const double iWorkingSetDelta);


//=============================================================================
// START AND STOP METHODS
//=============================================================================
// Starting the timer
  void _Start();

// Stoping the timer
  void _Stop();

// Resets the elapsed and CPU time
  void _Reset();

  // Getting after stop result
  //    oCpu (ms)
  //    oElapsed (ms)
  //    oWorkingSetDelta (bytes)
  //    oTicks (ticks)
  void _GetStopped(double & oCpu, double  & oElapsed, double & oWorkingSetDelta, CATULONG64 & oTicks);

  void _GetStopped(CATCGAreport_Measures & oMeasures);


  //=============================================================================
  // For persistency
  //=============================================================================

  // Setting stop result
  CATBoolean _IsStopped();

  // Setting stop result
  void _SetStopped(const double iCpu, const double  iElapsed, const double iWorkingSetDelta, const CATULONG64 & iTicks);

//=============================================================================
// INTERNAL DATAS 
//=============================================================================
protected: 
	CATCGAMeasureValue   _Values; // Start if Working, Differential if Stopped 

  CATBoolean           _CATCGAMeasure;
  CATBoolean           _Working;

  friend class CATCGAreport_Measures;
  friend class CATCGAreport_PCS;
  friend class CATCGAMeasure;

};

 

#endif
