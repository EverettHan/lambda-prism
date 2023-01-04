#ifndef CATPGMCreateWireHealerOperator_h_
#define CATPGMCreateWireHealerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopWireHealerOperator;

//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateWireHealerOperator
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
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopWireHealerOperator *CATPGMCreateWireHealerOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToClean);

#endif /* CATPGMCreateWireHealerOperator_h_ */
