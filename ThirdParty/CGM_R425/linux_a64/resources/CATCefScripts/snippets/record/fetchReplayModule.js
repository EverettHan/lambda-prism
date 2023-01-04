/* global dscef */
/* eslint no-console: off */

(() => {
  'use strict';
  const deps = ['DS/WebRecordReplayDriver/InteractionInterpreterNative'];
  require(deps, function(Interpreter) {
    try {
      dscef.Record.interpreter = new Interpreter();
      dscef.Record.notifyInterpreterLoad();
    } catch (error) {
      const message = 'Failed to load InteractionInterpreterNative.js.';
      dscef.showNotification('critical', message, 0);
      console.error(message, error);
    }
  });
})();
