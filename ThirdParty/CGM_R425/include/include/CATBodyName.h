#ifndef CATBodyName_H
#define CATBodyName_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//===========================================================================
// to put a debug name on a body.
#include "CATICGMObjectName.h"
#include "CATMathInline.h"
#include "CATBody.h"
#include "CATUnicodeString.h"
#include "YI00IMPL.h"
 
ExportedByYI00IMPL  void CATBodyPutName( CATBody * iBody, const CATUnicodeString & iString );

ExportedByYI00IMPL void CATBodyGetName( CATBody * iBody, CATUnicodeString & oString ); 
 
ExportedByYI00IMPL void CATBodyRemoveName( CATBody * iBody); 
 

#endif
