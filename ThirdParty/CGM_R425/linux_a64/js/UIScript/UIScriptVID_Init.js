(function(UI){
    
    var ctx = UI._uiContext; 
    if (ctx === undefined) 
      return;

    UI.getElement = function (iObj, iName) 
    {
      var myObj = null; 
      if (ctx.getVIDElement)
      {
          myObj = ctx.getVIDElement(iObj, iName);
          if (myObj !== undefined && myObj !== null)
          {
              UI.fillProperties(myObj);
          }
      } 
      return myObj; 
    }

    //UI.getIndexedConstraints = function(iLay, iChild, oConstraints) { ctx.getIndexedConstraints(iLay, iChild, oConstraints); };
    //UI.setIndexedConstraints = function(iLay, iChild, iConstraints) { ctx.setIndexedConstraints(iLay, iChild, iConstraints); };

})(UI); 
