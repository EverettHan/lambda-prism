/* global dscef */
/* eslint no-console: off */

(() => {
  'use strict';
  const deps = ['DS/WebRecordClient/Record/WebRecordAnalyzer'];
  require(deps, analyzer => {
    try {
      dscef.Record.analyzer = analyzer;
    } catch (error) {
      console.error('Failed to load WebRecordAnalyzer.js.', error);
    }
  });
})();
