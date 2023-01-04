/* global dscef */
/* eslint no-console: off */

// This file should be executed when the DOMContentLoaded event is caught.
(() => {
  'use strict';

  const MAX_ATTEMPTS = 50;

  let attempts = 0;

  function startRecordManager() {
    if (++attempts > MAX_ATTEMPTS) {
      console.log(`location: ${window.location.href}, ${window.define}, ${window.require}`);

      throw new Error('Impossible to load the record manager: AmdLoader not found');
    }

    if (window.define && window.define.amd) {
      dscef.Record.startManager();

      return true;
    }

    setTimeout(startRecordManager, 200);

    return false;
  }

  // Try once immediately.
  const started = startRecordManager();

  // Then start the recurring attempts if it failed.
  if (!started) {
    setTimeout(startRecordManager, 200);
  }
})();
