/** 
* @quickReview SGA8 19:09:25 IR-688645-3DEXPERIENCER2019x/20x, IR-699632-3DEXPERIENCER2019x/20x
* : Stopped calling Maximize command on Instance ready and started handling resize on using window.innerHeight
* @quickReview SGA8 19:04:29 IR-681839-3DEXPERIENCER2019x/20x: Version upgrade from 4.9.2 to 4.11.4
* @quickReview SGA8 19:03:19 IR-673809-3DEXPERIENCER2019x: Autolink and tableresize plugin added
* @quickReview SGA8 19:03:08 IR-655433-3DEXPERIENCER2019x/20x: Upgraded CKEditor to version 4.9.2 to provide format painter
* @quickReview SGA8 19:01:31 IR-656114-3DEXPERIENCER2019x/20x: Added Special Characters Supported in Notepad
* @quickReview SGA8 18:04:20 Added Default Font size and family to be shown in editor font drop down 
*/
/*jshint bitwise:true, noarg:true, eqeqeq:true, forin:true, immed:true,
         nonew:true, undef:true, strict:true, trailing:true, regexp:true,
         unused:true, globalstrict:true, camelcase:true
         curly:false*/

"use strict";
//----------------------- KERNEL runtime access
var CMObject = new KERNEL.WebRuntime("CMObject");
var fonts;

function sendCommand(commandID, commandData) { CMObject.sendCommand(commandID, commandData); }

var customToolbar = {

  styles: { name: 'styles', items: ['Font', 'FontSize'] },
  basicstyles: { name: 'basicstyles', items: ['Bold', 'Italic', 'Underline', 'Strike', 'Subscript', 'Superscript', '-', 'CopyFormatting', 'RemoveFormat'] },
  colors: { name: 'colors', items: ['TextColor', 'BGColor'] },
  clipboard: { name: 'clipboard', items: ['Cut', 'Copy', 'Paste', 'PasteText', 'PasteFromWord', '-', 'Undo', 'Redo'] },
  align: { name: 'align', items: ['JustifyLeft', 'JustifyCenter', 'JustifyRight', 'JustifyBlock'] },
  paragraph: { name: 'paragraph', items: ['NumberedList', 'BulletedList'] },
  insert: { name: 'insert', items: ['SpecialChar', 'Image', 'Table', 'HorizontalRule'] },
  direction: { name: 'direction', items: ['BidiLtr', 'BidiRtl'] },
  links: { name: 'links', items: ['Link', 'Unlink', 'Anchor'] },
  editing: { name: 'editing', items: ['Find', 'Replace'] },
  document: { name: 'document', items: ['Print', '-', 'Templates'] }
};

var ckeditorLibPath;
//This function will load 
//ckeditor.js library file from mweb module and after that 
//any other operation will be performed
function CK_loadJSFile(commandData) {
  ckeditorLibPath = commandData.match(/(.*)[\/\\]/)[1] || '';
  var jsTag = document.createElement("script");
  jsTag.setAttribute('src', commandData);
  document.head.appendChild(jsTag);
  jsTag.onload = function () {
    sendCommand("setConfig", "");
  };
}

function CK_Init() {

  //the documentation for plugins is available on CKEditor official website
  // https://ckeditor.com/docs/ckeditor4/latest/api/CKEDITOR_config.html

  var curPath = document.location.href;

  //configuration for the editor
  CKEDITOR.config.allowedContent = true;
  CKEDITOR.config.customConfig = "";
  //Do not convert any symbol to html entity except for &nbsp; &gt; &lt; &amp;
  CKEDITOR.config.entities = false;
  CKEDITOR.config.entities_greek = false;
  CKEDITOR.config.entities_latin = false;
  //if plugins are placed at seperate location
  //CKEDITOR.plugins.addExternal('autolink', curPath.substr(0, curPath.lastIndexOf("/")) + '/plugins/autolink/');
  CKEDITOR.config.extraPlugins = 'autolink,find,font,bidi,print,tableresize,panelbutton,colorbutton,colordialog,justify,templates';
  CKEDITOR.config.removePlugins = 'about,wsc,elementspath,scayt,a11yhelp,magicline';
  //for the expander/drag icon in footer
  CKEDITOR.config.resize_enabled = false;
  CKEDITOR.config.pasteFromWordRemoveFontStyles = false;
  CKEDITOR.config.pasteFromWordRemoveStyles = false;
  CKEDITOR.config.linkShowAdvancedTab = false;
  CKEDITOR.config.removeDialogTabs = 'image:advanced';
  CKEDITOR.config.pasteFilter = null;
  CKEDITOR.config.skin = 'moono-lisa';
  CKEDITOR.config.contentsCss = ["body{font-family:Segoe UI;font-size:11px}"];
  
  //code to replace bold/italic/underline tags with styling using spans 
  /*CKEDITOR.config.coreStyles_bold = {
      element: 'span',
      styles: { 'font-weight': 'bold' }
  };

  CKEDITOR.config.coreStyles_italic = {
      element: 'span',
      styles: { 'font-style': 'italic' }
  };

  CKEDITOR.config.coreStyles_underline = {
      element: 'span',
      styles: { 'text-decoration': 'underline' }
  };*/


  //CKEDITOR.config.toolbarCanCollapse = true;
  //CKEDITOR.config.fullPage = true;

  //hiding default margin provided by browser
  document.body.style.margin = "0px";
  //document.body.style.padding = "0px";
  //document.body.style.border = "0px";

  //Replace textarea with the CKEditor
  CKEDITOR.replace('editor1', {
    //Some other Configuration for the Editor
    font_names: fonts,
    font_defaultLabel: 'Segoe UI',
    fontSize_defaultLabel: '11'
  });

  CK_AttachEvents();
};

function CK_HandleCommand(commandID, commandData) {

  if (commandID === "requestText") { CK_GetText(); }
  else if (commandID === "requestXHTMLText") { CK_GetXHTMLText(); }
  else if (commandID === "appendSpecialChar") { CK_AppendSpecialChar(commandData); }
  else if (commandID === "replaceSpecialChar") { CK_ReplaceSpecialChar(commandData); }
  else if (commandID === "configToolbar") { CK_ConfigToolbar(commandData); }
  else if (commandID === "setFontList") { CK_SetFontList(commandData); }
  else if (commandID === "loadJSFile") { CK_loadJSFile(commandData); }

}

//groups : "basicStyles,paragraph,....."
function CK_ConfigToolbar(groups) {
  CKEDITOR.config.toolbar = [];
  if (groups !== undefined && groups !== "all") {
    var tools = groups.split(",");
    for (var i in tools) {
      var plugin = customToolbar[(tools[i.toLowerCase()]).trim()];
      if (tools.hasOwnProperty(i) && plugin !== undefined)
        CKEDITOR.config.toolbar.push(plugin);
    }
  } else {
    //for all
    for (var tool in customToolbar) {
      if (customToolbar.hasOwnProperty(tool) && customToolbar[tool] !== undefined)
        CKEDITOR.config.toolbar.push(customToolbar[tool]);
    }
  }
};

function CK_SetFontList(fontList) {
  //fontList should be list of fonts ;(semicolon) seperated
  fonts = fontList;
}

function CK_SetData(data) {
  var editor = CKEDITOR.instances.editor1;
  if (editor.status === "ready") {
    editor.setData(CK_ConvertPlainTextToHTML(KERNEL.UrlDecode(data)));
  } else {
    //Event listener needed as CKEDITOR.setData is asynchronous and we might call CKEDITOR.getData 
    //before CKEDITOR.setData has completed execution
    editor.on('dataReady', function (event) {
      //Remove Listener, as if we don't, it will be called each time data is modified
      event.removeListener();
      event.editor.setData(CK_ConvertPlainTextToHTML(KERNEL.UrlDecode(data)));
    });
  }
}

function CK_SetXHTMLData(data) {
  var editor = CKEDITOR.instances.editor1;
  if (editor.status === "ready") {
    editor.setData(KERNEL.UrlDecode(data));
  } else {
    //Event listener needed as CKEDITOR.setData is asynchronous and we might call CKEDITOR.getData 
    //before CKEDITOR.setData has completed execution
    editor.on('dataReady', function (event) {
      //Remove Listener, as if we don't, it will be called each time data is modified
      event.removeListener();
      event.editor.setData(KERNEL.UrlDecode(data));
    });
  }
}

function CK_GetText() {
  if (CKEDITOR.instances.editor1.status === "ready") {
    sendCommand("textRequested", KERNEL.UrlEncode(CK_GetPlainText(CKEDITOR.instances.editor1.getData())));
  } else {
    //Event listener needed as CKEDITOR.setData is asynchronous and we might call CKEDITOR.getData 
    //before CKEDITOR.setData has completed execution
    CKEDITOR.instances.editor1.on('dataReady', function (event) {
      //Remove Listener as it will be called each time data is modified
      event.removeListener();
      sendCommand("textRequested", KERNEL.UrlEncode(CK_GetPlainText(event.editor.getData())));
    });
  }
}

function CK_GetPlainText(strSrc) {
  var resultStr = "";

  // Ignore the <p> tag if it is in very start of the text
  if (strSrc.indexOf('<p>') == 0)
    resultStr = strSrc.substring(3);
  else
    resultStr = strSrc;

  // Replace <p> with two newlines
  //resultStr = resultStr.replace(/<p>/gi, "\r\r");
  // Replace <br /> with one newline
  //resultStr = resultStr.replace(/<br \/>/gi, "\r");
  //resultStr = resultStr.replace(/<br>/gi, "\r");

  //-+-+-+-+-+-+-+-+-+-+-+
  // Strip off other HTML tags.
  //-+-+-+-+-+-+-+-+-+-+-+
  return resultStr.replace(/<[^<|>]+?>/gi, '');
}

function CK_ConvertPlainTextToHTML(strSrc) {
  var resultStr = "<p>"
  resultStr += strSrc.replace(/\n\n/gi, "</p><p>");
  resultStr = resultStr.replace(/\n/gi, "<br />");
  resultStr += "</p>";

  return resultStr;
}

//add special characters available in CATVidCtlNotepad and not available by default in CKEditor
function CK_AddNotepadChars() {
  //adding missing special characters together at end.
  var charsToInsert = "∏,±,≠,≥,≤,∞,∆,√,Ω,α,β";
  CK_AppendSpecialChar(charsToInsert);
}


/**
 * Function to add special characters to the special character list in the editor
**/
function CK_AppendSpecialChar(charsString) {
  var charsArray = charsString.split(',');
  CKEDITOR.config.specialChars = CKEDITOR.config.specialChars.concat(charsArray);
}

function CK_ReplaceSpecialChar(charsString) {
  var charsArray = charsString.split(',');
  CKEDITOR.config.specialChars = charsArray;
}

function CK_GetXHTMLText() {
  if (CKEDITOR.instances.editor1.status === "ready") {
    sendCommand("XHTMLTextRequested", KERNEL.UrlEncode(CKEDITOR.instances.editor1.getData()));
  } else {
    //Event listener needed as CKEDITOR.setData is asynchronous and we might call CKEDITOR.getData 
    //before CKEDITOR.setData has completed execution
    CKEDITOR.instances.editor1.on('dataReady', function (event) {
      //Remove Listener as it will be called each time data is modified
      event.removeListener();
      sendCommand("XHTMLTextRequested", KERNEL.UrlEncode(event.editor.getData()));
    });
  }
}

function _getHeight() {
  return window.innerHeight - 1;
}


//Event Handlers----------------Start---------------------------

//HACK to get CKEditor DOM element
//var editor_element = document.getElementById("cke_" + evt.editor.name);

function CK_AttachEvents() {

  CKEDITOR.instances.editor1.on('loaded', function (evt) {
    //maximize the editor to take complete browser area and autoresize on changing dimensions
    //evt.editor.execCommand('maximize'); //causes scroll issue IR-688645
    evt.editor.resize('100%', _getHeight()); 
  });

  //When the Editor Instance is fully ready for interaction
  CKEDITOR.instances.editor1.on('instanceReady', function (evt) {
    //maximize the editor to take complete browser area and autoresize on changing dimensions
    //evt.editor.execCommand('maximize'); //causes scroll issue IR-688645
    evt.editor.resize('100%', _getHeight()); 

    sendCommand("editorInstanceReady");
  });

  //disable dialog resize
  CKEDITOR.on('dialogDefinition', function (ev) {

    ev.data.definition.resizable = CKEDITOR.DIALOG_RESIZE_NONE;
  });

  CKEDITOR.on('dialogDefinition', function (ev) {

    var dialogName = ev.data.name;
    var dialogDefinition = ev.data.definition;

    //To remove default paste security message
    if (dialogName == 'paste' && ev.editor.name == 'editor1') {

      var generalTab = dialogDefinition.getContents('general');
      generalTab.remove('securityMsg');
    }

    else if (dialogName == 'table' && ev.editor.name == 'editor1') {
      dialogDefinition.removeContents('advanced');
    }
  });

  CKEDITOR.instances.editor1.on('key', function (evt) {
    if (evt.data.keyCode == 116 || evt.data.keyCode == CKEDITOR.CTRL + 82 || evt.data.keyCode == CKEDITOR.CTRL + 116) {
      // Disabling Refresh

      // Cancel the event, so other listeners will not be executed and
      // the keydown's default behavior will be prevented.
      evt.cancel();
    }
  });

  var KeyHandler = function () {
    switch (event.keyCode) {
      case 116: //F5 Key
        event.returnValue = false;
        event.keyCode = 0;
        return false;
      case 82: //R Key
        if (event.ctrlKey) {
          event.returnValue = false;
          event.keyCode = 0;
          return false;
        }
    }
  };

  window.addEventListener("keydown", KeyHandler, 1);

  window.addEventListener("resize", function () {
    CKEDITOR.instances.editor1.resize("100%", _getHeight()); //IR-688645
  });

};

//Event Handlers----------------End---------------------------
