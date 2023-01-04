(() => {
  'use strict';

  const e = document.documentElement;

  return {
    width: Math.round(e.scrollWidth + (window.innerWidth - e.clientWidth)),
    height: Math.round(e.scrollHeight + (window.innerHeight - e.clientHeight))
  };
})();
