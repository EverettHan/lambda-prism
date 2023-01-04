/*! Copyright 2014 Dassault Systèmes */
define("DS/DataDragAndDrop/DataDragAndDrop",function(){"use strict";function e(e,t){var a=t?"":"none";["WebkitTouchCallout","WebkitUserSelect","KhtmlUserSelect","MozUserSelect","MsUserSelect","UserSelect"].forEach(function(t){try{e.style[t]=a}catch(e){}})}function t(e,t){(function(e,t){return!!(e.className&&(a=e.className,n=t,r=" ",r?(r+a+r).indexOf(r+n+r)>-1:a.indexOf(n)>-1));var a,n,r})(e,t)||(e.className=(e.className.trim()+" "+t).trim())}function a(e,t,a){t.addEventListener?t.addEventListener(e,a,!1):t.attachEvent&&t.attachEvent("on"+e,a,!1)}function n(e){e.preventDefault&&e.preventDefault(),e.returnValue=!1,void 0!==e.cancelable&&!0!==e.cancelable||void 0!==e.defaultPrevented||(e.defaultPrevented=!0)}var r={draggable:function(n,r){var s;n&&1!==n.nodeType||n._evts&&n._evts.drg||(n.setAttribute("draggable",!0),n._evts=n._evts||{},n._evts.drg={},s={dragstart:function(a){e(this,!1),a.dataTransfer.effectAllowed="all";try{r.data?a.dataTransfer.setData("text",r.data):a.dataTransfer.setData("text",this.innerHTML)}catch(e){}r.start&&r.start(this,a),t(this,"dragging")},dragend:function(t){var a,n;e(this,!0),r.stop&&r.stop(this,t),n="dragging",(a=this).className=a.className.replace(new RegExp("(^|\\s)"+n+"(?:\\s|$)"),"$1")}},Object.keys(s).forEach(function(e){n._evts.drg[e]=s[e],a(e,n,n._evts.drg[e])}))},droppable:function(e,t){var r;e&&-1===[1,9].indexOf(e.nodeType)||e._evts&&e._evts.drp||(e._evts=e._evts||{},e._evts.drp={},r={dragenter:function(e){t.enter&&t.enter(this,e)},dragover:function(e){(!t.over||t.over&&!1!==t.over(this,e))&&n(e)},dragleave:function(e){t.leave&&t.leave(this,e)},drop:function(e){!function(e){!function(e){e.stopPropagation&&e.stopPropagation(),e.cancelBubble=!0}(e),n(e)}(e),t.drop&&t.drop(e.dataTransfer.getData("text"),this,e)}},Object.keys(r).forEach(function(t){e._evts.drp[t]=r[t],a(t,e,e._evts.drp[t])}))},clean:function(e,t){function a(e,t){for(var a in e._evts[t])e._evts[t].hasOwnProperty(a)&&(n=a,r=e,s=e._evts[t][a],r.removeEventListener?r.removeEventListener(n,s,!1):r.detachEvent&&r.detachEvent("on"+n,s));var n,r,s}e&&1!==e.nodeType||!e._evts||(t&&"drop"!==t||a(e,"drp"),t&&"drag"!==t||(a(e,"drg"),e.removeAttribute("draggable")),!t&&delete e._evts)},on:function(e,t,a){[].forEach.call(e,function(e){r.draggable(e,a)}),[].forEach.call(t,function(e){r.droppable(e,a)})},off:function(e,t){[].slice.call(e).concat([].slice.call(t)).forEach(function(e){r.clean(e)})}};return r});