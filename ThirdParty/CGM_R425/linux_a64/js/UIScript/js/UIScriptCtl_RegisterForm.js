/*************************************************************************/
/* UIScriptCtl_RegisterForm.js                                           */
/*                                                                       */
/* An example of register form with input validators using regexps       */
/*                                                                       */
/*************************************************************************/

(function () {

  function initInput(inputName, validator, inputName2) {
    var input = UI.getElement(ctl, inputName),
        icon = UI.getElement(ctl, inputName + "Validate"),
        msg = UI.getElement(ctl, inputName + "ValidateMsg"),
        input2 = null;

    if (typeof (inputName2) === "string" && inputName2.length > 0)
      input2 = UI.getElement(ctl, inputName2);

    input.addEventListener("EditingFinished", function () {
      if ((validator && validator.exec(input.Text) == null)
       || (input2 !== null && input.Text !== input2.Text)) {
        icon.Texture = "icons/I_ReorderDlgClose.png";
        icon.VisibleFlag = msg.VisibleFlag = true;
      }
      else {
        icon.Texture = "icons/I_ReorderDlgOK.png";
        icon.VisibleFlag = true; msg.VisibleFlag = false;
      }
    });
    return input;
  }

  var email    = initInput("email", /^([a-z0-9_\.-]+)@([\da-z\.-]+)\.([a-z\.]{2,6})$/);
  var username = initInput("username", /^[a-zA-Z0-9_-]{3,16}$/);
  var password = initInput("password", /^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{6,16}$/);
  var confPass = initInput("confirmPass", null, "password");

})();

/*************************************************************************/ 
