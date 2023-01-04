#ifndef CATCGMForceBSFLevelAllConfigs_h
#define CATCGMForceBSFLevelAllConfigs_h

// COPYRIGHT DASSAULT SYSTEMES  2001

#include "ExportedByCATMathStream.h"

//----------------------------------------------------------------------------
// FOR INTERNAL USE ONLY
//----------------------------------------------------------------------------

#undef ExportedCATCGMForceBSFLevelAllConfigs

#ifdef	_WINDOWS_SOURCE
#if defined (__CATMathematics ) || defined (__CATMathStream) \
 || defined (__CATGeometricObjects) || defined (__CATTopologicalObjects) || defined (__CATGMModelInterfaces) \
 || defined (__CATTechGem ) || defined (__CATGem) || defined (__CATCGMChainUISW)   || defined (__CATCXDebug) || defined (__dsc_Update) 
#define  ExportedCATCGMForceBSFLevelAllConfigs  ExportedByCATMathStream
#else
#error Forbidden Access To CATCGMForceBSFLevelAllConfigs 
#endif
#else
#define  ExportedCATCGMForceBSFLevelAllConfigs  ExportedByCATMathStream
#endif

//----------------------------------------------------------------------------
// FOR INTERNAL USE ONLY
//----------------------------------------------------------------------------
ExportedByCATMathStream void  CATCGMForceBSFLevelAllConfigs(short iForAllCGMLevel);
ExportedByCATMathStream short CATCGMQueryBSFLevelAllConfigs();


class CATCGMNewMetaBloc;
ExportedByCATMathStream void CATTopDataSetNewMetaBloc( CATCGMNewMetaBloc *iMetaBloc );

#endif
