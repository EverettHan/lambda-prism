#ifndef DSYSysTSDataQueue_H
#define DSYSysTSDataQueue_H

#include "JS0MT.h"
#include "CATMutex.h"
#include "CATDataType.h"

#include "CATSysErrorDef.h"
#include "DSYSysRefCounter.h"

#include <atomic>

class DSYSysSemaphore;

#if defined(_WINDOWS_SOURCE)
// [Windows] To suppress warning C4275: non dll-interface class used as base for dll-interface class
#pragma warning( push )
#pragma warning( disable : 4275 )
#endif	// _WINDOWS_SOURCE

class ExportedByJS0MT DSYSysTSDataQueue : public DSYSysRefCounter
{
public:
    /* creates a dataQueue
    * @param iAutoWait defines if pop will wait for an element to be inserted before returning if dataQueue is empty
    * @param iMaxCount max Size of the dataQueue (0=infinite)
    * @return the newly created dataQueue
    */
    static DSYSysTSDataQueue * CreateEmptyQueue(bool iAutoWait = true, int iMaxCount = 0);
    virtual ~DSYSysTSDataQueue();
    
    /*
     * GetCurrentLength returns the current length of the queue, which may have changed 
     * by the time this function returns! (cf. concurrent calls to PushFirst/PopLast)
     */ 
    int GetCurrentLength();

    /* adds an element to the list, if autoWait mode then we can specify a max timeout
    * @param iElemPtr element to add
    * @param iTimeout max time to wait
    * @return 1 on success, -1 on error, 0 if timeout exceeded
    */
    int PushFirst(void * iElemPtr, int iTimeout = -1);

    /* gets an element from the list, if autoWait mode then we can specify a max timeout
    * @param oElemPtr element returned from the list, NULL if error
    * @param iTimeout max time to wait
    * @return 1 on success, -1 on error, 0 if timeout exceeded
    */
    int PopLast(void ** oElemPtr, int iTimeout = -1);
    
protected:
    struct fifo_list_elem
    {
        void * _data;
        struct fifo_list_elem * _next;
    };
    
    DSYSysTSDataQueue();
    bool Init(bool iAutoWait, int iMaxCount);
    
    // Members
    CATMutex _listAccess;
    DSYSysSemaphore * _autoWaitSem;
    DSYSysSemaphore * _boundedSem;
    struct fifo_list_elem * _head;
    struct fifo_list_elem * _tail;
    std::atomic<int> _length;
    int _maxLength;
};
#if defined(_WINDOWS_SOURCE)
#pragma warning( pop )
#endif	// _WINDOWS_SOURCE

inline int DSYSysTSDataQueue::GetCurrentLength() { return _length.load(std::memory_order_relaxed); };

#endif  // DSYSysTSDataQueue_H
