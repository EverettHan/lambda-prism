#ifndef CATCGMModifLocal_h
#define CATCGMModifLocal_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATCGMModif.h"
#include "CATIAV5Level.h"
#include "BigLittle.h"
 
// Nettoyage des donnees globales
extern ExportedByCATMathStream int CATCGMSoftwareModificationCleanForExit();

extern const CATSoftwareModification* GetCGMSoftwareModification();


extern ExportedByCATMathStream void CATCGMFirstSoftwareConfiguration();

#define _IsSupportedActif  0

//
// Defines the operating system (needed for the stream)
//
#if defined ( _ENDIAN_LITTLE )
/** @nodoc */
#define CONFIGURATION_NATIVE_FLAG 'N'
/** @nodoc */
#define CONFIGURATION_FOREIGN_FLAG 'U'
#else
/** @nodoc */
#define CONFIGURATION_NATIVE_FLAG 'U'
/** @nodoc */
#define CONFIGURATION_FOREIGN_FLAG 'N'
#endif


#endif
