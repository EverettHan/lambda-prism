#ifndef DSYApplicationMainTS_H
#define DSYApplicationMainTS_H

#include "CATSysTS.h"


// Save app arguments.
#define DSYSYSMAIN_GLOBAL_ARGUMENT      0x01

// WatchDog installation.
#define DSYSYSMAIN_INSTALL_WATCHDOG     0x02

// All-in-one flag.
#define DSYSYSMAIN_ALL                  (DSYSYSMAIN_GLOBAL_ARGUMENT | DSYSYSMAIN_INSTALL_WATCHDOG)


/**
 * TODO Doc
 * @param iFlag see defines DSYSYSMAIN_XXX a top of the file
 */

//=======================================================================
ExportedByCATSysTS void DSYSysMainInitialize(int iArgc, char** ippArgv, const int iFlag = DSYSYSMAIN_ALL);
//=======================================================================

#ifdef _WINDOWS_SOURCE
//=======================================================================
ExportedByCATSysTS void DSYSysMainInitialize(const int iFlag = DSYSYSMAIN_ALL);
//=======================================================================
#endif  // _WINDOWS_SOURCE

//=======================================================================
ExportedByCATSysTS void DSYSysMainFinalize(void);
//=======================================================================

#endif  // DSYApplicationMainTS_H
