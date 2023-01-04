#ifndef DSYSysAndroid_H
#define DSYSysAndroid_H

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
// Force symbol export.
#define DSYExport                               __attribute__ ((visibility("default")))
#define DSYImport                               __attribute__ ((visibility("default")))

#if defined(__DSYSysAndroid)
# define ExportedByDSYSysAndroid                DSYExport
#else // __DSYSysAndroid
# define ExportedByDSYSysAndroid                DSYImport
#endif  // __DSYSysAndroid

#define DSYSYSANDROID_LOGI(...)                 ((void)__android_log_print(ANDROID_LOG_INFO, "DSYSysAndroid", __VA_ARGS__))
#define DSYSYSANDROID_LOGW(...)                 ((void)__android_log_print(ANDROID_LOG_WARN, "DSYSysAndroid", __VA_ARGS__))

// Custom command indicating idle state.
#define APP_CMD_CUSTOM_CREATE                   50
// Custom command indicating idle state.
#define APP_CMD_CUSTOM_IDLE                     51
// Custom command for user looper events.
#define APP_CMD_CUSTOM_LOOPER_USER              52

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include <jni.h>
#include <errno.h>
#include <cassert>
#include <dlfcn.h>
#include <android/sensor.h>
#include <android/log.h>
//++vxg - 18:08:24 - Waiting to use it in official DS tools.
#ifdef _MK_MODNAME_
# include "tmp_android_native_app_glue.h"
#else   // _MK_MODNAME_
# include <android_native_app_glue.h>
#include <unistd.h>
#endif  // _MK_MODNAME_
//++vxg - 18:08:24 - Waiting to use it in official DS tools.

/************************************************************************/
/* Forward declarations                                                 */
/************************************************************************/

//=======================================================================
struct android_app;
//=======================================================================

//=======================================================================
struct AInputEvent;
//=======================================================================

//=======================================================================
struct DSYSysAndroidEngine;
//=======================================================================

/************************************************************************/
/* Types definition                                                     */
/************************************************************************/

//=======================================================================
typedef void (*fAndroidMain_t)(DSYSysAndroidEngine*, const int);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
typedef void (*fDeprectedOnCreate_t)(void*);
//=======================================================================

//=======================================================================
typedef void (*fDeprectedOnStateChange_t)(const int);
//=======================================================================

//=======================================================================
typedef void (*fDeprectedOnSystemCall_t)(const int);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
typedef int32_t (*dsysys_android_engine_handle_input)(const struct DSYSysAndroidEngine&, AInputEvent*);
//=======================================================================

/************************************************************************/
/* Structures declaration                                               */
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
 * @struct android_app_ds
 */
struct android_app_ds;

/**
 * @struct android_app_ds
 */
struct android_app_ds_deprecated_lifecycle
{
  /// Create entry point.
  fDeprectedOnCreate_t _fOnCreate;

  /// Status change entry point.
  fDeprectedOnStateChange_t _fOnStateChange;

  /// System call entry point.
  fDeprectedOnSystemCall_t _fSystemChange;
};

/**
 * @struct DSYSysAndroidEngine
 */
struct DSYSysAndroidEngine
{
  /// Pure native activity.
  int _PureNative;

  /// App instance (default native structure).
  struct android_app *_pApp;

  /// App private instance.
  struct android_app_ds *_pAppDS;

  /// App extension.
  void *_pAppExt;

  /// App main entry point.
  fAndroidMain_t _fMain;

  /// Function to process input events.
  dsysys_android_engine_handle_input _fInput;

  /// Life cycle entry points (old style).
  android_app_ds_deprecated_lifecycle _OldLifeCycle;
};

#ifdef __cplusplus
};
#endif  // __cplusplus

/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

//=======================================================================
extern "C" ExportedByDSYSysAndroid JNIEnv* DSYSysAndroidCurrentThreadAttach(const struct DSYSysAndroidEngine* ipEngine);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysAndroid void DSYSysAndroidCurrentThreadDetach(const struct DSYSysAndroidEngine* ipEngine);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
extern "C" ExportedByDSYSysAndroid char*  DSYSysAndroidGetMetaData(struct DSYSysAndroidEngine* ipEngine, const char* ipMetaDataName);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
/*
 *    Workaround ASensorManager_getInstance() deprecation false alarm
 *    for Android-N and before, when compiling with NDK-r15
 */
extern "C" ExportedByDSYSysAndroid ASensorManager* DSYSysAndroidAcquireASensorManagerInstance(android_app* app);
//=======================================================================

#endif //DSYSysAndroid_H
