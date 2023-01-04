/* eslint-disable no-console */
/* global dscef */

(() => {
  'use strict';

  const { SCROLL_STEP } = dscef._internals;

  // Trigger a native event on zoom changes.
  // We are using web event listeners because zoom should not happen when an
  // event listener has used Event.preventDefault().
  // In this case, handling zoom actions in the C++ wrapper is too early.
  document.addEventListener('mousewheel', event => {
    if (event.ctrlKey) {
      // Don't scroll if CTRL is held down (expected behavior for zoom in and zoom out).
      event.preventDefault();

      // On scroll down, deltaY is positive while wheelDeltaY is negative. Be careful.
      const delta = event.wheelDeltaY;
      dscef._internals.notifyZoomChange(delta - (delta % SCROLL_STEP));
    }
  });

  // Same thing for zoom triggered with a keyboard.
  document.addEventListener('keydown', event => {
    // On AZERTY layouts, ALTGR is interpreted as CTRL+ALT.
    if (event.ctrlKey && !event.altKey) {
      // With CTRL held down.
      const key = event.keyCode;

      if (key === 187 || key === 107) {
        // '= +' or 'numpad +' key.
        dscef._internals.notifyZoomChange(SCROLL_STEP);
      } else if (key === 189 || key === 109) {
        // '- _' or 'numpad -' key.
        dscef._internals.notifyZoomChange(-SCROLL_STEP);
      } else if (key === 48) {
        // '0' key.
        dscef._internals.notifyZoomReset();
      }
    }
  });
})();
