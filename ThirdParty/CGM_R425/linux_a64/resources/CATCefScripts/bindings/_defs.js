/*! Copyright Dassault Systemes 2018 */

/**
 * Global namespace for all bindings, registered as a v8 extension.
 * @example <caption>Use this to check for its existence in webapp contexts.</caption>
 * typeof(dscef) !== 'undefined'
 * @namespace dscef
 */
var dscef = {};

// Native functions are declared in this IIFE to avoid exposing them in a global context.
(() => {
  // Public functions.
  native function __sendString();
  native function __loadHomepage();
  native function __openDevTools();
  native function __closeDevTools();
  native function __showNotification();
  native function __getEnv();
  native function __getMyAppsURL();
  native function __saveValue();
  native function __loadValue();
  native function __getElementOffset();

  // Private functions.
  native function __notifyDOMReady();
  native function __notifyLoad();
  native function __notifyUnload();
  native function __notifyZoomChange();
  native function __notifyZoomReset();
  native function __registerPromise();
  native function __resolvePromise();
  native function __rejectPromise();

  // Functions for CATRecord/WebRecord tests.
  native function __startRecordManager();
  native function __startInteractionInterpreter();
  native function __loadAnalyzerStyles();
  native function __isRecording();
  native function __isReplaying();
  native function __fileExists();
  native function __capture();
  native function __replay();
  native function __handleReplayResult();
  native function __abort();
  native function __notifyInterpreterLoad();
  native function __pauseReplay();
  native function __resumeReplay();

  // Functions for all tests: WebRecord and Jasmine.
  native function __coverageEnabled();
  native function __collectCoverage();

  dscef = {
    __native__: {
      __sendString,
      __loadHomepage,
      __openDevTools,
      __closeDevTools,
      __showNotification,
      __getEnv,
      __getMyAppsURL,
      __saveValue,
      __loadValue,
      __getElementOffset,

      __notifyDOMReady,
      __notifyLoad,
      __notifyUnload,
      __notifyZoomChange,
      __notifyZoomReset,
      __registerPromise,
      __resolvePromise,
      __rejectPromise,

      __startRecordManager,
      __startInteractionInterpreter,
      __loadAnalyzerStyles,
      __isRecording,
      __isReplaying,
      __fileExists,
      __capture,
      __replay,
      __handleReplayResult,
      __abort,
      __notifyInterpreterLoad,
      __pauseReplay,
      __resumeReplay,

      __coverageEnabled,
      __collectCoverage
    }
  };
})();
