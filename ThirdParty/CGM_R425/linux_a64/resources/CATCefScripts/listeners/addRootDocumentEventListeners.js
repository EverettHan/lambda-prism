/* global dscef */
/* eslint no-console: off */

(() => {
  'use strict';

  // Notify the native client when the DOM is ready.
  const { notifyDOMReady } = dscef._internals;

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', notifyDOMReady, true);
  } else {
    notifyDOMReady();
  }

  // Notify the native client when the document is being unloaded.
  document.addEventListener('unload', dscef._internals.notifyUnload);

  // This namespace should be defined only if an ODT is running.
  if (dscef.Test) {
    window.addEventListener('beforeunload', () => {
      const { Test } = dscef;

      if (Test.coverageEnabled() && window.__coverage__) {
        const collected = Test.collectCoverage(JSON.stringify(window.__coverage__));

        if (collected) {
          console.log('Coverage data collected');
        } else {
          console.error('Coverage data failed to be collected');
        }
      }
    });
  }
})();
