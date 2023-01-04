// COPYRIGHT DASSAULT SYSTEMES 2003
#ifndef CATDESTRUCT_INCLUDE
#define CATDESTRUCT_INCLUDE
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

// Copyright DASSAULT SYSTEMS 1996
//-----------------------------------------------------------------------------
// Abstract:	Wrapper to call destructor
//-----------------------------------------------------------------------------
// Usage:	Should only be used with the CATDestructOnExit macro
//-----------------------------------------------------------------------------

#include <string.h>
#include "CATErrorDefs.h"

#ifdef _IRIX_SOURCE
    // Workaround for SGI template processor bug:
    // Call Destructor which should in turn call ~class()
    #define DTOR(class)		Destructor()
#else
    #define DTOR(class)		~class()
#endif

//
// Destructor wrapper
//

//
// Base class to have a generic pointer and virtual method
//
class ExportedByJS0ERROR CATDestruct {

  public:
    CATDestruct (void *obj);    
    virtual void Destruct () = 0;    
    virtual ~CATDestruct();
    
    friend class CATXHContext;

  protected:
    void *obj2Destruct;		// the object to destruct
    CATDestruct *prevDestruct;	// previous destruct protect

};

//
// Class template for a virtual destruct
//
template <class T>
class CATDestruct_ : public CATDestruct {

  public:
    CATDestruct_ (T *toDestruct) : CATDestruct (toDestruct) {}
    /*virtual*/ void Destruct () override;

};

template <class T>
void CATDestruct_<T>::Destruct ()
{
    if (obj2Destruct != nullptr) {
    // The destructor of T, "DTOR", might not return, and in this event,
    // any code after a call to "DTOR" is unreachable
    // If the compiler manage to prove this, it might emit a warning/error (for e.g., Visual C4702: unreachable code)
    // NOTE: at runtime, if "DTOR" throws an exception, the program is expected to abort 
    // because another uncaught exception is currently being processed/dispatched
    reinterpret_cast<T *>(obj2Destruct)->DTOR(T); // call destructor
    obj2Destruct = nullptr; // IMPORTANT: a warning/error on this line of code might predict/prevent a runtime error!
    }
}

#endif

    
