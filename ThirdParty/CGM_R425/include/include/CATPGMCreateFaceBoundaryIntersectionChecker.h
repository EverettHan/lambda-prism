#ifndef CATPGMCreateFaceBoundaryIntersectionChecker_h_
#define CATPGMCreateFaceBoundaryIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATIPGMFaceBoundaryIntersectionChecker;
class CATGeoFactory;
class CATTopData;



//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateFaceBoundaryIntersectionChecker
//
// Auteurs: EDS        Date: 09/10/2000
//
// Description: 
//   Creation d'une intance de l'operateur de check d'auto-intersection
//   de frontiere (loops) de face.
//   
// Arguments:
//   iFactory               Container geometrique de iBodyToCheck
//   iData                  Configuration pour le versionning + journaling
//   iBodyToCheck           Body contenant une ou plusieurs faces a checker
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMFaceBoundaryIntersectionChecker *CATPGMCreateFaceBoundaryIntersectionChecker(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCheck);

#endif /* CATPGMCreateFaceBoundaryIntersectionChecker_h_ */
