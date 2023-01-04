
#ifndef DSYCxxMagicStaticCustom_H
#define DSYCxxMagicStaticCustom_H
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/


// COPYRIGHT DASSAULT SYSTEMES 2021

/**
 * Alternative implementation to C++ function-local (magic) statics, 
 * in order to alleviate dynamic initialization bugs on Windows (init of static objects under Loader Lock that trigger init of magic statics)
 * Function-local statics guarantee a thread-safe initialization until C++11, 
 * unless this non-conformant compile option is set on Windows: LOCAL_POST_CCFLAGS = /Zc:threadSafeInit- 
 * 
 * Standard pattern:
 * inline T& getSingleton() {
 *      static T s_Inst(...);
 *      return s_Inst;
 * }
 * 
 * Equivalent code with this implementation:
 * inline T& getSingleton() {
 *      static MagicStatic<T> s_Inst;   // Not a magic static, bacause MagicStatic<T> is a POD!
 *      return s_Inst.GetInstance(...);
 * }
 * 
 * Or:
 *
 * static MagicStatic<T> s_Inst;    // Global scope definition
 * inline T& getSingleton() {
 *      return s_Inst.GetInstance(...);
 * }
 * 
 * Portability assumptions:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2444.html#AppendixSource
 */

// Valid only on x86/x86-64???
// TODO requirements
// C++17 support (could probably be loosen to C++14 support)

// cf. http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2444.html#AppendixSource
// cf. MS CRT code: crt\src\vcruntime\thread_safe_statics.cpp
// cf. https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Nifty_Counter
// cf. https://wiki.osdev.org/C_PlusPlus

// #include <stack> // Cause ambiguity with DS struct named 'stack' in the global namespace
#include <deque>
#include <climits>  // INT_MIN
#if defined(_MSC_VER)
#include <synchapi.h>   // SRWLOCK
#else
#include <mutex>                // std::unique_lock, std::mutex
#include <condition_variable>   // std::condition_variable
#endif

#define DSY_MAGIC_STATIC_UNINITIALIZED      0
#define DSY_MAGIC_STATIC_BEING_INITIALIZED  (-1)
#define DSY_MAGIC_STATIC_EPOCH_START        INT_MIN

// To date, 'no_sanitize' attribute only applies to functions and global variables
#if defined(__has_attribute)
#if __has_attribute(no_sanitize)
#define DSY_MAGIC_STATIC_NO_SANITIZE(what) __attribute__((no_sanitize(#what)))
#endif
#endif
#if !defined(DSY_MAGIC_STATIC_NO_SANITIZE)
#define DSY_MAGIC_STATIC_NO_SANITIZE(what)
#endif

#if defined(_MSC_VER)
#define DSY_MAGIC_STATIC_FORCE_INLINE   __forceinline
#else
#define DSY_MAGIC_STATIC_FORCE_INLINE   __inline__ __attribute__((always_inline))
#endif


namespace dsy::internal::magic_static 
{
    // Type that is expected to not exhibit word tearing when accessed with full-width accesses.
    using fast_once_t = int;

    // Helper function
    template<typename _Ty>
    inline _Ty& getSingletonLazy() {   // WARNING: must be called once in mono-thread for safe init
        static typename std::aligned_storage<sizeof(_Ty), alignof(_Ty)>::type g_Inst;
        static bool g_Inst_init = false;
        if (!g_Inst_init) {
            new (&g_Inst) _Ty();	// Placement new
            g_Inst_init = true;
        }
        return reinterpret_cast<_Ty&>(g_Inst);
    }
    
#if !defined(_MSC_VER)
    using mutex_t = std::mutex;
    template<typename _Ty>
    using unique_lock_t = std::unique_lock<_Ty>;
    using condition_variable_t = std::condition_variable;    
#else    
    class mutex_t
    {
        SRWLOCK m_srw;
        friend class condition_variable_t;
    public:
        // IMPORTANT: thanks to the constexpr default constructor, 
        // global objects of this class will be Constant-initialized:
        // cf. https://en.cppreference.com/w/cpp/language/constant_initialization
        constexpr mutex_t() noexcept : m_srw(SRWLOCK_INIT) {
        }
        void lock() {
            AcquireSRWLockExclusive(&m_srw);
        }
        void unlock() {
            ReleaseSRWLockExclusive(&m_srw);
        }
    };
    
    // Using std::unique_lock provokes compile errors in apps due to the inclusion of STL headers...
    // IVMultimediaPlugins RemoteGraphicsTools RemoteDesktopServer RemoteDesktopClient
    // error C2065: 'INTMAX_MAX': undeclared identifier
    template<typename _Ty>
    class unique_lock_t     
    {
        _Ty &m_rMutex;
    public:
        explicit unique_lock_t( _Ty& m ) : m_rMutex(m) {
            m_rMutex.lock();
        }
        ~unique_lock_t() {
            m_rMutex.unlock();
        }
        _Ty* mutex() const noexcept {
            return &(m_rMutex);
        }
    };
    
    // using condition_variable_t = std::condition_variable_any;    // Not supported in managed code (compiled with /clr)
    class condition_variable_t  // Hence a custom wrapper for Windows "CONDITION_VARIABLE"
    {
        CONDITION_VARIABLE m_cv;
    public:
        condition_variable_t() {
            InitializeConditionVariable(&m_cv);
        }
        void notify_all() noexcept {
            WakeAllConditionVariable(&m_cv);
        }
        void wait( unique_lock_t<mutex_t>& lock ) {
            const DWORD timeout = INFINITE;
            SleepConditionVariableSRW(&m_cv, &(lock.mutex()->m_srw), timeout, 0);
        }
    };    
#endif
    
    /**
     * Global variables
     * All these variables and accessor functions are inline, 
     * in order to guarantee their unicity per module (Dll/Exe)
     */
	inline fast_once_t global_epoch = DSY_MAGIC_STATIC_EPOCH_START;
	inline thread_local fast_once_t per_thread_epoch = DSY_MAGIC_STATIC_EPOCH_START;
    
    // global_mutex.
    // According to the C++ Standard, it is safe to lock a std::mutex in a constructor of any static object.
    // In other words, there is no risk of Initialization Order Fiasco.
    // !!! But currently, Visual C++ 2019 (16.9.2) does not seem to comply to this (cf. custom class mutex_t)
	inline mutex_t global_mutex;	// IMPORTANT: This is not intended to be a recursive lock !!!
    
    
    // The condition_variable must not be defined at global scope, 
    // because it would lead to a high risk of Initialization Order Fiasco, 
    // in case there are variables defined at global scope that trigger 
    // the initialization of a magic static (which depends on the condition variable)
    inline condition_variable_t& get_cv() {
        return getSingletonLazy<condition_variable_t>();
    }


    /**
     * Helper functions for accessing the mutex and the condition variable. 
     */

    // Control access to the initialization expression.  Only one thread may leave
    // this function before the variable has completed initialization, i.e. the thread
    // that will perform initialization.  All other threads are blocked until the
    // initialization completes or fails due to an exception.
    inline void Init_thread_header(fast_once_t* const pOnce) noexcept
    {
        unique_lock_t<mutex_t> lck(global_mutex);
        auto & cv = get_cv(); // ++IK8: Ensure thread-safe init of the condition variable

        if (*pOnce == DSY_MAGIC_STATIC_UNINITIALIZED)
        {
            *pOnce = DSY_MAGIC_STATIC_BEING_INITIALIZED;
        }
        else
        {
            while (*pOnce == DSY_MAGIC_STATIC_BEING_INITIALIZED)
            {
                // ++IK8
                // "wait" causes the current thread to block until the condition variable is notified 
                // or a spurious wakeup occurs, hence the need for loop.
                // Besides, the condition variable can be notified by a third party thread that happens 
                // to initialize another magic static variable (different *pOnce variable)
                // ++IK8
                cv.wait(lck);                

                if (*pOnce == DSY_MAGIC_STATIC_UNINITIALIZED)
                {
                    *pOnce = DSY_MAGIC_STATIC_BEING_INITIALIZED;
                    return;
                }
            }
            per_thread_epoch = global_epoch;
        }
    }   // Init_thread_header

    // Abort processing of the initializer due to an exception.  Reset the state
    // to DSY_MAGIC_STATIC_UNINITIALIZED and release waiting threads (one of which will take over
    // initialization, any remaining will again sleep).
    inline void Init_thread_abort(fast_once_t* const pOnce) noexcept
    {
        {
            unique_lock_t<mutex_t> lck(global_mutex);
            *pOnce = DSY_MAGIC_STATIC_UNINITIALIZED;
        }
        get_cv().notify_all();
    }

    // Called by the thread that completes initialization of a variable.
    // Increment the global and per thread counters, mark the variable as
    // initialized, and release waiting threads.
    // inline void Init_thread_success(fast_once_t* const pOnce) noexcept
    inline void Init_thread_success(fast_once_t* const pOnce, void(*pfunc)(void*param), void*param) noexcept
    {
        {
            unique_lock_t<mutex_t> lck(global_mutex);
            ++global_epoch;
            *pOnce = global_epoch;
            per_thread_epoch = global_epoch;
            if(pfunc) pfunc(param);    // ++IK8
        }
        get_cv().notify_all();
    }

}   // namespace dsy::internal::magic_static


namespace dsy
{
    template<typename _Ty>
    class MagicStatic
    {
    public:
        // CTOR: assuming "this" is TLS-allocated, initialized to 0, no guarantee that a custom constructor would be called in all cases!
        // Because the default constructor is constexpr, static MagicStatic objects are initialized as part of static non-local initialization, 
        // before any dynamic non-local initialization begins. This makes it safe to define a static MagicStatic object at function scope, 
        // it will not be compiled as a magic static
        constexpr MagicStatic() noexcept = default;   // Trivial constructor because MagicStatic is expected to be a POD
        
        template<typename ...Args>
        DSY_MAGIC_STATIC_FORCE_INLINE DSY_MAGIC_STATIC_NO_SANITIZE(thread) 
        _Ty& GetInstance(Args && ...args)
        {
            // FAST PATH LOGIC BEGIN: 
            // code potentially platform dependent (x86)
            // Sanitizers should report a data race here (by design).
            // WARNING: DO NOT change branch definition order - could worsen performance, causing branch mispredictions
            internal::magic_static::fast_once_t x = m_iOnce;    // unprotected access for performance
            if ( x <= dsy::internal::magic_static::per_thread_epoch) {
        #if __cplusplus >= 202002L
                [[likely]]
        #endif
                return reinterpret_cast<_Ty&>(m_object);
            }
            // IMPORTANT: the code is broken in (GetInstance + _getInstance) for these reasons:
            //  - Incitate the compiler to inline "GetInstance", which contains the code for the fast path
            //  - Limit the scope of DSY_MAGIC_STATIC_NO_SANITIZE(thread) to the designed unprotected memory access
            // FAST PATH LOGIC END 
            return _getInstance(std::forward<Args>(args)...);
        }
        
    #if 0   // MagicStatic must be a POD
        // TODO Replace by atexit? BEGIN
        ~MagicStatic() { 
            Destroy(this);
        }
        // TODO Replace by atexit? END
    #endif
        
        
    private:
        
        template<typename ...Args>
        _Ty& _getInstance(Args && ...args)
        {
            struct ExceptionHandler 
            {
                /**
                 * ExceptionHandler.
                 * Pros:
                 *  - No explicit catch handler (cf. support of code compiled with exceptions disabled
                 *  - No explicit rethrow, which conserve the stack of the original throw
                 */
                ExceptionHandler(internal::magic_static::fast_once_t & iOnce) noexcept 
                    : m_rOnce(iOnce)
                {
                    dsy::internal::magic_static::Init_thread_header(&m_rOnce);
                }
                ~ExceptionHandler() noexcept {
                    if(!m_bInitSuccess) {
                        // An exception occured!
                        dsy::internal::magic_static::Init_thread_abort(&m_rOnce);
                    }
                }
                internal::magic_static::fast_once_t & m_rOnce;
                bool m_bInitSuccess = false;
            } exceptHandler(m_iOnce);
            
            // By design, only one thread can go through here at a time 
            // (potential others are waiting on the condition variable in ExceptionHandler's constructor)
            if (m_iOnce == DSY_MAGIC_STATIC_BEING_INITIALIZED)
            {
                // The current thread is about to attempt to init the magic static
                if constexpr(std::is_class<_Ty>::value) 
                {
                    new (&m_object) _Ty(std::forward<Args>(args)...);	// Placement new                            
                    // CTOR did not fire any exception, init is done!
                
                    dsy::internal::magic_static::Init_thread_success(&m_iOnce, [](void *param) {
                        // Callback executed under lock, because multiple magic statics could be initialized at once by different threads
                        // TODO: what about stability of deinit order then???
                        get_ListMagicStatic().push_back(reinterpret_cast<MagicStatic*>(param));
                    }, this);
                    
                    // std::atexit - From Cpp standard: "The same function may be registered more than once."
                    std::atexit(_destroy);
                }
                else 
                {
                    reinterpret_cast<_Ty&>(m_object) = callInitFunc(std::forward<Args>(args)...);
                    // callInitFunc did not fire any exception, init is done!
                    dsy::internal::magic_static::Init_thread_success(&m_iOnce, nullptr, nullptr);
                }
            }
            // Report no exception fired
            exceptHandler.m_bInitSuccess = true;
            return reinterpret_cast<_Ty&>(m_object);
        }   // _getInstance
        
        static void Destroy(MagicStatic *pStatic)
        {
            // TODO: order of destruction vs static init ???? Problem... use atexit upon creation? 
            //if (m_bInitialized)
            // Equivalent to test < -1
            if(pStatic->m_iOnce != DSY_MAGIC_STATIC_UNINITIALIZED &&
                pStatic->m_iOnce != DSY_MAGIC_STATIC_BEING_INITIALIZED)    // m_iOnce should not be allowed to be in 'DSY_MAGIC_STATIC_BEING_INITIALIZED' state
            {
                // Destruction required!
                reinterpret_cast<_Ty&>(pStatic->m_object).~_Ty();   // Does nothing for built-in types (such as pointers...)
                pStatic->m_iOnce = DSY_MAGIC_STATIC_UNINITIALIZED;
            }
        }

        static void _destroy()
        {
            auto& list = get_ListMagicStatic();
            MagicStatic* pStatic = list.back();
            if (pStatic)
            {
                list.pop_back();
                Destroy(pStatic);
            }        
        }
        
        static std::deque<MagicStatic*>& get_ListMagicStatic() {
            return dsy::internal::magic_static::getSingletonLazy<std::deque<MagicStatic*>>();
        }
        
        template<typename TCallable, typename ...Args>
        _Ty callInitFunc(TCallable && callable, Args&& ...args) noexcept {
            return std::forward<TCallable>(callable)(std::forward<Args>(args)...);
        }
        
        
        // Data Members
        typename std::aligned_storage<sizeof(_Ty), alignof(_Ty)>::type m_object;
        internal::magic_static::fast_once_t m_iOnce;
        
    };  // class MagicStatic

}   // namespace dsy


#endif  // DSYCxxMagicStaticCustom_H
