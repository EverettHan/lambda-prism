#ifndef CATResourceLock_H
#define CATResourceLock_H

#include "JS0MT.h"

// COPYRIGHT DASSAULT SYSTEMES 2014

/****************************************************************************/
/* Declarations                                                             */
/****************************************************************************/
class CATResourceLockImplItf;

/**
 *  CATResourceLock is a readers-writer lock.
 *  Such a lock is like a mutex, in that it controls access to a shared 
 *  resource, allowing concurrent access to multiple threads for reading but 
 *  restricting access to a single thread for writes to the resource. 
 *  A common use might be to control access to a data structure in memory that 
 *  can't be updated atomically and isn't valid until the update is complete.
 * 
 *  General usage:
 *   - To update a shared resource, use the WriteLock method (exclusive access).
 *   - To gain access to the shared resource, use the ReadLock method.
 */
class ExportedByJS0MT CATResourceLock
{
public:
    
    /**
     * Constructor.
     * @param [in] iRecursive specifies whether the resource lock shall be 
     *             recursive or not.
     * NOTES:
     *  + depending on the implementation, the lock might still be 
     *    recursive even if iRecursive is set to 0.
     *  + Setting iRecursive to 0 may lead to better performance.
     */
    CATResourceLock (unsigned char iRecursive = 1);
    
    /**
     * Destructor.
     */
    ~CATResourceLock();
    
    /**
     * ReadLock.
     * Acquire the lock in shared mode.
     */
    void ReadLock();
    
    /**
     * ReadUnlock.
     * Release the lock acquired in shared mode.
     */
    void ReadUnlock();
    
    /**
     * WriteLock.
     * Acquire the lock in exclusive mode.
     */
    void WriteLock();
    
    /**
     * WriteUnlock.
     * Release the lock acquired in exclusive mode.
     */
    void WriteUnlock();
private:

    // Members
    CATResourceLockImplItf *m_impl;
};
#endif  // CATResourceLock_H
