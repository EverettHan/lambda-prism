/* global dscef */
/* eslint no-console: off */

// Avoid references to the DOM or loading the extension will terminate the process.
(() => {
  'use strict';

  Object.assign(dscef, {
    /**
     * Sends one or several string objects to the native client.
     * @function sendString
     * @memberof dscef
     * @param {...String} params
     * String data that will be sent to the native controller.
     * @param {Object} [options]
     * Optional parameters for the function.
     * @param {Boolean} [options.recordable=false]
     * If true, the data will be captured for Record ODTs.
     * Else, it is ignored.
     * @param {Boolean} [options.captureAll=true]
     * This option is taken into account only if options.recordable is true.
     * If true, all arguments will be captured for Record ODTs.
     * Else, only the first argument will be captured.
     * @return {undefined}
     */
    sendString: (...params) => {
      log('sendString', params);

      // Final arguments for SendString().
      let origin = { url: '<anonymous>', line: 1, column: 1 };
      let args = [];
      let options = {};

      const argCount = params.length;

      // Check the arguments.
      if (argCount < 1) {
        throw new Error('The sendString() function needs at least one argument.');
      }

      for (let i = 0; i < argCount; ++i) {
        const current = params[i];
        const isLast = i === argCount - 1;

        // The last argument can be a string or the options object.
        if (isLast && typeof current === 'object') {
          options = current;
          continue;
        }

        checkType(i, current, 'string', 'sendString');

        args.push(current);
      }

      // Line 0: error creation in _trace().
      // Line 1: _trace() call in dscef function.
      // > Line 2: dscef function call.
      const location = trace(2);

      if (location) {
        origin.url = location.url;
        origin.line = Number.parseInt(location.line, 10);
        origin.column = Number.parseInt(location.column, 10);
      }

      dscef.__native__.__sendString(args, origin, options);
    },

    /**
     * Loads the homepage set by the native client.
     * @function loadHomepage
     * @memberof dscef
     * @return {undefined}
     */
    loadHomepage: () => {
      log('loadHomepage');
      dscef.__native__.__loadHomepage();
    },

    /**
     * Opens the developer tools in a popup window.
     * @function openDevTools
     * @memberof dscef
     * @return {undefined}
     */
    openDevTools: () => {
      log('openDevTools');
      dscef.__native__.__openDevTools();
    },

    /**
     * Closes the developer tools window associated with the current browser.
     * @function closeDevTools
     * @memberof dscef
     * @return {undefined}
     */
    closeDevTools: () => {
      log('closeDevTools');
      dscef.__native__.__closeDevTools();
    },

    /**
     * Sends a message that will be displayed as a visual notification
     * by the native client.
     * @function showNotification
     * @memberof dscef
     * @param {String} type
     * The type of notification. It can be: 'info', 'warning', 'error' or 'critical'.
     * @param {String} text
     * The text that will be displayed by the notification.
     * @param {Number} duration
     * The display duration in seconds.
     * @return {undefined}
     */
    showNotification: (type, text, duration) => {
      log('showNotification', [type, text, duration]);

      checkType(0, type, 'string', 'showNotification');
      checkType(1, text, 'string', 'showNotification');
      checkType(2, duration, 'number', 'showNotification');

      dscef.__native__.__showNotification(type, text, duration);
    },

    /**
     * Returns the value of an environment variable.
     * @function getEnv
     * @memberof dscef
     * @param {String} name
     * The name of the wanted variable.
     * @return {String}
     * The value of the wanted variable.
     */
    getEnv: (name) => dscef.__native__.__getEnv(name),

    /**
     * Returns a root URL that is required to use web services on MyApps.
     * @return {Promise}
     * A Promise that can be resolved with a URL for MyApps.
     */
    getMyAppsURL: () => dscef._internals.promisify(dscef.__native__.__getMyAppsURL),

    /**
     * Saves any value on disk using a CATSysPreferenceRepository.
     * @param {String} name
     * A unique identifier for the value.
     * @param {*} value
     * A JS value of any type, except `undefined`, `function` and `symbol`.
     * @return {Promise<void>}
     * A promise that resolves if the value was saved
     * or rejects with an error describing the issue.
     */
    saveValue: (name, value) => {
      if (typeof name !== 'string' || name.length < 1) {
        return Promise.reject(
          new Error('1st argument is invalid: the name should be a non-empty string')
        );
      }

      const type = typeof value;
      if (type === 'undefined' || type === 'function' || type === 'symbol') {
        return Promise.reject(
          new Error('2nd argument is invalid: unsupported type (' + type + ')')
        );
      }

      return dscef._internals.promisify(dscef.__native__.__saveValue, {
        origin: encodeURIComponent(window.location.origin),
        name: name,
        value: JSON.stringify(value),
      });
    },

    /**
     * Loads the value identified by the `name` parameter using a CATSysPreferenceRepository.
     * @param {String} name
     * The unique identifier for the value.
     * @return {Promise<*>}
     * A promise that resolves with the targeted value
     * or rejects with an error describing the issue.
     */
    loadValue: (name) => {
      if (typeof name !== 'string' || name.length < 1) {
        return Promise.reject(
          new Error('1st argument is invalid: the name should be a non-empty string')
        );
      }

      return dscef._internals.promisify(dscef.__native__.__loadValue, {
        origin: encodeURIComponent(window.location.origin),
        name: name,
      });
    },

    /**
     * Gathers all private attributes and functions.
     * @private
     */
    _internals: {
      /**
       * From the top frame, use document.elementFromPoint to fetch the topmost element
       * at the given coordinates and return its position.
       * Can be used from iframe contexts to know their offset on the main document.
       * For security reasons, iframes usually cannot access that information.
       * @private
       * @return {?Object} { x, y } or null
       */
      getElementOffset: (x, y) => dscef.__native__.__getElementOffset(x, y),
      /**
       * Private callback to dispatch a native event on the `DOMContentLoaded` event.
       * We still have to expose it or addEventListener won't find it.
       * @private
       * @return {undefined}
       */
      notifyDOMReady: () => dscef.__native__.__notifyDOMReady(),
      /**
       * Private callback to dispatch a native event on the `load` event.
       * @private
       * @return {undefined}
       */
      notifyLoad: () => dscef.__native__.__notifyLoad(),
      /**
       * Private callback to dispatch a native event on the `unload` event.
       * @private
       * @return {undefined}
       */
      notifyUnload: () => dscef.__native__.__notifyUnload(),
      /**
       * Private callback to dispatch a native event on zoom changes
       * triggered by a keyboard or a mouse.
       * @param {Number} delta
       * The increment on the current zoom value.
       * @private
       * @return {undefined}
       */
      notifyZoomChange: (delta) => {
        checkType(0, delta, 'number', 'notifyZoomChange');
        dscef.__native__.__notifyZoomChange(delta);
      },
      /**
       * Private callback to dispatch a native event on zoom reset.
       * @private
       * @return {undefined}
       */
      notifyZoomReset: () => dscef.__native__.__notifyZoomReset(),
      /**
       * Wraps a native function with a promise.
       * The target function should be implemented with as:
       *   `function target(Number: promiseKey, Array: args)`
       * @private
       * @param {Function} func
       * The function that should resolve or reject the promise.
       * @param {Object} args
       * The arguments for the wrapped function, as named properties.
       * @return {Promise}
       * A promise that will resolve with the wrapped function's return value
       * or reject with an error.
       */
      promisify: (func, args) =>
        new Promise(function (resolve, reject) {
          const promiseKey = registerPromise(new PromiseExecutor(resolve, reject));
          func(promiseKey, args);
        }),
      /**
       * Private helper for resolving Promise objects
       * that are stored in one of the C++ handlers.
       * @param {Number} key
       * Unique identifier for the Promise object.
       * @param {*} value
       * The result for the resolved Promise.
       * @private
       * @return {undefined}
       */
      resolvePromise: (key, value) => dscef.__native__.__resolvePromise(key, value),
      /**
       * Private helper for rejecting Promise objects
       * that are stored in one of the C++ handlers.
       * @param {Number} key
       * Unique identifier for the Promise object.
       * @param {*} reason
       * The reason why the Promise has been rejected.
       * @private
       * @return {undefined}
       */
      rejectPromise: (key, reason) => dscef.__native__.__rejectPromise(key, reason),
      /**
       * Private helper to rethrow an error.
       * This is a bypass for converting a `CefV8Value` into a `CefV8Exception` in C++.
       * @param {Error} error
       * @private
       * @throws {Error} The error that was given as a parameter
       */
      rethrow: (error) => {
        throw error;
      },
      /**
       * Fixed multiplier for CEF scroll steps.
       * @const {Number}
       * @private
       * @readonly
       */
      SCROLL_STEP: 50,
    },
  });

  // ------------------------------------------------------------------------
  // Helper functions.
  // ------------------------------------------------------------------------

  /**
   * Type checking for function arguments.
   * @param {Number} argIndex
   * Argument index (for logging only).
   * @param {*} arg
   * Argument object to check.
   * @param {String} expectedType
   * Expected type for the argument.
   * @param {String} functionName
   * Name of the called function (for logging only).
   */
  function checkType(argIndex, arg, expectedType, functionName) {
    const argType = typeof arg;

    if (argType !== expectedType) {
      throw new TypeError(
        'Argument ' +
          String(argIndex + 1) +
          ' for function ' +
          functionName +
          '() should be of type: ' +
          expectedType +
          '. Actual type is: ' +
          argType
      );
    }
  }

  /**
   * Wrapper class for promise executor functions that carry a resolver and a rejector
   * to defer their execution in a native V8 handler.
   */
  class PromiseExecutor {
    /**
     * Creates a PromiseExecutor object.
     * @param {Function} resolve
     * Resolver for a Promise.
     * @param {Function} reject
     * Rejector for a Promise.
     */
    constructor(resolve, reject) {
      this.resolve = resolve;
      this.reject = reject;
    }
  }

  /**
   * Registers `resolve` and `reject` functions in a native handler
   * so they can be called asynchronously from C++ functions.
   * @param {PromiseExecutor} promiseExecutor
   * An object bundling the `resolve` and `reject` functions of a Promise.
   * @return {Number}
   * A unique key for the registered Promise so it can be resolved later in C++.
   */
  function registerPromise(promiseExecutor) {
    return dscef.__native__.__registerPromise(promiseExecutor);
  }

  /**
   * Location struct for describing call traces.
   */
  class Location {
    /**
     * Creates a Location object..
     * @param {String} url
     * Absolute URL of the file where the error is from.
     * @param {Number} line
     * Line number for the error in the file referenced by the `url`.
     * @param {Number} column
     * Column index for the error in the file referenced by the `url`.
     */
    constructor(url, line, column) {
      this.url = url;
      this.line = line;
      this.column = column;
    }

    /**
     * Formatting for console logs.
     * @return {String}
     * The error location formatted as `url:line:column`.
     */
    toString() {
      return `${this.url}:${this.line}:${this.column}`;
    }
  }

  /**
   * Separates line and column numbers from a string of the form "uri:line:column".
   * @param {String} location
   * Location string for an error.
   * @return {Location}
   * A Location object constructed from the parsed input.
   */
  function extractLocation(location) {
    // Fail-fast but return locations like "(native)".
    if (!location.includes(':')) {
      return [location];
    }

    // Removes parens.
    const stripped = location.replace(/[()]/g, '');

    // Captures URI, line number, and column without the colons.
    const partsRE = /(.+?)(?::(\d+))?(?::(\d+))?$/;
    const parts = partsRE.exec(stripped);

    return new Location(parts[1], parts[2] || 1, parts[3] || 1);
  }

  /**
   * Creates a Location object from an error call stack.
   * @param {Error} error
   * A thrown error.
   * @param {Number} target
   * A target index for a call stack frame.
   * @return {Location}
   * A Location object constructed from the error call stack.
   */
  function getOriginFromError(error, target) {
    const stackLines = error.stack
      .split('\n')
      // RegExp for V8 stack traces.
      .filter((line) => !!line.match(/^\s*at .*(\S+:\d+|\(native\))/m));

    /**
     * @param {String} line
     * A single call stack frame.
     * @return {Location}
     * A Location object constructed from a call stack frame.
     */
    const parse = function (line) {
      if (line.includes('(eval ')) {
        // Throw away eval info (not supported).
        line = line.replace(/eval code/g, 'eval').replace(/(\(eval at [^()]*)|(\),.*$)/g, '');
      }

      // Tokenize the stack frame.
      const tokens = line
        .replace(/^\s+/, '')
        .replace(/\(eval code/g, '(')
        .split(/\s+/)
        .slice(1);

      const location = extractLocation(tokens.pop());

      const fileName = ['eval', '<anonymous>'].includes(location.url)
        ? '<anonymous>'
        : location.url;

      return new Location(fileName, location.line || 1, location.column || 1);
    };

    return stackLines.length > target ? parse(stackLines[target]) : null;
  }

  /**
   * Generate a location for the call on `trace`.
   * @param {Number} target
   * A target index for a call stack frame.
   * @return {Location}
   * A Location for the trace call.
   */
  function trace(target) {
    return getOriginFromError(new Error(), target);
  }

  // Conditional log for dscef functions.
  let _logList = [];

  /**
   * Logs function usage.
   * @param {String} functionName
   * Name of the function.
   * @param {Array<*>} args
   * Arguments for the function.
   */
  function log(functionName, args) {
    if (_logList.length === 0) {
      // Extract the names of the functions to log.
      _logList = dscef.getEnv('CATCEF_BINDINGS_LOG').replace(/\s/g, '').split(',');
    }

    if (_logList.indexOf(functionName) !== -1 || _logList.indexOf('*') !== -1) {
      const location = trace(3);

      console.log(`[DSCEF LOG] ${functionName} called from ${location.toString()}`);

      if (args) {
        console.dir(args);
      }
    }
  }
})(); // End of IIFE.

/**
 * @function CATCefSendString
 * @deprecated Use {@link dscef.sendString} instead.
 * @return {void}
 */
//eslint-disable-next-line no-unused-vars
var CATCefSendString = (() => {
  'use strict';

  return function (...args) {
    console.warn('CATCefSendString() is deprecated. Use dscef.sendString() instead.');

    dscef.sendString(...args);
  };
})();
