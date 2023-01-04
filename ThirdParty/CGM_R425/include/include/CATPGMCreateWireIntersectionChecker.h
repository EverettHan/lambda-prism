#ifndef CATPGMCreateWireIntersectionChecker_h_
#define CATPGMCreateWireIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMWireIntersectionChecker;



//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateWireIntersectionChecker
//
// Auteurs: EDS        Date: 11/10/2000
//
// Description: 
//   Creation d'une intance de l'operateur de check d'intersection
//   de wires.
//   
// Arguments:
//   iFactory               Container geometrique de iBodyToCheck
//   iData                  Configuration pour le versioning + journaling
//   iBodyToCheck           Body contenant un ou plusieurs wires a checker
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMWireIntersectionChecker *CATPGMCreateWireIntersectionChecker(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCheck);

#endif /* CATPGMCreateWireIntersectionChecker_h_ */
