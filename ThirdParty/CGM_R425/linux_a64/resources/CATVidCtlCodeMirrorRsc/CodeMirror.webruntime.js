/*jshint bitwise:true, noarg:true, eqeqeq:true, forin:true, immed:true,
         nonew:true, undef:true, strict:true, trailing:true, regexp:true,
         unused:true, globalstrict:true, camelcase:true
         curly:false*/
/*jshint browser:true*/

//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/07/19
//===================================================================

if (typeof KERNEL === "undefined")
  var KERNEL = function() { /*NOTHING*/ };

(function() {
  "use strict";

  KERNEL.browser = (function() {
    var ua = navigator.userAgent;
    if (ua.match(/chrome/i))  return "chrome";
    if (ua.match(/firefox/i)) return "firefox";
    if (ua.match(/mozilla/i)) return "InternetExplorer";
    return "browser";
  })();

  KERNEL.log = (function(message) { (KERNEL.browser == "InternetExplorer") ? alert(message) : console.log(message); });
  
  KERNEL.UrlEncode = (function(chaine) {
    return chaine.replace(/\n/g, "@fdn@0A")
                 .replace(/\r/g, "@fdn@0D")
                 .replace(/\f/g, "@fdn@0C")
                 .replace(/\t/g, "@fdn@09")
                 .replace(/\"/g, "@fdn@22")
                 .replace(/\'/g, "@fdn@27")
                 .replace(/ /g, "@fdn@32")
                 .replace(/\\/g, "@fdn@16");
  });

  //KERNEL.UrlEncode = (function(chaine) { return encodeURIComponent(chaine); });
  
  KERNEL.UrlDecode = (function(chaine) {
      return chaine.replace(/@fdn@0A/g, "\n")
                   .replace(/@fdn@0D/g, "\r")
                   .replace(/@fdn@0C/g, "\f")
                   .replace(/@fdn@09/g, "\t")
                   .replace(/@fdn@22/g, "\"")
                   .replace(/@fdn@27/g, "\'")
                   .replace(/@fdn@32/g, " ")
                   .replace(/@fdn@16/g, "\\");
  });
  
  // GetElementsByClassName compatible with IE
  KERNEL.IEGetElementsByClassName = (function(node, classname) {
      var ua = navigator.userAgent;
      if (ua.match(/mozilla/i)) { // IE
        var a = [];
        var re = new RegExp('(^| )'+classname+'( |$)');
        var els = node.getElementsByTagName("*");
        for(var i=0,j=els.length; i<j; i++)
          if (re.test(els[i].className))
            a.push(els[i]);
        return a;
      }
      else { // other browser
        return node.getElementsByClassName(classname);
      }
  });

  // Get Window Height
  KERNEL.GetWindowHeight = (function() { return window.innerHeight || (document.documentElement || document.body).clientHeight; });

  // Switch CodeMirror instance to full window
  KERNEL.SetFullWindow = (function (cm) {
    var wrap = cm.getWrapperElement(), scroll = cm.getScrollerElement();
    wrap.className += " CodeMirror-fullscreen";
    scroll.style.height = KERNEL.GetWindowHeight() + "px";
    document.documentElement.style.overflow = "hidden";
    cm.refresh();
  });

  // Get the current scroll position
  KERNEL.GetScrollPosition = (function() {
    var scPos = new Array(2);
    scPos["top"] = document.body.scrollTop;
    var t1 = document.documentElement.scrollTop; // I love IE
    if (t1 > scPos["top"])
      scPos["top"] = t1; 
    scPos["height"] = document.body.scrollHeight;
    var t2 = document.documentElement.scrollHeight; // I love IE
    if (t2 > scPos["height"])
      scPos["height"] = t2; 
	  return scPos;
  });

  KERNEL.fakeSocket = (function() {
  });

  // Bufferised message (to be remove as soon as asynchrone messages are available)
  // The message is really sent only when the command play is provided
  var fullMessage = "";
  var encodedMessage = "";
  KERNEL.fakeSocket.prototype.sendMessageToC = function (iMessage) {
    var dbg = false;
    encodedMessage = KERNEL.UrlEncode(iMessage);

    // New version
    var textarea = document.createElement("textarea");
    textarea.setAttribute("name", "URLMessage");
    textarea.appendChild(document.createTextNode(encodedMessage));
    var form = document.createElement("form");
    form.setAttribute("method", "POST");
    form.setAttribute("action", "jsnotif://");
    form.appendChild(textarea);
    document.documentElement.appendChild(form);
    form.submit();
    form.parentNode.removeChild(form);
    form = null;

    // Reset the message
    fullMessage = "";
  };

  KERNEL.fakeSocket.prototype.sendCommand = function(commandID, commandData){
    var msg = commandID + "://"; 
    if (typeof commandData === "undefined") 
      msg += "null"; 
    else if (typeof commandData === "object") 
      msg += JSON.stringify(commandData); 
    else 
      msg += commandData; 
    
    //this.sendMessageToC(msg);
	if(dscef) {
		dscef.sendString(msg);
	}
  }
  
  KERNEL.WebRuntime = function(name) {
    this.ws = new KERNEL.fakeSocket();
  };

  KERNEL.WebRuntime.prototype.sendCommand = function(commandID, commandData){
    this.ws.sendCommand(commandID, commandData);
  };

}());
