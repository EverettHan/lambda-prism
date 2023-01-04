// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Methode permettant la creation d'une instance de l'operateur de 
// reparation et nettoyage de body
//=============================================================================

#ifndef __CATCreateBodyHealerOperator_h__ 
#define __CATCreateBodyHealerOperator_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopBodyHealerOperator;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateBodyHealerOperator
//
// Auteurs: ICE XDT        Date: 31/01/2001
//
// Description: 
//    Creation d'une instance de l'operateur de 
//    reparation et nettoyage de body
// Arguments:
//   iFactory               Container geometrique de iBodyToClean
//   iData                  Configuration pour le versionning + journaling
//   iBodyToClean           Body a reparer. Il ne doit etre constitue que de volumes ou que de skins ou que de wires.
//   
// Retour:
//   
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopBodyHealerOperator *
CATCreateBodyHealerOperator(CATGeoFactory * iFactory,
                            CATTopData    * iData,
                            CATBody       * iBodyToClean);

#endif

