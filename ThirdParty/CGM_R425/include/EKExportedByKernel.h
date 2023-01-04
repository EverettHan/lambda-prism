//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/06/25
//===================================================================

#ifndef EKExportedByKernel_H
#define EKExportedByKernel_H

#include "DSYExport.h"

#ifndef EK_NO_EXPORTS
#ifdef _STATIC_SOURCE
#define EK_NO_EXPORTS
#endif /*_STATIC_SOURCE*/
#endif /*EK_NO_EXPORTS*/

#ifdef EK_NO_EXPORTS
# define ExportedByKernel DSYLocal
#else
# ifdef __ExperienceKernel
#  define ExportedByKernel DSYExport
# else
#  define ExportedByKernel DSYImport
# endif
#endif /*EK_NO_EXPORTS*/

#endif /*EKExportedByKernel_H*/
