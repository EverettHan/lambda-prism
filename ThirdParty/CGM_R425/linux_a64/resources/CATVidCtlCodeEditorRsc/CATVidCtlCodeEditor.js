/*jshint bitwise:true, noarg:true, eqeqeq:true, forin:true, immed:true,
         nonew:true, undef:true, strict:true, trailing:true, regexp:true,
         unused:true, globalstrict:true, camelcase:true
         curly:false*/
/*global CodeMirror:false*/

"use strict";

if (typeof IDEJS === "undefined")
  var IDEJS = function () { /* NOTHING */ };

//-------------------------------------------------------
//-----------------Global functions
//-------------------------------------------------------
var ios = /AppleWebKit/.test(navigator.userAgent) && /Mobile\/\w+/.test(navigator.userAgent);
var mac = ios || /Mac/.test(navigator.platform);

// Remove browser contextual menu
// doesn't work on ie7 :-(
// document.onContextmenu = function () { return false; }

//----------------------- KERNEL runtime access
var CMObject = new KERNEL.WebRuntime("CMObject");

function sendCommand(commandID, commandData) { CMObject.sendCommand(commandID, commandData); }

//-----------------connect CodeMirror to the window size
CodeMirror.connect(window, "resize", function() {
  //var showing = IEGetElementsByClassName(document.body,"CodeMirror-fullscreen")[0];
  var showing = KERNEL.IEGetElementsByClassName(document.body, "CodeMirror-fullscreen")[0];
  if (!showing) return;
  showing.CodeMirror.getScrollerElement().style.height = KERNEL.GetWindowHeight() + "px";
});

//----------------- DefineInitHook is used to run some code whenever a CodeMirror instance is initialized.
CodeMirror.defineInitHook(function () {
  sendCommand("CodeMirrorInstanceInitialized");
});

//-------------------------------------------------------
//-----------------The CodeMirror editor and its settings
//-------------------------------------------------------
var input = CodeMirror.fromTextArea(document.getElementById("textarea_input"), {
  mode: "xml",
  matchBrackets: true,
  onCursorActivity: function () {
    highlightCurrentLine(input);
    var start = input.getCursor(true);
    var end = input.getCursor(false);
    sendCommand("cursorActivity", start.line + "," + start.ch + "," + end.line + "," + end.ch);
  },
  onChange: function () { sendCommand("textChanged", getCursorPosition()); },
  onGutterClick: function (cm, n) { cm.toggleBreakpoint(n, true); },
  onFocus: function () { sendCommand("onFocus"); },
  onBlur : function(){ sendCommand("onBlur"); }
});

function CM_HandleCommand(commandID, commandData) {
    if (commandID === "toggleBreakpoint")               { input.toggleBreakpoint(input.getCursor().line, true); }
    else if (commandID === "toggleBreakpointActivity")  { input.toggleBreakpointActivity(input.getCursor().line, true); }
    else if (commandID === "enableBreakpoint")          { input.enableBreakpoint(parseInt(commandData)); }
    else if (commandID === "disableBreakpoint")         { input.disableBreakpoint(parseInt(commandData)); }
    else if (commandID === "deleteBreakpoint")          { input.deleteBreakpoint(parseInt(commandData)); }
    else if (commandID === "enableAllBreakpoints")      { input.enableAllBreakpoints(false); }
    else if (commandID === "disableAllBreakpoints")     { input.disableAllBreakpoints(false); }
    else if (commandID === "deleteAllBreakpoints")      { input.deleteAllBreakpoints(false); }
    else if (commandID === "displayExecutionMarker")    { input.setExecutionMarkerPosition(parseInt(commandData)); }
    else if (commandID === "requestText")               { sendCommand("textRequested", input.getValue()); }
    else if (commandID === "find")                      { input.find(commandData); }
    else if (commandID === "findNext")                  { input.findNext(); }
    else if (commandID === "findPrev")                  { input.findPrev(); }
    else if (commandID === "clearSearch")               { CodeMirror.commands.clearSearch(input); }
    else if (commandID === "scrollToLine")              { input.scrollToLine(parseInt(commandData)); }
    else if (commandID === "clearHistory")              { input.clearHistory(); }
    else if (commandID === "registerCss")               { loadCss(commandData); }
    else if (commandID === "requestSelection")          { sendCommand("selectionRequested", input.getSelection()); }
    else if (commandID === "requestSelectionRange") {
      var start = input.getCursor(true);
      var end = input.getCursor(false);
      sendCommand("selectionRangeRequested", start.line + "," + start.ch + "," + end.line + "," + end.ch);
    }
    else if (commandID === "setSelection") {
      var args = JSON.parse(commandData);
      if (args.LineStart && args.CharStart && args.LineEnd && args.CharEnd) {
        input.setSelection({ line: parseInt(args.LineStart), ch: parseInt(args.CharStart) }, { line: parseInt(args.LineEnd), ch: parseInt(args.CharEnd) });
      }
    }
    else if (commandID === "replaceRange") {
      var args = JSON.parse(commandData);
      // Insert Text Functionality
      // It taskes as arguments the string to insert and the position (line + character) where to insert it.
      if (args.Source && args.LineStart && args.CharStart && !args.LineEnd && !args.CharEnd) {
        input.replaceRange(KERNEL.UrlDecode(args.Source), { line: parseInt(args.LineStart), ch: parseInt(args.CharStart) });
      }
      // Replace Text Functionality 
      // It takes as arguments the string to replace and the positions (line + character) from and to.
      else if (args.Source && args.LineStart && args.CharStart && args.LineEnd && args.CharEnd) {
        input.replaceRange(KERNEL.UrlDecode(args.Source), { line: parseInt(args.LineStart), ch: parseInt(args.CharStart) }, { line: parseInt(args.LineEnd), ch: parseInt(args.CharEnd) });
      }
    }
    else if (commandID === "markText") {
      var args = JSON.parse(commandData);
      if (args.LineStart && args.CharStart && args.LineEnd && args.CharEnd && args.ClassName) {
        input.markText({ line: parseInt(args.LineStart), ch: parseInt(args.CharStart) }, { line: parseInt(args.LineEnd), ch: parseInt(args.CharEnd) }, args.ClassName);
      }
    }
    else if (commandID === "unmarkText") {
        var args = JSON.parse(commandData);
        if (args.LineStart && args.CharStart && args.LineEnd && args.CharEnd) {
            //need to check that args.LineStart > args.LineEnd. If not, the markers will be removed by only using a start line and a start char.
            if(args.LineStart > args.LineEnd) {
                var arrayMarkers = input.findMarksAt({ line: parseInt(args.LineStart), ch: parseInt(args.CharStart) });
                for (var i in arrayMarkers) {
                arrayMarkers[i].clear();
                }
            }

            else {
                var startLine = parseInt(args.LineStart);
                var endLine = parseInt(args.LineEnd);
                for (var l = startLine; l <= endLine ; l++) {

                    var line = input.getLineHandle(l);
                    if (line) {
                        var startChar = 0;
                        var endChar = line.text.length - 1;

                        if (l === startLine) {
                            startChar = parseInt(args.LineStart);
                        } else if (l === endLine) {
                            endChar = parseInt(args.CharEnd);
                        }

                        for (var c = startChar; c <= endChar; c++) {
                            var arrayMarkers = input.findMarksAt({ line: l, ch: c });
                            for (var i in arrayMarkers) {
                                arrayMarkers[i].clear();
                            } 
                        }
                    }
                }
            }
        }
    }
}

function CM_SetText(s) { input.setValue(KERNEL.UrlDecode(s)); }

function CM_SetOption(option, value) { 
  (option === "mode" && value === "javascript") ? input.setOption(option, { name: "javascript", json: true }) : input.setOption(option, value);
}

function CM_SetStyleAttribute(attribute, value) {
  input.getWrapperElement().style[attribute] = value; input.refresh();
}

function CM_GetModes() {
  var data = "";
  for (var i in CodeMirror.modes) { data += i; data += " "; }
  sendCommand("modes", data);
}

var bpState = { enabled  : 0, disabled : 1, deleted  : 2 };

input.updateMarker = function(line, option, value) {
  var handle = this.getLineHandle(line);
  var markerInfo = handle.gutterMarkerInfo;

  if (markerInfo === undefined || markerInfo === null) markerInfo = {};
  markerInfo[option] = value;
  handle.gutterMarkerInfo = markerInfo;

  var marker = "";
  if (markerInfo.breakpoint === bpState.enabled) marker += this.bpeMarker;
  else if (markerInfo.breakpoint === bpState.disabled) marker += this.bpdMarker;
  if (markerInfo.execution) marker += this.exeMarker;

  (marker === "") ? this.clearMarker(line) : this.setMarker(line, marker + "%N%");
}

input.scrollToLine = function (lineNum) {
  this.setCursor(lineNum);
  this.setLineClass(lineNum, null, "activeline");
  var line = document.getElementById(".CodeMirror-lines.activeline");
  var linePos = Math.floor(line.offset().top);
  var scPos = KERNEL.GetScrollPosition();
  if (linePos <= scPos.top || linePos > scPos.height - scPos.height / 4) {
    var sk = document.getElementById(".CodeMirror-scroll");
    sk.scrollTop(0).scrollTop(line.offset().top - sk.offset().top - Math.floor(sk.height() / 2));
  }
}

input.toggleBreakpoint = function (line, notify) {
  if (this.getOption("breakpointsSupport")) {
    var markerInfo = this.getLineHandle(line).gutterMarkerInfo;

    (markerInfo && markerInfo.breakpoint === bpState.enabled) ? this.deleteBreakpoint(line) : this.enableBreakpoint(line);

    if (notify) sendCommand("breakpointToggled", line);
  }
}

input.toggleBreakpointActivity = function (line, notify) {
  var toggled = false;
  if (this.getOption("breakpointsSupport")) {
    var markerInfo = this.getLineHandle(line).gutterMarkerInfo;

    if (markerInfo) {
      if (markerInfo.breakpoint === bpState.enabled) {
        this.disableBreakpoint(line); toggled = true;
      }
      else if (markerInfo.breakpoint === bpState.disabled) {
        this.enableBreakpoint(line); toggled = true;
      }
    }

    if (notify && toggled) sendCommand("breakpointActivityToggled", line);
  }
}

input.enableBreakpoint = function (line)  { if (this.getOption("breakpointsSupport")) { this.updateMarker(line, "breakpoint", bpState.enabled);  }}
input.disableBreakpoint = function (line) { if (this.getOption("breakpointsSupport")) { this.updateMarker(line, "breakpoint", bpState.disabled); }}
input.deleteBreakpoint = function (line) { if (this.getOption("breakpointsSupport"))  { this.updateMarker(line, "breakpoint", bpState.deleted);  }}

input.enableAllBreakpoints = function (notify) {
  if (this.getOption("breakpointsSupport")) {
    for (var i = 0; i < this.lineCount(); ++i) {
      if (this.lineInfo(i).markerText) {
        var markerInfo = this.getLineHandle(i).gutterMarkerInfo;
        if (markerInfo && markerInfo.breakpoint === bpState.disabled) this.enableBreakpoint(i);
      }
    }
    if (notify) sendCommand("allBreakpointsEnabled");
  }
}

input.disableAllBreakpoints = function (notify) {
  if (this.getOption("breakpointsSupport")) {
    for (var i = 0; i < this.lineCount(); ++i) {
      if (this.lineInfo(i).markerText) {
        var markerInfo = this.getLineHandle(i).gutterMarkerInfo;
        if (markerInfo && markerInfo.breakpoint === bpState.enabled) this.disableBreakpoint(i);
      }
    }
    if (notify) sendCommand("allBreakpointsDisabled");
  }
}

input.hasAllBreakpointsEnabled = function () {
  for (var i = 0; i < this.lineCount(); ++i) {
    if (this.lineInfo(i).markerText) {
      var markerInfo = this.getLineHandle(i).gutterMarkerInfo;
      if (markerInfo && markerInfo.breakpoint === bpState.disabled) return false; 
    }
  }
  return true;
}

input.deleteAllBreakpoints = function (notify) {
  if (this.getOption("breakpointsSupport")) {
    for (var i = 0; i < this.lineCount(); ++i) {
      if (this.lineInfo(i).markerText) this.deleteBreakpoint(i);
    }
    if (notify) sendCommand("allBreakpointsDeleted");
  }
}

input.setExecutionMarkerPosition = function (line) {
  var currentPos = this.getOption("executionMarkerPos");
  if (currentPos !== -1) this.updateMarker(currentPos, "execution", false);
  if (line > -1) {
    this.setOption("executionMarkerPos", line);
    this.updateMarker(line, "execution", true);
    this.scrollToLine(line);
  }
}

input.find = function(query) {
  CodeMirror.commands.find(this, query);
  this.setOption("lastQuery", query);
}

input.findNext    = function() { CodeMirror.commands.findNext(this, this.getOption("lastQuery")); }
input.findPrev    = function() { CodeMirror.commands.findPrev(this, this.getOption("lastQuery")); }
input.clearSearch = function() { CodeMirror.commands.clearSearch(input); } 

function highlightCurrentLine(cm) {
  var highlightedLine = cm.getOption("highlightedLine");
  cm.setLineClass(highlightedLine, null, null);
  highlightedLine = cm.getCursor().line;
  cm.setOption("highlightedLine", highlightedLine);
  cm.setLineClass(highlightedLine, null, "activeline");
}

function loadCss(url) {
  var link = document.createElement("link");
  link.type = "text/css";
  link.rel = "stylesheet";
  link.href = url;
  document.getElementsByTagName("head")[0].appendChild(link);
}

function getCursorPosition() { return ((input.getCursor().line + 1) + " " + (input.getCursor().ch)); }

// breakpointsSupport Management
input.setOption("breakpointsSupport", false);
input.setOption("breakState", false);
input.setOption("executionMarkerPos", -1);

// gutters management // old symbols: ⚫⚪
input.bpeMarker = "<span class='red_gutterClass'>●</span>";
input.bpdMarker = "<span class='red_gutterClass'>○</span>";
input.exeMarker = "<span class='green_gutterClass'>▶</span>";
input.boeMarker = "<span class='blue_gutterClass'>◼</span>";
input.bodMarker = "<span class='blue_gutterClass'>◻</span>";

// highlightedLine Management
input.setOption("highlightedLine", 0);

// find management
input.setOption("lastQuery", "");

// merge keyMaps method
function merge_keyMaps(obj1,obj2){
    var obj3 = {};
    for (var attrname in obj1) { obj3[attrname] = obj1[attrname]; }
    for (var attrname in obj2) { obj3[attrname] = obj2[attrname]; }
    return obj3;
}

// extraKeys Management
var cmds = {
  // editor commands
  askForSave: function (cm) { sendCommand("askForSave"); },
  showFind: function (cm)   { sendCommand("showFindBar", cm.getSelection()); },
  hideFind: function (cm)   { sendCommand("hideFindBar"); },
  findNext: function (cm)   { cm.findNext(); },
  findPrev: function (cm)   { cm.findPrev(); },
  nullFunc: function (cm)   { },
  // breakpoints commands
  toggleBreakpoint: function (cm) { cm.toggleBreakpoint(cm.getCursor().line, true); },
  toggleBreakpointActivity: function (cm) { cm.toggleBreakpointActivity(cm.getCursor().line, true); },
  toggleAllBreakpointsActivity: function (cm) { cm.hasAllBreakpointsEnabled() ? cm.disableAllBreakpoints(true) : cm.enableAllBreakpoints(true); },
  deleteAllBreakpoints: function (cm) { cm.deleteAllBreakpoints(true); },
  // debug commands
  run: function (cm) { cm.getOption("breakState") ? sendCommand("continue") : sendCommand("run") },
  stop: function (cm) { if (cm.getOption("breakState")) sendCommand("stop"); },
  stepOver: function (cm) { if (cm.getOption("breakState")) sendCommand("stepOver"); },
  stepIn: function (cm) { if (cm.getOption("breakState")) sendCommand("stepIn"); },
  stepOut: function (cm) { if (cm.getOption("breakState")) sendCommand("stepOut"); },
  dbgBreak: function (cm) { sendCommand("break"); }
};

var extraKeysBasic = { "Esc": cmds.hideFind, "F3": cmds.findNext, "F5": cmds.run, "F9": cmds.toggleBreakpoint, "F10": cmds.stepOver, "F11": cmds.stepIn, "F12": cmds.nullFunc, 
                       "Shift-F3": cmds.findPrev, "Shift-F5": cmds.stop, "Shift-F10": cmds.nullFunc, "Shift-F11": cmds.stepOut };
var extraKeysPC = { "Ctrl-S": cmds.askForSave, "Ctrl-F": cmds.showFind, "Ctrl-O": cmds.nullFunc, "Ctrl-P": cmds.nullFunc, "Ctrl-L": cmds.nullFunc,
                    "Ctrl-N": cmds.nullFunc, "Ctrl-F5": cmds.dbgBreak, "Ctrl-F9": cmds.toggleBreakpointActivity, 
                    "Shift-Ctrl-F9": cmds.deleteAllBreakpoints, "Shift-Ctrl-F10": cmds.toggleAllBreakpointsActivity };
var extraKeysMAC = { "Cmd-S": cmds.askForSave, "Cmd-F": cmds.showFind, "Cmd-O": cmds.nullFunc, "Cmd-P": cmds.nullFunc, "Cmd-L": cmds.nullFunc,
                    "Cmd-N": cmds.nullFunc, "Cmd-F5": cmds.dbgBreak, "Cmd-F9": cmds.toggleBreakpointActivity, 
                    "Shift-Cmd-F9": cmds.deleteAllBreakpoints, "Shift-Cmd-F10": cmds.toggleAllBreakpointsActivity };

mac ? input.setOption("extraKeys", merge_keyMaps(extraKeysBasic, extraKeysMAC))
    : input.setOption("extraKeys", merge_keyMaps(extraKeysBasic, extraKeysPC));

input.getWrapperElement().style.fontSize = "10pt";
input.refresh(); 
KERNEL.SetFullWindow(input); // window filled by the editor
