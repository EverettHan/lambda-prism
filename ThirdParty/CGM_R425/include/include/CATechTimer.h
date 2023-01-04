#ifndef CATechTimer_H
#define CATechTimer_H
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
#include "ExportedByCATTechTools.h"
#include "CATCGATimer.h"

class ExportedByCATTechTools  CATechTimer : public CATCGATimer
{
public:
  CATechTimer();
  ~CATechTimer();

  CATechTimer (const CATechTimer &);          
  CATechTimer& operator=(const CATechTimer&);  

// Starting the timer
  void _Start();

// Stoping the timer
  void _Stop();

// Resets the elapsed and CPU time
  void _Reset();

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


};

#endif
