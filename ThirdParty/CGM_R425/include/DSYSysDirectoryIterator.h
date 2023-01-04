#ifndef DSYSysDirectoryIterator_H
#define DSYSysDirectoryIterator_H

#include "CATErrorDef.h"
#include "CATSysTS.h"
#include "CxxSupport.h" // DS_CXX11_SUPPORT_MOVE_SEMANTIC

class DSYSysDirectoryIteratorImpl;
class CATSysTSUnicodeString;
class DSYSysPath;

class ExportedByCATSysTS DSYSysDirectoryIterator
{
public:
    DSYSysDirectoryIterator();
    DSYSysDirectoryIterator(const DSYSysDirectoryIterator& iSrc);
    DSYSysDirectoryIterator & operator =(const DSYSysDirectoryIterator & it);
    
#if defined(DS_CXX11_SUPPORT_MOVE_SEMANTIC)
    // Move constructor.
    inline DSYSysDirectoryIterator(DSYSysDirectoryIterator &&iRValue);
    // Move assignment operator.
    inline DSYSysDirectoryIterator& operator=(DSYSysDirectoryIterator &&iRValue);
#endif  // DS_CXX11_SUPPORT_MOVE_SEMANTIC
    
    bool operator == (const DSYSysDirectoryIterator & iComparand) const;
    bool operator != (const DSYSysDirectoryIterator & iComparand) const;
    
    /**
     * Increment operator.
     * Only the prefix form is supported. 
     * Indeed, since there is no way to capture the iteration state
     */
    DSYSysDirectoryIterator& operator++();
    // inline DSYSysDirectoryIterator operator ++(int);                     // deprecated R420
    inline DSYSysDirectoryIterator& operator ++(int) { return ++*this; }    // Compatibility only, not standard, DO NOT USE!
    
    HRESULT	next(void);		
    
    const DSYSysPath & operator *() const;
    HRESULT  GetCurrentPath(DSYSysPath & oPath) const;
    
    // deprecated R417
    HRESULT  GetCurrentName(CATSysTSUnicodeString & oName) const;
    
    ~DSYSysDirectoryIterator();

protected:
    friend class DSYSysPathImpl;
    friend class DSYSysDirectoryIteratorImpl;
    
    // Members
    DSYSysDirectoryIteratorImpl * _impl;
};

#if defined(DS_CXX11_SUPPORT_MOVE_SEMANTIC)
// Move constructor.
inline DSYSysDirectoryIterator::DSYSysDirectoryIterator(DSYSysDirectoryIterator &&iRValue) : _impl(NULL)
{
    // "Steal" the letter from the source object
    _impl = iRValue._impl;    
    // Resetting the source impl pointer so that the destructor does not free it multiple times.
    iRValue._impl = NULL;
}
// Move assignment operator.
inline DSYSysDirectoryIterator& DSYSysDirectoryIterator::operator=(DSYSysDirectoryIterator &&iRValue)
{
    // Swap letters
    DSYSysDirectoryIteratorImpl* l_ThisImpl = _impl;
    _impl = iRValue._impl;          // "Steal" the letter from the source object
    iRValue._impl = l_ThisImpl;     // Let the destructor free l_ThisImpl if necessary
    return *this;
}
#endif  // DS_CXX11_SUPPORT_MOVE_SEMANTIC

#endif  // DSYSysDirectoryIterator_H
