#ifndef DSYSysRefCounter_H
#define DSYSysRefCounter_H

// Copyright DASSAULT SYSTEMES 2013
#include "DSYSysAtomic.h"   // Legacy dependency
#include <atomic>           // C++11 atomics

/*
// [Windows] To suppress warning C4275: non dll-interface class used as base for dll-interface class
#pragma warning( push )
#pragma warning( disable : 4275 )
class Derived : public DSYSysRefCounter { };
#pragma warning( pop )
*/

/**
 * DSYSysRefCounter.
 * Helper class that handles reference counting for a derived class (AddRef/Release), 
 * which objects are to be allocated on the heap with C++ operator new.
 * IMPORTANT: DO NOT ADD STATIC IN THIS OBJECT, NOR ADD OBJECT THAT USE STATIC METHOD, DATA MEMBER OR VARIABLE
 */
class DSYSysRefCounter
{
public:
    /**
     * Constructors.
     * Create a new object which reference count is necessarily 1.
     */
    // Default constructor
    DSYSysRefCounter() : m_cRef(1) {}
    // Copy constructor
    DSYSysRefCounter(const DSYSysRefCounter &) : m_cRef(1) {}
    // Move constructor
    DSYSysRefCounter(DSYSysRefCounter &&) noexcept : m_cRef(1) {}
    
    virtual ~DSYSysRefCounter() {};
    
    /**
     * Assignment operators.
     * Doesn't change the object's address, nor does it invalidate existing references to it,
     * so the reference count must not change!
     * Think of those as regular non-const member functions.
     */
    // Copy assignment
    DSYSysRefCounter & operator=(const DSYSysRefCounter &) {
        return *this;
    }
    // Move assignment
    DSYSysRefCounter & operator=(DSYSysRefCounter &&) noexcept {
        return *this;
    }
    
    
    CATINT32 AddRef();
    CATINT32 Release();
    
private:    // Not "protected" access! m_cRef must be accessible only through AddRef/Release member functions!
    std::atomic<CATINT32> m_cRef;
};

inline CATINT32 DSYSysRefCounter::AddRef()
{
    return m_cRef.fetch_add(1) + 1;
}

inline CATINT32 DSYSysRefCounter::Release()
{
    CATINT32 rc = this->m_cRef.fetch_sub(1) - 1;
    if (rc <= 0)
    {
        delete this;
    }
    return rc;
}

#endif  // DSYSysRefCounter_H
