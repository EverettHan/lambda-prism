// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation NVT 31/01/2001
//
// Methode permettant la creation d'une instance de l'operateur de 
// reparation et nettoyage de body
//=============================================================================

#ifndef __CATCreateWireHealerOperator_h__ 
#define __CATCreateWireHealerOperator_h__ 

#include "ExportedByCATTopologicalObjects.h"

class CATTopWireHealerOperator;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateWireHealerOperator
//
// Auteurs: NVT        Date: 31/01/2001
//
// Description: 
//    Creation d'une instance de l'operateur de 
//    reparation et nettoyage de body
// Arguments:
//   iFactory               Container geometrique de iBodyToRecompose
//   iData                  Configuration pour le versionning + journaling
//   iBodyToClean       
//   
// Retour:
//   
//--------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATTopWireHealerOperator *
CATCreateWireHealerOperator(CATGeoFactory * iFactory,
                        CATTopData    * iData,
                        CATBody       * iBodyToClean);

#endif

