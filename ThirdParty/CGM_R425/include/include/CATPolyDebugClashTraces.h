//=============================================================================
// COPYRIGHT Dassault Systemes 2013
//=============================================================================
//
// CATPolyDebugClashTraces.h
//
//=============================================================================
// 2013-05-03   JXO
//      * New
//=============================================================================
#ifndef CATPolyDebugClashTraces_H
#define CATPolyDebugClashTraces_H

/**
 * To trace a method, just add at the beginning of it:
 * void MyClass::MyMethod(...)
 * {
 *   DEBUGCLASHSTACKTRACE(type);
 *   // [...]
 * }
 *
 * To trace the construction and destruction of an object, add at the end of the class declaration:
 * class MyClass
 * {
 *   // [...]
 *   DEBUGCLASHOBJECTTRACE(membername);
 * };
 * And in the beginning of the definition of the constructor of the object:
 * MyClass::MyClass(...)
 * {
 *   DEBUGCLASHOBJECTTRACECTOR(membername, type);
 *   // [...]
 * }
 */

// Comment out to deactivate clash traces
#define ActivateCATPolyDebugClashTraces



#ifdef ActivateCATPolyDebugClashTraces
// Store previous state to put it back
#ifdef ActivateCATPolyDebugTraces
#define WasActivateCATPolyDebugTraces
#endif

#define ActivateCATPolyDebugTraces
#include "CATPolyDebugTraces.h"
#define DEBUGCLASHSTACKTRACE(type) DEBUGSTACKTRACE(CATPolyDebugStackTraceMaskClash|(type))
#define DEBUGCLASHOBJECTTRACE(membername) DEBUGOBJECTTRACE(membername)
#define DEBUGCLASHOBJECTTRACECTOR(membername, type) DEBUGOBJECTTRACECTOR(membername, CATPolyDebugStackTraceMaskClash|(type))
#else
#define DEBUGCLASHSTACKTRACE(type)
#define DEBUGCLASHOBJECTTRACE(membername)
#define DEBUGCLASHOBJECTTRACECTOR(membername, type)
#endif

#ifdef WasActivateCATPolyDebugTraces
#define ActivateCATPolyDebugTraces
#else
#undef ActivateCATPolyDebugTraces
#endif

#endif

