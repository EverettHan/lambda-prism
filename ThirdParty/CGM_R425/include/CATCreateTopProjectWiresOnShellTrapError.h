// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
// Creation JHN,ICE  16/06/2004
//
//  Cf. CATCreateTopProjectWiresOnShell.h
//
//=============================================================================

#ifndef __CATCreateTopProjectWiresOnShellTrapError_h__
#define __CATCreateTopProjectWiresOnShellTrapError_h__

#include "ExportedByCATTopologicalObjects.h"

class CATGeoFactory;
class CATTopData;
class CATMathDirection;
class CATBody;
class CATTopProjectWiresOnShell;

ExportedByCATTopologicalObjects CATTopProjectWiresOnShell *
CATCreateTopProjectWiresOnShellTrapError(CATGeoFactory * iFactory,
                             CATTopData       * iTopData,
                             CATMathDirection * iDirection,
                             CATBody          * iWiresBody,
                             CATBody          * iShellBody);

#endif
