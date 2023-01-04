//------------------------------------------------------------------------------
#ifdef _STATIC_SOURCE
#define	ExportedByPersistentCell
#elif defined __PersistentCell
#define ExportedByPersistentCell DSYExport
#else
#define ExportedByPersistentCell DSYImport
#endif
#include "DSYExport.h"
//------------------------------------------------------------------------------
