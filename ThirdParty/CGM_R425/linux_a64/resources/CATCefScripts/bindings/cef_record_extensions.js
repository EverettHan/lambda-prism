/* global dscef */
/* eslint no-console: off, object-shorthand: off */

/*! Copyright Dassault Systemes 2016 */

(() => {
  'use strict';

  /**
   * Utility bindings for WebRecord.
   * Only used when recording or replaying an ODT.
   * @namespace dscef.Record
   * @property {Object} manager
   * This will hold the RecordManager instance.
   * More details in the WebRecordTool framework and its WebRecordClient.
   * @property {Object} interpreter
   * This will hold the InteractionInterpreterNative instance.</p>
   * Details in the WebRecordTool framework and its WebRecordReplayDriver module.
   */
  dscef.Record = {
    // RecordManager.
    manager: null,
    // InteractionInterpreter
    interpreter: null,
    // WebRecordAnalyzer.
    analyzer: null,

    /**
     * Loads RecordManager.js, saves the instance in Record.manager
     * and starts recording in the current context (main world).
     * Chrome Extensions are different: they load content scripts in isolated worlds.
     * @function startManager
     * @memberof dscef.Record
     * @return {Promise<void>}
     */
    startManager() {
      return new Promise((resolve, reject) => {
        require([
          'DS/WebRecordClient/Record/RecordManagerInterface',
          'DS/WebRecordClient/Record/WebRecordAnalyzer'
        ], (recordInterface, analyzer) => {
          try {
            this.manager = recordInterface;
            this.manager.startRecord();
          } catch (error) {
            const message = 'Failed to load RecordManager.';

            dscef.showNotification('critical', message, 0);
            console.error(message, error);

            // Only reject if the recorder fails to load.
            // The analyzer is not critical.
            reject(new Error(message));
          }

          if (analyzer) {
            this.analyzer = analyzer;
          } else {
            console.error('Failed to load WebRecordAnalyzer.js.');
          }

          // Load the analyzer's stylesheet. This is done with a snippet called by a native function
          // because we cannot reference `document` here.
          dscef.__native__.__loadAnalyzerStyles();

          resolve();
        }, err => console.error(JSON.stringify(err)));
      });
    },

    /**
     * Stops the recording.
     * @function stopManager
     * @memberof dscef.Record
     * @return {undefined}
     */
    stopManager() {
      if (!this.manager) {
        throw new Error('Cannot stop RecordManager because there is no instance.');
      }

      this.manager.stopRecord();
      this.manager = null;
    },

    /**
     * Loads InteractionInterpreterNative.js and saves the instance in Record.interpreter.
     * @function startInterpreter
     * @memberof dscef.Record
     * @return {Promise<void>}
     */
    startInterpreter() {
      return new Promise((resolve, reject) => {
        require(['DS/WebRecordReplayDriver/InteractionInterpreterNative'], Interpreter => {
          try {
            this.interpreter = new Interpreter();
            this.notifyInterpreterLoad();

            resolve();
          } catch (error) {
            const message = 'Failed to load InteractionInterpreterNative.js.';

            dscef.showNotification('critical', message, 0);
            console.error(message, error);

            reject(new Error(message));
          }
        });
      });
    },

    /**
     * Releases Record.interpreter.
     * @function stopInterpreter
     * @memberof dscef.Record
     * @return {undefined}
     */
    stopInterpreter() {
      this.interpreter = null;
    },

    /**
     * Checks if native record is active, using capture mode.
     * @function isRecording
     * @memberof dscef.Record
     * @return {Boolean}
     * True if capture mode is currently enabled.
     */
    isRecording: () => dscef.__native__.__isRecording(),

    /**
     * Checks if native record is active, using replay mode.
     * @function isReplaying
     * @memberof dscef.Record
     * @return {Boolean}
     * True if replay mode is currently enabled.
     */
    isReplaying: () => dscef.__native__.__isReplaying(),

    /**
     * Checks if the file exists in the local file system.
     * @function fileExists
     * @memberof dscef.Record
     * @param {String} path
     * The absolute path to check.
     * @return {Boolean}
     * True if the file exists.
     */
    fileExists: path => dscef.__native__.__fileExists(path),

    /**
     * Sends data to the native client so it can be registered by
     * the native record platform.
     * @function capture
     * @memberof dscef.Record
     * @param {String} interaction
     * The record data for one interaction.
     * @return {undefined}
     */
    capture: interaction => dscef.__native__.__capture(interaction),

    /**
     * Parses an interaction (JSON) and uses the interpreter to replay it.
     * @param {String} interaction
     * Interaction properties as stored in the capture files (JSON).
     * @return {Promise}
     * The promise from the interpreter, if it is defined.
     * Or a rejected promise if it is undefined.
     */
    async interpret(interaction) {
      if (!this.interpreter) {
        const msg = 'The replay interpreter is undefined';
        console.error(msg);

        throw new Error(msg);
      }

      let props;
      try {
        props = JSON.parse(interaction);
      } catch (error) {
        console.error('Failed to parse interaction', interaction);

        throw error;
      }

      try {
        const result = await this.interpreter.interpret(props);
        return this.handleReplayResult(result);
      } catch (error) {
        const isError = error instanceof Error;
        const isReplayError = error.name !== undefined && error.name === 'ReplayError';

        const errorText = isError && error.stack !== undefined ? error.toString() : error;

        console.error(errorText);

        return this.abort(
          isReplayError ? error.code : 200,
          isError ? `${error.message}\n${error.stack}` : String(error)
        );
      }
    },

    /**
     * Notifies the native record platform after or while replaying one interaction.
     * It has only one behavior for now:
     *   - Device events:
     *     It will replay a device event, like 'mousedown' or 'keydown'.
     *     The options should include the event data.
     * Abstract events are replayed directly by the interaction interpreter
     * and results should be passed to Record.handleReplayResult().
     * @function replay
     * @memberof dscef.Record
     * @param {String} type
     * The event type: only 'device' for now.
     * @param {Object} options
     * The event parameters: coordinates, button id, etc.
     * @param {Number} timestamp
     * Captured timestamp for the event, in milliseconds and relative to the test start.
     * @return {undefined}
     */
    replay: (type, options, timestamp) =>
      dscef._internals.promisify(dscef.__native__.__replay, {
        type,
        options,
        timestamp
      }),

    /**
     * Takes a replay result and allows the native replay to proceed
     * with the next interaction.
     * The current native replay implementation locks the main thread while
     * waiting for the ongoing interaction to finish.
     * @function handleReplayResult
     * @memberof dscef.Record
     * @param {*} result
     * Should be the replay result from InteractionInterpreterNative.interpret().
     * It will be considered a failure if the result is undefined.
     * Any other value is valid.
     * @return {boolean}
     * True if the result is not undefined.
     */
    handleReplayResult: result => dscef.__native__.__handleReplayResult(result),

    /**
     * Notifies the native record platform that an error occurred and the replay has to stop.
     * @function abort
     * @memberof dscef.Record
     * @param {Number} code
     * The error code.
     * @param {String} message
     * The error description.
     * @return {undefined}
     */
    abort: (code, message) => dscef.__native__.__abort(code, message),

    /**
     * Private callback to signal the native client that the InteractionInterpreter
     * has been successfully loaded by the browser.
     * @private
     * @return {undefined}
     */
    notifyInterpreterLoad: () => dscef.__native__.__notifyInterpreterLoad(),

    /**
     * Highlights recordable and non-recordable elements.
     * @param {Element} target
     * The root element to inspect.
     * @param {Boolean} recordableOnly
     * If true, only highlight element that have a record ID.
     * @return {undefined}
     */
    inspect(target, recordableOnly) {
      this.analyzer.inspect(target, recordableOnly, false);
    },

    /**
     * Removes the highlights added by this.inspect().
     * @return {undefined}
     */
    clearInspect() {
      this.analyzer.clear();
    },

    /**
     * Tries to pause the native replay.
     * This will skip the current interaction and free the main message loop.
     * @return {undefined}
     */
    pauseReplay: () => dscef.__native__.__pauseReplay(),

    /**
     * Tries to resume the native replay.
     * @return {undefined}
     */
    resumeReplay: () => dscef.__native__.__resumeReplay()
  };
})();

/**
 * Shared namespace for web and native platforms.
 * Record/Replay only.
 * @namespace
 */
//eslint-disable-next-line no-unused-vars
var DSWebRecord = {
  env: {},
  getenv: dscef.getEnv
};
