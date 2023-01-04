/* global dscef */
/* eslint no-console: off */

// Executor for dscef.Record.startManager.
(() => {
  'use strict';
  const deps = ['DS/WebRecordClient/Record/RecordManagerInterface'];
  require(deps, recordInterface => {
    try {
      dscef.Record.manager = recordInterface;
      dscef.Record.manager.startRecord();
    } catch (error) {
      const message = 'Failed to load RecordManager.';
      dscef.showNotification('critical', message, 0);
      console.error(message, error);
    }
  });
})();
