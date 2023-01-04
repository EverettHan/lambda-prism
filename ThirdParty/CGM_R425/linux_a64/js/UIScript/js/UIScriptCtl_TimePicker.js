/*************************************************************************/
/* UIScriptCtl_TimePicker.js                                             */
/*                                                                       */
/* A time picker control                                                  */
/*                                                                       */
/*************************************************************************/
(function (ctl) {

  var combo = UI.getElement(ctl, "InternalCombo");
  if (combo !== undefined) {
    var items = new Array();
    for (var i = 0; i < 24; i++) {
      var hour = i % 12 + "";
      var suf = i > 11 ? " PM" : " AM";
      if (hour.length === 1) hour = "0" + hour;
      if (i === 12) hour = "" + i;
      items[i * 2] = hour + ":00" + suf;
      items[i * 2 + 1] = hour + ":30" + suf;
    }
    combo.AddItems(items);
    combo.SelectedIndex = 24;
  }
})(ctl);

/*************************************************************************/ 
