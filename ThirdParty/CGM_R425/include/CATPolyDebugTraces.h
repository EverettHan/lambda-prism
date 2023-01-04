//=============================================================================
// COPYRIGHT Dassault Systemes 2013
//=============================================================================
//
// CATPolyDebugTraces.h
//
//=============================================================================
// 2013-04-30   JXO
//      * New
//=============================================================================
#ifndef CATPolyDebugTraces_H
#define CATPolyDebugTraces_H

#include <stdlib.h>

/**
 * Define this variable before including this file if you want to use 
 * the DEBUGSTACKTRACE and DEBUGOBJECTTRACE macros:
 * "ActivateCATPolyDebugTraces"
 *
 * To trace a method, just add at the beginning of it:
 * void MyClass::MyMethod(...)
 * {
 *   DEBUGSTACKTRACE(type);
 *   // [...]
 * }
 *
 * To trace the construction and destruction of an object, add at the end of the class declaration:
 * class MyClass
 * {
 *   // [...]
 *   DEBUGOBJECTTRACE(membername);
 * };
 * And in the beginning of the definition of the constructor of the object:
 * MyClass::MyClass(...)
 * {
 *   DEBUGOBJECTTRACECTOR(membername, type);
 *   // [...]
 * }
 */

// ExportedBy
#include "PolyMathUtils.h"

// CGM
#include "CATCGMDynamicFunction.h"
#include "CATMathInline.h"

// System
#include "CATLib.h"

// Masks
// 0: Never taken
// 1: Sub routine
// 2: High level operator
// Type:
#define CATPolyDebugStackTraceMaskSubRoutine          1
#define CATPolyDebugStackTraceMaskOperator            3
// Class:
#define CATPolyDebugStackTraceMaskOthers              4
#define CATPolyDebugStackTraceMaskClash               8
#define CATPolyDebugStackTraceMaskGPGPU               16
#define CATPolyDebugStackTraceMaskPathPlanning        32
#define CATPolyDebugStackTraceMaskCGM                 64
// So default type is 5 (any subroutine)


class CATPolyDebugStackTraceEvent;
typedef CATPolyDebugStackTraceEvent * CreateStackTraceFunc(const char * funcname, CATPolyDebugStackTraceEvent * pE, int type);
typedef CATPolyDebugStackTraceEvent * CreateObjectTraceFunc(const char * funcname, CATPolyDebugStackTraceEvent * pE, int type);

class ExportedByPolyMathUtils CATPolyDebugStackTrace
{
public:
  INLINE CATPolyDebugStackTrace(const char * funcname = 0, int type = 5):
  m_pEvent(0)
  {
    if(s_Create && (type&s_TypeMask) && (type&s_ClassMask))
      m_pEvent = (*s_Create)(funcname, 0, type);
  }
  INLINE ~CATPolyDebugStackTrace()
  {
    if(s_Create && m_pEvent)
      (*s_Create)(0, m_pEvent, 0);
    m_pEvent = 0;
  }
private:
  CATPolyDebugStackTraceEvent * m_pEvent;
public:
  static CreateStackTraceFunc * s_Create;
  static int                    s_TypeMask;
  static int                    s_ClassMask;
};

class ExportedByPolyMathUtils CATPolyDebugObjectTrace
{
public:
  INLINE CATPolyDebugObjectTrace():m_pEvent(0){}
  INLINE void Construct(const char * funcname = 0, int type = 5)
  {
    if(s_Create && (type&CATPolyDebugStackTrace::s_TypeMask) && (type&CATPolyDebugStackTrace::s_ClassMask))
      m_pEvent = (*s_Create)(funcname, 0, type);
  }
  INLINE ~CATPolyDebugObjectTrace()
  {
    if(s_Create && m_pEvent)
      (*s_Create)(0, m_pEvent, 0);
    m_pEvent = 0;
  }
private:
  CATPolyDebugStackTraceEvent * m_pEvent;
public:
  static CreateObjectTraceFunc * s_Create;
};


#if defined(ActivateCATPolyDebugTraces) && defined(_WINDOWS_SOURCE)

#define EXPANDDEBUGSTACKTRACE2(w, x, y, z, t) CATPolyDebugStackTrace w##y (z" ["x":"#y"]", t);
#define EXPANDDEBUGSTACKTRACE1(w, x, y, z, t) EXPANDDEBUGSTACKTRACE2(w, x, y, z, t)
#define DEBUGSTACKTRACE(t) EXPANDDEBUGSTACKTRACE1(stack, __FILE__, __LINE__, __FUNCTION__, (t))

#define DEBUGOBJECTTRACE(object) CATPolyDebugObjectTrace object;
#define DEBUGOBJECTTRACECONSTRUCT(w, x, y, z, t) w.Construct(z" ["x":"#y"]", t)
#define DEBUGOBJECTTRACECTOR(object, t) DEBUGOBJECTTRACECONSTRUCT(object, __FILE__, __LINE__, __FUNCTION__, (t))

#else
#define DEBUGSTACKTRACE(type)
#define DEBUGOBJECTTRACE(object)
#define DEBUGOBJECTTRACECTOR(object, type)
#endif
#endif

