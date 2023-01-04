
/**
* @deprecated R422 - Use C++11 portable std::atomic instead
* Atomic operations
*
* The interlocked functions provide a simple mechanism for synchronizing 
* access to a variable that is shared by multiple threads. This function is 
* atomic with respect to calls to other interlocked functions.
*/

#ifndef DSYSysAtomic_h
#define DSYSysAtomic_h

/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "CATDataType.h"

/****************************************************************************/
/* Declarations                                                             */
/****************************************************************************/

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<int>::fetch_add)
* Increments atomically the value pointed by ioValue.
*
* @param [in, out] ioValue is a pointer to the variable to be incremented.
* @retval Integer which is the resulting incremented value.
*/
inline int DSYSysInterlockedIncrement(int *ioValue);

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<int>::fetch_sub)
* Decrements atomically the value pointed by ioValue.
*
* @param [in, out] ioValue is a pointer to the variable to be decremented.
* @retval Integer which is the resulting decremented value.
*/
inline int DSYSysInterlockedDecrement(int *ioValue);

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<int>::fetch_add / std::atomic<int>::fetch_sub)
* Atomically adds iValue to the value pointed by ioAddend with respect to 
* other atomic operations performed on ioAddend.
*
* @param [in, out] ioAddend is a pointer to a variable in which the result of 
* the operation will be stored.
* @param [in] iValue is a value to add to the value pointed by ioAddend.
* @retval Integer which is the initial value pointed by ioAddend.
*/
inline int DSYSysInterlockedAdd(int *ioAddend, int iValue);

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<T *>::compare_exchange_strong)
* Atomic test and set operation. The function tests *ioDest against 
* iComparand and sets *ioDest to iExchange if 
* iComparand == *ioDest. Otherwise, nothing is performed.
*
* @param [in, out] ioDest is a pointer to the variable to be compared and 
* possibly replaced.
* @param [in] iExchange  is the value to replace *ioDest if the tests 
* succeeds.
* @param [in] iComparand is the value to compare to *ioDest.
* @retval pointer which is the initial value of the ioDest parameter.
*/
inline void * DSYSysInterlockedCompareExchangePtr(
    void **ioDest, void *iExchange, void *iComparand);

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<int>::compare_exchange_strong)
* Atomic test and set operation.
* @see DSYSysInterlockedCompareExchangePtr.
* 
* @retval Integer which is the initial value of the ioDest parameter.
*/
inline int DSYSysInterlockedCompareExchangeInt32(
    int *ioDest, int iExchange, int iComparand);

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<T *>::exchange)
* Atomically sets the value of *ioDest to iValue with respect to 
* other atomic operations on ioDest.
*
* @param [in, out] ioDest is a pointer to the value to be exchanged.
* @param [in] iValue is the value to be exchanged with the value pointed to 
* by ioDest.
* @retval pointer which is the initial value of *ioDest.
*/
inline void * DSYSysInterlockedExchangePtr(void **ioDest, void *iValue);

/**
* @deprecated R422 - Use C++11 portable std::atomic instead (std::atomic<int>::exchange)
* Atomic exchange operation.
* @see DSYSysInterlockedExchangePtr.
*/
inline int DSYSysInterlockedExchangeInt32(int *ioDest, int iValue);

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/


// Implementation of inline functions
#if defined(_WINDOWS_SOURCE)
#include <windows.h>

inline int DSYSysInterlockedIncrement(int * ioValue)
{
	return InterlockedIncrement((long *) ioValue);
}

inline int DSYSysInterlockedDecrement(int * ioValue) 
{
	return InterlockedDecrement((long *) ioValue);
}

inline int DSYSysInterlockedAdd(int * ioAddend, int iValue)
{
	return InterlockedExchangeAdd((long *) ioAddend,(long)iValue);
}

inline void * DSYSysInterlockedCompareExchangePtr(
    void ** ioDest, void * iExchange, void * iComparand)
{
	return (void *) InterlockedCompareExchangePointer(
        ioDest, iExchange, iComparand);
}

inline int DSYSysInterlockedCompareExchangeInt32(
    int * ioDest, int iExchange, int iComparand)
{
	return InterlockedCompareExchange(
        (long*)ioDest, iExchange, iComparand);
}

inline void * DSYSysInterlockedExchangePtr( void ** ptr, void * value)
{
	return InterlockedExchangePointer( ptr,value);
}

inline int DSYSysInterlockedExchangeInt32(int *ioDest, int iValue)
{
    return InterlockedExchange((LONG volatile *)ioDest,(LONG) iValue);
}

#elif defined(_LINUX_SOURCE) || defined(_DARWIN_SOURCE) \
    || defined(_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)

inline int DSYSysInterlockedIncrement(int * ioValue) 
{
	return __sync_add_and_fetch(ioValue,1);
}

inline int DSYSysInterlockedDecrement(int * ioValue) 
{
	return __sync_sub_and_fetch(ioValue,1);
}

inline int DSYSysInterlockedAdd(int * ioAddend, int iValue)
{
	int l_newValue = __sync_add_and_fetch(ioAddend,iValue);
    return (l_newValue - iValue);
}

inline void * DSYSysInterlockedCompareExchangePtr(
    void ** ioDest, void * iExchange, void * iComparand)
{
	return __sync_val_compare_and_swap (
        ioDest, iComparand, iExchange);
}

inline int DSYSysInterlockedCompareExchangeInt32(
    int * ioDest, int iExchange, int iComparand)
{	
	//return (int)compare_and_swap (ioDest, &iComparand, iExchange);
	return __sync_val_compare_and_swap (ioDest, iComparand,iExchange);
}

inline void * DSYSysInterlockedExchangePtr(void ** ptr, void * value)
{
    // on Intel x86-64, __sync_lock_test_and_set genereates an xchg
    // instruction which is a full memory barrier
    // On other architectures, this intrinsic might require additional fence
    // instruction to implement a full memory barrier
	return __sync_lock_test_and_set(ptr,  value);
}

inline int DSYSysInterlockedExchangeInt32(int *ioDest, int iValue)
{
    return __sync_lock_test_and_set(ioDest, iValue);
}

#else
#error "Unknown OS"
#endif


#if defined(__cplusplus)

#include <atomic>

#ifndef __has_feature
  #define __has_feature(x) 0  // Compatibility with non-clang compilers.
#endif
#if defined(__SANITIZE_THREAD__) || __has_feature(thread_sanitizer) || defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer)
// Enable additional runtime checks for sanitized builds
#include <cassert>
#define DSYSysAtomic_RuntimeCheck
#endif

namespace dsy
{
    namespace internal  // Internal use only
    {
        template<typename _Ty>
        struct is_atomic /* : public std::false_type */{
            static constexpr bool value = false;
        };
        template<typename _Tz>
        struct is_atomic<std::atomic<_Tz>> /* : public std::true_type */ {
            static constexpr bool value = true;
        };
        
#if !defined(__cpp_lib_atomic_ref)  // Pre-C++20
        template<typename _Ty>
        using atom_t = typename std::conditional<std::is_const<_Ty>::value, 
                        std::atomic<typename std::remove_const<_Ty>::type> const, 
                        std::atomic<typename std::remove_const<_Ty>::type> >::type;
#endif
        template<class _Ty>
        CATULONGPTR addressof(_Ty& arg) noexcept {
            return reinterpret_cast<CATULONGPTR>(
                reinterpret_cast<_Ty*>( // cf. std::addressof
                    &const_cast<char&>(reinterpret_cast<const volatile char&>(arg))));
        }
    }   // namespace internal
    
    
#if defined(__cpp_lib_atomic_ref)   // C++20 and onwards
    template<typename _Ty>
        requires (std::atomic_ref<_Ty>::is_always_lock_free && !internal::is_atomic<_Ty>::value)
    std::atomic_ref<_Ty> get_atomic_ref(_Ty & obj) 
    {
        // cf. https://en.cppreference.com/w/cpp/atomic/atomic_ref 
        // "Atomic operations applied to an object through an atomic_ref are atomic 
        //  with respect to atomic operations applied through any other atomic_ref 
        //  referencing the same object."
        
        #if defined(DSYSysAtomic_RuntimeCheck)
        // "The behavior is undefined if obj is not aligned to required_alignment."
        // "Hardware could require that an object to be referenced by an atomic_ref<T> have stricter alignment than other T objects, 
        //  and whether operations on an atomic_ref are lock-free can depend on the alignment of the referenced object."
        assert( !(internal::addressof(obj) % std::atomic_ref<_Ty>::required_alignment) );
        #endif
        
        return std::atomic_ref<_Ty> { obj };
    }
#else   // Pre-C++20
    template<typename _Ty>
    internal::atom_t<_Ty> & get_atomic_ref(_Ty & obj) {
        static_assert(!internal::is_atomic<_Ty>::value, "get_atomic_ref makes no sense on an atomic type!");
        static_assert(sizeof(internal::atom_t<_Ty>) == sizeof(_Ty)); // For reinterpret_cast to be valid
        #if defined(__cpp_lib_atomic_is_always_lock_free)   // Requires C++17
        static_assert(internal::atom_t<_Ty>::is_always_lock_free, "Use a lock, not get_atomic_ref!");
        #endif
        
        #if defined(DSYSysAtomic_RuntimeCheck)
        assert( !(internal::addressof(obj) % alignof(internal::atom_t<_Ty>)) );
        #endif
        
        return reinterpret_cast<internal::atom_t<_Ty> &>(obj);
    }
#endif
    
}   // namespace dsy

#endif  // __cplusplus


#endif  // DSYSysAtomic_h
