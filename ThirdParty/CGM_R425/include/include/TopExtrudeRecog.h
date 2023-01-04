#ifdef _STATIC_SOURCE
#define	ExportedByMdlTopExtr
#elif defined __MdlExtrRecog
#define ExportedByMdlTopExtr DSYExport
#else
#define ExportedByMdlTopExtr DSYImport
#endif
#include "DSYExport.h"

