// COPYRIGHT DASSAULT SYSTEMES 2012
#ifndef DSYSysNeutralCore_H
#define DSYSysNeutralCore_H
/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#define ExportedByDSYSysNeutralCore ExportedByCATSysTS

#if defined(DSYINSTARCH) || defined (HTTPARCH) || defined(__CATBBMagic)
# undef  ExportedByDSYSysNeutralCore
# define ExportedByDSYSysNeutralCore
#endif  // DSYINSTARCH || HTTPARCH

#define DSY_SYS_NEUTRAL_CORE_THISMODULE_NAME(m)                         DSY_SYS_NEUTRAL_CORE_THISMODULE_NAME_(m)
#define DSY_SYS_NEUTRAL_CORE_THISMODULE_NAME_(m)                        #m

#define DSY_SYS_NEUTRAL_CORE_DUMMY_TOKEN_PASTE(x, y)                    DSY_SYS_NEUTRAL_CORE_DUMMY_TOKEN_PASTE_(x, y)
#define DSY_SYS_NEUTRAL_CORE_DUMMY_TOKEN_PASTE_(x, y)                   x ## y

#define DSY_SYS_NEUTRAL_CORE_NEW_DLMAIN_DECLARE__(ctor, schg, scall)    \
                                                                        \
  void ctor(void* ipUserData);                                          \
  void schg(const int iStateId);                                        \
                                                                        \
  DSYSysNeutralCoreDynamicMain DSY_SYS_NEUTRAL_CORE_DUMMY_TOKEN_PASTE(_MK_MODNAME_, DlMain)  \
                              ( DSY_SYS_NEUTRAL_CORE_THISMODULE_NAME(_MK_MODNAME_) \
                              , ctor                                    \
                              , schg                                    \
                              , scall);

/**
 * Life cycle macro for libraries.
 */
#define DSY_SYS_NEUTRAL_CORE_SHARED_LIBRARY_MAIN(ctor, schg, scall)     \
  DSY_SYS_NEUTRAL_CORE_NEW_DLMAIN_DECLARE__(ctor, schg, scall);

/**
 * Macro for application's main declaration.
 */
#ifdef _WINDOWS_SOURCE
# define DSY_SYS_NEUTRAL_CORE_APPLICATION_MAIN(ctor, schg, scall)       \
  int WINAPI WinMain  ( HINSTANCE hInstance                             \
                      , HINSTANCE hPrevInstance                         \
                      , LPSTR lpCmdLine                                 \
                      , int nCmdShow)                                   \
  {                                                                     \
    return DSYSysNeutralCoreApplicationMain ( (void *)hInstance         \
                                          , ctor, schg, scall);         \
  }
#else // _WINDOWS_SOURCE
# define DSY_SYS_NEUTRAL_CORE_APPLICATION_MAIN                          DSYSysNeutralCoreApplicationMain
#endif  // _WINDOWS_SOURCE

/**
 * Macro for application's main declaration (console).
 */
#if defined(_MOBILE_SOURCE)
# undef DSY_SYS_NEUTRAL_CORE_CONSOLE_SOURCE
# undef DSY_SYS_NEUTRAL_CORE_DESKTOP_SOURCE
# define DSY_SYS_NEUTRAL_CORE_CONSOLE_MAIN(ctor, schg, scall)
#else // _MOBILE_SOURCE
# define DSY_SYS_NEUTRAL_CORE_CONSOLE_SOURCE
# define DSY_SYS_NEUTRAL_CORE_DESKTOP_SOURCE
# define DSY_SYS_NEUTRAL_CORE_CONSOLE_MAIN(ctor, schg, scall)           \
  int main(int argc, char** argv, char** envp)                          \
  {                                                                     \
    return DSYSysNeutralCoreApplicationDesktopMain  ( argc              \
                                                    , argv              \
                                                    , envp              \
                                                    , ctor, schg, scall); \
  }
#endif  // _MOBILE_SOURCE

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <stdlib.h>
#ifdef _WINDOWS_SOURCE
# include <windows.h>
#else // _WINDOWS_SOURCE
# ifdef _ANDROID_SOURCE
#   include <jni.h>
#   include <assert.h>
#   include <pthread.h>
#   include <stdio.h>
#   include <string.h>
#   include <dlfcn.h>

#   include <android/log.h>
#   include <android/Configuration.h>
#   include <android/asset_manager_jni.h>
#   include <android/native_window_jni.h>
# endif // _ANDROID_SOURCE
#endif  // _WINDOWS_SOURCE

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "CATSysTS.h"
#include "DSYSysLifeCycle.h"

/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/////////////////////////////////////////////////////////////////////////
/// TO BE MOVED
/////////////////////////////////////////////////////////////////////////
/// THESE PROTOTYPES MUST BE DEFINED IN PRIVATE INTERFACES. FOR NOW AS
/// SYSTEM FW DOES NOT HAVE SYSTEMTS IN PREREQUISTE COMPONENT, WE PUT IN
/// PROTECTED INTERFACES.
/////////////////////////////////////////////////////////////////////////
//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationIsEnvironmentVariableReady(int* opFlag);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore char* DSYSysNeutralCoreApplicationGetOfficialEnvironmentVariableA(const char* ipOffVarName);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore char* DSYSysNeutralCoreApplicationGetEnvironmentVariableA(const char* ipVarName);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationPutEnvironmentVariableA(const char* ipKey, const char* ipValue);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore char** DSYSysNeutralCoreApplicationGetArgumentsA(int* opArgc);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationLifeCycleExitSuccess(void);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationLifeCycleExitFailure(void);
//=======================================================================

#ifdef _IOS_SOURCE
//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationGetSystemVersionMajor(void);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationGetSystemVersionMinor(void);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationGetSystemVersionPatch(void);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore void DSYSysNeutralCoreApplicationSetMainRunLoop(void* ipRunLoopAddr);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore void DSYSysNeutralCoreApplicationGetMainRunLoop(void** oppRunLoopAddr);
//=======================================================================
#endif  // _IOS_SOURCE

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationInTestMode(void);
//=======================================================================

//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationGetUTBIsOn(void);
//=======================================================================
/////////////////////////////////////////////////////////////////////////
/// TO BE MOVED
/////////////////////////////////////////////////////////////////////////

#ifdef _ANDROID_SOURCE
//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationAndroidMain(void* ipAppObj, const char* ipClassName);
//=======================================================================
#else // _ANDROID_SOURCE
//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationMain  ( void* ipUserData
                                                                  , DSYSysLifeCycleCreateFunc_t ipCreateFunc
                                                                  , DSYSysLifeCycleStateChangeFunc_t ipStateChangeFunc
                                                                  , DSYSysLifeCycleSystemCallFunc_t ipSystemCallFunc);
//=======================================================================

# if !defined(_MOBILE_SOURCE)
//=======================================================================
ExportedByDSYSysNeutralCore int DSYSysNeutralCoreApplicationDesktopMain ( int argc
                                                                        , char** argv
                                                                        , char** envp
                                                                        , DSYSysLifeCycleCreateFunc_t ipOnCreateFunc
                                                                        , DSYSysLifeCycleStateChangeFunc_t ipStateChangeFunc
                                                                        , DSYSysLifeCycleSystemCallFunc_t ipSystemCallFunc);
//=======================================================================
# endif // !_MOBILE_SOURCE
#endif  // _ANDROID_SOURCE

#ifdef __cplusplus
};
#endif // __cplusplus

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus
/**
 * @struct DSYSysNeutralCoreAppEngineStruct
 */
struct DSYSysNeutralCoreAppEngineStruct
{
#ifdef _ANDROID_SOURCE
  /// Life cycle state.
  int _LifeCycleState;

  /// Asset manager.
  AAssetManager* _pAssetManager;

  /// Configuration.
  AConfiguration* _pConfiguration;

  /// JAVA virtual machine object.
  JavaVM* _pJavaVM;

  /// JNI environment object
  JNIEnv* _pJNIEnv;

  /// Class object.
  jobject _pClassObj;

  /// Main window.
  jobject _pWindow;
#else // _ANDROID_SOURCE
  /// Main window.
  void* _pWindow;
#endif  // _ANDROID_SOURCE
};
#ifdef __cplusplus
};
#endif // __cplusplus

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysNeutralCoreDynamicMain
 */
class ExportedByDSYSysNeutralCore DSYSysNeutralCoreDynamicMain
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor.
  DSYSysNeutralCoreDynamicMain  ( const char* ipLibraryName
                                , DSYSysLifeCycleCreateFunc_t ipCreateFunc
                                , DSYSysLifeCycleStateChangeFunc_t ipStateChangeFunc = NULL
                                , DSYSysLifeCycleSystemCallFunc_t ipSystemCallFunc = NULL
                                , const unsigned short iPriority = 0/*DSY_SYS_LIFECYCLE_ORIGIN*/);

  /// Destructor.
  virtual ~DSYSysNeutralCoreDynamicMain();

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Calllbacks structure.
  void* m_pFunc;

  /// Library name.
  char* m_pMyLibraryName;
};
#endif  // DSYSysNeutralCore_H
