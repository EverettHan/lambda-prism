#ifndef CATCGMStreamVersionUtilities_h
#define CATCGMStreamVersionUtilities_h
// COPYRIGHT DASSAULT SYSTEMES  2007

//#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

#include "CATCGMStreamVersion.h"
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
#include "CATMathStreamDef.h"
#include "CATMathStreamVersionDef.h"
#include "CATMathInline.h"
 
 
ExportedByCATMathStream CATCGMStreamVersion CATCGMStreamVersionOfCATPartSaved();

ExportedByCATMathStream CATCGMStreamVersion CATCGMStreamVersionOfNCGMSaved();

ExportedByCATMathStream int CATCGMStreamVersionsAvailable( const int iSizeOfOutput, CATCGMStreamVersion *ioOutput );

// Version String a la nomenclature CATPart/
//  1) Correctif pour phase II 
//  2) see also CATCGMStreamVersionTools::IntToString for Debug Version
ExportedByCATMathStream void CATCGMStreamShortName(const CATCGMStreamVersion input, char ioShortName[6] );


//-----------------------------------------------------------------------------
// CATCGMStreamIsNewerThanOrEqualTo / Corrrection by  V5R20 
//-----------------------------------------------------------------------------

INLINE ExportedByCATMathStream CATBoolean CATCGMStreamIsStrictlyOlderThan(const CATCGMStreamVersion first, const CATCGMStreamVersion second)
{ return ( (int)first < (int)second ) ? TRUE : FALSE;  }


#endif

