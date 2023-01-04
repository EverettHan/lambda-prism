//=============================================================================
// COPYRIGHT Dassault Systemes 2013
//=============================================================================
//
// CATPolyDebugGPUTraces.h
//
//=============================================================================
// 2013-07-09   JXO
//      * New
//=============================================================================
#ifndef CATPolyDebugGPUTraces_H
#define CATPolyDebugGPUTraces_H

/**
 * To trace a method, just add at the beginning of it:
 * void MyClass::MyMethod(...)
 * {
 *   DEBUGGPUSTACKTRACE(type);
 *   // [...]
 * }
 *
 * To trace the construction and destruction of an object, add at the end of the class declaration:
 * class MyClass
 * {
 *   // [...]
 *   DEBUGGPUOBJECTTRACE(membername);
 * };
 * And in the beginning of the definition of the constructor of the object:
 * MyClass::MyClass(...)
 * {
 *   DEBUGGPUOBJECTTRACECTOR(membername, type);
 *   // [...]
 * }
 */

// Comment out to deactivate gpu traces
#define ActivateCATPolyDebugGPUTraces



#ifdef ActivateCATPolyDebugGPUTraces
// Store previous state to put it back
#ifdef ActivateCATPolyDebugTraces
#define WasActivateCATPolyDebugTraces
#endif

#define ActivateCATPolyDebugTraces
#include "CATPolyDebugTraces.h"
#define DEBUGGPUSTACKTRACE(type) DEBUGSTACKTRACE(CATPolyDebugStackTraceMaskGPGPU|(type))
#define DEBUGGPUOBJECTTRACE(membername) DEBUGOBJECTTRACE(membername)
#define DEBUGGPUOBJECTTRACECTOR(membername, type) DEBUGOBJECTTRACECTOR(membername, CATPolyDebugStackTraceMaskGPGPU|(type))
#else
#define DEBUGGPUSTACKTRACE(type)
#define DEBUGGPUOBJECTTRACE(membername)
#define DEBUGGPUOBJECTTRACECTOR(membername, type)
#endif

#ifdef WasActivateCATPolyDebugTraces
#define ActivateCATPolyDebugTraces
#else
#undef ActivateCATPolyDebugTraces
#endif

#endif

