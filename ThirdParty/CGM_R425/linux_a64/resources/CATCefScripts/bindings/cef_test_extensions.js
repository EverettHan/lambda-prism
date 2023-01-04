/* global dscef */

/*! Copyright Dassault Systemes 2017 */

(() => {
  'use strict';

  dscef.Test = {
    /**
     * Checks if MemoryCheck coverage is enabled for the current ODT.
     * @return {Boolean}
     * True if coverage is enabled, or false.
     */
    coverageEnabled: () => dscef.__native__.__coverageEnabled(),

    /**
     * Collects coverage data and feeds it to MemoryCheck.
     * @param {String} coverage
     * A stringified object that contains all the coverage data.
     * @return {Boolean}
     * True if the collect happened without any problem.
     */
    collectCoverage: coverage => dscef.__native__.__collectCoverage(coverage)
  };
})();
