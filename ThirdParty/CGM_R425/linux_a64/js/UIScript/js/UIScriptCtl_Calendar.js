/*************************************************************************/
/* UIScriptCtl_Calendar.js                                               */
/*                                                                       */
/* A calendar control                                                    */
/*                                                                       */
/*************************************************************************/
(function (ctl) {

  var mNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
  var mDCount = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];

  var today = new Date(), todayDay = today.getDate(), todayMonth = today.getMonth(), todayYear = today.getFullYear(),
    currentDay = todayDay, currentMonth = todayMonth, currentYear = todayYear;

  data = {
    pickedDay: currentDay,
    pickedMonth: currentMonth,
    pickedYear: currentYear,
    pickedDate: today.toDateString()
  }
  ctl.Data = data;

  ctl.updateData = function (pBtnLabel) {
    var pickedDate = new Date(currentYear, currentMonth, pBtnLabel);
    data.pickedYear = pickedDate.getFullYear();
    data.pickedMonth = pickedDate.getMonth();
    data.pickedDay = pickedDate.getDate();
    data.pickedDate = pickedDate.toDateString();
    this.Data = data;
  }

  var dayButtons = new Array();
  for (var i = 0; i < 42; i++) {
    var button = UI.createElement("CATVidCtlButton", { RequestedMinimumDimension: "30 25" });
    button.addEventListener("Click", function () {
      ctl.updateData(this.Label);
    });

    dayButtons.push({
      child: button,
      constraint: "x=" + i % 7 + " y=" + 2 + Math.floor(i / 7)
    });
  }

  UI.getElement(ctl, "daysLayout").Children = dayButtons;

  function leapYear(year) { return (year % 4e2 == 0) || (!(year % 1e2 == 0) && (year % 4 == 0)) }

  function BuildCalendar() {
    UI.getElement(ctl, "monthLabel").Text = mNames[currentMonth] + " " + currentYear;

    var fDayDate = new Date(currentYear, currentMonth, 1);
    var fDay = fDayDate.getDate();
    var lDay = mDCount[currentMonth];
    if (currentMonth == 1 && leapYear(currentYear)) lDay = 29;

    var bDay;
    for (var i = 0; i < 42; i++) {
      bDay = dayButtons[i].child;
      bDay.VisibleFlag = (i > fDay - 1) && (i < lDay + fDay);
      bDay.Label = "" + (i + 1 - fDay);
      ((currentYear == todayYear) && (currentMonth == todayMonth) && (i == todayDay + 1 - fDay))
                ? bDay.ForegroundColor = "0 90 240 255"
                : bDay.ForegroundColor = "0 0 0 255";
    }
  }

  UI.getElement(ctl, "prevMonth").addEventListener("Click", function () {
    if (--currentMonth < 0) {
      currentMonth = 11; currentYear--;
    } else {
      currentMonth % 12;
    }
    BuildCalendar();
  });

  UI.getElement(ctl, "nextMonth").addEventListener("Click", function () {
    if (++currentMonth > 11) {
      currentMonth = 0; currentYear++;
    } else {
      currentMonth % 12;
    }
    BuildCalendar();
  });

  BuildCalendar();

})(ctl);

/*************************************************************************/ 
