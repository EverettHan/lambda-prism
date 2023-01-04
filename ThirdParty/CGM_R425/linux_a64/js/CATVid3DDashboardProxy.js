/***************************************************************/
/** CATVid3DDashboardProxy.js                                  */
/***************************************************************/

var fillDashboardList = function () {
  require(["ds/PublicAPI"], function (DS_PublicAPI) {
    // retrieve dashboard list and format response
    DS_PublicAPI.getAllContexts({
      success: function () {
        var response = "";

        DS_PublicAPI.contexts
          .filter(function (element) { return (element.type === "dashboard" && element.owner === true) })
          .sort(function (a, b) { if (a.name > b.name) return 1; else if (a.name < b.name) return -1; else return 0; })
          .forEach(function (element, index, array) { response += element.name + "=" + element.modelId + ";" });

        response = response.slice(0, -1);

        // send command to native proxy with the built response
        CATCefSendString("api/context/nativeGetList://" + response);
      }
    });
   
  });
}

var getLastOpenedDashboardId = function () {
  require(["ds/PublicAPI"], function (DS_PublicAPI) {
    DS_PublicAPI.getUserAsync({
      retryNumber: 1,      // retryNumber
      success: function () {  // success
        console.log(DS_PublicAPI.getUserProperty("lastOpenedDashboardId"));
        CATCefSendString("api/users/nativeCurrent://" + DS_PublicAPI.getUserProperty("lastOpenedDashboardId"));
      },
      failure: function () {} // failure 
    });
  });
}


var getTabsList = function (iID) {
  require(["ifwe/PublicAPI"], function (IFWE_PublicAPI) {
    var options = {
      id: iID,
      success: function (r) {
        var response = "";
        r.forEach(function (element, index, array) { response += element.name + "=" + element.id + ";" });
        response = response.slice(0, -1);
        console.log("nativeGetDashboardTabs://" + response);
        CATCefSendString("nativeGetDashboardTabs://" + response);
      },
      failure: function (e) { }
    };

    // BIG HACK HERE :-(, issue during loading, sometimes getAllTabsData doesn't finished, with the timeout it works fine. 
    // We have to replace that when 3DD will give us a real bootstrap and not the actual way to build the web proxy.
    window.setTimeout(function () {
      IFWE_PublicAPI.getAllTabsData(options);
    }, 2000);

  });
}

var getTabsData = function (iID) {
  require(["ifwe/PublicAPI"], function (IFWE_PublicAPI) {
    var options = {
      id: iID,
      success: function (r) {
        var response = "";
        response = JSON.stringify(r);
        CATCefSendString("getTabsData://" + response);
      },
      failure: function (e) { }
    };

   IFWE_PublicAPI.getAllTabsData(options);

  });
}

var addDashboard = function (iDashboardName) {
  require(["ifwe/PublicAPI"], function (IFWE_PublicAPI) {
    var options = {
      name: iDashboardName,
      replacement: iDashboardName,
      success: function (dashboard) {
        // dashboard created
        console.log("dashboard creation successful");
        console.log(dashboard);
        CATCefSendString("dashboardCreated://" + dashboard.modelId);
      },
      failure: function () {
        // dashboard creation failure
      }
    };

    IFWE_PublicAPI.addDashboard(options);
  });
}

var setActiveDashboard = function (iDashboardId) {
  require(["ifwe/PublicAPI"], function (IFWE_PublicAPI) {
    var options = {
      id: iDashboardId,
      success: function () {
        console.log("setActiveDashboard on " + iDashboardId);
        CATCefSendString("setActiveDashboard://" + iDashboardId);
      }
    };

    IFWE_PublicAPI.setActiveDashboard(options);
  });
}

var addNewTab = function () {
  require(["ifwe/PublicAPI"], function (IFWE_PublicAPI) {
  
    // Will be replaced by addTab public API when 3DD will expose it. We need a callback here to register the tab in native world.
    var currentDashboard = IFWE_PublicAPI.getActiveDashboard();
    if (currentDashboard !== undefined && currentDashboard.layout !== undefined)
    {
      currentDashboard.layout.dispatchEvent("onNewTab");
    }
  });
}

var removeTab = function (iTabId) {
  if (iTabId !== "") {
    require(["ifwe/PublicAPI"], function (IFWE_PublicAPI) {
      var options = {
        id: iTabId
      };
      IFWE_PublicAPI.removeTab(options);
    });
  }
}
