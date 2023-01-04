define("DS/Usage/GDPR",function(){"use strict";Number.isInteger||(Number.isInteger=function(e){return"number"==typeof e&&isFinite(e)&&Math.floor(e)===e});var e=["status","privacyVersion","consentCategories","blockedOnCategories","creationTimestamp"],t=["necessary","functional","advertising"],n={getCookie:function(e){var t,n,a=[];try{a=document.cookie.split("; ")}catch(e){}return(t=a.filter(function(t){return t.split("=")[0]===e})).length&&(n=t[0].split("=")[1]),n},getIndexFromRank:function(e){if(e=parseInt(e),Number.isInteger(e))return e-1;throw new Error("GDPR : Cookie rank must be an integer")},decode:function(e,a){var r=a.includes("%2C")?a.split("%2C"):a;if("consentCategories"===e)if(a)if(Array.isArray(r))r=r.map(function(e){var a=n.getIndexFromRank(e);return t[a]});else{var o=n.getIndexFromRank(a);r=o?[t[o]]:r}else r=[t[0]];return r},getModel:function(){var t=n.getCookie("TC_PRIVACY"),a=t&&t.split("@")||[],r={status:0,privacyVersion:"001",consentCategories:[],blockedOnCategories:1,creationTimestamp:Date.now()};return a.forEach(function(t,a){var o=e[a];r[o]=n.decode(o,t)}),r}};return{get:n.getModel,getConsentCategories:function(){return this.get().consentCategories},isFunctionalConsent:function(){return this.getConsentCategories().includes(t[1])},hasConsent:function(){return!!this.getConsentCategories().length}}}),define("DS/Usage/Events",function(){"use strict";return{counter:{increment:"counter:increment"},timer:{start:"timer:start",stop:"timer:stop"},tracker:{creation:"tracker:creation",update:"tracker:update",getContent:"tracker:get-content",gotContent:"tracker:got-content"},page:{view:"page:view",event:"page:event",interaction:"page:interaction"},data:{register:"data:register"},error:{runtime:"error:runtime"}}}),define("DS/Usage/UsageShardingManager",["DS/WebappsUtils/Inherit","DS/WebappsUtils/Utils","DS/Usage/Events","DS/Usage/GDPR"],function(e,t,n,a){var r,o,i,s={themKey:"webapp",user:null,newVisitor:!1},c={scrollable:function(e){return e.clientWidth<e.offsetWidth||"scroll"==e.style.overflowY||"auto"==e.style.overflowY},getAppScrollableContainer:function(e){for(var t,n=e;n;)n.clientHeight<n.scrollHeight&&this.scrollable(n)&&(t=n),n=n.parentNode;return t||document.body},containerHeight:function(e){var t=Math.max(e.scrollHeight,e.offsetHeight,e.clientHeight);return e.getBoundingClientRect().top+t},containerWidth:function(e){var t=Math.max(e.scrollWidth,e.offsetWidth,e.clientWidth);return e.getBoundingClientRect().left+t},viewportTop:function(e){return e.scrollTop},viewportBottom:function(e){return this.viewportTop(e)+(window.innerHeight||document.documentElement.clientHeight||document.body.clientHeight)},viewportLeft:function(e){return e.scrollLeft},viewportRight:function(e){return this.viewportLeft(e)+(window.innerWidth||document.documentElement.clientWidth||document.body.clientWidth)}},u=function(e){var t=e.topic.split(":");return(t=t.length>2?t.slice(0,2):t).join(":")},p={flatten:function(t,n){t[n]&&Array.isArray(t[n])&&(t[n].forEach(function(n){e.extend(t,n)}),delete t[n])},flattenData:function(e){e&&e.data&&["persDimPages","persValPages","persDimPageEvents","persValPageEvents"].forEach(function(t){p.flatten(e.data,t)})},parseQuery:function(e){var t=e.substring(e.indexOf("?")+1).split(/[&;]/),n={};return t.length&&t.forEach(function(e){var t=e.indexOf("=")+1,a=t?e.substr(t):"",r=t?e.substr(0,t-1).match(/([^\]\[]+|(\B)(?=\]))/g):[e],o=n;r&&(a=decodeURIComponent(a),r.forEach(function(e,t){e=decodeURIComponent(e);var n=o[e];t<r.length-1?o=o[e]=n||{}:Array.isArray(n)?n.push(a):o[e]=void 0!==n?[n,a]:a}))}),n},parseUrl:(o=["source","subprotocol","protocol","authority","user","password","domain","port","path","directoryPath","fileName","query","anchor"],i=new RegExp("^(?:(?:(?:([^#.:]+):)?([^#.:]+):)?//)?((?:([^:/]+)(?::([^/]*?))?@)?([^:/?#]*)(?::(\\d*))?)?((/(?:[^?#](?![^?#/]*\\.[^?#/.]+(?:[\\?#]|$)))*/?)?([^?#/]*))?(?:\\?([^#]*))?(?:#(.*))?"),function(e){var t,n=i.exec(e),a={};for(t=0;t<o.length;t++)a[o[t]]=n[t]||"";return a.subprotocol&&(a.source=a.source.substr(a.subprotocol.length+1)),a.port||(a.port="https"===a.protocol?"443":"80"),a.directoryPath&&a.directoryPath.length>0&&(a.directoryPath=a.directoryPath.replace(/\/?$/,"/")),a.domain=a.domain.toLocaleLowerCase(),a.protocol=a.protocol.toLocaleLowerCase(),a}),clearData:function(e){e.sessions=[];var t={};e.pages.forEach(function(e){t[e.trackerscope]=e}),t=Object.keys(t).map(function(e){return t[e]}),e.pages=t.sort(function(e,t){return e.timestamp-t.timestamp}),e.interactions=[],e.events=[],e.errors=[]},pruneData:function(e){e.sessions=e.sessions.slice(0,100),e.pages=e.pages.slice(0,100),e.interactions=e.interactions.slice(0,100),e.events=e.events.slice(0,100)},getValidURL:(r=document.createElement("a"),function(e){return r.href=e,r.href}),models:[{internal:"pages",payload:"usage"},{internal:"events",payload:"usage"},{internal:"interactions",payload:"usage"},{internal:"errors",payload:"usage"},{internal:"sessions",payload:"cusage"}],getLastPageID:function(e,t){var n,a=e&&e.pages,r=[];return a&&a.length&&(r=t?a.filter(function(e){return e.trackerscope&&e.trackerscope===t}):a.filter(function(e){return!e.trackerscope})),(n=r.pop())&&n.id||""},getUTMParameters:function(){var e={},t=p.parseQuery(window.location.search);return t?(["utm_source","utm_medium","utm_campaign","utm_term","utm_content"].forEach(function(n){t.hasOwnProperty(n)&&(e[n]=t[n])}),e):e},getTopDomain:function(){var e,t=p.parseUrl(window.location).domain,n="";if(!/^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/g.test(t)&&"localhost"!==t){for(e=t.split(".");e.length>2;)e.shift();n=e.join(".")}return n},getConsentsAttributes:function(){var e={};return a.isFunctionalConsent()?e={consent:!0,visitormode:"optin"}:a.hasConsent()?a.hasConsent()&&!a.isFunctionalConsent()&&(e={consent:!0,visitormode:"optout",casUser:"",cookie_vuid:"",user:""}):e={consent:!1,visitormode:"noconsent",casUser:"",cookie_vuid:""},e},getSession:function(n){return n=n||{},e.extend(n,{r_schemaName:"wasession",r_schemaVersion:"1.13",r_service:s.service,r_timestamp:Date.now(),them:s.themKey,sessionID:t.getCookie("_dss"),cookie_vuid:t.getCookie("VUID"),user:t.getCookie("_dsu"),casUser:s.authUser?t.sha256(s.authUser):"",referrer:document.referrer,newVisitor:s.newVisitor,serverhostname:s.hostname,locale:navigator.language||"en-US",enginename:t.clientEngine.name,userAgent:t.clientEngine.userAgent,engineversion:t.clientEngine.version,userAgent:navigator.userAgent,platformname:t.clientPlatform.name,platformmobile:t.clientPlatform.mobile,resheight:t.clientPlatform.resheight,reswidth:t.clientPlatform.reswidth,navigationtype:t.navigationType,startTime:s.navigationStart}),e.extend(n,p.getUTMParameters()),e.extend(n,p.getConsentsAttributes()),n}},d={enableUserInteraction:function(a){var r=a&&a.target,o=r&&c.getAppScrollableContainer(r),i={};if(r&&p.getLastPageID(this)&&("scroll"!==a.type||o===r)){e.extend(i,{interactionid:t.uuid(),action:a.type,viewportTop:c.viewportTop(o),viewportBottom:c.viewportBottom(o),viewportLeft:c.viewportLeft(o),viewportRight:c.viewportRight(o),pageWitdh:c.containerWidth(o),pageHeight:c.containerHeight(o)}),["id","className","tagName"].forEach(function(e){var t=r[e];t&&("string"==typeof t||t instanceof String)&&(i[e]=r[e])}),["clientX","clientY"].forEach(function(e){a[e]&&(i[e]=a[e]),a.touches&&a.touches[0]&&a.touches[0][e]&&(i[e]=a.touches[0][e])});var s={topic:n.page.interaction,data:i},u={data:JSON.stringify(s)};this.readMessage(u)}},enableErrorTracking:function(e){var t,a={topic:n.error.runtime,data:{}};e.filename&&(a.data.source=e.filename),e.message&&(a.data.message=e.message),e.colno&&(a.data.column=e.colno),e.lineno&&(a.data.line=e.lineno),e.name&&(a.data.name=e.name),e.error&&e.error.name&&(a.data.name=e.error.name),e.stack&&(a.data.stack=e.stack),e.error&&e.error.stack&&(a.data.stack=e.error.stack),Object.keys(a.data).length&&(t={data:JSON.stringify(a)},this.readMessage(t))},manageCookies:function(){var n,r=t.getCookie("_dsus"),o=t.getCookie("_dsut"),i=p.getTopDomain();r&&t.setCookie("_dss",r,i,s.sessionDuration),o&&t.setPersistantCookie("_dsu",o,i),n=t.getCookie("_dss"),!s.seed&&n||(n=t.uuid(s.seed)),t.setCookie("_dss",n,i,s.sessionDuration),s.user=t.getCookie("_dsu"),s.user?s.newVisitor=!1:(s.user=t.uuid(),s.newVisitor=!0),a.hasConsent()&&!a.isFunctionalConsent()?t.removeCookie("_dsu",i):t.setPersistantCookie("_dsu",s.user,i),s.sessionID!==n&&(s.seed=null,s.navigationStart=Date.now(),s.sessionID=n,p.clearData(this),this.pages.length&&(this.pages=this.pages.map(function(n){return e.extend(n,{id:t.uuid(),sessionID:s.sessionID,browseTime:Date.now()-s.navigationStart,r_timestamp:Date.now(),timestamp:Date.now()})})),this.sessions.push(p.getSession()),this.send({force:!0}))}};return{sessions:[],pages:[],interactions:[],events:[],errors:[],init:function(){var n,a=this,r=!1;n="string"==typeof arguments[0]?{uploadPath:arguments[0],service:arguments[1],user:arguments[2]}:arguments[0]||{};try{window.top.location.protocol}catch(e){r=!0}r||(e.extend(s,{uploadPath:p.getValidURL(n.uploadPath),sessionDuration:n.sessionDuration||30,sendDebounceRate:n.sendDebounceRate||2500,userActivityThrottleRate:n.userActivityThrottleRate||5e3,userInteractionThrottleRate:n.userInteractionThrottleRate||1e3,userInteractionDebounceRate:n.userInteractionDebounceRate||500,service:n.service,authUser:n.user&&n.user.login||"",hostname:n.hostname||window.location.hostname,themKey:n.them||"webapp",seed:n.seed||null,navigationStart:!window.performance||window.performance&&!window.performance.timing?Date.now():window.performance.timing.navigationStart}),window.addEventListener("beforeunload",a.send.bind(a,{mode:"beacon"})),window.addEventListener("message",a.readMessage.bind(a)),window.addEventListener("mousemove",t.throttle(d.manageCookies.bind(a),s.userActivityThrottleRate,!1,!0)),["click","dblclick","contextmenu","touchstart","touchend"].forEach(function(e){window.addEventListener(e,t.throttle(d.enableUserInteraction.bind(a),s.userInteractionThrottleRate,!0),!0)}),["scroll","mousemove","touchmove"].forEach(function(e){window.addEventListener(e,t.debounce(d.enableUserInteraction.bind(a),s.userInteractionDebounceRate),!0)}),window.addEventListener("error",d.enableErrorTracking.bind(a)),a.sendDebounced=t.debounce(a.send.bind(a),s.sendDebounceRate),d.manageCookies.call(a))},readMessage:function(a){var r={};try{r=JSON.parse(a.data),p.flattenData(r)}catch(e){}if(!r.forAPI&&r.topic){switch(a.stopPropagation&&a.stopPropagation(),u(r)){case n.page.view:e.extend(r.data,{r_schemaName:"wapage3",r_schemaVersion:"1.10",r_service:s.service,r_timestamp:Date.now(),serverhostname:s.hostname,id:t.uuid(),sessionID:t.getCookie("_dss"),browseTime:Date.now()-s.navigationStart}),r.data.timestamp&&delete r.data.timestamp,this.pages.push(r.data);break;case n.page.event:e.extend(r.data,{r_schemaName:"waevent3",r_schemaVersion:"1.10",r_service:s.service,r_timestamp:Date.now(),id:t.uuid(),sessionID:t.getCookie("_dss"),sessionpageID:p.getLastPageID(this,r.data.trackerscope)}),r.data.timestamp&&delete r.data.timestamp,this.events.push(r.data);break;case n.page.interaction:e.extend(r.data,{r_schemaName:"wainteraction3",r_schemaVersion:"1.08",r_service:s.service,r_timestamp:Date.now(),sessionID:t.getCookie("_dss"),sessionpageID:p.getLastPageID(this)}),this.interactions.push(r.data);break;case n.data.register:e.extend(r.data,{r_schemaName:"wasession",r_schemaVersion:"1.13",r_service:s.service,r_timestamp:Date.now(),sessionID:t.getCookie("_dss")}),e.extend(r.data,p.getConsentsAttributes()),this.sessions.push(r.data);break;case n.error.runtime:e.extend(r.data,{r_schemaName:"waerror3",r_schemaVersion:"1.07",r_service:s.service,r_timestamp:Date.now(),id:t.uuid(),sessionID:t.getCookie("_dss"),sessionpageID:p.getLastPageID(this),level:"error",category:"runtime"}),this.errors.push(r.data)}p.pruneData(this),r.sync?this.send():this.sendDebounced()}},send:function(e){var n,r=new FormData,o=e&&e.mode||"xhr",i=this,c=0;p.models.forEach(function(e){i[e.internal].forEach(function(t){r.append(e.payload+c,JSON.stringify(t)),c++})}),c&&((!a.hasConsent()||a.isFunctionalConsent()||e&&e.force)&&("beacon"===o?navigator.sendBeacon?navigator.sendBeacon(s.uploadPath,r):t.beaconPolyfill(s.uploadPath,r):((n=new XMLHttpRequest).open("POST",s.uploadPath),n.send(r))),p.clearData(this))}}}),define("DS/Usage/UsageManager",["DS/Usage/UsageShardingManager"],function(e){return{init:function(){var t;t="string"==typeof arguments[0]?{uploadPath:arguments[0],service:arguments[1],user:arguments[2]}:arguments[0]||{},e.init(t)}}}),define("DS/Usage/AbstractTracker",["DS/WebappsUtils/Inherit","DS/WebappsUtils/Promise","DS/WebappsUtils/Emitter","DS/Usage/Events"],function(e,t,n,a){"use strict";function r(e){this.name=e}return e.inherit(r,{set:function(e,t){var r;"object"==typeof e?(r=e,t=void 0):(r={})[e]=t,Object.keys(r).length>0&&(r.name=this.name,r.type=this.type,n.trigger(a.tracker.update,r))},get:function(){var e=this;return new t(function(t){var r=a.tracker.gotContent+":"+e.name,o=a.tracker.getContent+":"+e.name;n.on(r,function(a){n.off(r),a&&a.data&&a.data.name===e.name&&t(a.data)}),n.trigger(o,{name:e.name})})}}),r}),define("DS/Usage/ActionTracker",["DS/WebappsUtils/Inherit","DS/Usage/AbstractTracker","DS/WebappsUtils/Console"],function(e,t,n){"use strict";function a(e){n.warn("Module DS/Usage/ActionTracker is deprecated. Use DS/Usage/TrackerAPI#trackPageEvent instead"),t.call(this,e),this.type="action"}return e.inherit(a,t),a}),define("DS/Usage/TrackerAPI",["DS/WebappsUtils/Inherit","DS/WebappsUtils/Emitter","DS/Usage/ActionTracker","DS/Usage/Events"],function(e,t,n,a){"use strict";var r=!1,o=function(){var e=window.location,t=window.top.location;try{t.protocol}catch(e){r=!0}return r?{}:{current:e.protocol+"//"+e.hostname+(e.port?":"+e.port:""),parent:t.protocol+"//"+t.hostname+(t.port?":"+t.port:"")}}(),i=window.top;function s(e){return"string"==typeof e||e instanceof String}function c(e){return"number"==typeof e&&isFinite(e)}function u(e){return e&&"object"==typeof e&&e.constructor===Object}function p(e){return"function"==typeof e}function d(e){var t=!0;if(!u(e))return!1;if(0==Object.keys(e).length)return!1;if(Object.keys(e).length>=20)return!1;for(var n in e)e.hasOwnProperty(n)&&(/^(pd|pv)[0-9]+$/.test(n)||(t=!1),s(e[n])||(t=!1));return t}function g(e){var t=!0;if(!u(e))return!1;if(0==Object.keys(e).length)return!1;if(Object.keys(e).length>=20)return!1;for(var n in e)e.hasOwnProperty(n)&&(/^(pd|pv)[0-9]+$/.test(n)||(t=!1),c(e[n])||(t=!1));return t}var l={getTracker:function(){var t,r,o=arguments,i=o[0],s=o[1],c=o[2];if(void 0===c&&"object"==typeof s?(c=s,s=i,i="action"):void 0===c&&"string"==typeof s?c={}:void 0===s&&void 0===c&&("string"==typeof i?(s=i,i="action",c={}):(s=(r=e.clone(i)).name,i=r.type,c=r.options||{})),void 0===s)throw new TypeError("No tracker name specified");switch(i){case"action":var u=c;u.name=s,this.notify(u,a.tracker.creation),t=new n(s)}return t},trackPageView:function(e,t,n,c,l){var f=arguments[0];if(u(f)&&(e=f.pageURL,t=f.pageTitle,n=f.persDim,c=f.pageLanguage,l={persVal:f.persVal,appID:f.appID,tenant:f.tenant,scope:f.scope}),!r&&e&&s(e)){var h={origin:o.current,topic:a.page.view,sync:!!f.callback,data:{url:e,location:window.location.href,timestamp:Date.now(),pagelg:c||(window.dsLang?window.dsLang:"")}};t&&s(t)&&(h.data.title=t),n&&d(n)&&(h.data.persDimPages=[n]),l&&u(l)&&g(l.persVal)&&(h.data.persValPages=[l.persVal]),l&&u(l)&&l.appID&&(h.data.appID=l.appID),l&&u(l)&&l.tenant&&(h.data.tenant=l.tenant),l&&u(l)&&s(l.scope)&&(h.data.trackerscope=l.scope),i.postMessage&&i.postMessage(JSON.stringify(h),o.parent),p(f.callback)&&setTimeout(f.callback,0)}},trackPageEvent:function(e,t,n,l,f,h){var m=arguments[0];if(u(m)&&(e=m.eventCategory,t=m.eventAction,n=m.eventLabel,l=m.eventValue,f=m.persDim,h={persVal:m.persVal,appID:m.appID,tenant:m.tenant,scope:m.scope}),!r&&e&&s(e)&&t&&s(t)){var v={origin:o.current,topic:a.page.event,sync:!!m.callback,data:{category:e,action:t,timestamp:Date.now()}};n&&s(n)&&(v.data.label=n),l&&c(l)&&(v.data.value=l),f&&d(f)&&(v.data.persDimPageEvents=[f]),h&&u(h)&&g(h.persVal)&&(v.data.persValPageEvents=[h.persVal]),h&&u(h)&&h.appID&&(v.data.appID=h.appID),h&&u(h)&&h.tenant&&(v.data.tenant=h.tenant),h&&u(h)&&s(h.scope)&&(v.data.trackerscope=h.scope),i.postMessage&&i.postMessage(JSON.stringify(v),o.parent),p(m.callback)&&setTimeout(m.callback,0)}},registerData:function(){var e,t,n=arguments;!r&&n.length&&(1===n.length&&"object"==typeof n[0]?e=n[0]:n.length>1&&((e={})[n[0]]=n[1]),e&&(t={origin:o.current,topic:a.data.register,data:e},i.postMessage&&i.postMessage(JSON.stringify(t),o.parent)))},notify:function(e,t){if(!r){var n={origin:o.current,topic:t,data:e};i.postMessage&&i.postMessage(JSON.stringify(n),o.parent)}},init:function(){if(!r){var n=this;this._initiated||(this._initiated=!0,t.on("*",function(t,a){a.forAPI||n.notify(e.clone(a),t)}),window.addEventListener("message",function(e){var n={};try{n=JSON.parse(e.data)}catch(e){}n.forAPI&&(e.stopPropagation(),t.trigger(n.topic,n))}))}}};return l.init(),l});