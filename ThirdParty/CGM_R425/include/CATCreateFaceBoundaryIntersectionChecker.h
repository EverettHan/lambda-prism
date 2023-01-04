// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  09/10/2000
//
// Methode permettant la creation d'une instance de l'operateur de check
// d'auto-intersection de frontiere (loops) de face.
//=============================================================================

#ifndef __CATCreateFaceBoundaryIntersectionChecker_h__ 
#define __CATCreateFaceBoundaryIntersectionChecker_h__ 

#include "CheckOperators.h"

class CATFaceBoundaryIntersectionChecker;
class CATGeoFactory;
class CATBody;
class CATTopData;


//--------------------------------------------------------------------------
//
// Methode: CATCreateFaceBoundaryIntersectionChecker
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

ExportedByCheckOperators CATFaceBoundaryIntersectionChecker *
CATCreateFaceBoundaryIntersectionChecker(CATGeoFactory     * iFactory,
                                         CATTopData        * iData,
                                         CATBody           * iBodyToCheck);
 
#endif
