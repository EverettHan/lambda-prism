// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// Methode permettant la creation d'une instance de l'operateur de posage
// d' un body contenant des wires (iWiresBody) et uniquement des wires sur un iShellBody.
//=============================================================================

#ifndef __CATCreateLayDownWiresOnShell_h__ 
#define __CATCreateLayDownWiresOnShell_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopLayDownWiresOnShell;
class CATGeoFactory;
class CATTopData;
class CATBody;

//--------------------------------------------------------------------------
//
// Methode: CATCreateLayDownWiresOnShell
//
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopLayDownWiresOnShell *
CATCreateLayDownWiresOnShell(CATGeoFactory * iFactory,
                             CATTopData    * iTopData,
                             CATBody       * iWorkingBody,
                             CATBody       * iWiresBody,
                             CATBody       * iShellBody);

#endif






