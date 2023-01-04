// COPYRIGHT DASSAULT SYSTEMES 2011
#ifndef DSYSysTrace_H
#define DSYSysTrace_H

/************************************************************************/
/* Documentation                                                        */
/************************************************************************/
/*
  //=======================================================================
  // Create a trace object.
  //
  //  @param ioppTraceHandle  Trace handle.
  //  @param iptraceName      Trace name.
  //
  //=======================================================================
  void DSYSysTraceCreate(DSYSysTraceHandle* ioppTraceHandle, const char* ipTraceName);
  //=======================================================================

  //=======================================================================
  // Log info trace.
  //
  //  @param ipTraceHandle    Trace handle that will log the message.
  //  @param iFlag            Activation flag (0 to deactivate, -1 to activate).
  //
  //=======================================================================
  void DSYSysTraceActivate(DSYSysTraceHandle ipTraceHandle, const int iFlag);
  //=======================================================================

  //=======================================================================
  // Log info trace.
  //
  //  @param ipTraceHandle    Trace handle that will log the message.
  //  @param ipMessage        Message to log.
  //
  //=======================================================================
  void DSYSysTraceInfo(DSYSysTraceHandle ipTraceHandle, const char* ipMessage, ...);
  //=======================================================================

  //=======================================================================
  // Log Debug trace.
  //
  //  @param ipTraceHandle    Trace handle that will log the message.
  //  @param ipMessage        Message to log.
  //
  //=======================================================================
  void DSYSysTraceDebug(DSYSysTraceHandle ipTraceHandle, const char* ipMessage, ...);
  //=======================================================================

  //=======================================================================
  // Log warning trace.
  //
  //  @param ipTraceHandle    Trace handle that will log the message.
  //  @param ipMessage        Message to log.
  //
  //=======================================================================
  void DSYSysTraceWarning(DSYSysTraceHandle ipTraceHandle, const char* ipMessage, ...);
  //=======================================================================

  //=======================================================================
  // Log error trace.
  //
  //  @param ipTraceHandle    Trace handle that will log the message.
  //  @param ipMessage        Message to log.
  //
  //=======================================================================
  void DSYSysTraceError(DSYSysTraceHandle ipTraceHandle, const char* ipMessage, ...);
  //=======================================================================

  //=======================================================================
  // Log info or error trace.
  //
  //  @param ipTraceHandle    Trace handle that will log the message.
  //  @param iCondition       Expression. If iCondition is true, an info message is logged, an error message is logged otherwise.
  //  @param ipMessage        Message to log.
  //
  //=======================================================================
  void DSYSysTraceAssert(DSYSysTraceHandle ipTraceHandle, const bool iCondition, const char* ipMessage, ...);
  //=======================================================================

  //=======================================================================
  // Delete a trace object.
  //
  //  @param ioppTraceHandle  Trace handle.
  //
  //=======================================================================
  void DSYSysTraceDelete(DSYSysTraceHandle* ioppTraceHandle);
  //=======================================================================
*/

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#define ExportedByDSYSysTrace  ExportedByCATSysTS

#undef DSY_SYS_TRACE_SOURCE
#define DSY_SYS_TRACE_SOURCE                                            __FILE__, __LINE__

#ifndef CATTraUnActivated
# define CATTraUnActivated                                              CATTraUnactivated
#endif  // CATTraUnActivated

#ifndef TRA_NAME_SIZE
# define TRA_NAME_SIZE                                                  16
#endif

#if !defined(DSYSysTrace)
//# define DSY_SYS_TRACE_SHADOW_ME
# ifdef DSY_SYS_TRACE_SHADOW_ME
#   define DSYSysTrace                                                  DSYSysTraceShadow
# else  // DSY_SYS_TRACE_SHADOW_ME
// ++vxg - 13:06:19 - Rollback for studio.
//#   define DSYSysTrace                                                  DSYSysTraceReal
#   define DSYSysTraceReal                                              DSYSysTrace
// --vxg - 13:06:19
# endif // DSY_SYS_TRACE_SHADOW_ME
#endif  // DSYSysTrace

#if !defined(_Printf_format_string_) && !defined(_WINDOWS_SOURCE)
// This macro is always defined on Windows (Visual Studio 2015+)
// and is used as part of static code analysis when the /analyze compiler switch is set.
# define _Printf_format_string_
#endif

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#ifdef _MK_MODNAME_
# include "CATSysTS.h"
# include "CATDataType.h"
#else // _MK_MODNAME_
# ifdef PLATEFORME_DS64
typedef int CATLONG32;
typedef unsigned int CATULONG32;
# else  // PLATEFORME_DS64
typedef long CATLONG32;
typedef unsigned long CATULONG32;
# endif // PLATEFORME_DS64
#endif  // _MK_MODNAME_

/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

/** Trace type. */
typedef void* DSYSysTraceHandle;

#ifndef CATTrace_H
/** Old trace activation flags */
enum CATTraMode
{
  CATTraActivated   = 1
, CATTraUnactivated = 0
};
#endif  // CATTrace_H

/** Trace options structure. */
# ifdef __cplusplus
extern "C" {
# endif  // __cplusplus
struct DSYSysTraceLineOptions
{
  /// Line options flag.
  unsigned int _LineOpt;

  /// Trace severity.
  int _Severity;

  /// Trace level.
  int _Level;

  /// Source line.
  int _CurrentLine;

  /// Trace name.
  const char* _pTraceName;

  /// End of line set.
  const char* _pEndOfLine;

  /// Source name.
  const char* _pCurrentSrcName;
};
# ifdef __cplusplus
};
# endif  // __cplusplus

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/**
 * @class DSYSysCATTrace
 */
class ExportedByDSYSysTrace DSYSysCATTrace
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /**
   * Constructor (deprecated).
   *
   * Note:  The parameters are widely inspired from the CATTrace class prototype
   *        but only the trace name 'ipName' is used.
   *
   * Note:  Do NOT declare this object as a global or/and static variable. This may cause
   *        hang on WINDOWS platform during crt_init call.
   *        If you want to use this object globally you must declare it as a pointer.
   */
  DSYSysCATTrace  ( const char ipTraceName[TRA_NAME_SIZE]
                  , const char ipComment[] = ""
                  , CATTraMode iDefaultMode = CATTraUnactivated
                  , const char ipDeviceName[]= NULL/*"STDOUT"*/
                  , int iLevelMaxAtInit = 1024);

  /**
   * Destructor.
   */
  virtual ~DSYSysCATTrace();

  /**
   * Get trace configuration flag.
   *
   * @return            1 if active or 0 if not.
   */
  int IsConfigured(void) const
  { return (m_ConfigurationFlag)? 1 : 0; }

  /**
   * Configure trace.
   */
  void Configuration(const int iFlag)
  { m_ConfigurationFlag = (0 != iFlag); }

  /**
   * Get trace activation flag.
   *
   * @return            1 if active or 0 if not.
   */
  int IsActive(void) const
  { return (m_ActivationFlag)? 1 : 0; }

  /**
   * Activate trace.
   */
  void Activate(const int iFlag)
  { m_ActivationFlag = (0 != iFlag); }

  /**
   * Print message without new line ending.
   *
   * @param iLevel      Message level.
   * @param ipMessage   String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int TraPut(const char* ipMessage);
  int TraPut(int iLevel, const char* ipMessage);

  /**
   * Print message without new line ending.
   *
   * @param iLevel      Message level.
   * @param ipMessage   String to print (same syntax as printf family).
   * @param iVal        Interger value.
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int TraPut(const char* ipMessage, CATLONG32 iVal);
  int TraPut(int iLevel, const char* ipMessage, CATLONG32 iVal);

  /**
   * Print message with new line ending.
   *
   * @param iLevel      Message level.
   * @param ipMessage   String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int TraPutLN(const char* ipMessage);
  int TraPutLN(int iLevel, const char* ipMessage);

  /**
   * Print message with new line ending.
   *
   * @param iLevel      Message level.
   * @param ipMessage   String to print (same syntax as printf family).
   * @param iVal        Interger value.
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int TraPutLN(const char* ipMessage, CATLONG32 iVal);
  int TraPutLN(int iLevel, const char* ipMessage, CATLONG32 iVal);

  /**
   * Print message.
   *
   * @param iLevel      Message level.
   * @param ipMessage   String to print (same syntax as printf family)
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int TraPrint(_Printf_format_string_ const char* ipFormat, ...);
  int TraPrint(int iLevel, _Printf_format_string_ const char* ipFormat, ...);

  /**
   * Print message with new line ending.
   *
   * @param iLevel      Message level.
   * @param ipMessage   String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int TraPrintNL(_Printf_format_string_ const char* ipFormat, ...);
  int TraPrintNL(int iLevel, _Printf_format_string_ const char* ipFormat, ...);

protected:
  /// Message format.
  int InternalMessagePrint(DSYSysTraceLineOptions* ipLineOptions, const char* ipMessage, va_list iArgs);

private:
  /// Copy contructor.
  DSYSysCATTrace(const DSYSysCATTrace& iSrc);

  /// Affectation.
  DSYSysCATTrace& operator=(const DSYSysCATTrace& iSrc);

private:
  /// Buil this object.
  int Build(const char* ipTraceName, const char* ipDeviceName = NULL, const unsigned int iTraceLineOptions = 0);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Activation flag.
  bool m_ActivationFlag;

  /// Configuration flag.
  bool m_ConfigurationFlag;

  /// Trace name.
  char* m_pTraceName;

  /// Trace manager.
  void* m_pTraceManagerObject;

  /// Line options object.
  DSYSysTraceLineOptions m_LineOptions;
};

/************************************************************************/
/************************************************************************/

#ifdef DSY_SYS_TRACE_SHADOW_ME
/**
 * @class DSYSysTraceShadow
 */
class ExportedByDSYSysTrace DSYSysTraceShadow
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /**
   * Shadow constructor.
   */
  DSYSysTraceShadow(const char* ipTraceName = NULL)
  { }

  /**
   * Shadow destructor.
   */
  virtual ~DSYSysTraceShadow()
  { }

  /**
   * Print shadow info message.
   */
  int Info(_Printf_format_string_ const char* ipMessage, ...)
  { return -1; }
  int Info(const int iLevel, _Printf_format_string_ const char* ipMessage, ...)
  { return -1; }

  /**
   * Print shadow debug message.
   */
  int Debug(_Printf_format_string_ const char* ipMessage, ...)
  { return -1; }
  int Debug(const int iLevel, _Printf_format_string_ const char* ipMessage, ...)
  { return -1; }

  /**
   * Print shadow warning message.
   */
  int Warning(_Printf_format_string_ const char* ipMessage, ...)
  { return -1; }
  int Warning(const int iLevel, _Printf_format_string_ const char* ipMessage, ...)
  { return -1; }

  /**
   * Print shadowerror message.
   */
  int Error(const char* ipCurrentSrcName, const int iCurrentLine, _Printf_format_string_ const char* ipMessage, ...)
  { return -1; }
  int Error(const char* ipCurrentSrcName, const int iCurrentLine, const int iLevel, _Printf_format_string_ const char* ipMessage, ...)
  { return -1; }

private:
  /// Shadow Copy contructor.
  DSYSysTraceShadow(const DSYSysTraceShadow& iSrc);

  /// Shadow Affectation.
  DSYSysTraceShadow& operator=(const DSYSysTraceShadow& iSrc);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
};
#endif  // !DSY_SYS_TRACE_SHADOW_ME

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysTraceReal
 * @brief: This is the brand-new API for trace.
 */
class ExportedByDSYSysTrace /*DSYSysTraceReal*/DSYSysTrace : protected DSYSysCATTrace
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:
  /// Trace options.
  enum DSYSysTraceLineOption
  {
    /// Timestamp flag.
    ADD_TIMESTAMP = 0x01
#undef DSY_SYS_TRACE_TIMESTAMP
#define DSY_SYS_TRACE_TIMESTAMP DSYSysTrace::ADD_TIMESTAMP

    /// Trace name flag.
  , ADD_TRACENAME = 0x02
#undef DSY_SYS_TRACE_TRACENAME
#define DSY_SYS_TRACE_TRACENAME DSYSysTrace::ADD_TRACENAME

    /// Level flag.
  , ADD_LEVEL = 0x04
#undef DSY_SYS_TRACE_LEVEL
#define DSY_SYS_TRACE_LEVEL DSYSysTrace::ADD_LEVEL

    /// Severity flag.
  , ADD_SEVERITY = 0x08
#undef DSY_SYS_TRACE_SEVERITY
#define DSY_SYS_TRACE_SEVERITY DSYSysTrace::ADD_SEVERITY

    /// Severity flag.
  , ADD_THREADID = 0x10
#undef DSY_SYS_TRACE_THREADID
#define DSY_SYS_TRACE_THREADID DSYSysTrace::ADD_THREADID

    /// Sum-up flag.
  , ADD_SUMP = 0x20
#undef DSY_SYS_TRACE_SUMUP
#define DSY_SYS_TRACE_SUMUP DSYSysTrace::ADD_SUMP
  };

#define DSY_SYS_TRACE_ALL \
  (DSY_SYS_TRACE_TIMESTAMP | DSY_SYS_TRACE_TRACENAME | DSY_SYS_TRACE_LEVEL | DSY_SYS_TRACE_SEVERITY | DSY_SYS_TRACE_THREADID | DSY_SYS_TRACE_SUMUP)

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /**
   * Constructor.
   *
   * @param ipTraceName         Name of the trace.
   *
   * Note:  Do NOT declare this object as a global or/and static variable. This may cause
   *        hang on WINDOWS platform during crt_init call.
   *        If you want to use this object globally you must declare it as a pointer.
   */
  DSYSysTrace(const char* ipTraceName = NULL);

  /**
   * Destructor.
   */
  virtual ~DSYSysTrace();

  /**
   * Get trace configuration flag.
   *
   * @return            1 if active or 0 if not.
   */
  int IsConfigured(void) const
  { return DSYSysCATTrace::IsConfigured(); }

  /**
   * Configure trace.
   */
  void Configuration(const int iFlag)
  { DSYSysCATTrace::Configuration(iFlag); }

  /**
   * Get trace activation flag.
   *
   * @return            1 if active or 0 if not.
   */
  int IsActive(void) const
  { return DSYSysCATTrace::IsActive(); }

  /**
   * Activate trace.
   */
  void Activate(const int iFlag)
  { DSYSysCATTrace::Activate(iFlag); }

  /**
   * Print info message.
   *
   * @param ipMessage   String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int Info(_Printf_format_string_ const char* ipMessage, ...);
  int InfoV(const char* ipMessage, va_list ipArg);

  /**
   * Print debug message.
   *
   * @param ipMessage   String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int Debug(_Printf_format_string_ const char* ipMessage, ...);
  int DebugV(const char* ipMessage, va_list ipArg);

  /**
   * Print warning message.
   *
   * @param ipMessage   String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int Warning(_Printf_format_string_ const char* ipMessage, ...);
  int WarningV(const char* ipMessage, va_list ipArg);

  /**
   * Print error message. You must consider the Error method has the following prototypes:
   *
   *    int Error(DSY_SYS_TRACE_SOURCE, const char* ipMessage, ...);
   *
   * Example:
   *
   *        DSYSysTrace l_MyTrace("my_trace_name");
   *          ...
   *        l_MyTrace.Error(DSY_SYS_TRACE_SOURCE, "My error message.");
   *
   *
   * @param ipCurrentSrcName  Source file name (use __FILE__ value by default).
   * @param iCurrentLine      Source file line (use __LINE__ value by default).
   * @param ipMessage         String to print (same syntax as printf family).
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  int Error(const char* ipCurrentSrcName, const int iCurrentLine, _Printf_format_string_ const char* ipMessage, ...);  
  int ErrorV(const char* ipCurrentSrcName, const int iCurrentLine, const char* ipMessage, va_list ipArg);

private:
  /// Copy contructor.
  DSYSysTrace(const DSYSysTrace& iSrc);

  /// Affectation.
  DSYSysTrace& operator=(const DSYSysTrace& iSrc);
  
  int Info(const int iLevel, _Printf_format_string_ const char* ipMessage, ...);
  int Debug(const int iLevel, _Printf_format_string_ const char* ipMessage, ...);
  int Warning(const int iLevel, _Printf_format_string_ const char* ipMessage, ...);
  int Error(const char* ipCurrentSrcName, const int iCurrentLine, const int iLevel, _Printf_format_string_ const char* ipMessage, ...);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:

};

/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

#if (defined(DEBUG) || defined(_DEBUG)) && !defined(CNEXT_CLIENT)
# define DSY_SYS_TRACE_DEACTIVATED
#else // (DEBUG || _DEBUG) && !CNEXT_CLIENT
# undef DSY_SYS_TRACE_DEACTIVATED
#endif  // (DEBUG || _DEBUG) && !CNEXT_CLIENT

#ifdef DSY_SYS_TRACE_DEACTIVATED
//=======================================================================
# define DSYSysTraceCreate(o, n)                                        \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceActivate(o, f)                                      \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceAssert(o, e, m, ...)                                \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceInfo(o, m, ...)                                     \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceDebug(o, m, ...)                                    \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceWarning(o, m, ...)                                  \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceError(o, m, ...)                                    \
  DSYSysTraceNULL__()
//=======================================================================

//=======================================================================
# define DSYSysTraceDestroy(o)                                          \
  DSYSysTraceNULL__()
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceNULL__(void);
//=======================================================================
#else // DSY_SYS_TRACE_DEACTIVATED
# ifdef _SUNOS_SOURCE
//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceAssert_For_SunOS(const char* ipCurrentSrcName, const int iCurrentLine, ...);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceInfo_For_SunOS(const char* ipCurrentSrcName, const int iCurrentLine, ...);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceDebug_For_SunOS(const char* ipCurrentSrcName, const int iCurrentLine, ...);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceWarning_For_SunOS(const char* ipCurrentSrcName, const int iCurrentLine, ...);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceError_For_SunOS(const char* ipCurrentSrcName, const int iCurrentLine, ...);
//=======================================================================
# endif // _SUNOS_SOURCE
//=======================================================================
# define DSYSysTraceCreate(o, n)                                        \
  DSYSysTraceCreate__(o, n)
//=======================================================================

//=======================================================================
# define DSYSysTraceActivate(o, f)                                      \
  DSYSysTraceActivate__(o, f)
//=======================================================================

//=======================================================================
# ifdef _SUNOS_SOURCE
#   define DSYSysTraceAsset(...)                                        \
  DSYSysTraceAssert_For_SunOS(__FILE__, __LINE__, __VA_ARGS__)
# else  // _SUNOS_SOURCE
// ++IK8 19:08:02
// MSVC: add "printf" in a ternary expression as a trick to enable static analysis/validation of potential variadic arguments specified in "m".
// For Visual Studio 2015+ compiler, works even without the /analyze compiler switch.
// The call to printf will be optimized out in release builds.
// Discard any return value by casting to void
// ++IK8 19:08:02
#   define DSYSysTraceAssert(o, e, m, ...)                              \
  static_cast<void>(false ? static_cast<void>(printf(m, ##__VA_ARGS__)) : static_cast<void>((void *)o ? ((e) ? ((DSYSysTraceReal*)o)->Info(m, ##__VA_ARGS__) : ((DSYSysTraceReal*)o)->Error(__FILE__, __LINE__, m, ##__VA_ARGS__)), true : false))
# endif // _SUNOS_SOURCE
//=======================================================================

//=======================================================================
# ifdef _SUNOS_SOURCE
#   define DSYSysTraceInfo(...)                                         \
  DSYSysTraceInfo_For_SunOS(__FILE__, __LINE__, __VA_ARGS__)
# else  // _SUNOS_SOURCE
// ++IK8 19:08:02
// MSVC: add "printf" in a ternary expression as a trick to enable static analysis/validation of potential variadic arguments specified in "m".
// For Visual Studio 2015+ compiler, works even without the /analyze compiler switch.
// The call to printf will be optimized out in release builds.
// Discard any return value by casting to void
// ++IK8 19:08:02
#   define DSYSysTraceInfo(o, m, ...)                                   \
  static_cast<void>(false ? static_cast<void>(printf(m, ##__VA_ARGS__)) : static_cast<void>((void *)o ? ((DSYSysTraceReal*)o)->Info(m, ##__VA_ARGS__), true : false))
# endif // _SUNOS_SOURCE
//=======================================================================

//=======================================================================
# ifdef _SUNOS_SOURCE
#   define DSYSysTraceDebug(...)                                        \
  DSYSysTraceDebug_For_SunOS(__FILE__, __LINE__, __VA_ARGS__)
# else // _SUNOS_SOURCE
// ++IK8 19:08:02
// MSVC: add "printf" in a ternary expression as a trick to enable static analysis/validation of potential variadic arguments specified in "m".
// For Visual Studio 2015+ compiler, works even without the /analyze compiler switch.
// The call to printf will be optimized out in release builds.
// Discard any return value by casting to void
// ++IK8 19:08:02
#   define DSYSysTraceDebug(o, m, ...)                                  \
  static_cast<void>(false ? static_cast<void>(printf(m, ##__VA_ARGS__)) : static_cast<void>((void *)o ? ((DSYSysTraceReal*)o)->Debug(m, ##__VA_ARGS__), true : false))
# endif // _SUNOS_SOURCE
//=======================================================================

//=======================================================================
# ifdef _SUNOS_SOURCE
#   define DSYSysTraceWarning(...)                                      \
  DSYSysTraceWarning_For_SunOS(__FILE__, __LINE__, __VA_ARGS__)
# else // _SUNOS_SOURCE
// ++IK8 19:08:02
// MSVC: add "printf" in a ternary expression as a trick to enable static analysis/validation of potential variadic arguments specified in "m".
// For Visual Studio 2015+ compiler, works even without the /analyze compiler switch.
// The call to printf will be optimized out in release builds.
// Discard any return value by casting to void
// ++IK8 19:08:02
#   define DSYSysTraceWarning(o, m, ...)                                \
  static_cast<void>(false ? static_cast<void>(printf(m, ##__VA_ARGS__)) : static_cast<void>((void *)o ? ((DSYSysTraceReal*)o)->Warning(m, ##__VA_ARGS__), true : false))
# endif // _SUNOS_SOURCE
//=======================================================================

//=======================================================================
# ifdef _SUNOS_SOURCE
#   define DSYSysTraceError(...)                                        \
  DSYSysTraceError_For_SunOS(__FILE__, __LINE__, __VA_ARGS__)
# else  // _SUNOS_SOURCE
// ++IK8 19:08:02
// MSVC: add "printf" in a ternary expression as a trick to enable static analysis/validation of potential variadic arguments specified in "m".
// For Visual Studio 2015+ compiler, works even without the /analyze compiler switch.
// The call to printf will be optimized out in release builds.
// Discard any return value by casting to void
// ++IK8 19:08:02
#   define DSYSysTraceError(o, m, ...)                                  \
  static_cast<void>(false ? static_cast<void>(printf(m, ##__VA_ARGS__)) : static_cast<void>((void *)o ? ((DSYSysTraceReal*)o)->Error(__FILE__, __LINE__, m, ##__VA_ARGS__), true : false))
# endif // _SUNOS_SOURCE
//=======================================================================

//=======================================================================
# define DSYSysTraceDestroy(o)                                          \
  DSYSysTraceDestroy__(o)
//=======================================================================

//=======================================================================
# define DSYSysTraceDelete                                             \
  DSYSysTraceDestroy
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceCreate__(void** oppTraceObj, const char* ipTraceName);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceActivate__(void* ipTraceObj, const int iFlag);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTrace void DSYSysTraceDestroy__(void** ioppTraceObj);
//=======================================================================
#endif  // DSY_SYS_TRACE_DEACTIVATED

#endif  // DSYSysTrace_H
