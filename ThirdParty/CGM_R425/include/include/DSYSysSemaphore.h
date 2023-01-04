/**
 * @author ik8
 * @fullreview  ik8         13:01:03
 */

#ifndef _DSYSysSemaphore_H_
#define _DSYSysSemaphore_H_

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#ifdef _WINDOWS_SOURCE
    #include <windows.h>
    #include <limits.h>
    #define DSY_SYS_SEM_VALUE_MAX   INT_MAX
#else
    #if ( (defined(_DARWIN_SOURCE)||defined(_IOS_SOURCE))   \
        && !defined MACOS_POSIX ) || defined(_ANDROID_SOURCE)
        #include <limits.h>
        #define DSY_SYS_SEM_VALUE_MAX   INT_MAX
    #else
        #include <semaphore.h>
        #ifdef _SUNOS_SOURCE
            #define DSY_SYS_SEM_VALUE_MAX   _POSIX_SEM_VALUE_MAX
        #else
            #define DSY_SYS_SEM_VALUE_MAX   SEM_VALUE_MAX
        #endif
    #endif
    #include "CATSysTSDataType.h"
#endif
#include "JS0MT.h"

/****************************************************************************/
/* Flags                                                                    */
/****************************************************************************/
#define DSY_SYS_SEM_UNLIMITED_COUNT    -1

#define DSY_SYS_SEM_FROZEN_COUNT        0
#define DSY_SYS_SEM_VARIABLE_COUNT      1

/****************************************************************************/
/* Declarations                                                             */
/****************************************************************************/

/**
 *  DSYSysSemaphore is an object that allows to limit the number of 
 *  simultaneous accesses to a resource.
 *  
 *  The maximum number of actors (e.g. threads) simultaneously accessing the 
 *  resource is specified at initialization (nMax). Although this parameter 
 *  is fixed in the general case, it can be modified at runtime if the 
 *  semaphore has been constructed with the flag DSY_SYS_SEM_VARIABLE_COUNT 
 *  set.\n  
 *  When nMax actors are already accessing the resource, the nMax+1th actor 
 *  will have to wait until one of the other actors releases it.
 * 
 *  General usage :
 *   - To create a semaphore, use the factory DSYSysCreateSemaphore
 *   - To gain access to the resource, use either Wait or TimedWait 
 *   methods
 *   - To release the resource, use the Signal method
 */
class ExportedByJS0MT DSYSysSemaphore
{
public:

    /**
    * DSYSysCreateSemaphore allows to create a semaphore object.
    *
    * @param [in] iMaxCount defines the semaphore's maximum count, i.e. the 
    * maximum number of allowed simultaneous accesses to the protected 
    * resource (range [0,DSY_SYS_SEM_VALUE_MAX] or 
    * DSY_SYS_SEM_UNLIMITED_COUNT).
    * @param [in] iInitialCount represents the initial number of available 
    * accesses. This parameter would generally be set equal to iMaxCount 
    * (range [0,iMaxCount]).
    * @param [in] iSemMode can be set to the following values to define a 
    * specific behavior:
    *   - DSY_SYS_SEM_FROZEN_COUNT
    *   - DSY_SYS_SEM_VARIABLE_COUNT
    *   .
    * In DSY_SYS_SEM_FROZEN_COUNT, the semaphore maximum count is permanently 
    * fixed at construction. This is the recommended mode since it gives the 
    * best performances.    \n
    * WARNING: the mode DSY_SYS_SEM_VARIABLE_COUNT should only be used when 
    * the number of simultenous accesses to the resource can't be bound and/or 
    * requires to be dynamically modified. As a drawback, performances can't 
    * match the ones achieved in DSY_SYS_SEM_FROZEN_COUNT mode.
    *
    * @retval pointer to a semaphore on success
    * @retval NULL otherwise
    */
	static DSYSysSemaphore * DSYSysCreateSemaphore(int iMaxCount, 
        int iInitialCount, char iSemMode = DSY_SYS_SEM_FROZEN_COUNT);
    
    /**
    * WARNING: if the semaphore is destroyed while there are still pending 
    * calls to other member functions (Wait...), the runtime behavior is 
    * undefined.
    */
    virtual ~DSYSysSemaphore();
		
	/**
	* Wait to acquire the access to a resource. If there are no more available 
    * accesses to the protected resource, the call will block until enough 
    * resource release occur. Otherwise, the counter of available accesses is 
    * decreased by one and the call returns immediately.
    * Please note that one should check for any error by using the FAILED
    * macro.
    * 
    * @retval S_OK on success.
    * @retval E_FAIL or a generated error code otherwise.
	*/
	virtual HRESULT Wait() = 0;

    /**
	* @see Wait
    *
    * TimedWait is similar to Wait, except that it allows to specify a limit 
    * on the amount of time that the call should block. Please note that no
    * guarantees are given on the timeout precision in the case of a variable 
    * count semaphore.
    * 
    * @param [in] iMillis is the timeout value in milliseconds (or -1 for 
    * infinite timeout).
    *
    * @retval S_OK on success.
    * @retval S_FALSE on timeout (access not granted).
    * @retval E_FAIL or a generated error code otherwise.
	*/
	virtual HRESULT TimedWait(int iMillis) = 0;

	/**
	* Signal releases an access to the protected resource and thus increments 
    * the available accesses counter by one. Please note that one should check 
    * for any error by using the FAILED macro.
    * 
    * @retval S_OK on success.
    * @retval E_FAIL or a generated error code otherwise.
	*/
	virtual HRESULT Signal() = 0;
    
    /**
    * GetMaxCount return the maximum number of allowed accesses to the 
    * protected resource. 
    *
    * @param [out] oMaxCnt variable where to store the value.
    * 
    * @retval S_OK.
    */
    virtual HRESULT GetMaxCount(int & oMaxCnt) const = 0;

    /************************************************************************/
    /* WARNING: member functions reserved to variable count semaphores, i.e.*/
    /* semaphores constructed with the DSY_SYS_SEM_VARIABLE_COUNT flag set. */
    /* Please read carefully the comments before opting for this mode.      */
    /************************************************************************/
    
    /**
    * IncreaseCount provides a way to increase the maximum count of the 
    * semaphore. 
    * 
    * @param [in] iDeltaMaxCnt is a delta relative to the semaphore current 
    * maximum count. Its value is used to increase the maximum number of 
    * allowed accesses to the protected resource (]0,DSY_SYS_SEM_VALUE_MAX] 
    * range).
    * @param [in] iFreeCnt represents the number of available accesses out of 
    * iDeltaMaxCnt (range [0,iDeltaMaxCnt]). It defines the number of each 
    * type of accesses out of iDeltaMaxCnt:
    *   - available accesses    (iFreeCnt)      
    *   - ongoing accesses      (iDeltaMaxCnt - iFreeCnt)
    *   .
    * This parameter would generally be set equal to iMaxCount.
    *
    * Conditions of success:
    *   + The increase does not entail an overflow of the internal counter 
    *   (cf. DSY_SYS_SEM_VALUE_MAX)
    *
    * @retval S_OK upon success.
    * @retval E_FAIL upon failure.
    * @retval E_NOTIMPL for fixed count semaphores.
    */
    virtual HRESULT IncreaseCount(int iDeltaMaxCnt, int iFreeCnt);

    /**
    * DecreaseCount provides a way to decrease the maximum count of the 
    * semaphore. 
    * 
    * @param [in] iDeltaMaxCnt is a delta relative to the semaphore current 
    * maximum count. Its value is used to decrease the maximum number of 
    * allowed accesses to the protected resource ([-DSY_SYS_SEM_VALUE_MAX,0[ 
    * range).
    *
    * Conditions of success:
    *   + iDeltaMaxCnt + current max count >= 0
    *   + abs(iDeltaMaxCnt) <= current available accesses 
    *     (to ensure that all actors currently accessing the resource can 
    *     then release it)
    *
    * @retval S_OK upon success.
    * @retval E_FAIL upon failure.
    * @retval E_NOTIMPL for fixed count semaphores.
    */
    virtual HRESULT DecreaseCount(int iDeltaMaxCnt);

    /**
    * GetCurrentCount return the current number of available accesses to the 
    * protected resource.
    *
    * @param [out] oCurCnt variable where to store the value.
    * 
    * @retval S_OK upon success.
    * @retval E_NOTIMPL for fixed count semaphores.
    */
    virtual HRESULT GetCurrentCount(int & oCurCnt) const;

protected:
    DSYSysSemaphore();

private:
    DSYSysSemaphore(const  DSYSysSemaphore &iSrc);              // Not impl
    DSYSysSemaphore& operator= (const DSYSysSemaphore &iSrc);   // Not impl
};

#endif
