//------------------------------------------------------------------------------
#ifdef _STATIC_SOURCE
#define	ExportedByMPRunnerEngine
#elif defined __MPRunnerEngine
#define ExportedByMPRunnerEngine DSYExport
#else
#define ExportedByMPRunnerEngine DSYImport
#endif
#include "DSYExport.h"
//------------------------------------------------------------------------------
