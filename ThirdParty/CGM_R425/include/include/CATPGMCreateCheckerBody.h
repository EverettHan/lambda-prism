#ifndef CATPGMCreateCheckerBody_h_
#define CATPGMCreateCheckerBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"

class CATBody;
class CATIPGMChecker;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATCell);

//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateCheckerBody
//
// Auteurs: JHN        Date: 23/09/2006
//
// Description: 
//   Creation d'une intance de l'operateur de check de Body.
//   
// Arguments:
//   iFactory       Container geometrique de iBodyToCheck
//   iData          Configuration pour le versionning + journaling
//   iBodyToCheck   Body contenant une ou plusieurs faces a checker
//   iCellsToCheck  Liste des cellules potentiellement modifiees du body. Elles sont a verifier.
//   
// Retour:
//     Pointeur sur une instance d'operateur topologique
//   
//--------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMChecker *CATPGMCreateBodyChecker(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCheck,
  CATLISTP(CATCell) *iCellsToCheck = 0);

#endif /* CATPGMCreateCheckerBody_h_ */
