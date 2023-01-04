(function(UI){
    
    var ctx = UI._uiContext; 
    if (ctx === undefined) 
      return;

    UI.fillProperties = function(iObj) {
    
      var introspectableProperties = ctx.GetProperties(iObj);

      for (var i = introspectableProperties.length - 1; i > -1; i--) {
          var myProp = introspectableProperties[i];
          if (!iObj.hasOwnProperty(myProp)) {
              Object.defineProperty(iObj, myProp, {
                  configurable: true, 
                  get: (function (propName) {
                      return function () { return ctx.GetProperty(this, propName); }
                  })(myProp),
                  set: (function (propName) {
                      return function (newVal) { ctx.SetProperty(this, propName, newVal); }
                  })(myProp)
              });
          }
      }

      // Not the good way to observe properties (no way to be notified when a change is performed on c++ side.
      // Try to bind services as CATSYP::Connect instead)
      /*
      Object.defineProperty(iObj, "addTrigger", {
          enumerable: false,
          configurable: true,
          writable: false,
          value: function (prop, handler) 
          {
              if (delete this[prop]) { // can't watch constants
                Object.defineProperty(this, prop, {
                  get: function () { return ctx.GetProperty(this, prop); }, 
                  set: function (val) {
                    oldval = ctx.GetProperty(this, prop);
                    handler.call(this, prop, oldval, val);
                    return ctx.SetProperty(this, prop, val);
                  },
                  enumerable: true, 
                  configurable: true,
                });
              }
              else {
                alert("can't delete this property");
              }
          }
      });
      */

     iObj.addEventListener = function(eventType, eventListener) {
        if (eventListener !== undefined && eventType !== "")
        {
          return ctx.AddEventListener(this, eventType, eventListener);
        }
      };
     
     iObj.removeEventListener = function(eventType, eventListener) {
        if (eventListener !== undefined && eventType !== "")
        {
          return ctx.RemoveEventListener(this, eventType, eventListener);
        }
      };
    };
    
    UI.createElement =  function (iName, iPropList)
    {
      var myObj = ctx.createNativeElement(iName);
      UI.fillProperties(myObj);
      if (iPropList) 
      {
          for (var prop in iPropList) {
              myObj[prop] = iPropList[prop];
          }
      }
      return myObj; 
    };

    UI.animate = function(iCmd, iParams, iDuration, iRepeatBehavior, iAutoReverseFlag, iEasingMode) { 
      return ctx.animate(iCmd, iParams, iDuration, iRepeatBehavior, iAutoReverseFlag, iEasingMode); 
    };
     
    UI.loadJSON = function(iFilePath) { 
      return ctx.loadJSON(iFilePath); 
    };

    UI.evaluateScript = function(iScript) {
     return ctx.evaluateScript(iScript); 
    };

    UI.connect= function (iSource, iSourceName, iTarget, iTargetName) {
      return ctx.connect(iSource, iSourceName, iTarget, iTargetName);
    };
  
    // move to UIScriptV3D
    /*
    UI.attachToCurrentViewpoint = function(iObj) { return ctx.attachToCurrentViewpoint(iObj); };
    
    UI.getV3DElement = function (iObj, iName)
    {
        var myObj = null;
        if (ctx.getV3DElement)
        {
            myObj = ctx.getV3DElement(iObj, iName);
            if (myObj !== undefined && myObj !== null)
            {
                UI.fillProperties(myObj);
            }
        }
        return myObj;
    };
    */
    // <-- UIScriptV3D

})(UI); 
