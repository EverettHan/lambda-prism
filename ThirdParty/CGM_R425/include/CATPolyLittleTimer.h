// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyLittleTimer
//
//===================================================================
// 2011-01-04   JXO
//      * New
//===================================================================
#ifndef CATPolyLittleTimer_H
#define CATPolyLittleTimer_H

#include "PolyMultiThreading.h"

#include "CATPolyAtomicOperations.h"

#include "CATMathInline.h"
#include "CATMutex.h"
#include "CATBoolean.h"

#define DEBUGTRACESTIMER

#include <chrono>
#include <stdio.h>
#include <iostream.h>

class ExportedByPolyMultiThreading CATPolyLittleTimer {
public:
  INLINE CATPolyLittleTimer(CATBoolean traces = FALSE){
    m_start_time = std::chrono::steady_clock::now();
    m_stopped = FALSE;
    m_total_time = std::chrono::duration<double, std::milli>::zero();
    m_nbcalls = 0;
    m_value = 0;
    m_traces = traces;
    m_id = CATPolyAtomicOperations::Increment(&s_id);

#ifdef DEBUGTRACESTIMER
    if(m_traces > 1)
    {
      printf("Creation of Timer id %d\n", m_id);
    }
#endif
  }

  ~CATPolyLittleTimer(){
    if(!m_stopped)
    {
      stop(0);
    }

#ifdef DEBUGTRACESTIMER
    if(m_traces)
    {
      printf("Deletion of Timer id %d:\n", m_id);
      printf("Total time for id %d: %fms\n", m_id, GetTotalTime());
      printf("Value for id %d: %d\n", m_id, GetValue());
      printf("Number of calls for id %d: %d\n", m_id, GetNbCalls());
    }
#endif
  }

  //! Start timer
  INLINE void start(int const value = 0){
    m_start_time = std::chrono::steady_clock::now();
    ++m_nbcalls;
    m_value+=value;
    m_stopped = FALSE;
  }

  //! Stop timer
  INLINE void stop(int const value = 0){
    m_end_time = std::chrono::steady_clock::now();
    auto const diff_time = m_end_time - m_start_time;
    m_total_time += diff_time;
    m_value+=value;

#ifdef DEBUGTRACESTIMER
    if(m_traces > 1)
    {
      printf("Stop for id %d:\n", m_id);
      printf("Total time for id %d: %fs\n", m_id, GetTotalTime());
      printf("Value for id %d: %d\n", m_id, GetValue());
      printf("Number of calls for id %d: %d\n", m_id, GetNbCalls());
    }
#endif
    m_stopped = TRUE;
  }

  //! Get total time, in milli-seconds
  INLINE double GetTotalTime()
  {
    return m_total_time.count();
  }
  //! Get value
  INLINE int GetValue()
  {
    return m_value;
  }
  //! Get nb calls
  INLINE int GetNbCalls()
  {
    return m_nbcalls;
  }
  //! Reset
  INLINE void Reset()
  {
    m_total_time = std::chrono::duration<double, std::milli>::zero();
    m_nbcalls = 0;
    m_value = 0;
    m_start_time = std::chrono::steady_clock::now();
    m_stopped = FALSE;
  }

private:
  std::chrono::time_point<std::chrono::steady_clock> m_start_time;
  std::chrono::time_point<std::chrono::steady_clock> m_end_time;

  std::chrono::duration<double, std::milli> m_total_time;
  int m_nbcalls;
  int m_value;
  CATBoolean m_traces;
  int m_id;
  CATBoolean m_stopped;

  static CATMutex s_m;
  static int s_id;

public:
  static CATPolyLittleTimer * CATGetPolyLittleTimer(void *& singleton);
};


#endif
