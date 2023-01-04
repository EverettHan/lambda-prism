(() => {
  'use strict';
  const link = document.createElement('link');
  link.type = 'text/css';
  link.rel = 'stylesheet';
  link.href = 'dsrtv://webapps/WebRecordClient/diagnosis.css';
  document.getElementsByTagName('head')[0].appendChild(link);
})();
