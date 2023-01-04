#ifndef CATCGMStreamVersionNative_h
#define CATCGMStreamVersionNative_h
// COPYRIGHT DASSAULT SYSTEMES  2007
//#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

#include "CATCGMStreamVersion.h"
#include "ExportedByCATMathStream.h"
 
#define CATCGMStreamMaxNumberOfVersion 49

ExportedByCATMathStream void CATCGMStreamVersionNative_itoa(const CATCGMStreamVersion iVersion, unsigned char & oVersion);

ExportedByCATMathStream void CATCGMStreamVersionNative_atoi(const unsigned char iVersion, CATCGMStreamVersion & oVersion );

#endif

