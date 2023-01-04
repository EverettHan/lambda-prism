#ifndef XHMACROS_H
#define XHMACROS_H  42400

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

//-----------------------------------------------------------------------------
// Abstract: Definition of error handling macros
//-----------------------------------------------------------------------------
// Usage:    Please refer to the manual for the description of CATTry, CATCatch,
//           CATCatchOthers, CATEndTry, CATThrow and CATRethrow
//-----------------------------------------------------------------------------
// Note:     The implementation of the above macros can use directly the
//           C++ try, catch, throw if the compiler supports it. However,
//           it is advised not to mix code compiled with different
//           implementations
//-----------------------------------------------------------------------------
#include <new> // avoid many errors with exception related keywords (new.h header is deprecated)
#include "CATError.h"
#include "CATXHContext.h"
#include "CATDestruct.h"
#if !defined(NATIVE_EXCEPTION)
#include <setjmp.h>
#endif

#if defined(__clang__)
/** @nodoc clang may pretend to be another compiler, so test it first
__has_feature is expected to be defined */
# if __has_feature(cxx_exceptions)
/** @nodoc */
#define CATXH_CXX_SUPPORT 1
# endif
#elif defined(__GNUC__) && defined(__EXCEPTIONS)
/** @nodoc */
#define CATXH_CXX_SUPPORT 1
#elif defined(_MSC_VER) && defined(_CPPUNWIND)
/** @nodoc */
#define CATXH_CXX_SUPPORT 1
#endif

#if !defined(CATXH_CXX_SUPPORT)
/** @nodoc */
#define CATXH_CXX_SUPPORT 0
#endif

/** @nodoc Macro used for potentially unreferenced variables to prevent "Unused" compiler warning */
#define CATXH_MAYBE_UNUSED(var)    (void)(sizeof(var))

#if defined(_MSC_VER)
/** @nodoc Visual C++ options: /W4 /analyze */
#define CATXH_VAR_SUPPRESS_WARN(VarName, /*DeclareInstruction*/...)\
    __pragma(warning( push ))\
    /* 4456: cf. /W4 warning shadows local variable */\
    /* 6246: cf. /analyze warning shadows local variable */\
    __pragma(warning(disable : 4456 6246))\
    __VA_ARGS__\
    __pragma(warning( pop ))\
    /* Suppress warning unused variable */\
    (void)sizeof(VarName)
#else
/** @nodoc GCC/Clang options: -Wall -Wextra -Wshadow (neither -W nor -Wall enables -Wshadow) */
#define CATXH_VAR_SUPPRESS_WARN(VarName, /*DeclareInstruction*/...)\
    _Pragma("GCC diagnostic push")\
    /* Suppress warning shadows local variable */\
    _Pragma("GCC diagnostic ignored \"-Wshadow\"")\
    __VA_ARGS__\
    _Pragma("GCC diagnostic pop")\
    /* Suppress warning unused variable */\
    (void)sizeof(VarName)
#endif

/** @nodoc required to take the address of variables which type has an overload for the & operator */
template< class T >
T* CATXH_AddressOf(T& arg) 
{
    // cf. std::addressof (but avoids the inclusion of the header <memory>)
    return reinterpret_cast<T*>(
               &const_cast<char&>(
                  reinterpret_cast<const volatile char&>(arg)));
}


/** @nodoc */
namespace CATErrorMacrosTrue
{
    // Used to detect context at compile-time while avoiding polluting the stack with local variables
    constexpr bool __CATCatchBlockType__ = true;
#if !defined( NATIVE_EXCEPTION )
    /** @nodoc */
    constexpr bool __CATTryBlockDeclared__         = true;
    /** @nodoc Use inline functions instead of variable to avoid compiler error: "already declared in this scope" */
    inline constexpr bool __CATCatchBlockDeclared__() {
        return true;
    }
    /** @nodoc CATCatchOthers must be defined at most once - enforced by declaring a variable instead of a function */
    constexpr bool __CATCatchOthersBlockDeclared__ = true;
#endif
}

/** @nodoc */
namespace CATErrorMacrosFalse
{
    // Used to detect context at compile-time while avoiding polluting the stack with local variables
    constexpr bool __CATCatchBlockType__ = false;
#if !defined( NATIVE_EXCEPTION )
    /** @nodoc */
    constexpr bool __CATTryBlockDeclared__         = false;
    /** @nodoc */
    inline constexpr bool __CATCatchBlockDeclared__() {
        return false;
    }
    /** @nodoc */
    constexpr bool __CATCatchOthersBlockDeclared__ = false;
#endif
}


#if !defined(__CATXH_CXX_SUPPORT_DISABLE_CHECK)
    #define __CATXH_CXX_SUPPORT_CHECK   static_assert(CATXH_CXX_SUPPORT, "Requires C++ Exception Handling to be enabled!")
#else
    #define __CATXH_CXX_SUPPORT_CHECK   do { continue; } while(false) /* To prevent any compiler warning */
#endif


#if !defined(CATXH_CGMTkCompat_Disable) && defined(_MOBILE_SOURCE) && !defined(CATXH_CGMTkCompat_Enable)
#define CATXH_CGMTkCompat_Disable
#endif

#if defined(CATXH_CGMTkCompat_Disable)
/** @nodoc */
#define CGMTkCompatTry
/** @nodoc */
#define CGMTkCompatEndTry
#else   // CATXH_CGMTkCompat_Disable
/** @nodoc */
#define CGMTkCompatTry  try {\
                            CATXH_VAR_SUPPRESS_WARN(_cgmTkCompat_, CGMTkCompatCtx _cgmTkCompat_;);

/** @nodoc */
#define CGMTkCompatEndTry   } catch(CATError::ThrowSmartPtr & _spErr_) {\
                                CGMTkCompatCtx::Rethrow(_spErr_);\
                            }
#endif  // CATXH_CGMTkCompat_Disable



/** @nodoc */
#define CATTryCxx                   CGMTkCompatTry\
                                    {\
                                        __CATXH_CXX_SUPPORT_CHECK;\
                                        try {\

/** @nodoc */
#define CATCatchCxx(errclass,errobj)    } catch (typename errclass::ThrowSmartPtr & _spErr_##errobj) {\
                                            errclass *errobj = static_cast<errclass *>(CATXHContextCxx::CatchBlockProlog(/*&_xhctx_*/nullptr,0,_spErr_##errobj));\
                                            CATXH_VAR_SUPPRESS_WARN(_ctxtCatch_, _err_catcatch_info const _ctxtCatch_ = { CATXH_AddressOf(_spErr_##errobj), errobj };);\
                                            using CATErrorMacrosFalse::__CATCatchBlockType__;

/** @nodoc Manages the lifecycle of the exception object automatically (compared to CATCatchCxx) */
#define CATCatchExCxx(errclass,errobj)  } catch (typename errclass::ThrowSmartPtr const & _spErr_##errobj) {\
                                            errclass & errobj = *static_cast<errclass *>(CATXHContextCxx::CatchBlockProlog(/*&_xhctx_*/nullptr,0,_spErr_##errobj));\
                                            CATXH_VAR_SUPPRESS_WARN(_ctxtCatch_, CATError *const _ctxtCatch_ = CATXH_AddressOf(errobj););\
                                            using CATErrorMacrosTrue::__CATCatchBlockType__;

/** @nodoc */
#define CATCatchOthersCxx               } catch (...) {\
                                            CATXH_VAR_SUPPRESS_WARN(_ctxtCatch_, CATError *const _ctxtCatch_ = CATXHContextCxx::CatchBlockProlog(/*&_xhctx_*/nullptr,0););\
                                            using CATErrorMacrosTrue::__CATCatchBlockType__;
                                        

/** @nodoc */
#define CATEndTryCxx                    }\
                                    }\
                                    CGMTkCompatEndTry

// Beware that errobj expression can have side-effects (a new exp. for ex.)
// and thus must evaled only ONCE!
/** @nodoc must support being used as a comma operator operand */
#define CATThrowCxx(errobj)             ([]{ __CATXH_CXX_SUPPORT_CHECK; }(), (errobj)->CATError::ThrowCxx(__FILE__,__LINE__))   

/** @nodoc */
#define CATRethrowCxx                    (CATXHContextCxx::DoRethrow(/*&_xhctx_*/nullptr,0,_ctxtCatch_))


//
// eXception Handling macros
//
#ifdef NATIVE_EXCEPTION     // DO NOT define this in your code!
    
    /** @nodoc */
    #define CATTry          CATTryCxx
    /** @nodoc */
    #define CATCatch        CATCatchCxx
    /** @nodoc */
    #define CATCatchEx      CATCatchExCxx
    /** @nodoc */
    #define CATCatchOthers  CATCatchOthersCxx
    /** @nodoc */
    #define CATEndTry       CATEndTryCxx
    /** @nodoc */
    #define CATThrow        CATThrowCxx
    /** @nodoc */
    #define CATRethrow      CATRethrowCxx
    
    
    /** nodoc NOT(CATXH_CXX_SUPPORT) => NOT(CATXH_CXX_UNWINDING_ON_CATTHROW) */
    #define CATXH_CXX_UNWINDING_ON_CATTHROW     CATXH_CXX_SUPPORT
    
    /** @nodoc compatibility macro */
    #define CATDestructOnExit(class,var,init)   __CATXH_CXX_SUPPORT_CHECK;\
                                                class var init
    /** @nodoc compatibility macro */
    #define CATXH_ENSURE_DESTRUCTION_EXPL(class, var)   CATXH_ENSURE_DESTRUCTION(var)
    /** @nodoc compatibility macro */
    #define CATXH_ENSURE_DESTRUCTION(var)               __CATXH_CXX_SUPPORT_CHECK

#else /* Poor man's exception */

    #ifndef CAT_ENABLE_NATIVE_EXCEPTION
    // Make sure native exception is not used
    /** 
    * This method can't be used.
    */
    #define try                 ERROR
    /** 
    * This method can't be used.
    */
    #define catch               ERROR
    /** 
    * This method can't be used.
    */
    #define throw               ERROR
    #endif
    
    
    /** @nodoc */
    #define CATXHMacrosCheckReset   \
      using CATErrorMacrosFalse::__CATTryBlockDeclared__;\
      using CATErrorMacrosFalse::__CATCatchBlockDeclared__;\
      using CATErrorMacrosFalse::__CATCatchOthersBlockDeclared__;\
      CATXH_MAYBE_UNUSED(__CATTryBlockDeclared__);\
      CATXH_MAYBE_UNUSED(__CATCatchOthersBlockDeclared__);
    
    // Reference the local variable _xhctx_ in the following macros
    // so that they cannot be used out of context (no punt)
    // lots of init is done in CATXHContext constructor
    /**
    * Begin of block CNEXT exceptions.
    * @see CATEndTry
    */
    #define CATTry \
    {\
      /*using-declarations: set or reset (cf. enclosing CATTry/CATCatch/CATCatchOthers block) */\
      CATXHMacrosCheckReset\
      {\
        using CATErrorMacrosTrue::__CATTryBlockDeclared__;\
        CATXH_VAR_SUPPRESS_WARN(_xhctx_, CATXHContext _xhctx_;);\
        CATXH_VAR_SUPPRESS_WARN(_bUncaughtException_, volatile bool _bUncaughtException_ = false;); /* Here, the volatile specifier mitigates potential optimizations */\
        /* that may break invalid code that writes to NON-volatile local variables in CATTry and then attempts to read them in CATCatch blocks */\
        if(setjmp(*_xhctx_.GetJmpbuf()) != 0) /* WARNING: setjmp is not a regular function and its use cases are limited!*/\
           _bUncaughtException_ = true; /* path after longjmp */\
        else {\
            /*Try block*/\
            CATXHMacrosCheckReset

    // errClass:Self is called to ensure that errclass has been defined
    // correctly using the class definition macros
    // The "_ctxtErr_" variable ensures that errclass is a CATError-derived type
    #define __CATCatch(errclass)    \
        }/* Close previous CATTry/CATCatch/CATCatchOthers block*/\
        /* Compile-time checks */\
        static_assert( __CATTryBlockDeclared__, "no CATTry block associated with this CATCatch handler");\
        static_assert(!__CATCatchOthersBlockDeclared__, "'" #errclass " *': is caught by previous CATCatchOthers block");\
        struct __CATCatchBlock_ ## errclass {};/*catch-block unicity check*/\
        /* using-declarations */\
        using CATErrorMacrosTrue::__CATCatchBlockDeclared__;\
        /* catch block */\
        if (_bUncaughtException_ && _xhctx_.GetError()->IsAKindOf (errclass::ClassName())) {\
          _bUncaughtException_ = false;\
          CATXH_VAR_SUPPRESS_WARN(_ctxtErr_, CATError *_ctxtErr_ = _xhctx_.GetError(););\
          CATXHMacrosCheckReset\
          
    
    /**
    * Catch CNEXT specific exceptions.
    */
    #define CATCatch(errclass,errobj)               \
        __CATCatch(errclass)                        \
        errclass *errobj = ((errclass *)_ctxtErr_)->errclass::Self ();  \
        using CATErrorMacrosFalse::__CATCatchBlockType__;
    
    /**
    * Catch CNEXT specific exceptions.
    */
    #define CATCatchEx(errclass,errobj)             \
        __CATCatch(errclass)                        \
        errclass & errobj = *((errclass *)_ctxtErr_)->errclass::Self ();\
        using CATErrorMacrosTrue::__CATCatchBlockType__;  \
        CATXH_VAR_SUPPRESS_WARN(_ce_, _err_cleaner_ _ce_(_ctxtErr_);); __CATXH_ENSURE_DESTRUCT_REENTRANT(_ce_);
        

    /**
    * Catch CNEXT exceptions.
    */
    #define CATCatchOthers  \
        }/* Close previous CATTry/CATCatch block*/\
        /* Compile-time checks */\
        static_assert( __CATTryBlockDeclared__, "no CATTry block associated with this CATCatchOthers handler");\
        struct __CATCatchOthersBlock {};/*catch-block unicity check*/\
        /* using-declarations */\
        using CATErrorMacrosTrue::__CATCatchOthersBlockDeclared__;\
        /* catch block */\
        if (_bUncaughtException_ && _xhctx_.GetError()) {\
            _bUncaughtException_ = false;\
            CATXH_VAR_SUPPRESS_WARN(_ctxtErr_, CATError *_ctxtErr_ = _xhctx_.GetError(););\
            CATXH_VAR_SUPPRESS_WARN(_ce_, _err_cleaner_ _ce_(_ctxtErr_);); __CATXH_ENSURE_DESTRUCT_REENTRANT(_ce_);\
            CATXHMacrosCheckReset\
            using CATErrorMacrosTrue::__CATCatchBlockType__;

    /**
    * End of block CNEXT exceptions.
    * @see CATTry
    */
    #define CATEndTry       \
        }/* Close previous CATCatch/CATCatchOthers block*/\
        /* Compile-time checks */\
        static_assert(__CATTryBlockDeclared__, "no CATTry macro associated with this CATEndTry macro");\
        static_assert(__CATCatchBlockDeclared__() || __CATCatchOthersBlockDeclared__, "'CATTry' block has no CATCatch/CATCatchOthers handlers");\
        if (_bUncaughtException_) {\
            /* Dead code if either a CATCatch(CATError) or a CATCatchOthers has been previously defined */\
            CATXH_VAR_SUPPRESS_WARN(_ctxtErr_, CATError *_ctxtErr_ = _xhctx_.GetError(););\
            CATRethrow;\
        }\
      }\
    }
    
    // Beware that errobj expression can have side-effects (a new exp. for ex.)
    // and thus must evaled only ONCE!
    /** @nodoc */
    #define CATThrow(errobj)            (errobj)->CATError::Throw(__FILE__,__LINE__)
    /** @nodoc The "_ctxtErr_" variable prevents calling erroneously CATRethrow outside of CATCatch/CATCatchOthers blocks 
        must need to support being used as a comma operator operand - noexcept important when CATXH_CXX_UNWINDING_ON_CATTHROW */
    #define CATRethrow                  (_ctxtErr_)->CATError::Throw(NULL, 0)



    #if defined(_MSC_VER) && (CATXH_CXX_SUPPORT != 0)
    /* Visual C++ will handle stack unwinding for setjmp/longjmp */
    
    /** nodoc NOT(CATXH_CXX_SUPPORT) => NOT(CATXH_CXX_UNWINDING_ON_CATTHROW) */
    #define CATXH_CXX_UNWINDING_ON_CATTHROW     CATXH_CXX_SUPPORT
    
    /** @nodoc */
    #define CATDestructOnExit(class,var,init)   class var init
    /** @nodoc */
    #define CATXH_ENSURE_DESTRUCTION_EXPL(class, var)   CATXH_ENSURE_DESTRUCTION(var)
    /** @nodoc */
    #define CATXH_ENSURE_DESTRUCTION(var)               do { continue; } while(false) /* To prevent any compiler warning */

    #else   /* Automatic Stack unwinding disabled */
    
    /** nodoc NOT(CATXH_CXX_SUPPORT) => NOT(CATXH_CXX_UNWINDING_ON_CATTHROW) */
    #define CATXH_CXX_UNWINDING_ON_CATTHROW     0
    
    /** @nodoc */
    #define CATDestructOnExit(class,var,init)\
        class var init;                \
        CATDestruct_<decltype(var)> var##Destructor(CATXH_AddressOf(var))
    /** @nodoc */
    #define CATXH_ENSURE_DESTRUCTION_EXPL(class, var) CATDestruct_<class> var##Destructor (CATXH_AddressOf(var))
    /** @nodoc */
    #define CATXH_ENSURE_DESTRUCTION(var)  CATXH_ENSURE_DESTRUCTION_EXPL(decltype(var), var)
    
    #endif
    
    
#if defined(_MSC_VER) && (_MSC_VER < 1926)
    // To bypass Visual C++ 2017 bugs when (CATXH_CXX_SUPPORT != 0)... IMPORTANT: "var" may be destructed more than once!
    #define __CATXH_ENSURE_DESTRUCT_REENTRANT(var)  CATDestruct_<decltype(var)> var##Destructor(CATXH_AddressOf(var))
#else
    #define __CATXH_ENSURE_DESTRUCT_REENTRANT(var)  CATXH_ENSURE_DESTRUCTION(var)
#endif

#endif  // NATIVE_EXCEPTION


/** @nodoc */
struct _err_cleaner_
{ 
    ExportedByJS0ERROR _err_cleaner_(CATError*e);
    ExportedByJS0ERROR ~_err_cleaner_();
    static void EnsureOwnerShipForThrow(CATError *e);
private:
    CATError *m_err;
    _err_cleaner_ *m_prev;
};


/** @nodoc */
struct _err_catcatch_info {
    CATError::ThrowSmartPtr *m_pExcObj;
    CATError *m_pErr;
};


/** @nodoc */
struct CGMTkCompatCtx
{
    ExportedByJS0ERROR  CGMTkCompatCtx() noexcept;
    ExportedByJS0ERROR ~CGMTkCompatCtx() noexcept;
    [[noreturn]] ExportedByJS0ERROR static void Rethrow(CATError::ThrowSmartPtr &);
};


#endif  // XHMACROS_H
