#ifndef CATPGMCreateBodyHealerOperator_h_
#define CATPGMCreateBodyHealerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATIPGMTopBodyHealerOperator;
class CATTopData;



//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateBodyHealerOperator
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
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopBodyHealerOperator *CATPGMCreateBodyHealerOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToClean);

#endif /* CATPGMCreateBodyHealerOperator_h_ */
