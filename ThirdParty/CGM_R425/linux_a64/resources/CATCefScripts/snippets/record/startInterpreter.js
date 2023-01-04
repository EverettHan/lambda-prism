/* global dscef */
/* eslint no-console: off */

// This file should be executed when the DOMContentLoaded event is caught.
(() => {
  'use strict';

  const MAX_ATTEMPTS = 50;

  let attempts = 0;

  function startInterpreter() {
    if (++attempts < MAX_ATTEMPTS) {
      if (window.define && window.define.amd) {
        dscef.Record.startInterpreter();

        return true;
      }

      setTimeout(startInterpreter, 200);
    }

    return false;
  }

  // Try once immediately.
  const started = startInterpreter();

  // Then start the recurring attempts if it failed.
  if (!started) {
    setTimeout(startInterpreter, 200);
  }
})();
