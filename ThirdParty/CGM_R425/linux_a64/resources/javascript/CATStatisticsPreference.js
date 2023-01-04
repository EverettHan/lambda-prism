//-----------------------------------------------
//  Function :: Activate_NbCopies
//-----------------------------------------------
var Activate_NbCopies =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_SpinnterValue = 0;
    if (argLength == 1 && 0 < inputArgumentArray[0].length)
        l_SpinnterValue = Number(inputArgumentArray[0]);

    if(l_SpinnterValue <= 0) l_SpinnterValue = 0;
    else l_SpinnterValue = 1;

    return l_SpinnterValue;
}

//-----------------------------------------------
//  Function :: Activate_WORKBENCH_TimeUnit
//-----------------------------------------------
var Activate_WORKBENCH_TimeUnit =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_WORKBENCH_ELPS = 0;
    var l_WORKBENCH_RTIM = 0;
    var l_WORKBENCH_CPUS = 0;
    var l_RetValue       = 0;
    if (argLength == 3)
    {
        if(0 < inputArgumentArray[0].length)
            l_WORKBENCH_ELPS = Number(inputArgumentArray[0]);
        if(0 < inputArgumentArray[1].length)
            l_WORKBENCH_RTIM = Number(inputArgumentArray[1]);
        if(0 < inputArgumentArray[2].length)
            l_WORKBENCH_CPUS = Number(inputArgumentArray[2]);
            
        l_RetValue = l_WORKBENCH_ELPS + l_WORKBENCH_RTIM + l_WORKBENCH_CPUS;
    }

    if(l_RetValue <= 0) l_SpinnterValue = 0;
    else l_RetValue = 1;

    return l_RetValue;
}

//-----------------------------------------------
//  Function :: Activate_SESSION_TimeUnit
//-----------------------------------------------
var Activate_SESSION_TimeUnit =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_SESSION_ELPS = 0;
    var l_SESSION_RTIM = 0;
    var l_SESSION_CPUS = 0;
    var l_RetValue       = 0;
    if (argLength == 3)
    {
        if(0 < inputArgumentArray[0].length)
            l_SESSION_ELPS = Number(inputArgumentArray[0]);
        if(0 < inputArgumentArray[1].length)
            l_SESSION_RTIM = Number(inputArgumentArray[1]);
        if(0 < inputArgumentArray[2].length)
            l_SESSION_CPUS = Number(inputArgumentArray[2]);
            
        l_RetValue = l_SESSION_ELPS + l_SESSION_RTIM + l_SESSION_CPUS;
    }

    if(l_RetValue <= 0) l_SpinnterValue = 0;
    else l_RetValue = 1;

    return l_RetValue;
}

//-----------------------------------------------
//  Function :: Activate_COMMAND_TimeUnit
//-----------------------------------------------
var Activate_COMMAND_TimeUnit =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_COMMAND_ELPS = 0;
    var l_COMMAND_RTIM = 0;
    var l_COMMAND_CPUS = 0;
    var l_RetValue       = 0;
    if (argLength == 3)
    {
        if(0 < inputArgumentArray[0].length)
            l_COMMAND_ELPS = Number(inputArgumentArray[0]);
        if(0 < inputArgumentArray[1].length)
            l_COMMAND_RTIM = Number(inputArgumentArray[1]);
        if(0 < inputArgumentArray[2].length)
            l_COMMAND_CPUS = Number(inputArgumentArray[2]);
            
        l_RetValue = l_COMMAND_ELPS + l_COMMAND_RTIM + l_COMMAND_CPUS;
    }

    if(l_RetValue <= 0) l_SpinnterValue = 0;
    else l_RetValue = 1;

    return l_RetValue;
}

//-----------------------------------------------
//  Function :: Activate_ERRORLOG_TimeUnit
//-----------------------------------------------
var Activate_ERRORLOG_TimeUnit =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_ERRORLOG_ELPS = 0;
    var l_ERRORLOG_RTIM = 0;
    var l_ERRORLOG_CPUS = 0;
    var l_RetValue       = 0;
    if (argLength == 3)
    {
        if(0 < inputArgumentArray[0].length)
            l_ERRORLOG_ELPS = Number(inputArgumentArray[0]);
        if(0 < inputArgumentArray[1].length)
            l_ERRORLOG_RTIM = Number(inputArgumentArray[1]);
        if(0 < inputArgumentArray[2].length)
            l_ERRORLOG_CPUS = Number(inputArgumentArray[2]);
            
        l_RetValue = l_ERRORLOG_ELPS + l_ERRORLOG_RTIM + l_ERRORLOG_CPUS;
    }

    if(l_RetValue <= 0) l_SpinnterValue = 0;
    else l_RetValue = 1;

    return l_RetValue;
}

//-----------------------------------------------
//  Function :: Activate_NETWORK_TimeUnit
//-----------------------------------------------
var Activate_NETWORK_TimeUnit =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_NETWORK_ELPS = 0;
    var l_NETWORK_RTIM = 0;
    var l_NETWORK_CPUS = 0;
    var l_RetValue       = 0;
    if (argLength == 3)
    {
        if(0 < inputArgumentArray[0].length)
            l_NETWORK_ELPS = Number(inputArgumentArray[0]);
        if(0 < inputArgumentArray[1].length)
            l_NETWORK_RTIM = Number(inputArgumentArray[1]);
        if(0 < inputArgumentArray[2].length)
            l_NETWORK_CPUS = Number(inputArgumentArray[2]);
            
        l_RetValue = l_NETWORK_ELPS + l_NETWORK_RTIM + l_NETWORK_CPUS;
    }

    if(l_RetValue <= 0) l_SpinnterValue = 0;
    else l_RetValue = 1;

    return l_RetValue;
}

//-----------------------------------------------
//  Function :: Activate_PCS_TimeUnit
//-----------------------------------------------
var Activate_PCS_TimeUnit =function (args) {
    var inputArgumentArray = arguments[0];
    var argLength = inputArgumentArray.length;

    var l_PCS_ELPS = 0;
    var l_PCS_RTIM = 0;
    var l_PCS_CPUS = 0;
    var l_RetValue       = 0;
    if (argLength == 3)
    {
        if(0 < inputArgumentArray[0].length)
            l_PCS_ELPS = Number(inputArgumentArray[0]);
        if(0 < inputArgumentArray[1].length)
            l_PCS_RTIM = Number(inputArgumentArray[1]);
        if(0 < inputArgumentArray[2].length)
            l_PCS_CPUS = Number(inputArgumentArray[2]);
            
        l_RetValue = l_PCS_ELPS + l_PCS_RTIM + l_PCS_CPUS;
    }

    if(l_RetValue <= 0) l_SpinnterValue = 0;
    else l_RetValue = 1;

    return l_RetValue;
}
