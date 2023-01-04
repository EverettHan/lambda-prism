
#ifndef CATSysTSThreadLocalStorage_h
#define CATSysTSThreadLocalStorage_h

#include "CATSysTS.h"
#include "CATErrorDef.h"
#ifndef _WINDOWS_SOURCE
#include <pthread.h>
#endif // _WINDOWS_SOURCE

class ExportedByCATSysTS CATSysTSThreadLocalStorage {

	public :
		
		static int CreateNewKey();
		
		static HRESULT SetValue(int iKey, void * iValue);
	
		static void * GetValue(int iKey);
	
		static HRESULT DeleteValue(int* iopKey);

	private :
		
		CATSysTSThreadLocalStorage();
		~CATSysTSThreadLocalStorage();

		static HRESULT _Init();

		// Static method called by pthread_once or DllMain to create the thread key
		static void _CreateThreadKey();

#ifndef _WINDOWS_SOURCE
		// Static method called each time a thread exits 
		static void _ThreadCleanup(void * iData);
#endif // _WINDOWS_SOURCE

		static void _Cleanup();

		static int S_counterKey;
#ifdef _WINDOWS_SOURCE
		static DWORD S_tlsKey;
#else // _WINDOWS_SOURCE
		static pthread_key_t S_tlsKey;
#endif // _WINDOWS_SOURCE
		
#ifdef _WINDOWS_SOURCE
		friend BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);
#endif // _WINDOWS_SOURCE
};

// ++vxg - 2012:11:23
//=======================================================================
extern "C" ExportedByCATSysTS int DSYSysThreadLocalStorageCreateNewKey(void);
//=======================================================================

//=======================================================================
extern "C" ExportedByCATSysTS void* DSYSysThreadLocalStorageGetValue(const int iKey);
//=======================================================================

//=======================================================================
extern "C" ExportedByCATSysTS int DSYSysThreadLocalStorageSetValue(const int iKey, void * iValue);
//=======================================================================

//=======================================================================
extern "C" ExportedByCATSysTS int DSYSysThreadLocalStorageDeleteValue(int* iopKey);
//=======================================================================
// --vxg - 2012:11:23

// ++IK8 - 2013:11:20
/**
 * The DSY_SYS_TLS_DEFINE_VAR(VarType, varName) macro defines a TLS 
 * pointer of type <VarType> and its accessors. This pointer is zero-
 * initialized. 
 * The macro should be called at file scope, preferably inside an 
 * anonymous namespace (to define a private access).
 * The accessors prototypes are:
 *  + VarType *_TLSGet##varName ()
 *  + void _TLSSet##varName (VarType *)
 *
 * WARNING: _TLSGetXXX primitive should be called once in a non-concurrent
 *          context to ensure thread-safety.
 */

#define DSY_SYS_THREAD_LOCAL    thread_local    // C++11
/* OLD CODE
#if defined(_WINDOWS_SOURCE)
# define DSY_SYS_THREAD_LOCAL  __declspec( thread )
#else
# define DSY_SYS_THREAD_LOCAL  __thread
#endif
*/

#if 1
// Platforms with compiler-supported TLS
# define DSY_SYS_TLS_COMPILER_ASSISTED
# define DSY_SYS_TLS_DEFINE_VAR(VarType, varName)                               \
    DSY_SYS_THREAD_LOCAL VarType *varName##TLS = NULL;                          \
    inline VarType *_TLSGet##varName()                                          \
    {                                                                           \
        return varName##TLS;                                                    \
    }                                                                           \
    inline void _TLSSet##varName(VarType *ipVal)                                \
    {                                                                           \
        varName##TLS = ipVal;                                                   \
    }
#else
// Platforms that do not support compiler-assisted TLS
# define DSY_SYS_TLS_DEFINE_VAR(VarType, varName)                               \
    int varName##TLSKey = -1;                                                   \
    inline VarType *_TLSGet##varName()                                          \
    {                                                                           \
        if(-1 == varName##TLSKey)                                               \
            varName##TLSKey = ::DSYSysThreadLocalStorageCreateNewKey();         \
        return (VarType *) ::DSYSysThreadLocalStorageGetValue(varName##TLSKey); \
    }                                                                           \
    inline void _TLSSet##varName(VarType *ipVal)                                \
    {                                                                           \
        if(-1 == varName##TLSKey)                                               \
            varName##TLSKey = ::DSYSysThreadLocalStorageCreateNewKey();         \
        ::DSYSysThreadLocalStorageSetValue(varName##TLSKey, (void *)ipVal);     \
    }
#endif  // _MACOSX_SOURCE

// --IK8 - 2013:11:20

#endif // CATSysTSThreadLocalStorage_h

