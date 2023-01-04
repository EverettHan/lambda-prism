// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyThreads.h
//
//===================================================================
//
// Usage notes:
//
// Thread class used to register pools at the beginning of a 
// computation and to unregister them at the end. This way 
// there is one pool per thread with no mutex locking/unlocking
// for each allocation / deallocation.
// You should derive from this class and implement CATThreads
// methods.
//
//===================================================================
//
// Aug 2010 Creation: JXO
// Nov 2016 Enable or not CATThread inheritance by template LQ2
//===================================================================

#ifndef CATPolyThreads_h
#define CATPolyThreads_h

// Poly
#include "PolyMultiThreading.h"
#include "CATPolyPool.h"

// System
#include "CATThreads.h"


/**
 * Thread class used to register pools at the beginning of a 
 * computation and to unregister them at the end. This way 
 * there is one pool per thread with no mutex locking/unlocking
 * for each allocation / deallocation.
 * You should derive from this class and implement CATThreads
 * methods.
 */
template< bool ACTIVATE >
class CATPolyThreads : public CATThreads
{
public:
    CATPolyThreads()
    {
#ifndef USE_TBB_MALLOC
        CATPolyPool::RegisterTSPool(this);
#endif
    }

    virtual ~CATPolyThreads()
    {
#ifndef USE_TBB_MALLOC
        CATPolyPool::ReleaseTSPool(this);
#endif
    }

};


template<>
class CATPolyThreads<false>
{
public :
    CATPolyThreads() {}

    virtual ~CATPolyThreads() {}

    //virtual CATLONG32 Begin( void *iArg = 0 ) { return 0; }
};


#endif /* CATPolyThreads */
