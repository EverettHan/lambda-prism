#ifndef CATPGMAppPerfTracker_h_
#define CATPGMAppPerfTracker_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

class ExportedByCATGMModelInterfaces CATPGMAppPerfTracker
{
public:
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Beginning of the run
//ipName : operator name
ExportedByCATGMModelInterfaces void CATPGMAPTStart(const char *ipName);

//The end of the run
//iIsOK : is the operator successfull or not
ExportedByCATGMModelInterfaces void CATPGMAPTEnd(CATBoolean iIsOK);

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Give environment variable
ExportedByCATGMModelInterfaces void CATPGMAPTEnv(const char *ipName);

//Give a message
ExportedByCATGMModelInterfaces void CATPGMAPTMsg(const char *ipName);

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//To activate performance tracker
ExportedByCATGMModelInterfaces void CATPGMAPTSetActivation(CATBoolean iActivation);

//To know if tracker has been activated
ExportedByCATGMModelInterfaces CATBoolean CATPGMAPTGetActivation();

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Set output (console or file)
ExportedByCATGMModelInterfaces void CATPGMAPTSetConsole(CATBoolean iConsole);

//Get output (console or file mode)
ExportedByCATGMModelInterfaces CATBoolean CATPGMAPTGetConsole();

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Get current Level
ExportedByCATGMModelInterfaces int CATPGMAPTGetLevel();

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Set depth
ExportedByCATGMModelInterfaces void CATPGMAPTSetDepth(int iDepth);

//Get depth
ExportedByCATGMModelInterfaces int CATPGMAPTGetDepth();

#endif /* CATPGMAppPerfTracker_h_ */
