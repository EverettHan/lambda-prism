#ifndef CATPGMCreateShellIntersectionChecker_h_
#define CATPGMCreateShellIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATIPGMShellIntersectionChecker;
class CATTopData;



//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateShellIntersectionChecker
//
// Auteurs: EDS        Date: 09/10/2000
//
// Description: 
//   Creation d'une intance de l'operateur de check d'intersection
//   shell/shell.
//   
// Arguments:
//   iFactory               Container geometrique de iBodyToCheck
//   iData                  Configuration pour le versionning + journaling
//   iBodyToCheck           Body contenant les shells a confronter
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMShellIntersectionChecker *CATPGMCreateShellIntersectionChecker(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCheck);

#endif /* CATPGMCreateShellIntersectionChecker_h_ */
