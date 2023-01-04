/*************************************************************************/
/* UIScriptCtl_Calculator.js                                             */
/*                                                                       */
/* A calculator control                                                  */
/*                                                                       */
/*************************************************************************/
(function (ctl) {

  var result = UI.getElement(ctl, "Result");
  result.Text = "0";

  function updateData() {
    ctl.Data = {
      result: parseFloat(result.Text)
    }
  }

  UI.getElement(ctl, "BtnReset").addEventListener("Click", function () {
    result.Text = "0";
    updateData();
  });

  UI.getElement(ctl, "BtnResult").addEventListener("Click", function () {
    result.Text = eval(result.Text + "") + "";
    updateData();
  });

  var operators = new Array("+", "-", "*", "/");

  function isOperator(fragment) { return (operators.indexOf(fragment) != -1); }

  function add(fragment) {
    var lastValue = result.Text + "";
    if (isOperator(lastValue.slice(-1)) && isOperator(fragment)) {
      result.Text = lastValue.substring(0, lastValue.length - 1) + fragment;
      return;
    }

    if (lastValue == "0" && (!isOperator(fragment) || fragment == ".")) {
      lastValue = fragment;
    }
    else {
      lastValue += fragment;
    }

    result.Text = lastValue;
  }

  for (var i = 0; i < 15; i++) {
    var btn = UI.getElement(ctl, "Btn" + i);
    btn.RequestedMinimumDimension = "40 20";
    btn.addEventListener("Click", function () {
      add(this.Label + "");
    });
  }

})(ctl);

/*************************************************************************/ 
