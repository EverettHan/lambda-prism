//=============================================================================
// COPYRIGHT Dassault Systemes 2013
//=============================================================================
//
// CATPolyDebugPathPlanningTraces.h
//
//=============================================================================
// 2013-10-21   JXO
//      * New
//=============================================================================
#ifndef CATPolyDebugPathPlanningTraces_H
#define CATPolyDebugPathPlanningTraces_H

/**
 * To trace a method, just add at the beginning of it:
 * void MyClass::MyMethod(...)
 * {
 *   DEBUGPATHPLANNINGSTACKTRACE(type);
 *   // [...]
 * }
 *
 * To trace the construction and destruction of an object, add at the end of the class declaration:
 * class MyClass
 * {
 *   // [...]
 *   DEBUGPATHPLANNINGOBJECTTRACE(membername);
 * };
 * And in the beginning of the definition of the constructor of the object:
 * MyClass::MyClass(...)
 * {
 *   DEBUGPATHPLANNINGOBJECTTRACECTOR(membername, type);
 *   // [...]
 * }
 */

// Comment out to deactivate Path Planning traces
#define ActivateCATPolyDebugPathPlanningTraces



#ifdef ActivateCATPolyDebugPathPlanningTraces
// Store previous state to put it back
#ifdef ActivateCATPolyDebugTraces
#define WasActivateCATPolyDebugTraces
#endif

#define ActivateCATPolyDebugTraces
#include "CATPolyDebugTraces.h"
#define DEBUGPATHPLANNINGSTACKTRACE(type) DEBUGSTACKTRACE(CATPolyDebugStackTraceMaskPathPlanning|(type))
#define DEBUGPATHPLANNINGOBJECTTRACE(membername) DEBUGOBJECTTRACE(membername)
#define DEBUGPATHPLANNINGOBJECTTRACECTOR(membername, type) DEBUGOBJECTTRACECTOR(membername, CATPolyDebugStackTraceMaskPathPlanning|(type))
#else
#define DEBUGPATHPLANNINGSTACKTRACE(type)
#define DEBUGPATHPLANNINGOBJECTTRACE(membername)
#define DEBUGPATHPLANNINGOBJECTTRACECTOR(membername, type)
#endif

#ifdef WasActivateCATPolyDebugTraces
#define ActivateCATPolyDebugTraces
#else
#undef ActivateCATPolyDebugTraces
#endif

#endif

