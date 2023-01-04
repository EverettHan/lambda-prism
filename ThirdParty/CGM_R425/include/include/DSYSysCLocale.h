#ifndef DSYSysCLocale_H
#define DSYSysCLocale_H

#include "CATSysTS.h"

#include "CATSysErrorDef.h"
#include "CATSysDataType.h"
#include "DSYSysCommon.h"   // MAX_PATH
#include "CxxSupport.h"     // DS_CXX macros

#if defined(_WINDOWS_SOURCE) 

#define DSYSysCLocalePerThreadSupport_Windows
#define DSYSysCLocalePerThreadSupport

#if (_MSC_VER < 1900)
#include <locale.h>
// Mandatory for per-thread locale support prior to Visual C++ 2015
// Indeed, prior to Visual C++ 2015, APIs such as localeconv are bugged...
// setlocale desynchronized with localeconv
// cf. https://msdn.microsoft.com/en-us/library/bb531344.aspx#Visual%20C++%202015%20Conformance%20Changes
struct _DSYLocale_t
{
    _DSYLocale_t() : m_locDesc(NULL) { }
    ~_DSYLocale_t() { Reset(); }
    
    operator _locale_t() {
        if(!m_locDesc) m_locDesc = _get_current_locale();
        return m_locDesc;
    }
    
    void Reset() {
        if(m_locDesc) _free_locale(m_locDesc);
        m_locDesc = NULL;
    }
    
protected:
    // Members
    _locale_t m_locDesc;
};

#define _DSYLocale_t_Defined
#endif  // (_MSC_VER < 1900)

#elif defined(_LINUX_SOURCE) || defined(_AIX_SOURCE) || defined(_DARWIN_SOURCE)
#define DSYSysCLocalePerThreadSupport_POSIX_2008    // uselocale
#define DSYSysCLocalePerThreadSupport
#endif  // _WINDOWS_SOURCE

#if !defined(LOCALE_NAME_MAX_LENGTH)
#define LOCALE_NAME_MAX_LENGTH          85
#endif  // LOCALE_NAME_MAX_LENGTH

#if defined(DSYSysCLocalePerThreadSupport_POSIX_2008)
#include <locale.h>         // locale_t, lconv
# if defined(_DARWIN_SOURCE)
#include <xlocale.h>
# endif  // _DARWIN_SOURCE
#else
struct lconv;
#endif

/**
 * The DSYSysCLocale namespace provides functions to handle safely the C locale in a multi-threaded environment.
 * IMPORTANT: when performance or portability are not major concerns, consider using temporary C++ locale objects,
 *            but do not use std::locale::global!
 *            For e.g., one could initialize a C++ locale object compliant with DS's environment 
 *            the following way (note that we did not used the locale name "" on purpose!):
 *            
 *            #include <locale>
 *            #include <stdexcept>          // std::runtime_error
 *            #include "DSYSysCLocale.h"    // DSYSysCLocaleEnvironGet
 *            ...
 *            try {
 *                const char *l_szLocaleName = DSYSysCLocaleEnvironGet();
 *                std::locale l_DSEnvironCxxLoc(l_szLocaleName);
 *            } catch(const std::runtime_error &ex) { ... }
 */
namespace DSYSysCLocale
{
    /**
     * ThreadLC is a class that allows to customize the C locale in a 
     * thread-safe manner. An instance lifetime defines a time range in which 
     * the locale is guaranteed to remain steady (unless one calls Reset).
     *
     * IMPORTANT: one must not alter the locale settings directly. In particular,
     * direct calls to the setlocale API are forbidden and could return spurious
     * results (for e.g. when per-thread locale is enabled on Unix-based platforms).
     * To ensure that a given thread is in a particular locale, simply instantiate 
     * a ThreadLC object with the required locale. 
     * Library calls that rely on the C locale (strtod, sscanf, rpmatch...) should not be 
     * called out of the scope/lifetime of a ThreadLC object.
     * Last but not least, localeconv should not be used because it is not thread-safe. Use DSYSysCLocale::GetLCConv instead!
     * These points are MANDATORY for the application code to be locale safe.
     * 
     * BEST PRACTICES:
     *  - Objects should be allocated on the stack: this allows for 
     *    automatic locale restoration when going out of scope.
     *  - Since ThreadLC may synchronize on the global C locale on some platforms, 
     *    it is necessary to ensure that the lifetime of an instance of ThreadLC is 
     *    reasonable to allow for efficient concurrency.
     * 
     * Typical use case:
     *   ...
     *   // Current thread C locale is the global application C locale for e.g.
     *   // We now need to switch to a French C locale whatever the current 
     *   // locale settings are.
     *   ThreadLC l_scopeLC(LC_ALL, "fr_FR", &hr);
     *   if(SUCCEEDED(hr))
     *   {
     *      // French locale dependent code
     *      ...
     *   }
     *   l_scopeLC.Reset();     // Optional - Restore previous locale settings 
     *                          // before end of scope
     */
    class ExportedByCATSysTS ThreadLC
    {
    public:
        /**
        * ThreadLC constructor.
        * @see C setlocale API.
        * @param [in]  iCategory specifies the portion of the locale to be 
        *   affected. It can be one of the following values:
        *   - LC_ALL	    The entire locale.
        *   - LC_COLLATE	Affects the behavior of strcoll and strxfrm.
        *   - LC_CTYPE      Affects character handling functions.
        *   - LC_MONETARY	Affects monetary formatting information returned 
        *                   by localeconv.
        *   - LC_NUMERIC	Affects the decimal-point character in formatted 
        *                   input/output operations and string formatting 
        *                   functions, as well as non-monetary information 
        *                   returned by localeconv.
        *   - LC_TIME       Affects the behavior of strftime.
        * @param [in]  iLocale is a C string containing the name of a C locale 
        *   which is system specific.
        * @param [out] oHr allows to determine if the locale has been 
        *   successfully set or not.
        *   - S_OK in case of success
        *   - E_FAIL in case of failure
        *   - S_FALSE if the locale did not need to be changed.
        */
        ThreadLC(int iCategory, const char *iLocale, HRESULT *oHr = NULL);

        /** 
        * Reset.
        * Restore the locale to its previous value (only if *oHr was S_OK at 
        * creation).
        * One might call this function to restore the locale to its previous state 
        * before the instance is destroyed.
        */
        void Reset();
        
        /**
        * @see Reset.
        * ThreadLC destructor.
        * Restore the locale to its previous value.
        */
        ~ThreadLC();
    private:
        // Prevent copy/move construction & assignment
        ThreadLC(const ThreadLC& iOther);
        ThreadLC &operator =(const ThreadLC &iOther);
#if defined(DS_CXX11_SUPPORT_MOVE_SEMANTIC)
        ThreadLC(ThreadLC &&iRValue);
        ThreadLC &operator=(ThreadLC &&iRValue);
#endif  // DS_CXX11_SUPPORT_MOVE_SEMANTIC
        
        // Members
        char *_prevLC;
#if defined(DSYSysCLocalePerThreadSupport_Windows)        
        int   _prevConfigThreadLocale;
#elif defined(DSYSysCLocalePerThreadSupport_POSIX_2008)
        locale_t  _prevLCObj;
#endif
        int     _category;  // ThreadLC category
        short   _flags;
    };
    
    
    /**
     * LConv.
     * NOTE: designed to hold Unicode characters only! Indeed, some strings may not be able 
     * to be represented in some C locale's encoding (would be OK for UTF-8 though).
     */
    struct LConv;
    struct ExportedByCATSysTS LConv
    {
        LConv()
        {
            memset(&m_plconvW, 0, sizeof(m_plconvW));
            _ReInit();
        }
        ~LConv() {}
        
        const wchar_t *decimal_point();
        const wchar_t *thousands_sep();
        const wchar_t *grouping();
        const wchar_t *int_curr_symbol();
        const wchar_t *currency_symbol();
        const wchar_t *mon_decimal_point();
        const wchar_t *mon_thousands_sep();
        const wchar_t *mon_grouping();
        const wchar_t *positive_sign();
        const wchar_t *negative_sign();
        wchar_t frac_digits();
        wchar_t p_cs_precedes();
        wchar_t n_cs_precedes();
        wchar_t p_sep_by_space();
        wchar_t n_sep_by_space();
        wchar_t p_sign_posn();
        wchar_t n_sign_posn();
        wchar_t int_frac_digits();
        
    private:
        friend ExportedByCATSysTS void GetLCConv(LConv &oLConv);
        
        void _ReInit();
        void _ReInitDecimalPoint(struct lconv &iLConv);
        struct lconv *_GetLibCLocaleConv(bool &oIsMTSafe);
        const wchar_t *_StoreAsWideChar(const char *ipSrc);
        const wchar_t *_StoreAsWideChar(const wchar_t *ipWSrc);
        const wchar_t *_StoreAsWideChar(char iChar);
        
        wchar_t *_AllocWideCharPointer(size_t iCharNum);
        void _FreeWideCharPointer(const wchar_t *&ipWStr);
        size_t _BufferSpaceLeft() {
            return (static_cast<size_t>(MAX_PATH) - m_BufferOffset);
        }
        
        /// Members
        wchar_t  m_Buffer[MAX_PATH];
        const wchar_t *m_plconvW[24];
#if defined(DSYSysCLocalePerThreadSupport_POSIX_2008)
        struct lconv m_lconv;
#endif  // DSYSysCLocalePerThreadSupport_POSIX_2008
        size_t   m_BufferOffset;
#if defined(_DSYLocale_t_Defined)
        _DSYLocale_t  m_LocaleWrapper;
#endif   // defined(_DSYLocale_t_Defined)
        struct lconv *m_plconv; // Set if lazy-initialization is allowed (MT-safe locale)
    };
  
    /**
    * GetLCConv.
    * Retrieves the values provided in the current locale object to format 
    * parameters for quantities.
    * Replacement for localeconv that is Unicode compliant and support per-thread locale when available.
    * It should always be used instead of direct calls to localeconv.
    * @param [out] oLConv reference to a LConv object to be initialized according to the current C locale.
    * NOTES:
    *   - When DSYSysCLocaleIsPerThread returns false, the return value of this function is not guaranteed 
    *     to be valid after the call. It is only guaranteed that it has been the case at some point during the call. 
    *     Thus, the retrieved data should not be strongly relied on.
    *   - Moreover, since the underlying localeconv function is not thread-safe on all platforms, GetLCConv
    *     might lock to avoid any concurrency issues. However, it cannot protect itself against concurrent
    *     calls to the localeconv function.
    */
    ExportedByCATSysTS void GetLCConv(LConv &oLConv);
}

/**
 * DSYSysCLocaleEnvironGet.
 * Retrieve the C locale which is required for DS applications to run properly.
 * Do not rely on the C environment's default locale "", which may be different, 
 * for example if DS language settings have been customized.
 * WARNING: this locale may change during the lifetime of the session. Thus, 
 *          the caller should not cache the returned pointer.
 * @param [in, out] ioBuffer is a buffer which's size must be at least LOCALE_NAME_MAX_LENGTH
 * @return a pointer to a locale string in case of success.
 * @return NULL otherwise (this can happen on platforms which do not support
 *         the C locale, such as Android, or if NLS core initialization failed).
 */
extern "C" ExportedByCATSysTS const char *DSYSysCLocaleEnvironGet(char *ioBuffer);


/**
 * @nodoc
 * DSYSysCLocaleIsPerThread.
 * Check wether the locale is private to the current thread or not.
 */
extern "C" ExportedByCATSysTS bool DSYSysCLocaleIsPerThread();

/**
 * @nodoc
 * see also DSYSysCLocaleIsPerThread (to check if enabled for the calling thread).
 */
inline bool DSYSysCLocaleIsPerThreadSupported()
{
#if defined(DSYSysCLocalePerThreadSupport)
    return true;
#else
    return false;
#endif
}

#endif // DSYSysCLocale_H
