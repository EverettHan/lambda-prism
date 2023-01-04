// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// Methode permettant la creation d'une instance de l'operateur de simplification
// d' un body contenant des wires (iWiresBody) sur un iShellBody.
//
// - Si un wire ne se simplifie pas, il est reporte dans le body resultat.
// - Si un shell est specifie (SetSupportShell), on ne simplifie que les wires poses sur ce shell.
//   Les autres wires sont ignores et ne sont pas reportes dans le body resultat.
//=============================================================================

#ifndef __CATCreateSimplifyLayDownWireOnShell_h__ 
#define __CATCreateSimplifyLayDownWireOnShell_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopSimplifyLayDownWireOnShell;
class CATGeoFactory;
class CATTopData;
class CATBody;

//--------------------------------------------------------------------------
//
// Methode: CATCreateLayDownWireOnShell
//
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopSimplifyLayDownWireOnShell *
CATCreateSimplifyLayDownWireOnShell(CATGeoFactory * iFactory,
                                    CATTopData    * iTopData,
                                    CATBody       * iWorkingBody,
                                    CATBody       * iWireBody,
                                    CATBody       * iShellBody);

#endif
