/* global dscef */

(() => {
  'use strict';

  // Notify the native client when the main resource and its dependencies
  // have finished loading (images, stylesheets, etc.).
  window.addEventListener('load', dscef._internals.notifyLoad);
})();
