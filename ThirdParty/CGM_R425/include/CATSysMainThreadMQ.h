#ifndef CATSysMainThreadMQ_H
#define CATSysMainThreadMQ_H

// COPYRIGHT DASSAULT SYSTEMES 2000

 /*  Definition des flags d'exportations   */
#if defined __CATSysMainThreadMQ
#define ExportedByCATSysMainThreadMQ DSYExport
#else
#define ExportedByCATSysMainThreadMQ DSYImport
#endif
#include "DSYExport.h"
#endif
