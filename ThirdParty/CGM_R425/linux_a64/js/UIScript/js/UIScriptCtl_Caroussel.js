/*************************************************************************/
/* UIScriptCtl_Caroussel.js                                              */
/*                                                                       */
/* A small caroussel control                                             */
/*                                                                       */
/*************************************************************************/
(function () {

  var slideNumbers = 4, slideWidth = 522, slideHeight = 298, selectedIndex = 0,
  slideSizeStr = slideWidth + " " + slideHeight;

  var scrollable = UI.getElement(ctl, "scrollable");

  function selectButton(buttons, selectedIndex) {
    for (var i = 0, b, len = buttons.length; i < len; i++) {
      b = buttons[i]; b.CheckState = (b._index === selectedIndex);
    }
    ctl.Data = { selectedPicture: "medium" + selectedIndex + ".jpg" };
  }

  function MyCustomSlide(index) {
    var slide = UI.createElement("CATVidGPSquare", {
      UseManipulatorFlag: true,
      PickFlag: true,
      RequestedMinimumDimension: slideSizeStr,
      Texture: "VidGallery/medium" + (index + 1) + ".jpg"
    });
    slide.addEventListener("Press", function () {
      UI.animate(scrollable, { HScrollOffset: -slideWidth * ((index + 1) % slideNumbers) }, 0.8, 1, false, "BounceOut");
      selectButton(idButtons, (index + 1) % slideNumbers);
    });
    return slide;
  }

  function MyButtonIndex(index) {
    var path = "icons/ActionBar/SWXUiActionBarMiniNavCircle";
    var buttonIndex = UI.createElement("CATVidCtlButtonIcon", {
      OnTexture: path + "Active.png",
      OffTexture: path + "Default.png",
      OverTexture: path + "Hover.png",
      CheckMode: true,
      _index: index,
      RequestedMinimumDimension: "14 16"
    });
    buttonIndex.addEventListener("Click", function () {
      UI.animate(scrollable, { HScrollOffset: -slideWidth * ((index) % slideNumbers) }, 0.8, 1, false, "BounceOut");
      selectButton(idButtons, index);
    });
    return buttonIndex;
  }

  var buttons = [], idButtons = [];
  for (var i = 0; i < slideNumbers; i++) {
    buttons.push({ child: new MyCustomSlide(i), constraint: "x=" + i + " y=0 attach=LRTB" });
    idButtons.push(new MyButtonIndex(i));
  }

  scrollable.RequestedMinimumDimension = slideSizeStr;
  scrollable.ScrolledWidget = UI.createElement("CATVidLayGrid", {
    RequestedMinimumDimension: slideNumbers * slideWidth + " " + slideHeight,
    Children: buttons
  });

  UI.getElement(ctl, "buttonsContainer").Children = idButtons;

  selectButton(idButtons, 0);

})();

/*************************************************************************/ 
